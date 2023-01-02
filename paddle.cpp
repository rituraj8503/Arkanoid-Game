#include "paddle.h"

sf::Texture paddle::texture;

paddle::paddle(float x, float y) : moving_entity() {
    // load the texture
    texture.loadFromFile("paddle.png");
    sprite.setTexture(texture);

    sprite.setPosition(x, y);
    velocity = {constants::paddle_speed, 0.0f};

    sprite.setOrigin(get_center());
}

void paddle::update() {
    process_player_input();

    sprite.move(velocity);

}

void paddle::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void paddle::move_up() noexcept {}

void paddle::move_down() noexcept {}

void paddle::move_left() noexcept {
    velocity.x = -constants::paddle_speed;
}

void paddle::move_right() noexcept {
    velocity.x = constants::paddle_speed;
}

void paddle::process_player_input() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        // Move to the left if left arrow keyis pressed unless you have gone past the left hand side
        if (x() >= 0) {
            velocity.x = -constants::paddle_speed;
        } else {
            velocity.x = 0;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        if (x() <= constants::window_width) {
            velocity.x = constants::paddle_speed;
        } else {
            velocity.x = 0;
        }
    } else {
        velocity.x = 0;
    }
}