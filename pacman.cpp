#include "pacman.hpp"

Pacman::Pacman(){
}

Pacman::Pacman(int TAILLE_ENTITE, sf::Vector2i POS_INI_PAC, int nbVie, float AGRANDISSEMENT){
    _pacman = Joueur(sf::Vector2f(POS_INI_PAC.x, POS_INI_PAC.y), sf::Color::Yellow, TAILLE_ENTITE);
    _spritePacman.setTexture(PAC_TEXTURE);
    _spritePacman.setPosition(AGRANDISSEMENT*(POS_INI_PAC.x), AGRANDISSEMENT*POS_INI_PAC.y);
    _portion = sf::IntRect(0, 0, TAILLE_SPRITE_PAC, TAILLE_SPRITE_PAC);
    _spritePacman.rotate(90);
    _spritePacman.move(TAILLE_ENTITE*AGRANDISSEMENT, 0);
    _nbVies = nbVie;
    _superPacman = false;
    _multiplicateurScore=100;
    _directionSouhaite = 'd' ;
    
    if (!_bufferMort.loadFromFile("death.ogg")){
        std::cout << "probleme chargement musique" << std::endl;
    }
    _soundMort.setBuffer(_bufferMort);
    
}

void Pacman::afficherPacman(sf::RenderWindow& window) const{
//    _pacman.afficherJoueur(window); //dessine le carre de couleur
    window.draw(_spritePacman); //dessine le sprite
}

Joueur Pacman::getPacman() const{
    return _pacman;
}

void Pacman::animation_deplacement_spritePacman(sf::Clock clock, bool autorisation, int TAILLE_ENTITE, char &derniereCase){
    if (!_superPacman){
    _portion.top = 0;
    //setCouleur(sf::Color::Yellow);
    if (clock.getElapsedTime().asSeconds() > 0.2){
        if (_portion.left == 1000)
        {
            derniereCase = 't';
        }
        if (_portion.left == 0)
        {
            derniereCase = 'f';
        }
        if (derniereCase == 'f')
        {
            _portion.left = _portion.left+200;
            _spritePacman.setTextureRect(_portion);
            _spritePacman.setScale(TAILLE_ENTITE/TAILLE_SPRITE_PAC, TAILLE_ENTITE/TAILLE_SPRITE_PAC);
        }
        else if (derniereCase == 't')
        {
            _portion.left = _portion.left-200;
            _spritePacman.setTextureRect(_portion);
            _spritePacman.setScale(TAILLE_ENTITE/TAILLE_SPRITE_PAC, TAILLE_ENTITE/TAILLE_SPRITE_PAC);
        }
        clock.restart();
    }
    }
    else{
        //setCouleur(sf::Color::Red);
        _portion.top = 200;
        if (clock.getElapsedTime().asSeconds() > 0.2){
        if (_portion.left != 1000)
        {
            _portion.left = _portion.left+200;
            _spritePacman.setTextureRect(_portion);
            _spritePacman.setScale(TAILLE_ENTITE/TAILLE_SPRITE_PAC, TAILLE_ENTITE/TAILLE_SPRITE_PAC);
        }
        else
        {
            _portion.left = 0;
            _spritePacman.setTextureRect(_portion);
            _spritePacman.setScale(TAILLE_ENTITE/TAILLE_SPRITE_PAC, TAILLE_ENTITE/TAILLE_SPRITE_PAC);
        }
        clock.restart();
    }
    }
    if (autorisation){
        if (_directionAsuivre=='q'){

        }


        if (_directionSouhaite=='d'){
            if (_directionAsuivre=='q'){
                //std::cout << "vien de gauche" << std::endl;
                _spritePacman.rotate(180);
                _spritePacman.move(TAILLE_ENTITE, -TAILLE_ENTITE);
            }
            else if (_directionAsuivre=='s'){
                //                std::cout << "vien de bas" << std::endl;
                _spritePacman.rotate(270);
                _spritePacman.move(0, -TAILLE_ENTITE);
            }
            else if (_directionAsuivre=='z'){
                //                std::cout << "vien de haut" << std::endl;
                _spritePacman.rotate(90);
                _spritePacman.move(TAILLE_ENTITE, 0);
            }
        }
        else if (_directionSouhaite=='q'){
            if (_directionAsuivre=='d'){
                //                std::cout << "vien de droite" << std::endl;
                _spritePacman.rotate(180);
                _spritePacman.move(-TAILLE_ENTITE, TAILLE_ENTITE);
            }
            else if (_directionAsuivre=='s'){
                //                std::cout << "vien de bas" << std::endl;
                _spritePacman.rotate(90);
                _spritePacman.move(-TAILLE_ENTITE,0);
            }
            else if (_directionAsuivre=='z'){
                //                std::cout << "vien de haut" << std::endl;
                _spritePacman.rotate(270);
                _spritePacman.move(0, TAILLE_ENTITE);
            }
        }
        else if (_directionSouhaite=='z'){
            if (_directionAsuivre=='d'){
                //                std::cout << "vien de droite" << std::endl;
                _spritePacman.rotate(270);
                _spritePacman.move(-TAILLE_ENTITE,0);
            }
            else if (_directionAsuivre=='q'){
                //                std::cout << "vien de gauche" << std::endl;
                _spritePacman.rotate(90);
                _spritePacman.move(0, -TAILLE_ENTITE);
            }
            else if (_directionAsuivre=='s'){
                //                std::cout << "vien de bas" << std::endl;
                _spritePacman.rotate(180);
                _spritePacman.move(-TAILLE_ENTITE, -TAILLE_ENTITE);
            }
        }
        else if (_directionSouhaite=='s'){
            if (_directionAsuivre=='d'){
                //                std::cout << "vien de droite" << std::endl;
                _spritePacman.rotate(90);
                _spritePacman.move(0, TAILLE_ENTITE);
            }
            else if (_directionAsuivre=='q'){
                //                std::cout << "vien de gauche" << std::endl;
                _spritePacman.rotate(270);
                _spritePacman.move(TAILLE_ENTITE, 0);
            }
            else if (_directionAsuivre=='z'){
                //                std::cout << "vien de haut" << std::endl;
                _spritePacman.rotate(180);
                _spritePacman.move(TAILLE_ENTITE, TAILLE_ENTITE);
            }
        }

    }
}

