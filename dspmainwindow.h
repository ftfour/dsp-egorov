#ifndef DSPMAINWINDOW_H
#define DSPMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class DSPMainWindow; }
QT_END_NAMESPACE

class DSPMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    DSPMainWindow(QWidget *parent = nullptr);
    ~DSPMainWindow();

private:
    Ui::DSPMainWindow *ui;
};
#endif // DSPMAINWINDOW_H
