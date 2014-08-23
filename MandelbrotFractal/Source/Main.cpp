////////////////////////////////////////////////////////////////////////////////
// Filename: Main.cpp
// Author:   Tobias Savinainen
// Year:     2014
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header files
////////////////////////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include "Mandelbrot.hpp"
#include <fstream>

void reload(Mandelbrot& mandelbrot);

////////////////////////////////////////////////////////////////////////////////
// Entry point of application
////////////////////////////////////////////////////////////////////////////////
int main()
{
    sf::RenderWindow renderWindow(sf::VideoMode(1600, 900, 32), "MandelbrotFractal");
    unsigned int width  = renderWindow.getSize().x;
    unsigned int height = renderWindow.getSize().y;

    Mandelbrot mandelbrot(width, height);
    reload(mandelbrot);    

    while(renderWindow.isOpen()) 
    {
        sf::Event event;
        while(renderWindow.pollEvent(event)) 
        {
            if(event.type == sf::Event::Closed)
                renderWindow.close();
            if(event.type == sf::Event::KeyPressed) 
            {
                if(event.key.code == sf::Keyboard::Escape)
                    renderWindow.close();

                if(event.key.code == sf::Keyboard::F5)
                    reload(mandelbrot);

                if(event.key.code == sf::Keyboard::F12)
                    renderWindow.capture().saveToFile("screenshot-" + std::to_string(std::time(nullptr)) + ".png");
            }
        }

        renderWindow.clear();

        for(int i = 0; i < 1; i++)
            renderWindow.draw(mandelbrot, sf::BlendAdd);

        renderWindow.display();
    }

    return 0;
}

void reload(Mandelbrot& mandelbrot)
{
    std::ifstream input("config.txt");
    if(!input)
        return;

    int maxIterations;
    double scale;
    float x, y;
    
    input >> maxIterations;
    input >> scale;
    input >> x;
    input >> y;

    mandelbrot.setScale(scale);
    mandelbrot.setCenter({x, y});
    mandelbrot.generate(maxIterations);
}