void Pacman::deplacementPacman(Mur ensembleMurs, sf::Clock clock, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED, char &derniereCase, float AGRANDISSEMENT){


    //prend en compte l'appui sur une touche
    _pacman.directionSouhaite(_directionSouhaite);
    //anime le sprite de Pacman, en fonction de la touche appuye, verifie si on peut se tourner
    animation_deplacement_spritePacman(clock, _pacman.autorisationChargerDirection(_directionSouhaite, ensembleMurs) && _directionAsuivre!=_directionSouhaite, TAILLE_ENTITE, derniereCase);
    //directionAsuivre prend la valeur DirectionSouhaite si il n'y a pas un mur dans cette direction



    _pacman.choixDirection(_directionAsuivre, _directionSouhaite, _pacman.autorisationChargerDirection(_directionSouhaite, ensembleMurs));
    //deplace pacman tant qu'il ne rencontre pas de mur
    _pacman.deplacementAutoJoueur(_directionAsuivre, ensembleMurs, _spritePacman, SPEED, AGRANDISSEMENT);
    //interaction avec les tunnels
    _pacman.interactionTunnelHorizontaux(t, _spritePacman, TAILLE_ENTITE);

}

bool Pacman::interactionBille(Boule& b, sf::Clock& changementEtat, Fantome& f1, Fantome& f2, Fantome& f3, Fantome& f4){
    bool stop = false;
    int cpt = 0;
    while (cpt<b.getNombreBoules() && !stop){
        if ( _pacman.getBody().colision(b.getEntiteBoule(cpt)) && b.pasDejaMange(cpt) ){
            stop = true;
            if (b.getEtatSuperBoule(cpt)){
                changementEtat.restart();
                f1.majDirectionInterditeGrosseBoule();
                f2.majDirectionInterditeGrosseBoule();
                f3.majDirectionInterditeGrosseBoule();
                f4.majDirectionInterditeGrosseBoule();
            }
            b.mangerBoule(cpt);
        }
        cpt++;
    }
    return stop;
}

int Pacman::getNbVies() const{
    return _nbVies;
}

bool Pacman::rencontreFantome(Fantome f){
    bool rencontrer = false;
    if (_pacman.getBody().colision(f.getFantome().getBody())){
        rencontrer = true;
    }
    return rencontrer;
}

