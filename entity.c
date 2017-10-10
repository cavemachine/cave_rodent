#include "cave_rodent.h"

extern int entities_alives;
extern int entities_active;
extern struct player player;
extern struct entity entity_list[10];
extern char map[MAP_Y][MAP_X];
extern int level;
extern int score;
extern int cronometer;
extern int crono_subcount;
extern int entity_speed;
extern int entity_speed_subcount;
char blockers[] = {'B', 'D', 'E', 'e'};

void create_entity(int y_, int x_) {
    entity_list[entities_alives].x = x_;
    entity_list[entities_alives].y = y_;
    entity_list[entities_alives].alive = true;
    entity_list[entities_alives].active = true;
    map [entity_list[entities_alives].y] [entity_list[entities_alives].x] = 'E';
    entities_active++;
    entities_alives++;  
}
void entity_queue() {
    
    entity_speed_subcount += 1;
    if (entity_speed_subcount == entity_speed) {
	printf("alive : %i ... actives : %i\n", entities_alives, entities_active);
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
	entity_speed_subcount = 0;
    }

    crono_subcount += 1;
    if (crono_subcount == 4) {
	score += 3;
	cronometer -= 1;
	crono_subcount = 0;
    }
    if (cronometer == 0) {
	//create more entities. TODO random location
    }
}
void entity_freedom_check(struct entity *entity) {
    
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
    
    bool moved_lateral = false;
    
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
bool try_lateral(struct entity *entity) {
    int init_ent_y = entity->y;
    int init_ent_x = entity->x;
    if (player.x < entity->x) {
	if (!memchr(blockers, map[entity->y][entity->x - 1], strlen(blockers))) {	    
	    map[entity->y][entity->x] = '0';
	    entity->x -= 1;
	    map[entity->y][entity->x] = 'E';
	}
    } else {
	if (player.x > entity->x) {
	    if (!memchr(blockers, map[entity->y][entity->x + 1], strlen(blockers))) {	
		map[entity->y][entity->x] = '0';
		entity->x += 1;
		map[entity->y][entity->x] = 'E';
	    }
	} 
    }
    if (player.y < entity->y) {
	if (!memchr(blockers, map[entity->y - 1][entity->x], strlen(blockers))) {
	    map[entity->y][entity->x] = '0';
	    entity->y -= 1;
	    map[entity->y][entity->x] = 'E';
	}
    } else {
	if (player.y > entity->y) {
	    if (!memchr(blockers, map[entity->y + 1][entity->x], strlen(blockers))) {
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
	if (!memchr(blockers, map[entity->y - 1][entity->x - 1], strlen(blockers))) {
	    map[entity->y][entity->x] = '0';		    
	    entity->y -= 1;
	    entity->x -= 1;
	    map[entity->y][entity->x] = 'E';
	}
    }
    if (player.y < entity->y && player.x > entity->x) {
	if (!memchr(blockers, map[entity->y - 1][entity->x + 1], strlen(blockers))) {
	    map[entity->y][entity->x] = '0';		    
	    entity->y -= 1;
	    entity->x += 1;
	    map[entity->y][entity->x] = 'E';	
	}
    }
    if (player.y > entity->y && player.x < entity->x) {
      if (!memchr(blockers, map[entity->y + 1][entity->x - 1], strlen(blockers))) {
	    map[entity->y][entity->x] = '0';		    
	    entity->y += 1;
	    entity->x -= 1;
	    map[entity->y][entity->x] = 'E';
	}
    }
    if (player.y > entity->y && player.x > entity->x) {
	if (!memchr(blockers, map[entity->y + 1][entity->x + 1], strlen(blockers))) {
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
	   if (!memchr(blockers, map[entity->y - 1][entity->x + 1], strlen(blockers))) {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y - 1;
		entity->x = entity->x + 1;
		break;
	    }
	}
	if (entity->y + 1 < MAP_Y && entity->x - 1 >= 0) {
	   if (!memchr(blockers, map[entity->y + 1][entity->x - 1], strlen(blockers))) {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y + 1;
		entity->x = entity->x - 1;
		break;
	    }
	}
	break;
    case 'w':
	if (entity->y - 1 >= 0 && entity->x - 1 >= 0) {
      	   if (!memchr(blockers, map[entity->y - 1][entity->x - 1], strlen(blockers))) {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y - 1;
		entity->x = entity->x - 1;
		break;
	    }
	}
	if (entity->y - 1 >= 0 && entity->x + 1 < MAP_X) {
	if (!memchr(blockers, map[entity->y - 1][entity->x + 1], strlen(blockers))) {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y - 1;
		entity->x = entity->x + 1;
		break;
	    }
	}
	break;
    case 'e':
	if (entity->y - 1 >= 0 && entity->x - 1 >= 0) {
	    if (!memchr(blockers, map[entity->y - 1][entity->x - 1], strlen(blockers))) {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y - 1;
		entity->x = entity->x - 1;
		break;
	    }
	}
	if (entity->y + 1 < MAP_Y && entity->x + 1 < MAP_X) {
	    if (!memchr(blockers, map[entity->y + 1][entity->x + 1], strlen(blockers))) {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y + 1;
		entity->x = entity->x + 1;
		break;
	    }
	}
	break;
    case 'd':
	if (entity->y - 1 >= 0 && entity->x + 1 < MAP_X) {
	    if (!memchr(blockers, map[entity->y - 1][entity->x + 1], strlen(blockers))) {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y - 1;
		entity->x = entity->x + 1;
		break;
	    }
	}
	if (entity->y + 1 < MAP_Y && entity->x + 1 < MAP_X) {
	    if (!memchr(blockers, map[entity->y + 1][entity->x + 1], strlen(blockers))) {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y + 1;
		entity->x = entity->x + 1;
		break;
	    }
	}
	break;
    case 'c':
	if (entity->y - 1 >= 0 && entity->x + 1 < MAP_X) {
	    if (!memchr(blockers, map[entity->y - 1][entity->x + 1], strlen(blockers))) {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y - 1;
		entity->x = entity->x + 1;
		break;
	    }
	}
	if (entity->y + 1 < MAP_Y && entity->x - 1 >= 0) {
	    if (!memchr(blockers, map[entity->y + 1][entity->x - 1], strlen(blockers))) {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y + 1;
		entity->x = entity->x - 1;
		break;
	    }
	}
	break;
    case 'x':
	if (entity->y + 1 < MAP_Y && entity->x + 1 < MAP_X) {
	    if (!memchr(blockers, map[entity->y + 1][entity->x + 1], strlen(blockers))) {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y + 1;
		entity->x = entity->x + 1;
		break;
	    }
	}
	if (entity->y + 1 < MAP_Y && entity->x - 1 >= 0) {
	    if (!memchr(blockers, map[entity->y + 1][entity->x - 1], strlen(blockers))) {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y + 1;
		entity->x = entity->x - 1;
		break;
	    }
	}
	break;
    case 'z':
	if (entity->y - 1 >= 0 && entity->x - 1 >= 0) {
	    if (!memchr(blockers, map[entity->y - 1][entity->x - 1], strlen(blockers))) {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y - 1;
		entity->x = entity->x - 1;
		break;     
	    }
	}
	if (entity->y + 1 < MAP_Y && entity->x + 1 < MAP_X) {
	    if (!memchr(blockers, map[entity->y + 1][entity->x + 1], strlen(blockers))) {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y + 1;
		entity->x = entity->x + 1;
		break;     
	    }
	}
	break;
    case 'a':
	if (entity->y + 1 < MAP_Y && entity->x - 1 >= 0) {
	    if (!memchr(blockers, map[entity->y + 1][entity->x - 1], strlen(blockers))) {
		map[entity->y][entity->x] = '0';
		entity->y = entity->y + 1;
		entity->x = entity->x - 1;
		break;
	    }
	}
	if (entity->y - 1 >= 0 && entity->x - 1 >= 0) {
	    if (!memchr(blockers, map[entity->y - 1][entity->x - 1], strlen(blockers))) {
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
void kill_them_all() {
    for (int y = 0; y < MAP_Y; y++) {
	for (int x = 0; x < MAP_X; x++) {
	    if (map[y][x] == 'e') { map[y][x] = 'D'; }
	  
	}
    }
    entities_alives = 0;
    cronometer += 30;
}
