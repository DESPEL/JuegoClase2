#include "MiniGameScene.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "GameWrapper.h"
#include "GameManager.h"
#include "menus/MainMenu.h"
#include "Macros.h"
#include "Translationengine.h"

USING_NS_CC;

MiniGameScene::MiniGameScene(bool jug) {
	this->two = jug;
	//this->highscore = GameManager::getInstance()->getMiniGameScore();
	
	MiniGameScene::init();
}

Scene* MiniGameScene::createScene(bool jug) {
	auto scene = Scene::create();
	auto layer = new MiniGameScene(jug); //DebugScene::create(jug);
	scene->addChild(layer);

	return scene;
}

bool MiniGameScene::init() {

	if (!Layer::init())
		return false;

	auto _visibleSize = Director::getInstance()->getWinSize();

	
	mensajeHS = this->mensajeHS + std::to_string(GameManager::getInstance()->getMiniGameScore());
	//Crea el background
	_bg = Background::create();
	button = ui::Button::create("menus/Pausa.png", "menus/Pausa.png", "menus/Pausa.png");

	button->setAnchorPoint(Point(1, 0.5));
	button->setPosition(Point(_visibleSize.width - 20 * getScaleX(), 280));
	button->addClickEventListener(CC_CALLBACK_0(MiniGameScene::pauseButtonAction, this));
	button->setScale(.2);
	addChild(button, 3);
	addChild(_bg, -1);

	button2 = ui::Button::create("menus/Play.png", "menus/Play.png", "menus/Play.png");
	button2->setAnchorPoint(Point(1, 0.5));
	button2->setPosition(Point(_visibleSize.width - 20 * getScaleX(), 280));
	button2->addClickEventListener(CC_CALLBACK_0(MiniGameScene::playButtonAction, this));
	button2->setScale(.2);
	button2->setVisible(false);
	addChild(button2, 3);

	button3 = ui::Button::create("menus/save.png", "menus/save.png", "menus/save.png");
	button3->setAnchorPoint(Point(.5, .5));
	button3->setPosition(Point(_visibleSize.width / 2, _visibleSize.height / 2));
	button3->addClickEventListener(CC_CALLBACK_0(MiniGameScene::playButtonAction, this));
	button3->setScale(.4);
	button3->setVisible(false);
	addChild(button3, 3);



	button4 = ui::Button::create("menus/Botones/SalirMenu0.png", "menus/Botones/SalirMenu1.png", "menus/Botones/SalirMenu0.png");
	button4->setAnchorPoint(Point(.5, .5));
	button4->setPosition(Point(_visibleSize.width / 2, 70));
	button4->addClickEventListener(CC_CALLBACK_0(MiniGameScene::salirButtonAction, this));
	button4->setScale(1);
	button4->setScaleX(1.5);
	button4->setVisible(false);
	addChild(button4, 3);
	
	label = Label::createWithTTF(mensaje, "fonts/arial.ttf", 24);
	label->setAnchorPoint(Point(0, 0));
	label->setPosition(0, 260);
	addChild(label, 5);


	

	if (!(TranslationEngine::getInstance()->getLanguage() == "ES_MX")) {

		label3 = Label::createWithTTF("Pick The Stars\n to get point", "fonts/arial.ttf", 24);
	}
	else {
		label3 = Label::createWithTTF("toca las estrellas\nPara obtener puntos", "fonts/arial.ttf", 24);
	}
	

	
	label3->setPosition(_visibleSize.width / 2, _visibleSize.height / 2);
	addChild(label3, 5);



	tiempo = Label::createWithTTF(mensajet, "fonts/arial.ttf", 24);
	tiempo->setAnchorPoint(Point(0, 0));
	tiempo->setPosition(0, 290);
	addChild(tiempo, 5);

	auto high_score = Label::createWithTTF(mensajeHS, "fonts/arial.ttf", 24);
	high_score->setAnchorPoint(Point(0, 0));
	high_score->setPosition(0, 230);
	if (!(TranslationEngine::getInstance()->getLanguage() == "ES_MX")) {
		high_score->setString("High Score: " + std::to_string(GameManager::getInstance()->getMiniGameScore()));
	}
	else
	{
		high_score->setString("Record: " + std::to_string(GameManager::getInstance()->getMiniGameScore()));
	}
	addChild(high_score, 5);
	/*
	auto manager = GameManager::getInstance();

//	if (manager->miniScoresAlmacenados >= 1) {
		auto high_score1 = Label::createWithTTF(std::to_string(manager->fiveMiniScores.at(0)), "fonts/arial.ttf", 24);
		high_score1->setAnchorPoint(Point(0, 0));
		high_score1->setPosition(400, 20);
		addChild(high_score1, 5);
	//}
	//if (manager->miniScoresAlmacenados >= 2) {
		auto high_score2 = Label::createWithTTF(std::to_string(manager->fiveMiniScores.at(1)), "fonts/arial.ttf", 24);
		high_score2->setAnchorPoint(Point(0, 0));
		high_score2->setPosition(400, 40);
		addChild(high_score2, 5);
	//}
	//if (manager->miniScoresAlmacenados >= 3) {
		auto high_score3 = Label::createWithTTF(std::to_string(manager->fiveMiniScores.at(2)), "fonts/arial.ttf", 24);
		high_score3->setAnchorPoint(Point(0, 0));
		high_score3->setPosition(400, 60);
		addChild(high_score3, 5);
	//}
	//if (manager->miniScoresAlmacenados >= 4) {
		auto high_score4 = Label::createWithTTF(std::to_string(manager->fiveMiniScores.at(3)), "fonts/arial.ttf", 24);
		high_score4->setAnchorPoint(Point(0, 0));
		high_score4->setPosition(400, 80);
		addChild(high_score4, 5);
	//}
	//if (manager->miniScoresAlmacenados >= 5) {
		auto high_score5 = Label::createWithTTF(std::to_string(manager->fiveMiniScores.at(4)), "fonts/arial.ttf", 24);
		high_score5->setAnchorPoint(Point(0, 0));
		high_score5->setPosition(400, 100);
		addChild(high_score5, 5);
	//}*/


	//Crea al jugador
	_player = Player::create(random(1,4));
	if (!this->two)
		_player->setPosition(_visibleSize.width / 2, _visibleSize.height / 2 - 100);
	else
		_player->setPosition(_visibleSize.width / 2 + 100, _visibleSize.height / 2 - 100);
	_player->setSpeed(4);
	_player->setScale(2);
	addChild(_player);

	if (this->two) {
		_player2 = Player2::create();
		_player2->setPosition(_visibleSize.width / 2 - 100, _visibleSize.height / 2 - 100);
		_player2->setScale(2);
		addChild(_player2);
	}

	GameWrapper::getInstance()->setPlayer(_player);
	GameWrapper::getInstance()->coop = this->two;

	this->schedule(schedule_selector(MiniGameScene::update));

	//Aparece enemigos de manera aleatoria y automatica
	variar = random(1,2);
	num = random(1, 3);
	DelayTime* delayAction = DelayTime::create(variar);

	for (int i = 0; i < num; i++) {
		CallFunc* callSelectorAction = CallFunc::create(CC_CALLBACK_0(MiniGameScene::createEnemy, this));
		auto shootSequence = Sequence::create(delayAction, callSelectorAction, NULL);
		runAction(RepeatForever::create(shootSequence));
	}


	// Guardar juego en wrapper
	GameWrapper::getInstance()->playing = GAME_TYPE::MINIJUEGO;
	// Musica
	//SimpleAudioEngine::getInstance()->playBackgroundMusic("Music\\Mantis.mp3", true);
	this->musictag = cocos2d::experimental::AudioEngine::play2d("Music/get_lucky.mp3", true, GameManager::getInstance()->getBgVolume() / 100);
	GameManager::getInstance()->setCurrentMusicTag(musictag);

	return true;
}

