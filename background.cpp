#include "background.h"

sf::Texture background::texture;


background::background(float x, float y) : entity() {
    texture.loadFromFile("background.jpg");

    sprite.setTexture(texture);

    sprite.setPosition(x, y);
}

void background::update() {

}

void background::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}