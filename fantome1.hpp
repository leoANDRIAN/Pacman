#include "joueur.hpp"
#include <cmath>

#ifndef fantome1_hpp
#define fantome1_hpp

class Fantome{
    Joueur _fantome;
    
    /**
    * \const sf::Texture _textureFantome
    * \brief Texture du sprite d'un fantome
    */
    sf::Texture _textureFantome;
    
    /**
    * \const sf::Sprite _spriteFantome1
    * \brief Sprite du fantome 1.
    */
    sf::Sprite _spriteFantome1;
    
    /**
    * \const char _directionSouhaite
    * \brief Direction a emprunter pour aller sur Pacman
    */
    char _directionSouhaite;
    
    /**
    * \const char _directionAsuivre
    * \brief Direction que le fantome suit a un moment
    */
    char _directionAsuivre;
    
    /**
    * \const char _directionAsuivre
    * \brief Direction que le fantome suit a un moment
    */
    char _directionInterdit;
    
    /**
    * \const char _directionPrecedente
    * \brief Direction que le fantome vient d'emprunter
    */
    char _directionPrecedente;
    
    /**
    * \const char _directionPrecedente
    * \brief Direction que le fantome vient d'emprunter
    */
    sf::Vector2f _positionPrecedent;
    
    /**
    * \const std::vector<char> _directionPossiblePrecedente
    * \brief Met a jour le directionPossible que peut emprunter un fantome
    */
    std::vector<char> _directionPossiblePrecedente;
    
    /**
    * \const int _dist_XPrecedent
    * \brief distance entre pacman et un fantome
    */
    int _dist_XPrecedent;
    
    /**
    * \const int _dist_YPrecedent
    * \brief distance entre pacman et un fantome
    */
    int _dist_YPrecedent;
    
    /**
    * \const bool _comestible
    * \brief Etant faisant varier l'interaction avec pacman, le deplacement du fantome
    */
    bool _comestible;
    
    /**
    * \const bool _seDeplacer
    * \brief Permet au fantome de se deplacer ou non
    */
    bool _seDeplacer;
    
    
    /**
    * \const sf::Clock _TpsReaparition
    * \brief Clock permettant au fantome d'apparaitre après être mort
    */
    sf::Clock _TpsReaparition;
    
    
    /**
    * \const sf::Color _saCouleur
    * \brief Couleur du fantome, utile lorsqu'on utilie pas de sprite
    */
    sf::Color _saCouleur;
    
    /**
    * \const int _speedF
    * \brief Vitesse de deplacement du fantome
    */
    int _speedF;
    
    /**
    * \const int _numeroFantome
    * \brief Numero du fantome. Utile pour gerer l'endroit d'apparition ainsi que son temps d'apparition
    */
    int _numeroFantome;
    
    /**
    * \const int _positionIniF
    * \brief Sert a initialiser le placement du fantome. Varie au fur et a mesure qu'on creer des entite fantomes. Varie grace au numeroFantome
    */
    sf::Vector2i _positionIniF;
        
    
    /**
    * \const bool _vienD_etre_mange
    * \brief Varie lorsque pacman mange un fantome. Peut être utile pour changer l'animation du sprite des fantomes lorsqu'il retourne a leur position initiale.
    */
    bool _vienD_etre_mange;
    
public:
    /**
    * \const Fantome(int TAILLE_ENTITE, sf::Vector2i POS_INI_Fantome, sf::Color couleur, int speedP, int tailleImage, float AGRANDISSEMENT, int nF)
    * \brief Initalise un fantome.
    */
    Fantome(int TAILLE_ENTITE, sf::Vector2i POS_INI_Fantome, sf::Color couleur, int speedP, int tailleImage, float AGRANDISSEMENT, int nF);
    
    /**
    * \const void afficherFantome(sf::RenderWindow& window)
    * \brief Affiche le sprite d'un fantome. Peut egalement afficher le carre de couleur
    */
    void afficherFantome(sf::RenderWindow& window) ;
    
    /**
    * \const void deplacement(Mur ensembleMurs, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED, sf::Vector2f posPacman, float AGRANDISSEMENT)
    * \brief Permet de deplacer le fantome. Il pointe sur posPacman. Sera utiliser pour le comportement de chaque fantome
    */
    void deplacement(Mur ensembleMurs, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED, sf::Vector2f posPacman, float AGRANDISSEMENT);
    
    /**
    * \const deplacementF1(Mur ensembleMurs, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED, sf::Vector2f posPacman, float AGRANDISSEMENT, sf::Clock stopPourchasser)
    * \brief Permet de deplacer le fantome 1. Il pointe sur pacman. La clock stopPourcahsser est fait pour faire varier les moments de répit. Pour l'instant ils ne sont pas prit en compte car l'IA est trop simple sinon. Le fantome 1 pointe toujours sur pacman
    */
    void deplacementF1(Mur ensembleMurs, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED, sf::Vector2f posPacman, float AGRANDISSEMENT, sf::Clock stopPourchasser);
    
