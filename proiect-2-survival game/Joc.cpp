#include "Joc.h"
#include <iostream>

using namespace std;

Joc::Joc( const char init_item ): nr_agenti(7), nr_itemi(4)
{
    arr_agenti = new Agent*[nr_agenti];

    item = init_item;
}

void Joc::afiseaza_harta() const
{
    char s;
    int dim_harta = h.get_dim();

    for( int i = 0; i < dim_harta; i++ )
    {
        cout<<"           ";

        for( int j = 0; j < dim_harta; j++ )
        {
            s = h.get_el(i, j);

            cout<< s <<" ";
        }
        cout<<endl;
    }
}
/// genereaza doua numere din intervalul [0,14]
///pentru a obtine o pozitie neocupata in matricea initiala;
///parametrul primit reprezinta numarul agentului care se va gasi pe pozitia generata
coord Joc::genereaza_poz( const char nr_agent )
{
    coord poz_generata;

    int irand = rand() % 15;

    int jrand = rand() % 15;

    while( h.get_el( irand, jrand ) != '_' )
    {
        irand = rand() % 15;

        jrand = rand() % 15;
    }

    h.set_poz( irand, jrand, nr_agent );

    poz_generata.lin = irand;

    poz_generata.col = jrand;

    return poz_generata;
}

///Main intai vor fi plasati trei agenti,unul din fiecare tip, apoi restul agentilor vor fi generati aleator
void Joc::plaseaza_agenti()
{
    coord poz_generata;

    int nr_rand;

    poz_generata = genereaza_poz( '1' );

    arr_agenti[0] = new Agent1;

    arr_agenti[0]->seteaza_coord( poz_generata );
    ///---------------------------------------
    poz_generata = genereaza_poz( '2' );

    arr_agenti[1] = new Agent2;

    arr_agenti[1]->seteaza_coord( poz_generata );
    ///----------------------------------------
    poz_generata = genereaza_poz( '3' );

    arr_agenti[2] = new Agent3;

    arr_agenti[2]->seteaza_coord( poz_generata );

    for( int i = 3; i < nr_agenti; i++ )
    {
        nr_rand = rand() % 3 + 1;

        switch( nr_rand )
        {
        case 1:
        {
            poz_generata = genereaza_poz( '1' );

            arr_agenti[i] = new Agent1;

            arr_agenti[i]->seteaza_coord( poz_generata );

            break;
        }
        case 2:
        {
            poz_generata = genereaza_poz( '2' );

            arr_agenti[i] = new Agent2;

            arr_agenti[i]->seteaza_coord( poz_generata );

            break;
        }
        case 3:
        {
            poz_generata = genereaza_poz( '3' );

            arr_agenti[i] = new Agent3;

            arr_agenti[i]->seteaza_coord( poz_generata );

            break;
        }
        }
    }
}

void Joc::plaseaza_itemi( const char item )
{
    coord poz_item;

    for( int i = 0; i < nr_itemi; i++ )
        poz_item = genereaza_poz( item );
}

