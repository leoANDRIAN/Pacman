#include "mur.hpp"


Mur::Mur(std::vector<std::vector<sf::Vector2i> > map, int TAILLE_ENTITE, float REDUC_MUR){
        for (int i=0; i < map.size(); i++){
            for(int j=0; j < map[i].size(); j++){
                if (map[i][j].x == EMPLACEMENT_SPRITE_MUR.x && map[i][j].y == EMPLACEMENT_SPRITE_MUR.y){
                    Entite e(sf::Vector2f(j * TAILLE_ENTITE, i * TAILLE_ENTITE), sf::Vector2f(TAILLE_ENTITE, TAILLE_ENTITE), TAILLE_ENTITE);
                    _ensembleMurs.push_back(e);
                    _positionFichierMurBrique.push_back(sf::Vector2i(i,j));
                }
                else if (map[i][j].x == 3 && map[i][j].y == EMPLACEMENT_SPRITE_MUR.y){ //mur invisible, spawn fantome
                    Entite e(sf::Vector2f(j * TAILLE_ENTITE, i * TAILLE_ENTITE), sf::Vector2f(TAILLE_ENTITE, TAILLE_ENTITE), TAILLE_ENTITE);
                    _ensembleMurs.push_back(e);
                }
            }
        }
    definirInfoMur();
    _spriteMurBrique.setTexture(MUR_BRIQUE_TEXTURE);
    _spriteMurBrique.setTextureRect(sf::IntRect(EMPLACEMENT_SPRITE_MUR.x * TAILLE_TUILE_MUR, EMPLACEMENT_SPRITE_MUR.y * TAILLE_TUILE_MUR, TAILLE_TUILE_MUR, TAILLE_TUILE_MUR));
    _spriteMurBrique.setScale(REDUC_MUR, REDUC_MUR);
}


void Mur::definirInfoMur(){
    for (int i=0; i<_ensembleMurs.size(); i++){
        _ensembleMurs[i].update();
    }
}

void Mur::afficherMurCarte(sf::RenderWindow& window, int TAILLE_ENTITE){
    for (int i=0; i< _positionFichierMurBrique.size(); i++){
        _spriteMurBrique.setPosition( _positionFichierMurBrique[i].y * TAILLE_ENTITE, _positionFichierMurBrique[i].x * TAILLE_ENTITE);
        window.draw(_spriteMurBrique);
    }
}

Entite Mur::getEntiteMur(int i) const{
    if (i<0 || i>= _ensembleMurs.size()){
        throw i;
    }
    return _ensembleMurs[i];
}

int Mur::getNombreMurs() const{
    return _ensembleMurs.size();
}




