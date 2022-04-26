#ifndef HOMEW_H
#define HOMEW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

namespace Ui {
class HomeW;
}

class HomeW : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomeW(QWidget *parent = 0);
    ~HomeW();

private slots:
    void on_addBt_clicked();
    void update_time();
    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_redSd_sliderMoved(int position);
    void on_greenSd_sliderMoved(int position);
    void on_blueSd_sliderMoved(int position);

private:
    Ui::HomeW *ui;
    QTimer *mtimer;
};

#endif // HOMEW_H
