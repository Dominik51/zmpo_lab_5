#ifndef CMenuItem_H
#define CMenuItem_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const string LINE = "----------------------------";
const char OPENING_ROUND_BRACKET = '(';
const char CLOSING_ROUND_BRACKET = ')';
const char OPENING_SQUARE_BRACKET = '[';
const char CLOSING_SQAURE_BRACKET = ']';
const char APOSTROPHE = '\'';
const char COMMA = ',';
const char SEMICOLON = ';';
const string OR = " lub ";
const string SPACE = " ";
const string BEGIN_OF_COMMAND = "['";
const string BEGIN_OF_MENU = "('";
const string INSERT_COMMAND = "Podaj komende: ";
const string COMMAND_NOT_FOUND = "Nie znaleziono pozycji";
const string EMPTY_COMMAND = "Pusta komenda";
const string ITEM_ALREADY_EXIST = "Podanan element menu juz istnieje";
const string ITEM_REMOVED = "Podanan element zostal usuniety";
const string ITEM_NOT_REMOVED = "Podanan element nie zostal znaleziony";
const string ITEM_NOT_ADDED = "Bledna nazwa lub komenda";
const string GET_COMMAND_NAME = "Podaj nazwe: ";
const string GET_COMMAND = "Podaj komende: ";
const string GET_RUN = "wybierz dzialanie nowej komendy: ";
const string GET_MENU_ITEM_TYPE = "[0] dodaje nowe menu [1] dodaje nowa komende: ";
const string ADD_MENU_ITEM = "Dodaj element";
const string DELETE_MENU_ITEM = "Usun element";
const string ADD_MENU_ITEM_COMMAND = "add";
const string DELETE_MENU_ITEM_COMMAND = "delete";
const string ADD_CTABLE_TEXT = "dodawanie tabeli w CTable";
const string SHOW_CTABLE_TEXT = "wyswietlanie tabeli w CTable";
const string SET_CELL_CTABLE_TEXT = "Ustawianie wartosci tabeli w CTable";
const string REMOVE_CTABLE_TEXT = "Usuwanie tabeli w CTable";
const string REMOVE_ALL_CTABLE_TEXT = "Usuwanie wszystkich tabeli w CTable";
const string SET_LENGTH_CTABLE_TEXT = "ustawianie dlugosci tabeli w CTable"; 
const string SET_NAME_CTABLE_TEXT = "ustawianie nazwy tabeli w CTable";
const string COPY_CTABLE = "kopiowanie wartosci tabeli w CTable";
const string BACK_COMMAND = "back";
const string MAIN_MENU_NAME = "Menu glowne";
const string MAIN_MENU_COMMAND = "main";
const string DEFAULT_MENU = "Komenda domyslna";
const string DEFAULT_MENU_COMMAND = "default";
const string DEFAULT_ALA_TEXT = "Napisz Ala ma kota";
const string DEFAULT_ALA_COMMAND = "ala";
const string ALA_TEXT = "Ala ma kota!";
const string ALA_DESCRIPTION = "wyswietla napisa Ala ma kota";
const string PATH_TO_SAVE = "C://Users//Dominik//Desktop//save.txt";
const string CORRECT_LOAD = "Plik zostal wczytany poprawnie";
const string CORRECT_SAVE = "Plik zostal zapisany poprawnie";
const string ERROR_LOAD = "Blad podczas wczytywanie pliku!";
const string SAVE_ERROR = "Blad podczas zapisu pliku!";
const string POINTS = ":";
const string EMPTY_STRING = "";
const string HELP_COMMAND = "help";
const string SEARCH_COMMAND = "search";
const string NO_COMMAND = "brak komendy";
const string COMMAND_NOT_SET = "komenda nie zostala ustawiona";
const string LOAD_ERROR = "Blad podczas wczytywania! ";
const string LOAD_ERROR_POS = "index: ";
const string LOAD_ERROR_EXPECTED = "spodziewany znak: ";
const string LOAD_ERROR_SIGN = "wczytany znak: ";
const string COMMANDS_NOT_FOUND = "Nie znaleziono komendy";
const string ARROW = " -> ";

const int ADD_MENU = 0;
const int ADD_COMMAND = 1;

class CMenuItem
{
public:
	virtual ~CMenuItem() {};

	virtual void vRun() = 0;
	virtual string sGetName() = 0;
	virtual string sGetCommand() = 0;
	virtual string sGetDescription() { return s_name; };
	virtual void vSetRoot(CMenuItem * root) {};
	void vSetPath(string sPath);
	string sGetPath();

protected:
	string s_command;
	string s_name;
	string s_path;
};
#endif
