#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QMediaPlayer>
#include <unistd.h>
#include "game_map.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateMap();
    void exchange(QPoint b1, QPoint b2);
    void setButtonImage();

private:
    Ui::MainWindow *ui;
    int gameSize;                                                                                //每行每列按钮个数
    int gameType;                                                                                //0-初始状态    1-游戏开始      2-游戏结束
    bool oneButtonIsSelect;                                                                      //是否有按钮已经被选中了
    QPoint selectedButton;                                                                       //被选中的按钮的坐标
    int buttonType[20][20] = {{0,1,2,3,0}, {1,2,3,0,1}, {2,3,0,1,2}, {3,0,1,2,3}, {0,1,2,3,0}};  //各个位置的图片编号 1、2、3、4
    QPushButton *gameButtons[20][20];                                                            //按钮
    QQueue<QPoint> buttonNeedChange;                                                              //待改变的按钮位置队列
    game_map *gm;
    int touchTimes;
    QMediaPlayer *musicPlayer;

protected:
    void paintEvent(QPaintEvent * event);

private slots:
    void gameStartButtonClicked();
    void gameStopButtonClicked();
    void gameHelpButtonClicked();
    void gameListButtonClicked();
    void gameButtonClicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_actionstartt_triggered();
    void on_actionhelpp_triggered();
    void on_pushButton_3_clicked();
    void on_actionmusicc_triggered();
    void on_actiongratMusicc_triggered();
    void on_pushButton_4_clicked();
    void on_actionlistt_triggered();
};

#endif // MAINWINDOW_H
