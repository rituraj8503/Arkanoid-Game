#ifndef GAME_H
#define GAME_H

#include <memory>
#include <typeinfo>
#include <vector>


#include "background.h"
#include "ball.h"
#include "brick.h"
#include "constants.h"
#include "entity.h"
#include "paddle.h"

// use aliases to simplify our code
using entity_vector = std::vector<std::unique_ptr<entity>>;
using entity_alias_vector = std::vector<entity *>;

class entity_manager {
    // A vector to store all the entities in the game
    entity_vector all_entities;

    // A map to store the entities grouped by type
    std::map<size_t, entity_alias_vector> grouped_entities;

    public:
        // Function to create an entity object of type T using args as constructor arguments
        template<typename T, typename ...Args>
        T &create(Args&& ...args) {
            static_assert(std::is_base_of<entity, T>::value, R"("T" type parameter in create() must be derived from "entity")");

            // Create a unique_ptr to the entity, Forward the arguments to the entity's constructor
            auto ptr{std::make_unique<T>(std::forward<Args>(args)...)};

            // Make an alias pointer to the allocated memory. This will be stored in the entity_type_vector
            auto ptr_alias = ptr.get();

            // Get the hash code for the entity object's type
            auto hash = typeid(T).hash_code();

            // Insert the object's pointer into the hash map
            grouped_entities[hash].emplace_back(ptr_alias);

            // Insert the object's pointer into the entities vector
            all_entities.emplace_back(std::move(ptr));

            // Return the new object
            return *ptr_alias;
        }

        // Function to scan all entities and clean up the destroyed ones
        void refresh();

        // Function to destroy all entities 
        void clear();

        // Function to update all the entities
        void update();

        // Function to draw all the entities
        void draw(sf::RenderWindow &window);

        // Function to retreive all the objects of a given type
        template <typename T>
        auto &get_all() {
            return grouped_entities[typeid(T).hash_code()];
        }

        // Apply a function to all entities of a given type
        template <typename T, typename Func>
        void apply_all(const Func &func) {
            auto &entity_group{get_all<T>()};

            for (auto ptr : entity_group) {
                func(*dynamic_cast<T*>(ptr));
            }
        }


};

class game {
    enum class game_state { paused, game_over, running, player_wins };


    sf::RenderWindow game_window{{constants::window_width, constants::window_height}, "Simple Breakout Game Version 1"};

    // background the_background{0.0f, 0.0f};

    // ball the_ball{constants::window_width/2.0f, constants::window_height/2.0f};

    // paddle the_paddle{constants::window_width/2.0f, constants::window_height - constants::paddle_height};

    // std::vector<brick> bricks;

    // Instead of initializing everything one at a time, just do it all at once with an entity manager
    entity_manager manager;

    sf::Font verdana;
    sf::Text text_state, text_lives;
    

    game_state state{game_state::game_over};

    int lives{constants::player_lives};

    public:
        game();

        // Reinitialize the game
        void reset();

        // Game loop
        void run();

}; 



#endif // GAME_H