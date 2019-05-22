#ifndef PORTASERIAL_H
#define PORTASERIAL_H

#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

class portaSerial
{
    protected:
        HANDLE ps;
        bool estado;
    public:
        portaSerial(void);
        portaSerial(const char *, DWORD);
        ~portaSerial();
        bool open(const char *, DWORD);
        void close(void);
        bool ready(void);
        bool writeByte(char);
        bool writeWord(short int, bool);
        bool write(char *, unsigned int);
        unsigned int BytesAvailable(void);
        bool setTimeOuts(unsigned int,unsigned int);
        char readByte(void);
        short int readWord(bool);
        bool read(char *, unsigned int);
};


#endif // PORTASERIAL_H
