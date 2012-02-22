/*
 * InteractiveObject.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: matthias
 */

#include "UsableObject.h"

UsableObject::UsableObject(Ogre::SceneManager* sceneMgr, CharacterController* cController)
	: GameObject(sceneMgr),
	  mSceneMgr(sceneMgr),
	  mCharacterController(cController)
	  {
}

UsableObject::~UsableObject() {
}

bool UsableObject::canUse()
{
	return mEntity->getWorldBoundingBox().intersects(mCharacterController->getBoundingBox());
}
