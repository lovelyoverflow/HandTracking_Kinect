#include "loadkinect.h"
#include "KinectController.h"

LoadKinect::LoadKinect(bool& load)
    : circleProgress(new QtMaterialCircularProgress),
      isLoaded(load)
{
   // circleProgress->setFixedSize(1280, 720);

   // circleProgress->show();
    // KinectController().init();
}

void LoadKinect::run()
{
   // KinectController().init();

    //if(KinectController::loaded == true)
        //circleProgress->close();
}
