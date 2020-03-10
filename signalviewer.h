#ifndef SIGNALVIEWER_H
#define SIGNALVIEWER_H

#include <QWidget>
#include <QTextEdit>
#include <QAction>
#include <QFileDialog>
#include <QCloseEvent>
#include <QMessageBox>
#include <QApplication>

class signalViewer : public QTextEdit
{
    Q_OBJECT
public:
    signalViewer(QWidget *parent = 0);
//    QSize sizeHint() const;
    QAction *windowMenuAction() const {return action; }

    static signalViewer *open(QWidget *parent = 0);
    static signalViewer *openFile(const QString &fileName,
                                  QWidget *parent = 0);
    static signalViewer *openExamples(QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void documentWasModified();

private:
    bool okToContinue();
    void setCurrentFile(const QString &fileName);
    bool readFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    bool isUntitled;
    QString curFile;
    QAction *action;
};

#endif // SIGNALVIEWER_H
