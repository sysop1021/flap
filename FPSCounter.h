#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <SFML/Graphics.hpp>

class FPSCounter
{
public:

    sf::Text fpsCtr;

    bool showCtr;
    float smoothTimer;
    sf::Font font;
    int fps;

    FPSCounter();
    ~FPSCounter();
    void render(sf::Time dt, sf::RenderWindow& window);
};

#endif
