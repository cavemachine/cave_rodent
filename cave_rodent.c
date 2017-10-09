#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>

#define MAP_X 21
#define MAP_Y 21
#define SPRITE_SIZE 20

void entity_chase();

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



void create_entity(int y_, int x_) {
    entity_list[entities_alives].x = x_;
    entity_list[entities_alives].y = y_;
    entity_list[entities_alives].alive = true;
    entity_list[entities_alives].active = true;
    map [entity_list[entities_alives].y] [entity_list[entities_alives].x] = 'E';
    entities_active++;
    entities_alives++;  
}

void entity_find(int mapy, int mapx, int newy, int newx) {
    
    /* find the index of an entity at a give map location.
       if entity is active: move the entity and update its x and y.
       if entity is not active: overwrite entity position with block and destroy entity. */
    
    for (int i = 0; i <= entities_alives; i++) {
	if (entity_list[i].y == mapy && entity_list[i].x == mapx) {
	    if (entity_list[i].active == true) {
		entity_list[i].y = newy;
		entity_list[i].x = newx;
	    } else {
		entity_list[i].alive = false;
		entities_alives--;
	    }
	}
    }
}

void move_block(char move_direction) {

    /* check if player can move blocks; move if can be found an empty square 
       or an inactive entity in the player moviment direction (down, up left or right) */
    
    bool can_move_empty = false;
    bool can_move_inactive = false;
    int y = player.y;
    int x = player.x;
    
    if (move_direction == 'd') {
	while (y < MAP_Y) {
	    if (map[y][player.x] == '0' || map[y][player.x] == 'e') {
		if (map[y][player.x] == '0') { can_move_empty = true; }
	       	if (map[y][player.x] == 'e') { can_move_inactive = true; }
		break;
	    } else {
		y++;
	    }	    
	}
	if (can_move_empty == true) {
	    while (y > player.y + 1) {
		if (map[y - 1][player.x] == 'E') {
		    entity_find(y - 1, player.x, y, player.x);
		}
		map[y][player.x] = map[y - 1][player.x];
		y--;	     
	    }
	    map[player.y][player.x] = '0';
	    player.y += 1;
	    map[player.y][player.x] = 'P';
	}
	if (can_move_inactive == true) {
	    while (y > player.y + 1) {
		if (map[y][player.x] == 'e') {
		    entity_find(y, player.x, y - 1, player.x);
		    map[y][player.x] = map[y - 1][player.x];
		    map[y - 1][player.x] = 'B';
		    y--;
		} else {
		    map[y][player.x] = map[y - 1][player.x];
		    y--;
		}
	    }
	    map[player.y][player.x] = '0';
	    player.y += 1;
	    map[player.y][player.x] = 'P';	    
	}
    }
		    
    if (move_direction == 'u') {
	while (y >= 0) {
	    if (map[y][player.x] == '0' || map[y][player.x] == 'e') {
		if (map[y][player.x] == '0') { can_move_empty = true; }
	       	if (map[y][player.x] == 'e') { can_move_inactive = true; }
		break;
	    } else {
		y--;
	    }
	}
	if (can_move_empty == true) {
	    while (y < player.y - 1) {
		if (map[y + 1][player.x] == 'E') {
		    entity_find(y + 1, player.x, y, player.x);
		}
		map[y][player.x] = map[y + 1][player.x];
		y++;	     
	    }
	    map[player.y][player.x] = '0';
	    player.y -= 1;
	    map[player.y][player.x] = 'P';
	}	  
	if (can_move_inactive == true) {
	    while (y < player.y - 1) {
		if (map[y][player.x] == 'e') {
		    entity_find(y, player.x, y + 1, player.x);
		    map[y][player.x] = map[y + 1][player.x];
		    map[y + 1][player.x] = 'B';
		    y++;
		} else {
		    map[y][player.x] = map[y + 1][player.x];
		    y++;
		}
	    }
	    map[player.y][player.x] = '0';
	    player.y -= 1;
	    map[player.y][player.x] = 'P';	    
	}
    }
    
    if (move_direction == 'l') {
	while (x >= 0) {
	    if (map[player.y][x] == '0' || map[player.y][x] == 'e') {
		if (map[player.y][x] == '0') { can_move_empty = true; }
	       	if (map[player.y][x] == 'e') { can_move_inactive = true; }
		break;
	    } else {
		x--;
	    }
	}
	if (can_move_empty == true) {
	    while (x < player.x - 1) {
		if (map[player.y][x + 1] == 'E') {
		    entity_find(player.y, x + 1, player.y, x);		    
		}
		map[player.y][x] = map[player.y][x + 1];
		x++;	     
	    }
	    map[player.y][player.x] = '0';
	    player.x -= 1;
	    map[player.y][player.x] = 'P';
	}
	if (can_move_inactive == true) {
	    while (x < player.x - 1) {
		if (map[player.y][x] == 'e') {
		    entity_find(player.y, x, player.y, x + 1);
		    map[player.y][x] = map[player.y][x + 1];
		    map[player.y][x + 1] = '0';
		    x++;
		} else {
		    map[player.y][x] = map[player.y][x + 1];
		    x++;
		}
	    }
	    map[player.y][player.x] = '0';
	    player.x -= 1;
	    map[player.y][player.x] = 'P';	    
	}       
    }
    
    if (move_direction == 'r') {
	while (x < MAP_X) {
	    if (map[player.y][x] == '0' || map[player.y][x] == 'e') {
		if (map[player.y][x] == '0') { can_move_empty = true; }
	       	if (map[player.y][x] == 'e') { can_move_inactive = true; }
		break;
	    } else {
		x++;
	    }
	}
	if (can_move_empty == true) {
	    while (x > player.x + 1) {
		if (map[player.y][x - 1] == 'E') {
		    entity_find(player.y, x - 1, player.y, x);		    
		}
		map[player.y][x] = map[player.y][x - 1];
		x--;	     
	    }
	    map[player.y][player.x] = '0';
	    player.x += 1;
	    map[player.y][player.x] = 'P';
	}
	if (can_move_inactive == true) {
	    while (x > player.x + 1) {
		if (map[player.y][x] == 'e') {
		    entity_find(player.y, x, player.y, x + 1);
		    map[player.y][x] = map[player.y][x - 1];
		    map[player.y][x - 1] = '0';
		    x--;
		} else {
		    map[player.y][x] = map[player.y][x - 1];
		    x--;
		}
	    }
	    map[player.y][player.x] = '0';
	    player.x += 1;
	    map[player.y][player.x] = 'P';	    
	}      
    }
}

