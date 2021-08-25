#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "BaseState.h"
#include "../GUI/Button.h"
#include "../GUI/InputForm.h"
#include "../GUI/Text.h"
#include "../GUI/FrameRate.h"
#include "../GUI/Selection.h"
#include "../GUI/MultipleSelection.h"
#include "../GUI/SingleSelection.h"
#include "../Game.h"

class MenuState : public BaseState
{
public:
	MenuState(Game& _game);

	void handleEvents(sf::Event e, const sf::RenderWindow& window) override;

	void update(const sf::Time& deltaTime) override;

	void draw(sf::RenderTarget& target) override;
private:
	std::string m_input = "";
	//std::string m_input[3][3];

	int m_value = 5;

	std::vector<const bool*> vecPtrToSelectBox;

	const float* fpsValuePointer = nullptr;

	std::vector<std::unique_ptr<Widget>> m_widgets;
	std::vector<std::unique_ptr<Widget>> m_widgetsAfterClick;

	std::vector<std::unique_ptr<Widget>>* m_active = &m_widgets;

	void m_compute();

	float m_determinant(float matrix[10][10], int n);
};

#endif

