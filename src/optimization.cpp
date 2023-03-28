#include <stdio.h>
#include <stdlib.h>
#include "optimization.h"

// ############################################################################
// ---------------------------NO_OPTIMIZATION----------------------------------

// Calculates iteration of  dropout.
int
opt_iter(int x, int y)
{
        float dx_0 = (WINDOW_WIDTH / 2.f - x) / (WINDOW_WIDTH / 6.f);
        float dy_0 = - (WINDOW_HEIGHT / 2.f - y) / (WINDOW_HEIGHT / 6.f);
        float dx = dx_0;
        float dy = dy_0;

        int i = 0;
        for ( ; i < MAX_ITERATION; i++) {
                float dx2 = dx * dx;
                float dy2 = dy * dy;
                float xy = dx * dy;

                dx = dx2 - dy2 + dx_0;
                dy = 2 * xy + dy_0;

                if (dx * dx + dy * dy > R_MAX_SQUARED)
                        break;
        }

        return i;
}

int *
opt_set_pixels()
{
        int *pixels = (int *) calloc(WINDOW_HEIGHT * WINDOW_WIDTH, sizeof(int));

        for (int y = 0; y < WINDOW_HEIGHT; y++) {
                for (int x = 0; x < WINDOW_WIDTH; x++) {
                        pixels[x + WINDOW_WIDTH * y] = opt_iter(x, y);
                }
        }

        return pixels;
}

// ############################################################################
