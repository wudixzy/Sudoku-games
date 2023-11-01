#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox>
#include"gamearea.h"
RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{


    ui->setupUi(this);
    myrank=new RankingDialog(this);
    setWindowTitle(tr("请输入用户名"));//设置窗体标题
    //界面美化
    this->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(204,204,255,200), stop:1 rgba(229,204,255, 210));");
    ui->sureButton->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(236,51,134);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(240,94,159);}"
                                    "QPushButton:pressed{background-color: rgb(182,16,90);}");//pressed
    ui->cancelButton->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(236,51,134);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(240,94,159);}"
                                    "QPushButton:pressed{background-color: rgb(182,16,90);}");//pressed
    ui->nameEdit->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:20px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:2px solid rgb(236,51,134);border-radius:15px;");//边框粗细-颜色-圆角设置
   ui->label->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                            "color: rgb(31,31,31);"		//字体颜色
                            "padding-left:20px;");      //内边距-字体缩进
   ui->label_2->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                            "color: rgb(31,31,31);"		//字体颜色
                            "padding-left:20px;");      //内边距-字体缩进


}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_sureButton_clicked()
{
    QString str=ui->nameEdit->text();

     myrank->insertdata(ui->nameEdit->text(),mTime,mScore);
    close();
}

void RegisterDialog::on_cancelButton_clicked()
{
    close();
}
void RegisterDialog::scoreShow()
{
    QString scoreText = QString::number(mScore);
    ui->scoreLabel->setText(scoreText);
}
