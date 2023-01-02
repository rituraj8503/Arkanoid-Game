#include <algorithm>

#include "game.h"
#include "interactions.h"

using namespace std;

void entity_manager::refresh() {
    // clean up the entity pointers first
    for (auto & [type, alias_vector] : grouped_entities) {
        alias_vector.erase(remove_if(begin(alias_vector), end(alias_vector), [](auto p) { return p->is_destroyed(); }), end(alias_vector));
    }

    all_entities.erase(remove_if(begin(all_entities), end(all_entities), [](const auto &p) { return p->is_destroyed();}), end(all_entities));
}

void entity_manager::clear() {
    grouped_entities.clear();
    all_entities.clear();
}

void entity_manager::update() {
    for (auto &e : all_entities) {
        e->update();
    }
}

void entity_manager::draw(sf::RenderWindow &window) {
    for (auto &e : all_entities) {
        e->draw(window);
    }
}


game::game() {
    // for (int i = 0; i < constants::brick_columns; ++i) {
    //     for (int j = 0; j < constants::brick_rows; ++j) {
    //         // Calculate the brick's position
    //         float x = constants::brick_offset + (i + 1) * constants::brick_width;
    //         float y = (j + 1) * constants::brick_height;

    //         bricks.emplace_back(x, y);
    //     }
    // }

    // set the frame limit
    game_window.setFramerateLimit(60);

    verdana.loadFromFile("verdana.ttf");

    text_state.setFont(verdana);
    text_state.setPosition(constants::window_width/2.0f-100.0f, constants::window_height/2.0f-100.0f);
    text_state.setCharacterSize(35);
    text_state.setFillColor(sf::Color::White);
    text_state.setString("Paused");

    text_lives.setFont(verdana);
    text_lives.setPosition(constants::window_width/2.0f-65.0f, constants::window_height/2.0f-50.0f);
    text_lives.setCharacterSize(35);
    text_lives.setFillColor(sf::Color::White);
    text_lives.setString("Lives: " + std::to_string(lives));

}

void game::reset() {
    lives = constants::player_lives;

    state = game_state::paused;

    manager.clear();
    manager.create<background>(0.0f, 0.0f);

    manager.create<ball>(constants::window_width/2.0f, constants::window_height/2.0f);
    manager.create<paddle>(constants::window_width/2.0f, constants::window_height - constants::paddle_height);
    
    for (int i = 0; i < constants::brick_columns; ++i) {
        for (int j = 0; j < constants::brick_rows; ++j) {
            // Calculate the brick's position
            float x = constants::brick_offset + (i + 1) * constants::brick_width;
            float y = (j + 1) * constants::brick_height;

            manager.create<brick>(x, y);
        }
    }
}

void game::run() {
    // Was the pause key pressed in the last frame?
    bool pause_key_active{false};


    // while our window is open
    while (game_window.isOpen()) {
        // clear our window -> turn screen to black
        game_window.clear(sf::Color::Black);

        // initialize a user event
        sf::Event event;


        // poll for an event, check to see if the user has done anything
         while (game_window.pollEvent(event)) {
            // if the user clicks the close button, close the window
            if (event.type == sf::Event::Closed) {
                game_window.close();
            }
        }

        // if the user presses the escape key, close the button
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            break;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
            if (!pause_key_active) {
                if (state == game_state::paused) {
                    state = game_state::running;
                } else {
                    state = game_state::paused;
                }
            }
            pause_key_active = true;
        } else {
            pause_key_active = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
            reset();
        }


        if (state == game_state::paused) {
            manager.draw(game_window);
        }

        if (state != game_state::running) {
            switch(state) {
                case game_state::paused:
                    text_state.setString("   Paused   ");
                    break;
                case game_state::game_over:
                    text_state.setString("   Game Over!   ");
                    break;
                case game_state::player_wins:
                    text_state.setString("   Player Wins!   ");
                default:
                    break;
            }
            game_window.draw(text_state);
            game_window.draw(text_lives);
        } else {
            if (manager.get_all<ball>().empty()) {
                manager.create<ball>(constants::window_width/2.0f, constants::window_height/2.0f);
                --lives;
                state = game_state::paused;
            }


            if (manager.get_all<brick>().empty()) {
                state = game_state::player_wins;
            }

            if (lives <= 0) {
                state = game_state::game_over;
            }

            text_lives.setString("Lives: " + std::to_string(lives));
            manager.update();

            manager.apply_all<ball>([this](auto &the_ball) {
                manager.apply_all<brick>([&the_ball](auto &the_brick) {
                    handle_collision(the_ball, the_brick);
                });
            });

            // for (auto &b : bricks) {
            //     handle_collision(the_ball, b);
            // }

            // ball and paddle interaction
            manager.apply_all<ball>([this](auto &the_ball) {
                manager.apply_all<paddle>([&the_ball](auto &the_paddle) {
                    handle_collision(the_ball, the_paddle);
                });
            });

            manager.refresh();

            manager.draw(game_window);
        }
        // the_background.draw(game_window);
        // the_ball.draw(game_window);
        // the_paddle.draw(game_window);

        // for (auto b : bricks) {
        //     b.draw(game_window);
        // }

        // display the window
        game_window.display();
    }

}