/*
 * CharacterController.cpp
 *
 *  Created on: 08.02.2012
 *      Author: Florian
 */

#include "CharacterController.h"
#include "model/UsableObject.h"

using namespace Ogre;

CharacterController::CharacterController(Camera* cam) {
	mSceneMgr = cam->getSceneManager();
	setupBody(mSceneMgr);
	setupCamera(cam);
	setupAnimations();
	mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());
}

CharacterController::~CharacterController() { }


void CharacterController::setupCamera(Camera* cam) {
	// create a pivot at roughly the character's shoulder
	mCameraPivot = cam->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	
	// this is where the camera should be soon, and it spins around the pivot
	mCameraGoal = mCameraPivot->createChildSceneNode(Vector3(0, 75, 200));
	
	// this is where the camera actually is
	mCameraNode = cam->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	mCameraNode->setPosition(mCameraPivot->getPosition()); // + mCameraGoal->getPosition());

	mCameraPivot->setFixedYawAxis(true);
	mCameraGoal->setFixedYawAxis(true);
	mCameraNode->setFixedYawAxis(true);
	
	// our model is quite small, so reduce the clipping planes
	// cam->setNearClipDistance(0.1);
	// cam->setFarClipDistance(100);
	mCameraNode->attachObject(cam);

	mPivotPitch = 0;
}


void CharacterController::setupBody(SceneManager* sceneMgr) {
	// create main model
	mBodyNode = sceneMgr->getRootSceneNode()->createChildSceneNode(Vector3::UNIT_Y * CHAR_HEIGHT);
	mBodyEnt = sceneMgr->createEntity("SinbadBody", "Sinbad.mesh");
	mBodyEnt->getSkeleton()->setBlendMode(Ogre::ANIMBLEND_CUMULATIVE);
	mBodyNode->attachObject(mBodyEnt);
	mMove = true;

	// scale to fit
	mBodyNode->scale(CHAR_SCALE_X, CHAR_SCALE_Y, CHAR_SCALE_Z);

	mKeyDirection = Vector3::ZERO;
	mVerticalVelocity = 0;

	// Get the two halves of the idle animation
	Ogre::AnimationState* baseAnim = mBodyEnt->getAnimationState("IdleBase");
	Ogre::AnimationState* topAnim = mBodyEnt->getAnimationState("IdleTop");

	// Enable both of them and set them to loop.
	baseAnim->setLoop(true);
	topAnim->setLoop(true);
	baseAnim->setEnabled(true);
	topAnim->setEnabled(true);

	mBodyNode->setVisible(false, true);
}

void CharacterController::setupAnimations() {
	// this is very important due to the nature of the exported animations
	mBodyEnt->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

	String animNames[] =
	{"IdleBase", "IdleTop", "RunBase", "RunTop", "HandsClosed", "HandsRelaxed", "DrawSwords",
	"SliceVertical", "SliceHorizontal", "Dance", "JumpStart", "JumpLoop", "JumpEnd"};

	// populate our animation list
	for (int i = 0; i < NUM_ANIMS; i++)
	{
		mAnims[i] = mBodyEnt->getAnimationState(animNames[i]);
		mAnims[i]->setLoop(true);
		mFadingIn[i] = false;
		mFadingOut[i] = false;
	}

	// start off in the idle state (top and bottom together)
	setBaseAnimation(ANIM_IDLE_BASE);
	setTopAnimation(ANIM_IDLE_TOP);

	// relax the hands since we're not holding anything
	mAnims[ANIM_HANDS_RELAXED]->setEnabled(true);

	mSwordsDrawn = false;
}


void CharacterController::addTime(Real deltaTime)
{
	updateBody(deltaTime);
	updateAnimations(deltaTime);
	updateCamera(deltaTime);
}

