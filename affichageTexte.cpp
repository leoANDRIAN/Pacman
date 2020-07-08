#include "affichageTexte.hpp"

void affichageNbPoints(sf::Font policeArial, sf::RenderWindow& window, int point, Boule ensembleBoules, int TAILLE_ENTITE){
    sf::Text points;
    points.setFont(policeArial);
    points.setString(std::to_string(point));
    points.setStyle(sf::Text::Bold); //En gras
    points.setFillColor(sf::Color::White); //Couleur
    points.setPosition(25*TAILLE_ENTITE, 0.5*TAILLE_ENTITE);
    points.setCharacterSize(TAILLE_ENTITE);
    window.draw(points);
    
    sf::Text texte;
    texte.setFont(policeArial);
    texte.setString(std::to_string(ensembleBoules.getNbBillesMangees()));
    texte.setStyle(sf::Text::Bold); //En gras
    texte.setFillColor(sf::Color::White); //Couleur
    texte.setPosition(34*TAILLE_ENTITE, 0.5*TAILLE_ENTITE);
    texte.setCharacterSize(TAILLE_ENTITE);
    window.draw(texte);
    
    sf::Text total;
    total.setFont(policeArial);
    total.setString("/ " + std::to_string(ensembleBoules.getNombreBoules()));
    total.setStyle(sf::Text::Bold); //En gras
    total.setFillColor(sf::Color::White); //Couleur
    total.setPosition(37*TAILLE_ENTITE, 0.5*TAILLE_ENTITE);
    total.setCharacterSize(TAILLE_ENTITE);
    window.draw(total);
}

void affichageVictoire(sf::Font policeArial, sf::RenderWindow& window){
    sf::RectangleShape fond;
    fond.setSize(sf::Vector2f(window.getSize().x,window.getSize().y));
    fond.setFillColor(sf::Color::Black);
    window.draw(fond);
    
    sf::Text victoire;
    victoire.setFont(policeArial);
    victoire.setString("VICTOIRE !");
    victoire.setStyle(sf::Text::Bold);
    victoire.setFillColor(sf::Color::White);
    victoire.setPosition(window.getSize().x/4, window.getSize().y/4);
    victoire.setCharacterSize(window.getSize().x/10);
    window.draw(victoire);
    window.display();
}


void affichageNbVies(sf::Font policeArial, sf::RenderWindow& window, int nbVie, int nbVieTot, int TAILLE_ENTITE){
    sf::Text texte;
    texte.setFont(policeArial);
    texte.setString(std::to_string(nbVie));
    texte.setStyle(sf::Text::Bold); //En gras
    texte.setFillColor(sf::Color::White); //Couleur
    texte.setPosition(11*TAILLE_ENTITE, 0.5*TAILLE_ENTITE);
    texte.setCharacterSize(TAILLE_ENTITE);
    window.draw(texte);
    
    sf::Text total;
    total.setFont(policeArial);
    total.setString("/ " + std::to_string(nbVieTot));
    total.setStyle(sf::Text::Bold); //En gras
    total.setFillColor(sf::Color::White); //Couleur
    total.setPosition(12*TAILLE_ENTITE, 0.5*TAILLE_ENTITE);
    total.setCharacterSize(TAILLE_ENTITE);
    window.draw(total);
}
