#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH  = 1280;
const int WINDOW_HEIGHT = 720;
const float BACKGROUND_SCROLL_SPEED = 30.f;
const float FOREGROUND_SCROLL_SPEED = 60.f;
const int BACKGROUND_LOOP_POINT = 1032;

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "bird1");

    sf::Texture backgroundTex, foregroundTex;

    backgroundTex.loadFromFile("assets/background.png");
    sf::Sprite backgroundSprite(backgroundTex);
    backgroundSprite.setScale(2.5f, 2.5f);
    float bgScroll = 0.f;
    backgroundSprite.setOrigin(0, 0);
    backgroundSprite.setPosition(0, 0);

    foregroundTex.loadFromFile("assets/ground.png");
    sf::Sprite foregroundSprite(foregroundTex);
    foregroundSprite.setScale(2.5f, 2.5f);
    float fgScroll = 0.f;
    foregroundSprite.setOrigin(0, 0);
    float fgYPos = (WINDOW_HEIGHT - foregroundSprite.getGlobalBounds().height);
    foregroundSprite.setPosition(0, fgYPos);

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
        }

        /* Handle Input */

        /* Update */
        backgroundSprite.setPosition((int)(bgScroll -= BACKGROUND_SCROLL_SPEED * dt.asSeconds()) % BACKGROUND_LOOP_POINT, 0); // TODO: bug: this jump is SUUUUUPER noticeable
        foregroundSprite.setPosition((int)(fgScroll -= FOREGROUND_SCROLL_SPEED * dt.asSeconds()) % WINDOW_WIDTH, fgYPos);

        /* Draw */
        window.clear();
        window.draw(backgroundSprite);
        window.draw(foregroundSprite);
        window.display();
    }

    return 0;
}
