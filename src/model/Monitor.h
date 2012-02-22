/*
 * Monitor.h
 *
 *  Created on: Feb 10, 2012
 *      Author: matthias
 */

#ifndef MONITOR_H_
#define MONITOR_H_

#include <OgreSceneManager.h>

#include "UsableObject.h"
#include "../CharacterController.h"

class Monitor : public UsableObject {

private:

	void setup();

public:
	Monitor(Ogre::SceneManager* sceneMgr, CharacterController* cc);
	virtual ~Monitor();

	void highlight(bool highlight);
};

#endif /* MONITOR_H_ */
