#include "mainwindow.h"
#include "mysqlite.h"
#include "addsupplierdialog.h"
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QStackedWidget>
#include <QLabel>
#include <QIcon>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QApplication>
#include <QHBoxLayout>
#include <QComboBox>
#include <QTimeEdit>
#include <QTableView>
#include <QSqlRecord>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    creatMenu();
    creatTool();
    this->setWindowTitle("云仓库");
    this->setFixedSize(800,800);
    creatNaviBar();
    creatStackWidget();

    checkDB();

        connect(homeAction,&QAction::triggered,this,&MainWindow::switchPages);
        connect(supplierAction,&QAction::triggered,this,&MainWindow::switchPages);
        connect(goodsAction,&QAction::triggered,this,&MainWindow::switchPages);
        connect(stockAction,&QAction::triggered,this,&MainWindow::switchPages);
        connect(infoAction,&QAction::triggered,this,&MainWindow::switchPages);
        connect(userAction,&QAction::triggered,this,&MainWindow::switchPages);

        mysql = new mySqlite;
            if(mysql->initSql())
                qDebug()<<"连接成功";
            else
                qDebug()<<"连接失败";

}


void MainWindow::userLogin()        //登录
{
    QString name = myLoginDialog->nameEdit->text();
    QString password = myLoginDialog->passwordEdit->text();
    mysql = new mySqlite;
    if(!mysql->loginUser(name,password))
        QMessageBox::information(this, tr("消息"), tr("登录失败，请重试!"), QMessageBox::Ok);
    else
    {
        QMessageBox::information(this, tr("消息"), tr("登录成功!"), QMessageBox::Ok);
        myLoginDialog->hide();
        loginAct->setVisible(false);
        userInfoLabel->setText("已登录:"+name);
        userInfoLabel->show();
    }
}
QWidget *MainWindow::creatSupplierPage()
{
    QWidget *supplierPage = new QWidget;

    QLabel *titleLabel = new QLabel("供应商信息");
    QPushButton *addButton = new QPushButton("添加");
    connect(addButton,&QPushButton::clicked,this,&MainWindow::addSupplier);
    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->addWidget(titleLabel);
    titleLayout->addStretch();
    titleLayout->addWidget(addButton);

    QLabel *idLabel = new QLabel("商家编号");
    QLineEdit *idEdit = new QLineEdit;
    QLabel *nameLabel = new QLabel("商家名称");
    QLineEdit *nameEdit = new QLineEdit;
    QLabel *addrLabel = new QLabel("所在地");
    QComboBox *addrEdit = new QComboBox;
    QLabel *dateLabel = new QLabel("添加日期");
    QDateEdit *dateEdit = new QDateEdit;
    QLabel *cateLabel = new QLabel("经营品类");
    QComboBox *cateEdit = new QComboBox;
    QPushButton *searchButton = new QPushButton("搜索");

    QHBoxLayout *sLayout_1 = new QHBoxLayout;
    sLayout_1->addWidget(idLabel);
    sLayout_1->addWidget(idEdit);
    sLayout_1->addStretch();
    sLayout_1->addWidget(nameLabel);
    sLayout_1->addWidget(nameEdit);
    sLayout_1->addStretch();
    sLayout_1->addWidget(addrLabel);
    sLayout_1->addWidget(addrEdit);
    sLayout_1->addStretch();
    sLayout_1->addWidget(dateLabel);
    sLayout_1->addWidget(dateEdit);

    QHBoxLayout *sLayout_2 = new QHBoxLayout;
    sLayout_2->addWidget(cateLabel);
    sLayout_2->addWidget(cateEdit);
    sLayout_2->addStretch();
    sLayout_2->addWidget(searchButton);

    QVBoxLayout *sLayout = new QVBoxLayout;
    sLayout->addLayout(sLayout_1);
    sLayout->addLayout(sLayout_2);
    QFrame *sFrame = new QFrame;
    sFrame->setFrameStyle(QFrame::StyledPanel);
    sFrame->setLayout(sLayout);

    supplierModel = new QSqlTableModel(supplierPage, mysql->myDB);//关联数据库
    supplierModel->setTable("supplier");//选择数据表
    supplierModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置保存策略为手动提交
    supplierModel->setHeaderData(0,Qt::Horizontal, "序号");
    supplierModel->setHeaderData(1,Qt::Horizontal, "商家名称");
    supplierModel->setHeaderData(2,Qt::Horizontal, "所在地");
    supplierModel->setHeaderData(3,Qt::Horizontal, "添加日期");
    supplierModel->setHeaderData(4,Qt::Horizontal, "经营类目");
    supplierModel->setHeaderData(5,Qt::Horizontal, "商品数量");
    supplierModel->setHeaderData(6,Qt::Horizontal, "联系人");
    supplierModel->setHeaderData(7,Qt::Horizontal, "联系方式");
    supplierModel->select(); //选取整个表的所有行

    QTableView *tableView = new QTableView(this);
    tableView->setModel(supplierModel);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//使其不可编辑

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(titleLayout);
    layout->addWidget(sFrame);
    layout->addWidget(tableView);
    supplierPage->setLayout(layout);
    return supplierPage;

}
void MainWindow::addSupplier()
{

    supplierAddDialog = new addSupplierDialog(this);
    supplierAddDialog->show();
    connect(supplierAddDialog->addButton,&QPushButton::clicked,this,&MainWindow::insertSupplierData);
}
void MainWindow::userRegister()            //注册
{
    QString name = myLoginDialog->nameEdit->text();
    QString password = myLoginDialog->passwordEdit->text();
    QString role = "staff";
    mysql = new mySqlite;
    if(!mysql->registerUser(name,password,role))
        QMessageBox::information(this, tr("消息"), tr("注册失败，请重试!"), QMessageBox::Ok);
    else
    {
        QMessageBox::information(this, tr("消息"), tr("注册成功!"), QMessageBox::Ok);
        userLogin();
    }
}
void MainWindow::insertSupplierData()
{
    QString supplierName = supplierDialog->nameEdit->text();
    QString supplierAddr = supplierDialog->addrEdit->currentText();
    QDate currentDate = QDateTime::currentDateTime().date();
    QString supplierDate = currentDate.toString("yyyy.MM.dd");
    QString suppliercategory = supplierDialog->categoryEdit->currentText();
    QString supplierContact = supplierDialog->contactEdit->text();
    QString supplierTele = supplierDialog->teleEdit->text();

    QSqlRecord record = supplierModel->record();
    record.setValue(1,supplierName);
    record.setValue(2,supplierAddr);
    record.setValue(3,supplierDate);
    record.setValue(4,suppliercategory);
    record.setValue(6,supplierContact);
    record.setValue(7,supplierTele);
    supplierModel->insertRecord(supplierModel->rowCount(), record);
    supplierModel->submitAll();
}
void MainWindow::creatStackWidget()
{
    stackWidget = new QStackedWidget;

    QLabel *label1 = new QLabel("1");
    QWidget *supplierPage = creatSupplierPage();
    QLabel *label3 = new QLabel("3");
    QLabel *label4 = new QLabel("4");
    QLabel *label5 = new QLabel("5");
    QLabel *label6 = new QLabel("6");
    stackWidget->addWidget(label1);
    stackWidget->addWidget(supplierPage);
    stackWidget->addWidget(label3);
    stackWidget->addWidget(label4);
    stackWidget->addWidget(label5);
    stackWidget->addWidget(label6);
    setCentralWidget(stackWidget);
}



