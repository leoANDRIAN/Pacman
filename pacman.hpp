#include "joueur.hpp"
#include "fichierExterne.hpp"
#include "fantome1.hpp"

#ifndef pacman_hpp
#define pacman_hpp


/**
* \const const float TAILLE_SPRITE_PAC
* \brief Taille du sprite de Pacman, utile dans la fonction afficher Pacman
*/
const float TAILLE_SPRITE_PAC = 200;

/**
* \const const sf::Vector2i POS_INI_PAC
* \brief Position initiale de Pacman sur la carte.
*
* Est utilie lors de la creation de Pacman.
*/


/**
* \const const sf::Texture PAC_TEXTURE
* \brief Texture de Pacman
*
* Est utilie lors de la creation de Pacman.
*/
const sf::Texture PAC_TEXTURE = chargementTexture(CHEMIN_REL + "SpriteSheetPacman.png");

class Pacman{
    /**
    * \const Joueur _pacman
    * \brief Pacman est un joueur, il peut donc utiliser les fonctions de la classe Joueur pour gerer son déplacement
    */
    Joueur _pacman;
    
    
    /**
    * \const sf::Sprite _spritePacman
    * \brief Sprite de Pacman.
    */
    sf::Sprite _spritePacman;
    
    /**
    * \const sf::IntRect _portion;
    * \brief portion de la texture.
    */
    sf::IntRect _portion;
    
    /**
    * \const int _nbVies
    * \brief Nombre de vies de Pacman
    */
    int _nbVies;
    
    /**
    * \const bool _superPacman
    * \brief Si est vrai pacman peut manger les fantomes
    */
    bool _superPacman;
    
    /**
    * \const int _multiplicateurScore
    * \brief Entier qui permet de calculer le score. A chaque fois que Pacman mange un fantome, on gagne 2 fois plus de points. 100 pour le premier puis 200, 400, 800.
    */
    int _multiplicateurScore;
   
    /**
    * \const char _directionSouhaite
    * \brief Direction prit en compte lorsqu'on appuie sur une touche du clavier
    */
    char _directionSouhaite;
    
    /**
    * \const char _directionAsuivre
    * \brief Direction que pacman suit a un moment
    */
    char _directionAsuivre;
    
    /**
    * \const char _directionPrecedente
    * \brief Direction que pacman vient d'emprunter
    */
    char _directionPrecedente;
    
    /**
    * \const sf::SoundBuffer _bufferMort
    * \brief Buffer pour le sond de la mort de pacman
    */
    sf::SoundBuffer _bufferMort;
    
    /**
    * \const sf::Sound _soundMort
    * \brief Son mort Pacman
    */
    sf::Sound _soundMort;
    
    
public:
    /**
    * \const Pacman()
    * \brief Constructeur de pacman.
    *
    */
    Pacman();
    
    /**
    * \const Pacman(int TAILLE_ENTITE, sf::Vector2i POS_INI_PAC, int nbVie)
    * \brief Constructeur de pacman.
    *
    * Pacman ou les fantomes auront une taille correspondant a celle de toutes les entite. La position du constructeur par defaut est au centre de la carte, sa couleur est bleu.
    */
    Pacman(int TAILLE_ENTITE, sf::Vector2i POS_INI_PAC, int nbVie, float AGRANDISSEMENT);
    
    
    /**
    * \const void afficherPacman()
    * \brief Affiche le carre de Pacman, temporaire en attente de sprite
    *
    * 
    */
    void afficherPacman(sf::RenderWindow& window) const;
    
    /**
    * \const Joueur getPacman() const
    * \brief Retourne l'attibut Joueur de Pacman
    *
    * Est utile dans le main pour deplacer Pacman: bool autorisationChangerDIrection
    */
    Joueur getPacman() const;
    
    /**
    * \const void animation_deplacement_spritePacman(sf::Clock clock, sf::Sprite& pacmanSprite, int taillePac, char directionSouhaite, char directionAsuivre, bool autorisation, int TAILLE_ENTITE, char &derniereCase)
    * \brief Gere l'animation du sprite de Pacman
    *
    * Utilise la fonction autorisationChangerDeDirection de la classe joueur, et une horloge pour animer le sprite. Pacman se tourne uniquement lorsqu'il en a la permission.
    */
    void animation_deplacement_spritePacman(sf::Clock clock, bool autorisation, int TAILLE_ENTITE, char &derniereCase);
    
    /**
    * \const void deplacementPacman(char& directionSouhaite, Mur ensembleMurs, char& directionAsuivre, sf::Sprite& sprite, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED)
    * \brief Gere le deplacement de Pacman
    *
    * Deplace Pacman et son sprite a l'aide des fonctions directionSouhaite, autorisationChargerDirection, choixDirection, deplacementAutoJoueur de la classe joueur. Gere egalement l'animation du sprite de Pacman, utilise pour cela la fonction animation_deplacement_spritePacman. Verifie egalement si Pacman rentre en contact avec un tunnel, si c'est le cas le deplace a son autre tunnel correspondant
    */
    void deplacementPacman(Mur ensembleMurs, sf::Clock clock, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED, char &derniereCase, float AGRANDISSEMENT);
    
