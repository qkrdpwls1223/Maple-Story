#include "Maple.h"
Font font;
Well512Random random;

void ProcessWindowMessage() {
	MSG msg;
	while (::PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
		::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
	}
	//https://darkpgmr.tistory.com/42
}

int main() {
	RenderWindow window(VideoMode(1280, 720), "Maple");
	window.setFramerateLimit(60);
	
	if (!font.loadFromFile("Maplestory Bold.ttf")) {
		cout << "폰트 불러오기 실패" << endl;
		exit(100);
	}
	Game game;
	game.openData();

	while (window.isOpen()) {
		ProcessWindowMessage();				//응답없음 현상 해결

		Event e;
		while (window.pollEvent(e)) {		//창닫기 누르면 프로그램 종료
			if (e.type == Event::Closed)
				window.close();
		}
		//MapChange
		/*
		if (Keyboard::isKeyPressed(Keyboard::Num1)) {
			game.setMap(Maps::ARCANA_VILLAGE, Vector2f(100.0, 100.0));
		}
		if (Keyboard::isKeyPressed(Keyboard::Num2)) {
			game.setMap(Maps::ARCANA_FIELD_A, Vector2f(100.0, 100.0));
		}
		if (Keyboard::isKeyPressed(Keyboard::Num3)) {
			game.setMap(Maps::ARCANA_FIELD_B, Vector2f(100.0, 100.0));
		}
		if (Keyboard::isKeyPressed(Keyboard::Num4)) {
			game.setMap(Maps::ARCANA_FIELD_C, Vector2f(100.0, 100.0));
		}
		if (Keyboard::isKeyPressed(Keyboard::Num5)) {
			game.setMap(Maps::ARCANA_MIDDLEREST, Vector2f(100.0, 100.0));
		}
		if (Keyboard::isKeyPressed(Keyboard::Num6)) {
			game.setMap(Maps::ARCANA_FIELD_FOREST_A, Vector2f(100.0, 100.0));
		}
		if (Keyboard::isKeyPressed(Keyboard::Num7)) {
			game.setMap(Maps::ARCANA_FIELD_FOREST_B, Vector2f(100.0, 100.0));
		}
		*/


		/*
		if (Keyboard::isKeyPressed(Keyboard::V)) {
			game.shapeViewChange();
		}
		* 카메라 이동
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			game.cameraMove_Left();
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			game.cameraMove_Right();
		}
		*/


		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			if (game.getIsAttack() == false) {
				game.setGesture(Action::WALK);
				game.allMoveLeft();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			if (game.getIsAttack() == false) {
				game.setGesture(Action::WALK);
				game.allMoveRight();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			game.ropeRiding(-5);
			game.usePotal();
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			game.setGesture(Action::PRONE);
			game.ropeRiding(5);
		}
		if (Keyboard::isKeyPressed(Keyboard::LAlt)) {			//점프
			game.playerJump();
		}
		if (Keyboard::isKeyPressed(Keyboard::LControl)) {		//공격
			game.attack();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {		//부활
			game.revival();
		}

		if (e.type == Event::KeyReleased) {
			if (e.key.code == Keyboard::Left or e.key.code == Keyboard::Right) {
				game.setGesture(Action::STAND);
			}
			if (e.key.code == Keyboard::Down) {
				game.setGesture(Action::STAND);
			}
		}
		
		window.clear();
		game.update();
		game.draw(window);
		window.display();
		Sleep(60);
	}
	game.saveData();
	return 0;
}