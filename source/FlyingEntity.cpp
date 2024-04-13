//
// Created by bgd on 11.04.2024.
//

#include "../header/FlyingEntity.h"

#include <iostream>

FlyingEntity::FlyingEntity(int altitude, int speed, int heading, const std::string &squawk,
                           const std::string &callsign, sf::Vector2f position, ResourcesManager *resourcesManager) :
        m_heading(heading), m_speed(speed), m_altitude(altitude), m_squawk{squawk},
        m_callsign(callsign), m_entitySelected{false}
{

    m_entity.setSize(sf::Vector2f(10, 10));
    m_entity.setFillColor(sf::Color::White);

    sf::FloatRect entity_bounds = m_entity.getGlobalBounds();
    m_entity.setOrigin(sf::Vector2f(entity_bounds.left + 5, entity_bounds.top + 5)); // pun originea in mijloc

    m_entity.setPosition(position);
}

void FlyingEntity::update()
{
    if(m_updatePositionInterval.getElapsedTime().asMilliseconds() >= m_updateInterval)
    {
        const sf::Vector2f translation_to_point = Math::TranslatePositionToPoint((float) m_speed, (float) m_heading);
        m_entity.move(translation_to_point);

        //sf::Vector2f pos = m_entity.getPosition();

        m_updatePositionInterval.restart();
    }
}

void FlyingEntity::render(sf::RenderWindow *game_window)
{
    game_window->draw(m_entity);

    if(m_entitySelected)
    {

    }
}

void FlyingEntity::handleEvent(const sf::Event game_event, const sf::Vector2f mouse_position)
{
    switch(game_event.type)
    {
        case sf::Event::MouseButtonPressed:
        {
            sf::FloatRect entity_bounds = m_entity.getGlobalBounds();

            if(entity_bounds.contains(mouse_position))
            {
                m_entitySelected = true;
            }
            else
            {
                m_entitySelected = false;
            }
        }

        default:
            break;
    }
}