/*
 * Telephone.cpp
 *
 *  Created on: Feb 6, 2012
 *      Author: matthias schmid
 */

#include <OgreSceneManager.h>
#include <OgreRay.h>

#include "Telephone.h"

Telephone::Telephone(Ogre::SceneManager* sceneMgr, const char* name) {

	mSceneMgr = sceneMgr;
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
	setupButtons();
}


void Telephone::setupButtons() {

}

bool Telephone::canUse(CharacterController* character)
{
	return mEntity->getWorldBoundingBox().intersects(character->getBoundingBox());

//	Ogre::Ray ray(character->getPosition(), character->getDirection());
//	mRaySceneQuery->setRay(ray);
//	Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
//	Ogre::RaySceneQueryResult::iterator itr;
//
//	for (itr = result.begin(); itr != result.end(); itr++) {
//		if (itr->movable->getName().compare(mName) == 0 && itr->distance > 10) {
//				return true;
//		}
//	}
//	return false;
}

void Telephone::highlight(bool highlight) {
	bool hCur = mSceneNode->getShowBoundingBox();
	if ((hCur && !highlight) || (!hCur && highlight)) {
		mSceneNode->showBoundingBox(highlight);
	}

}
