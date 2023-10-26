#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

class Particle {
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float radius;
    float timeLeft;
    float timeStart;
    sf::Color color;

    Particle() : Particle(32, sf::Vector2f(0,0), sf::Vector2f(0,0), 1) {}

    Particle(float radius, sf::Vector2f startPos, sf::Vector2f startVelocity, float lifetime)
        : position(startPos), velocity(startVelocity), radius(radius), timeLeft(lifetime), timeStart(lifetime)
    {
        // randomize color
        color.r = std::rand() % 256;
        color.g = std::rand() % 256;
        color.b = std::rand() % 256;
    }

    sf::CircleShape getShape() {
        auto shape = sf::CircleShape(radius * (timeLeft / timeStart));
        shape.setPosition(position);
        shape.setFillColor(color);
        return shape;
    }

    void update(float delta) {
        position += velocity * delta;
        timeLeft -= delta;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(getShape());
    }

    bool isDead() {
        return timeLeft <= 0;
    }
};