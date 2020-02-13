#include <iostream>
#include <vector>
#include <sstream>
#include <windows.h>
#include <cmath>
#include <cctype>
#include <algorithm>
using namespace std;

//funkcja split do rozbicia wyrazenia z vectora
vector<string> split(string &wyrazenie);

//funkcja zliczaj¹ca wartoœæ danego wyra¿enia
string* licz(string &wyrazenie, float &aktualny_wynik);

//funkcja zliczaj¹ca koñcowy wynik
void wylicz(string &wyrazenie, float &wynik, vector<string> &historia);

//funkcja odpowiadajaca za liczenie pierwiastkow i poteg
float* mat(vector<string> &array, int j, float &wynik);

//funkcja sprawdzaj¹ca czy string jest liczb¹
bool is_num(string str);

//funkcja zamieniaj¹ca wyrazenie na wynik podczas pierwistkowania i potegowania
void zamiana(vector<string> &array, int i, float &wynik);

//funkcja wyliczaj¹ca wartoœæ z nawiasów
void nawiasy(vector<string> &array, int i, float &wynik);