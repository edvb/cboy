/* settings for cboy */

/* quick settings */
#define CBOY_KEYS 1 /* arrow keys = 0, vi keys = 1, num pad = 2*/


#if CBOY_KEYS == 0
#  define CBOY_LEFT  KEY_LEFT
#  define CBOY_DOWN  KEY_DOWN
#  define CBOY_UP    KEY_UP
#  define CBOY_RIGHT KEY_RIGHT
#  define CBOY_STAND '.'
#elif CBOY_KEYS == 1
#  define CBOY_LEFT  'h'
#  define CBOY_DOWN  'j'
#  define CBOY_UP    'k'
#  define CBOY_RIGHT 'l'
#  define CBOY_STAND '.'
#elif CBOY_KEYS == 2
#  define CBOY_LEFT  '4'
#  define CBOY_DOWN  '2'
#  define CBOY_UP    '8'
#  define CBOY_RIGHT '6'
#  define CBOY_STAND '5'
#endif

#define CBOY_USE  'f'
#define CBOY_GET  'g'
#define CBOY_DROP 'd'
#define CBOY_OPEN 'o'
