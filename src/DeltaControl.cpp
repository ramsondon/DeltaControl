/*
 File:    DeltaControl.cpp
 */
#include "DeltaControl.h"
#include "model/ControlCenter.h"
#include "model/Telephone.h"
#include "model/Table.h"


//-------------------------------------------------------------------------------------
DeltaControl::DeltaControl(void) {
}
//-------------------------------------------------------------------------------------
DeltaControl::~DeltaControl(void) {
}

//-------------------------------------------------------------------------------------
void DeltaControl::createScene(void) {

	mSceneMgr->setSkyBox(true, "StormySkyBox");

	// Terrain* terrain = new Terrain(mSceneMgr);
	mControlCenter = new ControlCenter(mSceneMgr);
	mCharacter = new CharacterController(mCamera);

	Table* table = new Table(mSceneMgr);

	mPhone = new Telephone(mSceneMgr, "phone1");

}

bool DeltaControl::frameRenderingQueued(const Ogre::FrameEvent& evt)
{

	bool ret = BaseApplication::frameRenderingQueued(evt);
	mPhone->highlight(mPhone->canUse(mCharacter));




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
