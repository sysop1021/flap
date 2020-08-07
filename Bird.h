#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>

class Bird
{
public:
    Bird();
    ~Bird();

    void render(sf::RenderWindow& window);

    sf::Texture tex;
    sf::Sprite sprite;
    float xPos, yPos, width, height;

private:

};

#endif
