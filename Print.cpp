#include "Print.h"
#include "Lotto.h"
#include "Definitions.h"

//------------------------------------------------------------------------------------------------------------

void PrintResults( int** pStats, Player** players, int nSize )
{
	FILE * fout = NULL;
	if ( !( fout = fopen( "Output.txt", "w" ) ) )
	{
		printf( "PrintResults: file error" );
		return;
	}

	fprintf( fout, "\n-------------------------------------------------------------------------------------\n" );

	for ( int i = 0; i < nSize; i++ )
	{
		Player* person = players[i];  //Players[0]

		fprintf( fout, "\n-------------------------------------------------------------------------------------\n" );

		PrintName( person, fout );
		PrintSex( person, fout );
		PrintDate( person, fout );

		fprintf( fout, "\n" );

		PrintSwift( person, fout );
		PrintIban( person, fout );
		PrintPesel( person, fout );
		Underline( fout );
		Bets* personBets = person->bets;
		for ( int k = 0; k < person->nSize; k++ )
		{
			PrintBets( personBets, fout );
			personBets++;
		}
	}
		fprintf( fout, "  " );

		int* AllStats = pStats[0];
		fprintf( fout, "=========================================[STATISTICS]=========================================: \n\n" );
		fprintf( fout, "[MAINBET]: \n" );

		for ( int i = 0; i < FRMAINNUMBER; i++ )
		{
			fprintf( fout, "[%2d]: %2d ", i + 1, *AllStats++ );

			if ( ( ( i + 1 ) % 10 ) == 0 )                          //new line every 10 stat elem
				fprintf( fout, "\n" );
		}

		fprintf( fout, "\n" );

		int *pAllStats2 = pStats[1];

		fprintf( fout, "[EXTRABET]: \n" );

		for ( int i = 0; i < FREXTRANUMBER; i++ )
		{
			fprintf( fout, "[%2d]: %2d ", i + 1, *pAllStats2++ );

			if ( ( ( i + 1 ) % 10 ) == 0 )                          //new line every 10 stat elem
				fprintf( fout, "\n" );
		}
}
//------------------------------------------------------------------------------------------------------------
void PrintName( Player* player, FILE* file )
{
	fprintf( file, " %s %s\t   ", player->LastName, player->FirstName );
}
//------------------------------------------------------------------------------------------------------------
void PrintSex( Player* player, FILE* fout )
{
	switch ( player->Sex )
	{
	case 0:
		fprintf( fout, "*Typek* " );
		break;
	case 1:
		fprintf( fout, "*Panienka* " );
		break;
	}
}
//------------------------------------------------------------------------------------------------------------
void PrintDate( Player* player, FILE* fiout )
{
	fprintf( fiout, "[Date]:" );
	switch ( player->Date.Day )
	{
	case MON:fprintf( fiout, "Mon" );     break;
	case TUE:fprintf( fiout, "Tue" );     break;
	case WED:fprintf( fiout, "Wed" );     break;
	case THU:fprintf( fiout, "Thu" );     break;
	case FRI:fprintf( fiout, "Fri" );     break;
	case SAT:fprintf( fiout, "Sat" );     break;
	case SUN:fprintf( fiout, "Sun" );     break;

	}
	fprintf( fiout, ",%2d/", player->Date.dayNo );

	switch ( player->Date.Month )
	{
	case JAN: fprintf( fiout, "Jan/" );   break;
	case FEB: fprintf( fiout, "Feb/" );   break;
	case MAR: fprintf( fiout, "Mar/" );   break;
	case APR: fprintf( fiout, "Apr/" );   break;
	case MAY: fprintf( fiout, "May/" );   break;
	case JUN: fprintf( fiout, "Jun/" );   break;
	case JUL: fprintf( fiout, "Jul/" );   break;
	case AUG: fprintf( fiout, "Aug/" );   break;
	case SEP: fprintf( fiout, "Sep/" );   break;
	case OCT: fprintf( fiout, "Oct/" );   break;
	case NOV: fprintf( fiout, "Nov/" );   break;
	case DEC: fprintf( fiout, "Dec/" );   break;
	}
	fprintf( fiout, "%4d ", player->Date.year );
}//------------------------------------------------------------------------------------------------------------
void PrintSwift( Player* player, FILE* fout )
{
	fprintf( fout, "\n[SWIFT]:" );
	fprintf( fout, " %.4s %.2s %.2s %.3s",
			 player->SwiftNumber.BankSymbol,
			 player->SwiftNumber.CountrySymbol,
			 player->SwiftNumber.LocSymbol,
			 player->SwiftNumber.BranchSymbol );
}
//------------------------------------------------------------------------------------------------------------
void PrintIban( Player* player, FILE* fout )
{
	fprintf( fout, "\t\t[IBAN]:" );
	fprintf( fout, " %.2s %.2s ",
			 player->IbanNumber.AccountCountry, player->IbanNumber.CheckDigits );

	for ( int j = 0; j < 8; j++ )
	{
		fprintf( fout, "%c", player->IbanNumber.BankNumber[j] );

		if ( j == 3 )
			fprintf( fout, " " );
	}

	fprintf( fout, " " );

	for ( int j = 0; j < 16; j++ )
	{
		fprintf( fout, "%c", player->IbanNumber.AccountNumber[j] );

		if ( ( j + 1 ) % 4 == 0 )
			fprintf( fout, " " );
	}
}
//------------------------------------------------------------------------------------------------------------

void PrintBets( Bets* bets, FILE* fout )
{
	Bets* personBets = bets;

	int *main = personBets->MainBet;  //main bet
	int *extra = personBets->ExtraBet; //extra bet

	for ( int i = 0; i < MAINBETTABSIZE; i++ )
	{
		fprintf( fout, "%3d ", *main++ );
	}

	fprintf( fout, "\t\t" );

	for ( int i = 0; i < EXTRABETTABSIZE; i++ )
	{
		fprintf( fout, "%2d ", *extra++ );
	}

	fprintf( fout, "\n" );
}
//------------------------------------------------------------------------------------------------------------

void PrintPesel( Player* player, FILE* fout )
{
	fprintf( fout, "\t\t[PESEL]: %s \t", player->PeselNumber );
}

//------------------------------------------------------------------------------------------------------------


void PrintStatistics( int* tab, FILE* fout, int nSize )
{
	fprintf( fout, "\n\n" );

	for ( int i = 0; i < 54; i++ )
		fprintf( fout, "=" );
	fprintf( fout, "\n" );

	fprintf( fout, "\t\t   STATISTICS" );
	fprintf( fout, "\n" );

	for ( int i = 0; i < 54; i++ )
		fprintf( fout, "=" );
	fprintf( fout, "\n" );

	int* pointer = tab;
	for ( int j = 0; j < nSize; j++, pointer++ )
	{
		if ( j < 9 )
			fprintf( fout, "% d: %-2d ", j + 1, *pointer ); /// !!! na wskaznikach
		else
			fprintf( fout, "%d: %-2d ", j + 1, *pointer );

		if ( ( j + 1 ) % 10 == 0 )
			fprintf( fout, "\n" );
	}
}

//------------------------------------------------------------------------------------------------------------
void Underline( FILE* file )
{
	fprintf( file, "\n" );
	for ( int i = 0; i < 55; i++ )
		fprintf( file, "-" );
	fprintf( file, "\n" );
}
//------------------------------------------------------------------------------------------------------------