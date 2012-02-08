/*
 File:    DeltaControl.cpp
 */
#include "DeltaControl.h"
#include "model/Telephone.h"

//-------------------------------------------------------------------------------------
DeltaControl::DeltaControl(void) {
}
//-------------------------------------------------------------------------------------
DeltaControl::~DeltaControl(void) {
}

//-------------------------------------------------------------------------------------
void DeltaControl::createScene(void) {

	mSceneMgr->setSkyBox(true, "Examples/StormySkyBox");

// Create the ground with grass on it
	Ogre::Plane plane;
	plane.normal = Ogre::Vector3::UNIT_Y;
	// horizontal plane with normal up in y-direction
	plane.d = 0; //Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("floor",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
			FLOOR_WIDTH, FLOOR_LENGTH, 1, 1, true, 1, 12, 12,
			Ogre::Vector3::UNIT_Z);

	Ogre::Entity* pPlaneEnt = mSceneMgr->createEntity("plane", "floor");
	pPlaneEnt->setMaterialName("floor");
	pPlaneEnt->setCastShadows(false);
	Ogre::SceneNode* floorNode = mSceneMgr->createSceneNode("floor1");
	mSceneMgr->getRootSceneNode()->addChild(floorNode);
	floorNode->attachObject(pPlaneEnt);

	/* *******************************************************
	 * WALL PLANES
	 * *******************************************************/

	Ogre::Plane planeWall1;
	planeWall1.normal = Ogre::Vector3::UNIT_Z;
	// horizontal plane with normal up in y-direction
	planeWall1.d = 1000; //Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("wall1",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeWall1,
			1000, 100, 12, 12, true, 1, 12, 12, Ogre::Vector3::UNIT_Y);

	Ogre::Entity* pWall1 = mSceneMgr->createEntity("wall1", "wall1");
	pWall1->setMaterialName("wall_light_grey");
	pWall1->setCastShadows(false);
	Ogre::SceneNode* wallNode1 = mSceneMgr->createSceneNode("wall1");
	mSceneMgr->getRootSceneNode()->addChild(wallNode1);
	wallNode1->attachObject(pWall1);
	wallNode1->setPosition(0, 50, 500);

	Ogre::Plane planeWall2;
	planeWall2.normal = Ogre::Vector3::UNIT_Z;
	// horizontal plane with normal up in y-direction
	planeWall2.d = 1000; //Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("wall2",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeWall2,
			1000, 100, 12, 12, true, 1, 12, 12, Ogre::Vector3::UNIT_Y);

	Ogre::Entity* pWall2 = mSceneMgr->createEntity("wall2", "wall2");
	pWall2->setMaterialName("wall_light_grey");
	pWall2->setCastShadows(false);
	Ogre::SceneNode* wallNode2 = mSceneMgr->createSceneNode("wall2");
	mSceneMgr->getRootSceneNode()->addChild(wallNode2);
	wallNode2->attachObject(pWall2);
	wallNode2->setPosition(0, 43, -500);
	wallNode2->rotate(Ogre::Vector3(500, 0, 0), Ogre::Radian(45),
			Ogre::Node::TS_WORLD);

	Ogre::Plane planeWall3;
	planeWall3.normal = Ogre::Vector3::UNIT_Z;
	// horizontal plane with normal up in y-direction
	planeWall3.d = 1000; //Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("wall3",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeWall3,
			1000, 100, 12, 12, true, 1, 12, 12, Ogre::Vector3::UNIT_Y);

	Ogre::Entity* pWall3 = mSceneMgr->createEntity("wall3", "wall3");
	pWall3->setMaterialName("Examples/GrassFloor");
	pWall3->setCastShadows(false);
	Ogre::SceneNode* wallNode3 = mSceneMgr->createSceneNode("wall3");
	mSceneMgr->getRootSceneNode()->addChild(wallNode3);
	wallNode3->attachObject(pWall3);
	wallNode3->setPosition(0, 50, 500);
	wallNode3->rotate(Ogre::Vector3(0, 0, 0), Ogre::Radian(90),
			Ogre::Node::TS_WORLD);

	/* *********************************************************
	 * ENTITIES
	 * *********************************************************/

//	Telephone* phone = new Telephone(mSceneMgr, "phone1");
//	phone->init();
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
