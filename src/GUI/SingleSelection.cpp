#include "SingleSelection.h"

#include <iostream>

SingleSelection::SingleSelection()
{
	
}

void SingleSelection::handleEvents(sf::Event e, const sf::RenderWindow& window)
{
	std::vector<const bool*> ptrValuesBefore = getHandleToPointersToValues();
	std::vector<bool> valuesBefore;

	for (int i = 0; i < ptrValuesBefore.size(); i++)
		valuesBefore.push_back(*ptrValuesBefore[i]);

	for (auto& selection : m_selections)
		selection->handleEvents(e, window);

	std::vector<const bool*> valuesAfter = getHandleToPointersToValues();

	int index = -1;

	for (int i = 0; i < valuesBefore.size(); i++)
		if (valuesBefore[i] != *valuesAfter[i])
			index = i;

	//std::cout << valuesBefore[0] << " ";
	//std::cout << *valuesAfter[0] << std::endl;

	if (index != -1)
		for (int i = 0; i < valuesBefore.size(); i++)
			if (index != i)
				m_selections[i]->setSelected(false);

}