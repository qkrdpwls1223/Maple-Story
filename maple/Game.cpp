#include "Maple.h"
extern Font font;
extern Well512Random random;

Game::Game() {
	text.setFont(font);
	text.setPosition(30, 600);
	music.openFromFile("sounds/TheTuneOfAzureLight.wav");
	music.setVolume(50);
	music.play();
	soundB.setVolume(70);
}
void Game::draw(RenderWindow& window) {
	//��� �׸���
	window.draw(back.sprite);

	//���� �׸���
	if (back.monsterSpon) {
		for (int i = 0; i < (int)back.monster.size(); i++) {
			window.draw(back.monster[i].sprite);
			window.draw(back.monster[i].text);
		}
	}
	//�÷��̾� �׸���
	window.draw(p.sprite);
	//��Ʈ�ڽ� �׸���
	if (shapeView == true) {
		window.draw(p.hitbox.shape);
		window.draw(p.scope.shape);
		for (int i = 0; i < (int)back.groundSize; i++) {
			window.draw(getGround(i));
		}
		for (int i = 0; i < (int)back.ropeSize; i++) {
			window.draw(getRope(i));
		}
		for (int i = 0; i < (int)back.monster.size(); i++) {
			window.draw(getMob(i));
		}
	}

	window.draw(back.potal_L.sprite);
	window.draw(back.potal_R.sprite);
	//���� text �׸���
	window.draw(text);
}
//���� ������Ʈ
void Game::update() {
	String status = "LEVEL - " + to_string(p.level) + "\nEXP - " + to_string(p.exp) + "/100\nHP - " + to_string(p.hp) + "/1000";
	if (collisionMob()) {
		if (p.hp > 0) {
			p.hp -= random.GetValue(13);
			if (p.hp < 0) p.hp = 0;
		}
	}
	if (p.hp == 0) {
		setGesture(Action::DEAD);
		p.exp = 0;
		status = "LEVEL - " + to_string(p.level) + "\nEXP - " + to_string(p.exp) + L"/100\nHP - �׾����ϴ�. (ESC: �������� ��Ȱ)";
		//setMap(Maps::ARCANA_VILLAGE, Vector2f(500.0, 100.0));
	}
	text.setString(status);

	//�ִϸ��̼� & ü��ȸ��
	if (roopCnt == 4) {
		p.animation();
		if (back.monsterSpon) {
			for (int i = 0; i < (int)back.monster.size(); i++) {
				back.monster[i].animation();
			}
		}
		back.potal_L.animation();
		back.potal_R.animation();
		if (back.monsterSpon == true)
			//����Ϳ��� 1�� ȸ��
			if (p.hp < 1000 && p.hp > 0) p.hp++;
		if (back.monsterSpon == false) {
			//�������� 40�� ȸ��
			if (p.hp < 1000) p.hp += 40;
			if (p.hp > 1000) p.hp = 1000;
		}
		roopCnt = 0;
	}
	//���� ����
	if (back.monsterSpon) {
		for (int i = back.monster.size(); i < 10; i++) {		//�ִ� 10�������� ����
			//cout << "���� �߰�" << endl;
			back.monster.push_back(Monster(Vector2f((float)random.GetValue(back.endX * -2),
													(float)random.GetValue(0, 350)), back.mobType));
		}
	}
	//���� ����
	if (p.isAttack) {
		attackPro();
	}
	//�÷��̾� ����
	if (p.isJump) {
		p.jumping(p.underY);
		allMoveUp();
	}
	else {
		allMoveDown();
		gravity();
	}

	mobMoveRand();
	//���� Ƚ�� ����
	roopCnt++;
}