    /**
    * \const bool interactionBille(Boule& b)
    * \brief Retourne vrai et mange une bille lorsque Pacman rentre en contact avec.
    *
    * Lorsque Pacaman rentre en contact avec le milieu de l'entite qui compose la bille, change l'etat de la bille. Pour voir si Pacman est en contact avec une bille on parcourt le vecteur qui compose l'ensemble des billes. On peut manger une bille seulement si elle n'a pas etait manger avant, pour cela on regarde l'etat de la bille.
    */
    bool interactionBille(Boule& b, sf::Clock& changementEtat, Fantome& f1, Fantome& f2, Fantome& f3, Fantome& f4); //change le comportement de pacman si c'est une grosse bille
    
    /**
    * \const int getNbVies() const
    * \brief Retourne le nombre de vies de Pacman
    *
    *
    */
    int getNbVies() const;
    
    
    /**
    * \const int getNbVies() const
    * \brief Retourne vrai si il en rencontre et fait diminuer la vie de pacman de 1
    *
    *
    */
    bool rencontreFantome(Fantome f);
    
    
    /**
    * \const void interactionFantomes(Fantome& f1, Fantome& f2, Fantome& f3, Fantome& f4, int& point, int TAILLE_ENTITE, bool& nouvelleVie, sf::Clock& clockTest, sf::Vector2i POS_INI_PAC, sf::Vector2i POS_INI_FANTOME, sf::Clock& placementF, int speedP, float AGRANDISSEMENT)
    * \brief Gere l'interaction avec les fantomes
    *
    * En fonction de l'état de pacman, mange un fantome ou se fait tué par le fantome. Gere egalement un multiplicateur de score a chauque fantome mangé. On gagne 100 puis 200 puis 400, 800 points.

    */
    void interactionFantomes(Fantome& f1, Fantome& f2, Fantome& f3, Fantome& f4, int& point, int TAILLE_ENTITE, bool& nouvelleVie, sf::Clock& clockTest, sf::Vector2i POS_INI_PAC, sf::Vector2i POS_INI_FANTOME, sf::Clock& placementF, int speedP, float AGRANDISSEMENT);

    
    /**
    * \const void setPosition(sf::Vector2i POS_INI_PAC, float AGRANDISSEMENT)
    * \brief defini la position de pacman
    *
    * Utilie pour gerer plusieurs résolutions
    */
    void setPosition(sf::Vector2i POS_INI_PAC, float AGRANDISSEMENT);
    
    /**
    * \const sf::Sprite getSprite()
    * \brief retourne le sprite de Pacman
    *
    */
    sf::Sprite getSprite();
    
    
    /**
    * \const void setPosSprite(sf::Vector2f v)
    * \brief Defini la position du sprite de Pacman
    *
    */
    void setPosSprite(sf::Vector2f v);
    
    /**
    * \const float getRotationSprite() const
    * \brief Retourne l'orientation du sprite de pacman
    *
    */
    float getRotationSprite() const;
    
    
    /**
    * \const void AjusterEmplacement(int tailleEntite)
    * \brief Retourne l'orientation du sprite de pacman
    *
    */
    void AjusterEmplacement(int tailleEntite);
    
    
    /**
    * \const void setNbVie(int nbVie)
    * \brief Defini le nombre de vie
    *
    * Utile pour recommencer le jeu
    */
    void setNbVie(int nbVie);
    
    
    /**
    * \const bool getSuperPacman() const
    * \brief Retourne l'etat de pacman
    */
    bool getSuperPacman() const;
    
    /**
    * \const void setSuperPacman(bool etat)
    * \brief Defini l'etat de pacman
    */
    void setSuperPacman(bool etat);
    
    /**
    * \const void setCouleur(sf::Color c)
    * \brief Defini la couleur de l'entite de pacman. Utile si on utilise pas se sprite
    */
    void setCouleur(sf::Color c);
    
    /**
    * \const void changementComportementPF(Fantome& f1, Fantome& f2, Fantome& f3, Fantome& f4, sf::Clock& changementEtat, sf::Clock& clockJeu)
    * \brief Change le comportement de pacman lorsqu'il mange une grosse bille. Cette fonction est appele dans mangeBille. Permet de definir les secondes ou pacman est en mode super pacman
    */
    void changementComportementPF(Fantome& f1, Fantome& f2, Fantome& f3, Fantome& f4, sf::Clock& changementEtat, sf::Clock& clockJeu);
    
    /**
    * \const void changementComportementPF(Fantome& f1, Fantome& f2, Fantome& f3, Fantome& f4, sf::Clock& changementEtat, sf::Clock& clockJeu)
    * \brief Change le comportement de pacman lorsqu'il mange une grosse bille. Cette fonction est appele dans mangeBille
    */
    char getDirectionAsuivre();
};

#endif /* pacman_hpp */
