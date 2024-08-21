#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //创建数据库实例
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //设置连接主机的ip
    db.setHostName("localhost");
    //设置mysql的用户名 默认root
    db.setUserName("root");
    //设置数据库名
    db.setDatabaseName("testdb");
    //设置数据库密码
    db.setPassword("root");
    //设置数据库端口号
    db.setPort(3306);

    //连接数据库
    if(db.open()){
        qDebug() << db.lastError().text();
        return ;
    }

    //执行查询语句
    QSqlQuery query;
    query.exec("select * from person");
    while(query.next()){
        query.value(0);
        query.value("name");
        query.value("age").toInt();
    }

    //数据库事务
    db.transaction(); //创建一个事务,设置回滚点
    bool flag = query.exec("insert into person valuse(9,20,'man','tom')");
    if(flag){
        //提交修改
        db.commit();
    }else{
        //回滚数据
        db.rollback();
    }

    //断开连接
    db.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

