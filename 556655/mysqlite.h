#ifndef MYSQLITE_H
#define MYSQLITE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QLabel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include "addsupplierdialog.h"

class mySqlite
{
public:
    mySqlite();
    bool initSql();
    bool createTable();
    bool registerUser(QString name,QString password,QString role);
    bool loginUser(QString name,QString password);
    bool connectDB();
    QSqlQuery *query;
    QLabel  *userInfoLabel;
    QSqlDatabase myDB;

};
#endif
