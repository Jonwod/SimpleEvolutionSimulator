//
//  main.cpp
//  Evolve
//
//  Created by Jonathan Wood on 07/10/2016.
//  Copyright © 2016 Jonathan Wood. All rights reserved.
//

#include <iostream>
#include<SFML/Graphics.hpp>
#include "World.hpp"

void updateCamera(float dt, sf::View & view, sf::RenderWindow & window){
    const static float scrollRate = 200.0f;
    const static float zoomRate = 0.2f;
    const float zoom = view.getSize().x / window.getSize().x;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        view.move(0, -scrollRate*zoom*dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        view.move(0, scrollRate*zoom*dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        view.move(scrollRate*zoom*dt, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        view.move(-scrollRate*zoom*dt, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        view.zoom((1-zoomRate*dt));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        view.zoom(1+zoomRate*dt);
    
    window.setView(view);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    sf::ContextSettings contextSettings( 0, 0, 1) ;
    
    sf::RenderWindow window(sf::VideoMode(1280, 768, 32), "Simple Evolution Simulator", sf::Style::Default, contextSettings);
    
    window.setFramerateLimit(60);
    
    sf::Clock framerateClock;
    sf::Time deltaT = sf::seconds(1.0f / 60.0f);
    
    sf::View view;
    view.reset(sf::FloatRect(0, 0, 1280, 768));
    view.setViewport(sf::FloatRect(0,0 ,1.0f, 1.0f));
    
    window.setView(view);
    
    view.zoom(1.0f);
    
    
    while(window.isOpen()){
        sf::Event Event;
        while(window.pollEvent(Event)){
            switch (Event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }
        updateCamera(deltaT.asSeconds(), view, window);
        World::get().update(deltaT.asSeconds());
        World::get().draw(window);
        window.display();
        window.clear(sf::Color(255, 255, 255, 0));
        deltaT = framerateClock.restart();
    }
        
    return 0;
}
