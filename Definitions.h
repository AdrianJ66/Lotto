#pragma once

#include <iostream>
#include <time.h>

// IMIE I NAZWISKO
#define NAMELENGTH 25
// IBAN
#define ACOUNT 2 // Kraj konta. Takze do Swift. (2)
#define CDIG 2 // Cyfry Kontrolne. (2)
#define BNMBER 8 // Numer banku. (8)
#define ANMBER 16 // Numer konta. (16)
// SWIFT
#define BSNMBER 4 // Symbol banku. (4)
#define LSNMBER 2 // Symbol lokalizacji. (2)
#define BRSNMBER 3 // Symbol oddzialu. (3)
// POZOSTALE
#define PNMBER 10 // Numer Payback. (10)
#define MAINBETTABSIZE 5 // Ilosc liczb skladajaca sie na jeden normalny zaklad.
#define EXTRABETTABSIZE 2 // Ilosc liczb skladajaca sie na jeden dodatkowy zaklad.
#define BETSIZE 3 // Dlugosc tablicy przechowujacej tablice zakladow.
#define PLAYERSIZE 5 // Dlugosc tablicy z graczami.
#define FRMAINNUMBER 50 // Dlugosc tablicy ze statystykami.
#define FREXTRANUMBER 10

typedef enum { MALE, FEMALE } Sex;
typedef enum { MON = 15, TUE, WED = 31, THU, FRI, SAT = 101, SUN } Days;
typedef enum { JAN = 5, FEB, MAR, APR = 17, MAY, JUN = 36, JUL, AUG = 71, SEP, OCT, NOV = 104, DEC } Months;

typedef struct tagDate
{
	int dayNo;
	Days Day;
	Months Month;
	int year;
} Date;

typedef struct tagIban
{
	char AccountCountry[ACOUNT]; // Kraj konta
	char CheckDigits[CDIG]; // Cyfry kontrolne
	char BankNumber[BNMBER]; // Numer banku
	char AccountNumber[ANMBER]; // Numer konta
} Iban;

typedef struct tagSwitf
{
	char BankSymbol[BSNMBER]; // Symbol banku.
	char CountrySymbol[ACOUNT]; // Symbol kraju.
	char LocSymbol[LSNMBER]; // Symbol lokalizacji.
	char BranchSymbol[BRSNMBER]; // Symbol placowki.
} Swift;

typedef struct
{
	int* MainBet; //5 z 50
	int* ExtraBet; //2 z 10
} Bets;

typedef struct tagPlayer
{
	char FirstName[NAMELENGTH];
	char LastName[NAMELENGTH];
	Sex Sex;
	Date Date;
	Swift SwiftNumber;
	Iban IbanNumber;
	char PeselNumber[PNMBER];

	Bets* bets;
	int nSize; // Liczba zakladow.
	int cSize; // obecna ilosc

} Player;
