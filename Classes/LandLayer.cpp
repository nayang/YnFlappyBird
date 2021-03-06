#include "LandLayer.h"
#include "define.h"
#include "LandSprite.h"
#include "BirdSprite.h"
USING_NS_CC;

// on "init" you need to initialize your instance
bool Land::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	//yn

    //1 land
	m_spriteland1 = LandSprite::create(0.5);
	m_spriteland2 = LandSprite::create(1.5);
	this->addChild(m_spriteland1,LAND_ZORDER);
	this->addChild(m_spriteland2,LAND_ZORDER);

	this->schedule(schedule_selector(Land::move),LAND_VELOCITY);
    
    //2 bird
    auto birdSprite = BirdSprite::create();
    this->addChild(birdSprite);
    birdSprite->PrepareToFly();
    
    //3 flue
    
    
    _touchOneByOneListenr = EventListenerTouchOneByOne::create();
    _touchOneByOneListenr->setSwallowTouches(false);
    _touchOneByOneListenr->onTouchEnded =[=] (Touch *T, Event *e)
    {
        birdSprite->FlyUpward();
    };
    
    
    //4 touch event
    _touchOneByOneListenr = EventListenerTouchOneByOne::create();
    _touchOneByOneListenr->setSwallowTouches(false);//设置是否向下传递事件
    //由于触控开始的时候不作为，所以考虑这个是否可以删除

    _touchOneByOneListenr->onTouchBegan =[=] (Touch *t, Event *e)
    {
        return true;
    };
    
    _touchOneByOneListenr->onTouchEnded =[=] (Touch *t, Event *e)
    {
        birdSprite->FlyUpward();
    };
	
    return true;
}


void Land::move(float)
{
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto contentSize = m_spriteland1->getContentSize();

	m_spriteland1->setPositionX(m_spriteland1->getPositionX()-2);
	m_spriteland2->setPositionX(origin.x+m_spriteland1->getPositionX()+contentSize.width);
	if(m_spriteland2->getPositionX() == origin.x+contentSize.width/2)
	{
		m_spriteland1->setPositionX(origin.x+contentSize.width/2);
	}
}
void Land::stop()
{
	this->unschedule(schedule_selector(Land::move));
}