//��Ʈ�ڽ� ���̱�
void Game::shapeViewChange() {
	if (shapeView == false) shapeView = true;
	else shapeView = false;
}
//����
void Game::attackPro() {
	//cout << "isAttack - " << p.isAttack << endl;
	//cout << "gesture - " << (int)p.gesture << endl;
	//cout << "textureIndex - " << p.textureIndex << endl;
	if (p.textureIndex == 1) {
		if (sound.getStatus() == SoundSource::Status::Stopped) {
			buffer.loadFromFile("sounds/swordL_Attack.wav");
			sound.setBuffer(buffer);
			sound.play();
		}
	}
	int coll = collisionScope();
	if (coll != -1 && p.textureIndex == 2) {
		if (soundB.getStatus() == SoundSource::Status::Stopped) {
			switch (back.monster[coll].mob)
			{
			case Mob::WATERSPIRIT:
				bufferB.loadFromFile("sounds/8644000_Damage.wav");
				break;
			case Mob::SUNSPIRIT:
				bufferB.loadFromFile("sounds/8644001_Damage.wav");
				break;
			case Mob::SOILSPIRIT:
				bufferB.loadFromFile("sounds/8644002_Damage.wav");
				break;
			case Mob::FROSTYCLOUD:
				bufferB.loadFromFile("sounds/8644003_Damage.wav");
				break;
			case Mob::THUNDERCLOUD:
				bufferB.loadFromFile("sounds/8644004_Damage.wav");
				break;
			}
			soundB.setBuffer(bufferB);
			soundB.play();
		}
		back.monster[coll].health -= random.GetValue(3) ? random.GetValue(10, 30) : random.GetValue(30, 60);
		//0 ~ 3(1/4Ȯ��) �� 0(false)�� ������ ������ �ι�
		back.monster[coll].text.setString(to_string(back.monster[coll].health) + "/100");

		deque<Monster>::iterator iter = back.monster.begin();
		while (iter != back.monster.end()) {
			if (iter->health <= 0) {
				iter = back.monster.erase(iter);
				//cout << "���� ����" << endl;
				p.levelUp(15);
				//������ ü���� 0�̵Ǹ� ���Ͱ� deque���� �������� ����ġ�� ����
			}
			else iter++;
		}
	}

	if (p.gesture != Action::SWING_O1 && p.gesture != Action::SWING_O2)
		p.isAttack = false;
}
void Game::attack() {
	if (p.isAttack == false && p.hp > 0) {
		p.isAttack = true;
		p.textureIndex = 0;
		setGesture((Action)((int)rand() % 2 + 6));			//�������� ���� ��� ���� SWING_O1 = 6, SWING_O2 = 7
	}
}
//����Ÿ��
void Game::ropeRiding(int a) {
	if (collisionRope() == true) {
		setGesture(Action::ROPE);
		p.y += a;
		p.sprite.setPosition(p.x, p.y);
		p.hitbox.y += a;
		p.hitbox.shape.setPosition(p.hitbox.x, p.hitbox.y);
		p.scope.y += a;
		p.scope.shape.setPosition(p.scope.x, p.scope.y);
	}
	else {
		setGesture(Action::STAND);
	}
}
//����
void Game::playerJump() {
	if (p.isJump == false && p.under == true && p.hp > 0) {
		if (collisionRope() == false) {
			p.isJump = true;
			setGesture(Action::JUMP);
			buffer.loadFromFile("sounds/Jump.wav");
			sound.setBuffer(buffer);
			sound.play();
		}
	}
}
//���� ����ִ� ��
bool Game::collisionGround(HitBox& h) {
	FloatRect boundingBox = h.shape.getGlobalBounds();

	for (int i = 0; i < back.groundSize; i++) {
		if ( boundingBox.intersects(getGround(i).getGlobalBounds()) ) {
			return true;
		}
	}
	return false;
}
//���� Ÿ�� �ִ���
bool Game::collisionRope() {
	FloatRect boundingBox = p.hitbox.shape.getGlobalBounds();

	for (int i = 0; i < back.ropeSize; i++) {
		if (boundingBox.intersects(getRope(i).getGlobalBounds())) {
			setGesture(Action::ROPESTOP);
			return true;
		}
	}
	return false;
}
//�ٴ��� �ƴϸ� ������
int velocity = 15;
void Game::gravity() {
	if (collisionGround(p.hitbox) == true || collisionRope() == true) {		//�÷��̾ �ٴ� ��ƼƼ�� �浹�ϸ�  �� �̻� �������� ����
		p.under = true;
		p.underY = p.y;
		velocity = 15;
		if (p.isJump) {
			p.isJump = false;
		}
		if (p.gesture == Action::JUMP) setGesture(Action::STAND);
	}
	else {
		p.under = false;
	}
	if (p.under == false) {
		velocity += 1;
		setGesture(Action::JUMP);
		p.y += velocity;
		p.sprite.setPosition(p.x, p.y);
		p.hitbox.y += velocity;
		p.hitbox.shape.setPosition(p.hitbox.x, p.hitbox.y);
		p.scope.y += velocity;
		p.scope.shape.setPosition(p.scope.x, p.scope.y);
	}
	
	for (auto& e : back.monster) {
		if (collisionGround(e.hitbox) == true) {		//���Ͱ� �ٴ� ��ƼƼ�� �浹�ϸ� �� �̻� �������� ����
			e.under = true;
		}
		else {
			e.under = false;
		}
		if (e.under == false) {
			e.y += 15;
			e.sprite.setPosition(e.x, e.y);
			e.hitbox.y += 15;
			e.hitbox.shape.setPosition(e.hitbox.x, e.hitbox.y);
			e.text.setPosition(e.x + 10, e.y);
		}
	}
}

