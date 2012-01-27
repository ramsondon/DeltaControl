/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __DeltaControl_h_
#define __DeltaControl_h_

#include "BaseApplication.h"

class DeltaControl : public BaseApplication
{
public:
    DeltaControl(void);
    virtual ~DeltaControl(void);

protected:
    virtual void createScene(void);
};

#endif // #ifndef __DeltaControl_h_
