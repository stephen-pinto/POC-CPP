#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include <QMessageBox>
#include "codeedit.h"

class LineNumberArea : public QWidget
{
    Q_OBJECT

public:
    LineNumberArea(CodeEdit *parent);

    virtual ~LineNumberArea();

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
        CodeEdit *parentEditor;

public slots:

};

#endif // LINENUMBERAREA_H
