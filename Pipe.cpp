#include "Pipe.h"
#include "constants.h"

// must initialize static texture here and perform load in main()
sf::Texture Pipe::tex;

Pipe::Pipe()
{
    xOffset = rand() % 200 + 50; // TODO: tune this value for proc gen of pipes

    topSprite.setTexture(tex);
    topSprite.setScale(SCALING_FACTOR, SCALING_FACTOR);
    topSprite.setOrigin(0.f, 0.f);
    topWidth = topSprite.getGlobalBounds().width;
    topHeight = topSprite.getGlobalBounds().height;
    topSprite.setRotation(180);
    topX = WINDOW_WIDTH + topWidth + xOffset;
    topY = (WINDOW_HEIGHT / 4) - rand() % 50;                             // TODO: minus some rand
    topSprite.setPosition(topX, topY);

    bottomSprite.setTexture(tex);
    bottomSprite.setScale(SCALING_FACTOR, SCALING_FACTOR);
    bottomSprite.setOrigin(0.f, 0.f);
    bottomWidth = bottomSprite.getGlobalBounds().width;
    bottomHeight = bottomSprite.getGlobalBounds().height;
    bottomX = WINDOW_WIDTH + xOffset;
    bottomY = 3 * (WINDOW_HEIGHT / 4) + rand() % 50;                      // TODO: plus some rand
    bottomSprite.setPosition(bottomX, bottomY);
}

Pipe::~Pipe()
{

}

void Pipe::update(float dt)
{
    topX -= FOREGROUND_SCROLL_SPEED * dt;
    topSprite.setPosition(topX, topY);
    bottomX -= FOREGROUND_SCROLL_SPEED * dt;
    bottomSprite.setPosition(bottomX, bottomY);
}

void Pipe::render(sf::RenderWindow& window)
{
    window.draw(topSprite);
    window.draw(bottomSprite);
}
