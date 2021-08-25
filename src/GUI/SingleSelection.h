#ifndef SINGLESELECTION_H
#define SINGLESELECTION_H

#include "MultipleSelection.h"

class SingleSelection : public MultipleSelection
{
public:
	SingleSelection();

	void handleEvents(sf::Event e, const sf::RenderWindow& window) override;
};

inline std::unique_ptr<SingleSelection> makeSingleSelection()
{
	return std::make_unique<SingleSelection>();
}

#endif