#include "Game.h"
#include "Util/Random.h"
#include "Util/util.h"
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <any>

class test
{
public:
	test(std::string pattern)
	{
		
	}

	template<typename... Args, typename T>
	test(std::string pattern, T first, Args... args) : 
		m_pattern(std::move(pattern))
	{
		addIntegersToVector(first);

		implementation(args...);
	}

	void print()
	{
		std::string tmp = "";
		int index = 0;
		for (int i = 0; i < m_pattern.size(); i++)
		{
			if (m_pattern[i] == '%' && index < m_intVector.size())
				tmp += std::to_string(m_intVector[index++]);
			else
				tmp += m_pattern[i];
		}

		std::cout << tmp << '\n';
	}
private:
	std::string m_pattern;

	std::vector<int> m_intVector;

	template<typename T>
	void addIntegersToVector(T value)
	{
		if (typeid(T).name() == typeid(int).name())
			m_intVector.push_back(value);
	}

	template<typename T>
	void implementation(T& first)
	{
		std::cout << first << std::endl;

		addIntegersToVector(first);
	}
	
	template<typename... Args, typename T>
	void implementation(T& first, Args&... args)
	{
		constexpr auto numargs = sizeof...(Args) + 1;

		std::cout << first << std::endl;
		
		addIntegersToVector(first);

		implementation(args...);
	}
};

int main()
{
	test* t = new test("Hp: %", 5, 'a', 10, 10, 10, 10);
	t->print();
	std::unique_ptr<Game> game(new Game("Test", 1280, 720));
	return game->run();
}