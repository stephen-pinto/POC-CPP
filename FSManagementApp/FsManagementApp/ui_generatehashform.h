/********************************************************************************
** Form generated from reading UI file 'generatehashform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEHASHFORM_H
#define UI_GENERATEHASHFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GenerateHashForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *GenerateHashForm)
    {
        if (GenerateHashForm->objectName().isEmpty())
            GenerateHashForm->setObjectName(QStringLiteral("GenerateHashForm"));
        GenerateHashForm->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(GenerateHashForm);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(GenerateHashForm);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(GenerateHashForm);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        plainTextEdit = new QPlainTextEdit(GenerateHashForm);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        verticalLayout->addWidget(plainTextEdit);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(GenerateHashForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(GenerateHashForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(GenerateHashForm);

        QMetaObject::connectSlotsByName(GenerateHashForm);
    } // setupUi

    void retranslateUi(QWidget *GenerateHashForm)
    {
        GenerateHashForm->setWindowTitle(QApplication::translate("GenerateHashForm", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("GenerateHashForm", "Root directory: ", Q_NULLPTR));
        pushButton->setText(QApplication::translate("GenerateHashForm", "Hash it", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("GenerateHashForm", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GenerateHashForm: public Ui_GenerateHashForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEHASHFORM_H
