#include "MainMenu.h"
#include "Scenes/DebugScene.h"
#include "LevelSelectMenu.h"
#include "OptionsMenu.h"
#include "SelectPlayersMenu.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"
#include "MenuInstrucciones.h"
#include "Scenes/MiniGameScene.h"
#include "Scenes/TopScene.h"
#include "menus/LogorsMenu.h"
#include "menus/NextLvl.h"
#include "AudioEngine.h"
#include "Scenes/HistoriaMotherScene.h"

USING_NS_CC;
using namespace ui;


Scene* MainMenu::createScene() {
	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}


bool MainMenu::init() {
	if (!MotherMenu::init()) {
		return false;
	}
	
	//GameManager::getInstance()->resetScore();
	//GameManager::getInstance()->unlockRapidin();
	//GameManager::getInstance()->unlockMcDonalds();
	//GameManager::getInstance()->lockRapidin();
	//GameManager::getInstance()->lockMcDonalds();
	//UserDefault::getInstance()->destroyInstance();

	std::vector<std::function <void(cocos2d::Ref*)>> functions;
	//inicializamos un vector de funciones. Cada funcion lanza un nivel
	initFunctions(functions);
	 wrapper->SetLevel();
	
	 
	 auto title = Sprite::create("menus/Botones/logo.png");
	 title->setAnchorPoint(Point(0.5, 1));
	 title->setPosition(_visibleSize.width / 2  - 150, _visibleSize.height - 10);
	 addChild(title);
	 
	 //lanza automaticamente el siguiente nivel a jugar
	auto startButton = Button::create("menus/Botones/start0.png", "menus/Botones/start1.png", "menus/Botones/start0.png", Widget::TextureResType::LOCAL);
	startButton->setAnchorPoint(Point(0.5, 1));
	startButton->setScale(3, 1.5);
	startButton->setPosition(Vec2(_visibleSize.width * 0.5, _visibleSize.height - (70 * getScaleY())));
	if (GameManager::getInstance()->getNextLevel() == GameManager::NUM_LEVELS) {
		//startButton->addClickEventListener(functions.at(GameManager::NUM_LEVELS - 1));
		startButton->addClickEventListener(CC_CALLBACK_0(MainMenu::actionButton1, this));
	} // std::function <void (cocos2d::Ref *)>
	else {
		//startButton->addClickEventListener(functions.at(GameManager::getInstance()->getNextLevel()));
		startButton->addClickEventListener(CC_CALLBACK_0(MainMenu::actionButton1, this));
	}
	addChild(startButton);

	//lanza el menu de seleccion de nivel
	auto nextHeight = startButton->getPositionY() - startButton->getBoundingBox().size.height - (5 * getScaleY());
	auto selectButton = Button::create("menus/Botones/level0.png", "menus/Botones/level1.png", "menus/Botones/level0.png", Widget::TextureResType::LOCAL);
	selectButton->setAnchorPoint(Point(0.5, 1));
	selectButton->setScale(3, 1.5);
	selectButton->addClickEventListener(CC_CALLBACK_0(MainMenu::selectMenuButton, this));
	selectButton->setPosition(Point(startButton->getPositionX(), nextHeight));
	addChild(selectButton);

	//lanza las opciones para ajustar volumen y otras configuraciones
	nextHeight = selectButton->getPositionY() - selectButton->getBoundingBox().size.height - (5 * getScaleY());
	auto optionsButton = Button::create("menus/Botones/options0.png", "menus/Botones/options1.png", "menus/Botones/options0.png", Widget::TextureResType::LOCAL);
	optionsButton->setAnchorPoint(Point(0.5, 1));
	optionsButton->setScale(3, 1.5);
	optionsButton->addClickEventListener(CC_CALLBACK_0(MainMenu::optionsButton, this));
	optionsButton->setPosition(Point(startButton->getPositionX(), nextHeight));
	addChild(optionsButton);

	nextHeight = optionsButton->getPositionY() - optionsButton->getBoundingBox().size.height - (5 * getScaleY());
	auto Minigame = Button::create("menus/Botones/extra.png", "menus/Botones/extra.png", "menus/Botones/extra.png", Widget::TextureResType::LOCAL);
	Minigame->setAnchorPoint(Point(0.5, 1));
	Minigame->setScale(3, 1.5);
	Minigame->addClickEventListener(CC_CALLBACK_0(MainMenu::actionButton3, this));
	Minigame->setPosition(Point(optionsButton->getPositionX(), nextHeight));
	addChild(Minigame);



	nextHeight = optionsButton->getPositionY() - optionsButton->getBoundingBox().size.height - (5 * getScaleY());
	auto cerrar = Button::create("menus/Botones/close.png", "menus/Botones/close.png", "menus/Botones/close.png", Widget::TextureResType::LOCAL);
	cerrar->setAnchorPoint(Point(0.5, 1));
	cerrar->setScale(0.5, 0.3);
	cerrar->addClickEventListener(CC_CALLBACK_0(MainMenu::actionButton2, this));
	cerrar->setPosition(Point(400, 80));
	addChild(cerrar);

	nextHeight = Minigame->getPositionY() - Minigame->getBoundingBox().size.height - (5 * getScaleY());
	auto TOP = Button::create("menus/Botones/TOP.png", "menus/Botones/TOP1.png", "menus/Botones/TOP2.png", Widget::TextureResType::LOCAL);
	TOP->setAnchorPoint(Point(0.5, 1));
	TOP->setScale(3, 1.5);
	TOP->addClickEventListener(CC_CALLBACK_0(MainMenu::actionButton4, this));
	TOP->setPosition(Point(Minigame->getPositionX(), nextHeight));
	addChild(TOP);

	auto TP = Button::create("menus/Botones/Trofeo.png", "menus/Botones/Trofeo1.png", "menus/Botones/Trofeo.png", Widget::TextureResType::LOCAL);
	TP->setAnchorPoint(Point(0.0, 0));
	TP->setScale(.5, .25);
	TP->addClickEventListener(CC_CALLBACK_0(MainMenu::actionButton5, this));
	TP->setPosition(Point(0,0));
	addChild(TP);

	if (!experimental::AudioEngine::getPlayingAudioCount() >= 1) {
		this->musictag = experimental::AudioEngine::play2d("music/Hollow.mp3", true, GameManager::getInstance()->getBgVolume()/100);
		experimental::AudioEngine::setLoop(musictag, true);
		GameManager::getInstance()->setCurrentMusicTag(musictag);
	}
	return true;
}



