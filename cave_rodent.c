#include "cave_rodent.h"


const char map_1[MAP_Y][MAP_X] =
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

char map[MAP_Y][MAP_X];

//----------------INTERFACE

void show_initial_menu() {
    
	initialize_timer(0);
	SDL_Surface* initial_menu_surface = NULL;
	SDL_Texture* initial_menu_texture = NULL;
	initial_menu_surface      = SDL_LoadBMP("img/sprite_setup.bmp");
	initial_menu_texture      = SDL_CreateTextureFromSurface(renderer,
								 initial_menu_surface);
	SDL_FreeSurface(initial_menu_surface);
	
	SDL_Rect initial_menu_rect;	
	initial_menu_rect.h = 118;
	initial_menu_rect.w = 299;
	initial_menu_rect.x = 80;
	initial_menu_rect.y = 40;
	SDL_RenderCopy(renderer, initial_menu_texture, NULL, &initial_menu_rect);
	
	SDL_Rect marker_speed;
	marker_speed.h = 15;
	marker_speed.w = 85;
	marker_speed.x = 200;
	marker_speed.y = 67;
	
	SDL_Rect marker_map;
	marker_map.h = 15;
	marker_map.w = 75;
	marker_map.x = 290;
	marker_map.y = 70;
	
	SDL_RenderDrawRect(renderer, &marker_speed);
	SDL_RenderDrawRect(renderer, &marker_map);	
	SDL_RenderPresent(renderer);
	
	SDL_bool done = SDL_FALSE;
	while(!done) {
	    SDL_Event event;
	    while (SDL_PollEvent(&event)) {		
		if(event.type == SDL_QUIT) {
		    done = SDL_TRUE;
		}
		if(event.type == SDL_KEYUP) {
		    if (event.key.keysym.sym == SDLK_n) {
			new_level(level);
			initialize_timer(250000);
			done = SDL_TRUE;	       	   
		    }
		    if (event.key.keysym.sym == SDLK_1) {
		       	SDL_RenderCopy(renderer, initial_menu_texture,
				       NULL, &initial_menu_rect);
			marker_speed.h = 15;
			marker_speed.w = 85;
			marker_speed.x = 200;
			marker_speed.y = 67;
			SDL_RenderDrawRect(renderer, &marker_speed);
			SDL_RenderDrawRect(renderer, &marker_map);
			SDL_RenderPresent(renderer);			
		    }
		    if (event.key.keysym.sym == SDLK_2) {
			SDL_RenderCopy(renderer, initial_menu_texture,
				       NULL, &initial_menu_rect);
			marker_speed.h = 15;
			marker_speed.w = 85;
			marker_speed.x = 200;
			marker_speed.y = 82;
			SDL_RenderDrawRect(renderer, &marker_speed);
			SDL_RenderDrawRect(renderer, &marker_map);
			SDL_RenderPresent(renderer);			
		    }
		    if (event.key.keysym.sym == SDLK_3) {
			SDL_RenderCopy(renderer, initial_menu_texture,
				       NULL, &initial_menu_rect);
			marker_speed.h = 15;
			marker_speed.w = 85;
			marker_speed.x = 200;
			marker_speed.y = 95;			
			SDL_RenderDrawRect(renderer, &marker_speed);
			SDL_RenderDrawRect(renderer, &marker_map);
			SDL_RenderPresent(renderer);			
		    }
		    if (event.key.keysym.sym == SDLK_a) {
			SDL_RenderCopy(renderer, initial_menu_texture,
				       NULL, &initial_menu_rect);
			marker_map.h = 15;
			marker_map.w = 75;
			marker_map.x = 290;
			marker_map.y = 70;
			SDL_RenderDrawRect(renderer, &marker_speed);
			SDL_RenderDrawRect(renderer, &marker_map);
			SDL_RenderPresent(renderer);			
		    }
		    if (event.key.keysym.sym == SDLK_b) {
			SDL_RenderCopy(renderer, initial_menu_texture,
				       NULL, &initial_menu_rect);
			marker_map.h = 15;
			marker_map.w = 75;
			marker_map.x = 290;
			marker_map.y = 82;
			SDL_RenderDrawRect(renderer, &marker_speed);
			SDL_RenderDrawRect(renderer, &marker_map);
			SDL_RenderPresent(renderer);			
		    }
		    if (event.key.keysym.sym == SDLK_c) {
			SDL_RenderCopy(renderer, initial_menu_texture,
				       NULL, &initial_menu_rect);
			marker_map.h = 15;
			marker_map.w = 75;
			marker_map.x = 290;
			marker_map.y = 95;
			SDL_RenderDrawRect(renderer, &marker_speed);
			SDL_RenderDrawRect(renderer, &marker_map);
			SDL_RenderPresent(renderer);			
		    }		    
		}
	    }
	    SDL_Delay(50);	
	}
}

