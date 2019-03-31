#include "Definitions.h"
#include "Lotto.h"

int ReadPlayers( Player*** player, const char* FileName )
{
	//-------------------------------------------------------------------------------------------
	FILE* fin = fopen( FileName, "rt" );        // plik do odczytu   
	if ( !fin )
	{
		printf( "ReadData: file error" );
		return 0;
	}
	//-------------------------------------------------------------------------------------------

	int playersNum = 0;

	while ( !feof( fin ) )               // while !end   feof - zwraca wartoœæ niezerow¹ je¿eli wczeœniej napotkano koniec pliku tekstowego
	{
		///--------------------------------------------------------------------------------------
		if ( fgetc( fin ) == '*' )           // if znak ze strumienia = '*'
		{
			///---------------------------------------------------------------------------------- 

			if ( !( playersNum % PLAYERSIZE ) )                //realokuje pamiec jesli nie mam miejsca w tablicy
			{
				if ( !ReallocatePlayerTab( player, playersNum ) )
					break;
			}

			///----------------------------------------------------------------------------------

			Player* person = ( *player )[playersNum++] = ( Player* )calloc( 1, sizeof( Player ) );
			if ( !person )
			{
				printf( "ReadData: allocation error" );
				return 0;
			}
			///----------------------------------------------------------------------------------

			// wczytujê dane

			ReadPlayer( person, fin );

			///----------------------------------------------------------------------------------
			char c;
			while ( !feof( fin ) )                // while !end of line
			{
				///------------------------------------------------------------------------------

				if ( ( c = fgetc( fin ) ) == '*' )
				{
					ungetc( c, fin );               // return and stop while loop
					break;
				}
				else if ( c<'0' || c>'9' )             // if out of reach stop the iteration
					continue;

				ungetc( c, fin );                   // return

				///----------------------------------------------------------------------------------

				if ( !( person->nSize % BETSIZE ) )        //realokacja pamiêci jeœli nie ma miejsca w tab miejsca na bety
				{
					if ( !ReallocateBets( &person->bets, person->nSize ) )
						break;
				}

				///----------------------------------------------------------------------------------

				Bets* playerBets = &( person->bets[person->nSize++] );

				///----------------------------------------------------------------------------------

				int* five = playerBets->MainBet = ( int* )calloc( MAINBETTABSIZE, sizeof( int ) );

				if ( !five ) //check
				{
					printf( "ReadData: allocation error" );
					break;
				}

				int* two = playerBets->ExtraBet = ( int* )calloc( EXTRABETTABSIZE, sizeof( int ) );

				if ( !two ) //check 
				{
					printf( "ReadData: allocation error" );
					break;
				}
				//int k;
				for ( int i = 0; i < MAINBETTABSIZE; i++ )      //pobieram 5 dec 
				{
					fscanf( fin, "%d", /*&k*/five++ );
					//*five++ = k;
				}
				for ( int i = 0; i < EXTRABETTABSIZE; i++ )   //pobieram 2 dec
				{
					fscanf( fin, "%d", /*&k*/two++ );
					//*two++ = k;
				}
			}
		}
	}
	fclose( fin );

	return playersNum;

}
//------------------------------------------------------------------------------------------------------------
int ReallocatePlayerTab( Player*** tab, int playersNo )
{
	if ( !( playersNo % PLAYERSIZE ) )                //adds mem every 5 players                            
	{
		///-------------------------------------------------------------------------------------

		int newSize = playersNo + PLAYERSIZE;

		Player** temp = ( Player** )realloc( *tab, newSize * sizeof( Player* ) );

		if ( !temp )    //check
		{
			printf( "AllocAddMem: allocation error" );
			return 0;
		}

		///-------------------------------------------------------------------------------------
		*tab = temp;

		memset( ( temp + playersNo ), 0, sizeof( Player* ) * PLAYERSIZE );

		return 1;
	}
	return 0;
}
//------------------------------------------------------------------------------------------------------------

int ReallocateBets( Bets** bets, int nSize )
{
	///-----------------------------------------------------------------------------------------
	int newSize = nSize + BETSIZE;

	Bets* temp = ( Bets* )realloc( *bets, newSize * sizeof( Bets ) );

	if ( !temp ) //check 
	{
		printf( "ReallocateBets: reallocation error" );
		return 0;
	}

	///-----------------------------------------------------------------------------------------
	*bets = temp;

	memset( ( *bets + nSize ), 0, sizeof( Bets ) * BETSIZE );    // wype³nia now¹ pamiêæ zerami

	return 1;
}

