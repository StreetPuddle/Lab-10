#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>
#include "Sprite.h"

#include <iostream>
using namespace std;

void sprite::drawSprite(int WIDTH, int HEIGHT)
{

	ALLEGRO_BITMAP* currentFrame = image[curframe];

	if (SpinningSprite) {
		float cx = al_get_bitmap_width(currentFrame) / 2.0f;
		float cy = al_get_bitmap_height(currentFrame) / 2.0f;
		al_draw_rotated_bitmap(currentFrame, cx, cy, x + cx, y + cy, angle, 0);
	}
	else if(ScaredSprite && CollisionIsTrue && (al_get_time() - timeOfCollision < 3.0)) {
		al_draw_tinted_bitmap(currentFrame, scaredColor, x, y, 0);
	}
	else if (BabySprite) {

	}
	else if (FreezeSprite) {

	}
	
	CollisionIsTrue = false;
}

void sprite::updatesprite()
{
	//update x position
	if (++xcount > xdelay)
	{
		xcount = 0;
		x += xspeed;
	}

	//update y position
	if (++ycount > ydelay)
	{
		ycount = 0;
		y += yspeed;
	}


	if (framecount++ > framedelay)
	{
		framecount = 0;
		curframe++;
		if (curframe >= maxframe)
			curframe = 0;
	}

	if (SpinningSprite) {
		angle += 0.1f;
	}
}

void sprite::bouncesprite(int SCREEN_W, int SCREEN_H)
{
	//simple screen bouncing behavior
	if (x < 0)
	{
		x = 0;
		xspeed = rand() % 2 + 4;
		animdir *= -1;
	}

	else if (x > SCREEN_W - width)
	{
		x = SCREEN_W - width;
		xspeed = rand() % 2 - 6;
		animdir *= -1;
	}

	if (y < 0)
	{
		y = 0;
		yspeed = rand() % 2 + 4;
		animdir *= -1;
	}

	else if (y > SCREEN_H - height)
	{
		y = SCREEN_H -  height;
		yspeed = rand() % 2 - 6;
		animdir *= -1;
	}

}

void sprite::load_animated_sprite(int size)
{
	//load the animated sprite
	char s[80];
	maxframe=size;
	scaredColor = al_map_rgb(255, 255, 255); // no tint
	angle = 0;
	timeOfCollision = 0;
	CollisionIsTrue = false;
	setSpecialAbility();
	for (int n=0; n<size; n++)
	{
		sprintf_s(s,"kirbs%d.png",n);
		image[n] = al_load_bitmap(s);
		if (!image[n]) {
			al_show_native_message_box(nullptr, "Error", "File error", "Could not load sprite", 0, 0);
			exit(1);
		}
		//al_convert_mask_to_alpha(image[n], al_map_rgb(255, 255, 255));
	}  
	width=al_get_bitmap_width(image[0]);
	height=al_get_bitmap_height(image[0]);
	curframe = 0;
	framedelay = 5;
	framecount = 0;


}

sprite::~sprite()
{
	for(int i = 0; i < maxframe; i++)
		al_destroy_bitmap(image[i]);
}

void  sprite::setSpecialAbility() {
	int rng = rand() % 4;
	if (rng == 0) {
		SpinningSprite = true;
	}
	else if (rng == 1) {
		ScaredSprite = true;
	}
	else if (rng == 2) {
		BabySprite = true;
	}
	else if (rng == 3) {
		FreezeSprite = true;
	}
}

void sprite::Collision(sprite Sprites[], int cSize, int me, int WIDTH, int HEIGHT) {
	for (int i = 0; i < cSize; i++) {
		if (i != me) {
			if (x >= Sprites[i].getX() - width && x <= Sprites[i].getX() + width) {
				if (y >= Sprites[i].getY() - height && y <= Sprites[i].getY() + height) {
					
					CollisionIsTrue = true;
					timeOfCollision = al_get_time();
					x = rand() % WIDTH;
					y = rand() % height;



					if (ScaredSprite) {
						int r = rand() % 256;
						int g = rand() % 256;
						int b = rand() % 256;
						scaredColor = al_map_rgb(r, g, b);
						x = rand() % WIDTH;
						y = rand() % HEIGHT;
					}
					else if () {

					}
				}
			}
		}
	}
}