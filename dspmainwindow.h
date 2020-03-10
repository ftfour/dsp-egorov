#ifndef DSPMAINWINDOW_H
#define DSPMAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QLabel>
#include <QActionGroup>
#include "signalviewer.h"

class QMenu;

class DSPMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    DSPMainWindow();

public slots:
    void openFile(const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void open();
    void updateActions();
    void loadFiles();
//    void about();

private:
    void createActions();
    void createMenus();
    void createStatusBar();
    void addSignal(signalViewer *viewer);
    signalViewer *activeViewer();
    QMdiArea *mdiArea;
    QLabel *readyLabel;
//    QWidgetList windows;

    QMenu *fileMenu;
//    QMenu *windowMenu;
//    QMenu *helpMenu;
    QActionGroup *windowActionGroup;
    QAction *openAction;

};
#endif // DSPMAINWINDOW_H
