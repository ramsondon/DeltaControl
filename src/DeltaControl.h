/*
-----------------------------------------------------------------------------
Filename:    DeltaControl.h
-----------------------------------------------------------------------------
*/
#ifndef __DeltaControl_h_
#define __DeltaControl_h_

#include "BaseApplication.h"
#include "model/ControlCenter.h"
#include "model/Telephone.h"
#include "model/Table.h"
#include "model/Monitor.h"

#define ROOM_WIDTH 	600
#define ROOM_LENGTH	800
#define ROOM_HEIGHT	200

class DeltaControl : public BaseApplication
{
private:
	ControlCenter* mControlCenter;
	Telephone* mPhone;
	Table* mTable;
	Monitor* mMonitor;

public:
    DeltaControl(void);
    virtual ~DeltaControl(void);

protected:
    virtual void createScene(void);
    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

};

#endif // #ifndef __DeltaControl_h_
