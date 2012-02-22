/*
 * Terrain.cpp
 *
 *  Created on: Feb 9, 2012
 *      Author: matthias
 */


#include <OgreMeshManager.h>

#include "Terrain.h"

Terrain::Terrain(Ogre::SceneManager* sceneMgr) {
	// TODO Auto-generated constructor stub
	mSceneMgr = sceneMgr;
	setup();
}

Terrain::~Terrain() {
}

void Terrain::setup() {

	Ogre::Plane oceanSurface;
	oceanSurface.normal = Ogre::Vector3::UNIT_Y;
	oceanSurface.d = -150;
	Ogre::MeshManager::getSingleton().createPlane("OceanSurface",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		oceanSurface,
		1000, 1000, 50, 50, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);

	mOceanSurfaceEnt = mSceneMgr->createEntity( "OceanSurface", "OceanSurface" );
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(mOceanSurfaceEnt);
}
