////////////////////////////////////////////////////////////////////////////////
// Filename: Mandelbrot.hpp
// Author:   Tobias Savinainen
// Year:     2014
////////////////////////////////////////////////////////////////////////////////
#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

////////////////////////////////////////////////////////////////////////////////
// Header files
////////////////////////////////////////////////////////////////////////////////
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Mandelbrot : public sf::Drawable
{
public:

    Mandelbrot(unsigned int width, unsigned int height);

    void generate(int maxIterations);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setCenter(const sf::Vector2f& center);
    void setScale(double scale);

private:

    void plot(int x, int y, const sf::Color& color);
    void generate(int maxIterations, unsigned int y, unsigned int height);

private:

    sf::Uint8* m_pixels;

    sf::Texture m_texture;
    sf::Sprite  m_sprite;

    unsigned int m_width;
    unsigned int m_height;

    sf::Vector2f m_center;

    double m_minReal;
    double m_maxReal;
    double m_minImag;
    double m_maxImag;
};

#endif