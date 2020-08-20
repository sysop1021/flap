#include "Pipe.h"
#include "constants.h"

sf::Texture Pipe::tex;

Pipe::Pipe(bool isTop)
{
    sprite.setTexture(tex);
    sprite.setScale(SCALING_FACTOR, SCALING_FACTOR);
    sprite.setOrigin(0.f, 0.f);
    width = sprite.getGlobalBounds().width;
    height = sprite.getGlobalBounds().height;



    if (isTop)
    {
        sprite.setRotation(180);
        x = WINDOW_WIDTH + width;
        y = (WINDOW_HEIGHT / 4);

    }

    else
    {
        //y = rand() % (((WINDOW_HEIGHT - 10) - (WINDOW_HEIGHT / 4) + 1) + (WINDOW_HEIGHT / 4));
        x = WINDOW_WIDTH;
        y = 3 * (WINDOW_HEIGHT / 4);

    }

    sprite.setPosition(x, y);
}

Pipe::~Pipe()
{

}

void Pipe::update(float dt)
{
    x -= FOREGROUND_SCROLL_SPEED * dt;
    sprite.setPosition(x, y);
}

void Pipe::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}
