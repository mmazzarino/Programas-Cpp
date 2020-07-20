#include "leitorCSV.h"
using namespace std;

leitorCSV::leitorCSV(string arqName){
    this->arqName = arqName;
    this->numLinhas = -1;
    this->numColunas = 0;
}

bool leitorCSV::leDimensao(void){
    fstream arq(arqName + ".csv", ios::in);
    string str = "";

    if((arq.is_open()) && (!contagem)){
        while(!arq.eof()){
            if(numLinhas == -1){
                getline(arq, str);
                numColunas = (count(str.begin(), str.end(), ';') + 1);
                numLinhas ++;
            }
            else{
                getline(arq, str);
                numLinhas ++;
            }
        }
        contagem = true;
        arqExistente = true;
        arq.close();
    }
    return (arqExistente && contagem);
}

void leitorCSV::leArquivo(string * matriz){
    string str = "";
    if(contagem && arqExistente && !matrizGravada){//popula matriz
        fstream arq(arqName + ".csv", ios::in);

        if((arq.is_open()) && (!matrizGravada)){
            while((!arq.eof()) && (!matrizGravada)){
                int aux3 = 0;
                for(int cont1 = 0; cont1 < numLinhas; ){
                    getline(arq, str);
                    for(int cont2 = 0; cont2 < numColunas; ){
                        if(cont2 != (numColunas - 1)){
                            matriz[aux3] = str.substr(0, str.find(";"));
                            aux3++;
                            str = str.substr(str.find(";")+1, (str.size() - str.find(";")));
                        }
                        else{
                            matriz[aux3] = str.substr(0, str.size());
                            aux3++;
                        }
                        cont2++;
                    }
                    cont1++;
                }
                matrizGravada = true;
                arq.close();
            }     
        }
    }
}

string leitorCSV::getArqName(){
    return arqName;
}

int leitorCSV::getNumLinhas(){
    return numLinhas;
}

int leitorCSV::getNumColunas(){
    return numColunas;
}
