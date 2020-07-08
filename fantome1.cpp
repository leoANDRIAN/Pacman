#include "fantome1.hpp"


Fantome::Fantome(int TAILLE_ENTITE, sf::Vector2i POS_INI_FANTOME_1, sf::Color couleur, int speedP, int tailleImage, float AGRANDISSEMENT, int nF){
    _fantome = Joueur(sf::Vector2f(POS_INI_FANTOME_1.x, POS_INI_FANTOME_1.y), couleur, TAILLE_ENTITE);
    _comestible = false; //peut être mangé uniquement si est commestible, fait varier le mode de deplacement
    _seDeplacer = false; //interdit de se deplacer et d'etre afficher si le fantome vient d'etre mange
    _directionSouhaite = 'd';
    _saCouleur = couleur;
    _speedF = speedP;
    _textureFantome = chargementTexture(CHEMIN_REL + "pacman.png");
    _spriteFantome1.setTexture(_textureFantome);
    _spriteFantome1.setPosition(AGRANDISSEMENT*(POS_INI_FANTOME_1.x-(1-nF)*TAILLE_ENTITE), AGRANDISSEMENT*POS_INI_FANTOME_1.y);
    const float reduc = (AGRANDISSEMENT*TAILLE_ENTITE)/ tailleImage;
    _spriteFantome1.setScale(reduc, reduc);
    _spriteFantome1.setTextureRect(sf::IntRect(37*14+3, 5*14-5 + nF*16 , 14, 14)); //fantome 1
    _numeroFantome = nF;
    _positionIniF = POS_INI_FANTOME_1;
    _vienD_etre_mange = false;
}



void Fantome::afficherFantome(sf::RenderWindow& window){
    if (!_comestible){
        //setCouleur(_saCouleur);
        _spriteFantome1.setTextureRect(sf::IntRect(37*14+3, 5*14-5 + _numeroFantome*16 , 14, 14));
    }
    else{
        //setCouleur(sf::Color::White);
        _spriteFantome1.setTextureRect(sf::IntRect(43*14-1, 5*14-4, 14, 14));
    }
    window.draw(_spriteFantome1);
}

