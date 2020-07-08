#include "boule.hpp"

#ifndef affichageTexte_hpp
#define affichageTexte_hpp

/**
* \const void affichageNbPoints(sf::Font policeArial, sf::RenderWindow& window, int point, Boule ensembleBoules, int TAILLE_ENTITE)
* \brief Affiche le nombre de point actuel sur le nombre de boules totales
*
*   La police choisi est l'arial, on affiche sur la partie droite de la fenetre le message. L'ensemble des boules est necessaire pour afficher le total
*/
void affichageNbPoints(sf::Font policeArial, sf::RenderWindow& window, int point, Boule ensembleBoules, int TAILLE_ENTITE);

/**
* \const void affichageVictoire(sf::Font policeArial, sf::RenderWindow& window, bool condition)
* \brief Affiche victoire sur une nouvelle fenetre
*
*   La police choisi est l'arial, on affiche le message sur un nouveau rectangle a condition d'avoir ramasser toutes les boules
*/
void affichageVictoire(sf::Font policeArial, sf::RenderWindow& window);



/**
* \const void affichageNbVies(sf::Font policeArial, sf::RenderWindow& window, int vies, int nbVieTot,  int TAILLE_ENTITE)
* \brief Affiche le nombre de vie de Pacman
*
*   La police choisi est l'arial, on affiche sur la partie droite de la fenetre le message.
*/
void affichageNbVies(sf::Font policeArial, sf::RenderWindow& window, int nbVie, int nbVieTot, int TAILLE_ENTITE);


#endif /* affichageTexte_hpp */
