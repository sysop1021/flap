/*
    TODO: BUG: when moving or resizing the window, it screws with
    the position of new spawning pipes.

    TODO: pipes spawn every 2 seconds currently - make sure that random pipe spawning doesn't happen at on-screen coords
    (pipes may "pop-in" with current implementation)

    TODO: Bug - pipes may occasionally spawn overlapping each other (along x axis)

    TODO: replace deque usage with my own data structure
*/

#include <SFML/Graphics.hpp>
#include <deque>

#include "constants.h"
#include "Bird.h"
#include "Pipe.h"
#include "FPSCounter.h"

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "bird6");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    srand(time(0));

    sf::Texture backgroundTex;
    backgroundTex.loadFromFile("assets/background.png");
    sf::Sprite backgroundSprite(backgroundTex);
    backgroundSprite.setScale(SCALING_FACTOR, SCALING_FACTOR);
    float bgScroll = 0.f;
    backgroundSprite.setOrigin(0, 0);
    backgroundSprite.setPosition(0, 0);

    sf::Texture foregroundTex;
    foregroundTex.loadFromFile("assets/ground.png");
    sf::Sprite foregroundSprite(foregroundTex);
    foregroundSprite.setScale(SCALING_FACTOR, SCALING_FACTOR);
    float fgScroll = 0.f;
    foregroundSprite.setOrigin(0, 0);
    float fgYPos = (WINDOW_HEIGHT - foregroundSprite.getGlobalBounds().height);
    foregroundSprite.setPosition(0, fgYPos);

    Pipe::tex.loadFromFile("assets/pipe.png");

    Bird bird;

    FPSCounter fpsCounter;

    std::deque<Pipe> pipes;

    float pipeTimer = 0.f;

    sf::Clock clock;

    bool isScrolling = true;

    /* Game Loop */
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }

            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11))
            {
                fpsCounter.showCtr = !fpsCounter.showCtr;
            }
        }

        /* Update */

        if (isScrolling)
        {
            backgroundSprite.setPosition((int)(bgScroll -= BACKGROUND_SCROLL_SPEED * dt.asSeconds()) % BACKGROUND_LOOP_POINT, 0);
            foregroundSprite.setPosition((int)(fgScroll -= FOREGROUND_SCROLL_SPEED * dt.asSeconds()) % WINDOW_WIDTH, fgYPos);

            pipeTimer += dt.asSeconds();

            // Pipes are spawning based on time, rather than distance - I may change this
            if (pipeTimer > 2.f)
            {
                pipes.push_back(*new Pipe());
                pipeTimer = 0;
            }

            for (unsigned int i = 0; i < pipes.size(); i++)
            {
                pipes[i].update(dt.asSeconds());

                // remove old pipes as they pass to the left of the window
                if (pipes[i].bottomX + pipes[i].bottomWidth < 0)
                {
                     pipes.pop_front();
                }
            }

            bird.update(dt.asSeconds());

            for (unsigned int i = 0; i < pipes.size(); i++)
            {
                if (bird.checkCollision(pipes[i]))
                {
                    isScrolling = false;
                }
            }
        }

        /* Draw */
        window.clear();
        window.draw(backgroundSprite);

        for (unsigned int i = 0; i < pipes.size(); i++)
        {
            pipes[i].render(window);
        }

        window.draw(foregroundSprite);
        bird.render(window);
        fpsCounter.render(dt, window);
        window.display();
    }

    return 0;
}
