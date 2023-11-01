#include "difficulty.h"
#include "ui_difficulty.h"
#include"gamearea.h"
Difficulty::Difficulty(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Difficulty)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(204, 255, 255,200), stop:1 rgba(229, 255, 255, 210));");
    //设计页面渐变
}

Difficulty::~Difficulty()
{
    delete ui;
}

//下方难度调整
void Difficulty::on_difficultyButton_1_clicked()
{
    level=1;
    ui->difficultyLabel_2->setText("简单");
    update();
}

void Difficulty::on_difficultyButton_2_clicked()
{
    level=2;
    ui->difficultyLabel_2->setText("普通");
    update();
}

void Difficulty::on_difficultyButton_3_clicked()
{
    level=3;
    ui->difficultyLabel_2->setText("困难");
    update();
}
