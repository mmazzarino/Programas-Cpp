#include "gerador_de_graficos.h"
#include "ui_gerador_de_graficos.h"
#include "leitorCSV.h"
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

Gerador_de_graficos::Gerador_de_graficos(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gerador_de_graficos)
{
    ui->setupUi(this);
}

Gerador_de_graficos::~Gerador_de_graficos()
{
    delete ui;
}

void Gerador_de_graficos::on_buttonLerArq_clicked()
{
}

void Gerador_de_graficos::on_buttonLerArq_released()
{
    string arqName = ui->textEditArqName->toPlainText().toUtf8().constData();
    leitorCSV leitor(arqName);

    if(leitor.leDimensao()){
        string matriz[leitor.getNumLinhas()][leitor.getNumColunas()];
        leitor.leArquivo(&matriz[0][0]);

        QVector<double> x(leitor.getNumLinhas());
        QVector<double> y1(leitor.getNumLinhas());
        QVector<double> y2(leitor.getNumLinhas());

        for(int cont2 = 0; cont2 < leitor.getNumLinhas(); cont2++){
            x[cont2] = stod(matriz[cont2][0]);
        }
        for(int cont2 = 0; cont2 < leitor.getNumLinhas(); cont2++){
            y1[cont2] = stod(matriz[cont2][1]);
        }
        for(int cont2 = 0; cont2 < leitor.getNumLinhas(); cont2++){
            y2[cont2] = stod(matriz[cont2][2]);
        }

        ui->grafico->addGraph();
        ui->grafico->graph(0)->setData(x, y1);
        ui->grafico->graph(0)->setPen(QPen(Qt::red));

        ui->grafico->addGraph();
        ui->grafico->graph(1)->setData(x, y2);
        ui->grafico->graph(1)->setPen(QPen(Qt::green));

        ui->grafico->xAxis->setRange(0, 10);
        ui->grafico->yAxis->setRange(-2, 8);
        ui->grafico->replot();
    }

    else{
        cout << "arquivo nao encontrado!" << endl;
    }
}
