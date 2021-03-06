#include <SDL2/SDL_ttf.h>

/* the frame rate we're trying to hit.
 * make sure this is a double so we don't have to worry about accidentally
 * demoting to int when using it. */
#define TARGET_FRAME_RATE	144.0
#define WIN_WIDTH		640
#define WIN_HEIGHT		480

#define BALL_START_VEL	2
#define BALL_COOLDOWN	240

extern int PLAYER_SCORE;
extern int ENEMY_SCORE;
