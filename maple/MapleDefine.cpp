#include "Maple.h"
extern Font font;
extern Well512Random random;

Player::Player() {
	stand[0].loadFromFile("img/character/sword/avatar_stand1(0)_default(0).png");
	stand[1].loadFromFile("img/character/sword/avatar_stand1(1)_default(0).png");
	stand[2].loadFromFile("img/character/sword/avatar_stand1(2)_default(0).png");
	stand[3].loadFromFile("img/character/sword/avatar_stand1(1)_default(0).png");
	
	walk[0].loadFromFile("img/character/sword/avatar_walk1(0)_default(0).png");
	walk[1].loadFromFile("img/character/sword/avatar_walk1(1)_default(0).png");
	walk[2].loadFromFile("img/character/sword/avatar_walk1(2)_default(0).png");
	walk[3].loadFromFile("img/character/sword/avatar_walk1(3)_default(0).png");

	jump.loadFromFile("img/character/sword/avatar_jump(0)_default(0).png");
	prone.loadFromFile("img/character/sword/avatar_prone(0)_default(0).png");
	
	rope[0].loadFromFile("img/character/sword/avatar_rope(0)_default(0).png");
	rope[1].loadFromFile("img/character/sword/avatar_rope(1)_default(0).png");

	swingO1[0].loadFromFile("img/character/sword/avatar_swingO1(0)_default(0).png");
	swingO1[1].loadFromFile("img/character/sword/avatar_swingO1(1)_default(0).png");
	swingO1[2].loadFromFile("img/character/sword/avatar_swingO1(2)_default(0).png");

	swingO2[0].loadFromFile("img/character/sword/avatar_swingO2(0)_default(0).png");
	swingO2[1].loadFromFile("img/character/sword/avatar_swingO2(1)_default(0).png");
	swingO2[2].loadFromFile("img/character/sword/avatar_swingO2(2)_default(0).png");
	
	stabO2[0].loadFromFile("img/character/sword/avatar_stabO2(0)_default(0).png");
	stabO2[1].loadFromFile("img/character/sword/avatar_stabO2(1)_default(0).png");

	dead.loadFromFile("img/character/sword/avatar_dead(0)_default(0).png");

	x = 590;
	y = 300;
	sprite.setTexture(stand[0]);
	sprite.setScale(1.2f, 1.2f);
	sprite.setPosition(x, y);
	hitbox = HitBox{ Vector2f(55.0, 40.0), Vector2f(x + 140, y + 120) };		//플레이어의 히트박스
	scope = HitBox{ Vector2f(100.0, 80.0), Vector2f(x + 70, y + 80) };		//공격범위

	isJump = false;
	under = false;
	underY = NULL;
	isAttack = false;
	exp = 0;
	hp = 1000;
	level = 1;
}
void Player::jumping(float y) {
	gesture = Action::JUMP;
	this->y -= JUMPSPEED;
	hitbox.y -= JUMPSPEED;
	scope.y -= JUMPSPEED;
	if (this->y <= y - 60) {
		isJump = false;
		under = false;
	}
	sprite.setPosition(x, this->y);
	hitbox.shape.setPosition(hitbox.x, hitbox.y);
	scope.shape.setPosition(scope.x, scope.y);
}
void Player::animation() {
	switch (gesture) {
	case Action::STAND:
		if (textureIndex > 3) textureIndex = 0;
		sprite.setTexture(stand[textureIndex]);
		break;

	case Action::WALK:
		if (textureIndex > 3) textureIndex = 0;
		sprite.setTexture(walk[textureIndex]);
		break;

	case Action::JUMP:
		sprite.setTexture(jump);
		break;

	case Action::PRONE:
		sprite.setTexture(prone);
		break;

	case Action::ROPE:
		if (textureIndex > 1) textureIndex = 0;
		sprite.setTexture(rope[textureIndex]);
		break;

	case Action::ROPESTOP:
		sprite.setTexture(rope[0]);
		break;

	case Action::SWING_O1:
		if (textureIndex > 1) {
			isAttack = false;
			gesture = Action::STAND;
		}
		sprite.setTexture(swingO1[textureIndex]);
		break;

	case Action::SWING_O2:
		if (textureIndex > 1) {
			isAttack = false;
			gesture = Action::STAND;
		}
		sprite.setTexture(swingO2[textureIndex]);
		break;

	case Action::STAB_O2:
		if (textureIndex > 0) {
			isAttack = false;
			gesture = Action::STAND;
		}
		sprite.setTexture(stabO2[textureIndex]);
		break;
	case Action::DEAD:
		sprite.setTexture(dead);
		break;
	}

	textureIndex++;
}
void Player::levelUp(int exp) {
	this->exp += exp;
	if (this->exp >= 100) {
		this->exp = this->exp % 100;
		level++;
	}
}

