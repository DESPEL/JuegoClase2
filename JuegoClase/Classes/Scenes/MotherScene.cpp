/*#include "MotherScene.h"
#include "GameManager.h"

USING_NS_CC;

MotherScene::~MotherScene() {
	CC_SAFE_DELETE(_bg);
}

Scene* MotherScene::createScene() {
	auto scene = Scene::create();
	auto layer = MotherScene::create();
	scene->addChild(layer);
	return scene;
}


bool MotherScene::init() {
	if (!Layer::init()) {
		return false;
	}
	_visibleSize = Director::getInstance()->getVisibleSize();
	_completionPercentage = 0;
	_enemyIndex = 0;
	_scoreToCompleTheLevel = 1000;
	isLevelComplete = false;
	setTag(0);
	MotherScene::getInstance()->setPlayerScore(0);

	//todas las pantallas de nuestro juego usaran este sprite sheet
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Hunter.plist", "Hunter.png");
	addChild(_gameBatchNode, ForegroundPos);


	//player
	_player = Player::create();
	_player->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.3);
	_gameBatchNode->addChild(_player, ForegroundPos);


	//UI
	createHealthIndicator();
	createScoreAndPercentageLabels();
	createPauseAndResumeButtons();
	createRespawnButton();

	//crea el boton de ir hacia atras
	_backButton = ui::Button::create("back0", "back1", "back1", ui::Widget::TextureResType::PLIST);
	_backButton->setAnchorPoint(Point(0, 0.5));
	_backButton->addClickEventListener(CC_CALLBACK_0(MotherScene::actionButtonBack, this));
	_backButton->setPosition(Point(42.5 * getScaleX(), 50 * getScaleY()));
	_backButton->setEnabled(false);
	_backButton->setVisible(false);
	addChild(_backButton, UIPos);


	return true;
}

void MotherScene::levelCompleteActions() {
	if (!isLevelComplete) {
		float aniTime = 2.0f;
		auto winnerLabel = Label::createWithTTF("Level complete", "fonts/arial.ttf", 40);
		winnerLabel->setTextColor(Color4B::ORANGE);
		winnerLabel->setPosition(Point(_visibleSize.width * 0.5, _visibleSize.height - 100 * getScaleY()));
		addChild(winnerLabel, UIPos);
		GameManager::getInstance()->saveGame(getTag());

		auto moveTo = MoveTo::create(aniTime, Point(_visibleSize.width * 0.5, _visibleSize.height * 0.5));
		winnerLabel->runAction(moveTo);

		CallFunc* loadMenu = CallFunc::create(CC_CALLBACK_0(MotherScene::levelCompleteActionsHelper, this));
		DelayTime* delayAction = DelayTime::create(aniTime);
		auto sequence = Sequence::create(delayAction, loadMenu, NULL);
		runAction(sequence);
	}
	isLevelComplete = true;
}

void MotherScene::levelCompleteActionsHelper() {
	CustomAudioManager::getInstance()->stopAll();
	Director::getInstance()->replaceScene(SelectMenuLayer::createScene());
}


void MotherScene::resetPlayer() {
	_player->reset();
	_player->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.3);
	GameManager::getInstance()->setPlayerScore(0);
}


void MotherScene::createHealthIndicator() {
	auto healthContainerIndicator = Sprite::createWithSpriteFrameName("health_container_indicartor");
	healthContainerIndicator->setAnchorPoint(Point(0, 0.5));
	healthContainerIndicator->setPosition(Point(20 * getScaleX(), _visibleSize.height - 25 * getScaleY()));
	_gameBatchNode->addChild(healthContainerIndicator, UIPos);
	auto nextPosition = Point(healthContainerIndicator->getPositionX() + healthContainerIndicator->getBoundingBox().size.width + 5, healthContainerIndicator->getPositionY());

	auto healthContainer = Sprite::createWithSpriteFrameName("health_container");
	healthContainer->setScaleY(0.80f);
	healthContainer->setAnchorPoint(Point(0, 0.5));
	healthContainer->setPosition(nextPosition);
	_gameBatchNode->addChild(healthContainer, UIPos);

	_healthBar = Sprite::createWithSpriteFrameName("health_bar");
	_healthBar->setAnchorPoint(Point(0, 0.5));
	_healthBar->setPosition(nextPosition);
	_healthBar->setScaleY(0.78f);
	_healthBar->setScaleX(1);
	//nos aseguramos que aunque se reordenen los sprites, este estara arriba siempre.
	_gameBatchNode->addChild(_healthBar, UIPos + 1);
}

void MotherScene::createScoreAndPercentageLabels() {
	//score
	_scoreLabel = Label::createWithTTF("Score: 0", "fonts/arial.ttf", 15);
	_scoreLabel->setAnchorPoint(Point(0.5, 0.5));
	_scoreLabel->setPosition(Point(_visibleSize.width * 0.5, _healthBar->getPositionY()));
	_scoreLabel->setTextColor(Color4B::BLACK);
	addChild(_scoreLabel, UIPos);

	//percentage
	_completionPercentageLabel = Label::createWithTTF("0 %", "fonts/arial.ttf", 30);
	_completionPercentageLabel->setAnchorPoint(Point(1, 0));
	_completionPercentageLabel->setTextColor(Color4B::ORANGE);
	_completionPercentageLabel->setPosition(Point(_visibleSize.width - 5 * getScaleX(), 5 * getScaleY()));
	addChild(_completionPercentageLabel, UIPos);
}

void MotherScene::createPauseAndResumeButtons() {
	//pause button
	_pauseButton = ui::Button::create("pause0", "pause1", "pause1", ui::Widget::TextureResType::PLIST);
	_pauseButton->setScale(0.8f);
	_pauseButton->addClickEventListener(CC_CALLBACK_0(MotherScene::pauseButtonAction, this));
	_pauseButton->setAnchorPoint(Point(1, 0.5));
	_pauseButton->setPosition(Point(_visibleSize.width - 20 * getScaleX(), _scoreLabel->getPositionY()));
	addChild(_pauseButton, UIPos);

	//play
	_playButton = ui::Button::create("play0", "play1", "play1", ui::Widget::TextureResType::PLIST);
	_playButton->setScale(0.8f);
	_playButton->addClickEventListener(CC_CALLBACK_0(MotherScene::playButtonAction, this));
	_playButton->setAnchorPoint(Point(1, 0.5));
	_playButton->setVisible(false);
	_playButton->setEnabled(false);
	_playButton->setPosition(_pauseButton->getPosition());
	addChild(_playButton, UIPos);
}

void MotherScene::createRespawnButton() {
	_respawnButton = ui::Button::create("respawn0", "respawn1", "respawn1", ui::Widget::TextureResType::PLIST);
	_respawnButton->setPosition(Point(_visibleSize.width * 0.5, _visibleSize.height * 0.5));
	_respawnButton->setVisible(false);
	_respawnButton->setEnabled(false);
	_respawnButton->addClickEventListener(CC_CALLBACK_0(MotherScene::respawnButtonAction, this));
	addChild(_respawnButton, UIPos);
}

void MotherScene::actionButtonBack()
{
	CustomAudioManager::getInstance()->stopAll();
	Director::getInstance()->replaceScene(TransitionSplitRows::create(1, MainMenuLayer::createScene()));
}

void MotherScene::update(float dt) {

	if (_player->isVisible() && _bg) {
		_bg->update(dt);
	}
	else {
		_respawnButton->setVisible(true);
		_respawnButton->setEnabled(true);
		_backButton->setEnabled(true);
		_backButton->setVisible(true);
	}

	//actualizar ui
	_healthBar->setScaleX(static_cast(_player->getHealth()) / static_cast(MAX_HEALTH));
	_ostr << GameManager::getInstance()->getPlayerScore();
	_scoreLabel->setString("Score: " + _ostr.str());
	_ostr.str("");
	_ostr << (GameManager::getInstance()->getPlayerScore() * 100) / _scoreToCompleTheLevel;
	_completionPercentageLabel->setString(_ostr.str() + " %");
	_ostr.str("");
	if (GameManager::getInstance()->getPlayerScore() >= _scoreToCompleTheLevel) {
		levelCompleteActions();
	}
}

void MotherScene::pauseButtonAction() {
	pause();
	CustomAudioManager::getInstance()->pauseAll();
	_pauseButton->setVisible(false);
	_pauseButton->setEnabled(false);
	_playButton->setVisible(true);
	_playButton->setEnabled(true);
	_respawnButton->setVisible(true);
	_respawnButton->setEnabled(true);
	_backButton->setEnabled(true);
	_backButton->setVisible(true);
}

void MotherScene::playButtonAction() {
	resume();
	CustomAudioManager::getInstance()->resumeAll();
	_pauseButton->setVisible(true);
	_pauseButton->setEnabled(true);
	_playButton->setVisible(false);
	_playButton->setEnabled(false);
	_respawnButton->setVisible(false);
	_respawnButton->setEnabled(false);
	_backButton->setEnabled(false);
	_backButton->setVisible(false);
}

void MotherScene::respawnButtonAction() {
	playButtonAction();
	resetPlayer();
	_respawnButton->setVisible(false);
	_respawnButton->setEnabled(false);
}
*/
