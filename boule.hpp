#include "entite.hpp"
#include "fichierExterne.hpp"

#ifndef boule_hpp
#define boule_hpp

/**
* \const const float TAILLE_BOULE
* \brief Taille du sprite de la flamme, qui represente les boules a manger
*
* Taille en pixel du sprite
*/
const float TAILLE_BOULE = 200;

/**
* \const const float TAILLE_BOULE
* \brief Redimension la taille des boules en fonction de la taille choisi des entite
*
* Le rapport reduc boule est utiliser pour gerer l'affichage du sprite de le boule dans la focntion afficherBouleCarte
*/

/**
* \const const sf::Vector2i EMPLACEMENT_SPRITE_BOULE
* \brief Emplacement du sprite de la boule dans le fichier texte servant a creer la carte
*/
const sf::Vector2i EMPLACEMENT_SPRITE_BOULE = sf::Vector2i(0,0);

/**
* \const const sf::Texture BOULE_TEXTURE
* \brief Texture des boules flammes que Pacman mange
*
* Est utilie lors de la creation des boules, et lors de l'affichage
*/
const sf::Texture BOULE_TEXTURE = chargementTexture(CHEMIN_REL + "boule.png");


/**
* \const const float TAILLE_SUPER_BOULE
* \brief Taille du sprite de superPacman
*
* Taille en pixel du sprite
*/
const float TAILLE_SUPER_BOULE = 200;

const sf::Texture SUPER_BOULE_TEXTURE = chargementTexture(CHEMIN_REL + "SpriteSheetPacman.png");

class Boule{
    /**
    * \const vector<Entite> _ensembleBoules
    * \brief L'ensemble des boules sera representer par un vecteur d'entite
    *
    * L'ensemble des boules sera creer a partir du tableau sfVector2i qui provient de la lecture du fichier texte.
    */
    std::vector<Entite> _ensembleBoules;
    
    /**
    * \const vector<sf::Vector2i> _positionFichier
    * \brief Stocke pour chaque entite flamme sa position a partir du fichier texte de depart
    *
    * Sera utile pour gerer l'affichage des flammes/boules.
    */
    std::vector<sf::Vector2i> _positionFichier;
    
    /**
    * \const vector<bool> _etat
    * \brief Stocke pour chaque entite flamme son etat.
    *
    * Sera utile pour gerer l'affichage des flammes/boules lorsqu'elles sont mangees par Pacman. Par defaut leur etat est true, lorsqu'elle est manger son etat devient false.
    */
    std::vector<bool> _etat;
    
    /**
    * \const sf::Sprite _spriteBoule
    * \brief Sprite des boules en forme de flamme
    */
    sf::Sprite _spriteBoule;
    
    sf::Sprite _spriteSuperBoule;
    
    std::vector<bool> _superBoule;
    
public:
    /**
    * \const Boule(vector<vector<sf::Vector2i>> map, int TAILLE_ENTITE, float REDUC_BOULE)
    * \brief Constructeur permettant de creer l'ensemble des boules de la carte
    *
    * A partir du tableau de sf::Vector2i construit en parcourant le fichier texte qui modelise les element de la carte défini : la position de chaque boule, leur taille qui correspond a la valeur TAILLE_ENTITE, et leur etat de base aucune n'est mange.
    */
    Boule(std::vector<std::vector<sf::Vector2i> > map, int TAILLE_ENTITE, float REDUC_BOULE);
    
    /**
    * \const void definirInfoBoules()
    * \brief Initialise les attributs de chaque billes/flammes.
    *
    * Utilise la fonction update sur chaque entite qui compose une bille. Cette fonction est appele pour creer les entite boules.
    */
    void definirInfoBoules();
    
    /**
    * \const void afficherBouleCarte(sf::Sprite& boules, sf::RenderWindow& window, float tpsEcoule, int TAILLE_ENTITE)
    * \brief Affiche les billes a l'ecran.
    *
    * A partir du sprite des flammes, afiiche sur la fenetre les billes, le tempsEcoule sert a animer les flammes. On affiche les billes seulement si leur etat vaut true, donc qu'elles ne sont pas encore mange.
    */
    void afficherBouleCarte(sf::RenderWindow& window, float tpsEcoule, int TAILLE_ENTITE);
    
    /**
    * \const Entite getEntiteBoule(int i) const
    * \brief Retourne l'entite i du vecteur qui constitue l'ensemble des boules/flammes
    *
    * Sera utile pour gerer l'interaction entre pacman et les boules dans la fonction mangerBille
    */
    Entite getEntiteBoule(int i) const;
    
    /**
    * \const int getNombreBoules() const
    * \brief Retourne le nombres de billes sur la carte
    *
    * Sera utile pour gerer l'interaction entre pacman et les boules dans la fonction mangerBille. Utile egalement pour afficher le nombre de boules dans la fonction afficherNbPoints
    */
    int getNombreBoules() const;
    
    /**
    * \const bool pasDejaMange(int i) const
    * \brief Retourne l'etat de la bille numero i
    *
    * Sera utile pour gerer l'interaction entre pacman et les boules dans la fonction mangerBille.
    */
    bool pasDejaMange(int i) const;
    
    /**
    * \const void mangerBoule(int i)
    * \brief Changer l'etat de la boule numero i
    *
    * Sera utile pour gerer l'interaction entre pacman et les boules dans la fonction mangerBille.
    */
    void mangerBoule(int i);
    
    /**
    * \const void activerToutesLesBilles()
    * \brief Utile pour recommencer le jeu
    *
    * Reinitialise toute les boules en etat visible
    */
    void activerToutesLesBilles();
    
    /**
    * \const int getNbBillesMangees()
    * \brief Utile pour 
    *
    * Reinitialise toute les boules en etat visible
    */
    int getNbBillesMangees();
    
    /**
    * \const int getNbBillesMangees()
    * \brief Utile pour
    *
    * Reinitialise toute les boules en etat visible
    */
    bool getEtatSuperBoule(int i) const;
};


#endif /* boule_hpp */
