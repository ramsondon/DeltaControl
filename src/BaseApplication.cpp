/*
 -----------------------------------------------------------------------------
 Filename:    BaseApplication.cpp
 -----------------------------------------------------------------------------

 */
#include "BaseApplication.h"

BaseApplication::BaseApplication(void) :
		mRoot(0), mCamera(0), mSceneMgr(0), mWindow(0), mResourcesCfg(
				Ogre::StringUtil::BLANK), mPluginsCfg(Ogre::StringUtil::BLANK), mTrayMgr(
				0), mCameraMan(0), mDetailsPanel(0), mCursorWasVisible(false), mShutDown(
				false), mInputManager(0), mMouse(0), mKeyboard(0) {

	mMove = false;
}

BaseApplication::~BaseApplication(void) {
	if (mTrayMgr)
		delete mTrayMgr;
	if (mCameraMan)
		delete mCameraMan;
	if (mCharacter)
		delete mCharacter;

	//Remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
	delete mRoot;
}

bool BaseApplication::configure(void) {
	// Show the configuration dialog and initialise the system
	// You can skip this and use root.restoreConfig() to load configuration
	// settings if you were sure there are valid ones saved in ogre.cfg
	if (mRoot->showConfigDialog()) {
		// If returned true, user clicked OK so initialise
		// Here we choose to let the system create a default rendering window by passing 'true'
		mWindow = mRoot->initialise(true, "DeltaControl Render Window");

		return true;
	} else {
		return false;
	}
}

void BaseApplication::chooseSceneManager(void) {
	/* Get the SceneManager, in this case a generic one
	 * ST_GENERIC - Generic scene manager (Octree if you load Plugin_OctreeSceneManager, DotScene if you load Plugin_DotSceneManager)
	 * ST_EXTERIOR_CLOSE - old Terrain Scene Manager
	 * ST_EXTERIOR_REAL_FAR - Paging Scene Manager
	 * ST_INTERIOR - BSP scene manager
	 */

	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
}

void BaseApplication::createCamera(void) {
	// Create the camera
	mCamera = mSceneMgr->createCamera("PlayerCam");

	// Position it at 500 in Z direction
	mCamera->setPosition(Ogre::Vector3(0, 50, 0));
	// Look back along -Z
	mCamera->lookAt(Ogre::Vector3(0, 50, 0));
	mCamera->setNearClipDistance(5);

	// mCameraMan = new OgreBites::SdkCameraMan(mCamera); // create a default camera controller
	mCamera->setFixedYawAxis(true);
}

void BaseApplication::createFrameListener(void) {
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem(pl);

	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(
			OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(
			OIS::OISMouse, true));

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

	//Set initial mouse clipping size
	windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mMouse,
			this);
	//mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	//mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
	mTrayMgr->hideCursor();

	// create a params panel for displaying sample details
	Ogre::StringVector items;
	items.push_back("Waterlevel");
	items.push_back("Money loss");
//
	mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_TOPRIGHT,
			"DetailsPanel", 200, items);
	mDetailsPanel->setParamValue(0, "normal");
	mDetailsPanel->setParamValue(1, "0");
	mDetailsPanel->show();


	mRoot->addFrameListener(this);
}

void BaseApplication::destroyScene(void) {
}

void BaseApplication::createViewports(void) {
	// Create one viewport, entire window
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(
			Ogre::Real(vp->getActualWidth())
					/ Ogre::Real(vp->getActualHeight()));
}

void BaseApplication::setupResources(void) {
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements()) {
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i) {
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
					archName, typeName, secName);
		}
	}
}

void BaseApplication::createResourceListener(void) {

}

void BaseApplication::loadResources(void) {
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void BaseApplication::go(void) {
#ifdef _DEBUG
	mResourcesCfg = "resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#else
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
#endif

	if (!setup())
		return;

	mRoot->startRendering();

	// clean up
	destroyScene();
}

bool BaseApplication::setup(void) {
	mRoot = new Ogre::Root(mPluginsCfg);

	setupResources();

	bool carryOn = configure();
	if (!carryOn)
		return false;

	chooseSceneManager();
	createCamera();
	createViewports();

	// Set default mipmap level (NB some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// Create any resource listeners (for loading screens)
	createResourceListener();
	// Load resources
	loadResources();

	// Create the scene
	createScene();

	createFrameListener();

	return true;
}

bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	if (mWindow->isClosed())
		return false;

	if (mShutDown)
		return false;

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	mTrayMgr->frameRenderingQueued(evt);

	if (!mTrayMgr->isDialogVisible()) {

		// let the character update the camera and animations
		mCharacter->addTime(evt.timeSinceLastFrame);
	}

	return true;
}

bool BaseApplication::keyPressed(const OIS::KeyEvent &arg) {
	if (mTrayMgr->isDialogVisible())
		return true; // don't process any more keys if dialog is up

	if (arg.key == OIS::KC_ESCAPE)
		mShutDown = true;

	// inject keyPressed to character
	mCharacter->injectKeyDown(arg);

	return true;
}

bool BaseApplication::keyReleased(const OIS::KeyEvent &arg) {
	mCharacter->injectKeyUp(arg);
	return true;
}

bool BaseApplication::mouseMoved(const OIS::MouseEvent &arg) {
	if (mTrayMgr->injectMouseMove(arg)) {
		return true;
	}

	mCharacter->injectMouseMove(arg);
	return true;
}

bool BaseApplication::mousePressed(const OIS::MouseEvent &arg,
		OIS::MouseButtonID id) {
	if (mTrayMgr->injectMouseDown(arg, id)) {
		return true;
	}
	mCharacter->injectMouseDown(arg, id);
	return true;
}

bool BaseApplication::mouseReleased(const OIS::MouseEvent &arg,
		OIS::MouseButtonID id) {
	if (mTrayMgr->injectMouseUp(arg, id)) {
		return true;
	}

	return true;
}

//Adjust mouse clipping area
void BaseApplication::windowResized(Ogre::RenderWindow* rw) {
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void BaseApplication::windowClosed(Ogre::RenderWindow* rw) {
	//Only close for window that created OIS (the main window in these demos)
	if (rw == mWindow) {
		if (mInputManager) {
			mInputManager->destroyInputObject(mMouse);
			mInputManager->destroyInputObject(mKeyboard);

			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}
}
