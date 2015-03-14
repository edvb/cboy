#include <getopt.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cboy.h"

static const struct option longopts[] = {
	{"help", no_argument, NULL, 'h'},
	{"version", no_argument, NULL, 'v'},
	{NULL, 0, NULL, 0}
};

static void print_help(void) {
	printf("\
Usage: cboy [OPTION]\n\
A Small Wild West Themed ASCII Game\n\
\n\
  -h    display this help and exit\n\
  -v    display version information and exit\n\
\n\
cboy home page: <https://github.com/edvb54/cboy>\n\
");
}

static void print_version(void) {
	printf("cboy %s\n", VERSION);
}

int main(int argc, char *argv[]) {
	int optc;

	while ((optc = getopt_long(argc, argv, "hv", longopts, NULL)) != -1)
		switch (optc) {
			case 'h':
				print_help();
				return 0;
			case 'v':
				print_version();
				return 0;
			default:
				printf("cboy: error: option not supported\n");
				printf("for help run \"cboy -h\"\n");
				return 1;
		}

	initscr();
	/* nodelay(stdscr,true); */
	noecho();
	cbreak();
	curs_set(0);
	nonl();
	keypad(stdscr,true);
	scrollok(stdscr, false);
	/* timeout(1000); */

	start_color();

	/* TODO: Improve how colors are assigned */
	init_color( 0, 100,  100,  100); /* black */
	init_color( 1, 600,    0,    0); /* red */
	init_color( 2,   0,  600,    0); /* green */
	init_color( 3,   0,  400,  800); /* blue */
	init_color( 4, 800,  800,    0); /* yellow */
	init_color( 5, 370,  280,    0); /* brown */
	init_color( 6, 500,  500,  500); /* grey */
	init_color( 8, 650,  550,    0); /* dark yellow */
	init_color( 9,   0,  400,    0); /* dark green */
	init_color(10,   0,  200,  400); /* dark blue */
	init_color(11, 200,  200,  200); /* dark grey */
	init_color(12, 150,  120,   50); /* dark brown */
	init_color(13, 550,  450,    0); /* dark yellow */

	init_pair( 1,  1,  0); /* red */
	init_pair( 2,  2,  0); /* green */
	init_pair( 3,  3,  0); /* blue */
	init_pair( 4,  4,  0); /* yellow */
	init_pair( 5,  5,  0); /* brown */
	init_pair( 6,  6,  0); /* grey */
	init_pair( 8,  8,  0); /* dark yellow */
	init_pair( 9,  3,  0); /* water */
	init_pair(10,  2,  0); /* grass */
	init_pair(11, 11,  0); /* dark grey */
	init_pair(12,  6, 11); /* dark grey bg */
	init_pair(13,  5, 12); /* dark brown bg */
	init_pair(14, 13,  0); /* dark brown bg */

	int c;

	getmaxyx(stdscr, maxy, maxx);

	if (maxx < 80 || maxy < 24) {
		endwin();
		printf("cboy: error: terminal too small\n");
		return 1;
	}

	srand(time(NULL));

	init_map();
	init_map();
	init_entity();
	init_player(0, 0);
	player[0].bary = 0;

	init_item(0, 6);

	do {

		clear();

		for (int i = 0; i <= playerqty; i++)
			draw_map_floor(player[i], 10);
		player_run(c, &player[0]);
		for (int i = 0; i < entqty; i++)
			switch (entity[i].type) {
			case ENT_PLAYER: break;
			case ENT_HOSTILE:
				hostile_ai(&entity[i], player[0].x, player[0].y,
					   behostile, 8);
				break;
			case ENT_ANGRY:
				angry_ai(&entity[i], player[0].x, player[0].y, 8);
				break;
			case ENT_PEACEFUL:
				rand_ai(&entity[i], 8);
				break;
			}

		for (int i = 0; i <= playerqty; i++) {
			for (int j = itemqty; j >= 0; j--)
				draw_item(item[j], player[i], 10);
			draw_ent(player[i], player[i], 10);
			for (int j = 0; j <= entqty; j++)
				draw_ent(entity[j], player[i], 10);
			draw_map(player[i], 10);
		}

		c = getch();

	} while (c != 27);

	endwin();
	printf("GAME OVER\n");

	for (int i = 0; i <= playerqty; i++)
		for (int j = 0; j < MAX_HOLDING; j++)
			if (player[i].holding[j].face == '$')
				printf("%s's Score: %d\n",
				       player[i].name, player[i].holding[j].map[0][0]);

	for (int i = 0; i <= itemqty; i++)
		free(item[i].name);
	for (int i = 0; i <= playerqty; i++) {
		for (int i = 0; i < MAX_HOLDING; i++)
			free(player[i].holding[i].name);
		free(player[i].name);
	}
	for (int i = 0; i <= entqty; i++) {
		for (int i = 0; i < MAX_HOLDING; i++)
			free(entity[i].holding[i].name);
		free(entity[i].name);
	}

	return 0;
}

