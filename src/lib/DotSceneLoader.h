/*------------------------------------------------------------------------------
*  DotScene.h
*
*  This file provides some methods for the parsing of a .scene file, with
*  support for userData.
*
*  http://code.google.com/p/project-pr/source/browse/#svn%2Ftrunk%2Fportal_adaptation%2Fsrc%2Fmodel%2Fdotscene
*------------------------------------------------------------------------------*/

#ifndef DOT_SCENE_H
#define DOT_SCENE_H

#include <OGRE/OgreString.h>

#include <vector>
//#include "tinyxml.h"

namespace Ogre
{
	class SceneManager;
	class SceneNode;
}

class TiXmlElement;

class nodeProperty
{
	public:
		Ogre::String nodeName;
		Ogre::String propertyNm;
		Ogre::String valueName;

		nodeProperty(Ogre::String node, Ogre::String propertyName, Ogre::String value)
		{
			nodeName = node;
			propertyNm = propertyName;
			valueName = value;
		}
};

class DotSceneLoader
{
	public:
		DotSceneLoader() : mSceneMgr(0) {}
		virtual ~DotSceneLoader() {}

		void parseDotScene( const Ogre::String &sceneName, const Ogre::String& groupName, Ogre::SceneManager *yourSceneMgr, Ogre::SceneNode *attachNode = NULL, Ogre::String prependNode = "");
		Ogre::String getProperty(Ogre::String ndNm, Ogre::String prop); //ndNm = nodeName probably?

		std::vector<nodeProperty> nodeProperties;

	protected:
		void processNode(TiXmlElement *XMLNode, Ogre::SceneNode *pAttach);
		Ogre::SceneManager *mSceneMgr;
		Ogre::String m_sPrependNode;
};

#endif
