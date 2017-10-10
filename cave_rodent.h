#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <string.h>

#define MAP_X 21
#define MAP_Y 21
#define SPRITE_SIZE 20

struct player {
    int x;
    int y;
};
struct entity {
    int x;
    int y;
    bool alive;
    bool active;
};

void create_entity(int y_, int x_);
void entity_find(int mapy, int mapx, int newy, int newx);
void move_block(char move_direction);
void gotcha();
bool try_lateral(struct entity *entity);
void try_diagonal(struct entity *entity);
void try_contour_obstacules(struct entity *entity);
void new_level(int level_);
void kill_them_all();
void entity_freedom_check(struct entity *entity);
void entity_chase(struct entity *entity);
void entity_queue();
void initialize_timer();
void update_screen(SDL_Rect *sprite,
		   SDL_Rect *menu,
		   SDL_Rect *menu_mouse,
		   SDL_Rect *numbers,
		   SDL_Renderer *renderer,
		   SDL_Texture *player_texture,
		   SDL_Texture *entity_active_texture,
		   SDL_Texture *entity_not_active_texture,
		   SDL_Texture *entity_dead_texture,		   
		   SDL_Texture *button_texture,
		   SDL_Texture *menu_texture,
		   SDL_Texture *n0_texture,
		   SDL_Texture *n1_texture,
		   SDL_Texture *n2_texture,
		   SDL_Texture *n3_texture,
		   SDL_Texture *n4_texture,
		   SDL_Texture *n5_texture,
		   SDL_Texture *n6_texture,
		   SDL_Texture *n7_texture,
		   SDL_Texture *n8_texture,
		   SDL_Texture *n9_texture,
		   SDL_Texture *menu_mouse_texture);
void manage_keys(SDL_Event *event, SDL_Renderer *renderer);
void show_initial_menu(SDL_Renderer *renderer);
