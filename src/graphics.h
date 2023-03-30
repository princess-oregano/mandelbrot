#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>

const float  AXIS_OFFSET = 20.f;
const float SCALE_OFFSET = 0.9f;

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
gr_frame(sf::RenderWindow *window, int *pixels, float *x_0, float *y_0,
        float *scale, float fps, sf::Font *font);

#endif // GRAPHICS_H

