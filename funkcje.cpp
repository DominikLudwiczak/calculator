#include "funkcje.h"

vector<string> split(string &wyrazenie)
{
	vector<string> array;
	for (int i = 0; i < wyrazenie.length(); i++)
	{
		string pom;
		bool check = false;
		if (wyrazenie[i] != '+' && wyrazenie[i] != '-' && wyrazenie[i] != '*' && wyrazenie[i] != '/')
		{
			for (int j = i; j < wyrazenie.length(); j++)
			{
				if (wyrazenie[j] != '+' && wyrazenie[j] != '-' && wyrazenie[j] != '*' && wyrazenie[j] != '/')
				{
					if (wyrazenie[j] == 'p' && wyrazenie[j + 1] == 'o' && wyrazenie[j + 2] == 'w')
					{
						pom += "p(";
						array.push_back(pom);
						pom = "";
						check = true;
						j = i + 3;
					}
					else if (wyrazenie[j] == 's' && wyrazenie[j + 1] == 'q' && wyrazenie[j + 2] == 'r' && wyrazenie[j + 3] == 't')
					{
						pom += "s(";
						array.push_back(pom);
						pom = "";
						check = true;
						j = i + 4;
					}
					else if (wyrazenie[j] == ',')
					{
						array.push_back(pom);
						array.push_back(",");
						pom = "";
					}
					else if (wyrazenie[j] == ')')
					{
						array.push_back(pom);
						pom = "";
						pom += ")";
						check = false;
					}
					else
						pom += wyrazenie[j];
				}
				else if (check == true)
				{
					pom += wyrazenie[j];
				}
				else if(check == false)
				{
					i = j - 1;
					break;
				}

				if (wyrazenie[j + 1] == NULL)
					i = j;
			}
		}
		else
			pom = wyrazenie[i];
		array.push_back(pom);
	}
	return array;
}

bool is_num(string str)
{
	bool check = true;
	for (int i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]) && str[i] != '.')
			check = false;
	}
	return check;
}

void zamiana(vector<string> &array, int i, float &wynik)
{
	vector<string> wyrazenie_split = split(array.at(i));
	string wyrazenie;
	for (int x = 0; x < wyrazenie_split.size(); x++)
	{
		wyrazenie += wyrazenie_split.at(x);
	}
	array.at(i) = licz(wyrazenie, wynik)[0];
}

float* mat(vector<string> &array, int j, float &wynik)
{
	float p = 0;
	float wynik_posredni(0);
	for (int i = j; i < array.size(); i++)
	{
		bool num = is_num(array.at(i + 1));
		bool num2 = true;
		if(array.at(i)=="p(")
			num2 = is_num(array.at(i + 3));
		if (num == false)
		{
			zamiana(array, i + 1, wynik);
			i = j - 1;
		}
		else if (num2 == false)
		{
			zamiana(array, i + 3, wynik);
			i = j - 1;
		}
		else
		{
			float pierwsza = atof(array.at(i + 1).c_str());
			if (array.at(i) == "p(")
			{
				float druga = atof(array.at(i + 3).c_str());
				wynik_posredni = pow(pierwsza, druga);
				i += 4;
			}
			else
			{
				wynik_posredni = sqrt(pierwsza);
				i += 2;
			}
			p = (float)i;
			break;
		}
	}
	float tab[2] = { p, wynik_posredni };
	return tab;
}

string* licz(string &wyrazenie, float &aktualny_wynik)
{
	float wynik(0);
	string akcja;
	vector<string> array = split(wyrazenie);
	for (int i = 0; i < array.size(); i++)
	{
		if (array.at(i) != "+" && array.at(i) != "-" && array.at(i) != "*" && array.at(i) != "/")
		{
			if (array.at(i) == "p(" || array.at(i) == "s(")
			{
				wynik = mat(array, i, aktualny_wynik)[1];
				i = mat(array, i, aktualny_wynik)[0];
				akcja = "+";
			}
			else
			{
				float pierwsza = atof(array.at(i).c_str());
				float druga(0);
				if (i + 2 <= array.size() - 1)
				{
					if (array.at(i + 2) == "p(" || array.at(i + 2) == "s(")
					{
						int j = i + 2;
						druga = mat(array, j, aktualny_wynik)[1];
					}
					else
						druga = atof(array.at(i + 2).c_str());
				}
				else
					break;
				if (array.at(i + 1) == "+")
				{
					wynik = pierwsza + druga; 
					akcja = "+";
				}
				if (array.at(i + 1) == "-")
				{
					wynik = druga - pierwsza;
					akcja = "-";
				}
				if (array.at(i + 1) == "*")
				{
					wynik = pierwsza * druga;
					akcja = "*";
				}
				if (array.at(i + 1) == "/")
				{
					if (druga == 0)
						cout << "Nie mozna dzielic przez 0!" << endl;
					else
					{
						wynik = pierwsza / druga;
						akcja = "/";
					}
				}
				i += 2;
			}
		}
		else
		{
			float pierwsza;
			if (array.at(i + 1) != "p(" && array.at(i + 1) != "s(")
				pierwsza = atof(array.at(i + 1).c_str());
			if (array.at(i) == "+")
			{
				if (array.at(i + 1) == "p(" || array.at(i + 1) == "s(")
				{
					int j = i + 1;
					wynik += mat(array, j, aktualny_wynik)[1];
					i = mat(array, j, aktualny_wynik)[0] - 1;
				}
				else
					wynik += pierwsza;
				akcja = "+";
			}
			if (array.at(i) == "-")
			{
				if (array.at(i + 1) == "p(" || array.at(i + 1) == "s(")
				{
					int j = i + 1;
					wynik = mat(array, j, aktualny_wynik)[1] - wynik;
					i = mat(array, j, aktualny_wynik)[0] - 1;
				}
				else
					wynik = pierwsza - wynik;
				akcja = "-";
			}
			if (array.at(i) == "*")
			{
				wynik = 1;
				if (array.at(i + 1) == "p(" || array.at(i + 1) == "s(")
				{
					int j = i + 1;
					wynik *= mat(array, j, aktualny_wynik)[1];
					i = mat(array, j, aktualny_wynik)[0] - 1;
				}
				else
					wynik *= pierwsza;
				akcja = "*";
			}
			if (array.at(i) == "/")
			{
				wynik = aktualny_wynik;
				if (array.at(i + 1) == "p(" || array.at(i + 1) == "s(")
				{
					int j = i + 1;
					wynik /= mat(array, j, aktualny_wynik)[1];
					i = mat(array, j, aktualny_wynik)[0] - 1;
				}
				else
				{
					if (pierwsza == 0)
						cout << "Nie mozna dzielic przez 0!" << endl;
					else
						wynik /= pierwsza;
				}
				akcja = "/";
			}
			i += 1;
		}
	}
	string* tab = new string[2];
	tab[0] = to_string(wynik);
	tab[1] = akcja;
	return tab;
}

void wylicz(string &wyrazenie, float &wynik, vector<string> &historia)
{
	string akcja = licz(wyrazenie, wynik)[1];
	string wartosc = licz(wyrazenie, wynik)[0];
	if (akcja == "+")
		wynik += atof(wartosc.c_str());
	if (akcja == "-")
		wynik -= atof(wartosc.c_str());
	if (akcja == "*")
	{
		if (historia.size() == 1)
			wynik = 1;
		wynik *= atof(wartosc.c_str());
	}
	if (akcja == "/")
		wynik = atof(wartosc.c_str());
	historia.push_back(to_string(wynik));
}