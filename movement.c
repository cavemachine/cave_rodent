#include "cave_rodent.h"

extern struct player player;
extern char map[MAP_Y][MAP_X];
extern int entities_alives;
extern struct entity entity_list[10];

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
