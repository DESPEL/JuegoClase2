#include "BasicPoint.h"
#include "MovementPattern.h"

USING_NS_CC;

bool BasicPoint::init() {
	if (!Sprite::init())
		return false;

	_speed = 150;
	_currentAnimation = IDLE;
	createIdleAnimation();

	createExplosionAnimation();
	/*
	//runAction(_idleAnimation);

	for (int i = 0; i < _numbullets; i++) {
		Balas.pushBack(Bullet::createEnemyBullet());
	}
	scheduleShoot();
	*/

	return true;
}

void BasicPoint::erase() {

	auto delay = DelayTime::create(random(1, 5));
	auto seq = Sequence::create(delay, RemoveSelf::create(), NULL);
	this->runAction(seq);
	
}



void BasicPoint::createIdleAnimation() {
	Vector<SpriteFrame*> animFrames;
	auto sprite1 = Sprite::create("Estrella.png");
	auto size = sprite1->getContentSize();
	for (int i = 0; i < 4; i++) {
		auto frame = SpriteFrame::create("Estrellaani.png", Rect(Vec2(size.width * i, 0), size));
		animFrames.pushBack(frame);
	}

	this->setSpriteFrame(animFrames.at(0));

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.25f);

	auto animate = Animate::create(animation);

	_idleAnimation = RepeatForever::create(animate);

	_idleAnimation->setTag(BasicPoint::Animations::IDLE);

	_idleAnimation->retain();
}

void BasicPoint::createExplosionAnimation() {
	Vector<SpriteFrame*> animFrames;
	auto sprite1 = Sprite::create("Estrella.png");
	sprite1->setScale(2, 2);
	auto size = sprite1->getContentSize();
	for (int i = 0; i < 4; i++) {
		auto frame = SpriteFrame::create("Estrellaani.png", Rect(Vec2(size.width * i, 0), size));
		animFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.15f);

	_explosionAnimation = Animate::create(animation);

	_explosionAnimation->setTag(BasicPoint::Animations::EXPLOSION);

	_explosionAnimation->retain();
}

void BasicPoint::setCurrentAnimation(Animations anim) {
	if (_currentAnimation == anim) return;
	_currentAnimation = anim;
	if (_currentAnimation == IDLE) {
		stopActionByTag(EXPLOSION);
		runAction(_idleAnimation);
	}
	if (_currentAnimation == EXPLOSION) {
		stopActionByTag(IDLE);
		runAction(_explosionAnimation);
	}
}

void BasicPoint::explode() {
	this->setCurrentAnimation(BasicPoint::EXPLOSION);
	auto removeSelf = RemoveSelf::create();
	auto wait = DelayTime::create(0.90f);
	auto move = MoveTo::create(0, Vec2(this->getPosition().x, -500));
	this->runAction(Sequence::create(wait, move, removeSelf, NULL));
	exploded = true;
}

void BasicPoint::scheduleShoot() {

	//establecemos que la nave disparara cada medio segundo
	DelayTime* delayAction = DelayTime::create(2.0f);

	// cramos una accion a partir de una funcion
	CallFunc* callSelectorAction = CallFunc::create(CC_CALLBACK_0(BasicPoint::shoot, this));
	//creamos una secuencia que primero espera y luego dispara
	auto shootSequence = Sequence::create(delayAction, callSelectorAction, NULL);
	_shoot = RepeatForever::create(shootSequence);
	_shoot->setTag(20);
	// envolvemos la secuencia un una accion RepeatForever
	runAction(_shoot);
}



void BasicPoint::shoot() {
	auto bullet = Balas.at(bulletsact);
	bullet->activa = true;
	if (!vuelta)
		this->getParent()->addChild(bullet, -1);
	bullet->setAnchorPoint(Point(0.5, 0));
	if (!bullet->isVisible()) {
		bullet->setPosition(getPositionX(), getPositionY() + this->_contentSize.height / 2);
		bullet->setVisible(true);
	}
	if (bulletsact == _numbullets - 1) {
		bulletsact = 0;
		vuelta = 1;
	}
	else
		bulletsact++;
}



void BasicPoint::update(float delta) {

}
