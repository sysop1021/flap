#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

    sf::SoundBuffer jumpBuffer;
    sf::SoundBuffer hurtBuffer;
    sf::SoundBuffer splodeBuffer;

    sf::Sound jump;
    sf::Sound hurt;
    sf::Sound splode;


private:

};

#endif
