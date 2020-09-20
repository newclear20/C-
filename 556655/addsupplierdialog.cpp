#include "addsupplierdialog.h"
#include <QGridLayout>

addSupplierDialog::addSupplierDialog(QWidget *parent)
    : QDialog(parent)
{
    QLabel *nameLabel = new QLabel("商家名称");
    nameEdit = new QLineEdit;
    QLabel *addrLabel = new QLabel("商家所在地");
    addrEdit = new QComboBox;
    QStringList addrList;
    addrList<<"北京"<<"上海"<<"广州"<<"深圳"<<"重庆";
    addrEdit->addItems(addrList);
    QLabel *categoryLabel = new QLabel("经营类目");
    categoryEdit = new QComboBox;
    QStringList categoryList;
    categoryList<<"家电"<<"数码"<<"家居"<<"服饰"<<"食品";
    categoryEdit->addItems(categoryList);
    QLabel *contactLabel = new QLabel("联系人");
    contactEdit = new QLineEdit;
    QLabel *teleLabel = new QLabel("联系方式");
    teleEdit = new QLineEdit;
    addButton = new QPushButton("添加");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel,0,0);
    layout->addWidget(nameEdit,0,1);
    layout->addWidget(addrLabel,1,0);
    layout->addWidget(addrEdit,1,1);
    layout->addWidget(categoryLabel,2,0);
    layout->addWidget(categoryEdit,2,1);
    layout->addWidget(contactLabel,3,0);
    layout->addWidget(contactEdit,3,1);
    layout->addWidget(teleLabel,4,0);
    layout->addWidget(teleEdit,4,1);
    layout->addWidget(addButton,5,1);

    setLayout(layout);
    setWindowModality(Qt::WindowModal);
}
