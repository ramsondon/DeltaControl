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
	mSceneNode->setPosition(-ROOM_WIDTH/2+48,55,-20);
	mSceneNode->yaw(Ogre::Degree(90));
	mSceneNode->scale(0.00003,0.00003,0.00003);


	Ogre::Entity* m2ent = mSceneMgr->createEntity("monitor2", "monitor.mesh");
	Ogre::SceneNode* m2node = mSceneMgr->createSceneNode("monitor2");
	mSceneMgr->getRootSceneNode()->addChild(m2node);
	m2node->attachObject(m2ent);
	m2node->setPosition(-ROOM_WIDTH/2+60,55,-60);
	m2node->yaw(Ogre::Degree(50));
	m2node->scale(0.00003,0.00003,0.00003);

	Ogre::Entity* m3ent = mSceneMgr->createEntity("monitor3", "monitor.mesh");
	Ogre::SceneNode* m3node = mSceneMgr->createSceneNode("monitor3");
	mSceneMgr->getRootSceneNode()->addChild(m3node);
	m3node->attachObject(m3ent);
	m3node->setPosition(-ROOM_WIDTH/2+100,55,-75);
	m3node->yaw(Ogre::Degree(0));
	m3node->scale(0.00003,0.00003,0.00003);
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
