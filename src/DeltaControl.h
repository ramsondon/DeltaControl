/*
-----------------------------------------------------------------------------
Filename:    DeltaControl.h
-----------------------------------------------------------------------------
*/
#ifndef __DeltaControl_h_
#define __DeltaControl_h_

#include "BaseApplication.h"

#define ROOM_WIDTH 	600
#define ROOM_LENGTH	800
#define ROOM_HEIGHT	200

class DeltaControl : public BaseApplication
{
public:
    DeltaControl(void);
    virtual ~DeltaControl(void);

protected:
    virtual void createScene(void);
};

#endif // #ifndef __DeltaControl_h_
