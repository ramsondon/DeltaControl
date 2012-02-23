/*
 * GamePanel.h
 *
 *  Created on: Feb 23, 2012
 *      Author: matthias
 */

#ifndef GAMEPANEL_H_
#define GAMEPANEL_H_

#include <OIS.h>
#include <SdkTrays.h>
#include <OgreStringVector.h>
#include <OgreString.h>

class GamePanel {

protected:
	OgreBites::SdkTrayManager* mTrayMgr;
	Ogre::StringVector mItems;

public:

	GamePanel(){};

	GamePanel(OgreBites::SdkTrayManager* trayMgr)
	{
		mTrayMgr = trayMgr;
	}

	virtual ~GamePanel() {}

	void addItem(Ogre::String string)
	{
		mItems.push_back(string.c_str());
	}

	void setTrayManager(OgreBites::SdkTrayManager* trayMgr)
	{
		mTrayMgr = trayMgr;
	}

	virtual void createAndShow() = 0;

};

#endif /* GAMEPANEL_H_ */
