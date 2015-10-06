#ifndef ONEDAYFRAMEMANAGE_H
#define ONEDAYFRAMEMANAGE_H
#include "qcustomplot.h"
#include "xlengine.h"

class OneDayFrameManage
{
public:
    OneDayFrameManage();
private:
    QCustomPlot *customPlot;
    XlEngine *stockEngine;
public:
    inline void setCustomPlot(QCustomPlot *plot)
    {
        this->customPlot = plot;
    }

};

#endif // ONEDAYFRAMEMANAGE_H
