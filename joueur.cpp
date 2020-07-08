#include "joueur.hpp"


Joueur::Joueur(){
}

Joueur::Joueur(sf::Vector2f position, sf::Color couleur, int TAILLE_ENTITE){
    _body = Entite(sf::Vector2f(position.x, position.y), sf::Vector2f(TAILLE_ENTITE,TAILLE_ENTITE), couleur);
}

void Joueur::updatePosition(){
    _body.update();
}

void Joueur::afficherJoueur(sf::RenderWindow& window) const{
    window.draw(_body.getRect());
}

bool Joueur::nonColisionMurDroit(Mur m) const{
    bool retour = !_body.colisionDroite(m.getEntiteMur(0));
    int i = 0;
    while (retour && i<m.getNombreMurs() ){
        retour = retour && !_body.colisionDroite(m.getEntiteMur(i));
        i ++;
    }
    return retour;
}

bool Joueur::nonColisionMurGauche(Mur m) const{
    bool retour = !_body.colisionGauche(m.getEntiteMur(0));
    int i = 0;
    while (retour && i<m.getNombreMurs()){
        retour = retour && !_body.colisionGauche(m.getEntiteMur(i));
        i++;
    }
    return retour;
}

bool Joueur::nonColisionMurHaut(Mur m) const{
    bool retour = !_body.colisionHaut(m.getEntiteMur(0));
    int i = 0;
    while (retour && i<m.getNombreMurs()){
        retour = retour && !_body.colisionHaut(m.getEntiteMur(i));
        i++;
    }
    return retour;
}

bool Joueur::nonColisionMurBas(Mur m) const{
    bool retour = !_body.colisionBas(m.getEntiteMur(0));
    int i = 0;
    while (retour && i<m.getNombreMurs()){
        retour = retour && !_body.colisionBas(m.getEntiteMur(i));
        i++;
    }
    return retour;
}


void Joueur::directionSouhaite(char& directionSouhaite) const{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ){
        directionSouhaite = 'd';
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ){
        directionSouhaite = 'q';
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ){
        directionSouhaite = 'z';
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ){
        directionSouhaite = 's';
    }
}

bool Joueur::autorisationChargerDirection(char directionSouhaite, Mur ensembleMurs) const{
    if (directionSouhaite == 'd') {
        return nonColisionMurDroit(ensembleMurs);
    }
    else if (directionSouhaite == 'q') {
        return nonColisionMurGauche(ensembleMurs);
    }
    else if (directionSouhaite == 'z') {
        return nonColisionMurHaut(ensembleMurs);
    }
    else {
        return nonColisionMurBas(ensembleMurs);
    }
}

void Joueur::choixDirection(char& directionAsuivre, char directionSouhaite, bool autorisationChangerDirection){
    if (autorisationChangerDirection) {
        directionAsuivre = directionSouhaite;
    }
}

void Joueur::deplacementAutoJoueur(char directionAsuivre, Mur ensembleMurs, sf::Sprite& sprite, int SPEED, float AGRANDISSEMENT){
    if(directionAsuivre=='d' && nonColisionMurDroit(ensembleMurs) ){
        _body.moveEntite(SPEED, 0);
        sprite.move(AGRANDISSEMENT*SPEED,0);
    }
    else if(directionAsuivre=='q' && nonColisionMurGauche(ensembleMurs)){
        _body.moveEntite(-SPEED, 0);
//        spritePacman.rotate(180);
        sprite.move(-AGRANDISSEMENT*SPEED, 0);
    }
    else if(directionAsuivre=='z' && nonColisionMurHaut(ensembleMurs)){
        _body.moveEntite(0, -SPEED);
//        spritePacman.rotate(270);
        sprite.move(0, -AGRANDISSEMENT*SPEED);
    }
    else if(directionAsuivre=='s' && nonColisionMurBas(ensembleMurs)){
        _body.moveEntite(0, SPEED);
        sprite.move(0, AGRANDISSEMENT*SPEED);
    }
    updatePosition();
}


Entite Joueur::getBody() const{
    return _body;
}


void Joueur::interactionTunnelHorizontaux(const TunnelHorizontal& t, sf::Sprite& sprite, int TAILLE_ENTITE){
    std::vector<int> positionYtunnel = t.getPostionsY();
    int largeurCarte = t.getLargeurCarte();
    int debCarte = t.getDebCarte();
    
    //on regarde si le joueur possede la meme ordonne qu'un des tunnels
    bool posY = positionYtunnel[0]*TAILLE_ENTITE == _body.getRect().getPosition().y;
    for (int i=0; i<positionYtunnel.size(); i++){
        posY = posY || positionYtunnel[i]*TAILLE_ENTITE == _body.getRect().getPosition().y;
    }
    //on regarde si un joueur a la meme abscide que l'un des tunnels
    bool posXok = _body.getRect().getPosition().x == debCarte*TAILLE_ENTITE;
    
    //si un joueur passe dans le tunnel, il est deplacer de l'autre cote de la carte
    if (posXok && posY){
        _body.moveEntite((largeurCarte-1)*TAILLE_ENTITE, 0);
        sprite.move((largeurCarte-1)*TAILLE_ENTITE, 0);
    }
    else if(_body.getRect().getPosition().x == (debCarte-1)*TAILLE_ENTITE + largeurCarte*TAILLE_ENTITE && posY){
        _body.moveEntite(-(largeurCarte-1)*TAILLE_ENTITE, 0);
        sprite.move(-(largeurCarte-1)*TAILLE_ENTITE, 0);
    }
}

void Joueur::setPosRectEntite(sf::Vector2i v){
    _body.setRect(v);
}

void Joueur::setCouleur(sf::Color c){
    _body.setCouleur(c);
}

void Joueur::deplacementJoueur(int x, int y, sf::Sprite& sprite, int SPEED, int AGRANDISSEMENT){
    _body.moveEntite(x, y);
    sprite.move(AGRANDISSEMENT*x, AGRANDISSEMENT*y);
}
