class sprite
{
public: 
	~sprite();
	void updatesprite();
	void bouncesprite(int SCREEN_W, int SCREEN_H);
	void load_animated_sprite(int size);
	void drawSprite(int WIDTH, int HEIGHT);
	int getX(){return x;}
	int getY(){return y;}
	void setSpecialAbility();
	void Collision(sprite Sprites[], int cSize, int me, int WIDTH, int HEIGHT);

private:
	int x,y;
	int width,height;
	int xspeed,yspeed;
	int xdelay,ydelay;
	int xcount,ycount;
	float angle;
	float timeOfCollision;
	bool CollisionIsTrue;
	bool SpinningSprite;
	bool ScaredSprite;
	bool BabySprite;
	bool FreezeSprite;
	int curframe,maxframe,animdir;
	int framecount,framedelay;
	ALLEGRO_COLOR scaredColor;
	ALLEGRO_BITMAP *image[9];
};