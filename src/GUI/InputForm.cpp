#include "InputForm.h"

#include <iostream>

InputForm::InputForm(sf::Vector2f pos, sf::Vector2f size, std::string* ptrToString) :
    m_modifiedStringPtr(ptrToString),
    m_active(false),
    m_selected(false)
{
    setColor(sf::Color(60, 60, 60));
    setSize(size);
    setPosition(pos);

    m_shape.setOutlineThickness(10);
    m_shape.setOutlineColor(sf::Color(30, 30, 30));

    m_text.setCharacterSize(32);
    m_text.setFillColor(sf::Color::Red);
    m_text.setString(*m_modifiedStringPtr);

    m_text.setPosition(getPosition().x - getSize().x * 0.48, getPosition().y - m_text.getCharacterSize() * 4 / 5.f);

    m_select.setFillColor(sf::Color::Black);
    
    setFont(holder::get().fonts.get("arial"));

    m_underline.setFont(holder::get().fonts.get("arial"));

    m_underline.setCharacterSize(32);
}

void InputForm::handleEvents(sf::Event e, const sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_selected = false;

    switch (e.type) {
        case sf::Event::TextEntered:
        {
            if (m_active)
            {
                if (e.text.unicode < 128 && e.text.unicode >= 32)
                {
                    if (m_selected)
                        *m_modifiedStringPtr = static_cast<char>(e.text.unicode);
                    else
                        *m_modifiedStringPtr += static_cast<char>(e.text.unicode);

                    m_selected = false;
                }
                else if (e.text.unicode == 8) //Backspace
                {
                    if (m_selected)
                        *m_modifiedStringPtr = "";
                    else
                        m_text.setString(*m_modifiedStringPtr = (*m_modifiedStringPtr).substr(0, std::max((int)(*m_modifiedStringPtr).size() - 1, 0)));

                    m_selected = false;
                }
                else if (e.text.unicode == 1) //ctrl+A
                {
                    m_selected = true;
                    m_select.setPosition(m_text.getPosition());
                    m_select.setSize(sf::Vector2f(m_text.getGlobalBounds().width, m_text.getGlobalBounds().height * 3.f));
                }
                else if (e.text.unicode == 3 && m_selected) //ctrl+C
                    toClipboard(*m_modifiedStringPtr);

                m_text.setString(*m_modifiedStringPtr);

                if (m_text.getGlobalBounds().width >= 0.96 * getSize().x)
                {
                    m_text.setString(*m_modifiedStringPtr = (*m_modifiedStringPtr).substr(0, std::max((int)(*m_modifiedStringPtr).size() - 1, 0)));
                    m_text.setString(*m_modifiedStringPtr);
                }
            }
        } break;
        case sf::Event::MouseButtonPressed:
        {
            m_selected = false;

            if (e.mouseButton.button == sf::Mouse::Left)
            {
                m_underline.setString("");

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

void InputForm::update(const sf::Time& deltaTime)
{
    m_underline.setPosition(m_text.getPosition().x + m_text.getGlobalBounds().width, m_text.getPosition().y);

    if (m_clock.getElapsedTime().asSeconds() >= 1 && m_active)
    {
        if (m_underline.getString().getSize() != 0)
            m_underline.setString("");
        else
            m_underline.setString("_");

        m_clock.restart();
    }
}

void InputForm::draw(sf::RenderTarget& target)
{
    target.draw(m_shape);

    if (m_selected)
        target.draw(m_select);

    target.draw(m_text);

    target.draw(m_underline);
}

void InputForm::setPosition(sf::Vector2f pos)
{
    m_shape.setPosition(pos - m_shape.getSize() / 2.f);

    m_text.setPosition(getPosition().x - getSize().x * 0.48, getPosition().y - m_text.getCharacterSize() * 4 / 5.f);
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

void InputForm::toClipboard(const std::string& s) {
    OpenClipboard(0);
    EmptyClipboard();
    HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size());
    if (!hg) {
        CloseClipboard();
        return;
    }
    memcpy(GlobalLock(hg), s.c_str(), s.size());
    GlobalUnlock(hg);
    SetClipboardData(CF_TEXT, hg);
    CloseClipboard();
    GlobalFree(hg);
}