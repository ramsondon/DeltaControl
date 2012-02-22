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
#include "UsableObject.h"

class Telephone : public UsableObject {

private:
	Ogre::Entity* mEntity;
	Ogre::RaySceneQuery* mRaySceneQuery;
	const char* mName;

	void setup();

public:
	Telephone(Ogre::SceneManager* sceneMgr, CharacterController* cc, const char* name);
	virtual ~Telephone();

	void highlight(bool highlight);

	Ogre::Entity* getEntity();
};

#endif /* TELEPHONE_H_ */
