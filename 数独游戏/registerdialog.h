#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "rankingdialog.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:

    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_sureButton_clicked();
    void on_cancelButton_clicked();

public:
    void scoreShow();
    RankingDialog *myrank;  //排行榜

private:
    Ui::RegisterDialog *ui;

};

#endif // REGISTERDIALOG_H
