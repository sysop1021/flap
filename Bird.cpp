#include "Bird.h"
#include "constants.h"

Bird::Bird()
{
    tex.loadFromFile("assets/bird.png");
    sprite.setTexture(tex);
    sprite.setScale(SCALING_FACTOR, SCALING_FACTOR);
    sprite.setOrigin(0, 0);
    sprite.setPosition(WINDOW_WIDTH / 2 - sprite.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 - sprite.getGlobalBounds().height / 2);
}

Bird::~Bird()
{

}

void Bird::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}
