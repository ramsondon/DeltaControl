/*
 * Telephone.cpp
 *
 *  Created on: Feb 6, 2012
 *      Author: matthias schmid
 */

#include <OgreSceneManager.h>
#include <OgreRay.h>

#include "Telephone.h"

Telephone::Telephone(Ogre::SceneManager* sceneMgr, CharacterController* cc, const char* name)
	: UsableObject(sceneMgr, cc) {

	mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());
	mName = name;
	setup();
}

Telephone::~Telephone() {
}

void Telephone::setup() {
	mEntity = mSceneMgr->createEntity(mName, "Cube.mesh");
	mSceneNode = mSceneMgr->createSceneNode(mName);
	mSceneMgr->getRootSceneNode()->addChild(mSceneNode);
	mSceneNode->attachObject(mEntity);
	mSceneNode->setPosition(0,0,0);
}

void Telephone::highlight(bool highlight) {
	bool hCur = mSceneNode->getShowBoundingBox();
	if ((hCur && !highlight) || (!hCur && highlight)) {
		mSceneNode->showBoundingBox(highlight);
	}
	if (highlight) {
		mEntity->setMaterialName("phone1");
	} else {
		mEntity->setMaterialName("phone2");
	}
}
