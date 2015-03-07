#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "cboy.h"
#include "../config.h"

void player_run(int c, Ent *e) {
	if (isalive(e->hp)) {

		switch (c) {
			case CBOY_LEFT:
				move_entity(e, -1,  0);
				e->direc = LEFT;
				break;
			case CBOY_DOWN:
				move_entity(e,  0,  1);
				e->direc = DOWN;
				break;
			case CBOY_UP:
				move_entity(e,  0, -1);
				e->direc = UP;
				break;
			case CBOY_RIGHT:
				move_entity(e,  1,  0);
				e->direc = RIGHT;
				break;
			case CBOY_STAND: break;
			case CBOY_OPEN: toggle_door(e->x, e->y); break;
		}

	}
}

