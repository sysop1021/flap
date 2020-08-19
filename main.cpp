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

    Bird bird;

    FPSCounter fpsCounter;

    std::deque <Pipe> bottomPipes;
    std::deque <Pipe> topPipes;

    float pipeTimer = 0.f;

    sf::Clock clock;

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

        /* Handle Input */
        // punting to update

        /* Update */
        backgroundSprite.setPosition((int)(bgScroll -= BACKGROUND_SCROLL_SPEED * dt.asSeconds()) % BACKGROUND_LOOP_POINT, 0);
        foregroundSprite.setPosition((int)(fgScroll -= FOREGROUND_SCROLL_SPEED * dt.asSeconds()) % WINDOW_WIDTH, fgYPos);

        pipeTimer += dt.asSeconds();

        if (pipeTimer > 2.f)
        {
            // TODO: MB: need to reconsider this - memory leak prone?
            bottomPipes.push_back(*new Pipe(false));
            topPipes.push_back(*new Pipe(true));
            pipeTimer = 0;
        }

        for (int i = 0; i < bottomPipes.size(); i++)
        {
            bottomPipes[i].update(dt.asSeconds());

        }

        for (int i = 0; i < topPipes.size(); i++)
        {
            topPipes[i].update(dt.asSeconds());

        }

        if (bottomPipes.size() > 5)
        {
            bottomPipes.pop_front();
        }

        if (topPipes.size() > 5)
        {
            topPipes.pop_front();
        }

        bird.update(dt.asSeconds());

        /* Draw */
        window.clear();
        window.draw(backgroundSprite);

        for (int i = 0; i < bottomPipes.size(); i++)
        {
            bottomPipes[i].render(window);
        }

        for (int i = 0; i < topPipes.size(); i++)
        {
            topPipes[i].render(window);
        }

        window.draw(foregroundSprite);
        bird.render(window);
        fpsCounter.render(dt, window);
        window.display();
    }

    return 0;
}