//�÷��̾ �������� ��Ҵ���
bool Game::collisionMob() {
	FloatRect boundingBox = p.hitbox.shape.getGlobalBounds();

	for (auto& e : back.monster) {
		if (boundingBox.intersects(e.hitbox.shape.getGlobalBounds())) {
			return true;
		}
	}
	return false;
}
int Game::collisionScope() {
	FloatRect boundingBox = p.scope.shape.getGlobalBounds();

	for (int i = 0; i < (int)back.monster.size(); i++) {
		if (boundingBox.intersects(back.monster[i].hitbox.shape.getGlobalBounds())) {
			return i;
		}
	}
	return -1;
}

//��Ż�̶� �����ϴ���, �����Ѵٸ� ������Ż���� ��������Ż���� ��ȯ, �ƴ϶�� -1 ��ȯ
int Game::collisionPotal() {
	FloatRect boundingBox = p.hitbox.shape.getGlobalBounds();
	if (boundingBox.intersects(back.potal_L.sprite.getGlobalBounds())) {
		return 0;		//left
	}
	if (boundingBox.intersects(back.potal_R.sprite.getGlobalBounds())) {
		return 1;		//right
	}
	return -1;			//not
}

void Game::usePotal() {
	if (p.gesture == Action::STAND) {
		int dstn = collisionPotal();
		if (dstn != -1) {
			//���ʰ� �����ʿ� ���� ���̵��� �÷��̾��� ��ġ�� �������� ������ ���̸��� ��Ż ��ġ�� ������ �ѱ��.
			if (dstn == 0) setMap(back.potal_L.destination, dstn);
			else if (dstn == 1) setMap(back.potal_R.destination, dstn);
			buffer.loadFromFile("sounds/Portal.wav");
			sound.setBuffer(buffer);
			sound.play();
		}
	}
}
void Game::revival() {
	if (p.hp == 0) {
		setMap(Maps::ARCANA_VILLAGE, Vector2f(440.0, 300.0));
		p.hp = 500;
	}
}

//������ ����(�÷��̾�: level, exp, hp, last place)
void Game::saveData() {
	ofstream fout("save/save.txt");
	if (fout.is_open()) {
		fout << p.level << endl;
		fout << p.exp << endl;
		fout << p.hp << endl;
		fout << (int)back.map << endl;
		fout.close();
		cout << "����Ϸ�!!" << endl;
	}
	else {
		cout << "���̺����� ���� ����" << endl;
	}
}
void Game::openData() {
	ifstream fin("save/save.txt");
	if (fin.fail()) {
		cout << "���̺� ������ ã�� �� �����ϴ�. �⺻������ �����մϴ�." << endl;
		p.level = 1;
		p.exp = 0;
		p.hp = 1000;
		back.map = Maps::ARCANA_VILLAGE;
	}
	else {
		fin >> p.level;
		fin >> p.exp;
		fin >> p.hp;
		int tmp;
		fin >> tmp;
		back.map = (Maps)tmp;
		setMap(back.map, Vector2f(100.0, 100.0));
		fin.close();
	}
}