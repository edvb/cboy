const char mapstart[MAX_Y][MAX_X+1] = {
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
};

int maprand[MAX_Y][MAX_X+1];
char worldMap[MAX_Y][MAX_X+1];

const char river0[24][MAX_X+1] = {
"     ~~~~~~~~            ",
"     ~~~~~~~~            ",
"      ~~~~~~~~           ",
"      ~~~~~~~~           ",
"      ~~~~~~~~           ",
"      ~~~~~~~~           ",
"     ~~~~~~~~~           ",
"    ~~~~~~~~~            ",
"    ~~~~~~~~             ",
"   ~~~~~~~~~             ",
"   ~~~~~~~~~             ",
" XXXXXXXXXXX             ",
"XX.........XX            ",
".............            ",
".XXXXXXXXXXX.            ",
"XX~~~~~~~  XX            ",
"  ~~~~~~~                ",
"  ~~~~~~~        ~~      ",
"  ~~~~~~~~      ~~~~~    ",
"  ~~~~~~~~~~    ~~~~~~~  ",
"   ~~~~~~~~~~~~~~~~~~~~  ",
"   ~~~~~~~~  ~~~~~~~~~~~ ",
"   ~~~~~~~~~      ~~~~~  ",
"   ~~~~~~~~~             ",
};

const char river1[24][MAX_X+1] = {
"~~~~~~                   ",
" ~~~~~~~                 ",
"  ~~~~~~~                ",
"  ~~~~~~~~               ",
"   XXXXXXXXXXX           ",
"  XX.........XX          ",
"  .............          ",
"  .XXXXXXXXXXX.          ",
"  XX ~~~~~~~~XX          ",
"      ~~~~~~~~~          ",
"       ~~~~~~~~          ",
"       ~~~~~~~~~         ",
"        ~~~~~~~~         ",
"        ~~~~~~~~~        ",
"        ~~~~~~~~~~       ",
"         ~~~~~~~~~       ",
"         ~~~~~~~~~       ",
"        ~~~~~~~~~~       ",
"        ~~~~~~~~~        ",
"       ~~~~~~~~~         ",
"       ~~~~~~~~          ",
"      ~~~~~~~~~          ",
"      ~~~~~~~~~          ",
"     ~~~~~~~~~           ",
};

const char lake0[24][MAX_X+1] = {
" ~~~~~    ",
"~~~~~~~   ",
"~~~~~~~~~ ",
"~~~~~~~~~~",
" ~~~~~~~~~",
"   ~~~~~  ",
};

const char saloon[8][MAX_X+1] = {
"XXXXXXXXXX",
"X........X",
"X=======+X",
"X..h.h.h.X",
"Xh.......X",
"Xo.......X",
"Xh.....hoX",
"XXX+XXXXXX",
};

const char jail[7][MAX_X+1] = {
"XXXXXXXXXXXX",
"Xh..b....h.X",
"X...b...===X",
"Xbbbb......X",
"X...b......X",
"Xh..b......X",
"XXXXXXXXX+XX",
};

const char bank[5][MAX_X+1] = {
"XXXXXXXXXXXXXX",
"Xh......+...sX",
"X.......=h..sX",
"Xh......=h..sX",
"XXXX+XXXXXXXXX",
};

const char house[6][MAX_X+1] = {
"XXXXXXXXX",
"Xhoh....X",
"X....===X",
"X.......X",
"Xh.o...0X",
"XXXXX+XXX",
};

const char grave[6][MAX_X+1] = {
"bbbbbbbbbbbbbb",
"byygyyggyygyyb",
"bggggggggggggb",
"byygyyggyygyyb",
"bggggggggggggb",
"bbbbbbggbbbbbb",
};

const char well[3][MAX_X+1] = {
" # ",
"#~#",
" # ",
};

