#include "Harta.h"

Harta::Harta(): dim_harta(15)
{
    map = new char*[dim_harta];

    for( int i = 0; i < dim_harta; i++ )
    {
        map[i] = new char[dim_harta];

        for( int j = 0; j < dim_harta; j++ )
            map[i][j] = '_';
    }
}

Harta::Harta( Harta& ob)
{
    map = new char*[dim_harta];

    for( int i = 0; i < dim_harta; i++ )
    {
        map[i] = new char[dim_harta];

        for( int j = 0; j < dim_harta; j++ )
            map[i][j] = ob.map[i][j];
    }
}

Harta::~Harta()
{
    for( int i = 0; i < dim_harta; i++ )
        delete[] map[i];

    dim_harta = 0;
    delete map;
}

int Harta::get_dim() const
{
    return dim_harta;
}

/// intoarce elemntul de pe linia i si coloana j din matrice
const char Harta::get_el( int i, int j) const
{
    return map[i][j];
}
/// marcheaza in matrice pozitia aleator generata pentru un agent
void Harta::set_poz( int i, int j, char nr_agent)
{
    map[i][j] = nr_agent;
}





