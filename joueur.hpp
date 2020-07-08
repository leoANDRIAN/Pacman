#include "entite.hpp"
#include "mur.hpp"
#include "boule.hpp"
#include "tunnel.hpp"

#ifndef joueur_hpp
#define joueur_hpp

/**
* \const const int SPEED
* \brief Vitesse de déplacement de Pacman
*
* La vitesse de deplacement de Pacman est proportionnel a celle de l'entite. Il faut que la vitesse soit une multiple de la taille des entite, sinon ca pose probleme.
*/


class Joueur{
    /**
    * \const Entite _body
    * \brief Corps d'un joueur, qui peut etre pacman ou les fantomes. Le corps sera cubique, reprenseter par une entite. On va definir les colisions avec les murs.
    *
    */
    Entite _body;
    
public:
    
    /**
    * \const Joueur()
    * \brief Constructeur d'un joueur.
    *
    * 
    */
    Joueur();
    
    
    /**
    * \const Joueur(sf::Vector2f position, sf::Color couleur, int TAILLE_ENTITE)
    * \brief Constructeur d'un joueur en definissant sa position et sa couleur
    *
    * Pacman ou les fantomes auront une taille correspondant a celle de toutes les entite. On choisi avec ce constructeur leur position de départ et leur couleur. La couleur peut etre utile lorsque l'on travaille sans sprite.
    */
    Joueur(sf::Vector2f position, sf::Color couleur, int TAILLE_ENTITE);
    
    /**
    * \const void updatePosition()
    * \brief Met a jouer la position du joueur
    *
    * Actualise les attributs bottom, top, right et left du joueur pour gerer la colision avec les autres elements.
    */
    void updatePosition();
    
    /**
    * \const void afficherPacman(sf::RenderWindow& window) const
    * \brief Affiche le carre de couleur representant Pacman ou un fantome a l'ecran
    *
    * Affiche le carre correspondant a la couleur du joueur
    */
    void afficherJoueur(sf::RenderWindow& window) const;
    
    /**
    * \const bool nonColisionMurDroit(Mur m) const
    * \brief Test si un joueur rentre en colision avec un mur sur la droite
    *
    * Utilise la fontion colisionDroite de la classe Entite pour verifier si un joueur est en contact avec la partie gauche d'un mur. Pour cela on parcourt toutes les entites qui compose le mur, on s'arrete lorsque l'on trouve un mur en contact. Renvoie un booleen qui sera utile pour gerer le deplacement de Pacman.
    */
    bool nonColisionMurDroit(Mur m) const;
    
    /**
    * \const bool nonColisionMurGauche(Mur m) const
    * \brief Test si un joueur rentre en colision avec un mur sur la gauche
    *
    * Utilise la fontion colisionGauche de la classe Entite pour verifier si un joueur est en contact avec la partie droite d'un mur. Pour cela on parcourt toutes les entites qui compose le mur, on s'arrete lorsque l'on trouve un mur en contact. Renvoie un booleen qui sera utile pour gerer le deplacement de Pacman.
    */
    bool nonColisionMurGauche(Mur m) const;
    
    /**
    * \const bool nonColisionMurHaut(Mur m) const
    * \brief Test si un joueur rentre en colision avec un mur sur la gauche
    *
    * Utilise la fontion colisionHaut de la classe Entite pour verifier si un joueur est en contact avec le bas d'un mur. Pour cela on parcourt toutes les entites qui compose le mur, on s'arrete lorsque l'on trouve un mur en contact. Renvoie un booleen qui sera utile pour gerer le deplacement de Pacman.
    */
    bool nonColisionMurHaut(Mur m) const;
    
