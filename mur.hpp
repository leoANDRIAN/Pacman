#include "entite.hpp"
#include "fichierExterne.hpp"

#ifndef mur_hpp
#define mur_hpp

/**
* \const const float TAILLE_TUILE_MUR
* \brief Taile d'une tuile du mur dans le fichier tuile.png
*/
const float TAILLE_TUILE_MUR = 48;

/**
* \const const float REDUC_MUR
* \brief Ajuste la taille de la tuile en fonction de la taille des Entites
*/


/**
* \const const sf::Vector2i EMPLACEMENT_SPRITE_MUR
* \brief Emplacement du sprite du mur dans le fichier texte servant a creer la carte
*/
const sf::Vector2i EMPLACEMENT_SPRITE_MUR = sf::Vector2i(2,0);

/**
* \const const sf::Texture MUR_BRIQUE_TEXTURE
* \brief Texture du mur en brique de Pacman
*
* Est utilie lors de la creation des murs, et lors de l'affichage
*/
const sf::Texture MUR_BRIQUE_TEXTURE = chargementTexture(CHEMIN_REL + "tuile.png");

class Mur{
    /**
    * \const vector<Entite> _ensembleMurs
    * \brief L'ensemble des murs sera representer par un vecteur d'entite
    *
    * L'ensemble des murs sera creer a partir du tableau sfVector2i qui provient de la lecture du fichier texte.
    */
    std::vector<Entite> _ensembleMurs;
    
    /**
    * \const vector<sf::Vector2i> _positionFichierMurBrique
    * \brief Stocke pour chaque entite mur sa position a partir du fichier texte de depart.
    *
    * Sera utile pour gerer l'affichage des murs. On stocke toutes les positions des murs en brique. Si par la suite on veut utiliser plusieurs sprites pour les murs, on pourra.
    */
    std::vector<sf::Vector2i> _positionFichierMurBrique;
    
    /**
    * \const sf::Sprite _spriteMurBrique
    * \brief Sprite des murs
    */
    sf::Sprite _spriteMurBrique;
    
public:
    /**
    * \const Mur(vector<vector<sf::Vector2i>> map, int TAILLE_ENTITE, float REDUC_MUR)
    * \brief Constructeur permettant de creer l'ensemble des murs de la carte
    *
    * A partir du tableau de sf::Vector2i construit en parcourant le fichier texte qui modelise les element de la carte défini : la position de chaque mur, leur taille qui correspond a la valeur TAILLE_ENTITE
    */
    Mur(std::vector<std::vector<sf::Vector2i> > map, int TAILLE_ENTITE, float REDUC_MUR);
    
    /**
    * \const void definirInfoMur()
    * \brief Initialise les attributs de chaque mur.
    *
    * Utilise la fonction update sur chaque entite qui compose un mur. Cette fonction est appele pour creer les entite murs.
    */
    void definirInfoMur();
    
    /**
    * \const void afficherMurCarte(sf::Sprite& tiles, sf::RenderWindow& window, int TAILLE_ENTITE) const
    * \brief Affiche les murs a l'ecran
    *
    * A partir du sprite des mur, afiiche sur la fenetre les murs sans s'occuper de l'aspect physique.
    */
    void afficherMurCarte(sf::RenderWindow& window, int TAILLE_ENTITE);
    
    /**
    * \const Entite getEntiteMur(int i) const
    * \brief Retourne l'entite i du vecteur qui constitue l'ensemble des murs
    *
    * Sera utile pour gerer l'interaction entre pacman et les murs de la carte
    */
    Entite getEntiteMur(int i) const;
    
    /**
    * \const int getNombreMurs() const
    * \brief Retourne le nombres de murs sur la carte
    *
    * Sera utile pour gerer l'interaction entre pacman et les murs, notament les permissions d'avancer dans une direction donne.
    */
    int getNombreMurs() const;
    
    
};


#endif /* mur_hpp */
