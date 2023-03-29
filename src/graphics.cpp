#include <SFML/Graphics.hpp>
#include <assert.h>
#include "graphics.h"
#include "optimization.h"

// Calculates pixel color based on iteration of dot dropout.
static void
gr_set_color(sf::Color *color, int iter)
{
        assert(color);

        color->r = iter * 8;
        color->g = 0;
        color->b = iter % 2 * 64;
        color->a = 255;
}

// Builds image of Mandelbrot figure.
static void
gr_image(sf::Image *image, int x_0, int y_0, float scale)
{
        assert(image);

        int *pixels = opt_set_pixels(x_0, y_0, scale);

        for (unsigned int y = 0; y < WINDOW_HEIGHT; y++) {
                for (unsigned int x = 0; x < WINDOW_WIDTH; x++) {
                        sf::Color color;
                        gr_set_color(&color, pixels[x + WINDOW_WIDTH * y]);
                        image->setPixel(x, y, color);
                }
        }

        free(pixels);
}

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

static void
gr_chg_pos(int key, int *x_0, int *y_0, float *scale)
{
        switch (key) {
                case KEY_NON: 
                        break;
                case KEY_LEFT:
                        *x_0 += 10; 
                        break;
                case KEY_RIGHT: 
                        *x_0 -= 10; 
                        break;
                case KEY_UP: 
                        *y_0 += 10;
                        break;
                case KEY_DOWN: 
                        *y_0 -= 10;
                        break;
                case KEY_ADD:
                        *scale -= 0.01;
                        break;
                case KEY_SUB: 
                        *scale += 0.01;
                        break;
                default:
                        assert(0 && "Invalid key option.\n");
        }
}

void
gr_frame(sf::RenderWindow *window, float fps, sf::Font *font)
{
        assert(window);

        static int x_0 = WINDOW_WIDTH;
        static int y_0 = WINDOW_HEIGHT;
        static float scale = 6.f;

        gr_chg_pos(gr_get_key(), &x_0, &y_0, &scale);

        fprintf(stderr, "%f\n", scale);
        sf::Image image;
        image.create(WINDOW_WIDTH, WINDOW_HEIGHT);
        gr_image(&image, x_0, y_0, scale);

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

