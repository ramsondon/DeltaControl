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

class Observer;

class UsableObject : public GameObject {

protected:
	bool mIsUsing;
	Ogre::Entity* mEntity;
	Ogre::SceneNode* mSceneNode;
	Ogre::SceneManager* mSceneMgr;
	CharacterController* mCharacterController;

	Observer* mObserver;

public:
	UsableObject(Ogre::SceneManager* sceneMgr, CharacterController* cController);
	virtual ~UsableObject();

	virtual bool canUse();

	bool isUsing();

	/*
	 * calls notify to the registered Observer
	 */
	virtual void use();

	virtual void unuse();

	void setObserver(Observer* observable);
};

#endif /* USABLEOBJECT_H_ */
