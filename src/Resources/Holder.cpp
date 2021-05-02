#include "Holder.h"

holder holder::s_Instance;

holder& holder::get()
{
	return s_Instance;
}

holder::holder() : fonts("res/czcionki", "ttf"), textures("res/tekstury", "png"), sounds("res/dzwieki", "wav")
{
}