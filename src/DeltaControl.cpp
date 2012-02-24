/*
 File:    DeltaControl.cpp
 */
#include "DeltaControl.h"
#include "model/ControlCenter.h"
#include "model/Telephone.h"
//#include "model/Table.h"
#include "model/Monitor.h"
#include <OgreResourceGroupManager.h>
#include <OgreLight.h>

#include "lib/DotSceneLoader.h"


DeltaControl::DeltaControl(void) {
}

DeltaControl::~DeltaControl(void) {
}

void DeltaControl::createScene(void) {

	mSceneMgr->setSkyBox(true, "StormySkyBox");

	// Terrain* terrain = new Terrain(mSceneMgr);

	mControlCenter = new ControlCenter(mSceneMgr);
	mCharacter = new CharacterController(mCamera);

	//mTable = new Table(mSceneMgr);

	DotSceneLoader* sceneLoader = new DotSceneLoader();
	Ogre::SceneNode* roomNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("room1");
	roomNode->yaw(Ogre::Degree(90));
	roomNode->setPosition(650,0,200);
	sceneLoader->parseDotScene("TCOO_Scene.scene",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, mSceneMgr, roomNode);

	mMonitor = new Monitor(mSceneMgr, mCharacter);
	mPhone = new Telephone(mSceneMgr, mCharacter);


	// set lightning
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2,0.2,0.2));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
	pointLight->setType(Ogre::Light::LT_POINT);
	pointLight->setPosition(Ogre::Vector3(0, 150, 250));

	pointLight->setDiffuseColour(0.95, 0.95, 0.95);
	pointLight->setSpecularColour(0.95, 0.95, 0.95);
}

void DeltaControl::createFrameListener(void) {
	BaseApplication::createFrameListener();

	mPhone->setTrayManager(mTrayMgr);
}


bool DeltaControl::frameRenderingQueued(const Ogre::FrameEvent& evt) {

	bool ret = BaseApplication::frameRenderingQueued(evt);
	UsableObject* object = NULL;
	if (mPhone->canUse()) {
		mPhone->highlight(true);
		mMonitor->unuse();
		object = mPhone;
	} else if (mMonitor->canUse()) {
		mMonitor->highlight(true);
		mPhone->unuse();
		object = mMonitor;
	}
	mCharacter->setUsableObject(object);

	//mCharacter->setMove(!mControlCenter->intersects(mCharacter->getBoundingBox()));

	return ret;
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main(int argc, char *argv[])
#endif
		{
	// Create application object
	DeltaControl app;

	try {
		app.go();
	} catch (Ogre::Exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occured: "
				<< e.getFullDescription().c_str() << std::endl;
#endif
	}

	return 0;
}

#ifdef __cplusplus
}
#endif
