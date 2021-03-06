#include <ncurses.h>
#include <stdlib.h>

#include "cboy.h"

/* can_step: determine if entity can move to a new space */
bool can_step(Ent *e, int x, int y) {
	if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y) {
		if (e->type == ENT_PLAYER) {
			behostile = false;
			init_map();
			init_entity();
			init_item(0,6);
			for (int i = 0; i <= playerqty; i++)
				draw_map_floor(player[i], 10);
			if (x < 0)
				e->x = MAX_X-1;
			if (x >= MAX_X)
				e->x = 0;
			if (y < 0)
				e->y = MAX_Y-1;
			if (y >= MAX_Y)
				e->y = 0;
		}
		return false;
	}

	for (int i = 0; i <= entqty; i++)
		if (isalive(entity[i].hp) &&
		    entity[i].x == x && entity[i].y == y) {
			if (e->type == ENT_PLAYER) {
				attack(e, &entity[i]);
				if (entity[i].type != ENT_ANGRY)
					behostile = true;
			}
			return false;
		}
	for (int i = 0; i <= playerqty; i++)
		if (isalive(entity[i].hp) &&
		    player[i].x == x && player[i].y == y) {
			attack(e, &player[i]);
			return false;
		}

	if (!is_floor(x, y))
		return false;

	return true;
}

/* move_entity: move a entity by x_0 and y_0 */
void move_entity(Ent *e, int dx, int dy) {
	if (can_step(e, e->x + dx, e->y + dy)) {
		e->x += dx;
		e->y += dy;
	}
}

/* attack: entity e attack entity foe */
void attack(Ent *e, Ent *foe) {
	if (e->type != ENT_PEACEFUL)
		take_damage(foe, deal_damage(e));
}

void take_damage(Ent *e, int damage) {
	e->hp -= damage;
}

int deal_damage(Ent *e) {
	switch (e->holding[e->hold].type) {
		case ITEM_KNIFE:
			return e->damage + e->holding[e->hold].stat;
			break;
		default:
			return e->damage;
	}
}

bool be_hostile(Ent e) {
	switch (e.holding[e.hold].type) {
	case ITEM_GUN:
	case ITEM_KNIFE:
		if (e.holding[e.hold].map[0][0] > 0)
			return true;
	default:
		return false;
	}
}

/* isalive: determine if entity is alive */
bool isalive(int hp) {
	return (hp > 0) ? true : false;
}

/* holding: return x position for what entity is holding */
int holding_x(Ent e, int val) {
	switch (e.direc) {
		case LEFT:
		case LEFTDOWN:
		case LEFTUP:
			return val-1;
		case RIGHT:
		case RIGHTDOWN:
		case RIGHTUP:
			return val+1;
		default: return val;
	}
}

/* holding: return y position for what entity is holding */
int holding_y(Ent e, int val) {
	switch (e.direc) {
		case DOWN:
		case LEFTDOWN:
		case RIGHTDOWN:
			return val+1;
		case UP:
		case LEFTUP:
		case RIGHTUP:
			return val-1;
		default: return val;
	}
}

/* draw_ent: draw entity e if in range of entity oe by r */
void draw_ent(Ent e, Ent oe, int r) {
	if (isalive(e.hp)) {
		for (int j = 0; j < MAX_Y; j++)
		if (e.type == ENT_PLAYER) {
			mvprintw(e.bary, 0, "HP: %d", e.hp);
			printw(" Qty: %d", e.holding[e.hold].map[0][0]);
		}
		mvaddch(e.y, e.x, e.face + e.color);
		if (e.holding[e.hold].map[0][0] > 0)
			mvaddch(holding_y(e, e.y), holding_x(e, e.x),
				e.holding[e.hold].face + e.holding[e.hold].color);
	}
}

void
hostile_ai(Ent *e, int xNew, int yNew, bool topos, int speed) {
	if (isalive(e->hp)) {
		if (topos)
			angry_ai(e, xNew, yNew, speed);
		else
			rand_ai(e, speed);
	} else if (!e->isdead) {
		e->isdead = true;
		for (int i = 0; i < MAX_HOLDING; i++)
			while (e->holding[i].map[0][0] > 0) {
				add_item(&item[query_item(e->holding[i].name)],
					 e->x, e->y);
				e->holding[i].map[0][0]--;
			}
	}
}

void
angry_ai(Ent *e, int xNew, int yNew, int speed) {
	if (isalive(e->hp)) {

		int shouldMove = rand() % speed;

		if (shouldMove != 0) {
			if (xNew > e->x)
				move_entity(e, 1, 0);
			else if (xNew < e->x)
				move_entity(e, -1, 0);
			if (yNew > e->y)
				move_entity(e, 0, 1);
			else if (yNew < e->y)
				move_entity(e, 0, -1);
		}

	} else if (!e->isdead) {
		e->isdead = true;
		for (int i = 0; i < MAX_HOLDING; i++)
			while (e->holding[i].map[0][0] > 0) {
				add_item(&item[query_item(e->holding[i].name)],
					 e->x, e->y);
				e->holding[i].map[0][0]--;
			}
	}
}

/* TODO: Move to ai.c file */
/* TODO: Fix Speed */
void
rand_ai(Ent *e, int speed) {
	if (isalive(e->hp)) {

		int direc = rand() % speed;

		switch (direc) {
			case 0: move_entity(e, -1,  0); break;
			case 1: move_entity(e,  0,  1); break;
			case 2: move_entity(e,  0, -1); break;
			case 3: move_entity(e,  1,  0); break;
		}

	} else if (!e->isdead) {
		e->isdead = true;
		for (int i = 0; i < MAX_HOLDING; i++)
			while (e->holding[i].map[0][0] > 0) {
				add_item(&item[query_item(e->holding[i].name)],
					 e->x, e->y);
				e->holding[i].map[0][0]--;
			}
	}
}

