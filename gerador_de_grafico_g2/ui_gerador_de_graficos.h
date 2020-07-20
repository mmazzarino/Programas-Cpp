/********************************************************************************
** Form generated from reading UI file 'gerador_de_graficos.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GERADOR_DE_GRAFICOS_H
#define UI_GERADOR_DE_GRAFICOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Gerador_de_graficos
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QTextEdit *textEditArqName;
    QPushButton *buttonLerArq;
    QCustomPlot *grafico;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Gerador_de_graficos)
    {
        if (Gerador_de_graficos->objectName().isEmpty())
            Gerador_de_graficos->setObjectName(QStringLiteral("Gerador_de_graficos"));
        Gerador_de_graficos->resize(537, 470);
        centralwidget = new QWidget(Gerador_de_graficos);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(180, 30, 181, 16));
        textEditArqName = new QTextEdit(centralwidget);
        textEditArqName->setObjectName(QStringLiteral("textEditArqName"));
        textEditArqName->setGeometry(QRect(173, 50, 191, 31));
        buttonLerArq = new QPushButton(centralwidget);
        buttonLerArq->setObjectName(QStringLiteral("buttonLerArq"));
        buttonLerArq->setGeometry(QRect(170, 90, 191, 28));
        grafico = new QCustomPlot(centralwidget);
        grafico->setObjectName(QStringLiteral("grafico"));
        grafico->setGeometry(QRect(29, 139, 481, 261));
        Gerador_de_graficos->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Gerador_de_graficos);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 537, 26));
        Gerador_de_graficos->setMenuBar(menubar);
        statusbar = new QStatusBar(Gerador_de_graficos);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Gerador_de_graficos->setStatusBar(statusbar);

        retranslateUi(Gerador_de_graficos);

        QMetaObject::connectSlotsByName(Gerador_de_graficos);
    } // setupUi

    void retranslateUi(QMainWindow *Gerador_de_graficos)
    {
        Gerador_de_graficos->setWindowTitle(QApplication::translate("Gerador_de_graficos", "Gerador_de_graficos", Q_NULLPTR));
        label->setText(QApplication::translate("Gerador_de_graficos", "Digite o nome do arquivo CSV", Q_NULLPTR));
        buttonLerArq->setText(QApplication::translate("Gerador_de_graficos", "Gerar Gr\303\241fico", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Gerador_de_graficos: public Ui_Gerador_de_graficos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GERADOR_DE_GRAFICOS_H
