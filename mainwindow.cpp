#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gameSize(0),
    gameType(0),
    oneButtonIsSelect(false),
    touchTimes(0),
    musicPlayer(new QMediaPlayer)
{
    musicPlayer->setMedia(QUrl("qrc:/new/prefix1/Deemo.mp3"));
    musicPlayer->setVolume(1);
    musicPlayer->play();
    buttonNeedChange.clear();

//    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(gameStartButtonClicked()));
//    connect(ui->actionstartt, SIGNAL(traggered()), this, SLOT(gameStartButtonClicked()));
//    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(gameStopButtonClicked()));

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateMap() {
    for(int i = 0; i < gameSize; i++) {
        for(int j = 0; j < gameSize; j++) {
            if(buttonType[i][j] != gm->get_map(gm->index(i + 1, j + 1))) {
                buttonType[i][j] = gm->get_map(gm->index(i + 1, j + 1));
                buttonNeedChange.push_back(QPoint(i,j));
            }
        }
    }
    this->repaint();
}

void MainWindow::exchange(QPoint b1, QPoint b2) {
    int i1 = b1.x(), j1 = b1.y();
    int i2 = b2.x(), j2 = b2.y();
    int tmp = buttonType[i1][j1];
    buttonType[i1][j1] = buttonType[i2][j2];
    buttonType[i2][j2] = tmp;
    this->repaint();
}

void MainWindow::setButtonImage() {

    while(!buttonNeedChange.empty()) {
        QPoint button = buttonNeedChange.first();
        buttonNeedChange.pop_front();
        int i = button.x(), j = button.y();
        QIcon qicon;


        switch(buttonType[i][j]) {
        case 4: {
    //        qicon.addFile(":/new/prefix1/giraffee.png");
    //        gameButtons[i][j]->setIcon(qicon);
            if(gameButtons[i][j]->isChecked()) {
                gameButtons[i][j]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/giraffeeStroke.png);}");
            } else {
                gameButtons[i][j]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/giraffee.png);}"
                                                 "QPushButton:hover{border-image: url(:/new/prefix1/giraffeeStroke.png);}"
                                                 "QPushButton:pressed{border-image: url(:/new/prefix1/giraffeeStroke.png);}");
            }
            break;
        }
        case 1: {
    //        qicon.addFile(":/new/prefix1/giraffee.png");
    //        gameButtons[i][j]->setIcon(qicon);
            if(gameButtons[i][j]->isChecked()) {
                gameButtons[i][j]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/monkeyyStroke.png);}");
            } else {
                gameButtons[i][j]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/monkeyy.png);}"
                                                 "QPushButton:hover{border-image: url(:/new/prefix1/monkeyyStroke.png);}"
                                                 "QPushButton:pressed{border-image: url(:/new/prefix1/monkeyyStroke.png);}");
            }
            break;
        }
        case 2: {
    //        qicon.addFile(":/new/prefix1/giraffee.png");
    //        gameButtons[i][j]->setIcon(qicon);
            if(gameButtons[i][j]->isChecked()) {
                gameButtons[i][j]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/snakeeStroke.png);}");
            } else {
                gameButtons[i][j]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/snakee.png);}"
                                                 "QPushButton:hover{border-image: url(:/new/prefix1/snakeeStroke.png);}"
                                                 "QPushButton:pressed{border-image: url(:/new/prefix1/snakeeStroke.png);}");
            }
            break;
        }
        case 3: {
    //        qicon.addFile(":/new/prefix1/giraffee.png");
    //        gameButtons[i][j]->setIcon(qicon);
            if(gameButtons[i][j]->isChecked()) {
                gameButtons[i][j]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/hippopotamussStroke.png);}");
            } else {
                gameButtons[i][j]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/hippopotamuss.png);}"
                                                 "QPushButton:hover{border-image: url(:/new/prefix1/hippopotamussStroke.png);}"
                                                 "QPushButton:pressed{border-image: url(:/new/prefix1/hippopotamussStroke.png);}");
            }
            break;
        }
        case 5: {
    //        qicon.addFile(":/new/prefix1/giraffee.png");
    //        gameButtons[i][j]->setIcon(qicon);
            if(gameButtons[i][j]->isChecked()) {
                gameButtons[i][j]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/qieStroke.png);}");
            } else {
                gameButtons[i][j]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/qie.png);}"
                                                 "QPushButton:hover{border-image: url(:/new/prefix1/qieStroke.png);}"
                                                 "QPushButton:pressed{border-image: url(:/new/prefix1/qieStroke.png);}");
            }
            break;
        }
        case 6: {
    //        qicon.addFile(":/new/prefix1/giraffee.png");
    //        gameButtons[i][j]->setIcon(qicon);
            if(gameButtons[i][j]->isChecked()) {
                gameButtons[i][j]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/huliStroke.png);}");
            } else {
                gameButtons[i][j]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/huli.png);}"
                                                 "QPushButton:hover{border-image: url(:/new/prefix1/huliStroke.png);}"
                                                 "QPushButton:pressed{border-image: url(:/new/prefix1/huliStroke.png);}");
            }
            break;
        }
        case -1: {
            gameButtons[i][j]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/baozha.png);}");
        }
        }
    }
}

