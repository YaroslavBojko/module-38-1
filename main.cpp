#include "mainwindow.h"

#include <QApplication>

#include <iostream>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>


ImageButton::ImageButton(QWidget *parent)
{
    setParent(parent);
    setToolTip("Стоп");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mButtonUpPixmap = QPixmap(":/off.png");
    mButtonDownPixmap = QPixmap(":/on.jpg");
    buttonSound = QUrl("qrc:///click.mp3");
    mCurrentButtonPixmap = mButtonUpPixmap;
    setGeometry(mCurrentButtonPixmap.rect());
    player = new QMediaPlayer();
    player->setVolume(75);
    player->setMedia(buttonSound);
    connect(this, &QPushButton::clicked, this, &ImageButton::setDown);
}

void ImageButton::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentButtonPixmap);
}

QSize ImageButton::sizeHint() const
{
    return QSize(100, 100);
}

QSize ImageButton::minimumSizeHint() const
{
    return sizeHint();
}

void ImageButton::keyPressEvent(QKeyEvent *e)
{
    setDown();
}

void ImageButton::setDown()
{
    player->stop();
    player->play();
    mCurrentButtonPixmap = mButtonDownPixmap;
    update();
    QTimer::singleShot(500, this, &ImageButton::setUp);
}

void ImageButton::setUp()
{
    mCurrentButtonPixmap = mButtonUpPixmap;
    update();
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    ImageButton redButton(nullptr);
    redButton.setFixedSize(200, 200);
    redButton.move(1000, 400);
    redButton.show();

    return app.exec();
}
