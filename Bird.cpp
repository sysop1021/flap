#include "Bird.h"
#include "constants.h"

Bird::Bird()
{
    tex.loadFromFile("assets/bird.png");
    sprite.setTexture(tex);
    sprite.setScale(SCALING_FACTOR, SCALING_FACTOR);
    sprite.setOrigin(0, 0);
    xPos = WINDOW_WIDTH / 2 - sprite.getGlobalBounds().width / 2;
    yPos = WINDOW_HEIGHT / 2 - sprite.getGlobalBounds().height / 2;
    sprite.setPosition(xPos, yPos);
    yVel = 0.f;
    isReleased = true;
}

Bird::~Bird()
{

}

void Bird::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Bird::update(float dt)
{/*
    yVel += GRAVITY * dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isReleased)
    {
        yVel = -JUMP_FORCE;
        isReleased = false;
    }

    if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
    {
        isReleased = true;
    }

    yPos += yVel;
    sprite.setPosition(xPos, yPos);
    */
}
