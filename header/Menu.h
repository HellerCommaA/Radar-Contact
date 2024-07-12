//
// Created by bgd on 09.04.2024.
//

#ifndef OOP_MENU_H
#define OOP_MENU_H

#include <SFML/Graphics.hpp>

#include <array>

#include "Window.h"

class Menu : public Window {
public:
    Menu();
private:
    void render() override;
    void handleEvent() override;
    void update() override;

    void checkHovers();

    sf::Texture m_texture;
    sf::Sprite m_background;

    sf::Text liveData, localData;

    std::array<std::pair<sf::RectangleShape, std::string>, 10> m_regionsButtons;
    std::array<sf::Texture, 10> m_flagsTexture;
    std::array<sf::Text, 10> m_flagsLabel;
};


#endif //OOP_MENU_H
