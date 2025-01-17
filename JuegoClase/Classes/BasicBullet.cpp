#include "BasicBullet.h"

#define BULLET_MOVEMENT 90

bool BasicBullet::init() noexcept {
	return true;
}

void BasicBullet::run(float) {
	GameWrapper::getInstance()->val++;
	if (parent->exploded) {
		this->removeFromParentAndCleanup(true);
		return;
	}
	if (parent == nullptr) {
		this->removeFromParentAndCleanup(true);
		return;
	}
	cocos2d::log("running bullet");
	//this->setPosition(cocos2d::Vec2(200, 300));
	//cocos2d::log();
	setPosition(parent->getPosition());
	setVisible(true);
	auto seqf = seq->clone();
	seqf->setTag(BULLET_MOVEMENT);
	runAction(seq->clone());
	schedule(schedule_selector(BasicBullet::update));
}

void BasicBullet::update(float delta) {
	if (GameWrapper::getInstance()->getPlayer()->getBoundingBox().intersectsRect(getBoundingBox())) {
		GameWrapper::getInstance()->getPlayer()->hp--;
		if (GameWrapper::getInstance()->getPlayer()->hp <= 0) {
			GameWrapper::getInstance()->getPlayer()->setCurrentAnimation(Player::EXPLOSION);
		}
		this->stopActionByTag(BULLET_MOVEMENT);
		this->runAction(cocos2d::RemoveSelf::create());
		this->removeFromParentAndCleanup(true);
	}
	if (GameWrapper::getInstance()->coop) {
		if (GameWrapper::getInstance()->coop && GameWrapper::getInstance()->getPlayer2()->getBoundingBox().intersectsRect(getBoundingBox())) {
			GameWrapper::getInstance()->getPlayer2()->hp--;
			if (GameWrapper::getInstance()->getPlayer2()->hp <= 0) {
				GameWrapper::getInstance()->getPlayer2()->setCurrentAnimation(Player2::EXPLOSION);
			}
			this->stopActionByTag(BULLET_MOVEMENT);
			this->runAction(cocos2d::RemoveSelf::create());
		}
	}
}

BasicBullet* BasicBullet::create(BasicBullet* bull) {
	BasicBullet* ret = BasicBullet::create();
	ret->initWithTexture(bull->getTexture());
	ret->seq = bull->seq;
	return ret;
}

BasicBullet* BasicBullet::create(std::string name) {
	BasicBullet* val = BasicBullet::create();
	if (val == nullptr)
		return nullptr;
	val->initWithFile(name);
	return val;
}

BasicBullet::~BasicBullet() {
	GameWrapper::getInstance()->val--;
	//std::stringstream a;
	//a << "bullet deleted, remaining: " << GameWrapper::getInstance()->val;
	//cocos2d::log(a.str().c_str());
}