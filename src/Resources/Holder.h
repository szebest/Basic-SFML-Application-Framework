#ifndef HOLDER_H
#define HOLDER_H

#include <SFML/Audio.hpp>
#include "Manager.h"

class holder
{
public:
	static holder& get();

	holder(const holder&) = delete;

	manager<sf::Font> fonts;
	manager<sf::Texture> textures;
	manager<sf::SoundBuffer> sounds;

private:
	holder();

	static holder s_Instance;
};

#endif
