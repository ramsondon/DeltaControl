/*
 File:    DeltaControl.cpp
 */
#include "DeltaControl.h"
#include "model/ControlCenter.h"
//#include "model/Telephone.h"

//-------------------------------------------------------------------------------------
DeltaControl::DeltaControl(void) {
}
//-------------------------------------------------------------------------------------
DeltaControl::~DeltaControl(void) {
}

//-------------------------------------------------------------------------------------
void DeltaControl::createScene(void) {

	mSceneMgr->setSkyBox(true, "Examples/MyStormySkyBox");

	ControlCenter* controlCenter = new ControlCenter(mSceneMgr);

	/* *********************************************************
	 * ENTITIES
	 * *********************************************************/

//	Telephone* phone = new Telephone(mSceneMgr, "phone1");
//	phone->init();

	// Create entity from mesh and attach it to a scene node.
	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* ent = mSceneMgr->createEntity("Sinbad", "Sinbad.mesh");
	node->attachObject(ent);
	node->setPosition(0,50,0);
	node->scale(10,10,10);

	// Set animation blend mode to additive / cumulative.
	ent->getSkeleton()->setBlendMode(Ogre::ANIMBLEND_CUMULATIVE);

	// Get the two halves of the idle animation
	Ogre::AnimationState* baseAnim = ent->getAnimationState("IdleBase");
	Ogre::AnimationState* topAnim = ent->getAnimationState("IdleTop");

	// Enable both of them and set them to loop.
	baseAnim->setLoop(true);
	topAnim->setLoop(true);
	baseAnim->setEnabled(true);
	topAnim->setEnabled(true);

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
