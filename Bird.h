#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>
#include "Pipe.h"

class Bird
{
public:
    Bird();
    ~Bird();

    void render(sf::RenderWindow& window);
    void update(float dt);
    void resetPos();

    sf::Texture tex;
    sf::Sprite sprite;
    float xPos, yPos, yVel, width, height;
    bool isReleased;
    bool checkCollision(Pipe& pipe);

private:

};

#endif
