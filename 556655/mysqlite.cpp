#include "mysqlite.h"
#include <QSqlDatabase>
#include <QApplication>
#include <QSqlQuery>
#include <QDebug>

mySqlite::mySqlite()
{

}

bool mySqlite::initSql()
{
    if(!connectDB())
        return false;
    else if (!createTable())
    {
        return false;
    }
    return true;
}
bool mySqlite::connectDB()
{
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName(QApplication::applicationDirPath() +"myWMS.db");
    if(!myDB.open())
        return false;
    return true;
}
bool mySqlite::loginUser(QString name,QString password)
{
    query=new QSqlQuery;
    QString str=QString("select * from user where name= '%1' and password = '%2' ").arg(name).arg(password);
    query->exec(str);
    return query->next();
}
bool mySqlite::registerUser(QString name,QString password,QString role)
{
    query=new QSqlQuery;
    QString str = QString("insert into user values(null,'%1','%2','%3')").arg(name).arg(password).arg(role);
    if(!query->exec(str))
        return false;
    return true;
}
bool mySqlite::createTable()
{
    query=new QSqlQuery;
    QString userStr = "create table if not exists user("
                      "[id] integer primary key autoincrement,"
                      "[name] varchar(30),"
                      "[password] varchar(30),"
                      "[role] varchar(30)"
                      ")";
    QString supplierStr = "create table if not exists supplier("
                          "[id] integer primary key autoincrement,"
                          "[name] varchar(30),"
                          "[addr] varchar(30),"
                          "[date] varchar(30),"
                          "[category] varchar(30),"
                          "[goodsCount] integer,"
                          "[contact] varchar(30),"
                          "[telephone] varchar(30)"
                          ")";
    QString goodsStr = "create table if not exists goods("
                       "[id] integer primary key autoincrement,"
                       "[name] varchar(30),"
                       "[category] varchar(30),"
                       "[speci] varchar(30),"
                       "[addr] varchar(30),"
                       "[brand] varchar(30),"
                       "[manu] varchar(30),"
                       "[note] varchar(30)"
                       ")";
    if(!(query->exec(userStr)&&query->exec(supplierStr)&&query->exec(goodsStr)))
        return false;
    return true;
}
