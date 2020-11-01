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

void Bird::render(sf::RenderWindow &window)
{
    window.draw(sprite);
}

bool Bird::checkCollision(Pipe& pipe)
{
    // TODO: don't really like this - i need to factor out Pipe/pipes to a PipePair that has 2 Pipes.

   if ( !(xPos > (pipe.topX + pipe.topSprite.getGlobalBounds().width)) &&
        !((xPos + sprite.getGlobalBounds().width) < pipe.topX) &&
        !(yPos > (pipe.topY + pipe.topSprite.getGlobalBounds().height)) &&
        !((yPos + sprite.getGlobalBounds().height) < pipe.topY) )
    {
        return true;
    }

    else if ( !(xPos > (pipe.bottomX + pipe.bottomSprite.getGlobalBounds().width)) &&
              !((xPos + sprite.getGlobalBounds().width) < pipe.bottomX) &&
              !(yPos > (pipe.bottomY + pipe.bottomSprite.getGlobalBounds().height)) &&
              !((yPos + sprite.getGlobalBounds().height) < pipe.bottomY) )
    {
        return true;
    }

    else
    {
        return false;
    }
}

void Bird::update(float dt)
{
    // Commented out just for pipe debugging

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

}
