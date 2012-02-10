/*
 * Table.cpp
 *
 *  Created on: Feb 9, 2012
 *      Author: matthias
 */

#include "ControlCenter.h"
#include "Table.h"

Table::Table(Ogre::SceneManager* sceneMgr) {
	mSceneMgr = sceneMgr;
	setup();
}

Table::~Table() {
}

void Table::setup() {
		mEntity = mSceneMgr->createEntity("table", "Desk.mesh");
		mEntity->setMaterialName("Default");
		mSceneNode = mSceneMgr->createSceneNode("table");
		mSceneMgr->getRootSceneNode()->addChild(mSceneNode);
		mSceneNode->attachObject(mEntity);
		mSceneNode->setPosition(-ROOM_WIDTH/2+30,0,-95);
		mSceneNode->yaw(Ogre::Degree(90));
		mSceneNode->scale(75,75,75);

//		Ogre::Entity* table2 = mSceneMgr->createEntity("table2", "Desk.mesh");
//		Ogre::SceneNode* t2node = mSceneMgr->createSceneNode("table2");
//		mSceneMgr->getRootSceneNode()->addChild(t2node);
//		t2node->attachObject(table2);
//		t2node->setPosition(-ROOM_WIDTH/2+30,0,-95);
//		t2node->yaw(Ogre::Degree(180));
//		t2node->scale(75,75,75);

		Ogre::Entity* monitor1 = mSceneMgr->createEntity("monitor1", "monitor.mesh");
		Ogre::SceneNode* m1Node = mSceneMgr->createSceneNode("monitor1");
		mSceneMgr->getRootSceneNode()->addChild(m1Node);
		m1Node->attachObject(monitor1);
		m1Node->setPosition(-ROOM_WIDTH/2+60,55,-30);
		m1Node->yaw(Ogre::Degree(270));
		m1Node->scale(0.00003,0.00003,0.00003);
}