void Pacman::interactionFantomes(Fantome& f1, Fantome& f2, Fantome& f3, Fantome& f4, int& point, int TAILLE_ENTITE, bool& nouvelleVie, sf::Clock& clockJeu, sf::Vector2i POS_INI_PAC, sf::Vector2i POS_INI_FANTOME, sf::Clock& placementF, int speedP, float AGRANDISSEMENT){
    f1.placementApresManger(TAILLE_ENTITE, clockJeu, AGRANDISSEMENT, 2.5);
    f2.placementApresManger(TAILLE_ENTITE, clockJeu, AGRANDISSEMENT, 3.5);
    f3.placementApresManger(TAILLE_ENTITE, clockJeu, AGRANDISSEMENT, 4.5);
    f4.placementApresManger(TAILLE_ENTITE, clockJeu, AGRANDISSEMENT, 5.5);
    if (_superPacman && rencontreFantome(f1) && f1.getEtatComestible()){
        f1.seFaitMange(POS_INI_FANTOME,AGRANDISSEMENT, TAILLE_ENTITE);
        point += _multiplicateurScore;
        _multiplicateurScore *= 2;
    }
    else if (_superPacman && rencontreFantome(f2) && f2.getEtatComestible()){
        f2.seFaitMange(POS_INI_FANTOME,AGRANDISSEMENT, TAILLE_ENTITE);
        point += _multiplicateurScore;
        _multiplicateurScore *= 2;
    }
    else if (_superPacman && rencontreFantome(f3) && f3.getEtatComestible()){
        f3.seFaitMange(POS_INI_FANTOME,AGRANDISSEMENT, TAILLE_ENTITE);
        point += _multiplicateurScore;
        _multiplicateurScore *= 2;
    }
    else if (_superPacman && rencontreFantome(f4) && f4.getEtatComestible()){
        f4.seFaitMange(POS_INI_FANTOME,AGRANDISSEMENT, TAILLE_ENTITE);
        point += _multiplicateurScore;
        _multiplicateurScore *= 2;
    }

    else if (rencontreFantome(f1) || rencontreFantome(f2) || rencontreFantome(f3) || rencontreFantome(f4)){
        nouvelleVie = false;
        clockJeu.restart();
        setPosition(POS_INI_PAC, AGRANDISSEMENT);
        AjusterEmplacement(TAILLE_ENTITE*AGRANDISSEMENT);
        f1.placementZoneFantome(TAILLE_ENTITE, AGRANDISSEMENT);
        f2.placementZoneFantome(TAILLE_ENTITE, AGRANDISSEMENT);
        f3.placementZoneFantome(TAILLE_ENTITE, AGRANDISSEMENT);
        f4.placementZoneFantome(TAILLE_ENTITE, AGRANDISSEMENT);
        _nbVies--;
        _soundMort.play();
    }

}


void Pacman::setPosition(sf::Vector2i POS_INI_PAC, float AGRANDISSEMENT){
    _spritePacman.setPosition(AGRANDISSEMENT*POS_INI_PAC.x , AGRANDISSEMENT*POS_INI_PAC.y );
    _pacman.setPosRectEntite(POS_INI_PAC);
    _pacman.updatePosition();
}

sf::Sprite Pacman::getSprite(){
    return _spritePacman;
}

void Pacman::setPosSprite(sf::Vector2f v){
    _spritePacman.setPosition(v.x, v.y);
}

void Pacman::AjusterEmplacement(int tailleEntite){
    if (_spritePacman.getRotation() == 0){
    }
    if (_spritePacman.getRotation() == 90){
        _spritePacman.move(tailleEntite, 0);
    }
    if (_spritePacman.getRotation() == 270){
        _spritePacman.move(0, tailleEntite);
    }
    if (_spritePacman.getRotation() == 180){
        _spritePacman.move(tailleEntite, tailleEntite);
    }
}

void Pacman::setNbVie(int nbVie){
    _nbVies = nbVie;
}


bool Pacman::getSuperPacman() const{
    return _superPacman;
}
void Pacman::setSuperPacman(bool etat){
    _superPacman = etat;
}

void Pacman::setCouleur(sf::Color c){
    _pacman.setCouleur(c);
}

void Pacman::changementComportementPF(Fantome& f1, Fantome& f2, Fantome& f3, Fantome& f4, sf::Clock& changementEtat, sf::Clock& clockJeu){

    if (clockJeu.getElapsedTime() > changementEtat.getElapsedTime()){

        if (changementEtat.getElapsedTime().asSeconds() < 4.5){
            if (changementEtat.getElapsedTime().asSeconds() < 0.5){
                f1.setEtatComstible(true);
                f2.setEtatComstible(true);
                f3.setEtatComstible(true);
                f4.setEtatComstible(true);
            }
            _superPacman=true;
        }
        else{
            _multiplicateurScore = 100;
            _superPacman=false;
            f1.setEtatComstible(false);
            f2.setEtatComstible(false);
            f3.setEtatComstible(false);
            f4.setEtatComstible(false);
        }
    }
}

char Pacman::getDirectionAsuivre(){
    return _directionAsuivre;
}
