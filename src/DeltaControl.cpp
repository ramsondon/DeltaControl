/*
 -----------------------------------------------------------------------------
 Filename:    TutorialApplication.cpp
 -----------------------------------------------------------------------------

 This source file is part of the
 ___                 __    __ _ _    _
 /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
 / \_// (_| | | |  __/  \  /\  /| |   <| |
 \___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
 |___/
 Tutorial Framework
 http://www.ogre3d.org/tikiwiki/
 -----------------------------------------------------------------------------
 */
#include "DeltaControl.h"

//-------------------------------------------------------------------------------------
DeltaControl::DeltaControl(void) {
}
//-------------------------------------------------------------------------------------
DeltaControl::~DeltaControl(void) {
}

//-------------------------------------------------------------------------------------
void DeltaControl::createScene(void) {

	// OGRE Head
//	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
//	Ogre::SceneNode* headNode =
//			mSceneMgr->getRootSceneNode()->createChildSceneNode();
//	headNode->attachObject(ogreHead);

// Create the ground with grass on it
	Ogre::Plane plane;
	plane.normal = Ogre::Vector3::UNIT_Y;
	// horizontal plane with normal up in y-direction
	plane.d = 0; //Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("floor",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
			1000, 1000, 12, 12, true, 1, 12, 12, Ogre::Vector3::UNIT_Z);

	Ogre::Entity* pPlaneEnt = mSceneMgr->createEntity("plane", "floor");
	//pPlaneEnt->setMaterialName("Examples/GrassFloor");
	pPlaneEnt->setMaterialName("Examples/GrassFloor");
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
	//pPlaneEnt->setMaterialName("Examples/GrassFloor");
	pWall1->setMaterialName("Template/Rock");
	pWall1->setCastShadows(false);
	Ogre::SceneNode* wallNode1 = mSceneMgr->createSceneNode("wall1");
	mSceneMgr->getRootSceneNode()->addChild(wallNode1);
	wallNode1->attachObject(pWall1);
	wallNode1->setPosition(0,50,500);




	Ogre::Plane planeWall2;
	planeWall2.normal = Ogre::Vector3::UNIT_Z;
	// horizontal plane with normal up in y-direction
	planeWall2.d = 1000; //Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("wall2",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeWall2,
			1000, 100, 12, 12, true, 1, 12, 12, Ogre::Vector3::UNIT_Y);

	Ogre::Entity* pWall2 = mSceneMgr->createEntity("wall2", "wall2");
	pWall2->setMaterialName("Template/Rock");
	pWall2->setCastShadows(false);
	Ogre::SceneNode* wallNode2 = mSceneMgr->createSceneNode("wall2");
	mSceneMgr->getRootSceneNode()->addChild(wallNode2);
	wallNode2->attachObject(pWall2);
	wallNode2->setPosition(0,43,-500);
	wallNode2->rotate(Ogre::Vector3(500,0,0),Ogre::Radian(45), Ogre::Node::TS_WORLD);



	Ogre::Plane planeWall3;
		planeWall3.normal = Ogre::Vector3::UNIT_Z;
		// horizontal plane with normal up in y-direction
		planeWall3.d = 1000; //Plane passes through the origin i.e. plane at y = 0
		Ogre::MeshManager::getSingleton().createPlane("wall3",
				Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeWall3,
				1000, 100, 12, 12, true, 1, 12, 12, Ogre::Vector3::UNIT_Y);

		Ogre::Entity* pWall3 = mSceneMgr->createEntity("wall3", "wall3");
		pWall3->setMaterialName("Template/Rock");
		pWall3->setCastShadows(false);
		Ogre::SceneNode* wallNode3 = mSceneMgr->createSceneNode("wall3");
		mSceneMgr->getRootSceneNode()->addChild(wallNode3);
		wallNode3->attachObject(pWall3);
		wallNode3->setPosition(0,50,500);
		wallNode3->rotate(Ogre::Vector3(0,0,0),Ogre::Radian(90), Ogre::Node::TS_WORLD);



	/* *********************************************************
	 * ENTITIES
	 * *********************************************************/

	Ogre::Entity * cone = mSceneMgr->createEntity("torus", "Torus.mesh");
	cone->setMaterialName("Torus_defMat");
	Ogre::SceneNode* coneNode = mSceneMgr->createSceneNode("torus1");
	mSceneMgr->getRootSceneNode()->addChild(coneNode);
	coneNode->attachObject(cone);
	cone->setCastShadows(true);
	coneNode->scale(0.5, 0.5, 1);
	//coneNode->setPosition(0, 0, 0); // position

	Ogre::Entity * pyramid = mSceneMgr->createEntity("pyramid", "Tisch.mesh");
	//pyramid->setMaterialName("Template/texture_blend");
	pyramid->setMaterialName("Tischgestell");
	Ogre::SceneNode* pyramidNode = mSceneMgr->createSceneNode("pyramid1");
	mSceneMgr->getRootSceneNode()->addChild(pyramidNode);
	pyramidNode->attachObject(pyramid);
	pyramidNode->scale(5.5, 5.5, 2.5);
	pyramid->setCastShadows(true);
	//pyramidNode->setPosition(Ogre::Vector3(0, 0, 0.1)); // position
	pyramidNode->setPosition(2000, 0, -200); // position

	Ogre::Entity * ogreHead = mSceneMgr->createEntity("head", "ogrehead.mesh");
	Ogre::SceneNode* headNode = mSceneMgr->createSceneNode("head");
	mSceneMgr->getRootSceneNode()->addChild(headNode);
	headNode->attachObject(ogreHead);
	headNode->setPosition(0, 30, 0);

	Ogre::Entity * platonic = mSceneMgr->createEntity("platonic",
			"Platonic.mesh");
	platonic->setMaterialName("rock_lightmap");
	Ogre::SceneNode* platonicNode = mSceneMgr->createSceneNode("platonic1");
	mSceneMgr->getRootSceneNode()->addChild(platonicNode);
	platonicNode->attachObject(platonic);
	platonic->setCastShadows(true);
	//coneNode->setPosition(0, 0, 0); // position

	// Now to draw a ball on the ground at the origin
	// First create a ball Entity from an Ogre model
//	Ogre::Entity* ball = mSceneMgr->createEntity("sphere1",	"geosphere8000.mesh");
//	ball->setMaterialName("Examples/Hilite/Yellow");
//	double ballModelRadius = 200; // Radius of actual model in
//	//"geosphere8000.mesh"
//	double ballScale = 0.02;//To multiply radius by this factor
//	double ballRadius; // To store actual radius used here
//	// Create a new sceneNode and attach it to the rootSceneNode
//	//as a child of the scene manager
//	Ogre::SceneNode* ballNode = mSceneMgr->createSceneNode("sphere1");
//	mSceneMgr->getRootSceneNode()->addChild(ballNode);
//	ballNode->attachObject(ball);
//	// Amend the properties of the ball to suit your purposes
//	ball->setCastShadows(true);
//	ballNode->scale(ballScale, ballScale, ballScale);
//	ballRadius = ballScale * ballModelRadius; // Actual radius
//	ballNode->setPosition(Ogre::Vector3(0, ballRadius, 0)); // position
	//the ball on top of the ground
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
