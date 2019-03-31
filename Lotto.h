#include "Definitions.h"

int ReallocatePlayerTab( Player*** tab, int playersNo );
int ReallocateBets( Bets** bets, int nSize );

void FreeMemory( Player*** pTab, int nSize );

int ReadPlayers( Player*** player, const char* FileName );
void ReadPlayer( Player* player, FILE* filename );
void ReadName( Player* player, FILE* filename );
int ReadSex( Player* player, FILE* filename );
int ReadDate( Player* pDate, FILE* filename );
void ReadSwift( Player* player, FILE* filename );
void ReadIban( Player* player, FILE* filename );
void ReadPesel( Player* player, FILE* filename );

int getDay( Date* pDate, int month ); // Wczytywanie dnia tygodnia w danym miesiacu w danym roku.
int getMonth( Date* pDate, int month ); // Wczytywanie miesiaca.
int dayInMonth( int month, int year ); // Okreslanie, ile dni ma dany miesiac

void CheckC( char* c, FILE* filename );

int SetDate( Player* myPlayer, int day, int month, int year );
int SetSex( Player* myPlayer, char c );