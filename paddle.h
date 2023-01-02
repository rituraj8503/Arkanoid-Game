#ifndef PADDLE_H
#define PADDLE_H

#include "constants.h"
#include "entity.h"

class paddle : public moving_entity {
    static sf::Texture texture;

    // respond to input from the player
    void process_player_input();

    public:
        paddle(float x, float y);

        void update() override;
        void draw(sf::RenderWindow &window) override;

        void move_up() noexcept override;
        void move_down() noexcept override;
        void move_left() noexcept override;
        void move_right() noexcept override;
};



#endif // PADDLE_H