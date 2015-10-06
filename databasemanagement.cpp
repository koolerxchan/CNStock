#include "databasemanagement.h"

DataBaseManagement *DataBaseManagement::getInstance() throw(std::bad_alloc)
{
    static std::auto_ptr<DataBaseManagement> sp(new DataBaseManagement);
    static bad_alloc alloc_failed;
    if(sp.get() == NULL)
        throw(alloc_failed);
    return sp.get();
}


DataBaseManagement::DataBaseManagement()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName( "stockInfo.db");
    db.setHostName("localhost");
    db.setUserName("xchan");//设置数据库的用户名
    if(!db.open())
    {
        cout<<"db open failed!"<<endl;
         return ;
    }
}

void DataBaseManagement::installStockNameIDFromFile(QString fileName,QString label)
{
    QString result;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        cout<<"fatal error!"<<endl;
    }

    while(!file.atEnd())
    {
        result+= file.readLine();
    }
    file.close();
    QStringList stockList = result.split(" ");

    QSqlQuery query;//新建一个查询库
    //创建一个类型表,表名为type;varchar是用来保存可变长度的字符串
    query.exec("create table stockIDName(id int primary key, name varchar, atPlace varchar)");

    for(int i=0;i<stockList.size();i++)
    {
        QString name = stockList[i];i++;
        QString id = stockList[i];
        QString baseCMD = "insert into stockIDName values";
        baseCMD +="('" + id + "', '" + name+ "', '" + label+"')";
        //cout<<baseCMD.toStdString()<<endl;
        query.exec(baseCMD);
    }

}


void DataBaseManagement::dbtest()
{

    installStockNameIDFromFile("stockNameAndId-sz","sz");
    cout<<"sz file ... ok!"<<endl;
    installStockNameIDFromFile("stockNameAndId-sh","sh");
    cout<<"sh file ... ok!"<<endl;

}

pair<QString,QString> DataBaseManagement::getStockNameByID(QString id)
{
    QSqlQuery query;//新建一个查询库
}

pair<QString,QString> DataBaseManagement::getStockIDByName(QString name)
{

}





QString DataBaseManagement::getDataBaseName()
{
    return m_dbName;
}
