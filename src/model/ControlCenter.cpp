/*
 * ControlCenter.cpp
 *
 *  Created on: Feb 8, 2012
 *      Author: matthias
 */

#include <OgreSceneManager.h>
#include <OgreMeshManager.h>
#include <OgreResourceGroupManager.h>
#include <OgreEntity.h>

#include "ControlCenter.h"


ControlCenter::ControlCenter(Ogre::SceneManager* sceneMgr) {

	mSceneMgr = sceneMgr;
	setup();
}

ControlCenter::~ControlCenter() {
}

void ControlCenter::setup()
{
	setupFloor();
	setupRoof();
	setupWalls();
}

void ControlCenter::setupFloor()
{
	Ogre::Plane plane;
	plane.normal = Ogre::Vector3::UNIT_Y;
	// horizontal plane with normal up in y-direction
	plane.d = 0; //Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("floor",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
			ROOM_WIDTH, ROOM_LENGTH, 1, 1, true, 1, 12, 12,
			Ogre::Vector3::UNIT_Z);

	Ogre::Entity* pPlaneEnt = mSceneMgr->createEntity("plane", "floor");
	pPlaneEnt->setMaterialName("floor");
	pPlaneEnt->setCastShadows(false);
	Ogre::SceneNode* floorNode = mSceneMgr->createSceneNode("floor1");
	mSceneMgr->getRootSceneNode()->addChild(floorNode);
	floorNode->attachObject(pPlaneEnt);
}

void ControlCenter::setupRoof() {
	// Tap
	Ogre::Plane planeTap;
	planeTap.normal = Ogre::Vector3::UNIT_Y;
	planeTap.d = 0; //Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("tap",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeTap,
			ROOM_WIDTH, ROOM_LENGTH, 1, 1, true, 1, 12, 12,
			Ogre::Vector3::UNIT_Z);

	Ogre::Entity* tapEntity = mSceneMgr->createEntity("tap", "tap");
	tapEntity->setMaterialName("roof_white");
	tapEntity->setCastShadows(false);
	Ogre::SceneNode* tapNode = mSceneMgr->createSceneNode("tap");
	mSceneMgr->getRootSceneNode()->addChild(tapNode);
	tapNode->attachObject(tapEntity);
	tapNode->pitch(Ogre::Degree(180));
	tapNode->setPosition(0, ROOM_HEIGHT, 0);
}

void ControlCenter::setupWalls()
{

	/* *******************************************************
	 * WALL PLANES
	 * *******************************************************/
	setupWindowWall();
	setupWoodenWalls();


	Ogre::Plane planeWall1;
	planeWall1.normal = Ogre::Vector3::UNIT_Z;
	// horizontal plane with normal up in y-direction
	planeWall1.d = 0; //Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("wallright",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeWall1,
			ROOM_WIDTH, ROOM_HEIGHT, 12, 12, true, 1, 12, 12, Ogre::Vector3::UNIT_Y);

	mWallRight = mSceneMgr->createEntity("wallright", "wallright");
	mWallRight->setMaterialName("wall_light_grey");
	mWallRight->setCastShadows(false);
	Ogre::SceneNode* wallNode1 = mSceneMgr->createSceneNode("wallright");
	mSceneMgr->getRootSceneNode()->addChild(wallNode1);
	wallNode1->attachObject(mWallRight);
	wallNode1->setPosition(0,ROOM_HEIGHT/2, -ROOM_LENGTH/2);

	Ogre::Plane planeWall2;
	planeWall2.normal = Ogre::Vector3::UNIT_Z;
	// horizontal plane with normal up in y-direction
	planeWall2.d = 0; //Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("wallleft",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeWall2,
			ROOM_WIDTH, ROOM_HEIGHT, 12, 12, true, 1, 12, 12, Ogre::Vector3::UNIT_Y);

	mWallLeft = mSceneMgr->createEntity("wallleft", "wallleft");
	mWallLeft->setMaterialName("wall_light_grey");
	mWallLeft->setCastShadows(false);
	Ogre::SceneNode* wallNode2 = mSceneMgr->createSceneNode("wallleft");
	mSceneMgr->getRootSceneNode()->addChild(wallNode2);
	wallNode2->attachObject(mWallLeft);
	wallNode2->rotate(Ogre::Vector3(-ROOM_LENGTH/2, 0, 0), Ogre::Radian(45),
			Ogre::Node::TS_WORLD);
	wallNode2->setPosition(0, ROOM_HEIGHT/2, ROOM_LENGTH/2);



	// wall length
	Ogre::Plane planeWall4;
	planeWall4.normal = Ogre::Vector3::UNIT_Z;
	// horizontal plane with normal up in y-direction
	planeWall4.d = 0; //Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("wallback",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeWall4,
			ROOM_LENGTH, ROOM_HEIGHT, 12, 12, true, 1, 12, 12, Ogre::Vector3::UNIT_Y);

	mWallBack = mSceneMgr->createEntity("wallback", "wallback");
	mWallBack->setMaterialName("wall_light_grey");
	mWallBack->setCastShadows(false);
	Ogre::SceneNode* wallNode4 = mSceneMgr->createSceneNode("wallback");
	mSceneMgr->getRootSceneNode()->addChild(wallNode4);
	wallNode4->attachObject(mWallBack);
	wallNode4->yaw(Ogre::Degree(270));
	wallNode4->setPosition(ROOM_WIDTH/2, ROOM_HEIGHT/2, 0);
}