void MainWindow::paintEvent(QPaintEvent * event) {

//背景图片
    QPainter painter(this);
    QImage image;
    //加载图片
    image.load(":/new/prefix1/timg.jpg");
    //输出图片的一些信息
    //在界面上绘制图片
    painter.drawImage(QPoint(0, 0), image);

//按钮图片
    if(gameType==1) {
        int areaLeft, areaRight, areaUp, areaDown;
        int buttonSize;

        areaLeft = ui->groupBox->pos().x();
        areaUp = ui->groupBox->pos().y() + 65;         //不知道为什么上方位置不准
        areaRight = areaLeft + 650;
        areaDown = areaUp + 650;
        buttonSize = 650/gameSize;

        setButtonImage();
        ui->lcdNumber->display(gm->get_score());
        ui->lcdNumber_2->display(gm->combol);
        ui->lcdNumber_3->display(touchTimes);

    }
}

void MainWindow::gameStartButtonClicked() {
    if(gameType==1) {
        QMessageBox::information(this, tr("提示"), tr("游戏已经开始！"), QMessageBox::Ok);
        return;
    }

    int r = QMessageBox::question(this, tr("难度选择"), tr("请选择难度:"), QObject::tr(("简单")), QObject::tr(("普通")), QObject::tr(("困难")));

    if(r==0) {
        gameSize = 7;
        gm = new game_map(1, 0);
        touchTimes = 50;

    } else if(r==1) {
        gameSize = 10;
        gm = new game_map(2, 0);
        touchTimes = 40;
    } else {
        gameSize = 15;
        gm = new game_map(3, 0);
        touchTimes = 3;
    }

    gm->map_creat();

    int areaLeft, areaRight, areaUp, areaDown;
    int buttonSize;

    areaLeft = ui->groupBox->pos().x();
    areaUp = ui->groupBox->pos().y() + 65;         //不知道为什么上方位置不准
    areaRight = areaLeft + 650;
    areaDown = areaUp + 650;
    buttonSize = 650/gameSize;

    QGridLayout *layout = new QGridLayout;
    for(int i = 0; i < gameSize; i++) {
        for(int j = 0; j < gameSize; j++) {

            buttonType[i][j] = gm->get_map(gm->index(i + 1, j + 1));

            QString ss;
            gameButtons[i][j] = new QPushButton;
            gameButtons[i][j]->setMinimumSize(buttonSize, buttonSize);
            gameButtons[i][j]->setMaximumSize(buttonSize, buttonSize);
            gameButtons[i][j]->setFlat(true);
            gameButtons[i][j]->setCheckable(true);
            layout->addWidget(gameButtons[i][j], i, j);
            if(i<10) {
                ss[0] = '0';
                ss[1] = '0' + i;
            } else {
                ss[0] = '0' + i/10;
                ss[1] = '0' + i%10;
            }
            if(j<10) {
                ss[2] = '0';
                ss[3] = '0' + j;
            } else {
                ss[2] = '0' + j/10;
                ss[3] = '0' + j%10;
            }
            ss[4] = 0;
            gameButtons[i][j]->setObjectName(ss);
            connect(gameButtons[i][j], SIGNAL(clicked()), this, SLOT(gameButtonClicked()));
            buttonNeedChange.push_back(QPoint(i,j));
        }
    }
    ui->groupBox->setLayout(layout);
    gameType = 1;
}

void MainWindow::gameStopButtonClicked() {
    this->close();
}

void MainWindow::gameHelpButtonClicked() {
    QMessageBox::about(this, tr("游戏规则"), tr("\t游戏难度分为1，2，3级三个难度，分别对应7*7，10*10，15*15的矩\
                                            阵。1级难度需要在50步内对四种图形进行消除以积累得分，2级难度需要\
                                            在40步内对五种图形进行消除以积累的分，3级难度需要在30步内对六种图\
                                            形进行消除以累计得分。\
                                            \n\t游戏设置了连击数，对于每次填充后若无交换操作仍可消除将产生连击数，连击数越高得分加成越高哦！\
                                            \n\t排行榜可以记录游戏中同等难度最高的五次得分，加油获得更高的分数去冲击自己的排行吧！"));
}


