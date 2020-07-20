#include "piloto.h"
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <algorithm>

using namespace std;

class temporada
{
    piloto grid[30];
    int n_corridas;
    int n_pilotos;
    int ano;
    bool situacaoArq;//alteracao

public:
    temporada(void);
    temporada(string);
    bool leArquivo(string);
    void setGrid(string, int);
    int  buscarPiloto(string);
    void imprimeEstatisticas(int, int);
    void orderBy(string);
    void imprimeTemporada(void);
    void imprimeVitoriosos(void);
    bool salvaArquivo(string);
    void setAno(string);
    int  getAno();
    int  getNumCorridas();
    int  getNumPilotos();
    bool getsituacaoArq();//alteracao
};

temporada::temporada(){
}

temporada::temporada(string arqName){//construtor parametrizado apenas repassa o nome do arquivo para o metodo "leArquivo"
    situacaoArq = leArquivo(arqName);//alteracao
}

bool temporada::leArquivo(string arqName){
    string str = "";   
    int numLinha = 1;
    int numPiloto = 0;
    bool ultimoPiloto = false;

    fstream arq(arqName + ".csv", ios::in);

    if(arq.is_open()){
        cout << "Arquivo sendo lido..." << endl;

        while(!arq.eof()){//enquanto o arquivo não chegou ao fim

            if(numLinha == 1){
                getline(arq, str);//na primeira linha do arquivo
                setAno((string) str.substr(str.find(';')+1, 4));//pega o ano da temporada e seta no atributo "ano"
            }
            else if(numLinha == 2){//na segunda linha
                getline(arq, str);//nao faz nada
            }
            else if(numLinha >= 3){//nas demais linhas
                getline(arq, str);//pega a linha

                if(str.substr(0, str.find(";")).compare("#FINAL") == 0){//verifica se é a ultima linha
                    ultimoPiloto = true;
                    break;//se for, nao faz nada
                }
                else if(numLinha == 3){//se esta na terceira linha do arquivo
                    n_corridas = count(str.begin(), str.end(), ';') - 1;//conta o numero de ";", desconta 1 referente ao ";" da equipe e seta o numero de corridas
                    setGrid((string)str, numPiloto);//manda a linha 3 para ser tratada pelo metodo "setGrid" e gravada no atributo "grid[]"
                    numPiloto++;//incrementa o "numPiloto"
                }
                else{//se esta entre a terceira e a ultima
                    setGrid((string)str, numPiloto);//manda cada linha para ser tratada pelo metodo "setGrid" e gravada no atributo "grid[]"
                    numPiloto++;//incrementa o "numPiloto"
                }
            }
            numLinha ++;
        }

    if(ultimoPiloto == true){//se ja foram todos pilotos
        n_pilotos = (numPiloto);//seta o atributo "n_pilotos"
        arq.close();//e fecha o arquivo
        return true;//alteracao
        }

    }else{
        cout << "Problemas!!!" << endl;
        cout << "Verifique se arquivo existe na pasta." << endl;
        return false;//alteracao
    }
}

void temporada::setGrid(string linhaArq, int numPetolo){
    string nombre, equipa, auxColocacao;
    int vet[10] = {10,8,6,5,4,3,2,1,0,0};//vetor auxiliar contendo a pontuacao das 10 primeiras colocacoes na temporada de 2008
    int corrida = 0;

    nombre = linhaArq.substr(0, linhaArq.find(";"));//em cada linha recebida pelo metodo "leArquivo", pega a parte da string que vai do inicio dela ate o primeiro ";" e salva em "nombre"

    linhaArq = linhaArq.substr((linhaArq.find(";") + 1), (linhaArq.size() - linhaArq.find(";")));//remove da "linhaArq" a parte referente ao nome, ficando o nome da equipe no inicio da string
    equipa = linhaArq.substr(0, linhaArq.find(";"));//pega a parte da linhaArq que vai do inicio até o primeiro ";" e seta a "equipa"

    grid[numPetolo].setPiloto(nombre, equipa, getNumCorridas());//seta o nome do piloto, equipe e o numero de corridas da temporada atraves do metodo "setPiloto" da classe piloto

    while (corrida < getNumCorridas()){//enquanto "corrida" for menor que o numero total de corridas
        if(count(linhaArq.begin(), linhaArq.end(), ';') > 0){ //verifica se o numero de ';' na string linhaArq eh > 0
            linhaArq = linhaArq.substr(linhaArq.find(";")+1, (linhaArq.size() - linhaArq.find(";")));//na primeira passada do while remove o nome da equipe da string linhaArq e depois, a cada passada, remove a posicao que ja foi adicionada ao array de objetos
            if(count(linhaArq.begin(), linhaArq.end(), ';') > 0){//verifica se, após a remocao da parte da string, o restante dela continua tendo ";"
                auxColocacao = linhaArq.substr(0, linhaArq.find(";"));//se a string "linhaArq" tem ";", pega do inicio da string até o ";" e armazena a posicao em "auxColocacao"
            }else{
                auxColocacao = linhaArq.substr(0, linhaArq.size());//na ultima colocacao nao existe mais ';', entao a "auxColocacao" recebe todo restante da string petolo
            }
        }

        if((auxColocacao == "Ret") || (auxColocacao == "Dsq")){//se "auxColocacao" for Ret ou Dsq
            grid[numPetolo].setColocacao(corrida, (int)-1);//seta a colocacao do piloto, na respectiva corrida, com valor -1
        }
        else{//se nao for Ret nem Dsq
            grid[numPetolo].setColocacao(corrida, stoi(auxColocacao));//converte "auxColocacao" de string para int e seta a colocacao do piloto, na respectiva corrida
        }
        corrida++;
    }
    grid[numPetolo].calcula(vet);//executa o metodo calcula da classe piloto
   // grid[numPetolo].imprimePiloto();// cout << "teste rrr" << numPetolo << endl;
    return;
}

