#include "cave_rodent.h"

struct player player;
struct entity entity_list[10];
int entities_active = 0;
int entities_alives = 0;
int level = 1;

char map[MAP_Y][MAP_X] =
{{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
 {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
 {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
 {'0','0','0','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','0','0','0'},
 {'0','0','0','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','0','0','0'},
 {'0','0','0','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','0','0','0'},
 {'0','0','0','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','0','0','0'},
 {'0','0','0','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','0','0','0'},
 {'0','0','0','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','0','0','0'},
 {'0','0','0','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','0','0','0'},
 {'0','0','0','B','B','B','B','B','B','B','0','B','B','B','B','B','B','B','0','0','0'},
 {'0','0','0','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','0','0','0'},
 {'0','0','0','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','0','0','0'},
 {'0','0','0','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','0','0','0'},
 {'0','0','0','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','0','0','0'},
 {'0','0','0','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','0','0','0'},
 {'0','0','0','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','0','0','0'},
 {'0','0','0','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','0','0','0'},
 {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
 {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
 {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}}; 


//----------------INTERFACE
void initialize_timer() {
    struct itimerval it;
    srand(time(NULL));
    it.it_value.tv_sec = 0;
    it.it_value.tv_usec = 999999;
    it.it_interval = it.it_value;
    setitimer(ITIMER_REAL, &it, NULL);
    signal(SIGALRM,entity_queue);
}
void update_screen(SDL_Rect *sprite,
		   SDL_Renderer *renderer,
		   SDL_Texture *player_texture,
		   SDL_Texture *entity_active_texture,
		   SDL_Texture *entity_not_active_texture,
		   SDL_Texture *entity_dead_texture,		   
		   SDL_Texture *button_texture) {
    
    SDL_SetRenderDrawColor(renderer, 129, 122, 8, 255); // background color
    SDL_RenderClear(renderer);
    
    for (int y = 0; y < MAP_Y; y++) {
	for (int x = 0; x < MAP_X; x++) {
	    if (y == 0) { sprite->y = 0; }
	    if (x == 0) { sprite->x = 0; }
	    if (y != 0) { sprite->y = y * SPRITE_SIZE; }
	    if (x != 0) { sprite->x = x * SPRITE_SIZE; }
	    if (map[y][x] == 'P') {
		SDL_RenderCopy(renderer, player_texture, NULL, sprite);	       
	    }
	    if (map[y][x] == 'E') {
		SDL_RenderCopy(renderer, entity_active_texture, NULL, sprite);
	    }
	    if (map[y][x] == 'e') {
		SDL_RenderCopy(renderer, entity_not_active_texture, NULL, sprite);
	    }	    
	    if (map[y][x] == 'B') {
		SDL_RenderCopy(renderer, button_texture, NULL, sprite);
	    }
	    if (map[y][x] == 'D') {
		SDL_RenderCopy(renderer, entity_dead_texture, NULL, sprite);
	    }
	}
    }
    SDL_RenderPresent(renderer);
}
void manage_keys(SDL_Event *event) {
    char move_direction;
    
    //---------------- 'a' key: print board 2d array
    if (event->key.keysym.sym == SDLK_a) { // a: print board 2d array
	for (int i = 0; i < MAP_Y; i++) {
	    printf("\n");
	    for (int j = 0; j < MAP_X; j++) {
		printf("%c",map[i][j]);
	    }
	}
    }
    //----------------- 'b' key: print a summary of entities
    if (event->key.keysym.sym == SDLK_b) { // b: entities summary

	printf("entity1 alive: %i\n", entity_list[0].alive);
      	printf("entity1 active: %i\n", entity_list[0].active);
	printf("entity1 x: %i\n", entity_list[0].x);
      	printf("entity1 y: %i\n", entity_list[0].y);	
	printf("entity2 alive: %i\n", entity_list[1].alive);
      	printf("entity2 active: %i\n", entity_list[1].active);
	printf("entity2 x: %i\n", entity_list[1].x);
      	printf("entity2 y: %i\n", entity_list[1].y);	

    }
    //------------------Arrow keys: player moviment
    if (event->key.keysym.sym == SDLK_DOWN) {
	if (player.y != MAP_Y - 1) {
	    if (map[player.y + 1][player.x] == '0') {
		map[player.y][player.x] = '0';
		player.y += 1;
		map[player.y][player.x] = 'P';
	    } else {
		move_direction = 'd';
		move_block(move_direction);
	    }
	}
    }
    if (event->key.keysym.sym == SDLK_UP) {
	if (player.y != 0) {			
	    if (map[player.y - 1][player.x] == '0') {
		map[player.y][player.x] = '0';
		player.y -= 1;
		map[player.y][player.x] = 'P';
	    } else {
		move_direction = 'u';
		move_block(move_direction);
	    }
	}
    }
    if (event->key.keysym.sym == SDLK_LEFT) {
	if (player.x != 0) {
	    if (map[player.y][player.x - 1] == '0') {
		map[player.y][player.x] = '0';
		player.x -= 1;
		map[player.y][player.x] = 'P';
	    } else {
		move_direction = 'l';
		move_block(move_direction);
	    }
	}
    }
    if (event->key.keysym.sym == SDLK_RIGHT) {
	if (player.x != MAP_X - 1) {			
	    if (map[player.y][player.x + 1] == '0') {
		map[player.y][player.x] = '0';
		player.x += 1;
		map[player.y][player.x] = 'P';
	    } else {
		move_direction = 'r';
		move_block(move_direction);
	    }
	}		    
    }
}
//----------------END INTERFACE 


//----------------MISC
void gotcha() {
    
    /* (TODO) if cat catch the mouse*/
    printf("GOTCHA\n");
}
void new_level(int level_) {
    if (level_ == 1) {
	create_entity(1,4);
	create_entity(18,17);
    }
    if (level_ == 2) {
	create_entity(2,9);
	create_entity(1,6);
    }
}
//----------------END MISC 

 
int main(int argc, char *argv[]) {

    //--------------------- WINDOW INITIALIZATION
    
    SDL_Window* window;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* button_surface = NULL;
    SDL_Texture* button_texture = NULL;
    SDL_Surface* player_surface = NULL;
    SDL_Texture* player_texture = NULL;
    SDL_Surface* entity_active_surface = NULL;
    SDL_Texture* entity_active_texture = NULL;
    SDL_Surface* entity_not_active_surface = NULL;
    SDL_Texture* entity_not_active_texture = NULL;
    SDL_Surface* entity_dead_surface = NULL;
    SDL_Texture* entity_dead_texture = NULL;  
    SDL_Rect sprite;
    
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Rodent",
			      SDL_WINDOWPOS_CENTERED,
			      SDL_WINDOWPOS_CENTERED,
			      SPRITE_SIZE*21,
			      SPRITE_SIZE*21,
			      SDL_WINDOW_SHOWN );
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    
    button_surface = SDL_LoadBMP("img/sprite_block.bmp");
    button_texture = SDL_CreateTextureFromSurface(renderer, button_surface);
    player_surface = SDL_LoadBMP("img/sprite_mouse.bmp");
    player_texture = SDL_CreateTextureFromSurface(renderer, player_surface);
    entity_active_surface = SDL_LoadBMP("img/sprite_cat.bmp");
    entity_active_texture = SDL_CreateTextureFromSurface(renderer, entity_active_surface);
    entity_not_active_surface = SDL_LoadBMP("img/sprite_idle_cat.bmp");
    entity_not_active_texture = SDL_CreateTextureFromSurface(renderer, entity_not_active_surface);
    entity_dead_surface = SDL_LoadBMP("img/sprite_cheese.bmp");
    entity_dead_texture = SDL_CreateTextureFromSurface(renderer, entity_dead_surface);
    
    SDL_FreeSurface(button_surface);
    SDL_FreeSurface(player_surface);
    SDL_FreeSurface(entity_active_surface);
    SDL_FreeSurface(entity_not_active_surface);
    SDL_FreeSurface(entity_dead_surface);    

    //---------------------------- GAME INITIAL SETUP
    
    sprite.w = SPRITE_SIZE;
    sprite.h = SPRITE_SIZE;
    
    player.x = 10;
    player.y = 10;
    map[player.y][player.x] = 'P';
    
    new_level(level);
    initialize_timer();

    //---------------------------- ENTER MAIN LOOP
    
    SDL_bool done = SDL_FALSE;
    while(!done)
	{
	    SDL_Event event;
	    while (SDL_PollEvent(&event)) {
		
		if(event.type == SDL_QUIT) {
		    done = SDL_TRUE;
		}
		if(event.type == SDL_KEYUP) {		    
		    manage_keys(&event);
		}
		
	    }
	    update_screen(&sprite,
			  renderer,
			  player_texture,
			  entity_active_texture,
			  entity_not_active_texture,
			  entity_dead_texture,
			  button_texture);
	    SDL_Delay(50);
	}
    
    SDL_Quit();
    exit( 0 );
}
