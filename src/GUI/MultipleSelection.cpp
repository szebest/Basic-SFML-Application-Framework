#include "MultipleSelection.h"

MultipleSelection::MultipleSelection()
{
	
}

void MultipleSelection::handleEvents(sf::Event e, const sf::RenderWindow& window)
{
	for (auto& selection : m_selections)
		selection->handleEvents(e, window);
}

void MultipleSelection::update(const sf::Time& deltaTime)
{
	for (auto& selection : m_selections)
		selection->update(deltaTime);
}

void MultipleSelection::draw(sf::RenderTarget& target)
{
	for (auto& selection : m_selections)
		selection->draw(target);
}

void MultipleSelection::addSelections(std::vector<std::unique_ptr<Selection>> _selections)
{
	m_selections = std::move(_selections);
}

void MultipleSelection::addSelection(std::unique_ptr<Selection> _selections)
{
	m_selections.push_back(std::move(_selections));
}

std::vector<const bool*> MultipleSelection::getHandleToPointersToValues()
{
	std::vector<const bool*> vecOfPointers;
	vecOfPointers.reserve(m_selections.size());

	for (auto& selection : m_selections)
		vecOfPointers.push_back(selection->getPointerToSelected());

	return vecOfPointers;
}