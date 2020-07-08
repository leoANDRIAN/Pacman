#include "Menu.h"

//explications des procédures dans le menu.h

void Menu::ajoutBouton(Bouton b)
{
    _tabBouton.push_back(b);
}

void Menu::afficheBoutons(int x, float mx, float my, sf::RenderWindow& window)
{
    for (int i=x; i<_tabBouton.size(); i++)
    {
        if(_tabBouton[i].getSprite().getGlobalBounds().contains(mx, my))
        {
            _tabBouton[i].changeBoutonActif();
            window.draw(_tabBouton[i].getSprite());
            _tabBouton[i].changeBoutonPassif();
        }
        else window.draw(_tabBouton[i].getSprite());
    }
    window.draw(_tabBouton[0].getSprite());
    window.display();
}

void Menu::fonctionsBoutonsMenuPrinc(sf::RenderWindow& window, int& affichage, float mx, float my)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _tabBouton[1].getSprite().getGlobalBounds().contains(mx, my)){
        affichage = 2;
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _tabBouton[2].getSprite().getGlobalBounds().contains(mx, my)){
        affichage = 3;
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _tabBouton[3].getSprite().getGlobalBounds().contains(mx, my)) window.close();
}

void Menu::fonctionsBoutonsMenuPause(sf::RenderWindow& window, int& affichage, float mx, float my)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _tabBouton[1].getSprite().getGlobalBounds().contains(mx, my)){
        affichage = 2;
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _tabBouton[2].getSprite().getGlobalBounds().contains(mx, my)){
        affichage = 3;
    }
}

void Menu::fonctionsBoutonsMenuComm(sf::RenderWindow& window, int& affichage, float mx, float my, char back)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _tabBouton[1].getSprite().getGlobalBounds().contains(mx, my) && back == 'm'){
        affichage = 1;
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _tabBouton[1].getSprite().getGlobalBounds().contains(mx, my) && back == 'p'){
        affichage = 4;
    }
}

void Menu::fonctionsBoutonsMenuVictoire(sf::RenderWindow& window, int& affichage, float mx, float my)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _tabBouton[1].getSprite().getGlobalBounds().contains(mx, my)){
        affichage = 2;
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _tabBouton[2].getSprite().getGlobalBounds().contains(mx, my)){
        window.close();
    }
}
