#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 768),
                            "Shader Smaple",
                            sf::Style::Titlebar | sf::Style::Close);

    int shaderIndex                      = 0;

    std::vector<std::string> shaderNames = {"shader_fade.frag",
                                            "shader_red.frag",
                                            "shader_shake.frag",
                                            "shader_breathe.frag"};

    std::vector<sf::Shader> shaders(shaderNames.size());

    for (int i = 0; i < shaderNames.size(); i++)
    {
        std::string name = shaderNames[i];
        shaders[i].loadFromFile("resources/shader/" + name, sf::Shader::Fragment);
    }

    sf::Texture texture;
    texture.create(window.getSize().x, window.getSize().y);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    sprite.setScale(sf::Vector2f(0.1f, 0.1f));

    // create texture from PNG file
    sf::Texture sampleTexture;
    if (!sampleTexture.loadFromFile("resources/shader/icon-small.png"))
    {
        throw std::runtime_error("Error while loading texture");
    }

    sf::Font font;
    font.loadFromFile("resources/font/Roboto-Light.ttf");

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(sf::Vector2f(10.0, 10.0));

    sf::Clock time;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                    }
                    else if (event.key.code == sf::Keyboard::Enter)
                    {
                        shaderIndex = (shaderIndex + 1) % (int)shaders.size();
                    }
                    else if (event.key.code == sf::Keyboard::Space)
                    {
                        shaderIndex =
                            shaderIndex - 1
                            + shaders.size() * ((shaders.size() - shaderIndex) / shaders.size());
                    }
            }
        }

        texture.update(window);

        shaders[shaderIndex].setUniform("time", time.getElapsedTime().asSeconds());
        shaders[shaderIndex].setUniform("currentTexture", sampleTexture);

        text.setString(std::to_string(shaderIndex) + " " + shaderNames[shaderIndex]);

        window.clear();

        // Draw the sprite and apply shader
        window.draw(sprite, &shaders[shaderIndex]);
        window.draw(text);

        window.display();
    }

    return 0;
}
