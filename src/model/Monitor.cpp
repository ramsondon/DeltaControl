/*
 * Monitor.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: matthias
 */

#include "Monitor.h"
#include "UsableObject.h"
#include "ControlCenter.h"

Monitor::Monitor(Ogre::SceneManager* sceneMgr, CharacterController* cc) :
		UsableObject(sceneMgr, cc) {
	setup();
}

Monitor::~Monitor() {
}

void Monitor::setup() {

	// primary monitor -> right monitor
	mEntity = mSceneMgr->getEntity(
			"FBXASC0504zollFBXASC045ScreenFBXASC045BildFBXASC0462");
	mSceneNode = mSceneMgr->getSceneNode("FBXASC0504zollFBXASC045ScreenFBXASC045BildFBXASC0462");

	// left monitor
	mMonitorLeft = mSceneMgr->getEntity(
			"FBXASC0504zollFBXASC045ScreenFBXASC045Bild");
	mMonitorLeftSceneNode = mSceneMgr->getSceneNode("FBXASC0504zollFBXASC045ScreenFBXASC045Bild");


	mEntity->setMaterialName("monitor_left");
	mMonitorLeft->setMaterialName("monitor_right");
}

void Monitor::highlight(bool highlight) {
	if (highlight) {
		mEntity->setMaterialName("monitor_highlight");
		mMonitorLeft->setMaterialName("monitor_highlight");
	} else {
		mEntity->setMaterialName("monitor_left");
		mMonitorLeft->setMaterialName("monitor_right");
	}
}

bool Monitor::canUse() {
	if (!mEntity->getWorldBoundingBox().intersects(mCharacterController->getBoundingBox())) {
		return 	mMonitorLeft->getWorldBoundingBox().intersects(mCharacterController->getBoundingBox());
	}
	return true;
}
