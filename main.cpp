/* CSCI 261 Final Project: Zack and Kenny Go To Space
* Author: Zachary Lee
* Section B
* Author: Kenny Pham
* Section C
*/
#include <SFML/Graphics.hpp>

#include <vector>
#include <cstring>
#include <thread>
#include <iostream>
#include <mutex>
#include <windows.h>

#include "Planet.h"
#include "functions.h"
#include "Entry.h"


int main() {
    const unsigned int WIDTH = 1000;
    const unsigned int HEIGHT = 1000;
    std::vector<Planet> planets;
    // reserve space for 500 planets to avoid copying
    planets.reserve(500);
    planets.emplace_back(Planet(10000, Vector2D(500, 500), Vector2D(-1.5, 0)));
    planets.emplace_back(Planet(1000, Vector2D(500, 200), Vector2D(13, 0)));
    planets.emplace_back(Planet(10, Vector2D(500, 170), Vector2D(20, 0)));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gravity");
    sf::View view(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));
    window.setView(view);

    // if simulation is paused
    bool paused = false;

    bool running = true;

    // if text is being entry
    bool entering = false;

    // load font and set it as the static Entry Font (dependency injection)
    sf::Font font;
    font.loadFromFile("data/arial.ttf");
    Entry::setFont(font);
    Entry entry;

    sf::Clock clock;


    extern std::mutex planets_m;
    std::thread calculateThread(forwardAll, std::ref(planets), std::ref(paused), std::ref(running));

    while (window.isOpen()) {
        // 60 fps
        if (clock.getElapsedTime().asMilliseconds() > 16) {
            clock.restart();
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::MouseButtonReleased) {
                    Vector2D position(event.mouseButton.x, event.mouseButton.y);
                    entry = Entry(Vector2D(position));
                    entering = true;
                } else if (!entering) {
                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Space) {
                            // check is space key is pressed and toggle paused
                            paused = !paused;
                        } else if (event.key.code == sf::Keyboard::Left) {
                            planets_m.lock();
                            for (Planet &planet : planets) {
                                // when gravity is all that acts on the planets,
                                // *= -1 ing their velocity makes them seem to travel back in time
                                planet.velocity *= -1;
                            }
                            planets_m.unlock();
                        } else if (event.key.code == sf::Keyboard::R) {
                            // r clears all planets
                            planets_m.lock();
                            planets.clear();
                            planets_m.unlock();
                        }
                    } else if (event.type == sf::Event::MouseWheelMoved) {
                        if (event.mouseWheel.delta < 0) {
                            view.zoom(0.9 / (event.mouseWheel.delta * -1));
                        } else if (event.mouseWheel.delta > 0) {
                            view.zoom(event.mouseWheel.delta * 1.1);
                        }
                        window.setView(view);
                    }
                } else if (entering && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
                    // go to next field
                    entry.next();
                } else if (entering && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    // exit entering
                    entering = false;
                } else if (entering && event.type == sf::Event::KeyPressed &&
                           event.key.code == sf::Keyboard::BackSpace) {
                    // remove char from entering
                    entry.removeChar();
                } else if (entering && event.type == sf::Event::TextEntered &&
                           strchr("-1234567890.", event.text.unicode)) {
                    // add char to entering
                    entry.addChar(static_cast<char>(event.text.unicode));
                }
            }

            if (entering && entry.done()) {
                if (entry.getMass() > 0) {
                    planets_m.lock();
                    planets.emplace_back(entry.getMass(), entry.getPosition(), entry.getVelocity());
                    planets_m.unlock();
                    redraw(planets, window);
                }
                entering = false;
            }

            window.clear();

            redraw(planets, window);
            if (entering) {
                entry.draw(window);
            }

            window.display();
        }
    }

    running = false;
    calculateThread.join();

    return 0;
}
