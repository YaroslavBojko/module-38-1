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
    mButtonUpPixmap = QPixmap("/opt/off.png");
    mButtonDownPixmap = QPixmap("/opt/on.jpg");
    mCurrentButtonPixmap = mButtonUpPixmap;
    setGeometry(mCurrentButtonPixmap.rect());
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
    QObject::connect(&redButton, &QPushButton::clicked, [](){std::cout << "clicked\n";});
    redButton.show();

    return app.exec();
}
