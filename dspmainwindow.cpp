#include <QtGui>

#include "dspmainwindow.h"
#include "QDebug"
#include "signalviewer.h"
DSPMainWindow::DSPMainWindow()
{
    mdiArea = new QMdiArea();
    setCentralWidget(mdiArea);
    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
            this, SLOT(updateActions()));

    createActions();
    createMenus();
    createStatusBar();

    setWindowTitle("DSP - Egorov");
    QTimer::singleShot(0, this, SLOT(loadFiles()));
}

void DSPMainWindow::openFile(const QString &fileName)
{
    signalViewer *viewer = signalViewer::openFile(fileName, this);
    if (viewer)
        addSignal(viewer);
}

void DSPMainWindow::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows();
    if (!mdiArea->subWindowList().isEmpty()){
        event->ignore();
    } else {
        event->accept();
    }
}

void DSPMainWindow::open()
{
    signalViewer *viewer = signalViewer::open(this);
    if (viewer)
        addSignal(viewer);
}

void DSPMainWindow::updateActions()
{
    // TO - DO
}

void DSPMainWindow::loadFiles()
{
    QStringList args = QApplication::arguments();
    args.removeFirst();
    if (!args.isEmpty()){
        foreach (QString arg, args) {
            openFile(arg);
        }
        mdiArea->cascadeSubWindows();
    }
    mdiArea->activateNextSubWindow();
}

void DSPMainWindow::createActions()
{
    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an exisiting file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    windowActionGroup = new QActionGroup(this);
}

void DSPMainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();

    menuBar()->addSeparator();
}

void DSPMainWindow::createStatusBar()
{
    readyLabel = new QLabel(tr(" Ready"));
    statusBar()->addWidget(readyLabel, 1);
}

void DSPMainWindow::addSignal(signalViewer *viewer)
{
    QMdiSubWindow *subWindow = mdiArea->addSubWindow(viewer);
    subWindow->show();
}

signalViewer *DSPMainWindow::activeViewer()
{
    QMdiSubWindow *subWindow = mdiArea->activeSubWindow();
    if (subWindow)
        return qobject_cast<signalViewer *>(subWindow->widget());
    return 0;
}


