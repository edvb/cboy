# Cboy

A very small wild west themed roguelike where you play a c(ow)boy who was given
a job to kill the corrupt townspeople in the area

Cboy should run on any Unix based OS (Linux, BSD, Mac) as long as ncurses is 
installed, which is default on most systems. To compile the program type `make`
into a terminal. To run type `./cboy` in the same directory. If you have any
promblems with compiling or running feel free to contact me at: edvb54@gmail.com

## Keys

Move around with:

q w e

a s d

z x c

Hold down shift with movement keys to change direction

Other keys:

| Key | Function                            |
| --- | --------                            |
| g   | get item or cycle through inventory |
| v   | drop item                           |
| f   | use item                            |
| r   | load gun                            |
| o   | open door                           |

## Items

| Char | Name     | Type  |
| ---- | -------- | ----- |
| $    | gold     | gold  |
| %    | beef     | food  |
| /    | knife    | knife |
| )    | revolver | gun   |
| *    | ammo     | ammo  |

Food can be eaten with 'f' key and will heal your heath. When a knife is in
hand you do extra damage to others. A gun needs to be loaded with ammo every six
shots and changes to the ']' character when loaded. Then press 'f' to fire it
in direction you are looking. Gold increases your score which gets displayed at
the end of the game.

## Entities

| Char | Color | Name         | Description                               |
| ---- | ----- | ----         | -----------                               |
| c    | grey  | Cow          | Drops beef when killed                    |
| @    | brown | Bandit       | Tires to kill you when you attack someone |
| @    | grey  | Angry Bandit | Always tires to kill you                  |

Bandit's have a chance to drop gold and ammo when killed.
