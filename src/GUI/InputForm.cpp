#include "InputForm.h"

InputForm::InputForm(sf::Vector2f pos, sf::Vector2f size, std::string* ptrToString)
    : m_modifiedStringPtr(ptrToString)
{
    setColor(sf::Color(60, 60, 60));
    setSize(size);
    setPosition(pos);

    m_shape.setOutlineThickness(10);
    m_shape.setOutlineColor(sf::Color(30, 30, 30));

    m_text.setCharacterSize(32);
    m_text.setFillColor(sf::Color::Red);

    m_text.setPosition(getPosition().x - getSize().x * 0.49, getPosition().y - 32 * 4 / 5.f);
    
    setFont(holder::get().fonts.get("arial"));
}

void InputForm::handleEvents(sf::Event e, const sf::RenderWindow& window)
{
    switch (e.type) {
        case sf::Event::TextEntered:
        {
            if (m_active)
            {
                if (e.text.unicode < 128 && e.text.unicode >= 32)
                    *m_modifiedStringPtr += static_cast<char>(e.text.unicode);
                else if (e.text.unicode == 8) //Backspace
                    m_text.setString(*m_modifiedStringPtr = (*m_modifiedStringPtr).substr(0, std::max((int)(*m_modifiedStringPtr).size() - 1, 0)));

                if (m_text.getGlobalBounds().width >= 0.98 * getSize().x)
                    m_text.setString(*m_modifiedStringPtr = (*m_modifiedStringPtr).substr(0, std::max((int)(*m_modifiedStringPtr).size() - 1, 0)));
            }
        } break;
        case sf::Event::MouseButtonPressed:
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                m_active = isHovering(window);

                if (m_active)
                    setColor(sf::Color(45, 45, 45));
                else
                    setColor(sf::Color(60, 60, 60));
            }
        } break;
        default:
            break;
    }
}

void InputForm::update()
{
    m_text.setString(*m_modifiedStringPtr);
}

void InputForm::draw(sf::RenderTarget& target)
{
    target.draw(m_shape);
    target.draw(m_text);
}

void InputForm::setPosition(sf::Vector2f pos)
{
    m_shape.setPosition(pos - m_shape.getSize() / 2.f);
}

sf::Vector2f InputForm::getPosition()
{
    return m_shape.getPosition() + m_shape.getSize() / 2.f;
}

void InputForm::setSize(sf::Vector2f size)
{
    m_shape.setSize(size);
}

sf::Vector2f InputForm::getSize()
{
    return m_shape.getSize();
}

void InputForm::setText(const std::string& text)
{
    m_text.setString(text);

    m_text.setPosition(getPosition() - sf::Vector2f(m_text.getGlobalBounds().width, m_text.getGlobalBounds().height + m_text.getCharacterSize()) / 2.f);
}

void InputForm::setFont(const sf::Font& font)
{
    m_text.setFont(font);
}

void InputForm::setColor(sf::Color color)
{
    m_shape.setFillColor(color);
}

bool InputForm::isHovering(const sf::RenderWindow& window)
{
    auto pixelPos = sf::Mouse::getPosition(window);
    auto worldPos = window.mapPixelToCoords(pixelPos);
    return m_shape.getGlobalBounds().contains(worldPos.x, worldPos.y);
}