    /**
    * \const void deplacementF2(Mur ensembleMurs, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED, sf::Vector2f posPacman, char directionAsuivre, float AGRANDISSEMENT, sf::Clock stopPourchasser)
    * \brief Permet de deplacer le fantome 1. Il pointe 8 cases devant la ou pointe Pacman.
    */
    void deplacementF2(Mur ensembleMurs, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED, sf::Vector2f posPacman, char directionAsuivre, float AGRANDISSEMENT, sf::Clock stopPourchasser);
    
    /**
    * \const void deplacementF3(Mur ensembleMurs, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED, sf::Vector2f posPacman, char directionAsuivre, float AGRANDISSEMENT, sf::Clock stopPourchasser)
    * \brief Permet de deplacer le fantome 1. Il fait la moyenne entre la ou pointe le premier et le deuxieme fantome
    */
    void deplacementF3(Mur ensembleMurs, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED, sf::Vector2f posPacman, char directionAsuivre, float AGRANDISSEMENT, sf::Clock stopPourchasser);
    
    /**
    * \const void deplacementF4(Mur ensembleMurs, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED, sf::Vector2f posPacman, float AGRANDISSEMENT, sf::Clock stopPourchasser)
    * \brief Permet de deplacer le fantome 1. Il pointe sur pacman sauf quand il est a moins de 4 cases de lui, dans ce cas il retourne a sa position de depart
    */
    void deplacementF4(Mur ensembleMurs, const TunnelHorizontal& t, int TAILLE_ENTITE, int SPEED, sf::Vector2f posPacman, float AGRANDISSEMENT, sf::Clock stopPourchasser);
    
    /**
    * \const void MAJ_directionInterdite()
    * \brief Mets a jour a chaque instant la direction interdite d'un fantome car il n'a pas le droit de faire demi-tour
    */
    void MAJ_directionInterdite();
    
    /**
    * \const std::vector<char> listeDirectionPossible(Mur ensembleMurs) const
    * \brief En fonction de sa position et des murs qui l'entoure, liste les directions possible a prendre
    */
    std::vector<char> listeDirectionPossible(Mur ensembleMurs) const;
    
    /**
    * \const char choixDirrectionOptimal(sf::Vector2f posPacman) const
    * \brief En fonction de la position de pacman et du fantome choisi la meilleur option de déplacement
    */
    char choixDirrectionOptimal(sf::Vector2f posPacman) const;
    
    /**
    * \const Joueur getFantome() const
    * \brief Retourne l'attribut joueur du fantome
    */
    Joueur getFantome() const;
    
    
    /**
    * \const void seFaitMange(sf::Vector2i POS_INI_FANT, float AGRANDISSEMENT, int TAILLE_ENTITE)
    * \brief Change l'etat du fantome ainsi que sa position lorsuqu'il se fait manger
    */
    void seFaitMange(sf::Vector2i POS_INI_FANT, float AGRANDISSEMENT, int TAILLE_ENTITE);
    
    /**
    * \const void placementApresManger(int TAILLE_ENTITE, sf::Clock clockJeu, float AGRANDISSEMENT, float tpsApparition)
    * \brief Change l'emplacement du fantome après avoir été mangé
    */
    void placementApresManger(int TAILLE_ENTITE, sf::Clock clockJeu, float AGRANDISSEMENT, float tpsApparition);
    
    /**
    * \const void placementDebPartie(int TAILLE_ENTITE, sf::Clock clockJeu, float AGRANDISSEMENT)
    * \brief Place les fantomes a leur position de départ. Leur position varie en fonction de l'ordre a laquelle ils sont créer.
    */
    void placementDebPartie(int TAILLE_ENTITE, sf::Clock clockJeu, float AGRANDISSEMENT);
    
    
    /**
    * \const void placementDebPartie(int TAILLE_ENTITE, sf::Clock clockJeu, float AGRANDISSEMENT)
    * \brief Place les fantomes a leur position de départ. Leur position varie en fonction de l'ordre a laquelle ils sont créer.
    */
    bool getEtatComestible() const;
    
    /**
    * \const void setEtatComstible(bool etat)
    * \brief Change l'etat des fantomes.
    */
    void setEtatComstible(bool etat);
    
    /**
    * \const bool getEtatSeDeplacer() const
    * \brief Retourne l'etat du fantome pour savoir si il peut se deplacer ou non.
    */
    bool getEtatSeDeplacer() const;
    
    /**
    * \const void setEtatSeDeplacer(bool etat)
    * \brief Defini l'etat de se deplacer pour un fantome
    */
    void setEtatSeDeplacer(bool etat);
    
    /**
    * \const void setCouleur(sf::Color c)
    * \brief Defini la couleur du fantome. Est utilse lorsqu'on travaille sans sprime
    */
    void setCouleur(sf::Color c);
    
    /**
    * \const void majDirectionInterditeGrosseBoule()
    * \brief Change direction interdit du fantome et sa vitesse de deplacement
    */
    void majDirectionInterditeGrosseBoule();
    
    /**
    * \const void placementZoneFantome(int TAILLE_ENTITE, float AGRANDISSEMENT)
    * \brief Sert a decaler la positon des fantomes dans leur zone de départ.
    */
    void placementZoneFantome(int TAILLE_ENTITE, float AGRANDISSEMENT);
};


#endif /* fantome1_hpp */
