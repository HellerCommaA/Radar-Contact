//
// Created by bgd on 09.04.2024.
//

#include "../header/Menu.h"
#include "../header/Game.h"
#include "../header/StateMachine.h"

Menu::Menu() : Window({512, 512}, "Radar Contact - Menu")
{
    const std::vector<std::string> flags = {"Poland", "Iceland", "Cyprus", "Austria", "Turkey",
                                            "UK", "Denmark"};

    sf::RectangleShape button{sf::Vector2f(50,30)};
    button.setOutlineThickness(2.3f);


    for(int i = 0; i < (int) flags.size(); i++) {
        sf::Texture texture;
        if(!texture.loadFromFile("./resources/flags/" + flags[i] + ".png"))
            std::cout << "fail\n";

        sf::Text text(flags[i], ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 12);

        if(i <= 4) {
            button.setPosition(50 + 95 * (float) i, 140);
            text.setPosition(50 + 95 * (float) i, 170);
        }
        else if (i <= 9) {
            button.setPosition(50 + 95 * (float) (i % 5), 220);
            text.setPosition(50 + 95 * (float) (i % 5), 250);
        }

        m_flagsTexture[i] = (texture);
        button.setTexture(&m_flagsTexture[i]);

        m_regionsButtons[i] = std::make_pair<>(button, flags[i]);
        m_flagsLabel[i] = text;
    }

    m_background.setTexture(ResourcesManager::Instance().getTexture("menu.png"));


    liveData.setFont(ResourcesManager::Instance().getFont("Poppins-Regular.ttf"));
    localData.setFont(ResourcesManager::Instance().getFont("Poppins-Regular.ttf"));

    liveData.setString("Live Data");
    localData.setString("Offline");

    liveData.setPosition(20, 485);
    localData.setPosition(85, 485);

    liveData.setCharacterSize(13);
    localData.setCharacterSize(13);
}

void Menu::render()
{
    m_window.clear();

    m_window.draw(m_background);

    for(auto &regionsButton: m_regionsButtons) {
        m_window.draw(regionsButton.first);
    }
    for(auto &label: m_flagsLabel) {
        m_window.draw(label);
    }

    m_window.draw(liveData);
    m_window.draw(localData);

    m_window.display();
}

void Menu::update()
{
    if(ResourcesManager::Instance().isMockingEnabled()) {
        liveData.setFillColor(sf::Color(209, 206, 199, 100));
        localData.setFillColor(sf::Color::Green);
    }
    else {
        localData.setFillColor(sf::Color(209, 206, 199, 100));
        liveData.setFillColor(sf::Color::Green);
    }

    checkHovers();
}

void Menu::checkHovers()
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(m_window);
    sf::Vector2f float_mouse_position{(float) mouse_position.x, (float) mouse_position.y};

    for(auto &regionsButton: m_regionsButtons) {
        if(regionsButton.first.getGlobalBounds().contains(float_mouse_position)) {
            regionsButton.first.setOutlineColor(sf::Color::White);
        }
        else {
            regionsButton.first.setOutlineColor(sf::Color::Transparent);
        }
    }
}

void Menu::handleEvent()
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(m_window);
    sf::Vector2f float_mouse_position{(float) mouse_position.x, (float) mouse_position.y};
    sf::Event menu_event{};

    while(m_window.pollEvent(menu_event))
    {
        switch(menu_event.type)
        {
            case sf::Event::Closed: {
                m_window.close();

                break;
            }
            case sf::Event::KeyPressed:
            {
                const sf::Keyboard::Key key_code = menu_event.key.code;

                if(key_code == sf::Keyboard::Escape)
                {
                    m_window.close();
                }

                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                for(const auto &regionButtons: m_regionsButtons) {
                    if(regionButtons.first.getGlobalBounds().contains(float_mouse_position)) {
                        ResourcesManager::Instance().loadRegion(regionButtons.second);
                        std::shared_ptr<Window> game = std::make_shared<Game>();
                        StateMachine::Instance().pushState(game);

                        m_window.close();
                    }
                }

                if(liveData.getGlobalBounds().contains(float_mouse_position)) {
                    ResourcesManager::Instance().setMocking(false);
                }
                else if(localData.getGlobalBounds().contains(float_mouse_position)) {
                    ResourcesManager::Instance().setMocking(true);
                }

                break;
            }

            default:
                break;
        }
    }
}