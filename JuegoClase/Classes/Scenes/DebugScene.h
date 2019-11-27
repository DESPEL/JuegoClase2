#pragma once

#include "HelloWorldScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameWrapper.h"

class DebugScene : public cocos2d::Layer {
private:
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
		cocos2d::Vector<BasicEnemy*> _enemyPool;

		void createEnemy();

protected:
	virtual void pauseButtonAction();
	virtual void playButtonAction();
	virtual void saveButtonAction();
	virtual void salirButtonAction();

public:
		static cocos2d::Scene* createScene();

		virtual bool init();

		void update(float);

		// implement the "static create()" method manually
		//HelloWorld();
		CREATE_FUNC(DebugScene);

};

