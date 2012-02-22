/*
 * UsableObject.h
 *
 *  Created on: Feb 10, 2012
 *      Author: matthias
 */

#ifndef USABLEOBJECT_H_
#define USABLEOBJECT_H_

#include <OgreEntity.h>
#include <OgreSceneNode.h>

#include "../CharacterController.h"
#include "GameObject.h"


class UsableObject : public GameObject {

protected:
	Ogre::Entity* mEntity;
	Ogre::SceneNode* mSceneNode;
	Ogre::SceneManager* mSceneMgr;
	CharacterController* mCharacterController;

public:
	UsableObject(Ogre::SceneManager* sceneMgr, CharacterController* cController);
	virtual ~UsableObject();

	virtual bool canUse();
};

#endif /* USABLEOBJECT_H_ */