void Fantome::deplacement(Mur ensembleMurs, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED, sf::Vector2f posPacman, float AGRANDISSEMENT){
    if(_comestible){
        _speedF = SPEED/2;
    }
    else {
        //block servant a replacer les fantomes sur une position correcte, multiple de la vitesse de déplacement pour eviter qu'ils ne sortent de la carte. Change egalement la vitesse de deplacement des fantomes egale a celle de pacman
        int posX = _fantome.getBody().getRect().getPosition().x;
        int posY = _fantome.getBody().getRect().getPosition().y;
        if (posX % 4 != 0 || posY % 4 != 0) {
            if (_directionAsuivre == 'd'){
                _fantome.deplacementJoueur(-1, 0, _spriteFantome1, SPEED, AGRANDISSEMENT);
            }
            else if (_directionAsuivre == 'q'){
                _fantome.deplacementJoueur(1, 0, _spriteFantome1, SPEED, AGRANDISSEMENT);
            }
            else if (_directionAsuivre == 'z'){
                _fantome.deplacementJoueur(0, 1, _spriteFantome1, SPEED, AGRANDISSEMENT);
            }
            else if (_directionAsuivre == 's'){
                _fantome.deplacementJoueur(0, -1, _spriteFantome1, SPEED, AGRANDISSEMENT);
            }
        }
        _speedF = SPEED;
    }
    if (_seDeplacer){
        //directionAsuivre prend la valeur DirectionSouhaite si il n'y a pas un mur dans cette direction
        _fantome.choixDirection(_directionAsuivre, _directionSouhaite, _fantome.autorisationChargerDirection(_directionSouhaite, ensembleMurs));
        //deplace pacman tant qu'il ne rencontre pas de mur
        _fantome.deplacementAutoJoueur(_directionAsuivre, ensembleMurs, _spriteFantome1, _speedF, AGRANDISSEMENT);
        //interaction avec les tunnels
        _fantome.interactionTunnelHorizontaux(t, _spriteFantome1, TAILLE_ENTITE);


        MAJ_directionInterdite();

        sf::Vector2f posFantome = _fantome.getBody().getRect().getPosition();
        int dist_X = posPacman.x - posFantome.x;
        int dist_Y = posPacman.y - posFantome.y;

        //ensemble des directions possibles à un moment donné
        std::vector<char> directionRetenu = listeDirectionPossible(ensembleMurs);

        //si il n'y a qu'un seul choix, le fantome va l'emprunté
        if (directionRetenu.size() == 1){
            _directionSouhaite=directionRetenu[0];
        }
        //si il y a plusieurs choix
        else{
            char directionOptimal = choixDirrectionOptimal(posPacman);
            //Recherche si la direction optimal fait parti des directions possible à prendre
            bool trouve = false;
            for (int i=0; i<directionRetenu.size(); i++){
                if (directionOptimal==directionRetenu[i]){
                    trouve = true;
                }
            }
            //si c'est le cas, le fantome suit la direction optimale
            if (trouve){
                _directionSouhaite = directionOptimal;
            }
            //sinon si la direction optimal ne fait pas parti des directions possible, et qu'il y a 2 choix possible de direction
            else if( (_directionPrecedente =='z' || _directionPrecedente=='s') && directionRetenu.size() == 2  && (dist_Y*dist_Y - _dist_YPrecedent) > 0){
                //si le fantome se deplace verticalement, et qu'il s'éloigne de Pacman, il va prendre une direction horizontale des qu'il le peut
                for (int i = 0; i<directionRetenu.size(); i++){
                    if (directionRetenu[i] != 'z' && directionRetenu[i] != 's'){
                        _directionAsuivre = directionRetenu[i];
                    }
                }
            }
            else if( (_directionPrecedente =='q' || _directionPrecedente=='d') && directionRetenu.size() == 2 && (dist_X*dist_X - _dist_XPrecedent) > 0){
                //si le fantome se deplace horizontalement, et qu'il s'éloigne de Pacman, il va prendre une direction verticale des qu'il le peut
                for (int i = 0; i<directionRetenu.size(); i++){
                    if (directionRetenu[i] != 'q' && directionRetenu[i] != 'd'){
                        _directionSouhaite = directionRetenu[i];
                    }
                }
            }
            else if (_positionPrecedent == _fantome.getBody().getRect().getPosition()){
                //si le fantome se retrouve bloqué car la diretion optimal n'a pas changé, il choisi la direction le menant vers pacman
                if(_directionPrecedente == 'z' || _directionPrecedente == 's'){
                    if (dist_X > 0){
                        _directionSouhaite = 'd';
                    }
                    else _directionSouhaite = 'q';
                }
                else{
                    if (dist_Y >0){
                        _directionSouhaite = 's';
                    }
                    else{
                        _directionSouhaite = 'z';
                    }
                }
            }

        }


        //MAJ des choix precedent
        _positionPrecedent = _fantome.getBody().getRect().getPosition();
        _directionPrecedente = _directionAsuivre;
        _dist_XPrecedent = dist_X*dist_X;
        _dist_YPrecedent = dist_Y*dist_Y;
    }
}

void Fantome::MAJ_directionInterdite(){
    if (_directionAsuivre=='d'){
        _directionInterdit ='q';
    }
    else if (_directionAsuivre=='q'){
        _directionInterdit='d';
    }
    else if (_directionAsuivre=='z'){
        _directionInterdit='s';
    }
    else if (_directionAsuivre=='s'){
        _directionInterdit='z';
    }
}

std::vector<char> Fantome::listeDirectionPossible(Mur ensembleMurs) const{
    std::vector<char> listeDirectionPossible;
    listeDirectionPossible.push_back('z');
    listeDirectionPossible.push_back('q');
    listeDirectionPossible.push_back('s');
    listeDirectionPossible.push_back('d');

    std::vector<char> directionRetenu;
    for (int i=0; i<listeDirectionPossible.size(); i++){
        if (listeDirectionPossible[i] != _directionInterdit){ //impossible de faire demi tour pour un fantome
            if (_fantome.autorisationChargerDirection(listeDirectionPossible[i], ensembleMurs)){
                //si on peut aller dans une direction, on mémorise cette direction
                directionRetenu.push_back(listeDirectionPossible[i]);
            }
        }
    }
    return directionRetenu;
}

char Fantome::choixDirrectionOptimal(sf::Vector2f posPacman) const{
    sf::Vector2f posFantome = _fantome.getBody().getRect().getPosition();
    int dist_X = posPacman.x - posFantome.x;
    int dist_Y = posPacman.y - posFantome.y;
    if (dist_X*dist_X > dist_Y*dist_Y){ //on prends le carré si jamais cette distance est négative
        if (dist_X > 0){
            return 'd';
        }
        else return 'q';
    }
    else{
        if (dist_Y >0){
            return 's';
        }
        else{
            return 'z';
        }
    }
}

