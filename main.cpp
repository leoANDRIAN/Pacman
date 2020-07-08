#include "joueur.hpp"
#include "entite.hpp"
#include "mur.hpp"
#include "boule.hpp"
#include "affichageTexte.hpp"
#include "fichierExterne.hpp"
#include "fantome1.hpp"
#include "pacman.hpp"
#include "Menu.h"
#include "tunnel.hpp"

using namespace std;
int main(){

    //Creation de la fenetre
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Pac-Man");
    window.setFramerateLimit(60);
    const float tailleF = window.getSize().y;
    const int TAILLE_ENTITE=48; //taille des entitees, qui vont compose murs, boule, pacman & fantome
    float AGRANDISSEMENT;
    choixTailleResolution(tailleF, AGRANDISSEMENT);

    sf::Font policeArial = chargementPolice(CHEMIN_REL + "arial.ttf");

    // Recuperer les infos du fichier texte
    std::vector<std::vector<sf::Vector2i> > map = ouverture_creation_carte(CHEMIN_REL + "map.txt");


    //generer les murs
    const float REDUC_MUR = (AGRANDISSEMENT*TAILLE_ENTITE) / TAILLE_TUILE_MUR;
    Mur ensembleMurs(map, TAILLE_ENTITE, REDUC_MUR);

    //generer les boules
    const float REDUC_BOULE = (AGRANDISSEMENT*TAILLE_ENTITE) / (1.5*TAILLE_BOULE);
    Boule ensembleBoules(map, TAILLE_ENTITE, REDUC_BOULE);

    //Creation de pacman
    const int SPEED = (TAILLE_ENTITE) /12; //vitesse de deplcement
    const sf::Vector2i POS_INI_PAC = sf::Vector2i( TAILLE_ENTITE*24, TAILLE_ENTITE*24);
    int nbVieTot = 3;
    Pacman pacman(TAILLE_ENTITE, POS_INI_PAC, nbVieTot, AGRANDISSEMENT);

    //fantome
    const sf::Vector2i POS_INI_FANTOME = sf::Vector2i(TAILLE_ENTITE*24.5, TAILLE_ENTITE*15);


    Fantome fantome1(TAILLE_ENTITE, POS_INI_FANTOME, sf::Color::Red, SPEED, 14, AGRANDISSEMENT, 0);
    Fantome fantome2(TAILLE_ENTITE, POS_INI_FANTOME, sf::Color::Blue, SPEED, 14, AGRANDISSEMENT, 1);
    Fantome fantome3(TAILLE_ENTITE, POS_INI_FANTOME, sf::Color::Green, SPEED, 14, AGRANDISSEMENT, 2);
    Fantome fantome4(TAILLE_ENTITE, POS_INI_FANTOME, sf::Color::Yellow, SPEED, 14, AGRANDISSEMENT, 3);

    //Charge la texture du menu
    sf::Texture menuT;
    if (!menuT.loadFromFile(CHEMIN_REL + "Menu.png")) cout << "Erreur chargement image menu" << endl;

    //Construction d'un vecteur contenant les boutons du menu principal
    Menu menuPrinc;
    Menu menuComm;
    Menu menuPause;
    Menu menuVictoire;
    Menu menuDefaite;

    //Construction des boutons du menu
    Bouton titre(desktop.width/2, 150, 0, 300, 800, 200, menuT);
    Bouton jouer(desktop.width/2+200, desktop.height/2-100, 0, 0, 400, 100, menuT);
    Bouton commande(desktop.width/2+200, desktop.height/2+50, 0, 100, 400, 100, menuT);
    Bouton quitter(desktop.width/2+200, desktop.height/2+200, 0 ,200 ,400, 100, menuT);

    Bouton retour(desktop.width-100, desktop.height-100, 0 ,500 ,400, 100, menuT);
    Bouton instructions(desktop.width-(desktop.width/2), desktop.height-(desktop.height/2), 800, 0, 600, 200, menuT);

    Bouton reprendre(desktop.width/2+200, desktop.height/2-100, 0, 600, 400, 100, menuT);
    Bouton pause(desktop.width/2+200, 150, 0, 700, 400, 100, menuT);

    Bouton victoire(desktop.width/2+75, 200, 1000, 600, 600, 130, menuT);
    Bouton defaite(desktop.width/2+50, 200, 900, 750, 600, 200, menuT);
    Bouton recommencer(desktop.width/2+200, desktop.height/2-50, 800, 200, 400, 100, menuT);

    menuPrinc.ajoutBouton(titre);
    menuPrinc.ajoutBouton(jouer);
    menuPrinc.ajoutBouton(commande);
    menuPrinc.ajoutBouton(quitter);

    menuComm.ajoutBouton(instructions);
    menuComm.ajoutBouton(retour);

    menuPause.ajoutBouton(pause);
    menuPause.ajoutBouton(reprendre);
    menuPause.ajoutBouton(commande);

    menuVictoire.ajoutBouton(victoire);
    menuVictoire.ajoutBouton(recommencer);
    menuVictoire.ajoutBouton(quitter);

    menuDefaite.ajoutBouton(defaite);
    menuDefaite.ajoutBouton(recommencer);
    menuDefaite.ajoutBouton(quitter);

    float mx; //axe x de la souris
    float my; //axe y de la souris
    char derniereCase = 'f';
    bool nouvelleVie = true;


    //Creattion des tunnels
    TunnelHorizontal tunnel(map);

    //horloge
    sf::Clock clockP;
    sf::Clock clock;
    sf::Clock clockJeu;
    sf::Clock changementEtat;
    sf::Clock placementF;
    sf::Clock stopPourchasser;
    int point = 0;

    //Gestion du bouton retour
    char back = 'p';

    //switch des differentes interfaces
    int affichage = 1;

    while (window.isOpen())
    {
        //animation des flammes et de Pacman
        if (clock.getElapsedTime().asSeconds() > 0.4) clock.restart();
        if (stopPourchasser.getElapsedTime().asSeconds() > 6) stopPourchasser.restart();
        sf::Event event;
        window.clear();

        while (window.pollEvent(event) )
        {
            if (event.type == sf::Event::Closed) window.close();
        }
        //On recupere la pos de la souris
        mx = sf::Mouse::getPosition(window).x;
        my = sf::Mouse::getPosition(window).y;
        //Gestion des différents affichages possibles
        switch (affichage) {
                //Menu principal
            case 1:
                menuPrinc.afficheBoutons(1, mx, my, window);
                menuPrinc.fonctionsBoutonsMenuPrinc(window, affichage, mx, my);
                clockJeu.restart();
                back = 'm';
                break;
                //menu commandes
            case 3:
                menuComm.afficheBoutons(1, mx, my, window);
                menuComm.fonctionsBoutonsMenuComm(window, affichage, mx, my, back);
                break;
                //menu pause
            case 4:
                menuPause.afficheBoutons(1, mx, my, window);
                menuPause.fonctionsBoutonsMenuPause(window, affichage, mx, my);
                back = 'p';
                break;
                //menu victoire
            case 5:
                menuVictoire.afficheBoutons(1, mx, my, window);
                menuVictoire.fonctionsBoutonsMenuVictoire(window, affichage, mx, my);
                break;
                //menu victoire
            case 6:
                menuDefaite.afficheBoutons(1, mx, my, window);
                menuDefaite.fonctionsBoutonsMenuVictoire(window, affichage, mx, my);
                break;
                //le jeu
            case 2:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && clockJeu.getElapsedTime().asSeconds() > 5.2){
                    affichage = 4;
                }
                if (pacman.getNbVies() != 0 && ensembleBoules.getNbBillesMangees() != ensembleBoules.getNombreBoules()){
                    ensembleMurs.afficherMurCarte(window, TAILLE_ENTITE*AGRANDISSEMENT);
                    ensembleBoules.afficherBouleCarte(window, clock.getElapsedTime().asSeconds(), TAILLE_ENTITE*AGRANDISSEMENT);
                    pacman.afficherPacman(window);
                    fantome1.afficherFantome(window);
                    fantome2.afficherFantome(window);
                    fantome3.afficherFantome(window);
                    fantome4.afficherFantome(window);
                    affichageNbPoints(policeArial, window, point, ensembleBoules, TAILLE_ENTITE*AGRANDISSEMENT);
                    affichageNbVies(policeArial, window, pacman.getNbVies(), nbVieTot, TAILLE_ENTITE*AGRANDISSEMENT);
                    window.display();
                }
                if (clockJeu.getElapsedTime().asSeconds() > 2) nouvelleVie = true;
                if (nouvelleVie){

                    fantome1.placementDebPartie(TAILLE_ENTITE, clockJeu, AGRANDISSEMENT);
                    fantome2.placementDebPartie(TAILLE_ENTITE, clockJeu, AGRANDISSEMENT);
                    fantome3.placementDebPartie(TAILLE_ENTITE, clockJeu, AGRANDISSEMENT);
                    fantome4.placementDebPartie(TAILLE_ENTITE, clockJeu, AGRANDISSEMENT);

                    //compter et affichage des points
                    if( pacman.interactionBille(ensembleBoules, changementEtat, fantome1, fantome2, fantome3, fantome4) ) {
                        point ++;
                    }

                    if (pacman.getNbVies() != 0 && ensembleBoules.getNbBillesMangees() != ensembleBoules.getNombreBoules()){
                        pacman.deplacementPacman(ensembleMurs, clockP, tunnel, TAILLE_ENTITE*AGRANDISSEMENT, SPEED, derniereCase, AGRANDISSEMENT);

                        pacman.interactionFantomes(fantome1, fantome2, fantome3, fantome4, point, TAILLE_ENTITE, nouvelleVie, clockJeu, POS_INI_PAC, POS_INI_FANTOME, placementF, SPEED, AGRANDISSEMENT);
                        pacman.changementComportementPF(fantome1, fantome2, fantome3, fantome4, changementEtat, clockJeu);

                        //gerer Fantomes
                        sf::Vector2f cibleF = pacman.getPacman().getBody().getRect().getPosition();
                        fantome1.deplacementF1(ensembleMurs, tunnel, TAILLE_ENTITE, SPEED, cibleF, AGRANDISSEMENT, stopPourchasser);
                        fantome2.deplacementF2(ensembleMurs, tunnel, TAILLE_ENTITE, SPEED, cibleF, pacman.getDirectionAsuivre(), AGRANDISSEMENT, stopPourchasser);
                        fantome3.deplacementF3(ensembleMurs, tunnel, TAILLE_ENTITE, SPEED, cibleF, pacman.getDirectionAsuivre(), AGRANDISSEMENT, stopPourchasser);
                        fantome4.deplacementF4(ensembleMurs, tunnel, TAILLE_ENTITE, SPEED, cibleF, AGRANDISSEMENT, stopPourchasser);
                    }
                    else
                    {
                        pacman.setPosition(POS_INI_PAC, AGRANDISSEMENT);
                        pacman.AjusterEmplacement(TAILLE_ENTITE*AGRANDISSEMENT);
                        fantome1.placementZoneFantome(TAILLE_ENTITE, AGRANDISSEMENT);
                        fantome2.placementZoneFantome(TAILLE_ENTITE, AGRANDISSEMENT);
                        fantome3.placementZoneFantome(TAILLE_ENTITE, AGRANDISSEMENT);
                        fantome4.placementZoneFantome(TAILLE_ENTITE, AGRANDISSEMENT);
                        fantome1.setEtatComstible(false);
                        fantome2.setEtatComstible(false);
                        fantome3.setEtatComstible(false);
                        fantome4.setEtatComstible(false);
                        pacman.setSuperPacman(false);
                        clockJeu.restart();
                        ensembleBoules.activerToutesLesBilles();
                        pacman.setNbVie(nbVieTot);
                        point=0;
                        if (ensembleBoules.getNbBillesMangees() == ensembleBoules.getNombreBoules()){
                            affichage = 5;
                        }
                        else{
                            affichage = 6;
                        }
                    }
                }
        }
    }
    return 0;
}




