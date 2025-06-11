class sprite
{
public: 
	~sprite();
	void updatesprite();
	void bouncesprite(int SCREEN_W, int SCREEN_H);
	void load_animated_sprite(int size);
	void drawSprite();
	int getX(){return x;}
	int getY(){return y;}
	void setSpecialAbility();

private:
	int x,y;
	int width,height;
	int xspeed,yspeed;
	int xdelay,ydelay;
	int xcount,ycount;
	bool CollisionIsTrue;
	bool SpinningSprite;
	bool ScaredSprite;
	bool BabySprite;
	bool FreezeSprite;
	int curframe,maxframe,animdir;
	int framecount,framedelay;
	ALLEGRO_BITMAP *image[9];
};