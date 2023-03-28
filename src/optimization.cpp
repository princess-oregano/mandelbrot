#include <stdio.h>
#include <stdlib.h>
#include "optimization.h"

// ############################################################################
// ---------------------------NO_OPTIMIZATION----------------------------------

// Calculates iteration of  dropout.
int
opt_iter(int x, int y)
{
        float dx = WINDOW_WIDTH - x; 
        float dx_0 = dx;
        float dy = WINDOW_HEIGHT - y; 
        float dy_0 = dy;
        fprintf(stderr, "dx = %lg, dy = %lg\n", dx, dy);
        int i = 0;
        for ( ; i < MAX_ITERATION; i++) {
                float dx2 = dx * dx;
                float dy2 = dy * dy;
                float xy = dx * dy;

                dx = dx2 - dy2 + dx_0;
                dy = 2 * xy + dy_0;

                fprintf(stderr, "r2 = %.0f\n", dx*dx+dy*dy);
                if (dx * dx + dy * dy > R_MAX_SQUARED) 
                        break;
        }

        return i;
}

int *
opt_coord()
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