void ControlCenter::setupWindowWall()
{
	// wall glass
	Ogre::Plane planeWall3;
	planeWall3.normal = Ogre::Vector3::UNIT_Z;
	planeWall3.d = 0;
	Ogre::MeshManager::getSingleton().createPlane("window",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeWall3,
			ROOM_LENGTH, ROOM_HEIGHT, 12, 12, true, 1, 12, 12, Ogre::Vector3::UNIT_Y);



	Ogre::Entity* winEnt = mSceneMgr->createEntity("window", "window");
	winEnt->setMaterialName("window");
	Ogre::SceneNode* winNode = mSceneMgr->createSceneNode("window");
	mSceneMgr->getRootSceneNode()->addChild(winNode);
	winNode->attachObject(winEnt);
	winNode->yaw(Ogre::Degree(90));
	winNode->setPosition(-ROOM_WIDTH/2+1, ROOM_HEIGHT/2, 0);



	mPillarRight = mSceneMgr->createEntity("pillarright", "Cube.mesh");
	Ogre::SceneNode* pillarN1 = mSceneMgr->createSceneNode("pillarright");
	mSceneMgr->getRootSceneNode()->addChild(pillarN1);
	pillarN1->attachObject(mPillarRight);
	pillarN1->scale(0.5, 8, 0.5);
	pillarN1->setPosition(-ROOM_WIDTH/2+12, 0, ROOM_LENGTH/2+156);
	mPillarRight->setMaterialName("pillar");

	mPillarLeft = mSceneMgr->createEntity("pillarleft", "Cube.mesh");
	Ogre::SceneNode* pillarN2 = mSceneMgr->createSceneNode("pillarleft");
	mSceneMgr->getRootSceneNode()->addChild(pillarN2);
	pillarN2->attachObject(mPillarLeft);
	pillarN2->scale(0.5, 8, 0.5);
	pillarN2->setPosition(-ROOM_WIDTH/2+12, 0, -(ROOM_LENGTH/2-180));
	mPillarLeft->setMaterialName("pillar");

	mPillarMiddle = mSceneMgr->createEntity("pillarmiddle", "Cube.mesh");
	Ogre::SceneNode* pillarN3 = mSceneMgr->createSceneNode("pillarmiddle");
	mSceneMgr->getRootSceneNode()->addChild(pillarN3);
	pillarN3->attachObject(mPillarMiddle);
	pillarN3->scale(0.5, 8, 0.5);
	pillarN3->setPosition(-ROOM_WIDTH/2+12, 0, 186);
	mPillarMiddle->setMaterialName("pillar");

}

void ControlCenter::setupWoodenWalls() {
	mWallFront = mSceneMgr->createEntity("wallfront", "Cube.mesh");
	Ogre::SceneNode* woodenN1 = mSceneMgr->createSceneNode("wallfront");
	mSceneMgr->getRootSceneNode()->addChild(woodenN1);
	woodenN1->attachObject(mWallFront);
	woodenN1->scale(0.3, 1.8, 17);
	woodenN1->setPosition(-ROOM_WIDTH/2+8, 0, ROOM_LENGTH*7+120);
	mWallFront->setMaterialName("floor");
}

bool ControlCenter::intersects(const Ogre::AxisAlignedBox & box) {

	if (mWallBack->getWorldBoundingBox().intersects(box)) {
		return true;
	} else if (mWallLeft->getWorldBoundingBox().intersects(box)) {
		return true;
	} else if (mWallRight->getWorldBoundingBox().intersects(box)) {
		return true;
	} else if (mWallFront->getWorldBoundingBox().intersects(box)) {
		return true;
	} else if (mPillarLeft->getWorldBoundingBox().intersects(box)) {
		return true;
	} else if (mPillarMiddle->getWorldBoundingBox().intersects(box)) {
		return true;
	} else if (mPillarRight->getWorldBoundingBox().intersects(box)) {
		return true;
	}

	return false;
}
