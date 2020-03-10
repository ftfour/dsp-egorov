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

void DSPMainWindow::openExamples()
{
    signalViewer *viewer = signalViewer::openExamples();
    if (viewer)
        addSignal(viewer);
}

void DSPMainWindow::updateActions()
{
    bool hasViewer = (activeViewer() != 0);
    saveAction->setEnabled(hasViewer);
    saveAsAction->setEnabled(hasViewer);
    closeAction->setEnabled(hasViewer);
    closeAllAction->setEnabled(hasViewer);
    tileAction->setEnabled(hasViewer);
    cascadeAction->setEnabled(hasViewer);
    nextAction->setEnabled(hasViewer);
    prevAction->setEnabled(hasViewer);
    separatorAction->setVisible(hasViewer);

    if (activeViewer())
        activeViewer()->windowMenuAction()->setChecked(true);
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

void DSPMainWindow::about()
{
    QMessageBox::about(this, tr("About DSP"),
                       tr("<h2>DSP 0.2.1</h2>"
                          "<p>Copyright &copy; 2020 Ersan Egorov"
                          "<p>DSP is a small application for visualization "
                          "multichannel signals"));
}

void DSPMainWindow::createActions()
{
    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an exisiting file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    openExamplesAction = new QAction(tr("&Open examples"), this);
    openExamplesAction->setShortcut(tr("Ctrl+E"));
    openExamplesAction->setStatusTip(tr("Open examples"));
    connect(openExamplesAction, SIGNAL(triggered()), this, SLOT(openExamples()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setEnabled(false);
    saveAction->setStatusTip(tr("Save the file to disk"));
//    TO - DO
//    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(tr("&Save As"), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setEnabled(false);
    saveAsAction->setStatusTip(tr("Save the file to disk under a new name"));
//    TO - DO
//    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    // Menu - Window Actions
    closeAction = new QAction(tr("&Close"), this);
    closeAction->setEnabled(false);
    closeAction->setShortcut(tr("Ctrl+X"));
    closeAction->setStatusTip(tr("Close active window"));
    connect(closeAction, SIGNAL(triggered()),
            mdiArea, SLOT(closeActiveSubWindow()));
    closeAllAction = new QAction(tr("&Close All"), this);
    closeAllAction->setEnabled(false);
    closeAllAction->setStatusTip(tr("Close all window"));
    connect(closeAllAction, SIGNAL(triggered()),
            mdiArea, SLOT(closeAllSubWindows()));
    tileAction = new QAction(tr("&Tile"), this);
    tileAction->setEnabled(false);
    tileAction->setShortcut(tr("Ctrl+T"));
    tileAction->setStatusTip(tr("Set tiling windows layout"));
    connect(tileAction, SIGNAL(triggered()),
            mdiArea, SLOT(tileSubWindows()));
    cascadeAction = new QAction(tr("&Cascade"), this);
    cascadeAction->setEnabled(false);
    cascadeAction->setShortcut(tr("Ctrl+Y"));
    cascadeAction->setStatusTip(tr("Set cascade windows layout"));
    connect(cascadeAction, SIGNAL(triggered()),
            mdiArea, SLOT(cascadeSubWindows()));
    nextAction = new QAction(tr("&Next"), this);
    nextAction->setShortcut(tr("Ctrl+Tab"));
    nextAction->setEnabled(false);
    nextAction->setStatusTip(tr("Select next window"));
    connect(nextAction, SIGNAL(triggered()),
            mdiArea, SLOT(activateNextSubWindow()));
    prevAction = new QAction(tr("&Prev"), this);
    prevAction->setEnabled(false);
    prevAction->setShortcut(tr("Ctrl+Shift+Tab"));
    closeAction->setStatusTip(tr("Select previous window"));
    connect(prevAction, SIGNAL(triggered()),
            mdiArea, SLOT(activatePreviousSubWindow()));

    // Menu - Help Actions
    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    // Windows Group & Separator
    separatorAction = new QAction(this);
    separatorAction->setSeparator(true);
    windowActionGroup = new QActionGroup(this);
}

void DSPMainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(openExamplesAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    windowMenu = menuBar()->addMenu(tr("&Window"));
    windowMenu->addAction(closeAction);
    windowMenu->addAction(closeAllAction);
    windowMenu->addSeparator();
    windowMenu->addAction(tileAction);
    windowMenu->addAction(cascadeAction);
    windowMenu->addSeparator();
    windowMenu->addAction(nextAction);
    windowMenu->addAction(prevAction);
    windowMenu->addAction(separatorAction);


    menuBar()->addSeparator();
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void DSPMainWindow::createStatusBar()
{
    readyLabel = new QLabel(tr(" Ready"));
    statusBar()->addWidget(readyLabel, 1);
}

void DSPMainWindow::addSignal(signalViewer *viewer)
{
    QMdiSubWindow *subWindow = mdiArea->addSubWindow(viewer);
    windowMenu->addAction(viewer->windowMenuAction());
    windowActionGroup->addAction(viewer->windowMenuAction());
    subWindow->show();
}

signalViewer *DSPMainWindow::activeViewer()
{
    QMdiSubWindow *subWindow = mdiArea->activeSubWindow();
    if (subWindow)
        return qobject_cast<signalViewer *>(subWindow->widget());
    return 0;
}


