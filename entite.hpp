#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cctype>
#include <vector>
//using namespace std;



#ifndef entite_hpp
#define entite_hpp



/**
* \const const float TAILLE_ENTITE
* \brief Taille de chaque entite, c'est a dire des murs, de pacman, des fantomes, des boules
*
* Defini la taille carre de chaque entite. C'est la variable a modifier pour faire varier la taille du niveau. Chaque element du jeu sera une entite
* car il possedera une hitbox caractérié par le haut, le bas, la gauche et la droite du carre entite.

const float TAILLE_ENTITE = 48;
*/

class Entite{
    /**
    * \const sf::RectangleShape _rect
    * \brief Forme carre pour chaque entite
    */
    sf::RectangleShape _rect;
    
    /**
    * \const int _bottom
    * \brief bottom est la localisation du bas de l'entite
    */
    int _bottom;
    
    /**
    * \const int _top
    * \brief bottom est la localisation du haut de l'entite
    */
    int _top;
    
    /**
    * \const int _right
    * \brief bottom est la localisation de la droite de l'entite
    */
    int _right;
    
    /**
    * \const int _left
    * \brief bottom est la localisation de la gauche de l'entite
    */
    int _left;
    
    
public:
    /**
    * \const Entite()
    * \brief Contructeur par defaut de la classe entite
    *
    *    Constructeur inutilise dans la suite du code
    */
    Entite(){};
    
    /**
    * \const Entite(sf::Vector2f position, sf::Vector2f size, int TAILLE_ENTITE)
    * \brief Contructeur prenant en parametre une position, une taille
    *
    *    Constructeur inutilise pour creer les murs, les boules car ce qui sera afficher a l'ecran est un sprite prit a partir de fichier externe. Il sera utiliser pour creer pacman par la suite lorsque nous auront un sprite
    */
    Entite(sf::Vector2f position, sf::Vector2f size, int TAILLE_ENTITE);
    
    /**
    * \const Entite(sf::Vector2f position, sf::Vector2f size, sf::Color color)
    * \brief Contructeur prenant en parametre une position, une taille, une couleur
    *
    *    Constructeur inutilise pour creer pacman, en lui donnant une couleur bleu, en attendant d'utiliser un sprite
    */
    Entite(sf::Vector2f position, sf::Vector2f size, sf::Color color);
    
       
    /**
    * \const void update()
    * \brief Permet d'attribuer une valeur aux attribut de l'entite : la position du bord haut, bas, gauche et droite
    *
    *   Sera utile pour initialiser les attributs des boules et des murs au debut du programme. Sera tres utile pour actualiser la position de pacman et gerer sa colision avec les autres entite, et ainsi interagir avec elle en fonction de leur classe.
    */
    void update();
    
    /**
    * \const bool colision(Entite e) const
    * \brief Detecte la colision entre deux entites
    *
    *   Detecte la colision entre  l'entite cible et le milieu de l'entite passe en parametre. Sera utile pour la colision entre pacman et les boules de la carte
    */
    bool colision(Entite e) const;
    
    /**
    * \const bool colisionDroite(Entite e) const
    * \brief Detecte la colision de la partie droite de l'entite cible
    *
    *   Detecte la colision de la partie droite de l'entite cible avec la partie gauche de l'entite passe en parametre. Sera utile pour la colision entre pacman et les murs de la carte
    */
    bool colisionDroite(Entite e) const;
    
    /**
    * \const bool colisionGauche(Entite e) const
    * \brief Detecte la colision de la partie droite de l'entite cible
    *
    *   Detecte la colision de la partie gauche de l'entite cible avec la partie droite de l'entite passe en parametre. Sera utile pour la colision entre pacman et les murs de la carte
    */
    bool colisionGauche(Entite e) const;
    
    /**
    * \const bool colisionHaut(Entite e) const
    * \brief Detecte la colision du haut de l'entite cible
    *
    *   Detecte la colision du haut de l'entite cible avec le bas de l'entite passe en parametre. Sera utile pour la colision entre pacman et les murs de la carte
    */
    bool colisionHaut(Entite e) const;
    
    /**
    * \const bool colisionHaut(Entite e) const
    * \brief Detecte la colision du bas de l'entite cible
    *
    *   Detecte la colision du bas de l'entite cible avec le haut de l'entite passe en parametre. Sera utile pour la colision entre pacman et les murs de la carte
    */
    bool colisionBas(Entite e) const;
    
    /**
    * \const sf::RectangleShape getRect() const
    * \brief Retourne le rectangle d'une entite
    *
    *   Utile pour afficher le carre bleu reprensentant pacman, tant qu'on a pas de sprite qui lui correspond
    */
    sf::RectangleShape getRect() const;
    
    /**
    * \const void moveEntite(int x, int y)
    * \brief Deplacer le rectangle de l'entite
    *
    *   Utile pour deplacer Pacman
    */
    void moveEntite(int x, int y);
    
    
    
    /**
    * \void setRect(sf::Vector2i position)
    * \brief Deplacer le rectangle de l'entite physique
    *
    *   Utile pour deplacer Pacman
    */
    void setRect(sf::Vector2i position);
    
    
    /**
    * \void setCouleur(sf::Color c)
    * \brief Defini la couleur de l'entite
    *
    *   Utile pour pour visualiser pacman sans sprite
    */
    void setCouleur(sf::Color c);
};

#endif /* entite_hpp */
