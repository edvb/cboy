#ifndef CBOY_H
#define CBOY_H

#define ever (;;)

#define RED COLOR_PAIR(1)
#define GREEN COLOR_PAIR(2)
#define BLUE COLOR_PAIR(3)
#define YELLOW COLOR_PAIR(4)
#define BROWN COLOR_PAIR(5)
#define GREY COLOR_PAIR(6)
#define DARK_YELLOW COLOR_PAIR(8)
#define WATER COLOR_PAIR(9)
#define GRASS COLOR_PAIR(10)

#define MAX_X 80
#define MAX_Y 24
#define MAX_NAME 16
#define MAX_ITEMS 256
#define MAX_ENTITIES 256
#define MAX_PLAYERS 8
#define MAX_HOLDING 8

typedef enum {
	LEFT,
	DOWN,
	UP,
	RIGHT,
	LEFTDOWN,
	LEFTUP,
	RIGHTDOWN,
	RIGHTUP
} DIREC;

typedef enum {
	ITEM_MISC,
	ITEM_FOOD,
	ITEM_KNIFE,
	ITEM_AMMO,
	ITEM_GUN
} ITEM_TYPE;

typedef enum {
	ENT_PLAYER,
	ENT_HOSTILE,
	ENT_ANGRY,
	ENT_PEACEFUL
} ENT_TYPE;

typedef struct _Item Item;
struct _Item {
	char *name;
	ITEM_TYPE type;
	int map[MAX_Y][MAX_X];
	char face;
	int color;

	int stat;
};

typedef struct _Ent Ent;
struct _Ent {
	char *name;
	char *drop;
	ENT_TYPE type;
	char face;
	int color;

	DIREC direc;
	int x, y;
	int bary;

	int maxhp, hp;
	bool isdead;
	struct _Item holding[MAX_HOLDING];
	int hold;
	int damage;
};

/* TODO: localize some of these functions */

/***********************\
* map.c: handle the map *
\***********************/
void init_map(void);
char get_map(int x, int y);
void set_map(int x, int y, char newch);
bool is_floor(int x, int y);
bool is_floor_range(int x, int y, int dx, int dy);
int  floor_count(char ch);
void toggle_door(int x, int y);
void draw_map(Ent e, int r);
void draw_map_floor(Ent e, int r);

/**********************\
* item.c: handle items *
\**********************/
int  query_item(char *name);
void clear_item(Item *item, int x, int y);
void add_item(Item *item, int x, int y);
void draw_item(Item item, Ent e, int r);

/*****************************************\
* entity.c: handle anything with entities *
\*****************************************/
bool can_step(Ent *e, int x, int y);
void move_entity(Ent *e, int x_0, int y_0);
void attack(Ent *e, Ent *foe);
void take_damage(Ent *e, int damge);
int  deal_damage(Ent *e);
bool be_hostile(Ent e);
bool isalive(int hp);
int  holding_x(Ent e, int val);
int  holding_y(Ent e, int val);
void draw_ent(Ent e, Ent oe, int r);
void hostile_ai(Ent *e, int xNew, int yNew, bool topos, int speed);
void angry_ai(Ent *e, int xNew, int yNew, int speed);
void rand_ai(Ent *e, int speed);

/*****************************\
* player.c: handle the player *
\*****************************/
void player_run(int c, Ent *e);

/*********************************************\
* data.c: handle reading from data/ directory *
\*********************************************/
void init_item(int to, int from);
void init_entity(void);
void init_player(int from, int to);

int maxx;
int maxy;

int itemqty;
int playerqty;
int entqty;

Item item[MAX_ITEMS];
Ent player[MAX_PLAYERS];
Ent entity[MAX_ENTITIES];

#endif /* CBOY_H */
