#ifndef OPT_H
#define OPT_H

const int WINDOW_WIDTH  = 800;
const int WINDOW_HEIGHT = 800;
const int MAX_ITERATION = 256;
const float R_MAX_SQUARED = 20;

// Finds iteration of dropout (<MAX_ITERATION) for every pixel of the screen.
int *
opt_set_pixels(int x_0, int y_0);

#endif // OPT_H

