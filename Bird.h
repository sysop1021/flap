#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>

class Bird
{
public:
    Bird();
    ~Bird();

    void render(sf::RenderWindow& window);
    void update(float dt);

    sf::Texture tex;
    sf::Sprite sprite;
    float xPos, yPos, yVel, width, height;
    bool isReleased;

private:

};

#endif