void CharacterController::injectKeyDown(const OIS::KeyEvent& evt)
{
	if (evt.key == OIS::KC_Q && (mTopAnimID == ANIM_IDLE_TOP || mTopAnimID == ANIM_RUN_TOP))
	{
		// take swords out (or put them back, since it's the same animation but reversed)
		setTopAnimation(ANIM_DRAW_SWORDS, true);
		mTimer = 0;
	}

	// keep track of the player's intended direction
	else if (evt.key == OIS::KC_W) mKeyDirection.z = -1;
	else if (evt.key == OIS::KC_A) mKeyDirection.x = -1;
	else if (evt.key == OIS::KC_S) mKeyDirection.z = 1;
	else if (evt.key == OIS::KC_D) mKeyDirection.x = 1;

	else if (evt.key == OIS::KC_E && mCurUsableObject != NULL)
	{
		if (!mCurUsableObject->isUsing()) {
			mCurUsableObject->use();
		} else {
			mCurUsableObject->unuse();
		}
	}
	else if (evt.key == OIS::KC_SPACE && (mTopAnimID == ANIM_IDLE_TOP || mTopAnimID == ANIM_RUN_TOP))
	{
		// jump if on ground
		setBaseAnimation(ANIM_JUMP_START, true);
		setTopAnimation(ANIM_NONE);
		mTimer = 0;
	}

	if (!mKeyDirection.isZeroLength() && mBaseAnimID == ANIM_IDLE_BASE)
	{
		// start running if not already moving and the player wants to move
		setBaseAnimation(ANIM_RUN_BASE, true);
		if (mTopAnimID == ANIM_IDLE_TOP) setTopAnimation(ANIM_RUN_TOP, true);
	}
}

void CharacterController::injectKeyUp(const OIS::KeyEvent& evt)
{
	// keep track of the player's intended direction
	if (evt.key == OIS::KC_W && mKeyDirection.z == -1) mKeyDirection.z = 0;
	else if (evt.key == OIS::KC_A && mKeyDirection.x == -1) mKeyDirection.x = 0;
	else if (evt.key == OIS::KC_S && mKeyDirection.z == 1) mKeyDirection.z = 0;
	else if (evt.key == OIS::KC_D && mKeyDirection.x == 1) mKeyDirection.x = 0;

	if (mKeyDirection.isZeroLength() && mBaseAnimID == ANIM_RUN_BASE)
	{
		// stop running if already moving and the player doesn't want to move
		setBaseAnimation(ANIM_IDLE_BASE);
		if (mTopAnimID == ANIM_RUN_TOP) setTopAnimation(ANIM_IDLE_TOP);
	}
}

void CharacterController::injectMouseMove(const OIS::MouseEvent& evt)
{
	// update camera goal based on mouse movement
	updateCameraGoal(-0.05f * evt.state.X.rel, -0.05f * evt.state.Y.rel, -0.0005f * evt.state.Z.rel);
}

void CharacterController::injectMouseDown(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
	if (mSwordsDrawn && (mTopAnimID == ANIM_IDLE_TOP || mTopAnimID == ANIM_RUN_TOP))
	{
		// if swords are out, and character's not doing something weird, then SLICE!
		if (id == OIS::MB_Left) setTopAnimation(ANIM_SLICE_VERTICAL, true);
		else if (id == OIS::MB_Right) setTopAnimation(ANIM_SLICE_HORIZONTAL, true);
		mTimer = 0;
	}
}


void CharacterController::updateBody(Real deltaTime)
{
	mGoalDirection = Vector3::ZERO;   // we will calculate this

	if (mKeyDirection != Vector3::ZERO && mBaseAnimID != ANIM_DANCE)
	{
		if (mMove) {
		// calculate actually goal direction in world based on player's key directions
		mGoalDirection += mKeyDirection.z * mCameraNode->getOrientation().zAxis();
		mGoalDirection += mKeyDirection.x * mCameraNode->getOrientation().xAxis();
		} else {
			mGoalDirection -= mKeyDirection.z;// * mCameraNode->getOrientation().zAxis();
			mGoalDirection -= mKeyDirection.x;// * mCameraNode->getOrientation().xAxis();
		}
		mGoalDirection.y = 0;
		mGoalDirection.normalise();

		Quaternion toGoal = mBodyNode->getOrientation().zAxis().getRotationTo(mGoalDirection);

		// calculate how much the character has to turn to face goal direction
		Real yawToGoal = toGoal.getYaw().valueDegrees();
		// this is how much the character CAN turn this frame
		Real yawAtSpeed = yawToGoal / Math::Abs(yawToGoal) * deltaTime * TURN_SPEED;
		// reduce "turnability" if we're in midair
		if (mBaseAnimID == ANIM_JUMP_LOOP) yawAtSpeed *= 0.2f;

		// turn as much as we can, but not more than we need to
		if (yawToGoal < 0) yawToGoal = std::min<Real>(0, std::max<Real>(yawToGoal, yawAtSpeed)); //yawToGoal = Math::Clamp<Real>(yawToGoal, yawAtSpeed, 0);
		else if (yawToGoal > 0) yawToGoal = std::max<Real>(0, std::min<Real>(yawToGoal, yawAtSpeed)); //yawToGoal = Math::Clamp<Real>(yawToGoal, 0, yawAtSpeed);

		mBodyNode->yaw(Degree(yawToGoal));

		// move in current body direction (not the goal direction)
		mBodyNode->translate(0, 0, deltaTime * RUN_SPEED * mAnims[mBaseAnimID]->getWeight(),
			Node::TS_LOCAL);

	}

	if (mBaseAnimID == ANIM_JUMP_LOOP)
	{
		// if we're jumping, add a vertical offset too, and apply gravity
		mBodyNode->translate(0, mVerticalVelocity * deltaTime, 0, Node::TS_LOCAL);
		mVerticalVelocity -= GRAVITY * deltaTime;

		Vector3 pos = mBodyNode->getPosition();
		if (pos.y <= CHAR_HEIGHT)
		{
			// if we've hit the ground, change to landing state
			pos.y = CHAR_HEIGHT;
			mBodyNode->setPosition(pos);
			setBaseAnimation(ANIM_JUMP_END, true);
			mTimer = 0;
		}
	}
}

