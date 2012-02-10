/*
 * Monitor.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: matthias
 */

#include "Monitor.h"
#include "ControlCenter.h"

Monitor::Monitor(Ogre::SceneManager* sceneMgr) {
	mSceneMgr = sceneMgr;
	setup();
}

Monitor::~Monitor() {
	// TODO Auto-generated destructor stub
}


void Monitor::setup() {
	mEntity = mSceneMgr->createEntity("monitor1", "monitor.mesh");
	mSceneNode = mSceneMgr->createSceneNode("monitor1");
	mSceneMgr->getRootSceneNode()->addChild(mSceneNode);
	mSceneNode->attachObject(mEntity);
	mSceneNode->setPosition(-ROOM_WIDTH/2+60,55,-30);
	mSceneNode->yaw(Ogre::Degree(90));
	mSceneNode->scale(0.00003,0.00003,0.00003);
}


bool Monitor::canUse(CharacterController* character)
{
	return mEntity->getWorldBoundingBox().intersects(character->getBoundingBox());
}

void Monitor::highlight(bool highlight) {
	bool hCur = mSceneNode->getShowBoundingBox();
	if ((hCur && !highlight) || (!hCur && highlight)) {
		mSceneNode->showBoundingBox(highlight);
	}
}