void MiniGameScene::createEnemy() {
	auto _visibleSize = Director::getInstance()->getWinSize();
	
	
		auto enemy = BasicPoint::create();
		float maxX = _visibleSize.width - 40;
		float minX = 40;
		float maxY = _visibleSize.height - 20;
		float minY = 20;
		enemy->setPosition(random(minX, maxX), random(minY, maxY));
		enemy->setScale(2, 2);
		


		_enemyPool.pushBack(enemy);
		addChild(enemy, 5);
		enemy->erase();
		
	//enemy->run();
	
};

void MiniGameScene::update(float delta) {
	if (_player->isVisible() || two && (_player2->isVisible())) {// (wrapper->coop) ? (_player2->isVisible()) : ())
		_bg->update(delta);
	}
	Timer(delta);
	_player->update(delta);

	if (Tiempo <= 0) {
		GameManager::getInstance()->saveMiniGameScore(_puntos);
		GameManager::getInstance()->updateMiniScores(_puntos);
		
		if (guardado == false) {
			using namespace std;
			int num = _puntos;
			ofstream archivo;
			archivo.open("puntajes.txt", ios::app);

			archivo << endl << num;
			archivo.close();
			guardado = true;
		}

			cocos2d::experimental::AudioEngine::stop(musictag);

			// aqui, antes de llegar al death, se desbloquea la nave
			this->wrapper->death();
		
	}
	for (auto e : _enemyPool) {

		
		

		

		// Colision Enemigo - Jugador
		if (!e->exploded) {
			if (e->getBoundingBox().intersectsRect(_player->getBoundingBox())) {
				Maspuntos();
				e->explode();
			}
		}

		

		if (this->two) {
			if (!e->exploded) {
				if (e->getBoundingBox().intersectsRect(_player2->getBoundingBox())) {
					_player2->setCurrentAnimation(Player2::EXPLOSION);
					e->explode();
				}
			}
		}


		// Colision balas enemigo vs Jugador
		

		/*if (two) {
			for (auto bala : e->Balas) {
				if (bala->getBoundingBox().intersectsRect(_player2->getBoundingBox())) {
					_player2->setCurrentAnimation(Player2::EXPLOSION);
				}
			}
		}*/

		//if (two != false) {
			/*for (auto b : e->Balas) {
				if (b->activa) {
					if (b->getBoundingBox().intersectsRect(_player2->getBoundingBox())) {
						_player2->setCurrentAnimation(Player2::EXPLOSION);
					}
				}
			}*/
			//}
	}

	if ((_player->get_currentAnimation() == Player::EXPLOSION && !two) || (_player->get_currentAnimation() == Player::EXPLOSION && two && (_player2->get_currentAnimation() == Player2::EXPLOSION))) {
		for (auto e : _enemyPool) {
			e->stopActionByTag(20);
		}

		this->wrapper->death();
	}
}
void MiniGameScene::pauseButtonAction()
{
	button->setVisible(false);
	button2->setVisible(true);
	button3->setVisible(true);
	button4->setVisible(true);
	pause();
	experimental::AudioEngine::pause(musictag);

	cocos2d::Director::getInstance()->stopAnimation();

}
void ::MiniGameScene::Timer(float delta) {
	Tiempo -= delta;
	seg = Tiempo;
	if (seg==55)
	{
		label3->setVisible(false);
	}
	if (!(TranslationEngine::getInstance()->getLanguage() == "ES_MX")) {

		tiempo->setString("Time: " + std::to_string(seg));
		label->setString("Points: " + std::to_string(_puntos));
	}
	else {
		tiempo->setString("Tiempo: " + std::to_string(seg));
	}
}

void ::MiniGameScene::Maspuntos() {
	_puntos += 5;
	
	if (!(TranslationEngine::getInstance()->getLanguage() == "ES_MX")) {

		label->setString("Points: " + std::to_string(_puntos));
	}
	else {
		label->setString("Puntos: " + std::to_string(_puntos));
	}
}

void MiniGameScene::playButtonAction()
{
	button->setVisible(true);
	button2->setVisible(false);
	button3->setVisible(false);
	button4->setVisible(false);
	resume();
	experimental::AudioEngine::resume(musictag);

	cocos2d::Director::getInstance()->startAnimation();

}

void MiniGameScene::saveButtonAction() {

}

void MiniGameScene::salirButtonAction() {
	cocos2d::experimental::AudioEngine::stop(musictag);
	cocos2d::Director::getInstance()->startAnimation();
	Director::getInstance()->pushScene(TransitionFadeBL::create(1, MainMenu::createScene()));
}