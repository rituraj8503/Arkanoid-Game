#include <SFML/Graphics.hpp>
#include <string>
#include <random>
#include "constants.h";


using namespace std;
using namespace std::literals;

// Class to represent the ball
class creature {
    static mt19937 mt;
    static bernoulli_distribution bd;


    float vx{4.0f};
    float vy{4.0f};
    sf::Vector2 velocity;

    sf::CircleShape circle;

    public:
        creature(float x, float y) {
            velocity = {vx, vy};
            circle.setPosition(x, y);


            circle.setRadius(5.0f);
            circle.setFillColor(sf::Color::Red);
        }

        void draw(sf::RenderWindow &window) {
            window.draw(circle);
        }

        void update() {
            vx = bd(mt) ? vx : -vx;
            vy = bd(mt) ? vy : -vy;

            circle.move({vx, vy});
        }
}