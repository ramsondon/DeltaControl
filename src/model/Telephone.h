/*
 * Telephone.h
 *
 *  Created on: Feb 6, 2012
 *      Author: matthias schmid
 */

#ifndef TELEPHONE_H_
#define TELEPHONE_H_

#include <OgreEntity.h>
#include <string>
#include "../CharacterController.h"

class Telephone {

private:
	Ogre::Entity* mEntity;
	Ogre::SceneNode* mSceneNode;
	Ogre::SceneManager* mSceneMgr;
	Ogre::RaySceneQuery* mRaySceneQuery;
	const char* mName;

	void setup();
	void setupButtons();

public:
	Telephone(Ogre::SceneManager* sceneMgr, const char* name);
	virtual ~Telephone();

	bool canUse(CharacterController* character);
	void highlight(bool highlight);

	Ogre::Entity* getEntity();
};

#endif /* TELEPHONE_H_ */
