#include "entite.hpp"
#ifndef tunnel_hpp
#define tunnel_hpp

//les tunnels horizontaux sont representer par 9,9 dans le fichier texte.
//Il faut qu'ils soientt sur la partie des murs de la carte.

class TunnelHorizontal{
    /**
    * \const std::vector<int> _positionsY
    * \brief Ensemble des ordonnes correspondant au tunnels
    *
    */
    std::vector<int> _positionsY;
    
    /**
    * \const int _largeurCarte
    * \brief Largeur de la carte
    *
    * Ne prends pas en compte les x,x avant les premieres valeurs. On suppose la carte rectangulaire
    */
    int _largeurCarte;
    
    /**
    * \const int _debutCarte
    * \brief Debut de la carte dans le fichier texte
    *
    * Correspond a la premiere position son l'axe des abscisse : x, pour laquelle on a pas mit x,x sur la premiere ligne du fichier texte.
    */
    int _debutCarte;
    
public:
    /**
    * \const TunnelHorizontal(std::vector<std::vector<sf::Vector2i> > map)
    * \brief Creation des tunnels horizontaux
    *
    * A partir de la carte, on creer les tunnels. Pour cela on parcout d'abord la premiere ligne pour trouver le debut de la carte. On en déduit alors la taille de la carte. On parcourt ensuite toutes les lignes a la recherche de tunnels horizontaux qui seront situé sur la gauche de la carte.
    */
    TunnelHorizontal(std::vector<std::vector<sf::Vector2i> > map);
    
    /**
    * \const int getLargeurCarte() const
    * \brief Retourne la largeur de la carte.
    *
    * Est utile dans la classe Joueur, pour que les joueurs interagissent avec les tunnels
    */
    int getLargeurCarte() const;
    
    /**
    * \const std::vector<int> getPostionsY() const
    * \brief Retourne les positions en y des tunnels horizontaux.
    *
    * Est utile dans la classe Joueur, pour que les joueurs interagissent avec les tunnels
    */
    std::vector<int> getPostionsY() const;
    
    /**
    * \const int getDebCarte() const
    * \brief Retourne le debut de la carte.
    *
    * Est utile dans la classe Joueur, pour que les joueurs interagissent avec les tunnels
    */
    int getDebCarte() const;
};

#endif /* tunnel_hpp */
