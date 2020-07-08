#include <vector>
#include "bouton.h"

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

using namespace std;

class Menu{

/**
* \const vector<Bouton> _tabBouton;
* \brief Tableau de Boutons
*
* Un menu x correspondant a un tableau specifique (ex : menu principal, pause, scores...) contient y boutons utiles à ce tableau
*/
    vector<Bouton> _tabBouton;

public:
//Pas de constructeur, le vecteur est vide au depart

/**
* \const void ajoutBouton(Bouton b);
* \brief Ajouter, dans le menu cible, un bouton créer au prealable dans le main
*/
    void ajoutBouton(Bouton b);

/**
* \const void afficheBoutons(float mx, float my, sf::RenderWindow& window);
* \brief Affiche les boutons d'un menu (prise en charge des differents sprites d'un bouton)
*/
    void afficheBoutons(int x, float mx, float my, sf::RenderWindow& window);

/**
* \const void fonctionsBoutonsMenuPrinc(sf::RenderWindow& window, int& affichage, float mx, float my);
* \brief Cette procédure contient toutes les "mécaniques" des boutons du menu principal
*/
    void fonctionsBoutonsMenuPrinc(sf::RenderWindow& window, int& affichage, float mx, float my);

/**
* \const void fonctionsBoutonsMenuComm(sf::RenderWindow& window, int& affichage, float mx, float my, char back);
* \brief Cette procédure contient toutes les "mécaniques" des boutons du menu commande
*/
    void fonctionsBoutonsMenuComm(sf::RenderWindow& window, int& affichage, float mx, float my, char back);

/**
* \const void fonctionsBoutonsMenuPause(sf::RenderWindow& window, int& affichage, float mx, float my);
* \brief Cette procédure contient toutes les "mécaniques" des boutons du menu pause
*/
    void fonctionsBoutonsMenuPause(sf::RenderWindow& window, int& affichage, float mx, float my);

    void fonctionsBoutonsMenuVictoire(sf::RenderWindow& window, int& affichage, float mx, float my);
};

//En cas d'ajout d'un nouveau Menu, il faut créer la methode spécifique aux mécaniques de ses boutons

#endif // MENU_H_INCLUDED