void MainWindow::creatNaviBar()            //按钮贴纸
{
    QToolBar *naviBar = new QToolBar("导航",this);
    naviBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addToolBar(Qt::LeftToolBarArea,naviBar);

    const QIcon homeIcon = QIcon::fromTheme("home", QIcon(":/tubiao/home.png"));
    homeAction = new QAction(homeIcon,"主页",this);
    naviBar->addAction(homeAction);

    const QIcon supplierIcon = QIcon::fromTheme("supplier", QIcon(":/tubiao/giver.png"));
    supplierAction = new QAction(supplierIcon,"供应商管理",this);
    naviBar->addAction(supplierAction);

    const QIcon goodsIcon = QIcon::fromTheme("goods", QIcon(":/tubiao/shangpin.png"));
    goodsAction = new QAction(goodsIcon,"商品管理",this);
    naviBar->addAction(goodsAction);

    const QIcon stockIcon = QIcon::fromTheme("stock", QIcon(":/tubiao/things.png"));
    stockAction = new QAction(stockIcon,"库存管理",this);
    naviBar->addAction(stockAction);

    const QIcon infoIcon = QIcon::fromTheme("info", QIcon(":/tubiao/information.png"));
    infoAction = new QAction(infoIcon,"信息管理",this);
    naviBar->addAction(infoAction);

    const QIcon userIcon = QIcon::fromTheme("user", QIcon(":/tubiao/user.png"));
    userAction = new QAction(userIcon,"用户管理",this);
    naviBar->addAction(userAction);

    naviBar->setMovable(false);
}
void MainWindow::switchPages()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if(action->text() == "主页")
        stackWidget->setCurrentIndex(0);
    if(action->text() == "供应商管理")
        stackWidget->setCurrentIndex(1);
    if(action->text() == "商品管理")
        stackWidget->setCurrentIndex(2);
    if(action->text() == "库存管理")
        stackWidget->setCurrentIndex(3);
    if(action->text() == "信息管理")
        stackWidget->setCurrentIndex(4);
    if(action->text() == "用户管理")
        stackWidget->setCurrentIndex(5);
}

void MainWindow::checkDB()
{
    QString dbFilePath = QApplication::applicationDirPath() +"myWMS.db";
    QFile file(dbFilePath);
    if(!file.exists())
    {
        QMessageBox messageWarning(QMessageBox::Warning,"警告","数据库配置失败，是否初始化数据库",QMessageBox::Yes|QMessageBox::No);
        if (messageWarning.exec()==QMessageBox::Yes)
        {
            mysql = new mySqlite;
            if(mysql->initSql())
                QMessageBox::information(this, "数据库信息", "数据库已重置。");
            else
                QMessageBox::information(this, "数据库信息", "数据库重置失败，请联系系统管理员。");
        }
    }
    else
    {
        mysql = new mySqlite;
        if(!mysql->connectDB())
            QMessageBox::information(this, "数据库信息", "数据库连接失败，请联系系统管理员。");
        else
            qDebug()<<"连接成功";
    }
}
void MainWindow::creatTool()
{
    QToolBar *loginToolBar = addToolBar("登录");//添加登录工具条
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    loginToolBar->addWidget(spacer);
    QAction *loginAct = new QAction("登录", this);//新建登录动作
    loginToolBar->addAction(loginAct);
    loginToolBar->setMovable(false);
    myLoginDialog = new loginDialog(this);
    connect(loginAct,&QAction::triggered,myLoginDialog,&QDialog::show);
    connect(myLoginDialog->registButton,&QPushButton::clicked,this,&MainWindow::userRegister);
    connect(myLoginDialog->loginButton,&QPushButton::clicked,this,&MainWindow::userLogin);
     userInfoLabel = new QLabel("");
     loginToolBar->addWidget(userInfoLabel);
     userInfoLabel->hide();
}

void MainWindow::creatMenu()
{
    QMenu *fileMenu = menuBar()->addMenu("文件");//添加文件菜单项
}
MainWindow::~MainWindow()
{

}
