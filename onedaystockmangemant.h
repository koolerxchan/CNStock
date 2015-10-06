#ifndef ONEDAYSTOCKMANGEMANT_H
#define ONEDAYSTOCKMANGEMANT_H

#include <QFrame>
#include <qcustomplot.h>
#include "xlengine.h"

namespace Ui {
class OnedayStockMangemant;
}

class OnedayStockMangemant : public QFrame
{
    Q_OBJECT

public:
    explicit OnedayStockMangemant(QWidget *parent = 0);
    ~OnedayStockMangemant();

    /* there shoud be a base manager class to inherit from.
     * actually the purpose of the base class is to better contorl
     * all the frame-manager-type class.* to do it later*/
    /*virtual */void activeFrame(bool on);

    /* set up the all today data, form the 9:00 to now time
     * as result ,we get the point to
     * the QStack<OnedayHistoryStockData>from engine*/
    void setupStockDate();

    //dram a lengend form the data
    void setupLengend();

    void setupCurrentStockData();

private slots:
    void updateCurrentStockData();

private:
    double m_current_highestPrice;
    double m_current_lowestPrice;
    /* the newest data get from the engine,
     * it describes the current time how the stock data is.
     * all the data should merged into the m_todayStockData,to plot
     * or do some prediction.*/
    QQueue<CurrentStock> *m_current_stockData;
    QStack<OnedayHistoryStockData> *m_todayStockData;
    Ui::OnedayStockMangemant *ui;
    XlEngine *stockEngine;

    QTimer *dataTimer;
};

#endif // ONEDAYSTOCKMANGEMANT_H