void Fantome::deplacementF1(Mur ensembleMurs, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED, sf::Vector2f posPacman, float AGRANDISSEMENT, sf::Clock stopPourchasser){
    const sf::Vector2f POS_INI_FANTOME_1 = sf::Vector2f(TAILLE_ENTITE*2, TAILLE_ENTITE*3);
    if (_comestible /*&& stopPourchasser.getElapsedTime().asSeconds() < 5*/){
        deplacement(ensembleMurs, t, TAILLE_ENTITE, SPEED, POS_INI_FANTOME_1, AGRANDISSEMENT);
    }
    else    deplacement(ensembleMurs, t, TAILLE_ENTITE, SPEED, posPacman, AGRANDISSEMENT);
}

void Fantome::deplacementF2(Mur ensembleMurs, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED, sf::Vector2f posPacman, char directionAsuivre, float AGRANDISSEMENT, sf::Clock stopPourchasser){
    const sf::Vector2f POS_INI_FANTOME_2 = sf::Vector2f(TAILLE_ENTITE*27, TAILLE_ENTITE*3);
    if (_comestible /*&& stopPourchasser.getElapsedTime().asSeconds() < 5*/){
        deplacement(ensembleMurs, t, TAILLE_ENTITE, SPEED, POS_INI_FANTOME_2, AGRANDISSEMENT);
    }
    else{
        sf::Vector2f cibleF2 = posPacman;
        switch ( directionAsuivre )
        {
            case 'z':
                cibleF2.y -= 8*TAILLE_ENTITE;
                break;
            case 's':
                cibleF2.y += 8*TAILLE_ENTITE;
                break;
            case 'd':
                cibleF2.x += 8*TAILLE_ENTITE;
                break;
            case 'q':
                cibleF2.x -= 8*TAILLE_ENTITE;
                break;
        }

        deplacement(ensembleMurs, t, TAILLE_ENTITE, SPEED, posPacman, AGRANDISSEMENT);
    }
}

void Fantome::deplacementF3(Mur ensembleMurs, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED, sf::Vector2f posPacman, char directionAsuivre, float AGRANDISSEMENT, sf::Clock stopPourchasser){
    const sf::Vector2f POS_INI_FANTOME_3 = sf::Vector2f(TAILLE_ENTITE*2, TAILLE_ENTITE*29);
    if (_comestible /*&& stopPourchasser.getElapsedTime().asSeconds() < 5*/){
        deplacement(ensembleMurs, t, TAILLE_ENTITE, SPEED, POS_INI_FANTOME_3, AGRANDISSEMENT);
    }
    else{
        sf::Vector2f cibleF2 = posPacman;
        switch ( directionAsuivre )
        {
            case 'z':
                cibleF2.y -= 8*TAILLE_ENTITE;
                break;
            case 's':
                cibleF2.y += 8*TAILLE_ENTITE;
                break;
            case 'd':
                cibleF2.x += 8*TAILLE_ENTITE;
                break;
            case 'q':
                cibleF2.x -= 8*TAILLE_ENTITE;
                break;
        }
        sf::Vector2f cibleF3;
        cibleF3.x = sqrt(posPacman.x*posPacman.x + cibleF2.x*cibleF2.x);
        cibleF3.y = sqrt(posPacman.y*posPacman.y + cibleF2.y*cibleF2.y);

        //meme comportement que F1 sauf quand il est a moins de 8 cases
        sf::Vector2f posFantome = _fantome.getBody().getRect().getPosition();
        int dist_X = posPacman.x - posFantome.x;
        int dist_Y = posPacman.y - posFantome.y;
        int mini = std::max(abs(dist_Y), abs(dist_X));
            deplacement(ensembleMurs, t, TAILLE_ENTITE, SPEED, cibleF3, AGRANDISSEMENT);
    }
}

void Fantome::deplacementF4(Mur ensembleMurs, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED, sf::Vector2f posPacman, float AGRANDISSEMENT, sf::Clock stopPourchasser){
    //meme comportement que F1 sauf quand il est a moins de 4 cases
    const sf::Vector2f POS_INI_FANTOME_4 = sf::Vector2f(TAILLE_ENTITE*27, TAILLE_ENTITE*29);
    if (_comestible /*&& stopPourchasser.getElapsedTime().asSeconds() < 5*/){
        deplacement(ensembleMurs, t, TAILLE_ENTITE, SPEED, POS_INI_FANTOME_4, AGRANDISSEMENT);
    }
    else{
        sf::Vector2f posFantome = _fantome.getBody().getRect().getPosition();
        int dist_X = posPacman.x - posFantome.x;
        int dist_Y = posPacman.y - posFantome.y;
        int mini = std::max(abs(dist_Y), abs(dist_X));
        if (mini/TAILLE_ENTITE > 4){
            deplacement(ensembleMurs, t, TAILLE_ENTITE, SPEED, posPacman, AGRANDISSEMENT);
        }
        else{
            deplacement(ensembleMurs, t, TAILLE_ENTITE, SPEED, POS_INI_FANTOME_4, AGRANDISSEMENT);
        }
    }
}