int  temporada::buscarPiloto(string nomePetolo){//recebe o nome de um piloto como parametro e, se encontrado na temporada, retorna o numero do indice em que o piloto se encontra no array "grid[]"
    bool encontrado = false;
    bool percorreuTudo = false;
    int indicePetolo = 40;

    string a = "";
    while((encontrado == false) && (percorreuTudo == false)){
        for(int aux = 0; aux < n_pilotos; aux++){//até passar por todos pilotos do "grid[]"
            a = grid[aux].getNome();//pega o nome de cada piloto
            if((a.compare(nomePetolo)) == 0){//se o nome do piloto for igual ao parametro passado "nomePetolo"
                indicePetolo = aux;//atribui o valor de "aux" ao "indicePetolo"
                encontrado = true;//atribui true ao "encontrado", para sair do while
            }else if(aux == (n_pilotos - 1)){//se nao saiu do while e chegou ao ultimo piloto
                percorreuTudo = true;//atribui true ao "percorreuTudo, para sair do while
            }
        }
    }
    return indicePetolo;//retorna o indice
}

void temporada::imprimeEstatisticas(int indicePetolo, int numCorridas){//recebe o numero do indice do piloto que foi retornado pelo metodo "buscarPiloto", e recebe o numero de corridas, retornado pelo metodo "getNumCorridas".

    int pontos, vitorias, podios, DNFs;
    grid[indicePetolo].getEstatisticas(pontos, vitorias, podios, DNFs);//utiliza o metodo "getEstatisticas" da classe piloto

    cout << "Estatisticas piloto :" << grid[indicePetolo].getNome() << endl << endl;

    cout << "Porcent. vitorias: " << (((float)vitorias/(float)numCorridas)*100) << endl;
    cout << "Provas concluidas: " << (n_corridas - DNFs) << endl;
    cout << "Porcent. podios: " << (((float)podios/(float)numCorridas)*100) << endl;
    cout << "Pontuacao final: " << pontos << endl << endl;

    system("pause");
    system("cls");
}

void temporada::orderBy(string order){//recebe como parametro uma string com o nome do atributo que deve ser ordenado e utiliza o algoritmo "bubble sort" para posicionar cada objeto da classe piloto em seu devido lugar dentro do "grid[]"

    bool swapped;
    if(order.compare("pontuacao") == 0){ //ordenar por pontuacao
        for(int cont = 0; cont < (getNumPilotos()); cont++){
            swapped = false;
            for(int cont2 = 0; cont2 < (getNumPilotos() - cont - 1); cont2++){
                if(grid[cont2].getPontuacao() < grid[cont2 + 1].getPontuacao()){
                    swap(grid[cont2], grid[cont2 + 1]);
                    swapped = true;
                }
            }
            if (swapped == false){
                break;
            }
        }
    }else
         if(order.compare("vitorias") == 0){//ordenar por numero de vitorias
            for(int cont = 0; cont < (getNumPilotos()); cont++){
                swapped = false;
                for(int cont2 = 0; cont2 < (getNumPilotos() - cont - 1); cont2++){
                    if(grid[cont2].getContColocacao(1) < grid[cont2 + 1].getContColocacao(1)){
                        swap(grid[cont2], grid[cont2 + 1]);
                        swapped = true;
                    }
                }
                if (swapped == false){
                    break;
                }
            }
        }
}

void temporada::imprimeTemporada(){

    orderBy("pontuacao");//chama o metodo de ordenamento e informa que quer que seja ordenado por "pontuacao"

    cout << "Temporada " << getAno() << " de Formula 1" << endl << endl;

    for(int cont = 0; cont < getNumPilotos(); cont++){
        cout << grid[cont].getNome() << " - " << grid[cont].getPontuacao() << endl;
    }  
    cout << endl;
    system("pause");
    system("cls");
}

