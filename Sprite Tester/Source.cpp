#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "Sprite.h"
#include <iostream>
using namespace std;

int main(void)
{
	//variables
	int width = 1200;
	int height = 800;
	bool done = false;
	bool redraw = true;
	const int FPS = 60;
	const int MAX_SPRITES = 4;
	srand(time(NULL));


	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	sprite kirbs[MAX_SPRITES];
	ALLEGRO_TIMER *timer = NULL;

	//program init
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if(!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_image_addon();
	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_set_target_bitmap(al_get_backbuffer(display));
	al_start_timer(timer);
	
	for (int i = 0; i < MAX_SPRITES; i++) {
		kirbs[i].load_animated_sprite(9, width, height);
	}

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//timer event
		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			for (int i = 0; i < MAX_SPRITES; i++) {
				kirbs[i].bouncesprite(width, height);
			}
			for (int i = 0; i < MAX_SPRITES; i++) {
				kirbs[i].Collision(kirbs, MAX_SPRITES, i, width, height);
			}
			redraw = true;
			
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;

		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}

		//rendering block
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false; 
			al_clear_to_color(al_map_rgb(0, 0, 0));
			for (int i = 0; i < MAX_SPRITES; i++) {
				kirbs[i].updatesprite();
			}
			for (int i = 0; i < MAX_SPRITES; i++) {
				kirbs[i].drawSprite(width, height);
			}
			al_flip_display();
		}
	}
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object
	al_destroy_timer(timer);
	return 0;
}