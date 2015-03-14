#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "cboy.h"
#include "../config.h"

static void
fire_gun(DIREC direc, int x_0, int y_0, int range, int dmg) {
	switch (direc) {
	case LEFT:
		for (int i = x_0; i > x_0-range; i--) {
			for (int j = 0; j <= entqty; j++)
				if (entity[j].x == i && entity[j].y == y_0)
					entity[j].hp -= dmg;
			if (!is_floor(i, y_0))
				return;
			mvaddch(y_0, i, 'x' + RED);
		}
		break;
	case DOWN:
		for (int i = y_0; i < y_0+range; i++) {
			for (int j = 0; j <= entqty; j++)
				if (entity[j].x == x_0 && entity[j].y == i)
					entity[j].hp -= dmg;
			if (!is_floor(x_0, i))
				return;
			mvaddch(i, x_0, 'x' + RED);
		}
		break;
	case UP:
		for (int i = y_0; i > y_0-range; i--) {
			for (int j = 0; j <= entqty; j++)
				if (entity[j].x == x_0 && entity[j].y == i)
					entity[j].hp -= dmg;
			if (!is_floor(x_0, i))
				return;
			mvaddch(i, x_0, 'x' + RED);
		}
		break;
	case RIGHT:
		for (int i = x_0; i < x_0+range; i++) {
			for (int j = 0; j <= entqty; j++)
				if (entity[j].x == i && entity[j].y == y_0)
					entity[j].hp -= dmg;
			if (!is_floor(i, y_0))
				return;
			mvaddch(y_0, i, 'x' + RED);
		}
		break;
	case LEFTDOWN:
		for (int i = x_0, j = y_0;
		     i > x_0-range && j < y_0+range;
		     i--, j++) {
			for (int num = 0; num <= entqty; num++)
				if (entity[num].x == i && entity[num].y == j)
					entity[num].hp -= dmg;
			if (!is_floor(i, j))
				return;
			mvaddch(j, i, 'x' + RED);
		}
		break;
	case LEFTUP:
		for (int i = x_0, j = y_0;
		     i > x_0-range && j > y_0-range;
		     i--, j--) {
			for (int num = 0; num <= entqty; num++)
				if (entity[num].x == i && entity[num].y == j)
					entity[num].hp -= dmg;
			if (!is_floor(i, j))
				return;
			mvaddch(j, i, 'x' + RED);
		}
		break;
	case RIGHTDOWN:
		for (int i = x_0, j = y_0;
		     i < x_0+range && j > y_0-range; 
		     i++, j++) {
			for (int num = 0; num <= entqty; num++)
				if (entity[num].x == i && entity[num].y == j)
					entity[num].hp -= dmg;
			if (!is_floor(i, j))
				return;
			mvaddch(j, i, 'x' + RED);
		}
		break;
	case RIGHTUP:
		for (int i = x_0, j = y_0;
		     i < x_0+range && j > y_0-range;
		     i++, j--) {
			for (int num = 0; num <= entqty; num++)
				if (entity[num].x == i && entity[num].y == j)
					entity[num].hp -= dmg;
			if (!is_floor(i, j))
				return;
			mvaddch(j, i, 'x' + RED);
		}
		break;
	}
}

static void
load_gun(Ent *e) {
	if (e->holding[e->hold].type == ITEM_GUN)
		for (int i = 0; i <= MAX_HOLDING; i++)
			if (e->holding[i].map[0][0] > 0 &&
			    e->holding[i].type == ITEM_AMMO) {
				e->holding[i].map[0][0]--;
				e->holding[e->hold].face = ']';
				/* TODO: Dont make this hard coded */
				e->holding[e->hold].stat = 6;
				return;
			}
}

static void
player_drop(Ent *e) {
	if (e->holding[e->hold].map[0][0] > 0) {
		e->holding[e->hold].map[0][0]--;
		add_item(&item[query_item(e->holding[e->hold].name)], e->x, e->y);
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

static void
player_use(Ent *e) {
	int dmg;
	if (e->holding[e->hold].map[0][0] > 0)
		switch(e->holding[e->hold].type) {
		case ITEM_MISC:
		case ITEM_KNIFE:
		case ITEM_AMMO:
			break;
		case ITEM_FOOD:
			e->hp += e->holding[e->hold].stat;
			e->holding[e->hold].map[0][0]--;
			break;
		case ITEM_GUN:
			if (e->holding[e->hold].face == ']') {
				if (rand()%2 == 0)
					dmg = e->holding[query_item("ammo")].stat + rand()%3;
				else
					dmg = e->holding[query_item("ammo")].stat - rand()%5;
				fire_gun(e->direc, e->x, e->y,
					 20, dmg);
				e->holding[e->hold].stat--;
				if (e->holding[e->hold].stat <= 0)
					e->holding[e->hold].face = ')';
			}
			break;
		}
}

void
player_run(int c, Ent *e) {
	if (isalive(e->hp)) {

		switch (c) {
			case CBOY_LEFT:      move_entity(e, -1,  0);  e->direc = LEFT; break;
			case CBOY_DOWN:      move_entity(e,  0,  1);  e->direc = DOWN; break;
			case CBOY_UP:        move_entity(e,  0, -1);  e->direc = UP; break;
			case CBOY_RIGHT:     move_entity(e,  1,  0);  e->direc = RIGHT; break;
			case CBOY_LEFTDOWN:  move_entity(e, -1,  1);  e->direc = LEFTDOWN; break;
			case CBOY_LEFTUP:    move_entity(e, -1,  -1); e->direc = LEFTUP; break;
			case CBOY_RIGHTDOWN: move_entity(e,  1,  1);  e->direc = RIGHTDOWN; break;
			case CBOY_RIGHTUP:   move_entity(e,  1,  -1); e->direc = RIGHTUP; break;
			case CBOY_STAND:     break;
			case CBOY_DROP:      player_drop(e); break;
			case CBOY_GET:       player_get(e); break;
			case CBOY_LOAD:      load_gun(e); break;
			case CBOY_OPEN:      toggle_door(e->x, e->y); break;
			case CBOY_USE:       player_use(e); break;
		}

		if (e->hp > e->maxhp)
			e->hp = e->maxhp;

	}
}

