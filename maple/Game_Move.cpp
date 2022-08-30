#include "Maple.h"
extern Well512Random random;

#define CAMERA 20
//방향키 이동으로 전체를 움직이는 함수
void Game::allMoveLeft() {
	if (p.hp > 0) {		//죽으면 못움직임
		if (p.sprite.getScale().x < 0) {
			p.sprite.setScale(1.2f, 1.2f);
			p.x -= 320;
			p.sprite.setPosition(p.x, p.y);
			p.scope.x -= 130;
			p.scope.shape.setPosition(p.scope.x, p.scope.y);
			//filp
		}
		if (back.x <= -20 && p.hitbox.x >= 590 && p.hitbox.x <= 630) {
			bgMoveX(SPEED);
			shapeMoveX(SPEED);
			mobMoveX(SPEED);
		}
		else if (p.hitbox.x >= 0) {
			plyerMoveX(SPEED * -1);
		}
		if (sound.getStatus() == SoundSource::Status::Stopped && p.under == true) {
			buffer.loadFromFile("sounds/leaf" + to_string(random.GetValue(0, 5)) + ".wav");
			sound.setBuffer(buffer);
			sound.play();
		}
	}
}
void Game::allMoveRight() {
	if (p.hp > 0) {
		if (p.sprite.getScale().x > 0) {
			p.sprite.setScale(-1.2f, 1.2f);
			p.x += 320;
			p.sprite.setPosition(p.x, p.y);
			p.scope.x += 130;
			p.scope.shape.setPosition(p.scope.x, p.scope.y);
			//flip
		}
		if (back.x > back.endX && p.hitbox.x >= 590 && p.hitbox.x <= 630) {
			bgMoveX(SPEED * -1);
			shapeMoveX(SPEED * -1);
			mobMoveX(SPEED * -1);
		}
		else if (p.hitbox.x <= 1200) {
			plyerMoveX(SPEED);
		}
		if (sound.getStatus() == SoundSource::Status::Stopped && p.under == true) {
			buffer.loadFromFile("sounds/leaf" + to_string(random.GetValue(0, 5)) + ".wav");
			sound.setBuffer(buffer);
			sound.play();
		}
	}
}
void Game::allMoveUp() {
	if (back.y <= -20) {
		bgMoveY(SPEED);
		shapeMoveY(SPEED);
		mobMoveY(SPEED);
	}
}
void Game::allMoveDown() {
	if (back.y > back.endY) {
		bgMoveY(SPEED * -1);
		shapeMoveY(SPEED * -1);
		mobMoveY(SPEED * -1);
	}
}

//모든 히트박스 이동
void Game::shapeMoveX(int a) {
	for (int i = 0; i < back.groundSize; i++) {
		back.grounds[i].x += a;
		back.grounds[i].shape.setPosition(back.grounds[i].x, back.grounds[i].y);
	}
	for (int i = 0; i < back.ropeSize; i++) {
		back.ropes[i].x += a;
		back.ropes[i].shape.setPosition(back.ropes[i].x, back.ropes[i].y);
	}
}
void Game::shapeMoveY(int a) {
	for (int i = 0; i < back.groundSize; i++) {
		back.grounds[i].y += a;
		back.grounds[i].shape.setPosition(back.grounds[i].x, back.grounds[i].y);
	}
	for (int i = 0; i < back.ropeSize; i++) {
		back.ropes[i].y += a;
		back.ropes[i].shape.setPosition(back.ropes[i].x, back.ropes[i].y);
	}
}

//몬스터 이동
void Game::mobMoveX(int a) {
	for (auto& e : back.monster) {
		e.x += a;
		e.sprite.setPosition(e.x, e.y);
		e.hitbox.x += a;
		e.hitbox.shape.setPosition(e.hitbox.x, e.hitbox.y);
		if (e.sprite.getScale().x < 0)
			e.text.setPosition(e.x - 100, e.y);
		else
			e.text.setPosition(e.x + 10, e.y);
	}
}
void Game::mobMoveY(int a) {
	for (int i = 0; i < (int)back.monster.size(); i++) {
		back.monster[i].y += a;
		back.monster[i].sprite.setPosition(back.monster[i].x, back.monster[i].y);
		back.monster[i].hitbox.y += a;
		back.monster[i].hitbox.shape.setPosition(back.monster[i].hitbox.x, back.monster[i].hitbox.y);
		back.monster[i].text.setPosition(back.monster[i].x + 10, back.monster[i].y);
	}
}

//배경 이동
void Game::bgMoveX(int a) {
	back.x += a;
	back.sprite.setPosition(back.x, back.y);
	back.potal_L.x += a;
	back.potal_R.x += a;
	back.potal_L.sprite.setPosition(back.potal_L.x, back.potal_L.y);
	back.potal_R.sprite.setPosition(back.potal_R.x, back.potal_R.y);
}
void Game::bgMoveY(int a) {
	back.y += a;
	back.sprite.setPosition(back.x, back.y);
	back.potal_L.y += a;
	back.potal_R.y += a;
	back.potal_L.sprite.setPosition(back.potal_L.x, back.potal_L.y);
	back.potal_R.sprite.setPosition(back.potal_R.x, back.potal_R.y);
}

//플레이어 이동
void Game::plyerMoveX(int a) {
	p.x += a;
	p.sprite.setPosition(p.x, p.y);
	p.hitbox.x += a;
	p.hitbox.shape.setPosition(p.hitbox.x, p.hitbox.y);
	p.scope.x += a;
	p.scope.shape.setPosition(p.scope.x, p.scope.y);
}
void Game::plyerMoveY(int a) {
	p.y += a;
	p.sprite.setPosition(p.x, p.y);
	p.hitbox.y += a;
	p.hitbox.shape.setPosition(p.hitbox.x, p.hitbox.y);
	p.scope.y += a;
	p.scope.shape.setPosition(p.scope.x, p.scope.y);
}

void Game::mobMoveRand() {
	FloatRect boundingBox = back.sprite.getGlobalBounds();
	for (auto& e : back.monster) {
		if (e.under == true) {
			if (e.step == 0) {
				e.step = random.GetValue(-20, 20);
			}
			else if (e.step < 0) {
				e.move(-5);
				e.step++;
			}
			else if (e.step > 0) {
				e.move(5);
				e.step--;
			}
		}
	}
	deque<Monster>::iterator iter = back.monster.begin();
	while (iter != back.monster.end()) {
		if (!boundingBox.intersects(iter->hitbox.shape.getGlobalBounds())) {
			iter = back.monster.erase(iter);
			//cout << "범위를 벗어난 몬스터가 삭제 됩니다." << endl;
		}
		else {
			iter++;
		}
	}
}

//카메라 무빙
void Game::cameraMove_Left() {
	if (back.x <= -20) {
		plyerMoveX(CAMERA);
		bgMoveX(CAMERA);
		shapeMoveX(CAMERA);
		mobMoveY(CAMERA);
	}
}
void Game::cameraMove_Right() {
	if (back.x > back.endX) {
		plyerMoveX(CAMERA * -1);
		bgMoveX(CAMERA * -1);
		shapeMoveX(CAMERA * -1);
		mobMoveX(CAMERA * -1);
	}
}