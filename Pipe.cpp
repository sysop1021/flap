#include "Pipe.h"
#include "constants.h"

Pipe::Pipe()
{
    // TODO: MB: make this static so we only ever have one copy in mem
    tex.loadFromFile("assets/pipe.png");
    sprite.setTexture(tex);
    sprite.setScale(SCALING_FACTOR, SCALING_FACTOR);
    sprite.setOrigin(0.f, 0.f);

    x = WINDOW_WIDTH;
    y = rand() % (((WINDOW_HEIGHT - 10) - (WINDOW_HEIGHT / 4) + 1) + (WINDOW_HEIGHT / 4));
    width = sprite.getGlobalBounds().width;

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