void gotcha() {
    
    /* (TODO) if cat catch the mouse*/
    printf("GOTCHA\n");
}

bool try_lateral(struct entity *entity) {

    int init_ent_y = entity->y;
    int init_ent_x = entity->x;

    if (player.x < entity->x) {
	if (map[entity->y][entity->x - 1] != 'B') {
	    
	    map[entity->y][entity->x] = '0';
	    entity->x -= 1;
	    map[entity->y][entity->x] = 'E';
	}
    } else {
	if (player.x > entity->x) {
	    if (map[entity->y][entity->x + 1] != 'B') {
		map[entity->y][entity->x] = '0';
		entity->x += 1;
		map[entity->y][entity->x] = 'E';
	    }
	} 
    }
    if (player.y < entity->y) {
      	if (map[entity->y - 1][entity->x] != 'B') {
	    map[entity->y][entity->x] = '0';
	    entity->y -= 1;
	    map[entity->y][entity->x] = 'E';
	}
    } else {
	if (player.y > entity->y) {
	    if (map[entity->y + 1][entity->x] != 'B') {
		map[entity->y][entity->x] = '0';		    
		entity->y += 1;
		map[entity->y][entity->x] = 'E';
	    }
	}
    }
    if (init_ent_x != entity->x || init_ent_y != entity->y) {
	return(true);
    } else {
	return(false);
    }
}

