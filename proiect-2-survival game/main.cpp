#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "Joc.h"

using namespace std;

int main()
{
    srand( time( NULL ) );
    Joc j(1);
    j.plaseaza_agenti();
    j.plaseaza_itemi(1);
    cout<<"==============Harta initiala====================="<<endl;
    j.afiseaza_harta();
    cout<<endl<<"=================================================="<<endl<<endl<<endl;
    j.deplaseaza_agenti();









    return 0;
}
