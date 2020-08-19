#include "FPSCounter.h"
#include <math.h>

FPSCounter::FPSCounter()
{
    fpsCtr.setString("FPS:");
    font.loadFromFile("assets/font.ttf");

    fpsCtr.setFont(font);
    fpsCtr.setFillColor(sf::Color::Red);
    fpsCtr.setPosition(5.f, 5.f);

    showCtr = false;
    smoothTimer = 0.f;
    fps = 0;
}

FPSCounter::~FPSCounter()
{

}

void FPSCounter::render(sf::Time dt, sf::RenderWindow& window)
{
    if (showCtr)
    {
        window.draw(fpsCtr);
    }

    fps = ceil(1.f / dt.asSeconds());
    smoothTimer += dt.asMilliseconds();

    if (smoothTimer > 500.f)
    {
        fpsCtr.setString("FPS:" + std::to_string(fps));
        smoothTimer = 0.f;
    }
}
