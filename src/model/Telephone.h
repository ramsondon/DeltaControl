/*
 * Telephone.h
 *
 *  Created on: Feb 6, 2012
 *      Author: matthias schmid
 */

#ifndef TELEPHONE_H_
#define TELEPHONE_H_

#include <SdkTrays.h>
#include "GamePanel.h"
#include "UsableObject.h"

class SceneManager;
class CharacterController;

class Telephone: public UsableObject, public GamePanel, public OgreBites::SdkTrayListener {

private:
	void setup();
	void buttonHit(OgreBites::Button* button);

public:
	Telephone(Ogre::SceneManager* sceneMgr, CharacterController* cc);
	virtual ~Telephone();

	void highlight(bool highlight);
	virtual void use();
	virtual void unuse();

	// inherited abstract methods
	void createAndShow();
};

#endif /* TELEPHONE_H_ */
