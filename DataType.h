#ifndef DATATYPE_H
#define DATATYPE_H
#include<QString>
#include <sstream>
#include<iostream>
#include<vector>
#include <QTime>
#include <QDate>
using namespace std;

#define ERROR_PARAM -201
#define NONETWORKCONNNECT -202

string g_str(double number);
string g_str(int number);
string g_str(QString s);

#define VAR2STR(x) string(#x)+":"+g_str(x) + "\n"

struct OnedayHistoryStockData{
    QString stockID;

    QString stockName;
    QTime dealTime;
    double dealPrice;
    double percents;
    double priceChange;
    double tradeNum;
    double turnOver;
    int    dealType;
    OnedayHistoryStockData():
        dealPrice(0),
        percents(0),
        priceChange(0),
        tradeNum(0),
        turnOver(0){}
    void infoPrintf()
    {
        string info  = VAR2STR(stockID) ;
        info  += VAR2STR(stockName) ;
        info  += VAR2STR(dealPrice) ;
        info  += VAR2STR(percents);
        info  += VAR2STR(priceChange) ;
        info  += VAR2STR(tradeNum);
        info  += VAR2STR(turnOver);
        info  += dealTime.toString(Qt::ISODate).toStdString();
        cout<<info<<endl;
    }
    OnedayHistoryStockData(QString ID) :
        stockID(ID),
        dealPrice(0),
        percents(0),
        priceChange(0),
        tradeNum(0),
        turnOver(0){}
};


struct CurrentStock{
    QString stockID;
    QString stockName;
    double todayOpenPrice;
    double yesterdayClosePrice;
    double currentPrice;
    double todayHighest;
    double todayLowest;
    double bidPrice;//竞买价
    double auctionPrice;//竞卖价
    double tradeNumber;//成交的股票数
    double turnOver;//成交金额
    vector<int> buyNum;
    vector<double> buyPrice;
    vector<int> sellNum;
    vector<double> sellPrice;
    QDate data;
    QTime time;
    void infoPrintf()
    {
        string info  = VAR2STR(stockID) ;
        info  += VAR2STR(stockName) ;
        info  += VAR2STR(todayOpenPrice) ;
        info  += VAR2STR(yesterdayClosePrice) ;
        info  += VAR2STR(currentPrice) ;
        info  += VAR2STR(todayHighest) ;
        info  += VAR2STR(todayLowest) ;
        info  += VAR2STR(bidPrice);
        info  += VAR2STR(auctionPrice) ;
        info  += VAR2STR(tradeNumber);
        info  += VAR2STR(turnOver);
        info  += data.toString(Qt::ISODate).toStdString();
        info  += time.toString(Qt::ISODate).toStdString();
        cout<<info<<endl;
    }

    CurrentStock(QString ID) :
        stockID(ID),
        todayOpenPrice(0),
        yesterdayClosePrice(0),
        currentPrice(0),
        todayHighest(0),
        todayLowest(0),
        bidPrice(0),
        auctionPrice(0),
        tradeNumber(0),
        turnOver(0){}
};



#endif // DATATYPE_H
