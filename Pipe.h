#ifndef PIPE_H
#define PIPE_H

#include <SFML/Graphics.hpp>
#include "constants.h"

class Pipe
{
public:
    Pipe();
    ~Pipe();

    void update(float dt);
    void render(sf::RenderWindow& window);

    sf::Texture tex;
    sf::Sprite sprite;

    float x;
    float y;
    float width;

};

#endif
