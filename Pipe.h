#ifndef PIPE_H
#define PIPE_H

#include <SFML/Graphics.hpp>

class Pipe
{
public:
    Pipe();
    ~Pipe();

    void update(float dt);
    void render(sf::RenderWindow& window);

    static sf::Texture bottomTex;
    static sf::Texture topTex;
    sf::Sprite topSprite;
    sf::Sprite bottomSprite;

    float topX;
    float topY;
    float topWidth;
    float topHeight;

    float bottomX;
    float bottomY;
    float bottomWidth;
    float bottomHeight;

    float xOffset;

};

#endif
