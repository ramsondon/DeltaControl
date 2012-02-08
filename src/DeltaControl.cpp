/*
 File:    DeltaControl.cpp
 */
#include "DeltaControl.h"
//#include "model/Telephone.h"

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
			ROOM_WIDTH, ROOM_LENGTH, 1, 1, true, 1, 12, 12,
			Ogre::Vector3::UNIT_Z);

	Ogre::Entity* pPlaneEnt = mSceneMgr->createEntity("plane", "floor");
	pPlaneEnt->setMaterialName("floor");
	pPlaneEnt->setCastShadows(false);
	Ogre::SceneNode* floorNode = mSceneMgr->createSceneNode("floor1");
	mSceneMgr->getRootSceneNode()->addChild(floorNode);
	floorNode->attachObject(pPlaneEnt);

	// Tap

	Ogre::Plane planeTap;
	planeTap.normal = Ogre::Vector3::UNIT_Y;
	planeTap.d = 0; //Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("tap",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
			ROOM_WIDTH, ROOM_LENGTH, 1, 1, true, 1, 12, 12,
			Ogre::Vector3::UNIT_Z);

	Ogre::Entity* tapEntity = mSceneMgr->createEntity("tap", "tap");
	tapEntity->setMaterialName("wall_light_grey");
	tapEntity->setCastShadows(false);
	Ogre::SceneNode* tapNode = mSceneMgr->createSceneNode("tap");
	mSceneMgr->getRootSceneNode()->addChild(tapNode);
	tapNode->attachObject(tapEntity);
	tapNode->pitch(Ogre::Degree(180));
	tapNode->setPosition(0, ROOM_HEIGHT, 0);

	/* *******************************************************
	 * WALL PLANES
	 * *******************************************************/

	Ogre::Plane planeWall1;
	planeWall1.normal = Ogre::Vector3::UNIT_Z;
	// horizontal plane with normal up in y-direction
	planeWall1.d = 0; //Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("wall1",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeWall1,
			ROOM_WIDTH, ROOM_HEIGHT, 12, 12, true, 1, 12, 12, Ogre::Vector3::UNIT_Y);

	Ogre::Entity* pWall1 = mSceneMgr->createEntity("wall1", "wall1");
	pWall1->setMaterialName("wall_light_grey");
	pWall1->setCastShadows(false);
	Ogre::SceneNode* wallNode1 = mSceneMgr->createSceneNode("wall1");
	mSceneMgr->getRootSceneNode()->addChild(wallNode1);
	wallNode1->attachObject(pWall1);
	wallNode1->setPosition(0,ROOM_HEIGHT/2, -ROOM_LENGTH/2);

	Ogre::Plane planeWall2;
	planeWall2.normal = Ogre::Vector3::UNIT_Z;
	// horizontal plane with normal up in y-direction
	planeWall2.d = 0; //Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("wall2",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeWall2,
			ROOM_WIDTH, ROOM_HEIGHT, 12, 12, true, 1, 12, 12, Ogre::Vector3::UNIT_Y);

	Ogre::Entity* pWall2 = mSceneMgr->createEntity("wall2", "wall2");
	pWall2->setMaterialName("wall_light_grey");
	pWall2->setCastShadows(false);
	Ogre::SceneNode* wallNode2 = mSceneMgr->createSceneNode("wall2");
	mSceneMgr->getRootSceneNode()->addChild(wallNode2);
	wallNode2->attachObject(pWall2);
	wallNode2->rotate(Ogre::Vector3(-ROOM_LENGTH/2, 0, 0), Ogre::Radian(45),
			Ogre::Node::TS_WORLD);
	wallNode2->setPosition(0, ROOM_HEIGHT/2, ROOM_LENGTH/2);


	// wall glass
	Ogre::Plane planeWall3;
	planeWall3.normal = Ogre::Vector3::UNIT_Z;
	planeWall3.d = 0;
	Ogre::MeshManager::getSingleton().createPlane("window",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeWall3,
			ROOM_LENGTH, ROOM_HEIGHT, 12, 12, true, 1, 12, 12, Ogre::Vector3::UNIT_Y);



	Ogre::Entity* winEnt = mSceneMgr->createEntity("window", "window");
	winEnt->setMaterialName("window");
	Ogre::SceneNode* winNode = mSceneMgr->createSceneNode("window");
	mSceneMgr->getRootSceneNode()->addChild(winNode);
	winNode->attachObject(winEnt);
	winNode->yaw(Ogre::Degree(90));
	winNode->setPosition(-ROOM_WIDTH/2+1, ROOM_HEIGHT/2, 0);



	Ogre::Entity* pillar1 = mSceneMgr->createEntity("p1", "Cube.mesh");
	Ogre::SceneNode* pillarN1 = mSceneMgr->createSceneNode("p1");
	mSceneMgr->getRootSceneNode()->addChild(pillarN1);
	pillarN1->attachObject(pillar1);
	pillarN1->scale(0.5, 8, 0.5);
	pillarN1->setPosition(-ROOM_WIDTH/2+12, 0, ROOM_LENGTH/2+156);
	pillar1->setMaterialName("pillar");

	Ogre::Entity* pillar2 = mSceneMgr->createEntity("p2", "Cube.mesh");
	Ogre::SceneNode* pillarN2 = mSceneMgr->createSceneNode("p2");
	mSceneMgr->getRootSceneNode()->addChild(pillarN2);
	pillarN2->attachObject(pillar2);
	pillarN2->scale(0.5, 8, 0.5);
	pillarN2->setPosition(-ROOM_WIDTH/2+12, 0, -(ROOM_LENGTH/2-180));
	pillar2->setMaterialName("pillar");

	Ogre::Entity* pillar3 = mSceneMgr->createEntity("p3", "Cube.mesh");
	Ogre::SceneNode* pillarN3 = mSceneMgr->createSceneNode("p3");
	mSceneMgr->getRootSceneNode()->addChild(pillarN3);
	pillarN3->attachObject(pillar3);
	pillarN3->scale(0.5, 8, 0.5);
	pillarN3->setPosition(-ROOM_WIDTH/2+12, 0, 186);
	pillar3->setMaterialName("pillar");



	// wall length
	Ogre::Plane planeWall4;
	planeWall4.normal = Ogre::Vector3::UNIT_Z;
	// horizontal plane with normal up in y-direction
	planeWall4.d = 0; //Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("wall4",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeWall4,
			ROOM_LENGTH, ROOM_HEIGHT, 12, 12, true, 1, 12, 12, Ogre::Vector3::UNIT_Y);

	Ogre::Entity* pWall4 = mSceneMgr->createEntity("wall4", "wall4");
	pWall4->setMaterialName("wall_light_grey");
	pWall4->setCastShadows(false);
	Ogre::SceneNode* wallNode4 = mSceneMgr->createSceneNode("wall4");
	mSceneMgr->getRootSceneNode()->addChild(wallNode4);
	wallNode4->attachObject(pWall4);
	wallNode4->yaw(Ogre::Degree(270));
	wallNode4->setPosition(ROOM_WIDTH/2, ROOM_HEIGHT/2, 0);


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
