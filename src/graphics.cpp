#include <SFML/Graphics.hpp>
#include <assert.h>
#include "graphics.h"
#include "optimization.h"

// Calculates pixel color based on iteration of dot dropout.
static void
gr_set_color(sf::Color *color, int iter)
{
        assert(color);

        fprintf(stderr, "iter = %d\n", iter);

        color->r = iter * 8;
        color->g = iter * 8;
        color->b = iter * 8;
        color->a = iter * 8;
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
gr_frame(sf::RenderWindow *window)
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

        window->clear();
        window->draw(sprite); 
        window->display();
}

