/*
 * Observer.h
 *
 *  Created on: Feb 23, 2012
 *      Author: matthias
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

class Observer {
public:
	Observer();
	virtual ~Observer();
	virtual void notify() = 0;
};

#endif /* OBSERVER_H_ */
