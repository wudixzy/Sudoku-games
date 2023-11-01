#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Difficulty; }
QT_END_NAMESPACE

class Difficulty : public QDialog
{
    Q_OBJECT

public:
    Difficulty(QWidget *parent = nullptr);
    ~Difficulty();

private slots:
    void on_difficultyButton_1_clicked();

    void on_difficultyButton_2_clicked();

    void on_difficultyButton_3_clicked();

private:
    Ui::Difficulty *ui;
};
#endif // DIFFICULTY_H
