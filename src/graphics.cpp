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
gr_image(sf::Image *image)
{
        assert(image);

        int *pixels = opt_coord();

        for (unsigned int y = 0; y < WINDOW_HEIGHT; y++) {
                for (unsigned int x = 0; x < WINDOW_WIDTH; x++) {
                        sf::Color color;
                        gr_set_color(&color, pixels[x + WINDOW_WIDTH * y]);
                        image->setPixel(x, y, color);
                }
        }

        free(pixels);
}

void 
gr_frame(sf::RenderWindow *window, float fps, sf::Font *font)
{
        assert(window);

        sf::Image image;
        image.create(WINDOW_WIDTH, WINDOW_HEIGHT);
        gr_image(&image);
        
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

