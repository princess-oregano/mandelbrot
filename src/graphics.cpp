#include <SFML/Graphics.hpp>
#include <assert.h>
#include "graphics.h"
#include "optimization.h"

// Calculates pixel color based on iteration of dot dropout.
static void
gr_set_color(sf::Color *color, int iter)
{
        assert(color);

        color->r = (sf::Uint8) iter * 8;
        color->g = 0;
        color->b = (sf::Uint8) iter % 4 * 32;
        color->a = 255;
}

// Builds image of Mandelbrot figure.
static void
gr_image(sf::Image *image, int *pixels, float x_0, float y_0, float scale)
{
        assert(image);
        assert(pixels);

        opt_set_pixels(pixels, x_0, y_0, scale);

        sf::Color color;
        for (float y = 0; y < WINDOW_HEIGHT; y++) {
                for (float x = 0; x < WINDOW_WIDTH; x++) {
                        int elem = (int) x + (int) WINDOW_WIDTH * (int) y;
                        gr_set_color(&color, pixels[elem]);
                        image->setPixel((uint32_t) x, (uint32_t) y, color);
                }
        }
}

// Catches key and returns value from key_press_t.
// (Could code-generate, BUT ::+<KEY> is not valid token.)
static int
gr_get_key()
{
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                return KEY_LEFT;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                return KEY_RIGHT;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                return KEY_UP;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                return KEY_DOWN;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
                return KEY_ADD;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
                return KEY_SUB;

        return KEY_NON;
}

// Changes position of figure center and scale.
static void
gr_chg_pos(int key, float *x_0, float *y_0, float *scale)
{
        assert(x_0);
        assert(y_0);
        assert(scale);

        switch (key) {
                case KEY_NON:
                        break;
                case KEY_LEFT:
                        *x_0 += AXIS_OFFSET;
                        break;
                case KEY_RIGHT:
                        *x_0 -= AXIS_OFFSET;
                        break;
                case KEY_UP:
                        *y_0 += AXIS_OFFSET;
                        break;
                case KEY_DOWN:
                        *y_0 -= AXIS_OFFSET;
                        break;
                case KEY_ADD:
                        *scale *= SCALE_OFFSET;
                        *x_0 = WINDOW_HEIGHT / 2 + (*x_0 - WINDOW_WIDTH / 2) / SCALE_OFFSET;
                        *y_0 = WINDOW_HEIGHT / 2 + (*y_0 - WINDOW_WIDTH / 2) / SCALE_OFFSET;
                        break;
                case KEY_SUB:
                        *scale /= SCALE_OFFSET;
                        *x_0 = WINDOW_HEIGHT / 2 + (*x_0 - WINDOW_WIDTH / 2) * SCALE_OFFSET;
                        *y_0 = WINDOW_HEIGHT / 2 + (*y_0 - WINDOW_WIDTH / 2) * SCALE_OFFSET;
                        break;
                default:
                        assert(0 && "Invalid key option.\n");
        }
}

void
gr_frame(sf::RenderWindow *window, int *pixels, float *x_0, float *y_0,
        float *scale, float fps, sf::Font *font)
{
        assert(window);
        assert(pixels);
        assert(x_0 && y_0 && scale);
        assert(font);

        gr_chg_pos(gr_get_key(), x_0, y_0, scale);

        sf::Image image;
        image.create(WINDOW_WIDTH, WINDOW_HEIGHT);
        gr_image(&image, pixels, *x_0, *y_0, *scale);

        // A long transformation of image to window, because
        // SFML works this way.
        sf::Texture texture;
        texture.loadFromImage(image);
        sf::Sprite sprite;
        sprite.setTexture(texture);

        sf::Text text;
        text.setFont(*font);
        char fps_str[4] = {};
        sprintf(fps_str, "%.0f", fps);
        text.setString(fps_str);

        window->clear();
        window->draw(sprite);
        window->draw(text);
        window->display();
}

