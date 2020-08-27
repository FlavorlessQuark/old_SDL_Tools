#include "SDL_Master.h"


int main()
{
	game *game;
	game = game_init();
	game->display = display_init();
	update(game);
}
