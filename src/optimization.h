#ifndef OPT_H
#define OPT_H

const int MAX_ITERATION = 256;
const float WINDOW_WIDTH  = 800.f;
const float WINDOW_HEIGHT = 800.f;
const float R_MAX_SQUARED = 20.f;

// Finds iteration of dropout (<MAX_ITERATION) for every pixel of the screen.
int *
opt_set_pixels(int x_0, int y_0, float scale);

#endif // OPT_H

