#ifndef MULTIPLESELECTION_H
#define MULTIPLESELECTION_H

#include <vector>

#include "Widget.h"
#include "Selection.h"

class MultipleSelection : public Widget
{
public:
	MultipleSelection();

	void handleEvents(sf::Event e, const sf::RenderWindow& window) override;

	void update(const sf::Time& deltaTime) override;

	void draw(sf::RenderTarget& target) override;

	void addSelections(std::vector<std::unique_ptr<Selection>> _selections);

	void addSelection(std::unique_ptr<Selection> _selections);

	std::vector<const bool*> getHandleToPointersToValues();

protected:
	std::vector<std::unique_ptr<Selection>> m_selections;
};

inline std::unique_ptr<MultipleSelection> makeMultipleSelection()
{
	return std::make_unique<MultipleSelection>();
}

#endif