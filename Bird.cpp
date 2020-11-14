#include "Bird.h"
#include "constants.h"
#define GRAVITY_ON

Bird::Bird()
{
    tex.loadFromFile("assets/bird.png");
    sprite.setTexture(tex);
    sprite.setScale(SCALING_FACTOR, SCALING_FACTOR);
    sprite.setOrigin(0, 0);
    width = sprite.getGlobalBounds().width;
    height = sprite.getGlobalBounds().height;
    resetPos();
    isReleased = true;

    jumpBuffer.loadFromFile("assets/jump.wav");
    hurtBuffer.loadFromFile("assets/hurt.wav");
    splodeBuffer.loadFromFile("assets/explosion.wav");

    jump.setBuffer(jumpBuffer);
    hurt.setBuffer(hurtBuffer);
    splode.setBuffer(splodeBuffer);
}

Bird::~Bird()
{

}

void Bird::resetPos()
{
    yVel = 0.f;
    xPos = WINDOW_WIDTH / 2 - width / 2;
    yPos = WINDOW_HEIGHT / 2 - height / 2;
    sprite.setPosition(xPos, yPos);
}

void Bird::render(sf::RenderWindow &window)
{
    window.draw(sprite);
}

bool Bird::checkCollision(Pipe& pipe)
{
    // TODO: don't really like this - i need to factor out Pipe/pipes to a PipePair that has 2 Pipes.

    if ( !(xPos + 4 > (pipe.topX + pipe.topWidth)) &&
         !((xPos + width - 4) < pipe.topX) &&
         !(yPos + 3 > (pipe.topY + pipe.topHeight)) &&
         !((yPos + height - 3) < pipe.topY) )
    {
        hurt.play();
        splode.play();
        return true;
    }

    else if ( !(xPos + 4 > (pipe.bottomX + pipe.bottomWidth)) &&
              !((xPos + width - 4) < pipe.bottomX) &&
              !(yPos + 3 > (pipe.bottomY + pipe.bottomHeight)) &&
              !((yPos + height - 3) < pipe.bottomY) )
    {
        hurt.play();
        splode.play();
        return true;
    }

    else
    {
        return false;
    }
}

void Bird::update(float dt)
{
#ifdef GRAVITY_ON
    yVel += GRAVITY * dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isReleased)
    {
        yVel = -JUMP_FORCE;
        isReleased = false;
        jump.play();
    }

    if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
    {
        isReleased = true;
    }

    yPos += yVel;
    sprite.setPosition(xPos, yPos);
#endif
}
