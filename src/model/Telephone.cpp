/*
 * Telephone.cpp
 *
 *  Created on: Feb 6, 2012
 *      Author: matthias schmid
 */

#include <OgreSceneManager.h>
#include "../CharacterController.h"
#include "Telephone.h"

Telephone::Telephone(Ogre::SceneManager* sceneMgr, CharacterController* cc)
	: UsableObject(sceneMgr, cc) {

	setup();
}

Telephone::~Telephone() {
}

// setup must set SceneNode and Entity
void Telephone::setup() {
	mSceneNode = mSceneMgr->getSceneNode("Telefon_body");
	mEntity = mSceneMgr->getEntity("Telefon_body");
}

void Telephone::highlight(bool highlight) {
	if (highlight) {
		mEntity->setMaterialName("phone1");
	} else {
		mEntity->setMaterialName("NoMaterial");
	}
}
