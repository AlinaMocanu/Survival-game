#include "Agent.h"
#include<iostream>

using namespace std;

Agent::Agent( const std::string weapon ): viata( true ), item( false ), arma( weapon )
{
    poz.lin = 0;

    poz.col = 0;
}

Agent::~Agent()
{
    viata = 0;

    poz.lin = -1;

    poz.col = -1;

    item = false;

    arma = "";
}

void Agent::seteaza_coord( coord poz_generata )
{
    poz.lin = poz_generata.lin;

    poz.col = poz_generata.col;
}

coord Agent::get_poz() const
{
    return poz;
}

void Agent::set_item( bool val )
{
    item = val;
}

bool Agent::get_item() const
{
    return item;
}

void Agent::set_viata( bool val )
{
    viata = val;
}

bool Agent::get_viata() const
{
    return viata;
}

std::string Agent::get_arma() const
{
    return arma;
}

std::ostream & operator<<( std::ostream & out, const Agent &ob )
{
    out<<"viata: "<<ob.viata<<endl;

    out<<"item: "<<ob.item<<endl;

    out<<"pozitia: "<<ob.poz.lin<<" "<<ob.poz.col<<endl;

    out<<"arma: "<<ob.arma<<endl;

    return out;
}

///=========================================
Agent1::Agent1(): Agent( "pistol" )
{

}

Agent1::~Agent1()
{

}

/// Returneaza 1 daca agentul care a atacat a fost eliminat sau 0 daca a castigat
///In cazul in care agentul care a atacat castiga runda, metoda ii modifica pozitia pe harta
///Invincibilitatea va putea fi folosita o singura runda, asadar dupa ce e folosita va fi resetata
///Confruntarea incepe prin verificare itemilor, apoi daca ce doi agenti nu se pot diferentia astfel,
///se vor compara armele
const int Agent1::ataca( Agent* agent )
{
    if( get_item() == true && agent->get_item() == false )
    {
        seteaza_coord( agent->get_poz() );

        agent->set_viata( false );

        set_item( false );

        return 0;
    }

    if( get_item() == false && agent->get_item() == true )
    {
        set_viata( false );

        agent->set_item( false );

        return 1;
    }

    seteaza_coord( agent->get_poz() );

    agent->set_viata( false );

    set_item( false );

    return 0;
}
///================================================
Agent2::Agent2(): Agent( "sabie" )
{

}

Agent2::~Agent2()
{

}

const int Agent2::ataca( Agent* agent )
{
    if( get_item() == true && agent->get_item() == false )
    {
        seteaza_coord( agent->get_poz() );

        agent->set_viata( false );

        set_item( false );

        return 0;
    }

    if( get_item() == false && agent->get_item() == true )
    {

        set_viata( false );

        agent->set_item( false );

        return 1;
    }

    if( agent->get_arma() == "topor" )
    {
        seteaza_coord( agent->get_poz() );

        agent->set_viata( false );

        set_item( false );

        return 0;
    }

    set_viata( false );

    agent->set_item( false );

    return 1;
}
///===============================
Agent3::Agent3(): Agent( "topor" )
{

}

Agent3::~Agent3()
{

}

const int Agent3::ataca( Agent* agent)
{
    if( get_item() == true && agent->get_item() == false )
    {
        seteaza_coord( agent->get_poz() );

        agent->set_viata( false );

        set_item( false );

        return 0;
    }

    if( get_item() == false && agent->get_item() == true )
    {
        set_viata( false );

        agent->set_item( false );

        return 1;
    }

    set_viata( false );

    agent->set_item( false );

    return 1;
}





