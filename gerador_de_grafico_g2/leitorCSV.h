#ifndef LEITORCSV_H
#define LEITORCSV_H
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <QVector>
#include <QString>
#include <new>

using namespace std;

class leitorCSV
{
    string arqName;
    int numLinhas;
    int numColunas;
    bool arqExistente = false;
    bool contagem = false;
    bool matrizGravada = false;

public:
    leitorCSV(string);
    bool leDimensao(void);
    void leArquivo(string *);
    string getArqName();
    int getNumLinhas();
    int getNumColunas();
};
#endif
