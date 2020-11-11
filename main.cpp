/*
    TODO: BUG: when moving or resizing the window, it screws with
    the position of new spawning pipes.

    TODO: pipes spawn every 2 seconds currently - make sure that random pipe spawning doesn't happen at on-screen coords
    (pipes may "pop-in" with current implementation)

    TODO: replace deque usage with my own data structure

    TODO: Implement ground collision
*/

#include <SFML/Graphics.hpp>
#include <deque>

#include "constants.h"
#include "Bird.h"
#include "Pipe.h"
#include "FPSCounter.h"

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "bird9");
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

    Pipe::topTex.loadFromFile("assets/topPipe.png");
    Pipe::bottomTex.loadFromFile("assets/bottomPipe.png");

    sf::Font titleFont;
    titleFont.loadFromFile("assets/flappy.ttf");

    sf::Text titleCard;
    titleCard.setString("Floppy Bird");
    titleCard.setFont(titleFont);
    titleCard.setFillColor(sf::Color::White);
    titleCard.setCharacterSize(70);
    titleCard.setPosition(WINDOW_WIDTH / 2 - titleCard.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 - titleCard.getGlobalBounds().height + 10);

    sf::Text enterPrompt;
    enterPrompt.setString("Press Enter to play");
    enterPrompt.setFont(titleFont);
    enterPrompt.setFillColor(sf::Color::White);
    //enterPrompt.setCharacterSize(/*uint - 30 is default */);
    enterPrompt.setPosition(WINDOW_WIDTH / 2 - enterPrompt.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 + enterPrompt.getGlobalBounds().height + 10);

    sf::Text lostText;
    lostText.setString("Bummer, dude.");
    lostText.setFont(titleFont);
    lostText.setFillColor(sf::Color::White);
    lostText.setCharacterSize(70);
    lostText.setPosition(WINDOW_WIDTH / 2 - lostText.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 - lostText.getGlobalBounds().height - 40);

    sf::Text scoreText;
    scoreText.setString("Score: 0");
    scoreText.setFont(titleFont);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    sf::Text scoreCard;
    scoreCard.setString("Score: 0");
    scoreCard.setFont(titleFont);
    scoreCard.setFillColor(sf::Color::White);
    scoreCard.setPosition(WINDOW_WIDTH / 2 - scoreCard.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 - scoreCard.getGlobalBounds().height / 2);

    sf::Text againPrompt;
    againPrompt.setString("Press Enter to play again");
    againPrompt.setFont(titleFont);
    againPrompt.setFillColor(sf::Color::White);
    //againPrompt.setCharacterSize(/*uint - 30 is default */);
    againPrompt.setPosition(WINDOW_WIDTH / 2 - againPrompt.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 + againPrompt.getGlobalBounds().height + 40);

    Bird bird;

    unsigned int score = 0;

    FPSCounter fpsCounter;

    std::deque<Pipe> pipes;

    float pipeTimer = 0.f;

    sf::Clock clock;

    State state = TITLE;

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
        switch (state)
        {
            case PLAY:
            {
                backgroundSprite.setPosition((int)(bgScroll -= BACKGROUND_SCROLL_SPEED * dt.asSeconds()) % BACKGROUND_LOOP_POINT, 0);
                foregroundSprite.setPosition((int)(fgScroll -= FOREGROUND_SCROLL_SPEED * dt.asSeconds()) % WINDOW_WIDTH, fgYPos);

                pipeTimer += dt.asSeconds();

                // Pipes are spawning based on time, rather than distance - I may change this
                if (pipeTimer > 2.5f)
                {
                    pipes.push_back(*new Pipe());
                    pipeTimer = 0;
                }

                for (unsigned int i = 0; i < pipes.size(); i++)
                {
                    pipes[i].update(dt.asSeconds());

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
                        state = SCORE;
                    }

                    if (bird.xPos + bird.width >= pipes[i].bottomX + pipes[i].bottomWidth && !pipes[i].isScored)
                    {
                        pipes[i].isScored = true;
                        score++;
                        scoreText.setString("Score: " + std::to_string(score));
                    }
                }

                window.clear();
                window.draw(backgroundSprite);

                for (unsigned int i = 0; i < pipes.size(); i++)
                {
                    pipes[i].render(window);
                }
                window.draw(scoreText);
                window.draw(foregroundSprite);
                bird.render(window);
            }
            break;

            case TITLE:
            {

                backgroundSprite.setPosition((int)(bgScroll -= BACKGROUND_SCROLL_SPEED * dt.asSeconds()) % BACKGROUND_LOOP_POINT, 0);
                foregroundSprite.setPosition((int)(fgScroll -= FOREGROUND_SCROLL_SPEED * dt.asSeconds()) % WINDOW_WIDTH, fgYPos);

                window.draw(backgroundSprite);
                window.draw(titleCard);
                window.draw(enterPrompt);
                window.draw(foregroundSprite);


                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    bird.resetPos();
                    state = PLAY;
                }
            }
            break;

            case SCORE:
            {
                pipes.clear();
                backgroundSprite.setPosition((int)(bgScroll -= BACKGROUND_SCROLL_SPEED * dt.asSeconds()) % BACKGROUND_LOOP_POINT, 0);
                foregroundSprite.setPosition((int)(fgScroll -= FOREGROUND_SCROLL_SPEED * dt.asSeconds()) % WINDOW_WIDTH, fgYPos);

                window.draw(backgroundSprite);
                window.draw(lostText);
                scoreCard.setString("Score: " + std::to_string(score));
                window.draw(scoreCard);
                window.draw(againPrompt);
                window.draw(foregroundSprite);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    bird.resetPos();
                    state = PLAY;
                    score = 0;
                    scoreText.setString("Score: " + std::to_string(score));
                }
            }
            break;

        default:
            {

            }
            break;
        }

        /* Draw */

        fpsCounter.render(dt, window);
        window.display();
    }

    return 0;
}
