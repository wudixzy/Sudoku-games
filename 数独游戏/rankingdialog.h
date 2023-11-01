#ifndef RANKINGDIALOG_H
#define RANKINGDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QCoreApplication>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QList>

namespace Ui {
class RankingDialog;
}

class RankingDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit RankingDialog(QWidget *parent = nullptr);  //构造函数
    ~RankingDialog();                                   //析构函数
    void insertdata(QString name, int level, int score);    //表格中加入数据

  private:
    Ui::RankingDialog *ui;                              //界面
    //设置模型
    QSqlTableModel *model;
    int msize;
};

#endif // RANKINGDIALOG_H
