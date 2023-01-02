#ifndef ENTITY_H
#define ENTITY_H


#include <SFML/Graphics.hpp>

class entity {
    protected:
        sf::Sprite sprite;

        bool destroyed{false};

    public:
        virtual void update() = 0;
        virtual void draw(sf::RenderWindow &window) = 0;

        // helper function to get the bounding box of a sprite
        sf::FloatRect get_bounding_box() const noexcept;

        // helper function to get the center of a sprite
        sf::Vector2f get_center() const noexcept;

        // helper functions to get the positions of the sprite
        float x() const noexcept;
        float y() const noexcept;

        // helper functions to get the edges of the sprite
        float left() const noexcept;
        float right() const noexcept;
        float top() const noexcept;
        float bottom() const noexcept;

        // helper functions for the state of the entity
        void destroy() noexcept;
        bool is_destroyed() const noexcept;


        virtual ~entity() {}
};


class moving_entity : public entity {
    protected:
        sf::Vector2f velocity;
    public:
        // helper functions to change the sprite's direction
        virtual void move_up() noexcept = 0;
        virtual void move_down() noexcept = 0;
        virtual void move_left() noexcept = 0;
        virtual void move_right() noexcept = 0;
        

};









#endif // ENTITY_H