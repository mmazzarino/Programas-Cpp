#include <iostream>
#include "portaserial.h"

using namespace std;

int main()
{
   portaSerial s1;
   s1.open("COM4", 9600);
   if(s1.ready())
   {
       for(char k = 0; k < 100; k++)
       {
           s1.writeByte(k);
           Sleep(100);
           cout << k << endl;
       }
   }
   else
   {
       cout << "deu pau" << endl;
   }



}