//------------------------------------------------------------------------------------------------------------
void FreeMemory( Player*** pTab, int nSize )
{
	///-----------------------------------------------------------------------------------------

	for ( int i = 0; i < nSize; i++ )
	{
		///-------------------------------------------------------------------------------------

		Player* player = ( *pTab )[i];   // Players[x]

		Bets* playerBets = player->bets;

		///-------------------------------------------------------------------------------------
		for ( int j = 0; j < player->nSize; j++, playerBets++ ) // zwalniamy pamiêc z zak³adów 
		{
			free( playerBets->MainBet );  //free mainbet
			free( playerBets->ExtraBet ); //free extrabet
		}

		free( player->bets );
		free( player );
	}
	free( *pTab );
	pTab = NULL;
}
//------------------------------------------------------------------------------------------------------------
void ReadPlayer( Player* player, FILE* filename )
{
	ReadName( player, filename );

	if ( !ReadSex( player, filename ) )
	{
		printf( "ERROR_setSex.\n\n" );
		return;
	}

	ReadSwift( player, filename );
	ReadIban( player, filename );

	if ( !ReadDate( player, filename ) )
	{
		printf( "ERROR_setDate.\n\n" );
		return;
	}

	ReadPesel( player, filename );
		
	player->bets = NULL;
	player->nSize = 0;
	player->cSize = 0;
}
//------------------------------------------------------------------------------------------------------------
void ReadName( Player* player, FILE* filename )
{
	fscanf( filename, "%s %s", player->LastName, player->FirstName );
}
//------------------------------------------------------------------------------------------------------------
int ReadSex( Player* player, FILE* filename )
{
	char sex;
	fscanf( filename, " %c", &sex );

	switch ( sex )
	{
	case 'f':
	case 'F': player->Sex = FEMALE; return 1;
	case 'm':
	case 'M': player->Sex = MALE;	return 1;
	}
	return 0;
}
//------------------------------------------------------------------------------------------------------------
void ReadSwift( Player* gracz, FILE* plik )
{
	fscanf( plik, " %4c", gracz->SwiftNumber.BankSymbol );
	fscanf( plik, "%2c", gracz->SwiftNumber.CountrySymbol );
	fscanf( plik, "%2c", gracz->SwiftNumber.LocSymbol );
	fscanf( plik, "%3c", gracz->SwiftNumber.BranchSymbol );
}
//------------------------------------------------------------------------------------------------------------
void ReadIban( Player* gracz, FILE* plik )
{
	fscanf( plik, " %2c", gracz->IbanNumber.AccountCountry );
	fscanf( plik, "%2c", gracz->IbanNumber.CheckDigits );
	fscanf( plik, "%8c", gracz->IbanNumber.BankNumber );
	fscanf( plik, "%16c", gracz->IbanNumber.AccountNumber );
}
//------------------------------------------------------------------------------------------------------------
void ReadPesel( Player* player, FILE* plik )
{
	fscanf( plik, " %11c", player->PeselNumber );
}
//------------------------------------------------------------------------------------------------------------

int ReadDate( Player* player, FILE* filename )
{
	int year;
	int month;
	int day;

	fscanf( filename, " %d/%d/%d", &day, &month, &year );

	if ( year < 1950 || ( month < 1 || month > 12 ) || ( day < 1 || day > dayInMonth( month, year ) ) )
		return 0;

	time_t actualTime = time( NULL );
	tm* readTime = localtime( &actualTime );
	readTime->tm_year += 1900;

	player->Date.dayNo = day; // Dzien miesiaca (1-31)
	player->Date.year = year;

	if ( ( !getDay( &player->Date, month ) ) || ( !getMonth( &player->Date, month ) ) )
		return 0;

	return 1;
}
//------------------------------------------------------------------------------------------------------------
int getDay( Date* pDate, int month )
{
	tm readTime;

	readTime.tm_year = pDate->year - 1900;
	readTime.tm_mon = month - 1;
	readTime.tm_mday = pDate->dayNo;
	readTime.tm_hour = readTime.tm_min = readTime.tm_sec = 0;

	mktime( &readTime );

	switch ( readTime.tm_wday )
	{
	case 0: pDate->Day = SUN; return 1;
	case 1: pDate->Day = MON; return 1;
	case 2: pDate->Day = TUE; return 1;
	case 3: pDate->Day = WED; return 1;
	case 4: pDate->Day = THU; return 1;
	case 5: pDate->Day = FRI; return 1;
	case 6: pDate->Day = SUN; return 1;
	}

	return 0;
}
//------------------------------------------------------------------------------------------------------------
int getMonth( Date* pDate, int month )
{
	switch ( month )
	{
	case 1: pDate->Month = JAN; return 1;
	case 2: pDate->Month = FEB; return 1;
	case 3: pDate->Month = MAR;	return 1;
	case 4: pDate->Month = APR;	return 1;
	case 5: pDate->Month = MAY;	return 1;
	case 6: pDate->Month = JUN;	return 1;
	case 7: pDate->Month = JUL;	return 1;
	case 8: pDate->Month = AUG;	return 1;
	case 9: pDate->Month = SEP;	return 1;
	case 10: pDate->Month = OCT; return 1;
	case 11: pDate->Month = NOV; return 1;
	case 12: pDate->Month = DEC; return 1;
	}
	return 0;
}
//------------------------------------------------------------------------------------------------------------
int dayInMonth( int month, int year )
{
	switch ( month )
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12: return 31;
	case 4:
	case 6:
	case 9:
	case 11: return 30;
	case 2:
		if ( ( year % 4 == 0 ) && ( ( year % 100 != 0 ) || ( year % 400 == 0 ) ) )
			return 29;
		else return 28;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------------------
void CheckC( char* c, FILE* filename )
{
	*c = fgetc( filename );

	while ( *c == '\n' || *c == ' ' ) // nowa linia, spacja
		*c = fgetc( filename );
}
//------------------------------------------------------------------------------------------------------------
