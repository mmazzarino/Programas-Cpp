#ifndef PILOTO_H
#define PILOTO_H

#include <iostream>
#include <string>

using namespace std;

class piloto
{
        string nome;
        string equipe;
        int colocacao_corrida[25];  // Colocação do piloto na n-ésima corrida
        int n_corridas;             // Número de corridas na temporada
        int pontuacao;              // Pontuação na Temporada
        int n_vitorias;             // Vitórias na Temporada
        int n_podios;               // Número de Pódios
        int contador_colocacoes[30];// Controle de colocação
        int n_dnf;                  // Did Not Finish (número de provas não terminadas)
    public:
        piloto(void);
        void imprimePiloto(void);
        void setPiloto(string, string, int);
        void setColocacao(int, int);
        void calcula(int *);
        string getNome(void);
        string getEquipe(void);
        int getPontuacao(void);
        int getColocacao(int);
        int getContColocacao(int);
        void getEstatisticas(int &,int &,int &,int &);
};


#endif // PILOTO_H
