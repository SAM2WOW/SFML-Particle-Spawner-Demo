#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include "Particle.h"

class Spawner {
public:
    float PI = 3.1415926;

    int maxParticles;
    std::vector<Particle> particles;

    float timeLeft;

    Spawner() {}

    Spawner(sf::Vector2f position, int amount, int maxSpeed, int maxSize, int maxLifetime) {
        maxParticles = amount;
        particles.reserve(maxParticles);

        for (int i = 0; i < maxParticles; i++) {
            float randomSpeed = float(abs(rand()) % (maxSpeed + 1));
            float randomAngleDegrees = float(abs(rand()) % 360);
            float randomAngleRadius = randomAngleDegrees * PI / 180.f;
            auto randomDirection = sf::Vector2f(cos(randomAngleRadius), sin(randomAngleRadius));
            auto randomVelocity = randomDirection * randomSpeed;

            float randomSize = float(abs(rand()) % (maxSize + 1));
            float randomLifetime = float(abs(rand()) % (maxLifetime * 100 + 1)) / 100.f;

            auto newParticle = Particle(randomSize, position, randomVelocity, randomLifetime);
            particles.push_back(newParticle);

            timeLeft = maxLifetime;
        }
    }

    ~Spawner() {
        particles.clear();
    }

    void update(float delta) {
        // Clean bad particles
        for (int i = particles.size()-1; i >= 0; i--) {
            auto curPart = particles[i];
            if (curPart.isDead()) {
                particles.erase(particles.begin() + i);
            }
        }
        
        for (int i = 0; i < particles.size(); i++) {
            particles[i].update(delta);
        }

        timeLeft -= delta;
    }

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < particles.size(); i++) {
            particles[i].draw(window);
        }
    }

    bool isDead() {
        return timeLeft <= 0;
    }
};