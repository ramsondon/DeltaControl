/*
 * InteractiveObject.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: matthias
 */

#include "UsableObject.h"
#include "Observer.h"

UsableObject::UsableObject(Ogre::SceneManager* sceneMgr, CharacterController* cController)
	: GameObject(sceneMgr),
	  mSceneMgr(sceneMgr),
	  mCharacterController(cController),
	  mObserver(0)
	  {
}

UsableObject::~UsableObject() {
}

bool UsableObject::isUsing()
{
	return mIsUsing;
}

bool UsableObject::canUse()
{
	return mEntity->getWorldBoundingBox().intersects(mCharacterController->getBoundingBox());
}

void UsableObject::use() {

	mIsUsing = true;
	if (mObserver != NULL) {
		mObserver->notify();
	}
}

void UsableObject::unuse() {
	mIsUsing = false;
}

void UsableObject::setObserver(Observer* observer) {
	mObserver = observer;
}
