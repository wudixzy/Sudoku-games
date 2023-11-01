#include "rankingdialog.h"
#include "ui_rankingdialog.h"
RankingDialog::RankingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RankingDialog)
{
    ui->setupUi(this);

    //设置不可修改
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    msize=0;
    setWindowTitle(tr("排行榜"));//设置窗体标题
    QSqlDatabase db =QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("TetrisDB.db");      //设置数据库名
    db.setHostName("easybook-3313b0");  //设置数据库主机名
    db.setUserName("kaz");        //设置数据库用户名
    db.setPassword("123456");           //设置数据库密码
    if (db.open() == false)
    {
       QMessageBox::warning(this, "错误", db.lastError().text());
       return;
    }

    QSqlQuery query;
    bool success=true;
    if(db.tables().contains(QString("Tetris")))//判断是否存在表
     {
        qDebug()<<QObject::tr("Tetris！\n");
        success=query.exec(QString("DROP TABLE Tetris"));
        if( success)
            qDebug()<<QObject::tr("数据库表Tetris删除成功！\n");
        else
            qDebug()<<QObject::tr("数据库表删除失败！\n");
     }

    success=query.exec("create table Tetris(id int primary key,"
                                 "name varchar, score int, leverl int);");
   query.finish();
   if(success)
       qDebug()<<QObject::tr("数据库表创建成功！\n");
   else
       qDebug()<<QObject::tr("数据库表创建失败！\n");

   model = new QSqlTableModel(this);  //建立模型
   model->setTable("Tetris");//指定使用的表

   //把model放入view中
   ui->tableView->setModel(model);

   //显示数据
   model->select();

   //修改表头
   model->setHeaderData(0,Qt::Horizontal,"排名");
   model->setHeaderData(1,Qt::Horizontal,"用户名");
   model->setHeaderData(2,Qt::Horizontal,"分数");
   model->setHeaderData(3,Qt::Horizontal,"用时");
   ui->tableView->hideColumn(0);
}

RankingDialog::~RankingDialog()
{
    delete ui;
}

void RankingDialog::insertdata(QString name, int time, int score)
{
    QSqlQuery query;
    bool success=false;   //用于判断数据库操作是否成功
    query.prepare("insert into Tetris values(?,?,?,?);");  //?占位 后面赋值
    msize++;  //记录已有的游戏记录总数
    query.bindValue(0,msize);  //第一列为关键字，进入排行榜的顺序
    query.bindValue(1,name);   //第二列为用户名
    query.bindValue(2,score);  //第三列为游戏分数
    query.bindValue(3,time);  //第四列为游戏时间
    success=query.exec(); //执行一次插入操作，用bindvalue替换占位符“？”
    if(!success) //如果插入不成功
    {
        //在控制台现实失败原因，便于维护程序
        QSqlError lastError=query.lastError();
        qDebug()<<lastError.driverText()<<QString(QObject::tr("插入失败"));
    }
    else qDebug()<<QString(QObject::tr("插入成功"));

    model->clear();            //清除之前的表
    model->setTable("Tetris");//指定使用的表

    //把model放入view中
    ui->tableView->setModel(model);

    //显示数据
    model->select();

    //修改表头
    model->setHeaderData(0,Qt::Horizontal,"排名");
    model->setHeaderData(1,Qt::Horizontal,"用户名");
    model->setHeaderData(2,Qt::Horizontal,"分数");
    model->setHeaderData(3,Qt::Horizontal,"用时");
    model->setSort(2,Qt::DescendingOrder);
    model->select();
    ui->tableView->hideColumn(0); //第一列不显示
    query.finish();  //关闭query

}
