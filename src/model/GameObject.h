/*
 * GameObject.h
 *
 *  Created on: Feb 10, 2012
 *      Author: matthias
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <OgreSceneManager.h>

class GameObject {

protected:
	Ogre::SceneManager* mSceneMgr;

public:
	GameObject(Ogre::SceneManager* sceneMgr);
	virtual ~GameObject();
};

#endif /* GAMEOBJECT_H_ */
