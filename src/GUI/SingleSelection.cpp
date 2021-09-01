#include "SingleSelection.h"

#include <iostream>

SingleSelection::SingleSelection()
{
	
}

void SingleSelection::handleEvents(sf::Event e, const sf::RenderWindow& window)
{
	std::vector<const bool*> ptrValuesBefore = getPointersToValues();
	std::vector<bool> valuesBefore;

	for (int i = 0; i < ptrValuesBefore.size(); i++)
		valuesBefore.push_back(*ptrValuesBefore[i]);

	for (auto& selection : m_selections)
		selection->handleEvents(e, window);

	std::vector<const bool*> valuesAfter = getPointersToValues();

	int index = -1;

	for (int i = 0; i < valuesBefore.size(); i++)
		if (valuesBefore[i] != *valuesAfter[i])
			index = i;

	if (index != -1)
		for (int i = 0; i < valuesBefore.size(); i++)
			if (index != i)
				m_selections[i]->setSelected(false);

}