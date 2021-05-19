#ifndef GENERATEHASHFORM_H
#define GENERATEHASHFORM_H

#include <QWidget>

namespace Ui {
class GenerateHashForm;
}

class GenerateHashForm : public QWidget
{
    Q_OBJECT

public:
    explicit GenerateHashForm(QWidget *parent = 0);
    ~GenerateHashForm();

private:
    Ui::GenerateHashForm *ui;
};

#endif // GENERATEHASHFORM_H
