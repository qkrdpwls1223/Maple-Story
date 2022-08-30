#include "Maple.h"
extern Font font;
extern Well512Random random;

//접근자
RectangleShape Game::getMob(int i) {
	return back.monster[i].hitbox.shape;
}
RectangleShape Game::getGround(int i) {
	return back.grounds[i].shape;
}
RectangleShape Game::getRope(int i) {
	return back.ropes[i].shape;
}
bool Game::getIsAttack() {
	return p.isAttack;
}

//설정자
void Game::setGesture(Action g) {		//동작 설정
	if (p.gesture == Action::SWING_O1) {
		p.textureIndex = 0;
	}
	p.gesture = g;
}
Action Game::getGesture() {
	return p.gesture;
}

void Game::mapSelect(Maps map) {
	if (map == Maps::ARCANA_VILLAGE) {
		back.setGround({
			HitBox(Vector2f(2926.0, 5.0), Vector2f(0.0, 620.0)),		//맵 바닥 생성
			HitBox(Vector2f(270.0, 5.0), Vector2f(220.0, 360.0)),
			HitBox(Vector2f(400.0, 5.0), Vector2f(2050.0, 250.0))
			});
		back.setRope({
			HitBox(Vector2f(5.0, 200.0), Vector2f(455.0, 365.0)),
			HitBox(Vector2f(5.0, 280.0), Vector2f(2450.0, 270.0))		//맵 로프 생성
			});
		back.setImage(-1620, 0, "img/arcana_village.png", Vector2f(0.88f, 0.88f));
		back.setMonster(false);
		back.potal_L = Potal(Vector2f(50.0, 450.0), Maps::ARCANA_FIELD_FOREST_B);
		back.potal_R = Potal(Vector2f(2750.0, 450.0), Maps::ARCANA_FIELD_A);
	}

	else if (map == Maps::ARCANA_FIELD_A) {
		back.setGround({
			HitBox(Vector2f(2150.0, 5.0), Vector2f(0.0, 780.0)),
			HitBox(Vector2f(290.0, 5.0), Vector2f(80.0, 290.0)),
			HitBox(Vector2f(360.0, 5.0), Vector2f(400.0, 450.0)),
			HitBox(Vector2f(425.0, 5.0), Vector2f(800.0, 570.0)),
			HitBox(Vector2f(350.0, 5.0), Vector2f(1250.0, 450.0)),
			HitBox(Vector2f(344.0, 5.0), Vector2f(1640.0, 570.0)),
			});
		back.setRope({
			HitBox(Vector2f(5.0, 110.0), Vector2f(344.0, 300.0)),
			HitBox(Vector2f(5.0, 90.0), Vector2f(740.0, 460.0)),
			HitBox(Vector2f(5.0, 120.0), Vector2f(1141.0, 580.0)),
			HitBox(Vector2f(5.0, 100.0), Vector2f(1281.0, 460.0)),
			HitBox(Vector2f(5.0, 100.0), Vector2f(1585.0, 460.0)),
			HitBox(Vector2f(5.0, 120.0), Vector2f(1965.0, 580.0)),

			});
		back.setImage(-860, -180, "img/arcana_fieldA.png", Vector2f(0.78f, 0.78f));
		back.setMonster(true, Mob::WATERSPIRIT);
		back.potal_L = Potal(Vector2f(50.0, 600.0), Maps::ARCANA_VILLAGE);
		back.potal_R = Potal(Vector2f(2000.0, 600.0), Maps::ARCANA_FIELD_B);
	}

	else if (map == Maps::ARCANA_FIELD_B) {
		back.setGround({
			HitBox(Vector2f(2150.0, 5.0), Vector2f(0.0, 690.0)),
			HitBox(Vector2f(265.0, 5.0), Vector2f(140.0, 530.0)),
			HitBox(Vector2f(520.0, 5.0), Vector2f(480.0, 310.0)),
			HitBox(Vector2f(220.0, 5.0), Vector2f(680.0, 530.0)),
			HitBox(Vector2f(330.0, 5.0), Vector2f(1040.0, 420.0)),
			HitBox(Vector2f(330.0, 5.0), Vector2f(1400.0, 270.0)),
			HitBox(Vector2f(400.0, 5.0), Vector2f(1400.0, 530.0)),
			});
		back.setRope({
			HitBox(Vector2f(5.0, 80.0), Vector2f(180.0, 540.0)),
			HitBox(Vector2f(5.0, 150.0), Vector2f(484.0, 320.0)),
			HitBox(Vector2f(5.0, 90.0), Vector2f(850.0, 540.0)),
			HitBox(Vector2f(5.0, 70.0), Vector2f(1344.0, 440.0)),
			HitBox(Vector2f(5.0, 70.0), Vector2f(1420.0, 280.0)),
			HitBox(Vector2f(5.0, 80.0), Vector2f(1756.0, 540.0))
			});
		back.setImage(-740, -100, "img/arcana_fieldB.png", Vector2f(0.73f, 0.73f));
		back.setMonster(true, Mob::SUNSPIRIT);
		back.potal_L = Potal(Vector2f(50.0, 510.0), Maps::ARCANA_FIELD_A);
		back.potal_R = Potal(Vector2f(1900.0, 510.0), Maps::ARCANA_FIELD_C);
	}

	else if (map == Maps::ARCANA_FIELD_C) {
		back.setGround({
			HitBox(Vector2f(2150.0, 5.0), Vector2f(0.0, 620.0)),
			HitBox(Vector2f(150.0, 5.0), Vector2f(150.0, 460.0)),
			HitBox(Vector2f(210.0, 5.0), Vector2f(380.0, 400.0)),
			HitBox(Vector2f(210.0, 5.0), Vector2f(670.0, 330.0)),
			HitBox(Vector2f(160.0, 5.0), Vector2f(960.0, 255.0)),
			HitBox(Vector2f(490.0, 5.0), Vector2f(800.0, 470.0)),
			HitBox(Vector2f(210.0, 5.0), Vector2f(1200.0, 330.0)),
			HitBox(Vector2f(200.0, 5.0), Vector2f(1510.0, 400.0)),
			HitBox(Vector2f(150.0, 5.0), Vector2f(1790.0, 455.0))
			});
		back.setRope({
			HitBox(Vector2f(5.0, 80.0), Vector2f(163.0, 478.0)),
			HitBox(Vector2f(5.0, 180.0), Vector2f(450.0, 340.0)),
			HitBox(Vector2f(5.0, 180.0), Vector2f(1360.0, 340.0)),
			HitBox(Vector2f(5.0, 80.0), Vector2f(1903.0, 465.0)),

			});
		back.setImage(-740, -20, "img/arcana_fieldC.png", Vector2f(0.73f, 0.73f));
		back.setMonster(true, Mob::SOILSPIRIT);
		back.potal_L = Potal(Vector2f(50.0, 440.0), Maps::ARCANA_FIELD_B);
		back.potal_R = Potal(Vector2f(1820.0, 280.0), Maps::ARCANA_MIDDLEREST);
	}

	else if (map == Maps::ARCANA_MIDDLEREST) {
		back.setGround({
			HitBox(Vector2f(2050.0, 5.0), Vector2f(0.0, 610.0))
			});
		back.setRope({});
		back.setImage(-640, -20, "img/arcana_middleRest.png", Vector2f(0.79f, 0.79f));
		back.setMonster(false);
		back.potal_L = Potal(Vector2f(50.0, 440.0), Maps::ARCANA_FIELD_C);
		back.potal_R = Potal(Vector2f(1700.0, 440.0), Maps::ARCANA_FIELD_FOREST_A);
	}

	else if (map == Maps::ARCANA_FIELD_FOREST_A) {
		back.setGround({
			HitBox(Vector2f(2750.0, 5.0), Vector2f(0.0, 630.0)),
			HitBox(Vector2f(300.0, 5.0), Vector2f(640.0, 490.0)),
			HitBox(Vector2f(300.0, 5.0), Vector2f(1020.0, 350.0)),
			HitBox(Vector2f(450.0, 5.0), Vector2f(1380.0, 250.0)),
			HitBox(Vector2f(300.0, 5.0), Vector2f(1820.0, 350.0)),

			HitBox(Vector2f(50.0, 5.0), Vector2f(170.0, 610.0)),
			HitBox(Vector2f(50.0, 5.0), Vector2f(220.0, 590.0)),
			HitBox(Vector2f(50.0, 5.0), Vector2f(270.0, 570.0)),
			HitBox(Vector2f(270.0, 5.0), Vector2f(280.0, 550.0)),
			HitBox(Vector2f(100.0, 5.0), Vector2f(600.0, 590.0)),
			HitBox(Vector2f(50.0, 5.0), Vector2f(2080.0, 610.0)),
			HitBox(Vector2f(50.0, 5.0), Vector2f(2130.0, 580.0)),
			HitBox(Vector2f(180.0, 5.0), Vector2f(2180.0, 550.0)),
			HitBox(Vector2f(50.0, 5.0), Vector2f(2370.0, 580.0)),
			HitBox(Vector2f(50.0, 5.0), Vector2f(2420.0, 600.0))
			});
		back.setRope({
			HitBox(Vector2f(5.0, 150.0), Vector2f(1040.0, 360.0)),
			HitBox(Vector2f(5.0, 150.0), Vector2f(1440.0, 260.0)),
			HitBox(Vector2f(5.0, 150.0), Vector2f(1718.0, 260.0)),
			HitBox(Vector2f(5.0, 150.0), Vector2f(2103.0, 360.0))
			});
		back.setImage(-1350, 0, "img/arcana_field_forestA.png", Vector2f(0.81f, 0.81f));
		back.setMonster(true, Mob::FROSTYCLOUD);
		back.potal_L = Potal(Vector2f(50.0, 460.0), Maps::ARCANA_MIDDLEREST);
		back.potal_R = Potal(Vector2f(2480.0, 460.0), Maps::ARCANA_FIELD_FOREST_B);
	}

	else if (map == Maps::ARCANA_FIELD_FOREST_B) {
		back.setGround({
			HitBox(Vector2f(2650.0, 5.0), Vector2f(0.0, 630.0)),
			HitBox(Vector2f(400.0, 5.0), Vector2f(60.0, 100.0)),
			HitBox(Vector2f(500.0, 5.0), Vector2f(440.0, 200.0)),
			HitBox(Vector2f(235.0, 5.0), Vector2f(1020.0, 240.0)),
			HitBox(Vector2f(235.0, 5.0), Vector2f(1460.0, 240.0)),
			HitBox(Vector2f(550.0, 5.0), Vector2f(1740.0, 200.0)),
			HitBox(Vector2f(320.0, 5.0), Vector2f(2260.0, 100.0)),
			HitBox(Vector2f(230.0, 5.0), Vector2f(1240.0, 390.0)),

			HitBox(Vector2f(50.0, 5.0), Vector2f(1010.0, 600.0)),
			HitBox(Vector2f(50.0, 5.0), Vector2f(1060.0, 570.0)),
			HitBox(Vector2f(50.0, 5.0), Vector2f(1110.0, 530.0)),
			HitBox(Vector2f(450.0, 5.0), Vector2f(1150.0, 490.0)),
			HitBox(Vector2f(50.0, 5.0), Vector2f(1630.0, 530.0)),
			HitBox(Vector2f(50.0, 5.0), Vector2f(1680.0, 570.0)),
			HitBox(Vector2f(50.0, 5.0), Vector2f(1730.0, 600.0))
			});
		back.setRope({
			HitBox(Vector2f(5.0, 310.0), Vector2f(520.0, 220.0)),
			HitBox(Vector2f(5.0, 310.0), Vector2f(901.0, 220.0)),
			HitBox(Vector2f(5.0, 125.0), Vector2f(1162.0, 260.0)),
			HitBox(Vector2f(5.0, 125.0), Vector2f(1563.0, 260.0)),
			HitBox(Vector2f(5.0, 310.0), Vector2f(1817.0, 220.0)),
			HitBox(Vector2f(5.0, 310.0), Vector2f(2220.0, 220.0)),
			});
		back.setImage(-1300, 0, "img/arcana_field_forestB.png", Vector2f(0.81f, 0.81f));
		back.setMonster(true, Mob::THUNDERCLOUD);
		back.potal_L = Potal(Vector2f(50.0, 460.0), Maps::ARCANA_FIELD_FOREST_A);
		back.potal_R = Potal(Vector2f(2400.0, 460.0), Maps::ARCANA_VILLAGE);
	}
}
void Game::setMap(Maps map, Vector2f p_coor) {
	back.monster.clear();
	back.map = map;
	mapSelect(map);

	//맵 변경시 위치 변경
	cout << p_coor.x << "  " << p_coor.y << endl;
	p.x = p_coor.x;
	p.y = p_coor.y;
	p.hitbox.x = p.x + 140;
	p.scope.x = p.x + 50;
	if (p.sprite.getScale().x < 0) {
		p.x += 320;
		p.scope.x += 130;
	}
	p.hitbox.y = p.y + 120;
	p.scope.y = p.y + 80;

	p.sprite.setPosition(p.x, p.y);
	p.hitbox.shape.setPosition(p.hitbox.x, p.hitbox.y);
	p.scope.shape.setPosition(p.scope.x, p.scope.y);

	back.x = 0;
	back.y = 0;
	back.sprite.setPosition(0, 0);
}
void Game::setMap(Maps map, int dstn) {
	back.monster.clear();
	back.map = map;
	mapSelect(map);

	//맵 변경시 위치 변경
	if (dstn == 0) {
		p.x = (float)(back.endX * -1 + 1000);
		p.y = 300;
	}
	else if (dstn == 1) {
		p.x = -50;
		p.y = 300;
	}
	p.hitbox.x = p.x + 140;
	p.scope.x = p.x + 50;
	if (p.sprite.getScale().x < 0) {
		p.x += 320;
		p.scope.x += 130;
	}
	p.hitbox.y = p.y + 120;
	p.scope.y = p.y + 80;

	p.sprite.setPosition(p.x, p.y);
	p.hitbox.shape.setPosition(p.hitbox.x, p.hitbox.y);
	p.scope.shape.setPosition(p.scope.x, p.scope.y);

	back.x = 0;
	back.y = 0;
	back.sprite.setPosition(0, 0);

	if (dstn == 0) {
		for (; back.x > back.endX;) {
			cameraMove_Right();
		}
	}
}

