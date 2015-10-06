#include "xlengine.h"
//http://market.finance.sina.com.cn/downxls.php?date=2015-08-17&symbol=sh601006
XlEngine::XlEngine()
{
#ifdef WIN32
    networkkeinel = new NetworkKernel_Win();
#else
    networkkeinel = new NetworkKernerl_Linux();
#endif

    todayHistoryStockUrl = QString("vip.stock.finance.sina.com.cn/quotes_service/view/vMS_tradedetail.php?");
    currentStockUrl = QString("hq.sinajs.cn/list=sh");
    m_date =QDate::currentDate();

}

QQueue<CurrentStock> *XlEngine::getCurrentStockData()
{
    return &stockData;
}

QStack<OnedayHistoryStockData> *XlEngine::getTodaystockData()
{
    return &todayStockData;
}


//call before run();
void XlEngine::generateURL(QString Id)
{
    this->stockID = Id;
    this->hostURL = this->currentStockUrl + Id;
}
void XlEngine::generateURL(QString Id,int page)
{
//    symbol=sh601006&date=2015-08-21&page=39";


    if(m_date.dayOfWeek()>5)
    {
        m_date.setDate(m_date.year(),m_date.month(),
                            m_date.day()-(m_date.dayOfWeek()-5));
        this->hostURL = HistoryDetaillData;
    }
    else
        this->hostURL =this->todayHistoryStockUrl;
    this->hostURL +="symbol=sh" + this->stockID;
    this->hostURL += "&data="+m_date.toString(Qt::ISODate);
    this->hostURL += "&page=" + QString::number(page);
}

void XlEngine::getTodayData()
{
    int page =1;
    bool ret = true;
    while(ret)
    {
//        this->generateURL(this->stockID,page);
//        if(networkkeinel->httpConnection(this->hostURL)!=0)
//        {
//            break;
//        }

        QString temp = "./page" + QString::number(page);
        QString result;
        QFile file(temp);
        if(!file.open(QIODevice::ReadWrite|QIODevice::Text))
        {
            cout<<"fatal error!"<<endl;
            break;
        }
//        QTextStream output(&file);
//        output<<networkkeinel->getResult()<<endl;
//        file.close();

        while(!file.atEnd())
        {
            result+= file.readLine();
        }
        file.close();
        ret = this->getHtmlTableDate(result);
        //cout<<"Page="<<page<<"  ret:"<<ret<<endl;
        page++;
//        if(page ==41)
//            break;
    }
//    ofstream log;
//    QString temp = "page" + QString::number(page);
//    const char* name = temp.toStdString().c_str();
//    //cout<<name<<endl;
//    log.open(name);
//    log<<networkkeinel->getResult().toStdString();
//    log.close();
//    ifstream log;
//    log.open("todayData");
//    QString result;
//    string s;
//    while(!log.eof())
//    {
//        string temp;
//        log>>temp;
//        s +=temp;
//    }



}

