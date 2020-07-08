#include "entite.hpp"

#ifndef fichierExterne_hpp
#define fichierExterne_hpp


/**
* \const const std::string CHEMIN_REL
* \brief Chemin relatif au repertoire de travail
*/
const std::string CHEMIN_REL = "./";
///ex: /Users/nicolas/Documents/AS/CodeBlock/ProjetTutore/IA_fantomes/IA_fantomes/
/**
* \const sf::Font chargementPolice(string emplacementPolice)
* \brief Charge la police a partir d'un .ttf
*/
sf::Font chargementPolice(std::string emplacementPolice);

/**
* \const sf::Texture chargementTextureMur(std::string emplacementTexture)
* \brief Charge une texture a partir d'un fichier jpg
*/
sf::Texture chargementTexture(std::string emplacementTexture);

/**
* \const std::vector<std::vector<sf::Vector2i> > ouverture_creation_carte(std::string localisation)
* \brief Generer la carte. Prends en compte 
*/
std::vector<std::vector<sf::Vector2i> > ouverture_creation_carte(std::string localisation);

/**
* \const void choixTailleResolution(int tailleEcran, float& TAILLE_ENTITEE)
* \brief Change la valeur agrandissement, ce qui permet d'adapter la resolution
*/
void choixTailleResolution(int tailleEcran, float& TAILLE_ENTITEE);
#endif /* fichierExterne_hpp */

