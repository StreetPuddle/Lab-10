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
	int setSpecialAbility() { return rand() % 4; }
	bool getAbility() { return specialityPower; }

private:
	int x,y;
	int width,height;
	int xspeed,yspeed;
	int xdelay,ydelay;
	int xcount,ycount;
	bool CollisionIsTrue;
	bool specialityPower[4] = { true, true, true, true }; //0=Spining, 1= Scared, 2=Baby, 3=Freeze
	int curframe,maxframe,animdir;
	int framecount,framedelay;
	ALLEGRO_BITMAP *image[9];
};