void temporada::imprimeVitoriosos(){

    orderBy("vitorias");//chama o metodo de ordenamento e informa que quer que seja ordenado por "vitorias"

    cout << "Vitoriosos de " << getAno() << " da Formula 1" << endl << endl;
    for(int cont = 0; cont < getNumPilotos(); cont++){
        cout << grid[cont].getNome() << " - " << grid[cont].getContColocacao(1) << endl;
    }
    cout << endl;
    system("pause");
    system("cls");
}

bool temporada::salvaArquivo(string nomeArquivo){//recebe o nome do arquivo como parametro, monta a string "conteudo" fazendo diversas concatenacoes, separando as celulas por ";" e as linhas por "\n". Ao final, atribui a string ao arquivo csv
     fstream arq;
     string conteudo;

     arq.open(nomeArquivo + ".csv" , ios::out );
     if(arq.is_open())
     {
         conteudo  = "Classificacao final temporada de: " + to_string(getAno()) + " da F1 \n\n"; // \n quebra a linha
         conteudo += "#INICIO;\n";
         orderBy("pontuacao"); //chama o metodo "orderBy" com parametro "pontuacao" para ordenar por pontuacao

         for(int cont = 0; cont < getNumPilotos(); cont++){//ate percorrer todos pilotos
             conteudo += grid[cont].getNome() + ";" + grid[cont].getEquipe() + ";"; //adiciona o nome do piloto e a equipe na string "conteudo"

             for(int cont2 = 0; cont2 <= getNumCorridas(); cont2++){//apos isso, ate percorrer todas corridas do piloto

                 if(cont2 == getNumCorridas()){ //se ja adicionou todas pontuacoes do piloto, adiciona a pontuacao total dele e quebra linha
                     conteudo += to_string(grid[cont].getPontuacao()) + ";\n";
                 }
                 else if(grid[cont].getColocacao(cont2) > 0){//se a pontuacao eh diferente de -1, apenas converte pra string e adiciona a pontuacao
                     conteudo += to_string(grid[cont].getColocacao(cont2)) + ";";
                 }
                 else if(grid[cont].getColocacao(cont2) < 0){//se a pontuacao eh = -1, adiciona 'Ret||Dsq'
                     conteudo += "Ret||Dsq;";
                 }
             }
         }
         conteudo += "#FINAL;\n";

         arq << conteudo;//adiciona a string conteudo ao arquivo criado

         arq.close();//fecha o arquivo
         return true;
     }
     else
     {
         cout << "PROBLEMAS!" << endl;
         cout << "Verifique nome do arquivo." << endl;
         return false;
     }
     system("pause");
     system("cls");
}

void temporada::setAno(string parAno){
    ano = stoi(parAno);
}

int temporada::getAno(){
    return ano;
}

int temporada::getNumCorridas(){
   return n_corridas;
}

int temporada::getNumPilotos(){
   return n_pilotos;
}

bool temporada::getsituacaoArq(){//alteracao
    return situacaoArq;
}

int main()
{    
    string arqName = "";
    string nomePiloto = "";
    int escolha;
    bool sair = false;


    cout << "Digite o nome do arquivo da temporada:" << endl;
    getline(cin, arqName);

    temporada temp(arqName);//passa o nome do arquivo para o construtor parametrizado

    if(temp.getsituacaoArq()){//alteracao -> só executa o while se situacaoArq = true
        while(sair == false){
            cout << "       Menu" << endl;
            cout << "Escolha a opcao:" << endl;
            cout << "1 - Imprimir estatisticas" << endl;
            cout << "2 - Imprimir temporada" << endl;
            cout << "3 - Imprimir vitoriosos" << endl;
            cout << "4 - Salvar arquivo" << endl;
            cout << "5 - Sair" << endl;

            cin >> escolha;

            switch(escolha){
                case 1:
                    cin.clear(); cin.sync(); //limpa o buffer de entrada deixado pelo "cin"
                    system("cls");//limpa cmd

                    cout << "Digite o nome do piloto: " << endl;
                    getline(cin, nomePiloto);
                    system("cls");
                    temp.imprimeEstatisticas(temp.buscarPiloto(nomePiloto), temp.getNumCorridas());
                    break;
                case 2:
                    system("cls");
                    temp.imprimeTemporada();
                    break;
                case 3:
                    system("cls");
                    temp.imprimeVitoriosos();
                    break;
                case 4:
                    cin.clear(); cin.sync(); //limpa o buffer de entrada deixado pelo "cin"
                    system("cls");
                    cout << "Digite um nome para o arquivo: " << endl;
                    getline(cin, arqName);

                    if(temp.salvaArquivo(arqName) == true){
                        cout << "Arquivo gravado com sucesso!" << endl << endl;
                    }
                    system("pause");
                    system("cls");
                    break;
                case 5:
                    system("cls");
                    sair = true;
                break;
            }
        }
    }

    system("PAUSE");
    return 0;
}
