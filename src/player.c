#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "cboy.h"
#include "../config.h"

static void
fire_gun(DIREC direc, int x_0, int y_0, int range, int dmg) {
	switch (direc) {
	case LEFT:
		for (int i = x_0; i > x_0-range; i--)
			for (int j = 0; j <= entqty; j++)
				if (entity[j].x == i && entity[j].y == y_0)
					entity[j].hp -= dmg;
		break;
	case DOWN:
		for (int i = y_0; i < y_0+range; i++)
			for (int j = 0; j <= entqty; j++)
				if (entity[j].x == x_0 && entity[j].y == i)
					entity[j].hp -= dmg;
		break;
	case UP:
		for (int i = y_0; i > y_0-range; i--)
			for (int j = 0; j <= entqty; j++)
				if (entity[j].x == x_0 && entity[j].y == i)
					entity[j].hp -= dmg;
		break;
	case RIGHT:
		for (int i = x_0; i < x_0+range; i++)
			for (int j = 0; j <= entqty; j++)
				if (entity[j].x == i && entity[j].y == y_0)
					entity[j].hp -= dmg;
		break;
	}
}

static void
player_use(Ent *e) {
	if (e->holding[e->hold].map[0][0] > 0)
		switch(e->holding[e->hold].type) {
		case ITEM_MISC:
			break;
		case ITEM_FOOD:
			e->hp += e->holding[e->hold].stat;
			e->holding[e->hold].map[0][0]--;
			break;
		case ITEM_AMMO:
			break;
		case ITEM_GUN:
			for (int i = 0; i <= MAX_HOLDING; i++)
				if (e->holding[i].type == ITEM_AMMO)
					fire_gun(e->direc, e->x, e->y, 10, 20);
			break;
		}
}

static void
player_get(Ent *e) {
	for (int i = 0; i <= itemqty; i++)
		if (item[i].map[e->y][e->x] > 0)
			for (int j = 1; j <= MAX_HOLDING; j++)
				if (e->holding[j].face == ' ') {
					e->holding[j] = item[i];
					e->holding[j].map[0][0]++;
					clear_item(&item[i], e->x, e->y);
					return;
				} else if (e->holding[j].face == item[i].face) {
					e->holding[j].map[0][0]++;
					clear_item(&item[i], e->x, e->y);
					return;
				}
	e->hold++;
	if (e->hold == MAX_HOLDING)
		e->hold = 0;
}

void
player_run(int c, Ent *e) {
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
			case CBOY_USE: player_use(e); break;
			case CBOY_GET: player_get(e); break;
			case CBOY_OPEN: toggle_door(e->x, e->y); break;
		}

		if (e->hp > e->maxhp)
			e->hp = e->maxhp;

	}
}

