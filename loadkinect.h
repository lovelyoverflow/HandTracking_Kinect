#ifndef LOADKINECT_H
#define LOADKINECT_H

#include <QThread>
#include <qtmaterialcircularprogress.h>

class LoadKinect : public QThread
{
public:
    LoadKinect(bool& load);

    void run();

private:
    QtMaterialCircularProgress *circleProgress;
    bool& isLoaded;
};

#endif // LOADKINECT_H
