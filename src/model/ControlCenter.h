/*
 * ControlCenter.h
 *
 *  Created on: Feb 8, 2012
 *      Author: matthias
 */

#ifndef CONTROLCENTER_H_
#define CONTROLCENTER_H_

#define ROOM_WIDTH 	600
#define ROOM_LENGTH	800
#define ROOM_HEIGHT	200


#include <OgreSceneManager.h>

class ControlCenter {

private:
	Ogre::SceneManager* mSceneMgr;
	Ogre::Entity* mWallLeft;
	Ogre::Entity* mWallRight;
	Ogre::Entity* mWallBack;
	Ogre::Entity* mWallFront;
	Ogre::Entity* mPillarLeft;
	Ogre::Entity* mPillarMiddle;
	Ogre::Entity* mPillarRight;


	void setup();
	void setupRoof();
	void setupFloor();
	void setupWalls();
	void setupWindowWall();
	void setupWoodenWalls();

public:
	ControlCenter(Ogre::SceneManager* sceneMgr);
	virtual ~ControlCenter();
	bool intersects(const Ogre::AxisAlignedBox & box);
};

#endif /* CONTROLCENTER_H_ */
