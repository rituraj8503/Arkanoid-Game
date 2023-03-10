#include "interactions.h"

bool is_interacting(const entity &e1, const entity &e2) {
    auto box1 = e1.get_bounding_box();
    auto box2 = e2.get_bounding_box();
    return box1.intersects(box2);
}


void handle_collision(ball &b, const paddle &p) {
    if (is_interacting(p, b)) {
        // the ball bounces upwards
        b.move_up();

        // depending on where the paddle is hit, the ball will move in different directions
        if (b.x() < p.x()) {
            b.move_left();
        } else {
            b.move_right();
        }
    }
}

void handle_collision(ball &the_ball, brick &block) {
    if (is_interacting(block, the_ball)) {
        block.weaken();

        if (block.is_too_weak()) {
            block.destroy();
        }
        

        float left_overlap = the_ball.right() - block.left();
        float right_overlap = block.right() - the_ball.left();
        float top_overlap = the_ball.bottom() - block.top();
        float bottom_overlap = block.bottom() - the_ball.top();


        // if left overlap is smaller than right overlap, the bal hit the left side
        bool from_left = std::abs(left_overlap) < std::abs(right_overlap);
        bool from_top = std::abs(top_overlap) < std::abs(bottom_overlap);

        // use the right or left overlap as appropriate
        float min_x_overlap = from_left ? left_overlap : right_overlap;
        float min_y_overlap = from_top ? top_overlap : bottom_overlap;

        // if the ball hit the left or right side of the brick, change its horizontal direction
        // if the ball hit the top or bottom of the brick, change its vertical direction

        if (std::abs(min_x_overlap) < std::abs(min_y_overlap)) {
            if (from_left) {
                the_ball.move_left();
            } else {
                the_ball.move_right();
            }
        } else {
            if (from_top) {
                the_ball.move_up();
            } else {
                the_ball.move_down();
            }
        }


        
    }
}