/// Pe rand, fiecare agent memorat in vector va parcurge harta de la stanga la dreapta, de sus in jos daca nu a fost deja eliminat.
/// Daca pozitia imediat urmatoare este libera sau contine un item, agentul inainteaza si daca e cazul colecteaza itemul.
/// Daca intalneste un alt agent, agentul care parcurge harta va initia o confruntare.
/// In cazul in care iese castigator, isi continua drumul, altfel va fi eliminat si se va alege urmatorul agent memorat in vector pentru a parcurge harta.
void Joc::deplaseaza_agenti()
{
    coord pozitie_noua, pozitie_veche, poz_temp;
    Agent* agent;
    int result;

    for( int i = 0; i < nr_agenti; i++ )
    {
        pozitie_noua = arr_agenti[i]->get_poz();

        while( ( pozitie_noua.lin != 14 || pozitie_noua.col != 14 ) && arr_agenti[i]->get_viata() != false )
        {
            ///====trecere la rand nou====
            if( pozitie_noua.col == 14 )
            {
                if( h.get_el( pozitie_noua.lin + 1, 0 ) == '_' )
                {
                    pozitie_noua.lin++;

                    pozitie_noua.col = 0;

                    pozitie_veche = arr_agenti[i]->get_poz();

                    h.set_poz( pozitie_noua.lin, pozitie_noua.col, h.get_el( pozitie_veche.lin, pozitie_veche.col ) );

                    h.set_poz( pozitie_veche.lin, pozitie_veche.col, '_' );

                    arr_agenti[i]->seteaza_coord( pozitie_noua );
                }
                else if( h.get_el( pozitie_noua.lin + 1, 0 ) == item )
                {
                    pozitie_noua.lin++;

                    pozitie_noua.col = 0;

                    pozitie_veche = arr_agenti[i]->get_poz();

                    h.set_poz( pozitie_noua.lin, pozitie_noua.col, h.get_el( pozitie_veche.lin, pozitie_veche.col ) );

                    h.set_poz( pozitie_veche.lin, pozitie_veche.col, '_' );

                    arr_agenti[i]->seteaza_coord( pozitie_noua );

                    arr_agenti[i]->set_item( true );
                }
                else
                {
                    afiseaza_harta();

                    cout<<endl<<"=================================================="<<endl;

                    for( int j = 0; j < 7; j++ )
                    {
                        poz_temp = arr_agenti[j]->get_poz();

                        if( arr_agenti[i]->get_viata() != false )

                            if( poz_temp.lin == pozitie_noua.lin + 1 &&  poz_temp.col == 0 )
                            {
                                agent = arr_agenti[j];

                                break;
                            }
                    }


                    cout<< endl << "Confruntare intre agentul " << h.get_el( pozitie_noua.lin, pozitie_noua.col ) << endl << *arr_agenti[i];

                    cout<< endl << "si agentul " << h.get_el( poz_temp.lin, poz_temp.col ) << endl << *agent;

                    result = arr_agenti[i]->ataca( agent );

                    if( result == 0)
                    {
                        cout<< endl << "A fost eliminat agentul " << h.get_el( poz_temp.lin, poz_temp.col ) << " de pe pozitia " << poz_temp.lin <<" "<< poz_temp.col <<endl;

                        cout<< "Agentul atacat a fost eliminat" << endl;

                        h.set_poz( poz_temp.lin, poz_temp.col, h.get_el( pozitie_noua.lin, pozitie_noua.col ) );

                        h.set_poz( pozitie_noua.lin, pozitie_noua.col, '_' );
                    }
                    else
                    {
                        cout<<endl<< "A fost eliminat agentul " << h.get_el( pozitie_noua.lin, pozitie_noua.col )<< " de pe pozitia "<< pozitie_noua.lin <<" "<< pozitie_noua.col <<endl;

                        cout<< "Agentul atacat a castigat" <<endl;

                        h.set_poz( pozitie_noua.lin, pozitie_noua.col, '_' );
                    }

                    afiseaza_harta();

                    cout<<endl<<"=================================================="<<endl;

                    pozitie_noua = poz_temp;
                }
            }
            ///=====deplasarea pe acelasi rand===============
            else if( h.get_el( pozitie_noua.lin, pozitie_noua.col + 1 ) == '_' )
            {
                pozitie_noua.col++;

                pozitie_veche = arr_agenti[i]->get_poz();

                h.set_poz( pozitie_noua.lin, pozitie_noua.col, h.get_el( pozitie_veche.lin, pozitie_veche.col ) );

                h.set_poz( pozitie_veche.lin, pozitie_veche.col, '_' );

                arr_agenti[i]->seteaza_coord( pozitie_noua );
            }
            else if( h.get_el( pozitie_noua.lin, pozitie_noua.col + 1 ) == item )
            {
                pozitie_noua.col++;

                pozitie_veche = arr_agenti[i]->get_poz();

                h.set_poz( pozitie_noua.lin, pozitie_noua.col, h.get_el( pozitie_veche.lin, pozitie_veche.col ) );

                h.set_poz( pozitie_veche.lin, pozitie_veche.col, '_' );

                arr_agenti[i]->seteaza_coord( pozitie_noua );

                arr_agenti[i]->set_item( true );
            }
            else
            {
                afiseaza_harta();

                cout<<endl<<"=================================================="<<endl;

                for( int j = 0; j < 7; j++ )
                {
                    poz_temp = arr_agenti[j]->get_poz();

                    if( arr_agenti[i]->get_viata() != false )

                        if( poz_temp.lin == pozitie_noua.lin && poz_temp.col == pozitie_noua.col + 1 )
                        {
                            agent = arr_agenti[j];

                            break;
                        }
                }

                cout<< endl << "Confruntare intre agentul " << h.get_el( pozitie_noua.lin, pozitie_noua.col ) << endl << *arr_agenti[i] <<endl;
                cout<< "si agentul " << h.get_el( poz_temp.lin, poz_temp.col ) << endl << *agent << endl;

                result = arr_agenti[i]->ataca( agent );


                if( result == 0)
                {
                    cout<< endl << "A fost eliminat agentul " << h.get_el( poz_temp.lin, poz_temp.col ) << " de pe pozitia " << poz_temp.lin <<" "<< poz_temp.col << endl;

                    cout<< "Agentul atacat a fost eliminat" <<endl;

                    h.set_poz( poz_temp.lin, poz_temp.col, h.get_el( pozitie_noua.lin, pozitie_noua.col ) );

                    h.set_poz( pozitie_noua.lin, pozitie_noua.col, '_' );
                }
                else
                {
                    cout<< endl << "A fost eliminat agentul " << h.get_el( pozitie_noua.lin, pozitie_noua.col )<< " de pe pozitia " << pozitie_noua.lin <<" "<< pozitie_noua.col << endl;

                    cout<< "Agentul atacat a castigat" <<endl;

                    h.set_poz( pozitie_noua.lin, pozitie_noua.col, '_' );
                }

                afiseaza_harta();

                cout<<endl<<"=================================================="<<endl;

                pozitie_noua.col++;
            }
        }
    }
}


Joc::~Joc()
{
    for( int i = 0; i < nr_agenti; i++)
        delete arr_agenti[i];

    nr_itemi = 0;
    nr_agenti = 0;
    delete[] arr_agenti;
}
