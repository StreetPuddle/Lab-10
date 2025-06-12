#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>
#include <iostream>
#include "Sprite.h"

using namespace std;
int sprite::ability = 0;

void sprite::load_animated_sprite(int size, int WIDTH, int HEIGHT)
{
	//load the animated sprite
	x = rand() % WIDTH;
	y = rand() % HEIGHT;
	char s[80];
	maxframe = size;
	scaredColor = al_map_rgb(255, 255, 255);
	angle = 0;
	timeOfCollision = 0;
	scaleDown = 1.0f;
	frozenSprite = false;
	scaledDownTooFar = false;
	for (int n = 0; n < size; n++)
	{
		sprintf_s(s, "kirbs%d.png", n);
		image[n] = al_load_bitmap(s);
		if (!image[n]) {
			al_show_native_message_box(nullptr, "Error", "File error", "Could not load sprite", 0, 0);
			exit(1);
		}
	}
	width = al_get_bitmap_width(image[0]);
	height = al_get_bitmap_height(image[0]);
	setSpecialAbility();
	curframe = 0;
	framedelay = 5;
	framecount = 0;
}

sprite::~sprite()
{
	for (int i = 0; i < maxframe; i++)
		al_destroy_bitmap(image[i]);
}

void sprite::drawSprite(int WIDTH, int HEIGHT)
{
	
	if (scaledDownTooFar) {
		return;
	}
	ALLEGRO_BITMAP* currentFrame = image[curframe];

	if (SpinningSprite) {
		al_draw_rotated_bitmap(currentFrame, width / 2.0f, height / 2.0f, x + width / 2.0f, y + height / 2.0f, angle, 0);
	}
	else if(ScaredSprite && (al_get_time() - timeOfCollision < 3.0)) {
		al_draw_tinted_bitmap(currentFrame, scaredColor, x, y, 0);
		//cout << "scared!\n";//test line
	}
	else if (BabySprite && (al_get_time() - timeOfCollision < 10.0)) {
		al_draw_scaled_bitmap(currentFrame, 0, 0, width, height, x, y, width * scaleDown, height * scaleDown, 0);
		//cout << "shrinking\n";//test line
	}
	else if (FreezeSprite && (al_get_time() - timeOfCollision < 5.0)) {
		al_draw_bitmap(currentFrame, x, y, 0);
		//cout << "FROZEN\n";//test line
	}
	else {
		al_draw_bitmap(currentFrame, x, y, 0);
	}
}

void sprite::updatesprite()
{
	if (SpinningSprite) {
		angle += 0.1f;
	}
	else if (FreezeSprite && frozenSprite) {
		if (al_get_time() - timeOfCollision > 5.0) {
			frozenSprite = false;
		}
		else {
			return;
		}
	}

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

//randomly assigns a special ability to the sprite
void  sprite::setSpecialAbility() {
	if (ability == 4) {
		ability = 0;
	}

	if (ability == 0) {
		SpinningSprite = true;
		ability++;
		//cout << "SpinningSprite assigned\n";
	}
	else if (ability == 1) {
		ScaredSprite = true;
		ability++;
		//cout << "ScaredSprite assigned\n";
	}
	else if (ability == 2) {
		BabySprite = true;
		ability++;
		//cout << "BabySprite assigned\n";
	}
	else if (ability == 3) {
		FreezeSprite = true;
		ability++;
		//cout << "FreezeSprite assigned\n";
	}
}

void sprite::Collision(sprite Sprites[], int cSize, int me, int WIDTH, int HEIGHT) {
	for (int i = 0; i < cSize; i++) {
		if (i != me && !scaledDownTooFar) {
			if (x >= Sprites[i].getX() - width && x <= Sprites[i].getX() + width) {
				if (y >= Sprites[i].getY() - height && y <= Sprites[i].getY() + height) {
					
					timeOfCollision = al_get_time();
					Sprites[i].timeOfCollision = al_get_time();
					x = rand() % WIDTH;
					y = rand() % height;

					if (ScaredSprite) {
						float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
						float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
						float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
						scaredColor = al_map_rgba_f(r, g, b, 1);
						x = rand() % WIDTH;
						y = rand() % HEIGHT;
					}
					if (Sprites[i].ScaredSprite) {
						float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
						float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
						float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
						Sprites[i].scaredColor = al_map_rgba_f(r, g, b, 1);
						Sprites[i].x = rand() % WIDTH;
						Sprites[i].y = rand() % HEIGHT;
					}
					if (BabySprite && !scaledDownTooFar) {
						scaleDown /= 2;
						x = rand() % WIDTH;
						y = rand() % HEIGHT;
						if (scaleDown <= 0.1f) {
							scaledDownTooFar = true;
							x = -(width - 10);
							y = -(height - 10);
							cout << "A sprite has vanished into thin air!" << endl;
						}
					}
					if (Sprites[i].BabySprite && !Sprites[i].scaledDownTooFar) {
						Sprites[i].scaleDown /= 2;
						Sprites[i].x = rand() % WIDTH;
						Sprites[i].y = rand() % HEIGHT;
						if (Sprites[i].scaleDown <= 0.1f) {
							Sprites[i].scaledDownTooFar = true;
							Sprites[i].x = -(Sprites[i].width - 10);
							Sprites[i].y = -(Sprites[i].height - 10);
							cout << "A sprite has vanished into thin air!" << endl;
						}
					}
					if (FreezeSprite) {
						frozenSprite = true;
					}
					if (Sprites[i].FreezeSprite) {
						Sprites[i].frozenSprite = true;
					}
				}
			}
		}
	}
}