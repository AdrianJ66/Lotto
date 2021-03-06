// Lotto.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string.h>
#include <ctype.h>
#include "Definitions.h"
#include "Lotto.h"
#include "Print.h"

using namespace std;

void HeapCheck(); // wziety z helpa
void CalcStat( int **pStats, Player** player, int nSize ); // zlicza ilość wystąpień każdej licby we wszystkich zakładach osobno dla podstawowych i																			dodatkowych
void Sort( Player** player, int playerNum );
int strCompare( char * s1, char *s2 );



int main( int argc, char* argv[] )
{
	if ( argc != 2 )
	{
		printf( "Error: Start the program using an input file!\n" );
		return -1;
	}

	Player** Players = NULL;

	int playersNo = ReadPlayers( &Players, argv[1] ); // arg
	if ( !playersNo )
	{
		printf( "Error: Not able to read the input file! \n" );
		return -2;
	}

	int **statTab = ( int** )calloc( 2, sizeof( int* ) ); //struktura zlozona z 2 tablic z wynikami
	if ( !statTab ) 
	{
		printf( "MainError: allocation error" );
		return 0;
	}

	statTab[0] = ( int* )calloc( FRMAINNUMBER, sizeof( int ) );  //50
	statTab[1] = ( int* )calloc( FREXTRANUMBER, sizeof( int ) ); //10

	if ( !statTab[0] || !statTab[1] )
	{
		printf( "MainError: allocation error" );
		return 0;
	}

	CalcStat( statTab, Players, playersNo );

	///------------------------------------------------------------------------------------------

	Sort( Players, playersNo );  // sortujemy graczy (porównujemy alfabetycznie)

	///------------------------------------------------------------------------------------------

	PrintResults( statTab, Players, playersNo );	



	free( statTab[0] );
	free( statTab[1] );
	free( statTab );

	FreeMemory( &Players, playersNo );

	HeapCheck();

	return 123;
}


//------------------------------------------------------------------------------------------

void Sort( Player** players, int playerNum ) //porownuje funkcja biblioteczna
{
	for ( int i = 0; i < playerNum - 1; i++ )  // dla kazdego gracza
	{
		Player* min = players[i];    
		int x = i;

		for ( int j = i + 1; j < playerNum; j++ )
		{
			if ( strCompare( min->LastName, players[j]->LastName ) > 0 ) // strncmp porownuje wg porzadku alfabetycznego
			{
				min = players[j];     //porówna 6 pierwszych liter, unikam overflow
				x = j;
			}
		}
		players[x] = players[i];
		players[i] = min;
	}
}

//--------------------------------------------------------------------------------------------

void CalcStat( int **pStats, Player** player, int nSize )  //oblicza statystyki dla kazdego gracza z obu zakladow
{
	int* temp5 = pStats[0];  // tablica dla mainBet
	int* temp2 = pStats[1];  // tablica dla extraBet

	for ( int i = 0; i < nSize; i++ ) //przechodzi przez wszystkich graczy
	{
		Player* person = *player;    

		Bets* personBets = person->bets;


		for ( int j = 0; j < person->nSize; j++ ) // przejdziemy przez wszytstkie zakłady
		{
			///-------------------------------------------------------------------------------

			int* pMainBet = personBets->MainBet;

			for ( int k = 0; k < MAINBETTABSIZE; k++ )  
			{
				if ( ( *pMainBet > FRMAINNUMBER + 1 ) || ( *pMainBet < 1 ) )  //ustalam granice 0-50
				{
					printf( "CalcStatERROR: Main wrong data" ); //podalismy zla liczbe
					return;
				}
				temp5[*pMainBet - 1]++;                                // dodajemy do statystyk

				*pMainBet++;                                            // kolejna obstawiona liczba
			}

			///-------------------------------------------------------------------------------

			int* pExtraBet = personBets->ExtraBet;

			for ( int l = 0; l < EXTRABETTABSIZE; l++ ) 
			{
				if ( ( *pExtraBet > FREXTRANUMBER ) || *pExtraBet < 1 ) // ustalam granice liczb 0-10
				{
					printf( "CalcStatERROR: Extra wrong data" ); //podalismy zla liczbe
					return;
				}
				temp2[*pExtraBet - 1]++;                          // dodajemy do statystyk //pExtrabet[c] 

				*pExtraBet++;                                                // kolejna obstawiona liczba
			}
			personBets++; //przechodzimy do kolejnego betu danego gracza
		}
		*player++;  //kolejny gracz
	}
}

//----------------------------------------------------------------------------------------------

void HeapCheck() {   //Przeprowadza sprawdzanie spójności na stosie
	int heapstatus = _heapchk();
	switch ( heapstatus )
	{
	case _HEAPOK:
		printf( " OK - heap is fine\n" );
		break;
	case _HEAPEMPTY:
		printf( " OK - heap is empty\n" );
		break;
	case _HEAPBADBEGIN:
		printf( "ERROR - bad start of heap\n" );
		break;
	case _HEAPBADNODE:
		printf( "ERROR - bad node in heap\n" );
		break;
	}
}

//----------------------------------------------------------------------------------------------

int strCompare( char* string1, char* string2 )
{
	//char* str1 = ( char* )calloc( strlen( string1 ) + 1, sizeof( char ) );
	//char* str2 = ( char* )calloc( strlen( string2 ) + 1, sizeof( char ) );
	char* str1 = ( char* )malloc( strlen( string1 ) + 1 * sizeof( char ) );
	char* str2 = ( char* )malloc( strlen( string2 ) + 1 * sizeof( char ) );


	if ( !str1 || !str2 ) // check
	{
		perror( "StrCompareError: allocation error" );
		return 5;
	}

	strcpy( str1, string1 ); // strcpy(wskaźnik do docelowej tablicy znaków, wskaźnik do źródłowej tablicy znaków)
	strcpy( str2, string2 ); // strcpy(wskaźnik do docelowej tablicy znaków, wskaźnik do źródłowej tablicy znaków)

	for ( size_t i = 0; i < strlen( string1 ); i++ ) // zamieniam na wielkie
		str1[i] = toupper( str1[i] );

	for ( size_t i = 0; i < strlen( string2 ); i++ ) // zamieniam na wielkie
		str2[i] = toupper( str2[i] );

	int wynik = strcmp( str1, str2 ); // compare

	free( str1 );
	free( str2 );

	return wynik;
}