Joueur Fantome::getFantome() const{
    return _fantome;
}



void Fantome::seFaitMange(sf::Vector2i POS_INI_FANT, float AGRANDISSEMENT, int TAILLE_ENTITE){
    sf::Vector2i POS_INI_FANTOME = POS_INI_FANT;
    POS_INI_FANTOME.x -= AGRANDISSEMENT*((1-_numeroFantome)*TAILLE_ENTITE);
    _fantome.setPosRectEntite(POS_INI_FANTOME);
    _spriteFantome1.setPosition(AGRANDISSEMENT*POS_INI_FANTOME.x, AGRANDISSEMENT*POS_INI_FANTOME.y);
    _fantome.updatePosition();
    _seDeplacer = false;
    _TpsReaparition.restart();
    _vienD_etre_mange = true;
}

void Fantome::placementApresManger(int TAILLE_ENTITE, sf::Clock clockJeu, float AGRANDISSEMENT, float tpsApparition){
    sf::Vector2i POS_INI_FANTOME = _positionIniF;
    POS_INI_FANTOME.y -= 2*TAILLE_ENTITE;
    if ( _vienD_etre_mange && _TpsReaparition.getElapsedTime().asSeconds() > 2 ){
        _spriteFantome1.setPosition(AGRANDISSEMENT*POS_INI_FANTOME.x, AGRANDISSEMENT*POS_INI_FANTOME.y);
        _fantome.setPosRectEntite(POS_INI_FANTOME);
        _fantome.updatePosition();
        _seDeplacer = true;
        _comestible = false;
        setCouleur(_saCouleur);
        _vienD_etre_mange = false;
    }
}

void Fantome::placementDebPartie(int TAILLE_ENTITE, sf::Clock clockJeu, float AGRANDISSEMENT){
    sf::Vector2i POS_INI_FANTOME = _positionIniF;
    POS_INI_FANTOME.y -= 2*TAILLE_ENTITE;
    bool estPosDepart =(_fantome.getBody().getRect().getPosition().x > 21*TAILLE_ENTITE && _fantome.getBody().getRect().getPosition().x < 28*TAILLE_ENTITE) && (_fantome.getBody().getRect().getPosition().y > 14*TAILLE_ENTITE && _fantome.getBody().getRect().getPosition().y < 17*TAILLE_ENTITE);
    if ( estPosDepart && (clockJeu.getElapsedTime().asSeconds() < (2.2+_numeroFantome) && clockJeu.getElapsedTime().asSeconds() > (2.1+_numeroFantome)) ){
        _spriteFantome1.setPosition(AGRANDISSEMENT*POS_INI_FANTOME.x, AGRANDISSEMENT*POS_INI_FANTOME.y);
        _fantome.setPosRectEntite(POS_INI_FANTOME);
        _fantome.updatePosition();
        _seDeplacer = true;
        _comestible = false;
        setCouleur(_saCouleur);
    }
}


bool Fantome::getEtatComestible() const{
    return _comestible;
}
void Fantome::setEtatComstible(bool etat){
    _comestible = etat;
}

bool Fantome::getEtatSeDeplacer() const{
    return _seDeplacer;
}
void Fantome::setEtatSeDeplacer(bool etat){
    _seDeplacer = etat;
}

void Fantome::setCouleur(sf::Color c){
    _fantome.setCouleur(c);
}



void Fantome::majDirectionInterditeGrosseBoule(){ //change direction
    char temp = _directionInterdit;
    _directionInterdit = _directionSouhaite;
    _directionSouhaite = temp;
    _directionPrecedente = temp;
}

void Fantome::placementZoneFantome(int TAILLE_ENTITE, float AGRANDISSEMENT){
    sf::Vector2i v = _positionIniF;
    v.x -= (1-_numeroFantome)*TAILLE_ENTITE;
    _spriteFantome1.setPosition(AGRANDISSEMENT*v.x, AGRANDISSEMENT*v.y);
    _fantome.setPosRectEntite(v);
}

