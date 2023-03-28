#include <stdio.h>
#include "graphics.h"
#include "optimization.h"

int
main()
{
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), 
                                "Mandelbrot");

        float fps;
        sf::Clock clock;
        sf::Time previousTime = clock.getElapsedTime();
        sf::Time currentTime;

        while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                                window.close();
                        }
                }

                gr_frame(&window); 

                currentTime = clock.getElapsedTime();
                fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
                fprintf(stderr, "%.0f\n", fps);
                previousTime = currentTime;
        }


        return 0;
}