void MainWindow::gameListButtonClicked() {
    int r = QMessageBox::question(this, tr("排行榜"), tr("请选择难度:"), QObject::tr(("简单")), QObject::tr(("普通")), QObject::tr(("困难")));
    gm->get_data(r);
    QMessageBox::about(this, tr("排行榜"), tr("").sprintf("\t\t排行榜\n\t1、\t%d\n\t2、\t%d\n\t3、\t%d\n\t4、\t%d\n\t5、\t%d\n",gm->get_v(0),gm->get_v(1),gm->get_v(2),gm->get_v(3),gm->get_v(4)));
}

void MainWindow::gameButtonClicked() {

    QObject *object = QObject::sender();
    QPushButton *push_button = qobject_cast<QPushButton *>(object);
    QString object_name = push_button->objectName();
    QByteArray ssp = object_name.toLatin1();
    char* sp = ssp.data();
    int ii, jj;
    ii = (sp[0] - '0')*10 + (sp[1] - '0');
    jj = (sp[2] - '0')*10 + (sp[3] - '0');
    buttonNeedChange.push_back(QPoint(ii,jj));
    this->repaint();

    if(!gm->continue_game_judge()) {
        gm->map_creat();
        gameButtons[ii][jj]->setChecked(false);
        for(int i = 0; i < gameSize; i++) {
            for(int j = 0; j < gameSize; j++) {
                buttonType[i][j] = gm->get_map(gm->index(i + 1, j + 1));
                buttonNeedChange.push_back(QPoint(i,j));
            }
        }
        return;
    }

    if(oneButtonIsSelect==false) {
        oneButtonIsSelect = true;
        selectedButton.setX(ii);
        selectedButton.setY(jj);
    } else {

        gameButtons[selectedButton.x()][selectedButton.y()]->setChecked(false);
        gameButtons[ii][jj]->setChecked(false);

        if((abs(selectedButton.x()-ii)==1&&(selectedButton.y()==jj))||(abs(selectedButton.y()-jj)==1&&(selectedButton.x()==ii))) {

            qDebug() << tr("交换两点");

            oneButtonIsSelect = false;
            buttonNeedChange.push_back(QPoint(selectedButton.x(),selectedButton.y()));
            buttonNeedChange.push_back(QPoint(ii,jj));
            exchange(selectedButton, QPoint(ii, jj));
            sleep(300);
            if(!gm->change_judge(ii + 1, jj + 1, selectedButton.x() + 1, selectedButton.y() + 1)) {

                qDebug() << tr("换回两点");

                buttonNeedChange.push_back(QPoint(selectedButton.x(),selectedButton.y()));
                buttonNeedChange.push_back(QPoint(ii,jj));
                exchange(selectedButton, QPoint(ii, jj));

            } else {

                qDebug() << tr("开始消除");
                touchTimes--;
                gm->combol = 1;
                do {

                    qDebug() << tr("消除第") << gm->combol << tr("次");

                    updateMap();
                    sleep(300);
                    gm->block_fill();
                    updateMap();
                    sleep(300);
                } while(gm->all_check_destroy(gm->combol++));
                gm->combol--;
            }
        } else {
            oneButtonIsSelect = false;
        }


        qDebug() << '\n';
    }
    if(!touchTimes) {
        QMessageBox::information(this, tr("提示"), tr("").sprintf("交换次数用尽，游戏结束！\n\t你的分数是%d", gm->get_score()), QMessageBox::Ok);
        gm->fill_operator();
        gameStopButtonClicked();
    }
}

void MainWindow::on_actionstartt_triggered()
{
    gameStartButtonClicked();
}

void MainWindow::on_pushButton_clicked()
{
    gameStartButtonClicked();
}

void MainWindow::on_pushButton_2_clicked()
{
    gameStopButtonClicked();
}

void MainWindow::on_actionhelpp_triggered()
{
    gameHelpButtonClicked();
}

void MainWindow::on_pushButton_3_clicked()
{
    gameHelpButtonClicked();
}

void MainWindow::on_actionmusicc_triggered()
{
    musicPlayer->play();
}

void MainWindow::on_actiongratMusicc_triggered()
{
    musicPlayer->stop();
}

void MainWindow::on_pushButton_4_clicked()
{
    gameListButtonClicked();
}

void MainWindow::on_actionlistt_triggered()
{
    gameListButtonClicked();
}
