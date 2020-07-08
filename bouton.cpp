#include "bouton.h"

using namespace std;

    Bouton::Bouton(int xPos, int yPos, int xTex, int yTex, int horizontal, int vertical, sf::Texture& t)
    {
        _portion = sf::IntRect(xTex, yTex, horizontal, vertical);
        _spriteBouton.setTexture(t);
        _spriteBouton.setTextureRect(_portion);
        _spriteBouton.setOrigin(400.f, 100.f);
        _spriteBouton.setPosition(xPos, yPos);
    }

    void Bouton::changeBoutonActif()
    {
        _portion.left += 400;
        _spriteBouton.setTextureRect(_portion);
    }

    void Bouton::changeBoutonPassif()
    {
        _portion.left -= 400;
        _spriteBouton.setTextureRect(_portion);
    }

    sf::Sprite Bouton::getSprite()
    {
        return _spriteBouton;
    }
