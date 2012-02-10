/*
 * Monitor.h
 *
 *  Created on: Feb 10, 2012
 *      Author: matthias
 */

#ifndef MONITOR_H_
#define MONITOR_H_

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>

#include "../CharacterController.h"

class Monitor {

private:
	Ogre::SceneManager* mSceneMgr;
	Ogre::Entity* mEntity;
	Ogre::SceneNode* mSceneNode;

	void setup();

public:
	Monitor(Ogre::SceneManager* sceneMgr);
	virtual ~Monitor();

	bool canUse(CharacterController* character);
	void highlight(bool highlight);
};

#endif /* MONITOR_H_ */
