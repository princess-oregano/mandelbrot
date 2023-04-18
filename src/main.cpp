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
        if (pixels == nullptr)
                return 1;

        float x_0 = WINDOW_WIDTH / 2.f;
        float y_0 = x_0;
        float scale = 6.f / WINDOW_WIDTH;

        while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                                window.close();
                        }
                }

                gr_frame(&window, pixels, &x_0, &y_0, &scale, fps, &font);

                currentTime = clock.getElapsedTime();
                fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
                previousTime = currentTime;
        }

        free(pixels);

        return 0;
}
