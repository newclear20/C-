#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logindialog.h"
#include "addsupplierdialog.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <mysqlite.h>
#include <QSqlTableModel>
#include  <QWidget>

#include  <QDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void creatMenu();
    void creatTool();
    void creatNaviBar();
    void creatStackWidget();
    void switchPages();
    void userRegister();
    void userLogin();
    void checkDB();

   QWidget *creatSupplierPage();
   addSupplierDialog *supplierDialog;
   addSupplierDialog *supplierAddDialog;
    void addSupplier();
    void insertSupplierData();

    mySqlite *mysql;
    QStackedWidget *stackWidget;
    loginDialog *myLoginDialog;
        QSqlTableModel* supplierModel;
        QLabel  *userInfoLabel;
        QAction *homeAction;
        QAction *supplierAction;
        QAction *goodsAction;
        QAction *stockAction;
        QAction *infoAction;
        QAction *userAction;
        QAction *loginAct;

};

#endif // MAINWINDOW_H
