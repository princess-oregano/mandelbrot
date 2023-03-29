#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>

enum key_press_t {
        KEY_NON   = 0, 
        KEY_LEFT  = 1,
        KEY_RIGHT = 2,
        KEY_UP    = 3,
        KEY_DOWN  = 4,
        KEY_ADD   = 5,
        KEY_SUB   = 6,
};

// Draws single frame.
void
gr_frame(sf::RenderWindow *window, float fps, sf::Font *font);

#endif // GRAPHICS_H

