//
// Created by bgd on 20.04.2024.
//

#include "../header/Helicopter.h"
#include "../header/Math.h"

void Helicopter::update() {
    updateAltitudeData(m_updateAltitudeInterval);
    updateSpeedData(m_updateSpeedInterval);
    updateHeadingData(m_updateHeadingInterval);

    if(m_updatePositionInterval.getElapsedTime().asMilliseconds() >= m_updateInterval)
    {
        if(m_heading == m_newHeading) {
            const sf::Vector2f translation_to_point = Math::TranslatePositionToPoint((float) m_speed,
                                                                                     (float) m_heading);
            m_entity.move(translation_to_point);

            updateText(m_entity.getPosition());
        }

        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            m_headingStick.setRotation((float)m_heading - 90);
        }

        m_updatePositionInterval.restart();
    }
}