/*
-----------------------------------------------------------------------------
Filename:    DeltaControl.h
-----------------------------------------------------------------------------
*/
#ifndef __DeltaControl_h_
#define __DeltaControl_h_

#include "BaseApplication.h"
#include "model/ControlCenter.h"

#define ROOM_WIDTH 	600
#define ROOM_LENGTH	800
#define ROOM_HEIGHT	200

class DeltaControl : public BaseApplication
{
private:
	ControlCenter* mControlCenter;

public:
    DeltaControl(void);
    virtual ~DeltaControl(void);

protected:
    virtual void createScene(void);
};

#endif // #ifndef __DeltaControl_h_
