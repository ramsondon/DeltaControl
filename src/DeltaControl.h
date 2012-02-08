/*
-----------------------------------------------------------------------------
Filename:    DeltaControl.h
-----------------------------------------------------------------------------
*/
#ifndef __DeltaControl_h_
#define __DeltaControl_h_

#include "BaseApplication.h"

#define FLOOR_WIDTH 10750
#define FLOOR_LENGTH 20490

class DeltaControl : public BaseApplication
{
public:
    DeltaControl(void);
    virtual ~DeltaControl(void);

protected:
    virtual void createScene(void);
};

#endif // #ifndef __DeltaControl_h_
