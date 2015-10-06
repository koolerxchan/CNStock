#ifndef XLENGINE_H
#define XLENGINE_H
#include "networkkernel.h"
#include<QRegularExpression>
#include <QQueue>
#include <QStack>
#include <QTime>
#include<QDate>
#include <QFile>
#ifdef WIN32
    #include "networkkernel_win.h"
#else
    #include "networkkernerl_linux.h"
#endif
static QString HistoryDetaillData = "vip.stock.finance.sina.com.cn/quotes_service/view/vMS_tradehistory.php?";

//xinlang data
class XlEngine
{
public:
    XlEngine();
private:
    NetworkKernel *networkkeinel;
    void handleResult(QString result);
    void getTodayData();
    bool getHtmlTableDate(QString data);
    QQueue<CurrentStock> stockData;
    QStack<OnedayHistoryStockData> todayStockData;
    QString stockName;
    QString stockID;
    QString hostURL;
    QString todayHistoryStockUrl;
    QString currentStockUrl;
    QDate m_date;
public:
    void generateURL(QString Id);
    void generateURL(QString Id,int page);
    void run();
    void getCurrentStockDataFromNetwork();
     QQueue<CurrentStock> *getCurrentStockData();
    QStack<OnedayHistoryStockData> *getTodaystockData();
    inline QString getStockName()
    {
        return stockName;
    }

    inline void setStockName(QString name)
    {
        this->stockName = name;
    }

    inline QDate getDate()
    {
        return m_date;
    }
    inline void setStockID(QString stockID)
    {
        this->stockID = stockID;
    }


};

#endif // XLENGINE_H
