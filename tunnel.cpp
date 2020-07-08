#include "tunnel.hpp"


TunnelHorizontal::TunnelHorizontal(std::vector<std::vector<sf::Vector2i> > map){
    //recherche de la premiere colonne avec autre chose que x,x dans le fichier texte
    //on commence la carte sur la premiere ligne du fichier texte
    int debCarte = 0; //represente le debut de la carte, en position y
    bool nonTrouve = map[0][0].x == -1;
    while (nonTrouve){
        debCarte++;
        nonTrouve = map[0][debCarte].x == -1;
    }
    
    //on parcourt la carte pour rechercher les tunnels, qui sont place sur la gauche de la carte
    for (int i=0; i<map.size(); i++){
        if (map[i][debCarte].x == 9 && map[i][debCarte].y == 9){ //9,9 est la valeur attribue au tunnel horizontaux
            _positionsY.push_back(i);
        }
    }
    _largeurCarte = map[0].size() - debCarte;
    _debutCarte = debCarte;
}


std::vector<int> TunnelHorizontal::getPostionsY() const{
    return _positionsY;
}

int TunnelHorizontal::getLargeurCarte() const{
    return _largeurCarte;
}

int TunnelHorizontal::getDebCarte() const{
    return _debutCarte;
}
