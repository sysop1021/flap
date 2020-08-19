#ifndef PIPE_H
#define PIPE_H

#include <SFML/Graphics.hpp>

class Pipe
{
public:
    Pipe(bool isTop);
    ~Pipe();

    void update(float dt);
    void render(sf::RenderWindow& window);

    sf::Texture tex;
    sf::Sprite sprite;

    float x;
    float y;
    float width;
    float height;

};

#endif
