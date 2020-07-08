#include "boule.hpp"


Boule::Boule(std::vector<std::vector<sf::Vector2i> > map, int TAILLE_ENTITE, float REDUC_BOULE){
    for (int i=0; i < map.size(); i++){
        for(int j=0; j < map[i].size(); j++){
            if (map[i][j].x == EMPLACEMENT_SPRITE_BOULE.x && map[i][j].y == EMPLACEMENT_SPRITE_BOULE.y){
                Entite e(sf::Vector2f(j * TAILLE_ENTITE, i * TAILLE_ENTITE), sf::Vector2f(TAILLE_ENTITE, TAILLE_ENTITE), TAILLE_ENTITE);
                _ensembleBoules.push_back(e);
                _positionFichier.push_back(sf::Vector2i(i,j));
                _etat.push_back(true);
                _superBoule.push_back(false);
            }
            else if (map[i][j].x == 8 && map[i][j].y == 8){
                Entite e(sf::Vector2f(j * TAILLE_ENTITE, i * TAILLE_ENTITE), sf::Vector2f(TAILLE_ENTITE, TAILLE_ENTITE), sf::Color::Blue);
                _ensembleBoules.push_back(e);
                _positionFichier.push_back(sf::Vector2i(i,j));
                _etat.push_back(true);
                _superBoule.push_back(true);
            }
        }
    }
    definirInfoBoules();
    _spriteBoule.setTexture(BOULE_TEXTURE);
    _spriteBoule.setScale(REDUC_BOULE, REDUC_BOULE);
    
    _spriteSuperBoule.setTexture(SUPER_BOULE_TEXTURE);
    _spriteSuperBoule.setScale(REDUC_BOULE, REDUC_BOULE);
    
    
}

void Boule::definirInfoBoules(){
    for (int i = 0; i<_ensembleBoules.size(); i++){
        _ensembleBoules[i].update();
    }
}

void Boule::afficherBouleCarte(sf::RenderWindow& window, float tpsEcoule, int TAILLE_ENTITE){
    for (int i=0; i<_positionFichier.size(); i++){
        if (_etat[i] && !_superBoule[i]){
            _spriteBoule.setPosition(_positionFichier[i].y*TAILLE_ENTITE+0.2*TAILLE_ENTITE, _positionFichier[i].x*TAILLE_ENTITE+0.2*TAILLE_ENTITE);
            //raison du 0.2 : placer la bille au centre
            //animation de la flamme
            if (tpsEcoule < 0.1) {
                _spriteBoule.setTextureRect(sf::IntRect(EMPLACEMENT_SPRITE_BOULE.x * TAILLE_BOULE, EMPLACEMENT_SPRITE_BOULE.y * TAILLE_BOULE, TAILLE_BOULE, TAILLE_BOULE));
            }
            else if (tpsEcoule < 0.2) {
                _spriteBoule.setTextureRect(sf::IntRect(EMPLACEMENT_SPRITE_BOULE.x*TAILLE_BOULE + TAILLE_BOULE, EMPLACEMENT_SPRITE_BOULE.y * TAILLE_BOULE, TAILLE_BOULE, TAILLE_BOULE));
            }
            else if (tpsEcoule < 0.3) {
                _spriteBoule.setTextureRect(sf::IntRect(EMPLACEMENT_SPRITE_BOULE.x * TAILLE_BOULE + 3*TAILLE_BOULE, EMPLACEMENT_SPRITE_BOULE.y * TAILLE_BOULE, TAILLE_BOULE, TAILLE_BOULE));
            }
            else{
                _spriteBoule.setTextureRect(sf::IntRect(EMPLACEMENT_SPRITE_BOULE.x * TAILLE_BOULE + 2*TAILLE_BOULE, EMPLACEMENT_SPRITE_BOULE.y * TAILLE_BOULE, TAILLE_BOULE, TAILLE_BOULE));
            }
            window.draw(_spriteBoule);
        }
        else if (_etat[i] && _superBoule[i]){
            _spriteSuperBoule.setPosition(_positionFichier[i].y*TAILLE_ENTITE+0.2*TAILLE_ENTITE, _positionFichier[i].x*TAILLE_ENTITE+0.2*TAILLE_ENTITE);
            _spriteSuperBoule.setTextureRect(sf::IntRect(0, 2*TAILLE_BOULE, TAILLE_BOULE, TAILLE_BOULE));
//            window.draw(_ensembleBoules[i].getRect());
            window.draw(_spriteSuperBoule);
            
        }
    }
}

//interaction avec Pacman

Entite Boule::getEntiteBoule(int i) const{
    if (i<0 || i>= _ensembleBoules.size()){
        throw i;
    }
    return _ensembleBoules[i];
}

int Boule::getNombreBoules() const{
    return _ensembleBoules.size();
}

void Boule::mangerBoule(int i){
    if (i<0 || i>=_ensembleBoules.size()){
        throw i;
    }
    _etat[i]=false;
    
}

bool Boule::pasDejaMange(int i) const{
    if (i<0 || i>=_ensembleBoules.size()){
        throw i;
    }
    return _etat[i];
}

void Boule::activerToutesLesBilles(){
    for (int i=0; i<_ensembleBoules.size(); i++ ){
        _etat[i]=true;
    }
}

int Boule::getNbBillesMangees(){
    int nbBillesMange = _ensembleBoules.size();
    for (int i=0; i<_ensembleBoules.size(); i++ ){
        if(_etat[i]==true) nbBillesMange--;
    }
    return nbBillesMange;
}

bool Boule::getEtatSuperBoule(int i) const{
    return _superBoule[i];
}
