#include <stdio.h>
#include "graphics.h"
#include "optimization.h"

int
main()
{
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                                "Mandelbrot");

        float fps = 0;
        sf::Clock clock;
        sf::Time previousTime = clock.getElapsedTime();
        sf::Time currentTime;

        sf::Font font;
        font.loadFromFile("IBMPlexMono-Regular.ttf");

        int *pixels = (int *) calloc(WINDOW_HEIGHT * WINDOW_WIDTH, sizeof(int));

        while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                                window.close();
                        }
                }

                gr_frame(&window, pixels, fps, &font);

                currentTime = clock.getElapsedTime();
                fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
                previousTime = currentTime;
        }
        
        free(pixels);

        return 0;
}