void CharacterController::updateAnimations(Real deltaTime)
{
	Real baseAnimSpeed = 1;
	Real topAnimSpeed = 1;

	mTimer += deltaTime;

	if (mTopAnimID == ANIM_DRAW_SWORDS)
	{
		// flip the draw swords animation if we need to put it back
		topAnimSpeed = mSwordsDrawn ? -1 : 1;

		// half-way through the animation is when the hand grasps the handles...
		if (mTimer >= mAnims[mTopAnimID]->getLength() / 2 &&
			mTimer - deltaTime < mAnims[mTopAnimID]->getLength() / 2)
		{
			// so transfer the swords from the sheaths to the hands
			mBodyEnt->detachAllObjectsFromBone();
			// change the hand state to grab or let go
			mAnims[ANIM_HANDS_CLOSED]->setEnabled(!mSwordsDrawn);
			mAnims[ANIM_HANDS_RELAXED]->setEnabled(mSwordsDrawn);
		}

		if (mTimer >= mAnims[mTopAnimID]->getLength())
		{
			// animation is finished, so return to what we were doing before
			if (mBaseAnimID == ANIM_IDLE_BASE) setTopAnimation(ANIM_IDLE_TOP);
			else
			{
				setTopAnimation(ANIM_RUN_TOP);
				mAnims[ANIM_RUN_TOP]->setTimePosition(mAnims[ANIM_RUN_BASE]->getTimePosition());
			}
			mSwordsDrawn = !mSwordsDrawn;
		}
	}
	else if (mTopAnimID == ANIM_SLICE_VERTICAL || mTopAnimID == ANIM_SLICE_HORIZONTAL)
	{
		if (mTimer >= mAnims[mTopAnimID]->getLength())
		{
			// animation is finished, so return to what we were doing before
			if (mBaseAnimID == ANIM_IDLE_BASE) setTopAnimation(ANIM_IDLE_TOP);
			else
			{
				setTopAnimation(ANIM_RUN_TOP);
				mAnims[ANIM_RUN_TOP]->setTimePosition(mAnims[ANIM_RUN_BASE]->getTimePosition());
			}
		}

		// don't sway hips from side to side when slicing. that's just embarrasing.
		if (mBaseAnimID == ANIM_IDLE_BASE) baseAnimSpeed = 0;
	}
	else if (mBaseAnimID == ANIM_JUMP_START)
	{
		if (mTimer >= mAnims[mBaseAnimID]->getLength())
		{
			// takeoff animation finished, so time to leave the ground!
			setBaseAnimation(ANIM_JUMP_LOOP, true);
			// apply a jump acceleration to the character
			mVerticalVelocity = JUMP_ACCEL;
		}
	}
	else if (mBaseAnimID == ANIM_JUMP_END)
	{
		if (mTimer >= mAnims[mBaseAnimID]->getLength())
		{
			// safely landed, so go back to running or idling
			if (mKeyDirection == Vector3::ZERO)
			{
				setBaseAnimation(ANIM_IDLE_BASE);
				setTopAnimation(ANIM_IDLE_TOP);
			}
			else
			{
				setBaseAnimation(ANIM_RUN_BASE, true);
				setTopAnimation(ANIM_RUN_TOP, true);
			}
		}
	}

	// increment the current base and top animation times
	if (mBaseAnimID != ANIM_NONE) mAnims[mBaseAnimID]->addTime(deltaTime * baseAnimSpeed);
	if (mTopAnimID != ANIM_NONE) mAnims[mTopAnimID]->addTime(deltaTime * topAnimSpeed);

	// apply smooth transitioning between our animations
	fadeAnimations(deltaTime);
}

