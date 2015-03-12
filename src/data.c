#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "cboy.h"

/* TODO: Improve and implement in other functions */
static void calc_rarity(int *rarity) {
	*rarity = (floor_count('.') % 10) * (*rarity * 1);
	if (rand() % 2 == 0)
		*rarity += rand() % 10;
	else
		*rarity -= rand() % 5;
	if (*rarity + entqty > MAX_ENTITIES)
		*rarity = 0;
}

/* init_item: read from data/items.txt file and store in item array */
void init_item(int from, int to) {

	char *name = malloc(MAX_NAME * sizeof(char));
	char face;
	int color;
	int type;
	int stat;
	int rarity;

	FILE *f = fopen("data/items.txt", "r");

	for (int num = from; num <= to; num++) {
		fscanf(f, "%s %c(%i): type=%i stat=%i rarity=%i\n",
			   name, &face, &color, &type, &stat, &rarity);

		int l = strlen(name);
		for(int i = 0; i < l; i++) {
			if(name[i] == '_') {
				name[i] = ' ';
				continue;
			}
			if(name[i] == ' ')
				break;
		}

		item[num].name = malloc(MAX_NAME * sizeof(char));
		strcpy(item[num].name, name);
		item[num].face = face;
		item[num].color = COLOR_PAIR(color);
		item[num].type = type;
		item[num].stat = stat;

		for (int i = 0; i < MAX_X; i++)
			for (int j = 0; j < MAX_Y; j++)
				item[num].map[j][i] = 0;

		if (rarity != 0)
			if (rand() % 2 == 0)
				rarity += rand() % 3;
			else
				rarity -= rand() % 3;
			if (rarity <= 0)
				rarity = 1;
			for (int x, y, i = 0; i < rarity; i++, itemqty++) {
				do {
					x = rand() % MAX_X;
					y = rand() % MAX_Y;
				} while (!is_floor(x, y));
				item[num].map[y][x]++;
			}

	}

	fclose(f);

	free(name);

	itemqty = to;
}

/* init_entity: read from data/entities.txt file and store in entity array */
void init_entity(void) {

	char *name = malloc(MAX_NAME * sizeof(char));
	char *drop = malloc(MAX_NAME * sizeof(char));
	int type;
	int x_0, y_0;
	char face;
	int color;
	int maxhp;
	int damage;
	int rarity;

	entqty = 0;

	FILE *f = fopen("data/entities.txt", "r");

	do {
		fscanf(f, "%s %c(%i): hp=%i damge=%i type=%i rarity=%i %s\n",
			   name, &face, &color, &maxhp, &damage, &type, &rarity, drop);

		for(int i = 0, l = strlen(name); i < l; i++) {
			if(name[i] == '_') {
				name[i] = ' ';
				continue;
			}
			if(name[i] == ' ')
				break;
		}

		for(int i = 0, l = strlen(drop); i < l; i++) {
			if(drop[i] == '_') {
				drop[i] = ' ';
				continue;
			}
			if(drop[i] == ' ')
				break;
		}

		if (rarity != 0) {
			if (rand() % 2 == 0)
				rarity += rand() % 3;
			else
				rarity -= rand() % 3;
			for (int num = entqty; num < rarity; num++, entqty++) {
				entity[num].name = malloc(MAX_NAME * sizeof(char));
				strcpy(entity[num].name, name);
				entity[num].drop = malloc(MAX_NAME * sizeof(char));
				strcpy(entity[num].drop, drop);
				entity[num].face = face;
				entity[num].color = COLOR_PAIR(color);
				entity[num].maxhp = maxhp;
				entity[num].hp = maxhp;
				entity[num].isdead = false;
				entity[num].damage = damage;
				entity[num].type = type;

				for (int i = 0; i < MAX_HOLDING; i++) {
					entity[num].holding[i].name =
						malloc(MAX_NAME * sizeof(char));
					entity[num].holding[i].face = ' ';
					entity[num].holding[i].color = 0;
					entity[num].holding[i].type = 0;
					entity[num].holding[i].stat = 0;
					entity[num].holding[i].map[0][0] = 0;
				}
				entity[num].hold = 0;

				if (type == ENT_HOSTILE ||
				    type == ENT_ANGRY) {
					strcpy(entity[num].holding[1].name, "gold");
					entity[num].holding[1].map[0][0] = rand()%3;
					strcpy(entity[num].holding[2].name, "ammo");
					entity[num].holding[2].map[0][0] = rand()%2;
				}
				if (type == ENT_PEACEFUL) {
					strcpy(entity[num].holding[1].name, "beef");
					entity[num].holding[1].map[0][0] = rand()%2;
				}

				/* TODO: Break into function and add smart
				 * intergration of is_floor function */
				do {
					x_0 = rand() % MAX_X;
					y_0 = rand() % MAX_Y;
				} while (!is_floor(x_0, y_0));
				entity[num].x = x_0;
				entity[num].y = y_0;

			}
		}
	} while (!feof(f));

	fclose(f);

	free(name);
	free(drop);

}

/* init_player: read from data/players.txt file and store in player array */
void init_player(int from, int to) {

	char *name = malloc(MAX_NAME * sizeof(char));
	int x_0, y_0;
	char face;
	int color;
	int maxhp;
	int damage;

	FILE *f = fopen("data/players.txt", "r");

	for (int num = from; num <= to; num++) {
		fscanf(f, "%s %c(%i): hp=%i damge=%i\n",
			   name, &face, &color, &maxhp, &damage);

		int l = strlen(name);
		for(int i = 0; i < l; i++) {
			if(name[i] == '_') {
				name[i] = ' ';
				continue;
			}
			if(name[i] == ' ')
				break;
		}

		player[num].name = malloc(MAX_NAME * sizeof(char));
		strcpy(player[num].name, name);
		player[num].face = face;
		player[num].color = COLOR_PAIR(color);
		player[num].maxhp = maxhp;
		player[num].hp = maxhp;
		player[num].damage = damage;

		for (int i = 0; i < MAX_HOLDING; i++) {
			player[num].holding[i].name =
				malloc(MAX_NAME * sizeof(char));
			player[num].holding[i].face = ' ';
			player[num].holding[i].color = 0;
			player[num].holding[i].type = 0;
			player[num].holding[i].stat = 0;
		}
		player[num].hold = 0;

		do {
			x_0 = rand() % MAX_X;
			y_0 = rand() % MAX_Y;
		} while (!is_floor(x_0, y_0));
		player[num].x = x_0;
		player[num].y = y_0;

	}

	fclose(f);

	free(name);

	playerqty = to;
}

