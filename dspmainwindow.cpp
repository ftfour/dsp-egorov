#include "dspmainwindow.h"
#include "ui_dspmainwindow.h"

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

