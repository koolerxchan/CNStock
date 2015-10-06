#ifndef DATABASEMANAGEMENT_H
#define DATABASEMANAGEMENT_H
#include <QSql>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <iostream>
#include <auto_ptr.h>
using namespace std;

class DataBaseManagement
{
public:
    friend class std::auto_ptr<SnifferThread>;
    static DataBaseManagement *getInstance() throw(std::bad_alloc);
    DataBaseManagement();
    QString getDataBaseName();

    /* pair.first is ID or the Name you want to get
     * pair.second is what type of the stock is ,or the atPlace
     * which means sz or sh or jj(基金)*/
    pair<QString,QString> getStockNameByID(QString id);
    pair<QString,QString>  getStockIDByName(QString name);

    void dbtest();


private:
    QSqlDatabase db ;
    QString m_dbName;

private:
    /* file come from internet
     * website is http://bbs.10jqka.com.cn/codelist.html*/
    void installStockNameIDFromFile(QString fileName, QString label);

};

#endif // DATABASEMANAGEMENT_H
