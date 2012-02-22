/*
 * Telephone.h
 *
 *  Created on: Feb 6, 2012
 *      Author: matthias schmid
 */

#ifndef TELEPHONE_H_
#define TELEPHONE_H_

#include "UsableObject.h"

class SceneManager;
class CharacterController;

class Telephone : public UsableObject {

private:
	void setup();

public:
	Telephone(Ogre::SceneManager* sceneMgr, CharacterController* cc);
	virtual ~Telephone();

	void highlight(bool highlight);

};

#endif /* TELEPHONE_H_ */