void CharacterController::fadeAnimations(Real deltaTime)
{
	for (int i = 0; i < NUM_ANIMS; i++)
	{
		if (mFadingIn[i])
		{
			// slowly fade this animation in until it has full weight
			Real newWeight = mAnims[i]->getWeight() + deltaTime * ANIM_FADE_SPEED;
			mAnims[i]->setWeight(Math::Clamp<Real>(newWeight, 0, 1));
			if (newWeight >= 1) mFadingIn[i] = false;
		}
		else if (mFadingOut[i])
		{
			// slowly fade this animation out until it has no weight, and then disable it
			Real newWeight = mAnims[i]->getWeight() - deltaTime * ANIM_FADE_SPEED;
			mAnims[i]->setWeight(Math::Clamp<Real>(newWeight, 0, 1));
			if (newWeight <= 0)
			{
				mAnims[i]->setEnabled(false);
				mFadingOut[i] = false;
			}
		}
	}
}

void CharacterController::updateCamera(Real deltaTime)
{
	// place the camera pivot roughly at the character's shoulder
	mCameraPivot->setPosition(mBodyNode->getPosition() + Vector3::UNIT_X * 20);
	// move the camera smoothly to the goal
	Vector3 goalOffset = mCameraGoal->_getDerivedPosition() - mCameraNode->getPosition();
	mCameraNode->translate(goalOffset * deltaTime * 9.0f);
	// always look at the pivot
	mCameraNode->lookAt(mCameraPivot->_getDerivedPosition(), Node::TS_WORLD);
}

void CharacterController::updateCameraGoal(Real deltaYaw, Real deltaPitch, Real deltaZoom)
{
	mCameraPivot->yaw(Degree(deltaYaw), Node::TS_WORLD);

	// bound the pitch
	if (!(mPivotPitch + deltaPitch > 25 && deltaPitch > 0) &&
		!(mPivotPitch + deltaPitch < -60 && deltaPitch < 0))
	{
		mCameraPivot->pitch(Degree(deltaPitch), Node::TS_LOCAL);
		mPivotPitch += deltaPitch;
	}

	Real dist = mCameraGoal->_getDerivedPosition().distance(mCameraPivot->_getDerivedPosition());
	Real distChange = deltaZoom * dist;

	// bound the zoom
	if (!(dist + distChange < 8 && distChange < 0) &&
		!(dist + distChange > 25 && distChange > 0))
	{
		mCameraGoal->translate(0, 0, distChange, Node::TS_LOCAL);
	}
}

void CharacterController::setBaseAnimation(AnimID id, bool reset)
{
	if (mBaseAnimID >= 0 && mBaseAnimID < NUM_ANIMS)
	{
		// if we have an old animation, fade it out
		mFadingIn[mBaseAnimID] = false;
		mFadingOut[mBaseAnimID] = true;
	}

	mBaseAnimID = id;

	if (id != ANIM_NONE)
	{
		// if we have a new animation, enable it and fade it in
		mAnims[id]->setEnabled(true);
		mAnims[id]->setWeight(0);
		mFadingOut[id] = false;
		mFadingIn[id] = true;
		if (reset) mAnims[id]->setTimePosition(0);
	}
}

void CharacterController::setTopAnimation(AnimID id, bool reset)
{
	if (mTopAnimID >= 0 && mTopAnimID < NUM_ANIMS)
	{
		// if we have an old animation, fade it out
		mFadingIn[mTopAnimID] = false;
		mFadingOut[mTopAnimID] = true;
	}

	mTopAnimID = id;

	if (id != ANIM_NONE)
	{
		// if we have a new animation, enable it and fade it in
		mAnims[id]->setEnabled(true);
		mAnims[id]->setWeight(0);
		mFadingOut[id] = false;
		mFadingIn[id] = true;
		if (reset) mAnims[id]->setTimePosition(0);
	}
}

const Vector3 & CharacterController::getPosition(void)
{
	return mBodyNode->getPosition();
}

const Vector3 & CharacterController::getDirection()
{
	return mBodyNode->getAutoTrackLocalDirection();
}

const AxisAlignedBox& CharacterController::getBoundingBox()
{
	return mBodyEnt->getWorldBoundingBox();
}

void CharacterController::setMove(bool move) {
	mMove = move;
}

void CharacterController::setUsableObject(UsableObject* object) {
	mCurUsableObject = object;
}


