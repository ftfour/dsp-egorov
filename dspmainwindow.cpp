#include "dspmainwindow.h"
#include "ui_dspmainwindow.h"
#include "QDebug"
#include "aboutwindow.h"

DSPMainWindow::DSPMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DSPMainWindow)
{
    ui->setupUi(this);
}

DSPMainWindow::~DSPMainWindow()
{
    delete ui;
}


void DSPMainWindow::on_actionAbout_triggered()
{
    qDebug() << "Menu Action About triggered";
    AboutWindow aboutWindow;
    aboutWindow.setModal(true);
    aboutWindow.exec();
    qDebug() << "Open about window";
}
