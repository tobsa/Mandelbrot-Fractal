////////////////////////////////////////////////////////////////////////////////
// Filename: Mandelbrot.cpp
// Author:   Tobias Savinainen
// Year:     2014
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header files
////////////////////////////////////////////////////////////////////////////////
#include "Mandelbrot.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <functional>
#include <thread>
#include <SFML/System/Clock.hpp>

Mandelbrot::Mandelbrot(unsigned int width, unsigned int height) :
    m_minReal (-2.5),
    m_maxReal (1.0),
    m_minImag (-1.0),
    m_maxImag (1.0),
    
    m_width (width),
    m_height (height)
{
    m_texture.create(width, height);
    m_sprite.setTexture(m_texture);

    m_pixels = new sf::Uint8[m_width * m_height * 4];

}

void Mandelbrot::generate(int maxIterations, unsigned int ty, unsigned int height)
{
    double real = (m_maxReal - m_minReal) / m_width;
    double imag = (m_maxImag - m_minImag) / m_height;

    for(unsigned int x = 0; x < m_width; x++)
    {
        for(unsigned int y = ty; y < height; y++)
        {
            double cx = m_minReal + x * real + m_center.x * real; 
            double cy = m_maxImag - y * imag - m_center.y * imag;

            double zx = cx;
            double zy = cy;

            int iteration = 0;

            while(zx*zx + zy*zy < 4 && iteration < maxIterations)
            {
                double tempX = zx*zx - zy*zy + cx;
                double tempY = 2 * zx * zy + cy;

                if(zx == tempX && zy == tempY) {
                    iteration = maxIterations;
                    break;
                }

                zx = tempX;
                zy = tempY;

                iteration++;
            }

            if(iteration == maxIterations)
                plot(x, y, sf::Color::Black);
            else 
            {
                sf::Color color;

                if (iteration == maxIterations) {
                  color = sf::Color(0, 0, 0);
                } else if (iteration < 64) {
                  color = sf::Color(iteration * 2, 0, 0);
                } else if (iteration < 128) {
                  color = sf::Color((((iteration - 64) * 128) / 126) + 128, 0, 0);
                } else if (iteration < 256) {
                  color = sf::Color((((iteration - 128) * 62) / 127) + 193, 0, 0); 
                } else if (iteration < 512) {
                  color = sf::Color(255, (((iteration - 256) * 62) / 255) + 1, 0);
                } else if (iteration < 1024) {
                  color = sf::Color(255, (((iteration - 512) * 63) / 511) + 64, 0);
                } else if (iteration < 2048) {
                  color = sf::Color(255, (((iteration - 1024) * 63) / 1023) + 128, 0);
                } else if (iteration < 4096) {
                  color = sf::Color(255, (((iteration - 2048) * 63) / 2047) + 192, 0);
                } else {
                  color = sf::Color(iteration, iteration, 0);
                }

                plot(x, y, color);
            }
        }
    }

    m_texture.update(m_pixels);
}

void Mandelbrot::generate(int maxIterations)
{    
    int step = m_height / 5;

    std::vector<std::thread> threads;
    for(unsigned int i = 0; i < m_height; i += step)
        threads.push_back(std::thread([=](){generate(maxIterations, i, i + step);}));

    for(auto& thread : threads)
        thread.join();
}

void Mandelbrot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

void Mandelbrot::plot(int x, int y, const sf::Color& color)
{
    m_pixels[(x + y * m_width) * 4 + 0] = color.r;
    m_pixels[(x + y * m_width) * 4 + 1] = color.g;
    m_pixels[(x + y * m_width) * 4 + 2] = color.b;
    m_pixels[(x + y * m_width) * 4 + 3] = color.a;
}

void Mandelbrot::setCenter(const sf::Vector2f& center)
{
    m_center = center;
}

void Mandelbrot::setScale(double scale)
{
    m_minReal = -2.5;
    m_maxReal = 1.0;
    m_minImag = -1.0;
    m_maxImag = 1.0;

    m_minReal *= scale;
    m_maxReal *= scale;
    m_minImag *= scale;
    m_maxImag *= scale;
}