    /**
    * \const bool nonColisionMurBas(Mur m) const
    * \brief Test si un joueur rentre en colision avec un mur sur la gauche
    *
    * Utilise la fontion colisionHaut de la classe Entite pour verifier si un joueur est en contact avec le haut d'un mur. Pour cela on parcourt toutes les entites qui compose le mur, on s'arrete lorsque l'on trouve un mur en contact. Renvoie un booleen qui sera utile pour gerer le deplacement de Pacman.
    */
    bool nonColisionMurBas(Mur m) const;
    
    
    /**
    * \const void directionSouhaite(char& direction) const
    * \brief Memorise la direction choisi en appuyant sur les fleches directionnelles
    *
    * Change la valeur de la varible direction passe en parametre. Elle prend respectivement la valeur z, s, q, d si on appuie sur la fleche haut, bas, gauche, droite.
    */
    void directionSouhaite(char& directionSouhaite) const;
    
    /**
    * \const bool autorisationChargerDirection(char directionSouhaite, Mur ensembleMurs) const
    * \brief Verifie si un joueur peut changer de direction
    *
    * Parcourt l'ensensemble des murs, et verifie si la directionSouhaite est realisable, retourne true si c'est le cas.
    */
    bool autorisationChargerDirection(char directionSouhaite, Mur ensembleMurs) const;
    
    /**
    * \const void choixDirection(char& directionAsuivre, char directionSouhaite, bool autorisationChangerDirection)
    * \brief Change la directionAsuivre du joueur ou non en fonction de l'autorisation de changer de direction
    *
    * Utilise les deux fonction precedente. On choisi une direction, on regarde si on peut aller dans cette direction, tant qu'on ne peut pas on continu d'avancer dans la direction dans laquelle on est engage. Des qu'on peut avancer vers la direction souhaite on le fait.
    */
    void choixDirection(char& directionAsuivre, char directionSouhaite, bool autorisationChangerDirection);
    
    /**
    * \const void deplacementAutoPacman(char directionAsuivre, Mur ensembleMurs, int SPEED)
    * \brief Deplace automatiquement le joueur en verifiant qu'il a bien le droit d'avancer
    *
    * Fait avancer le joueur a une vitesse constance SPEED choisi en haut du .hpp, verifie l'ensemble des entite mur pour voir si il peut avancer.
    */
    void deplacementAutoJoueur(char directionAsuivre, Mur ensembleMurs, sf::Sprite& sprite, int SPEED, float AGRANDISSEMENT);
    
    
    /**
    * \const void getBody() const
    * \brief Retourne l'entite du joueur
    *
    * Utile pour gerer l'interaction entre Pacman et les billes.
    */
    Entite getBody() const;
    
    /**
    * \const void interactionTunnelHorizontaux(const TunnelHorizontal& t, sf::Sprite& sprite, int TAILLE_ENTITE)
    * \brief Deplace le joueur a l'oppose de la carte si il traverse un tunnel
    *
    * A partir de l'ensemble des tunnels horizontaux, modifier la position de l'entité bordy. Prend egalment en parametre un sprite et le deplace.
    */
    void interactionTunnelHorizontaux(const TunnelHorizontal& t, sf::Sprite& sprite, int TAILLE_ENTITE);
    
    /**
    * \const  void setPosRectEntite(sf::Vector2i v)
    * \brief Defini la position physique de Pacman
    *
    * A partir d'un vecteur défini la nouvelle position physique ainsi que le sprite de pacman'
    */
    void setPosRectEntite(sf::Vector2i v);
    
    /**
    * \const void setCouleur(sf::Color c)
    * \brief Defini la couleur de l'entite de Pacman
    *
    * Defini le couleur de l'entite de Pacman
    */
    void setCouleur(sf::Color c);
    
    /**
    * \const void deplacementJoueur(int x, int y, sf::Sprite& sprite, int SPEED, int AGRANDISSEMENT)
    * \brief Deplace le sprite d'un joueur, ne correspond pas a l'entite physique
    *
    * Utile pour ajuster l'affichage deu jeu. La position des sprite ne correspond pas a leur entite physique.
    */
    void deplacementJoueur(int x, int y, sf::Sprite& sprite, int SPEED, int AGRANDISSEMENT);
};


#endif /* joueur_hpp */