HitBox::HitBox(const Vector2f& size, const Vector2f& coor) {
	x = coor.x;
	y = coor.y;
	shape.setSize(size);
	shape.setOutlineThickness(5);
	shape.setOutlineColor(Color::Red);
	shape.setTexture(NULL);
	shape.setPosition(x, y);
}
void HitBox::set(const Vector2f& size, const Vector2f& coor) {
	x = coor.x;
	y = coor.y;

	shape.setSize(size);
	shape.setOutlineThickness(5);
	shape.setOutlineColor(Color::Red);
	shape.setTexture(NULL);
	shape.setPosition(x, y);
}

Monster::Monster(Vector2f coor, Mob m) {
	mob = m;
	x = coor.x;
	y = coor.y;
	health = 100;
	step = random.GetValue(-20, 20);
	switch (m) {
	case Mob::WATERSPIRIT:
		textureLen = 6;
		texture = new Texture[textureLen];
		texture[0].loadFromFile("img/mob/water_spirit(0).png");
		texture[1].loadFromFile("img/mob/water_spirit(1).png");
		texture[2].loadFromFile("img/mob/water_spirit(2).png");
		texture[3].loadFromFile("img/mob/water_spirit(3).png");
		texture[4].loadFromFile("img/mob/water_spirit(4).png");
		texture[5].loadFromFile("img/mob/water_spirit(5).png");

		hitbox.set(Vector2f(50, 70), Vector2f(x + 30, y + 80));					//몬스터 히트박스 설정
		sprite.setTexture(texture[0]);
		break;
	case Mob::SUNSPIRIT:
		textureLen = 6;
		texture = new Texture[textureLen];
		texture[0].loadFromFile("img/mob/sun_spirit(0).png");
		texture[1].loadFromFile("img/mob/sun_spirit(1).png");
		texture[2].loadFromFile("img/mob/sun_spirit(2).png");
		texture[3].loadFromFile("img/mob/sun_spirit(3).png");
		texture[4].loadFromFile("img/mob/sun_spirit(4).png");
		texture[5].loadFromFile("img/mob/sun_spirit(5).png");

		hitbox.set(Vector2f(60, 80), Vector2f(x + 50, y + 120));					//몬스터 히트박스 설정
		sprite.setTexture(texture[0]);
		break;
	case Mob::SOILSPIRIT:
		textureLen = 8;
		texture = new Texture[textureLen];
		texture[0].loadFromFile("img/mob/soil_spirit(0).png");
		texture[1].loadFromFile("img/mob/soil_spirit(1).png");
		texture[2].loadFromFile("img/mob/soil_spirit(2).png");
		texture[3].loadFromFile("img/mob/soil_spirit(3).png");
		texture[4].loadFromFile("img/mob/soil_spirit(4).png");
		texture[5].loadFromFile("img/mob/soil_spirit(5).png");
		texture[6].loadFromFile("img/mob/soil_spirit(6).png");
		texture[7].loadFromFile("img/mob/soil_spirit(7).png");

		hitbox.set(Vector2f(70, 70), Vector2f(x + 30, y + 60));					//몬스터 히트박스 설정
		sprite.setTexture(texture[0]);
		break;
	case Mob::FROSTYCLOUD:
		textureLen = 6;
		texture = new Texture[textureLen];
		texture[0].loadFromFile("img/mob/frosty_cloud(0).png");
		texture[1].loadFromFile("img/mob/frosty_cloud(1).png");
		texture[2].loadFromFile("img/mob/frosty_cloud(2).png");
		texture[3].loadFromFile("img/mob/frosty_cloud(3).png");
		texture[4].loadFromFile("img/mob/frosty_cloud(4).png");
		texture[5].loadFromFile("img/mob/frosty_cloud(5).png");

		hitbox.set(Vector2f(90, 70), Vector2f(x + 40, y + 100));					//몬스터 히트박스 설정
		sprite.setTexture(texture[0]);
		break;
	case Mob::THUNDERCLOUD:
		textureLen = 6;
		texture = new Texture[textureLen];
		texture[0].loadFromFile("img/mob/thunder_cloud(0).png");
		texture[1].loadFromFile("img/mob/thunder_cloud(1).png");
		texture[2].loadFromFile("img/mob/thunder_cloud(2).png");
		texture[3].loadFromFile("img/mob/thunder_cloud(3).png");
		texture[4].loadFromFile("img/mob/thunder_cloud(4).png");
		texture[5].loadFromFile("img/mob/thunder_cloud(5).png");

		hitbox.set(Vector2f(80, 70), Vector2f(x + 50, y + 100));					//몬스터 히트박스 설정
		sprite.setTexture(texture[0]);
		break;
	}

	text.setFont(font);
	text.setPosition(x + 30, y - 150);
	text.setString(to_string(health) + "/100");
	text.setCharacterSize(20);
	sprite.setPosition(x, y);
}
void Monster::animation() {
	if (textureIdx > textureLen - 1) {
		textureIdx = 0;
	}
	sprite.setTexture(texture[textureIdx]);
	textureIdx++;
}
void Monster::move(int a) {
	if (a > 0 && sprite.getScale().x > 0) {		//오른쪽이동
		sprite.setScale(-1.0f, 1.0f);
		x += 120;
		sprite.setPosition(x, y);
		//flip
	}
	if (a < 0 && sprite.getScale().x < 0) {		//왼쪽이동
		sprite.setScale(1.0f, 1.0f);
		x -= 120;
		sprite.setPosition(x, y);
		//filp
	}
	x += a;
	sprite.setPosition(x, y);
	hitbox.x += a;
	hitbox.shape.setPosition(hitbox.x, hitbox.y);
	
	if (a > 0) text.setPosition(x - 100, y);
	else if (a < 0) text.setPosition(x + 10, y);
}
Potal::Potal() {
	x = 0;
	y = 0;
	destination = Maps::ARCANA_VILLAGE;
	textureIdx = 0;
}
Potal::Potal(Vector2f coor, Maps dstn) {
	x = coor.x;
	y = coor.y;
	destination = dstn;
	textureIdx = 0;

	texture[0].loadFromFile("img/potal/potal_0.png");
	texture[1].loadFromFile("img/potal/potal_1.png");
	texture[2].loadFromFile("img/potal/potal_2.png");
	texture[3].loadFromFile("img/potal/potal_3.png");
	texture[4].loadFromFile("img/potal/potal_4.png");

	sprite.setTexture(texture[0]);
	sprite.setPosition(x, y);
}
void Potal::animation() {
	if (textureIdx > 4) {
		textureIdx = 0;
	}
	sprite.setTexture(texture[textureIdx]);
	textureIdx++;
}

BackGround::BackGround() {
	x = 0;
	y = 0;
	endX = 0;
	endY = 0;
	map = Maps::ARCANA_VILLAGE;
}
void BackGround::setMonster(bool spon) {
	monsterSpon = spon;
}
void BackGround::setMonster(bool spon, Mob mob) {
	monsterSpon = spon;
	mobType = mob;
}
void BackGround::setGround(initializer_list<HitBox> args) {
	if (grounds != NULL) delete[] grounds;

	groundSize = args.size();
	grounds = new HitBox[groundSize];

	for (int i = 0; i < groundSize; i++) {
		grounds[i] = *(args.begin() + i);
	}
}
void BackGround::setRope(initializer_list<HitBox> args) {
	if (ropes != NULL) delete[] ropes;

	ropeSize = args.size();
	ropes = new HitBox[ropeSize];

	for (int i = 0; i < ropeSize; i++) {
		ropes[i] = *(args.begin() + i);
	}
}
void BackGround::setImage(int endX, int endY, String filePath, Vector2f scale) {
	this->endX = endX;
	this->endY = endY;
	img.loadFromFile(filePath);
	sprite.setTexture(img, true);
	sprite.setScale(scale);
}
