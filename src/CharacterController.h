/*
 * CharacterController.h
 *
 *  Created on: 08.02.2012
 *      Author: Florian
 */

#ifndef CHARACTERCONTROLLER_H_
#define CHARACTERCONTROLLER_H_

#include <Ogre.h>
#include <OgreCamera.h>
#include <OIS.h>

#define NUM_ANIMS 13           // number of animations the character has
#define CHAR_HEIGHT 50          // height of character's center of mass above ground
#define CAM_HEIGHT 20           // height of camera above character's center of mass
#define RUN_SPEED 150          // character running speed in units per second
#define TURN_SPEED 700.0f      // character turning in degrees per second
#define ANIM_FADE_SPEED 7.5f   // animation crossfade speed in % of full weight per second
#define JUMP_ACCEL 30.0f       // character jump acceleration in upward units per squared second
#define GRAVITY 90.0f          // gravity in downward units per squared second
#define CHAR_SCALE_X 10
#define CHAR_SCALE_Y CHAR_SCALE_X
#define CHAR_SCALE_Z CHAR_SCALE_X

using namespace Ogre;

class CharacterController {
private:
	// all the animations our character has, and a null ID
	// some of these affect separate body parts and will be blended together
	enum AnimID
	{
		ANIM_IDLE_BASE,
		ANIM_IDLE_TOP,
		ANIM_RUN_BASE,
		ANIM_RUN_TOP,
		ANIM_HANDS_CLOSED,
		ANIM_HANDS_RELAXED,
		ANIM_DRAW_SWORDS,
		ANIM_SLICE_VERTICAL,
		ANIM_SLICE_HORIZONTAL,
		ANIM_DANCE,
		ANIM_JUMP_START,
		ANIM_JUMP_LOOP,
		ANIM_JUMP_END,
		ANIM_NONE
	};

	Camera* mCamera;
	SceneNode* mBodyNode;
	SceneNode* mCameraPivot;
	SceneNode* mCameraGoal;
	SceneNode* mCameraNode;
	Real mPivotPitch;
	Entity* mBodyEnt;
	Entity* mSword1;
	Entity* mSword2;
	RibbonTrail* mSwordTrail;
	AnimationState* mAnims[NUM_ANIMS];    // master animation list
	AnimID mBaseAnimID;                   // current base (full- or lower-body) animation
	AnimID mTopAnimID;                    // current top (upper-body) animation
	bool mFadingIn[NUM_ANIMS];            // which animations are fading in
	bool mFadingOut[NUM_ANIMS];           // which animations are fading out
	bool mSwordsDrawn;
	Vector3 mKeyDirection;      // player's local intended direction based on WASD keys
	Vector3 mGoalDirection;     // actual intended direction in world-space
	Real mVerticalVelocity;     // for jumping
	Real mTimer;                // general timer to see how long animations have been playing

public:
	CharacterController(Camera* cam);
	virtual ~CharacterController();

	void addTime(Real deltaTime);
	void injectMouseDown(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
	void injectMouseMove(const OIS::MouseEvent& evt);
	void injectKeyUp(const OIS::KeyEvent& evt);
	void injectKeyDown(const OIS::KeyEvent& evt);

private:
	void setupAnimations();
	void setupBody(SceneManager* sceneMgr);
	void setupCamera(Camera* cam);
	void setTopAnimation(AnimID id, bool reset = false);
	void setBaseAnimation(AnimID id, bool reset = false);
	void updateCameraGoal(Real deltaYaw, Real deltaPitch, Real deltaZoom);
	void updateCamera(Real deltaTime);
	void fadeAnimations(Real deltaTime);
	void updateAnimations(Real deltaTime);
	void updateBody(Real deltaTime);
};

#endif /* CHARACTERCONTROLLER_H_ */
