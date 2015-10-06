#include "onedaystockmangemant.h"
#include "ui_onedaystockmangemant.h"

OnedayStockMangemant::OnedayStockMangemant(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::OnedayStockMangemant)
{
    ui->setupUi(this);
    stockEngine = new XlEngine();
    /* using for test,later get it from the signals */
    stockEngine->setStockID("601006");
    stockEngine->setStockName("大秦铁路");

    ui->customPlot->axisRect()->setupFullAxesBox(true);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->customPlot->xAxis->setAutoTickStep(true);
    ui->customPlot->xAxis->setTickStep(3600); // 1h tickstep
    ui->customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->customPlot->xAxis->setDateTimeSpec(Qt::UTC);
    ui->customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->customPlot->xAxis->setAutoTickCount(4);
    this->dataTimer = new QTimer();
    this->dataTimer->start(1000*20);
    connect(dataTimer, SIGNAL(timeout()), this, SLOT(updateCurrentStockData()));
    setupCurrentStockData();
}

void OnedayStockMangemant::setupStockDate()
{


    stockEngine->run();
    ui->stockName->setText(stockEngine->getStockName());
    this->m_todayStockData = stockEngine->getTodaystockData();
    cout<<m_todayStockData->size()<<endl;
    if(this->m_todayStockData == NULL)
    {
        //here should add exception
        return;
    }
}

void OnedayStockMangemant::setupLengend()
{
    int ttnum = m_todayStockData->size();
    double min=1000,max=-1000;
    QVector<double> x(ttnum), y(ttnum);
    for (int i=0; i<ttnum; ++i)
    {
      QDateTime m_time = QDateTime(stockEngine->getDate(),m_todayStockData->at(i).dealTime,Qt::UTC);
      x[i] = m_time.toTime_t();
      y[i] = m_todayStockData->at(i).dealPrice;  // let's plot a quadratic function
      if(y[i]<min) min = y[i];
      if(y[i]>max) max =y[i];
    }

    ui->HighestPrice->setText(QString::number(max));
    ui->LowestPrice->setText(QString::number(min));
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    ui->customPlot->graph(0)->setAdaptiveSampling(true);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("time");
    ui->customPlot->yAxis->setLabel("price");
    ui->customPlot->xAxis->setRange(x[0], x[ttnum-1]);
    ui->customPlot->yAxis->setRange(min-0.1, max+0.2);
}

void OnedayStockMangemant::updateCurrentStockData()
{
    QDateTime dt = QDateTime::currentDateTime();
    if(dt.date().dayOfWeek()>5 || (dt.time()<QTime::fromString("09:00:00",Qt::ISODate)
                                   ||dt.time()>QTime::fromString("15:05:00",Qt::ISODate)))
        return;
    setupCurrentStockData();
}

void OnedayStockMangemant::setupCurrentStockData()
{
   stockEngine->getCurrentStockDataFromNetwork();
   m_current_stockData = stockEngine->getCurrentStockData();
   if(m_current_stockData->size() != 0)
   {
       cout<<"test"<<endl;
       CurrentStock temp = m_current_stockData->first();
       ui->buy1Num->setText(QString::number(temp.buyNum[0]));
       ui->buy1Price->setText(QString::number(temp.buyPrice[0]));

       ui->buy2Num->setText(QString::number(temp.buyNum[1]));
       ui->buy2Price->setText(QString::number(temp.buyPrice[1]));

       ui->buy3Num->setText(QString::number(temp.buyNum[2]));
       ui->buy3Price->setText(QString::number(temp.buyPrice[2]));

       ui->buy4Num->setText(QString::number(temp.buyNum[3]));
       ui->buy4Price->setText(QString::number(temp.buyPrice[3]));

       ui->buy5Num->setText(QString::number(temp.buyNum[4]));
       ui->buy5Price->setText(QString::number(temp.buyPrice[4]));

       ui->sell1Num->setText(QString::number(temp.sellNum[0]));
       ui->sell1Price->setText(QString::number(temp.sellPrice[0]));

       ui->sell2Num->setText(QString::number(temp.sellNum[1]));
       ui->sell2Price->setText(QString::number(temp.sellPrice[1]));

       ui->sell3Num->setText(QString::number(temp.sellNum[2]));
       ui->sell3Price->setText(QString::number(temp.sellPrice[2]));

       ui->sell4Num->setText(QString::number(temp.sellNum[3]));
       ui->sell4Price->setText(QString::number(temp.sellPrice[3]));

       ui->sell5Num->setText(QString::number(temp.sellNum[4]));
       ui->sell5Price->setText(QString::number(temp.sellPrice[4]));



   }
}


OnedayStockMangemant::~OnedayStockMangemant()
{
    delete ui;
}


