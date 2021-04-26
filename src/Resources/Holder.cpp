#include "Holder.h"

holder holder::s_Instance;

holder& holder::get()
{
	return s_Instance;
}

holder::holder() : fonts("czcionki", "ttf"), textures("tekstury", "png"), sounds("dzwieki", "wav")
{

}