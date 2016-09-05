#include "main.h"
#include <game/CGame.h>

#ifdef _WIN32
int SDL_main(int argc, char **argv)
#else
int main(int argc, char **argv)
#endif
{
	CGame* game = new CGame();
	game->start();
	while (game->gameloop());
	game->stop();
	delete game;
}
