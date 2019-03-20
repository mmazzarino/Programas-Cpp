#include <iostream>
#include <string>
using namespace std;

struct aluno{
    string nome;
    int notas[2];

};

int main()
{
    struct aluno fulano;

    string aux1, aux2, aux3;
    cout << "Digite uma string:" << endl;
    getline(cin, aux1);

    cout << "Digite uma string:" << endl;
    getline(cin, aux2);

    aux3 = aux1 + " " + aux2;  //em C não podemos concatenar strings tão facil
    cout << aux3 << endl;

    return 0;
}