void try_diagonal(struct entity *entity) {
    if (player.y < entity->y && player.x < entity->x) {
	if (map [entity->y - 1][entity->x - 1] != 'B') {
	    map[entity->y][entity->x] = '0';		    
	    entity->y -= 1;
	    entity->x -= 1;
	    map[entity->y][entity->x] = 'E';
	}
    }
    if (player.y < entity->y && player.x > entity->x) {
	if (map [entity->y - 1][entity->x + 1] != 'B') {
	    map[entity->y][entity->x] = '0';		    
	    entity->y -= 1;
	    entity->x += 1;
	    map[entity->y][entity->x] = 'E';
	
	}
    }
    if (player.y > entity->y && player.x < entity->x) {
	if (map [entity->y + 1][entity->x - 1] != 'B') {
	    map[entity->y][entity->x] = '0';		    
	    entity->y += 1;
	    entity->x -= 1;
	    map[entity->y][entity->x] = 'E';
	}
    }
    if (player.y > entity->y && player.x > entity->x) {
	if (map [entity->y + 1][entity->x + 1] != 'B') {
	    map[entity->y][entity->x] = '0';		    
	    entity->y += 1;
	    entity->x += 1;
	    map[entity->y][entity->x] = 'E';
	}
    }
}

void try_contour_obstacules(struct entity *entity) {

    int init_x = entity->x;
    int init_y = entity->y;
    
    char direction;
    // use q,w,e,a,d,z,x,c for cardinal representation;
    if (entity->x > player.x && entity->y > player.y) { direction = 'q'; }	
    if (entity->x == player.x && entity->y > player.y) { direction = 'w'; }
    if (entity->x < player.x && entity->y > player.y) { direction = 'e'; }
    if (entity->x < player.x && entity->y == player.y) { direction = 'd'; }
    if (entity->x < player.x && entity->y < player.y) { direction = 'c'; }
    if (entity->x == player.x && entity->y < player.y) { direction = 'x'; }
    if (entity->x > player.x && entity->y < player.y) { direction = 'z'; }
    if (entity->x > player.x && entity->y == player.y) { direction = 'a'; }

    switch (direction) {
    case 'q':
	if (entity->y - 1 >= 0 && entity->x + 1 < MAP_X) {
	    if (map[entity->y - 1][entity->x + 1] != 'B') {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y - 1;
		entity->x = entity->x + 1;
		break;
	    }
	}
	if (entity->y + 1 < MAP_Y && entity->x - 1 >= 0) {
	    if (map[entity->y + 1][entity->x - 1] != 'B') {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y + 1;
		entity->x = entity->x - 1;
		break;
	    }
	}
	break;
    case 'w':
	if (entity->y - 1 >= 0 && entity->x - 1 >= 0) {
	    if (map[entity->y - 1][entity->x - 1] != 'B') {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y - 1;
		entity->x = entity->x - 1;
		break;
	    }
	}
	if (entity->y - 1 >= 0 && entity->x + 1 < MAP_X) {
	    if (map[entity->y - 1][entity->x + 1] != 'B') {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y - 1;
		entity->x = entity->x + 1;
		break;
	    }
	}
	break;
    case 'e':
	if (entity->y - 1 >= 0 && entity->x - 1 >= 0) {
	    if (map[entity->y - 1][entity->x - 1] != 'B') {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y - 1;
		entity->x = entity->x - 1;
		break;
	    }
	}
	if (entity->y + 1 < MAP_Y && entity->x + 1 < MAP_X) {
	    if (map[entity->y + 1][entity->x + 1] != 'B') {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y + 1;
		entity->x = entity->x + 1;
		break;
	    }
	}
	break;
    case 'd':
	if (entity->y - 1 >= 0 && entity->x + 1 < MAP_X) {
	    if (map[entity->y - 1][entity->x + 1] != 'B') {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y - 1;
		entity->x = entity->x + 1;
		break;
	    }
	}
	if (entity->y + 1 < MAP_Y && entity->x + 1 < MAP_X) {
	    if (map[entity->y + 1][entity->x + 1] != 'B') {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y + 1;
		entity->x = entity->x + 1;
		break;
	    }
	}
	break;
    case 'c':
	if (entity->y - 1 >= 0 && entity->x + 1 < MAP_X) {
	    if (map[entity->y - 1][entity->x + 1] != 'B') {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y - 1;
		entity->x = entity->x + 1;
		break;
	    }
	}
	if (entity->y + 1 < MAP_Y && entity->x - 1 >= 0) {
	    if (map[entity->y + 1][entity->x - 1] != 'B') {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y + 1;
		entity->x = entity->x - 1;
		break;
	    }
	}
	break;
    case 'x':
	if (entity->y + 1 < MAP_Y && entity->x + 1 < MAP_X) {
	    if (map[entity->y + 1][entity->x + 1] != 'B') {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y + 1;
		entity->x = entity->x + 1;
		break;
	    }
	}
	if (entity->y + 1 < MAP_Y && entity->x - 1 >= 0) {
	    if (map[entity->y + 1][entity->x - 1] != 'B') {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y + 1;
		entity->x = entity->x - 1;
		break;
	    }
	}
	break;
    case 'z':
	if (entity->y - 1 >= 0 && entity->x - 1 >= 0) {
	    if (map[entity->y - 1][entity->x - 1] != 'B') {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y - 1;
		entity->x = entity->x - 1;
		break;     
	    }
	}
	if (entity->y + 1 < MAP_Y && entity->x + 1 < MAP_X) {
	    if (map[entity->y + 1][entity->x + 1] != 'B') {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y + 1;
		entity->x = entity->x + 1;
		break;     
	    }
	}
	break;
    case 'a':
	if (entity->y + 1 < MAP_Y && entity->x - 1 >= 0) {
	    if (map[entity->y + 1][entity->x - 1] != 'B') {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y + 1;
		entity->x = entity->x - 1;
		break;
	    }
	}
	if (entity->y - 1 >= 0 && entity->x - 1 >= 0) {
	    if (map[entity->y - 1][entity->x - 1] != 'B') {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y - 1;
		entity->x = entity->x - 1;
		break;     
	    }
	}
	break;
	
    }
    if (init_x != entity->x || init_y != entity->y) {
	map[entity->y][entity->x] = 'E';
    }
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

void kill_them_all() {
    for (int y = 0; y < MAP_Y; y++) {
	for (int x = 0; x < MAP_X; x++) {
	    if (map[y][x] == 'e') { map[y][x] = 'D'; }
	  
	}
    }
    entities_alives = 0;
}

bool entity_freedom_check(struct entity *entity) {
    
    printf("entity_func\n");
    bool entity_free = false;
    for (int around_y = entity->y - 1; around_y <= entity->y + 1; around_y++) {
	for (int around_x = entity->x - 1; around_x <= entity->x + 1; around_x++) {
	    if (around_y == entity->y && around_x == entity->x) {
		continue;
	    } else {
		if (map[around_y][around_x] != 'B' &&
		    map[around_y][around_x] != 'E' &&
		    around_x >= 0 &&
		    around_x < MAP_X &&
		    around_y >= 0 &&
		    around_y < MAP_Y) {
		    
		    entity_free = true;
		}
	    }
	}
    }
    if (entity_free == true) {
	if (entity->active == false && entity->alive == true) {
	    entity->active = true;
	    entities_active++;
	    map[entity->y][entity->x] = 'E';
	}
    } else {
	if (entity->active == true) {
	    entity->active = false;
	    entities_active--;
	    map[entity->y][entity->x] = 'e';
	    if (entities_active == 0) {
		kill_them_all();
	    }
	}
    }
    if (entity->active == true && entity->alive == true) {
	entity_chase(entity);
    }

}
void entity_chase(struct entity *entity) {
 
    /* try to move using north, south, east, west directions toward the player    
       if not possible (obstacules), try NE, NW, SE, SW directions
       if none was possible so far, try to contour obstacle; */
 	
    int initial_entity_x = entity->x;
    int initial_entity_y = entity->y;
    
    bool random_moved = false;
    bool moved_lateral = false;
    bool moved_diagonal = false;
	
    moved_lateral = try_lateral(entity);

    if (moved_lateral == false) {
	try_diagonal(entity);
    }

    if (initial_entity_x == entity->x && initial_entity_y == entity->y) {
	try_contour_obstacules(entity);
    }
        
    if (player.x == entity->x && player.y == entity->y) {
	gotcha();
    }
}

void entity_queue() {
    if (entities_alives > 0) {
	for (int visitor = 0; visitor <= entities_alives; visitor++) {
	    if (entity_list[visitor].alive == true) {		
		entity_freedom_check(&entity_list[visitor]);
	    }
	}
    } else {
	level++;
	new_level(level);
    }
    
    printf("alive : %i ... actives : %i\n", entities_alives, entities_active);
}

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