void show_game_over() {
    
    initialize_timer(0);
    SDL_Surface* gameover_surface = NULL;
    SDL_Texture* gameover_texture = NULL;
    gameover_surface      = SDL_LoadBMP("img/sprite_gameover.bmp");
    gameover_texture      = SDL_CreateTextureFromSurface(renderer, gameover_surface);
    SDL_FreeSurface(gameover_surface);
	
    SDL_Rect gameover_rect;	
    gameover_rect.h = 118;
    gameover_rect.w = 299;
    gameover_rect.x = 80;
    gameover_rect.y = 40;
    SDL_RenderCopy(renderer, gameover_texture, NULL, &gameover_rect);

    	SDL_bool done = SDL_FALSE;
	while(!done) {
	    SDL_Event event;
	    while (SDL_PollEvent(&event)) {		
		if(event.type == SDL_QUIT) {
		    done = SDL_TRUE;
		}
		if(event.type == SDL_KEYUP) {
		    if (event.key.keysym.sym == SDLK_n) {
			lifes = 3;
			new_level(level);
			initialize_timer(250000);
			done = SDL_TRUE;	       	   
		    }
		    if (event.key.keysym.sym == SDLK_q) {
			SDL_Quit();
			exit( 0 );	       	   
		    }
		}
	    }
	    SDL_Delay(50);
	    SDL_RenderPresent(renderer);
	}
}

void new_level(int level_) {
    clear_all_entities();
    entities_active = 0;
    entities_alives = 0;
    lifes = 3;
    score = 0;
    cronometer = 180;
    crono_subcount = 0;
    entity_speed_subcount = 0;
    
    if (level_ == 1) {
	memcpy(map,map_1, (sizeof(char)*MAP_Y*MAP_X));    
    	create_entity(1,4);
	create_entity(18,17);
    }
    if (level_ == 2) {
	create_entity(2,9);
	create_entity(1,6);
    }
    
    player.x = 10;
    player.y = 10;
    map[player.y][player.x] = 'P';
}

void gotcha() {

    printf("GOTCHA\n");
    lifes -= 1;
}

