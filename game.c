#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "error.h"
#include "basic.h"
#include "sprite.h"
#include "log.h"
#include "strings.h"
#include "utils.h"
#include "data.h"

#define MOVE_SPEED	4

int game_loop()
{
	int done = FALSE;
	enum game_state state = PLAYING;
	int mright, mleft, mup, mdown;

	double clock;		/* last time sample in seconds */
	double render_timer;	/* time control for rendering */
	double frmtime;		/* timer used for when to show updated fps */
	int frms;		/* frame counter for fps display */

	DT = 0.0;
	render_timer = 0.0;
	clock = getseconds();

	if (DEBUG) {
		frmtime = getseconds();
		frms = 0;
	}

	mright = mleft = mup = mdown = FALSE;

	SDL_Event *event = malloc(sizeof(*event));

	/* everything related to this initializing this sprite
	 * should eventually be abstracted to a function in the
	 * sprite header */
	// struct sprite pl_sprite = SPRITE_DEFAULT;
	// pl_sprite.surface = SDL_LoadBMP(PLAYER_SPR);

	// if (pl_sprite.surface == NULL) {
	// 	throw_err(SDL_BMP_ERR);
	// }

	// pl_sprite.frames = 3;
	// pl_sprite.dest_rect = malloc(sizeof(*(pl_sprite.dest_rect)));
	// pl_sprite.dest_rect->x = 0;
	// pl_sprite.dest_rect->y = 0;
	// pl_sprite.dest_rect->w = 200;
	// pl_sprite.dest_rect->h = 144;

	// pl_sprite.source_rect = malloc(sizeof(*(pl_sprite.source_rect)));
	// *(pl_sprite.source_rect) = *(pl_sprite.dest_rect);

	// anispeed(&pl_sprite, (1/60.0));
	// aniset(&pl_sprite, pl_sprite.frames);
	// anireverse(&pl_sprite, TRUE);
	// anistart(&pl_sprite, TRUE);

	logstr("Entering main game loop");
	/* this stuff is all for testing, any engine-related
	 * code needs to be abstracted out at some point */
	while (!done) {
		DT = getseconds() - clock; /* get the current delta time for this frame */
		clock = getseconds(); /* updates the clock to check the next delta time */

		switch (state) {
		case PLAYING:
			while (SDL_PollEvent(event)) {
				switch (event->type) {
				case SDL_QUIT:
					done = TRUE;
					break;
				case SDL_KEYDOWN:
					switch (event->key.keysym.sym) {
					case SDLK_ESCAPE:
						done = TRUE;
						break;
					case SDLK_RIGHT:
						mright = TRUE;
						break;
					case SDLK_LEFT:
						mleft = TRUE;
						break;
					case SDLK_UP:
						mup = TRUE;
						break;
					case SDLK_DOWN:
						mdown = TRUE;
						break;
					}

					break;
				case SDL_KEYUP:
					switch (event->key.keysym.sym) {
					case SDLK_RIGHT:
						mright = FALSE;
						break;
					case SDLK_LEFT:
						mleft = FALSE;
						break;
					case SDLK_UP:
						mup = FALSE;
						break;
					case SDLK_DOWN:
						mdown = FALSE;
						break;
					}

					break;
				}
			}

			/*if (mright == TRUE)
				pl_sprite.x += sectomsec(DT) / MOVE_SPEED;
			if (mleft == TRUE)
				pl_sprite.x -= sectomsec(DT) / MOVE_SPEED;
			if (mup == TRUE)
				pl_sprite.y -= sectomsec(DT) / MOVE_SPEED;
			if (mdown == TRUE)
				pl_sprite.y += sectomsec(DT) / MOVE_SPEED;

			pl_sprite.dest_rect->x = pl_sprite.x;
			pl_sprite.dest_rect->y = pl_sprite.y;*/

			/* checks if the frame is ready to render */
			if (render_timer >= (1/TARGET_FRAME_RATE)) {
				if (DEBUG)
					/* increment counter for framerate */
					frms++;

				animate(&SPRITES[PLYR]);

				SDL_UpdateWindowSurface(WINDOW);

				if (SDL_FillRect(SCREEN, NULL, SDL_MapRGB(
								SCREEN->format,
								255, 255, 255))
						!= 0) {
					throw_err(SDL_RECT_ERR);
				}

				/* do not set to zero, remove the accumulated
				 * frame time to avoid skipping */
				render_timer -= (1/TARGET_FRAME_RATE);
			}

			if (DEBUG) {
				if (frmtime >= 1) {
					char fps[LOG_LINE_SIZE];
					snprintf(fps, LOG_LINE_SIZE,
							"FPS: %d", frms);
					logstr(fps);
					frms = 0;
					/* decrement frmtime instead of setting to 0 */
					frmtime--;
				}
			}

			render_timer += DT;

			if (DEBUG)
				frmtime += DT;

			break;
		case PAUSED:
			break;
		case MAIN_MENU:
			break;
		default:
			throw_err(NO_STATE_ERR);
		}

	}
	logstr("Left main game loop");

	free(event);
	SDL_FreeSurface(SPRITES[PLYR].surface);
	return 0;
}
