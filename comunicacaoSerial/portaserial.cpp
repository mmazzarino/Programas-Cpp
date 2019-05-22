#include "portaSerial.h"

portaSerial::portaSerial(void)
{
    this->estado = false;
}

// Construtor. Cria e configura a porta. É possível alterar BaudRate através de br
portaSerial::portaSerial(const char *nome, DWORD br = CBR_9600)
{
    DCB dadosSerial;
    string aux(nome);
    this->estado = false;
    aux = "\\\\.\\" + aux;
    this->ps = CreateFileA(
                aux.c_str(),
                GENERIC_READ | GENERIC_WRITE,
                0,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL);
    if(this->ps == INVALID_HANDLE_VALUE)
    {
        cout << "ERRO AO ABRIR A PORTA" << endl;
        cout << "VERIFIQUE NOME / DISPOSITIVO" << endl;
    }
    else
    {
        SecureZeroMemory(&dadosSerial, sizeof(DCB));
        dadosSerial.DCBlength = sizeof(DCB);
        dadosSerial.BaudRate = br;
        dadosSerial.ByteSize = 8;
        dadosSerial.Parity = NOPARITY;
        dadosSerial.StopBits = ONESTOPBIT;
        if(!SetCommState(ps, &dadosSerial))  cout << "Problemas ao configurar porta..." << endl;
        else
        {
            PurgeComm(ps, PURGE_RXCLEAR | PURGE_TXCLEAR);
            Sleep(1500); //o sleep é p/ esperar o arduino sincronizar
            estado = true;
        }
    }
}

// Descrutor da classe. Fecha a porta
portaSerial::~portaSerial(void)
{
    if(this->estado) CloseHandle(this->ps);
}

// Abre a porta
bool portaSerial::open(const char *nome, DWORD br = CBR_9600)
{
    if(this->estado)
    {
        cout << "PORTA ESTA ABERTA!";
        return false;
    }
    DCB dadosSerial;
    string aux(nome);
    aux = "\\\\.\\" + aux;
    this->ps = CreateFileA(
                aux.c_str(),
                GENERIC_READ | GENERIC_WRITE,
                0,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL);
    if(this->ps == INVALID_HANDLE_VALUE)
    {
        cout << "ERRO AO ABRIR A PORTA" << endl;
        cout << "VERIFIQUE NOME / DISPOSITIVO" << endl;
    }
    else
    {
        SecureZeroMemory(&dadosSerial, sizeof(DCB));
        dadosSerial.DCBlength = sizeof(DCB);
        dadosSerial.BaudRate = br;
        dadosSerial.ByteSize = 8;
        dadosSerial.Parity = NOPARITY;
        dadosSerial.StopBits = ONESTOPBIT;
        if(!SetCommState(ps, &dadosSerial))  cout << "Problemas ao configurar porta..." << endl;
        else
        {
            PurgeComm(ps, PURGE_RXCLEAR | PURGE_TXCLEAR);
            Sleep(1500);
            this->estado = true;
        }
    }
    return this->estado;
}

void portaSerial::close(void)
{
    if(this->estado)
    {
        this->estado = false;
        CloseHandle(this->ps);
    }

}

// Retorna estado (verdadeiro = porta aberta e pronta)
bool portaSerial::ready(void)
{
    return this->estado;
}

// Escreve um byte na porta serial
bool portaSerial::writeByte(char data)
{
    DWORD dadosEscritos;
    bool aux = 0;
    if(this->estado) aux = WriteFile(this->ps,&data, 1, &dadosEscritos, NULL);
    return aux;
}

// Escreve uma palavra (2 bytes - short int)
// Ordem define como os bytes serão escritos: false (padrão) Byte baixo primeiro
bool portaSerial::writeWord(short int data, bool ordem = false)
{
    bool aux = 0;
    unsigned char a;
    if(this->estado)
    {
        if(ordem)
        {
            a = data;
            aux = this->writeByte(a);
            a = (data >> 8);
            aux |= this->writeByte(a);
        }
        else
        {
            a = (data >> 8);
            aux = this->writeByte(a);
            a = data;
            aux |= this->writeByte(a);
        }
    }
    return aux;
}

// Escreve vários bytes (qtde) na porta
bool portaSerial::write(char *data, unsigned int qtde)
{
    bool aux = 0;
    DWORD dadosEscritos;
    if(this->estado)
    {
        aux = WriteFile(this->ps,data,qtde,&dadosEscritos,NULL);
    }
    return aux;
}

// Retorna número de bytes no buffer de entrada
unsigned int portaSerial::BytesAvailable(void)
{
    COMSTAT st;
    DWORD erros;
    if(this->estado)
    {
        ClearCommError(this->ps, &erros, &st);
        return st.cbInQue;
    }
    else return 0;  // Sem uma contingencia melhor...
}

// Seta tempos de espera para leitura:
// n_bytes * tmaxbyte + tmaxread é o tempo total maximo em uma operação de ReadFile na porta
bool portaSerial::setTimeOuts(unsigned int tmaxread, unsigned int tmaxbyte)
{
    if(this->estado)
    {
        COMMTIMEOUTS timeouts;
        timeouts.ReadIntervalTimeout = tmaxbyte;
        timeouts.ReadTotalTimeoutConstant = tmaxread;
        timeouts.ReadTotalTimeoutMultiplier = tmaxbyte;
        return SetCommTimeouts(this->ps, &timeouts);
    }
    return 0;
}

// Lê um byte da porta
// (ATENÇÃO: não testa se leitura foi bem sucedida! Para testar deve-se utilizar read())
char portaSerial::readByte(void)
{
    char a;
    DWORD dadosLidos;
    if(this->estado)
    {
        ReadFile(this->ps,&a,1,&dadosLidos,NULL);
        return a;
    }
    return 0;
}

// Lê uma palavra da porta
// ordem (padrão falso), define a ordem de leitura. ordem = falso, byte baixo primeiro
// (ATENÇÃO: não testa se leitura foi bem sucedida! Para testar deve-se utilizar read())
short int portaSerial::readWord(bool ordem = false)
{
    union _si
    {
        short int a;
        char b[2];
    } data;
    if(this->estado)
    {
        if(ordem)
        {
            data.b[1] = this->readByte();
            data.b[0] = this->readByte();
        }
        else
        {
            data.b[0] = this->readByte();
            data.b[1] = this->readByte();
        }
    }
    return data.a;
}

// Lê vários bytes (qtde) da porta. Testa se leitura foi bem sucedida
bool portaSerial::read(char *data, unsigned int qtde)
{
    bool aux = 0;
    DWORD dadosLidos;
    if(this->estado)
    {
        aux = ReadFile(this->ps,data,qtde,&dadosLidos,NULL);
    }
    return aux;
}
