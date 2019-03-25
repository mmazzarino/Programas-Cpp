#include <iostream>
#include <string>
#define N 10

using namespace std;

class contaBancaria{
    private:
        float saldo;
        float limite;
        int senha;

    public:
        string numeroConta;
        string titular;

    void cadastraCliente();
    void saque;
    void depositoPropriaConta;
    void imprimeSaldo(void);
    void acessarConta();
}


int main()
{
  contaBancaria v[N];
  cout << "    MENU PRINCIPAL" << endl << endl;
  cout << "1 - Acessar conta" << endl;
  cout << "2 - Cadastrar nova conta" << endl;
    cin >> int escolha1;
        switch(escolha1){
          case 1:
            cout << "Digite o numero da conta: " << endl;
            cin >> conta_aux1;
                for(int i = 0; i < N; i++){
                    if(conta_aux1 == v[i].numeroConta){
                        cout << "Digite a senha: " << endl;
                        cin >> senha_aux1;
                        if(senha_aux1 == v[i].senha){
                            v[i].acessarConta();
                        }
                    }
                }
                if(conta_aux1 == )


            }

    }


    return 0;
}
