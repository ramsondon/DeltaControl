/*
 * Terrain.h
 *
 *  Created on: Feb 9, 2012
 *      Author: matthias
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_

#include <OgreSceneManager.h>
#include <OgreEntity.h>

class Terrain {

private:
	Ogre::SceneManager* mSceneMgr;

	Ogre::Entity* mOceanSurfaceEnt;

	void setup();

public:
	Terrain(Ogre::SceneManager* sceneMgr);
	virtual ~Terrain();
};

#endif /* TERRAIN_H_ */
