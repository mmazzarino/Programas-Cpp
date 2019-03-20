#include <iostream>
#include <string>

using namespace std;

class contaBancaria{
    public:
        float saldo;
        string titular;
        string numeroConta;
        float limiteCE;

        void imprimeSaldo(void){
            cout << "Saldo da conta:" << saldo << endl;
        }
};

int main()
{
    contaBancaria contas[5];
    contas[0].saldo = 999999;
    contas[0].titular = "Matheus Mazzarino";
    contas[0].numeroConta = "17111115-6";
    contas[0].limiteCE = 99999999;
    contas[0].imprimeSaldo();

    return 0;
}