void MainMenu::selectMenuButton() {
	Director::getInstance()->pushScene(TransitionFadeBL::create(1, LevelSelectMenu::createScene()));
}

void MainMenu::optionsButton() {
	Director::getInstance()->pushScene(TransitionFlipX::create(1, OptionsMenu::createScene()));
}

void MainMenu::selectPlayer() {
	Director::getInstance()->pushScene(TransitionFlipX::create(1, SelectPlayersMenu::createScene()));
}



void MainMenu::initFunctions(std::vector<std::function <void(cocos2d::Ref*)>> functions) {
	functions.push_back(CC_CALLBACK_0(MainMenu::actionButton1, this));
	functions.push_back(CC_CALLBACK_0(MainMenu::actionButton2, this));
	functions.push_back(CC_CALLBACK_0(MainMenu::actionButton3, this));
	functions.push_back(CC_CALLBACK_0(MainMenu::actionButton4, this));
	functions.push_back(CC_CALLBACK_0(MainMenu::actionButton5, this));
	functions.push_back(CC_CALLBACK_0(MainMenu::actionButton6, this));
	functions.push_back(CC_CALLBACK_0(MainMenu::actionButton7, this));
	functions.push_back(CC_CALLBACK_0(MainMenu::actionButton8, this));
	functions.push_back(CC_CALLBACK_0(MainMenu::actionButton9, this));
}

void MainMenu::actionButton1() { Director::getInstance()->pushScene(TransitionCrossFade::create(1, MenuIns::createScene())); 
	//Director::getInstance()->pushScene(TransitionFadeBL::create(1, HistoriaMotherScene::createScene(wrapper->p1TipoNave, wrapper->coop, wrapper->p2TipoNave, )));
}
void MainMenu::actionButton2() { Director::getInstance()->end(); }

void MainMenu::actionButton3() { 
	Director::getInstance()->pushScene(TransitionCrossFade::create(1, MiniGameScene::createScene()));
	cocos2d::experimental::AudioEngine::stop(musictag);
}

void MainMenu::actionButton4() { Director::getInstance()->pushScene(TransitionFadeBL::create(1, TopMenu::createScene()));  }
void MainMenu::actionButton5() { Director::getInstance()->pushScene(TransitionFadeBL::create(1, LogMenu::createScene())); }
void MainMenu::actionButton6() {  /*TODO*/ }
void MainMenu::actionButton7() {  /*TODO*/ }
void MainMenu::actionButton8() {  /*TODO*/ }
void MainMenu::actionButton9() {  /*TODO*/ }

