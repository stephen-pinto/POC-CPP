#ifndef MAINEDITOR_H
#define MAINEDITOR_H

#include <QMainWindow>
#include "codeedit.h"

namespace Ui {
class MainEditor;
}

class MainEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainEditor(QWidget *parent = 0);
    ~MainEditor();

private slots:
    void on_actionClose_triggered();

    void on_actionOpen_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionSelect_All_triggered();

    void on_actionFind_and_replace_triggered();

private:
    Ui::MainEditor *ui;
    QPlainTextEdit *m_CodeEdit;
};

#endif // MAINEDITOR_H
