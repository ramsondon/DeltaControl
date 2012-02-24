/*
 * Telephone.cpp
 *
 *  Created on: Feb 6, 2012
 *      Author: matthias schmid
 */

#include <OgreSceneManager.h>
#include <OIS.h>
#include <SdkTrays.h>
#include <OgreStringVector.h>
#include "../CharacterController.h"
#include "Telephone.h"

Telephone::Telephone(Ogre::SceneManager* sceneMgr, CharacterController* cc) :
		UsableObject(sceneMgr, cc), GamePanel() {
	setup();
}

Telephone::~Telephone() {
}

// setup must set SceneNode and Entity
void Telephone::setup() {
	mSceneNode = mSceneMgr->getSceneNode("Telefon_body");
	mEntity = mSceneMgr->getEntity("Telefon_body");

	addItem("None");
	addItem("Supervisor");
	addItem("Firebrigade");
	addItem("Tower");
}

void Telephone::highlight(bool highlight) {
	if (highlight) {
		mEntity->setMaterialName("phone1");
	} else {
		mEntity->setMaterialName("NoMaterial");
	}
}

void Telephone::use() {

	// notify observers
	UsableObject::use();

	// create user interaction dialog
	createAndShow();
}

void Telephone::unuse() {
	UsableObject::unuse();

	mTrayMgr->hideCursor();
	mTrayMgr->destroyAllWidgetsInTray(OgreBites::TL_CENTER);
}

void Telephone::createAndShow() {
	LogManager::getSingleton().logMessage("show telephone panel");


	mTrayMgr->setWidgetSpacing(5);
	mTrayMgr->setWidgetPadding(10);

	mTrayMgr->createThickSelectMenu(
			OgreBites::TL_CENTER, "a2", "Address Book", 600,
			5, mItems);


	OgreBites::Button* button1 = mTrayMgr->createButton(OgreBites::TL_CENTER,
			"b1", "Call", 100);
	OgreBites::Button* button2 = mTrayMgr->createButton(OgreBites::TL_CENTER,
				"b2", "Dismiss", 100);

	button1->_assignListener(this);
	button2->_assignListener(this);

	mTrayMgr->showCursor();

}

void Telephone::buttonHit(OgreBites::Button* button) {

	SdkTrayListener::buttonHit(button);
	this->unuse();
}