void initialize_window() {
    
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Rodent",
			      SDL_WINDOWPOS_CENTERED,
			      SDL_WINDOWPOS_CENTERED,
			      SPRITE_SIZE*21,
			      SPRITE_SIZE*23,
			      SDL_WINDOW_SHOWN );
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    
    button_surface            = SDL_LoadBMP("img/sprite_block.bmp");
    player_surface            = SDL_LoadBMP("img/sprite_mouse.bmp");
    entity_active_surface     = SDL_LoadBMP("img/sprite_cat.bmp");
    entity_not_active_surface = SDL_LoadBMP("img/sprite_idle_cat.bmp");
    entity_dead_surface       = SDL_LoadBMP("img/sprite_cheese.bmp");
    status_surface            = SDL_LoadBMP("img/sprite_menu.bmp");
    status_mouse_surface      = SDL_LoadBMP("img/sprite_menu_mouse.bmp");
    
    button_texture            = SDL_CreateTextureFromSurface(renderer, button_surface);
    player_texture            = SDL_CreateTextureFromSurface(renderer, player_surface);
    entity_active_texture     = SDL_CreateTextureFromSurface(renderer, entity_active_surface);
    entity_not_active_texture = SDL_CreateTextureFromSurface(renderer, entity_not_active_surface);
    entity_dead_texture       = SDL_CreateTextureFromSurface(renderer, entity_dead_surface);
    status_texture            = SDL_CreateTextureFromSurface(renderer, status_surface);
    status_mouse_texture      = SDL_CreateTextureFromSurface(renderer, status_mouse_surface);
    
    n0_surface = SDL_LoadBMP("img/fonts/0.bmp");
    n1_surface = SDL_LoadBMP("img/fonts/1.bmp");
    n2_surface = SDL_LoadBMP("img/fonts/2.bmp");
    n3_surface = SDL_LoadBMP("img/fonts/3.bmp");
    n4_surface = SDL_LoadBMP("img/fonts/4.bmp");
    n5_surface = SDL_LoadBMP("img/fonts/5.bmp");
    n6_surface = SDL_LoadBMP("img/fonts/6.bmp");
    n7_surface = SDL_LoadBMP("img/fonts/7.bmp");
    n8_surface = SDL_LoadBMP("img/fonts/8.bmp");
    n9_surface = SDL_LoadBMP("img/fonts/9.bmp");

    n0_texture = SDL_CreateTextureFromSurface(renderer, n0_surface);
    n1_texture = SDL_CreateTextureFromSurface(renderer, n1_surface);
    n2_texture = SDL_CreateTextureFromSurface(renderer, n2_surface);
    n3_texture = SDL_CreateTextureFromSurface(renderer, n3_surface);
    n4_texture = SDL_CreateTextureFromSurface(renderer, n4_surface);
    n5_texture = SDL_CreateTextureFromSurface(renderer, n5_surface);
    n6_texture = SDL_CreateTextureFromSurface(renderer, n6_surface);
    n7_texture = SDL_CreateTextureFromSurface(renderer, n7_surface);
    n8_texture = SDL_CreateTextureFromSurface(renderer, n8_surface);
    n9_texture = SDL_CreateTextureFromSurface(renderer, n9_surface);

    SDL_FreeSurface(n0_surface);
    SDL_FreeSurface(n1_surface);
    SDL_FreeSurface(n2_surface);
    SDL_FreeSurface(n3_surface);
    SDL_FreeSurface(n4_surface);
    SDL_FreeSurface(n5_surface);
    SDL_FreeSurface(n6_surface);
    SDL_FreeSurface(n7_surface);
    SDL_FreeSurface(n8_surface);
    SDL_FreeSurface(n9_surface);  
    SDL_FreeSurface(button_surface);
    SDL_FreeSurface(player_surface);
    SDL_FreeSurface(entity_active_surface);
    SDL_FreeSurface(entity_not_active_surface);
    SDL_FreeSurface(entity_dead_surface);
    SDL_FreeSurface(status_surface);
    SDL_FreeSurface(status_mouse_surface); 
}

void initialize_variables() {

    entities_active = 0;
    entities_alives = 0;
    level = 1;
    lifes = 3;
    score = 0;
    cronometer = 180;
    crono_subcount = 0;
    entity_speed = 4; // 4 = 1s ; 3 = 750ms ; 2 = 500 ms ; 1 = 250 ms
    entity_speed_subcount = 0;

    sprite.w = SPRITE_SIZE;
    sprite.h = SPRITE_SIZE;
    status_bar.w = 420;
    status_bar.h = 40;
    status_bar.x = 0;
    status_bar.y = 420; 


    memcpy(map,map_1, sizeof(char)*400);    
    player.x = 10;
    player.y = 10;
    map[player.y][player.x] = 'P';

    initial_menu = true;
}

