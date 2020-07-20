#include "piloto.h"

piloto::piloto(void) // Inicializa o piloto zerado
{
    for(int k = 0; k < 25; colocacao_corrida[k++]=-1);
    for(int k = 0; k < 30; contador_colocacoes[k++]=0);
    pontuacao = n_vitorias = n_podios = n_dnf = 0;
}

void piloto::imprimePiloto(void)
{
    cout.width(22);
    cout.unsetf(ios::adjustfield);
    cout.setf(ios::left);
    cout << nome;
    cout.unsetf(ios::adjustfield);
    cout.setf(ios::right);
    for(int k = 0; k < n_corridas; k++)
    {
        cout.width(4);
        if( colocacao_corrida[k] == -1 ) cout << "DNF";
        else cout << colocacao_corrida[k];
    }
    cout << endl;
}

void piloto::setPiloto(string n, string e, int num)
{
    nome = n; equipe = e; n_corridas = num;
}

void piloto::setColocacao(int corrida, int colocacao)
{
    colocacao_corrida[corrida] = colocacao;
}

void piloto::calcula(int *pt_por_col)
{
    for(int k = 0; k < n_corridas; k++)
    {
        if( colocacao_corrida[k] == -1 ) n_dnf++;
        else
        {
            if( colocacao_corrida[k] <= 10 )
            {
                pontuacao += pt_por_col[ colocacao_corrida[k]-1 ];
                contador_colocacoes[colocacao_corrida[k]-1]++;
            }
        }
    }
    n_vitorias = contador_colocacoes[0];
    for(int k = 0; k < 3; k++) n_podios += contador_colocacoes[k];
}

string piloto::getNome(void)
{
    return nome;
}

string piloto::getEquipe(void)
{
    return equipe;
}

int piloto::getPontuacao(void)
{
    return pontuacao;
}

int piloto::getColocacao(int indice)
{
    if(indice >= n_corridas) return -1;
    return colocacao_corrida[indice];
}

int piloto::getContColocacao(int indice)
{
    if(indice >= 30) return -1;
    if(indice <= 0) return -1;
    return contador_colocacoes[indice-1];
}

void piloto::getEstatisticas(int &pt, int &nv, int &np, int &nd)
{
    pt = pontuacao; nv = n_vitorias; np = n_podios; nd = n_dnf;
}
