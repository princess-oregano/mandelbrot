#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <immintrin.h>
#include <assert.h>
#include "optimization.h"

// ############################################################################
// ---------------------------NO_OPTIMIZATION----------------------------------

// Calculates iteration of  dropout.
static int inline
opt_iter(float x, float y, float x_0, float y_0, float scale)
{
        float dx_0 = (x - x_0) * scale;
        float dy_0 = (y_0 - y) * scale;
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
opt_set_pixels(int *pixels, float x_0, float y_0, float scale)
{
        assert(pixels);

        for (float y = 0; y < WINDOW_HEIGHT; y++) {
                for (float x = 0; x < WINDOW_WIDTH; x++) {
                        int elem = (int) x + (int) y * (int) WINDOW_WIDTH;
                        pixels[elem] = opt_iter(x, y, x_0, y_0, scale);
                }
        }

        return pixels;
}

// ############################################################################
// ----------------------------AVX_OPTIMIZATION--------------------------------


void
opt_set_pix_avx(int *pixels, float x_c, float y_c, float scale)
{
        assert(pixels);

        const __m256 avx_r2_lim = _mm256_set1_ps(R_MAX_SQUARED);
        const __m256 avx_dx = _mm256_set_ps(7 * scale, 6 * scale, 5 * scale, 4 * scale,
                                            3 * scale, 2 * scale, 1 * scale, 0 * scale);

        // Convert pixel coordinates to conventional.
        y_c *= scale;
        x_c *= scale;

        for (float y = 0; y < WINDOW_HEIGHT; y++) {
                // y_0 = (y_c - y) * scale;
                __m256 avx_y_0 = _mm256_set1_ps(y_c - y * scale);
                for (float x = 0; x < WINDOW_WIDTH; x += 8) {
                        // x_0 = (x - x_c) * scale;
                        __m256 avx_x_0 = _mm256_add_ps(_mm256_set1_ps(x * scale - x_c), avx_dx);

                        __m256 avx_x = avx_x_0;
                        __m256 avx_y = avx_y_0;

                        __m256i avx_i = _mm256_setzero_si256();
                        for (int i = 0; i < MAX_ITERATION; i++) {
                                // x2 = x * x
                                __m256 avx_x2 = _mm256_mul_ps(avx_x, avx_x);
                                // y2 = y * y
                                __m256 avx_y2 = _mm256_mul_ps(avx_y, avx_y);
                                // xy = x * y
                                __m256 avx_xy = _mm256_mul_ps(avx_x, avx_y);

                                // r2 = x2 + y2
                                __m256 avx_r2 = _mm256_add_ps(avx_x2, avx_y2);

                                __m256 cmp = _mm256_cmp_ps(avx_r2, avx_r2_lim, _CMP_LT_OQ);
                                if (!_mm256_movemask_ps(cmp))
                                        break;

                                avx_i = _mm256_sub_epi32(avx_i, _mm256_castps_si256(cmp));

                                avx_x = _mm256_add_ps(_mm256_sub_ps(avx_x2, avx_y2), avx_x_0);
                                avx_y = _mm256_add_ps(avx_y_0, _mm256_add_ps(avx_xy, avx_xy));
                        }

                        for (int i = 0; i < 8; i++) {
                                int *ptr_iter = (int *) &avx_i;
                                int elem = (int) x + i + (int) y * (int) WINDOW_WIDTH;

                                pixels[elem] = *(ptr_iter + i);
                        }
                }
        }
}
