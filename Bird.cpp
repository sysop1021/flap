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

    if ( !(xPos + 4 > (pipe.topX + pipe.topWidth)) &&
         !((xPos + sprite.getGlobalBounds().width - 4) < pipe.topX) &&
         !(yPos + 3 > (pipe.topY + pipe.topHeight)) &&
         !((yPos + sprite.getGlobalBounds().height - 3) < pipe.topY) )
    {
        return true;
    }

    else if ( !(xPos + 4 > (pipe.bottomX + pipe.bottomWidth)) &&
              !((xPos + sprite.getGlobalBounds().width - 4) < pipe.bottomX) &&
              !(yPos + 3 > (pipe.bottomY + pipe.bottomHeight)) &&
              !((yPos + sprite.getGlobalBounds().height - 3) < pipe.bottomY) )
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
    /*
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
