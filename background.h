#ifndef BACKGROUND_H
#define BACKGROUND_H


#include "constants.h"
#include "entity.h"

class background : public entity {
    static sf::Texture texture;

    public:
        background(float x, float y);

        void update() override;
        void draw(sf::RenderWindow &window) override; 

};



#endif // BACKGROUND_H