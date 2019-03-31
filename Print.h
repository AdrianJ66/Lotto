#include "Definitions.h"

void PrintResults( int** pStats, Player** players, int nSize );
void PrintName( Player* player, FILE* fout );
void PrintDate( Player* player, FILE* fout );
void PrintSex( Player* player, FILE* fout );
void PrintSwift( Player* player, FILE* fout );
void PrintIban( Player* player, FILE* fout );
void PrintBets( Bets* bets, FILE* fout );
void PrintPesel( Player* player, FILE* fout );
void PrintStatistics( int* tab, FILE* fout, int nSize );

void Underline( FILE* file );

