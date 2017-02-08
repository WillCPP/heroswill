#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
protected:
	int x, y;
	int shadow_x, shadow_y;
	int spawn_x, spawn_y;
	int check_x, check_y;
	bool collide_up, collide_down, collide_left, collide_right;
public:
	bool getCollideUp() { return collide_up; }
	bool getCollideDown() { return collide_down; }
	bool getCollideLeft() { return collide_left; }
	bool getCollideRight() { return collide_right; }

	void setCollideUp(bool b) { collide_up = b; return; }
	void setCollideDown(bool b) { collide_down = b; return; }
	void setCollideLeft(bool b) { collide_left = b; return; }
	void setCollideRight(bool b) { collide_right = b; return; }

	int getX() { return x; }
	int getY() { return y; }

	void setX(int i) { x = i; return; }
	void setY(int i) { y = i; return; }

	int getShadowX() { return shadow_x; }
	int getShadowY() { return shadow_y; }

	void setShadowX(int i) { shadow_x = i; return; }
	void setShadowY(int i) { shadow_y = i; return; }

	int getSpawnX() { return spawn_x; }
	int getSpawnY() { return spawn_y; }

	void setSpawnX(int i) { spawn_x = i; return; }
	void setSpawnY(int i) { spawn_y = i; return; }
};

#endif
