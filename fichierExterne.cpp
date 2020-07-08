#include "fichierExterne.hpp"


sf::Font chargementPolice(std::string emplacementPolice){
    sf::Font policeArial;
    if(! policeArial.loadFromFile(emplacementPolice)){
        std::cout << "Erreur chargement de la police d'ecriture" << std::endl;
    }
    return policeArial;
}

std::vector<std::vector<sf::Vector2i> > ouverture_creation_carte(std::string localisation){
    std::vector<sf::Vector2i> tempMap;
    std::vector<std::vector<sf::Vector2i> > map;
    /// parcours du fichier
    std::ifstream fichier(localisation.c_str(), std::ios::in); /// ouvrir le fichier en lecture
    if(!fichier.is_open())   /// si pb ouverture
    throw std::string ("l'ouverture du fichier a echoue : " + localisation);
    while(!fichier.eof()){ //tant qu'on est pas a la fin on lit
        std::string mot;
        fichier >> mot;
        char x = mot[0];
        char y = mot[2];
        if (!isdigit(x) || !isdigit(y)){ //vient de la bibliotheque cctype, verifie que c'est un nombre
            tempMap.push_back(sf::Vector2i(-1, -1));
        }
        else{
            tempMap.push_back(sf::Vector2i(x-'0',y-'0'));
        }
        if (fichier.peek() == '\n'){//si le caractere suivant est un retour a la ligne
            map.push_back(tempMap);
            tempMap.clear(); //on supprime les donnee du vecteur
        }
    }
    map.push_back(tempMap); //ajoute la derniere ligne
    fichier.close(); //fermer le fichier
    return map;
}

sf::Texture chargementTexture(std::string emplacementTexture){
    sf::Texture tileTexture;
    if(!tileTexture.loadFromFile(emplacementTexture)){
        std::cout << "Erreur chargement de la texture " + emplacementTexture << std::endl;
    }
    return tileTexture;
}


void choixTailleResolution(int tailleEcran, float& agrandissement){
    if (tailleEcran > 1080){
        agrandissement = 1;
    }
    else if (tailleEcran > 720){
        agrandissement = 0.5;
    }
    else if (tailleEcran > 480){
        agrandissement = 0.25;
    }
    else{
        agrandissement = 0.25;
    }
}
