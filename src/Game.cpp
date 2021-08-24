#include "Game.h"

Game::Game(std::string&& name, unsigned int width, unsigned int height)
	: m_window({ width, height }, std::move(name))
{
    pushState(std::unique_ptr<MenuState>(new MenuState(*this)));
}

int Game::run()
{
    //Time variables
    const unsigned TICKS_PER_SEC = 30;
    const sf::Time TIME_PER_UPDATE = sf::seconds(1.0f / static_cast<float>(TICKS_PER_SEC));
    unsigned ticks = 0;

    sf::Clock timer;
    sf::Clock dt;
    auto lastTime = sf::Time::Zero;
    auto lag = sf::Time::Zero;

    m_window.setFramerateLimit(60);

    //Main loop of the game
    while (m_window.isOpen() && m_states.size() > 0) 
    {
        if (m_states.size() > 0)
        {
            handleEvent();

            //Calculate time
            auto time = timer.getElapsedTime();
            auto elapsed = time - lastTime;
            lastTime = time;

            try
            {
                BaseState& currentState = getCurrentState();
                currentState.update(elapsed);

                //Render
                m_window.clear();

                currentState.draw(m_window);

                m_window.display();
            }
            catch (std::exception& e)
            {
                m_window.close();
            }
        }
    }

    return 0;
}

const sf::RenderWindow& Game::getWindow() const
{
	return this->m_window;
}

void Game::handleEvent()
{
    sf::Event e = sf::Event();

    while (m_window.pollEvent(e)) 
    {
        getCurrentState().handleEvents(e, m_window);

        switch (e.type) 
        {
            case sf::Event::Closed:
            {
                m_window.close();
            } break;
            default:
                break;
        }
    }
}

void Game::pushState(std::unique_ptr<BaseState> _ptr)
{
    m_states.push_back(std::move(_ptr));
}

void Game::popAndPushState(std::unique_ptr<BaseState> _ptr)
{
    m_states.pop_back();
    m_states.push_back(std::move(_ptr));
}

void Game::popAndPushAllStates(std::unique_ptr<BaseState> _ptr)
{
    m_states.clear();
    m_states.push_back(std::move(_ptr));
}

void Game::popState()
{
    m_states.pop_back();
}

BaseState& Game::getCurrentState()
{
    if (m_states.size() == 0)
        throw std::exception();
    return *m_states.back();
}