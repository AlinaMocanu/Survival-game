#ifndef JOC_H
#define JOC_H
#include "Harta.h"
#include "Agent.h"

class Joc
{
    int nr_agenti;
    int nr_itemi;
    Harta h;
    Agent** arr_agenti;
    char item;                         ///-->ofera invincibilitate pe parcursul unei runde
                                       /// doi agenti care au un item isi vor anula reciproc invincibilitatea; mai multi itemi gasiti nu se vor cumula
    coord genereaza_poz( const char );
public:
    Joc( const char );
    void afiseaza_harta() const;
    void plaseaza_agenti();
    void plaseaza_itemi( const char );
    ~Joc();
    void deplaseaza_agenti();
};

#endif // JOC_H
