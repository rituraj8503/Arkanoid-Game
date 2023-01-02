#ifndef BRICK_H
#define BRICK_H

#include "constants.h"
#include "entity.h"

class brick : public entity {
    static sf::Texture texture;

    int strength{constants::brick_strength};

    public:
        brick(float x, float y);

        // Helper functions for brick strength
        void set_strength(int) noexcept;
        void weaken() noexcept;
        bool is_too_weak() const noexcept;

        void update() override;
        void draw(sf::RenderWindow &window) override;
};

#endif // BRICK_H