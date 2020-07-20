#include "gerador_de_graficos.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gerador_de_graficos w;
    w.show();
    return a.exec();
}
