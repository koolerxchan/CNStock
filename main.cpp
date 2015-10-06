
#include "mainwindow.h"
#include <QApplication>
#include "xlengine.h"
#include "databasemanagement.h"

int main(int argc, char *argv[])
{
    DataBaseManagement *dbManager  = DataBaseManagement::getInstance();
    dbManager->dbtest();


//    XlEngine *t = new XlEngine();
//    t->run();
//    return 1;

//#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
//  QApplication::setGraphicsSystem("raster");
//#endif
//  QApplication a(argc, argv);
//  MainWindow w;
//  w.show();
//  return a.exec();
}
