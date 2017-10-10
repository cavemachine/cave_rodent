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

//-----------------------VARIABLES
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

SDL_Window* window;
SDL_Renderer* renderer;
    
SDL_Surface* n0_surface;
SDL_Surface* n1_surface;
SDL_Surface* n2_surface;
SDL_Surface* n3_surface;
SDL_Surface* n4_surface;
SDL_Surface* n5_surface;
SDL_Surface* n6_surface;
SDL_Surface* n7_surface;
SDL_Surface* n8_surface;
SDL_Surface* n9_surface;

SDL_Texture* n0_texture;
SDL_Texture* n1_texture;
SDL_Texture* n2_texture;
SDL_Texture* n3_texture;
SDL_Texture* n4_texture;
SDL_Texture* n5_texture;
SDL_Texture* n6_texture;
SDL_Texture* n7_texture;
SDL_Texture* n8_texture;
SDL_Texture* n9_texture;
    
SDL_Surface* button_surface;
SDL_Surface* player_surface;
SDL_Surface* entity_active_surface;
SDL_Surface* entity_not_active_surface;
SDL_Surface* entity_dead_surface;
SDL_Surface* status_surface;
SDL_Surface* status_mouse_surface;
  
SDL_Texture* button_texture;
SDL_Texture* player_texture;
SDL_Texture* entity_active_texture;
SDL_Texture* entity_not_active_texture;
SDL_Texture* entity_dead_texture;
SDL_Texture* status_texture;
SDL_Texture* status_mouse_texture;
     
SDL_Rect sprite;
SDL_Rect status_bar;

struct player player;
struct entity entity_list[10];

int entities_active;
int entities_alives;
int level;
int lifes;
int score;
int cronometer;
int crono_subcount;
int entity_speed; // 4 = 1s ; 3 = 750ms ; 2 = 500 ms ; 1 = 250 ms
int entity_speed_subcount;
bool initial_menu;


//---------------------------FUNCTIONS
void create_entity(int y_, int x_);
void clear_all_entities();
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
void update_screen();
void manage_keys(SDL_Event *event);
void show_initial_menu();
void show_game_over();
void initialize_window();
void initialize_variables();
void update_screen_score();
void update_screen_cronometer();
void update_screen_life();
