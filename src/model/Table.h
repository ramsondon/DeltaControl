/*
 * Table.h
 *
 *  Created on: Feb 9, 2012
 *      Author: matthias
 */

#ifndef TABLE_H_
#define TABLE_H_

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>

class Table {

private:
	Ogre::SceneManager* mSceneMgr;
	Ogre::Entity* mEntity;
	Ogre::SceneNode* mSceneNode;
public:
	Table(Ogre::SceneManager* sceneMgr);
	virtual ~Table();

	void setup();
};

#endif /* TABLE_H_ */
