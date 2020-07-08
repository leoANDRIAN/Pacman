#include "entite.hpp"

Entite::Entite(sf::Vector2f position, sf::Vector2f size, int TAILLE_ENTITE){
    _rect.setPosition(position);
    _rect.setSize(sf::Vector2f(TAILLE_ENTITE,TAILLE_ENTITE));
}

Entite::Entite(sf::Vector2f position, sf::Vector2f size, sf::Color color){
    _rect.setPosition(position);
    _rect.setSize(size);
    _rect.setFillColor(color);
}

sf::RectangleShape Entite::getRect() const{
    return _rect;
}

void Entite::update(){
    _bottom = _rect.getPosition().y + _rect.getSize().y;
    _left = _rect.getPosition().x;
    _right = _rect.getPosition().x + _rect.getSize().x;
    _top = _rect.getPosition().y;
}

bool Entite::colision(Entite e) const{
    return !(_right < (e._left+e._right)/2 || _left > (e._left+e._right)/2 || _bottom < (e._top+e._bottom)/2 || _top > (e._top+e._bottom)/2);
}

bool Entite::colisionDroite(Entite e) const{
    return (_right >= e._left && _right <= e._right) && ( (_bottom > e._top && _bottom <= e._bottom) || (_top < e._bottom && _top >= e._top)) ;
}

bool Entite::colisionGauche(Entite e) const{
    return (_left <= e._right && _left >= e._left) && ( (_bottom > e._top && _bottom <= e._bottom) || (_top < e._bottom && _top >= e._top) );
}

bool Entite::colisionHaut(Entite e) const{
    return (_top == e._bottom) && ( (_right > e._left && _right <= e._right) || (_left < e._right && _left > e._left) );
}

bool Entite::colisionBas(Entite e) const{
    return (_bottom == e._top) && ( (_right > e._left && _right <= e._right) || (_left < e._right && _left >= e._left) );
}

void Entite::moveEntite(int x, int y){
    _rect.move(x, y);
    update();
}



void Entite::setRect(sf::Vector2i position){
    _rect.setPosition(position.x, position.y);
    update();
}


void Entite::setCouleur(sf::Color c){
    _rect.setFillColor(c);
}
 