void initialize_timer(int speed) {
    struct itimerval it;
    srand(time(NULL));
    it.it_value.tv_sec = 0;
    it.it_value.tv_usec = speed;
    it.it_interval = it.it_value;
    setitimer(ITIMER_REAL, &it, NULL);
    signal(SIGALRM,entity_queue);
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
    if (event->key.keysym.sym == SDLK_b) { 

	printf("entity1 alive: %i\n", entity_list[0].alive);
      	printf("entity1 active: %i\n", entity_list[0].active);
	printf("entity1 x: %i\n", entity_list[0].x);
      	printf("entity1 y: %i\n", entity_list[0].y);	
	printf("entity2 alive: %i\n", entity_list[1].alive);
      	printf("entity2 active: %i\n", entity_list[1].active);
	printf("entity2 x: %i\n", entity_list[1].x);
      	printf("entity2 y: %i\n", entity_list[1].y);	
    }
    
    //------------------ 'm' key: initial menu
        if (event->key.keysym.sym == SDLK_m) { 
	    show_initial_menu(renderer);
    }
	
    //------------------Arrow keys: player moviment
    char map_element;
    if (event->key.keysym.sym == SDLK_DOWN) {
	map_element = map[player.y + 1][player.x];
	if (player.y != MAP_Y - 1) {
	    if (map_element == '0' || map_element == 'D') {
		map[player.y][player.x] = '0';
		player.y += 1;
		map[player.y][player.x] = 'P';
		if (map_element == 'D') { score += 100; }
	    } else {
		move_direction = 'd';
		move_block(move_direction);
	    }
	}
    }
    if (event->key.keysym.sym == SDLK_UP) {
	map_element = map[player.y - 1][player.x];
	if (player.y != 0) {			
	    if (map_element == '0' || map_element == 'D') {
		map[player.y][player.x] = '0';
		player.y -= 1;
		map[player.y][player.x] = 'P';
		if (map_element == 'D') { score += 100; }		
	    } else {
		move_direction = 'u';
		move_block(move_direction);
	    }
	}
    }
    if (event->key.keysym.sym == SDLK_LEFT) {
	map_element = map[player.y][player.x - 1];
	if (player.x != 0) {
	    if (map_element == '0' || map_element == 'D') {
		map[player.y][player.x] = '0';
		player.x -= 1;
		map[player.y][player.x] = 'P';
		if (map_element == 'D') { score += 100; }
	    } else {
		move_direction = 'l';
		move_block(move_direction);
	    }
	}
    }
    if (event->key.keysym.sym == SDLK_RIGHT) {
	map_element = map[player.y][player.x + 1];	
	if (player.x != MAP_X - 1) {			
	    if (map_element == '0' || map_element == 'D') {
		map[player.y][player.x] = '0';
		player.x += 1;
		map[player.y][player.x] = 'P';
		if (map_element == 'D') { score += 100; }		
	    } else {
		move_direction = 'r';
		move_block(move_direction);
	    }
	}		    
    }
}

