#include "MenuState.h"

#include <iostream>

MenuState::MenuState(Game& _game)
	: BaseState(_game)
{
	auto m_options = makeOptions(sf::Vector2f(100, 100), sf::Vector2f(500, 35));

	m_options->addOption("-%");
	m_options->addOption("druga");
	m_options->addOption("trzeciaaaaaaaaaaaaaaa");

	m_ptrToOptionString = m_options->getPtrToString();
	m_ptrToOptionIndex = m_options->getPtrToIndex();


	auto m_button1 = makeButton((sf::Vector2f)_game.getWindow().getSize() / 2.f, sf::Vector2f(200, 100), "Button 1");

	/*auto m_multipleSelection = makeSingleSelection();

	for (int i = 0; i < 7000; i++)
	{
		auto m_select1 = makeSelection(sf::Vector2f( 100, 100 * (i + 1)));
		m_multipleSelection->addSelection(std::move(m_select1));

		auto m_text = makeText(sf::Vector2f( 200, 90 + 100 * i ), "test" + std::to_string(i + 1));
		m_widgets.push_back(std::move(m_text));
	}

	vecPtrToSelectBox = m_multipleSelection->getPointersToValues();*/

	m_button1->setFunction([&]()
		{
			std::cout << "Button 1 was pressed\n";
			std::cout << "Selected string: " <<*m_ptrToOptionString << " Selected item: " << *m_ptrToOptionIndex << '\n';
			m_active = &m_widgetsAfterClick;
		}
	);

	auto m_button2 = makeButton((sf::Vector2f)_game.getWindow().getSize() / 2.f + sf::Vector2f(0, 150), sf::Vector2f(200, 100), "Exit");

	m_button2->setFunction([&]()
		{
			std::cout << "Exit\n";
			m_exit = true;
		}
	);

	auto m_button11 = makeButton((sf::Vector2f)_game.getWindow().getSize() / 2.f, sf::Vector2f(200, 100), "Button 1.1");

	m_button11->setFunction([&]()
		{
			std::cout << "Button 1.1 was pressed: " + m_input + '\n';
			m_active = &m_widgets;
		}
	);

	auto m_inputForm = makeInputForm((sf::Vector2f)_game.getWindow().getSize() / 2.f - sf::Vector2f(0, 150), sf::Vector2f(400, 50), &m_input);

	auto m_text1 = makeText((sf::Vector2f)_game.getWindow().getSize() / 2.f - sf::Vector2f(0, 250), "-% -% a -% b:");

	auto m_fps1 = makeFrameRate(sf::Vector2f(125, 0));
	auto m_fps2 = makeFrameRate(sf::Vector2f(125, 0));

	fpsValuePointer = m_fps1->getFpsPointer();

	m_text1->setArgs(&m_input, &m_value, &m_value);
	m_text1->setColor(sf::Color::Red);
	m_text1->setCharSize(64);
	m_text1->setOutlineThickness(0);
	m_text1->setOutlineColor(sf::Color::White);

	auto m_canvas = makeCanvas(sf::FloatRect(0, 0, m_game->getWindow().getSize().x, m_game->getWindow().getSize().y), 500);

	m_canvas->addWidget(std::move(m_button1));
	m_canvas->addWidget(std::move(m_button2));
	m_canvas->addWidget(std::move(m_inputForm));
	m_canvas->addWidget(std::move(m_text1));
	m_canvas->addWidget(std::move(m_options));

	m_widgets.push_back(std::move(m_canvas));
	m_widgets.push_back(std::move(m_fps1));

	m_widgetsAfterClick.push_back(std::move(m_button11));
	m_widgetsAfterClick.push_back(std::move(m_fps2));
	//m_widgets.push_back(std::move(m_multipleSelection));

	/*auto m_fps1 = makeFrameRate(sf::Vector2f(125, 0));

	m_widgets.push_back(std::move(m_fps1));

	auto m_button1 = makeButton((sf::Vector2f)_game.getWindow().getSize() / 2.f + sf::Vector2f(0, 290), sf::Vector2f(200, 100), "Compute");

	m_button1->setFunction([&]()
		{
			std::cout << "Button 1 was pressed\n";
			m_compute();
			m_active = &m_widgetsAfterClick;
		}
	);

	m_widgets.push_back(std::move(m_button1));

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			auto m_inputForm = makeInputForm((sf::Vector2f)_game.getWindow().getSize() / 2.f + sf::Vector2f(150 * i - 150, 150 * j - 150), sf::Vector2f(100, 100), &m_input[i][j]);

			m_widgets.push_back(std::move(m_inputForm));
		}
	}*/
}

void MenuState::handleEvents(sf::Event e, const sf::RenderWindow& window)
{
	for (auto& widget : *m_active)
		widget->handleEvents(e, window);

	if (m_exit)
		m_game->popState();
}

void MenuState::update(const sf::Time& deltaTime)
{
	//for (const bool* ptr : vecPtrToSelectBox)
		//std::cout << *ptr << " ";
	//std::cout << std::endl;
	m_value++;
	if (m_value > 1000)
		m_value = 0;

	for (auto& widget : *m_active)
		widget->update(deltaTime);
}

void MenuState::draw(sf::RenderTarget& target)
{
	for (auto& widget : *m_active)
		widget->draw(target);
}

void MenuState::m_compute()
{
	/*m_widgetsAfterClick.clear();

	auto m_fps1 = makeFrameRate(sf::Vector2f(125, 0));

	m_widgetsAfterClick.push_back(std::move(m_fps1));

	float matrix[10][10];

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			matrix[i][j] = atof(m_input[i][j].c_str());

	float det = m_determinant(matrix, 3);

	auto m_text1 = makeText((sf::Vector2f)m_game->getWindow().getSize() / 2.f, "Determinant: " + std::to_string(det));

	m_text1->setColor(sf::Color::Red);
	m_text1->setCharSize(64);
	m_text1->setOutlineThickness(2);
	m_text1->setOutlineColor(sf::Color::White);

	m_widgetsAfterClick.push_back(std::move(m_text1));

	auto m_button1 = makeButton((sf::Vector2f)m_game->getWindow().getSize() / 2.f + sf::Vector2f(0, 290), sf::Vector2f(200, 100), "Back");

	m_button1->setFunction([&]()
		{
			std::cout << "Button 2 was pressed\n";
			m_active = &m_widgets;
		}
	);

	m_widgetsAfterClick.push_back(std::move(m_button1));*/
}

float MenuState::m_determinant(float matrix[10][10], int n) {
	float det = 0;
	float submatrix[10][10];
	if (n == 2)
		return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
	else {
		for (int x = 0; x < n; x++) {
			int subi = 0;
			for (int i = 1; i < n; i++) {
				int subj = 0;
				for (int j = 0; j < n; j++) {
					if (j == x)
						continue;
					submatrix[subi][subj] = matrix[i][j];
					subj++;
				}
				subi++;
			}
			det = det + (pow(-1, x) * matrix[0][x] * m_determinant(submatrix, n - 1));
		}
	}
	return det;
}
