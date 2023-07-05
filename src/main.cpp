#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main()
{
    std::vector<std::string> shaderFiles = {"resources/shader/shader_fade.frag",
                                            "resources/shader/shader_red.frag",
                                            "resources/shader/shader_shake.frag",
                                            "resources/shader/shader_breathe.frag"};

    size_t currentShaderIndex = 0;

    sf::RenderWindow window(sf::VideoMode(256, 256),
                            "Shader Sample",
                            sf::Style::Titlebar | sf::Style::Close);

    // create a window size texture and a sprite for the shader
    sf::Texture tex;
    tex.create(256, 256);
    sf::Sprite spr(tex);

    // enable vertical sync. (vsync)
    window.setVerticalSyncEnabled(true);

    // create texture from PNG file
    sf::Texture texture;
    if (!texture.loadFromFile("resources/shader/icon-small.png"))
    {
        std::cerr << "Error while loading texture" << std::endl;
        return -1;
    }
    // enable the smooth filter. the texture appears smoother so that pixels are less noticeable
    texture.setSmooth(true);

    // create the sprite and apply the texture
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sf::FloatRect spriteSize = sprite.getGlobalBounds();

    // set origin in the middle of the sprite
    sprite.setOrigin(spriteSize.width / 2, spriteSize.height / 2);
    sprite.setScale(4.0, 4.0);

    if (!sf::Shader::isAvailable())
    {
        std::cerr << "Shader are not available" << std::endl;
        return -1;
    }

    // load shader
    sf::Shader shader;
    if (!shader.loadFromFile(shaderFiles[currentShaderIndex], sf::Shader::Fragment))
    {
        std::cerr << "Error while shaders" << std::endl;
        return -1;
    }

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
                    else
                    {
                        currentShaderIndex = (currentShaderIndex + 1) % shaderFiles.size();
                        if (!shader.loadFromFile(shaderFiles[currentShaderIndex],
                                                 sf::Shader::Fragment))
                        {
                            std::cerr << "Error while shaders" << std::endl;
                            return -1;
                        }
                    }
            }
        }

        // set shader parameters
        shader.setUniform("time", time.getElapsedTime().asSeconds());

        // clear the window and apply grey background
        window.clear(sf::Color(127, 127, 127));

        // Draw the sprite and apply shader
        sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
        window.draw(sprite, &shader);

        window.display();
    }

    return 0;
}