void update_screen(){
    	 
    SDL_SetRenderDrawColor(renderer, 168, 168, 87, 255); // background color
    SDL_RenderClear(renderer);
    
    for (int y = 0; y < MAP_Y; y++) {
	for (int x = 0; x < MAP_X; x++) {
	    if (y == 0) { sprite.y = 0; }
	    if (x == 0) { sprite.x = 0; }
	    if (y != 0) { sprite.y = y * SPRITE_SIZE; }
	    if (x != 0) { sprite.x = x * SPRITE_SIZE; }
	    if (map[y][x] == 'P') {
		SDL_RenderCopy(renderer, player_texture, NULL, &sprite);	       
	    }
	    if (map[y][x] == 'E') {
		SDL_RenderCopy(renderer, entity_active_texture, NULL, &sprite);
	    }
	    if (map[y][x] == 'e') {
		SDL_RenderCopy(renderer, entity_not_active_texture, NULL, &sprite);
	    }	    
	    if (map[y][x] == 'B') {
		SDL_RenderCopy(renderer, button_texture, NULL, &sprite);
	    }
	    if (map[y][x] == 'D') {
		SDL_RenderCopy(renderer, entity_dead_texture, NULL, &sprite);
	    }
	}
    }

    SDL_RenderCopy(renderer, status_texture, NULL, &status_bar);
    
    update_screen_score();
    update_screen_cronometer();
    update_screen_life();
    
    SDL_RenderPresent(renderer);
    
    if (lifes == 0) { show_game_over(renderer); }
    if (initial_menu == true) {
	show_initial_menu(renderer);
	initial_menu = false;
    }
}
void update_screen_life() {

    SDL_Rect status_mouse;
    status_mouse.w = 15;
    status_mouse.h = 15;
    status_mouse.y = 430;
    status_mouse.x = 50;
    // initial_x = menu_mouse->x;
    
    int lifes_count = lifes;
    while (lifes_count > 0) {
	SDL_RenderCopy(renderer, status_mouse_texture, NULL, &status_mouse);
	status_mouse.x -= 15;
	lifes_count -= 1;
    }
}
void update_screen_score() {
   
    SDL_Rect numbers;
    numbers.w = 12;
    numbers.h = 12;
    
    SDL_Texture *tmp_texture;
    int initial_x = 400;
    int digit;
    numbers.y = 440;
    
    int score_digits = score;
    while (score_digits > 0) {	
	digit = score_digits % 10;	
	numbers.x = initial_x;
	switch (digit) {
	case 0:
	    tmp_texture = n0_texture;
	    break;
	case 1:
	    tmp_texture = n1_texture;
	    break;
	case 2:
	    tmp_texture = n2_texture;
	    break;
	case 3:
	    tmp_texture = n3_texture;
	    break;
	case 4:
	    tmp_texture = n4_texture;
	    break;
	case 5:
	    tmp_texture = n5_texture;
	    break;
	case 6:
	    tmp_texture = n6_texture;
	    break;
	case 7:
	    tmp_texture = n7_texture;
	    break;
	case 8:
	    tmp_texture = n8_texture;
	    break;
	case 9:
	    tmp_texture = n9_texture;
	    break;
	}
	    
	SDL_RenderCopy(renderer, tmp_texture, NULL, &numbers);
	score_digits /= 10;
	initial_x -= 12;
    }
}
void update_screen_cronometer() {
    
    SDL_Texture *tmp_texture;
    int initial_x = 210;

    SDL_Rect numbers;
    numbers.w = 12;
    numbers.h = 12;
    numbers.y = 440;

    int cronometer_digits = cronometer;
    
    while (cronometer_digits > 0) {
	
	int digit = cronometer_digits % 10;	
	numbers.x = initial_x;
	switch (digit) {
	case 0:
	    tmp_texture = n0_texture;
	    break;
	case 1:
	    tmp_texture = n1_texture;
	    break;
	case 2:
	    tmp_texture = n2_texture;
	    break;
	case 3:
	    tmp_texture = n3_texture;
	    break;
	case 4:
	    tmp_texture = n4_texture;
	    break;
	case 5:
	    tmp_texture = n5_texture;
	    break;
	case 6:
	    tmp_texture = n6_texture;
	    break;
	case 7:
	    tmp_texture = n7_texture;
	    break;
	case 8:
	    tmp_texture = n8_texture;
	    break;
	case 9:
	    tmp_texture = n9_texture;
	    break;
	}
	    
	SDL_RenderCopy(renderer, tmp_texture, NULL, &numbers);
	cronometer_digits /= 10;
	initial_x -= 12;
    }
}

int main(int argc, char *argv[]) {
    
    initialize_window();

    initialize_variables();
    

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
	    
	    update_screen();
	    
	    SDL_Delay(10);
	}
    
    SDL_Quit();
    exit( 0 );
}
