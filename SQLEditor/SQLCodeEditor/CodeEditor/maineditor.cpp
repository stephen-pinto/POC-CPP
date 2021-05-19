#include "maineditor.h"
#include "ui_maineditor.h"
#include "linenumberarea.h"
#include <QFileDialog>

MainEditor::MainEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainEditor)
{
    ui->setupUi(this);

    m_CodeEdit = new CodeEdit(this);
    ui->verticalLayout->addWidget(m_CodeEdit);

    setCentralWidget(m_CodeEdit);
}

MainEditor::~MainEditor()
{
    delete ui;
}

void MainEditor::on_actionOpen_triggered()
{
    //Ask for file
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open code file"),
                                                    "C:/Users/Stephen/Desktop",
                                                    tr("C Source Files (*.c *.cpp *.h)"));
    //Load the provided file
    QFile file(fileName);
    if (file.open(QFile::ReadOnly | QFile::Text))
        m_CodeEdit->setPlainText(file.readAll());
}

void MainEditor::on_actionClose_triggered()
{
    close();
}

void MainEditor::on_actionUndo_triggered()
{
    m_CodeEdit->undo();
}

void MainEditor::on_actionRedo_triggered()
{
    m_CodeEdit->redo();
}

void MainEditor::on_actionCut_triggered()
{
    m_CodeEdit->cut();
}

void MainEditor::on_actionCopy_triggered()
{
    m_CodeEdit->copy();
}

void MainEditor::on_actionPaste_triggered()
{
    m_CodeEdit->paste();
}

void MainEditor::on_actionSelect_All_triggered()
{
    m_CodeEdit->selectAll();
}

void MainEditor::on_actionFind_and_replace_triggered()
{

}
