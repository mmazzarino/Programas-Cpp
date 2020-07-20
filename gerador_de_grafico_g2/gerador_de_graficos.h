#ifndef GERADOR_DE_GRAFICOS_H
#define GERADOR_DE_GRAFICOS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Gerador_de_graficos; }
QT_END_NAMESPACE

class Gerador_de_graficos : public QMainWindow
{
    Q_OBJECT

public:
    Gerador_de_graficos(QWidget *parent = nullptr);
    ~Gerador_de_graficos();

private slots:
    void on_buttonLerArq_clicked();

    void on_buttonLerArq_released();

    void on_buttonGeraGraf_released();

private:
    Ui::Gerador_de_graficos *ui;
};
#endif // GERADOR_DE_GRAFICOS_H
