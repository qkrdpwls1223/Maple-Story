#ifndef __MAPLE_H__
#define __MAPLE_H__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>
#include <string>
#include <cstdarg>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <fstream>
#include "Well512Random.h"
using namespace sf;
using namespace std;

class HitBox {
public:
	RectangleShape shape;		//��Ʈ�ڽ��� ǥ���ϱ� ���� �簢�� ��ƼƼ
	float x, y;					//��Ʈ�ڽ� ��ǥ

	HitBox() : x{ 0 }, y{ 0 } {	}
	HitBox(const Vector2f& size, const Vector2f& coor);
	void set(const Vector2f& size, const Vector2f& coor);
};
class Entity {
public:
	float x, y;
	HitBox hitbox;
	Sprite sprite;
};
enum class Mob {
	WATERSPIRIT,
	SUNSPIRIT,
	SOILSPIRIT,
	FROSTYCLOUD,
	THUNDERCLOUD
};
class Monster : public Entity {
public:
	Mob mob;		//�� ����
	Text text;
	Texture *texture = nullptr;

	int textureLen = 0;
	int textureIdx = 0;
	int health;
	int step;
	bool under = false;					//������ �� �ؿ� �ٴ��� �ִ���

	Monster(Vector2f coor, Mob m);
	void animation();
	void move(int);
};

//�� ����
enum class Maps {
	ARCANA_VILLAGE,
	ARCANA_FIELD_A,
	ARCANA_FIELD_B,
	ARCANA_FIELD_C,
	ARCANA_MIDDLEREST,
	ARCANA_FIELD_FOREST_A,
	ARCANA_FIELD_FOREST_B
};
class Potal : public Entity {
public:
	Maps destination;		//��Ż ������
	Texture texture[5];
	int textureIdx;

	Potal();
	Potal(Vector2f coor, Maps dstn);
	void animation();
};

class BackGround : public Entity {
public:
	Maps map;		//���� �� ����
	int endX;			//���� �� ��ǥ
	int endY;
	Texture img;

	int groundSize = 3;
	int ropeSize = 2;
	HitBox* grounds = nullptr;
	HitBox* ropes = nullptr;

	bool monsterSpon = false;
	Mob mobType = Mob::WATERSPIRIT;
	deque<Monster> monster;
	Potal potal_L;
	Potal potal_R;
	BackGround();
	void setMonster(bool spon);
	void setMonster(bool spon, Mob);
	void setGround(initializer_list<HitBox> args);
	void setRope(initializer_list<HitBox> args);
	void setImage(int endX, int endY, String filePath, Vector2f scale);
};

//�ִϸ��̼� ���� �̸�
enum class Action {
	STAND,
	WALK,
	JUMP,
	PRONE,
	ROPE,
	ROPESTOP,
	SWING_O1,
	SWING_O2,
	STAB_O2,
	DEAD,
};

class Player : public Entity {
public:
	Action gesture = Action::STAND;

	Texture stand[4];
	Texture walk[4];
	Texture jump;
	Texture prone;
	Texture rope[2];
	Texture swingO1[3];
	Texture swingO2[3];
	Texture stabO2[2];
	Texture dead;
	int textureIndex = 0;

	HitBox scope;				//���ݹ���
	bool isJump;				//�����ϰ� �ִ���(�������̸� true)
	bool under;					//�÷��̾��� �� �ؿ� �ٴ��� �ִ���
	float underY;				//�÷��̾� ���� �ٴ� ��ǥ
	bool isAttack;				//�����ϰ� �ִ���

	int level;
	int exp;
	int hp;

	Player();
	void jumping(float);
	void animation();
	void levelUp(int);
};


#define JUMPSPEED 15
#define SPEED 20

class Game {
private:
	//Font font;
	Text text;
	BackGround back;
	Player p;

	SoundBuffer buffer;
	SoundBuffer bufferB;
	Sound sound;
	Sound soundB;
	Music music;

	int roopCnt = 0;
	bool shapeView = false;


	bool collisionGround(HitBox&);
	bool collisionRope();
	bool collisionMob();
	int collisionScope();
	int collisionPotal();
	
	void attackPro();
	void gravity();
	void setMap(Maps, int dstn);
	void mapSelect(Maps);

	Action getGesture();
	RectangleShape getGround(int);
	RectangleShape getRope(int);
	RectangleShape getMob(int);
	void shapeMoveX(int);
	void shapeMoveY(int);
	void bgMoveX(int);
	void bgMoveY(int);
	void plyerMoveX(int);
	void plyerMoveY(int);
	void mobMoveX(int);
	void mobMoveY(int);
	void allMoveUp();
	void allMoveDown();
	void cameraMove_Left();
	void cameraMove_Right();
	void mobMoveRand();

public:
	Game();
	void update();
	void draw(RenderWindow&);
	void shapeViewChange();
	void ropeRiding(int);
	void attack();
	void revival();
	void playerJump();
	void usePotal();
	void openData();
	void saveData();
	void allMoveLeft();
	void allMoveRight();

	void setMap(Maps, Vector2f coor);
	bool getIsAttack();
	void setGesture(Action);
};

#endif // !1