bool XlEngine::getHtmlTableDate(QString data)
{
    QRegularExpression rx;
    QRegularExpressionMatch match;
    QString temp;
    QStringList dataList = data.split("</table>");
    for(int i =0;i<dataList.size();i++)
    {
        rx.setPattern("class=\"datatbl\"");
        if(rx.match(dataList[i]).hasMatch())
        {
            temp = dataList[i];
//            if(data.contains(temp))
//                cout<<"right"<<endl;
            break;
        }
    }
    temp = temp.split("</thead>")[1];

    if(temp.size()<150)
        return false;
//    <tr class="medium">
//        <th>15:00:03</th>
//        <td>10.21</td>
//        <td>-7.35%</td>
//        <td>--</td>
//        <td>210</td>
//        <td>215,390</td>
//        <th>
//            <h6>卖盘</h6>
//        </th>
//    </tr>
    QStringList resultList = temp.split("</tr>");
    //here tha last is empty,i don't known why,but it is
    for(int i =0;i<resultList.size()-1;i++)
    {
        OnedayHistoryStockData stockTemp(stockID);
        stockTemp.stockName = this->stockName;

        rx.setPattern("(?<time>\\d{2}:\\d{2}:\\d{2})");

        QString time= rx.match(resultList[i]).captured("time");
        rx.setPattern("(?<h>\\d{1,2}):(?<m>\\d{1,2}):(?<s>\\d{1,2})");
        match =  rx.match(time);
        stockTemp.dealTime = QTime(match.captured("h").toInt(),match.captured("m").toInt()
                           ,match.captured("s").toInt());
//        cout<<stockTemp.dealTime.toStdString()<<endl;

        rx.setPattern(">(?<dealprice>\\d{1,2}.\\d{2})<");
        //cout<<"hasmatch:"<<rx.match(resultList[i]).hasMatch()<<endl;
        stockTemp.dealPrice = rx.match(resultList[i]).captured("dealprice").toDouble();
       // cout<<stockTemp.dealPrice<<endl;

        rx.setPattern("(?<percent>[+-]\\d{1,2}\\.\\d{2})%");
        stockTemp.percents = rx.match(resultList[i]).captured("percent").toDouble();

        rx.setPattern("<td>(?<priceChange>[+-]\\d{1,2}\\.\\d{1,2})</td");
        match = rx.match(resultList[i]);
        if(match.hasMatch())
            stockTemp.priceChange = match.captured("priceChange").toDouble();

        rx.setPattern("<td>(?<tradeNum>\\d{1,})</td>");
        stockTemp.tradeNum = rx.match(resultList[i]).captured("tradeNum").toDouble();

        rx.setPattern("<td>(?<turnOver>[(\\d)(,)]{1,})</td><th");
        temp = rx.match(resultList[i]).captured("turnOver");
        QStringList tempList = temp.split(",");
        QString turnOver;
        for(int j =0;j<tempList.size();j++)
            turnOver += tempList[j];
        stockTemp.turnOver = turnOver.toDouble();

        rx.setPattern("<h\\d>(?<dealType>.*?)</h\\d>");
        temp = rx.match(resultList[i]).captured("dealType");
        if(temp == "买盘")
            stockTemp.dealType =1;
        else if(temp == "卖盘")
            stockTemp.dealType =-1;
        else
            stockTemp.dealType = 0;
        //cout<<i<<"  "<<rx.match(resultList[i]).captured("dealType").toStdString()<<endl;
//        stockTemp.infoPrintf();
       this->todayStockData.push(stockTemp);
    }
    return true;

}

void XlEngine::run()
{
//    networkkeinel->httpConnection(this->hostURL);
//    this->handleResult(networkkeinel->getResult());
    getTodayData();

}
void XlEngine::getCurrentStockDataFromNetwork()
{
    this->generateURL(this->stockID);
    //cout<<this->hostURL.toStdString()<<endl;
    networkkeinel->httpConnection(this->hostURL);
    //cout<<networkkeinel->getResult().toStdString()<<endl;
    this->handleResult(networkkeinel->getResult());

}

void XlEngine::handleResult(QString result)
{
    if(result.isEmpty())
        return ;
    QString val = result.section("=\"",1);
    //qDebug()<<val<<endl;
    QStringList valList = val.split(",");
    //qDebug()<<valList.size()<<endl;//33
    CurrentStock stock(stockID);
    if(valList.size()<30)
    {
        return ;
    }
    stock.stockName = valList[0];
    this->stockName = valList[0];
    stock.todayOpenPrice = valList[1].toDouble();
    stock.yesterdayClosePrice = valList[2].toDouble();
    stock.currentPrice = valList[3].toDouble();
    stock.todayHighest = valList[4].toDouble();
    stock.todayLowest = valList[5].toDouble();
    stock.bidPrice = valList[6].toDouble();
    stock.auctionPrice = valList[7].toDouble();
    stock.tradeNumber = valList[8].toDouble()/100;
    stock.turnOver = valList[9].toDouble();
    int i = 10;
    for(int j=0;j<5;j++)
    {
        double buynum = valList[i].toDouble()/100;
        double buyprice = valList[i+1].toDouble();
        stock.buyNum.push_back(buynum);
        stock.buyPrice.push_back(buyprice);
        i=i+2;
    }
    for(int j=0;j<5;j++)
    {
        double sellnum = valList[i].toDouble()/100;
        double sellprice = valList[i+1].toDouble();
        stock.sellNum.push_back(sellnum);
        stock.sellPrice.push_back(sellprice);
        i=i+2;
    }
    QRegularExpression rx;
    rx.setPattern("(?<y>\\d{4})-(?<m>\\d{1,2})-(?<d>\\d{1,2})");
    QRegularExpressionMatch match =  rx.match(valList[i++]);
    stock.data = QDate(match.captured("y").toInt(),match.captured("m").toInt()
                       ,match.captured("d").toInt());
    rx.setPattern("(?<h>\\d{1,2}):(?<m>\\d{1,2}):(?<s>\\d{1,2})");
    stock.time = QTime(match.captured("h").toInt(),match.captured("m").toInt()
                       ,match.captured("s").toInt());
    //stock.infoPrintf();
    this->stockData.push_back(stock);
}
