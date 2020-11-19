
#include "state.h"

using namespace std;

int main(int argc, char**args)
{

	SDL_Init(SDL_INIT_EVERYTHING);
	State::menu = new Menu();
	State::create = new Create();
	State::generate = new Generate();
	State::current = State::menu;

	while (1)
	{
		State::current->enter();
		State::current->update();
		State::current->exit();
	}

	return 0;
}