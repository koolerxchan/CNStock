#include "DataType.h"
string g_str(int number)
{
    stringstream ss;
    ss<<number;
    return ss.str();
}

string g_str(double number)
{
    stringstream ss;
    ss<<number;
    return ss.str();
}

string g_str(QString s)
{

    return s.toStdString();
}
