#ifndef AGENT_H
#define AGENT_H
#include <string>
#include <iostream>

typedef struct
{
    int lin, col;
} coord;

class Agent
{
    bool viata;
    bool item;
    coord poz;
    std::string arma;
public:
    Agent( const std::string );
    virtual ~Agent();
    void seteaza_coord( coord );
    coord get_poz() const;
    void set_item( bool );
    bool get_item() const;
    void set_viata( bool );
    bool get_viata() const;
    std::string get_arma() const;
    virtual const int ataca( Agent* ) = 0;
    friend std::ostream & operator<<( std::ostream & out, const Agent & ob );
};

class Agent1: public Agent /// arma este pistolul, care poate invinge atat sabia cat si toporul
{

public:
    Agent1();
    ~Agent1();
    const int ataca( Agent* );
};

class Agent2: public Agent /// arma este sabia, care poate invinge doar toporul
{

public:
    Agent2();
    ~Agent2();
    const int ataca( Agent* );
};

class Agent3: public Agent /// arma este toporul, arma cu cel mai mic grad de aparare
{

public:
    Agent3();
    ~Agent3();
    const int ataca( Agent* );
};
#endif // AGENT_H
