class sprite
{
public: 
	~sprite();
	int getX() { return x; }
	int getY() { return y; }
	void updatesprite();
	void bouncesprite(int SCREEN_W, int SCREEN_H);
	void load_animated_sprite(int size, int WIDTH, int HEIGHT);
	void drawSprite(int WIDTH, int HEIGHT);
	static int ability;
	void setSpecialAbility();
	void Collision(sprite Sprites[], int cSize, int me, int WIDTH, int HEIGHT);

private:
	int x, y;
	int width,height;
	int xspeed,yspeed;
	int xdelay,ydelay;
	int xcount,ycount;
	float angle;
	float timeOfCollision;
	float scaleDown;
	bool scaledDownTooFar;
	bool frozenSprite;
	bool SpinningSprite = false;
	bool ScaredSprite = false;
	bool BabySprite = false;
	bool FreezeSprite = false;
	int curframe,maxframe,animdir;
	int framecount,framedelay;
	ALLEGRO_COLOR scaredColor;
	ALLEGRO_BITMAP *image[9];
};