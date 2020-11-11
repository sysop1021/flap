#include "Pipe.h"
#include "constants.h"

// must initialize static texture here and perform load in main()
sf::Texture Pipe::bottomTex;
sf::Texture Pipe::topTex;

Pipe::Pipe()
{
    xOffset = 0; //rand() % 200 + 50; // TODO: tune this value for proc gen of pipes

    isScored = false;

    topSprite.setTexture(topTex);
    topSprite.setScale(SCALING_FACTOR, SCALING_FACTOR);
    topWidth = topSprite.getGlobalBounds().width;
    topHeight = topSprite.getGlobalBounds().height;
    topSprite.setOrigin(0, 0);
    topX = WINDOW_WIDTH + xOffset;
    topY = (WINDOW_HEIGHT / 5) - topHeight;
    topY = (WINDOW_HEIGHT / 5) - topHeight + rand() % 150;
    topSprite.setPosition(topX, topY);

    bottomSprite.setTexture(bottomTex);
    bottomSprite.setScale(SCALING_FACTOR, SCALING_FACTOR);
    bottomSprite.setOrigin(0.f, 0.f);
    bottomWidth = bottomSprite.getGlobalBounds().width;
    bottomHeight = bottomSprite.getGlobalBounds().height;
    bottomX = WINDOW_WIDTH + xOffset;
    bottomY = 4 * (WINDOW_HEIGHT / 5) - rand() % 150;
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
