#ifndef HARTA_H
#define HARTA_H

class Harta
{
    int dim_harta;
    char** map;
public:
    Harta();
    ~Harta();
    Harta( Harta& );
    const char get_el( int, int ) const;
    void  set_poz( int, int, char );
    int get_dim() const;
};

#endif // HARTA_H
