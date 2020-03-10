#include <QtGui>
#include "signalviewer.h"

signalViewer::signalViewer(QWidget *parent) : QTextEdit(parent)
{
     action = new QAction(this);
     action->setCheckable(true);
     connect(action, SIGNAL(triggered()), this, SLOT(show()));
     connect(action, SIGNAL(triggered()), this, SLOT(setFocus()));

     isUntitled = true;

     connect(document(), SIGNAL(contentsChanged()),
             this, SLOT(documentWasModified()));

     setWindowTitle("[*]");
     setAttribute(Qt::WA_DeleteOnClose);
}

signalViewer *signalViewer::open(QWidget *parent)
{
    QString fileName =
            QFileDialog::getOpenFileName(parent, tr("Open"), ".");
    if (fileName.isEmpty())
        return 0;

    return openFile(fileName, parent);
}

signalViewer *signalViewer::openFile(const QString &fileName, QWidget *parent)
{
    signalViewer *viewer = new signalViewer(parent);
    if (viewer->readFile(fileName)){
        viewer->setCurrentFile(fileName);
        return viewer;
    } else {
        delete viewer;
        return 0;
    }
}

signalViewer *signalViewer::openExamples(QWidget *parent)
{
   QString fileName = ":/examples.txt";
   return openFile(fileName, parent);
}

void signalViewer::closeEvent(QCloseEvent *event)
{
    if (okToContinue()){
        event->accept();
    } else {
        event->ignore();
    }
}

void signalViewer::documentWasModified()
{
    setWindowModified(true);
}

bool signalViewer::okToContinue()
{
    if (document()->isModified()){
        int r = QMessageBox::warning(this, tr("DSP"),
                                     tr("File %1 has been modified.\n"
                                        "Do you want to save your changes?")
                                     .arg(strippedName(curFile)),
                                     QMessageBox::Yes | QMessageBox::No
                                     | QMessageBox::Cancel);
        if (r == QMessageBox::Yes){
            return true;
        } else if (r == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

void signalViewer::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    isUntitled = false;
    action->setText(strippedName(curFile));
    document()->setModified(false);
    setWindowTitle(strippedName(curFile) + "[*]");
    setWindowModified(false);
}

bool signalViewer::readFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, tr("DSP Editor"),
                             tr("Cannot read file %1:\n%2")
                             .arg(file.fileName())
                             .arg(file.errorString())
                             );
        return false;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();
    return true;
}
QString signalViewer::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

