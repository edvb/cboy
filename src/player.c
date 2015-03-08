#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "cboy.h"
#include "../config.h"

static void player_get_item(Ent *e) {
	for (int i = 0; i <= itemqty; i++)
		if (item[i].map[e->y][e->x] > 0) {
			for (int j = 1; j <= MAX_HOLDING; j++)
				if (e->holding[j].face == ' ') {
					e->holding[j] = item[i];
					clear_item(&item[i], e->x, e->y);
					return;
				}
		}
	e->hold++;
	if (e->hold == MAX_HOLDING)
		e->hold = 0;
}

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
			case CBOY_GET: player_get_item(e); break;
			case CBOY_OPEN: toggle_door(e->x, e->y); break;
		}

	}
}

