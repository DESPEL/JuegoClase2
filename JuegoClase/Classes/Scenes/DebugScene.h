#pragma once

#include "HelloWorldScene.h"

#include "Player.h"
#include "BasicEnemy.h"
#include "Player/Player2.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameWrapper.h"
#include "MovementPattern.h"
#include "AttackPattern.h"

class DebugScene : public cocos2d::Layer {
private:
	//Enemys
	int _numEnemies = 10;
	int _enemyIndex = 0;
	float delay = 0;

	Background* _bg;
	Player* _player;
	cocos2d::Vector<BasicEnemy*> _enemyPool;

	void createEnemy();

		bool two = 0;
		int naveP1;
		int naveP2;

		//Enemys
		int _numEnemies = 10;
		int _enemyIndex = 0;
		float delay = 0;
		cocos2d::ui::Button* button;
		cocos2d::ui::Button* button2;
		cocos2d::ui::Button* button3;
		cocos2d::ui::Button* button4;

		Background* _bg;
		
		Player* _player;
		Player2* _player2;
		cocos2d::Vector<BasicEnemy*> _enemyPool;

		void createEnemy();

protected:
	virtual void saveButtonAction();
	virtual void salirButtonAction();

public:
	static cocos2d::Scene* createScene();
		
		virtual void pauseButtonAction();
		virtual void playButtonAction();
		bool pausado = 0;
	
		static cocos2d::Scene* createScene(int tipoP1 = 1, bool two = 0, int tipoP2 = 0);
		DebugScene(int tipoP1, bool two, int tipoP2);
		~DebugScene() {};

	virtual bool init();

	void update(float);

	// implement the "static create()" method manually
	//HelloWorld();
	CREATE_FUNC(DebugScene);

		GameWrapper* wrapper = GameWrapper::getInstance();

		// implement the "static create()" method manually
		//HelloWorld();
		//CREATE_FUNC(DebugScene);

};

