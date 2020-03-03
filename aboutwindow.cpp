#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include "QDebug"
#include <QFile>
#include <QTextStream>

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    loadTextFile();
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::on_backButton_clicked()
{
    QDialog::reject();
    qDebug() << "About window rejected";
}

void AboutWindow::loadTextFile()
{
    QFile inputFile(":/about.txt");
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString line = in.readAll();
    inputFile.close();

    ui->textEdit->setText(line);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
}
