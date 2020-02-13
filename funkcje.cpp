#include "funkcje.h"

bool check_minus = false;
vector<string> split(string &wyrazenie)
{
	vector<string> array;
	int counter = 0;
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
						pom += "p[";
						array.push_back(pom);
						pom = "";
						check = true;
						j = i + 3;
					}
					else if (wyrazenie[j] == 's' && wyrazenie[j + 1] == 'q' && wyrazenie[j + 2] == 'r' && wyrazenie[j + 3] == 't')
					{
						pom += "s[";
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
					else if (wyrazenie[j] == '(' && check == false)
					{
						pom += "(";
						counter++;
						pom += to_string(counter);
						array.push_back(pom);
						pom = "";
						j = i++;
					}
					else if (wyrazenie[j] == ')')
					{
						array.push_back(pom);
						pom = "";
						if (check == true)
						{
							pom += "]";
							check = false;
						}
						else
						{
							pom += ")";
							pom += to_string(counter);
							counter--;
						}
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
		if(array.at(i)=="p[")
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
			if (array.at(i) == "p[")
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

void nawiasy(vector<string> &array, int i, float &wynik)
{
	string wyrazenie;
	vector<string>::iterator p1 = array.begin();
	vector<string>::iterator p2 = array.begin();
	int j = 0;
	string counter;
	for (int j = 1; j < array[i].length(); j++)
		counter += array.at(i)[j];
	while (j < i)
	{
		j++;
		p1++;
		p2++;
	}
	for (int j = i+1; j < array.size(); j++)
	{
		p2++;
		string w = ")" + counter;
		if (array.at(j) == w)
			break;
		else
		{
			if (array.at(j)[0] == ')')
				wyrazenie += ")";
			else if (array.at(j)[0] == '(')
				wyrazenie += "(";
			else
				wyrazenie += array.at(j);
		}
	}
	string wynik_posredni = licz(wyrazenie, wynik)[0];
	array.erase(p1, p2);
	array.at(i) = wynik_posredni;
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
			if (array.at(i) == "p[" || array.at(i) == "s[")
			{
				wynik = mat(array, i, aktualny_wynik)[1];
				i = mat(array, i, aktualny_wynik)[0];
				akcja = "+";
			}
			if (array.at(i)[0] == '(')
			{
				nawiasy(array, i, aktualny_wynik);
				i = -1;
			}
			else
			{
				float pierwsza = atof(array.at(i).c_str());
				float druga(0);
				if (i + 2 <= array.size() - 1)
				{
					if (array.at(i + 2) == "p[" || array.at(i + 2) == "s[")
					{
						int j = i + 2;
						druga = mat(array, j, aktualny_wynik)[1];
					}
					else if (array.at(i + 2)[0] == '(')
					{
						nawiasy(array, i+2, aktualny_wynik);
						i = -1;
					}
					else
						druga = atof(array.at(i + 2).c_str());
				}
				else
					break;
				if (i > -1)
				{
					if (array.at(i + 1) == "+")
					{
						wynik = pierwsza + druga;
						akcja = "+";
					}
					if (array.at(i + 1) == "-")
					{
						if (check_minus == true)
							wynik = druga - pierwsza;
						else
							wynik = pierwsza - druga;
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
		}
		else
		{
			if (array.at(i+1)[0] == '(')
			{
				nawiasy(array, i + 1, aktualny_wynik);
				i = -1;
			}
			else
			{
				float pierwsza;
				if (array.at(i + 1) != "p[" && array.at(i + 1) != "s[")
					pierwsza = atof(array.at(i + 1).c_str());
				if (array.at(i) == "+")
				{
					if (array.at(i + 1) == "p[" || array.at(i + 1) == "s[")
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
					if (array.at(i + 1) == "p[" || array.at(i + 1) == "s[")
					{
						int j = i + 1;
						wynik = mat(array, j, aktualny_wynik)[1] - wynik;
						i = mat(array, j, aktualny_wynik)[0] - 1;
					}
					else
					{
						if (check_minus == true)
							wynik -= pierwsza;
						else
							wynik = pierwsza - wynik;
					}
					akcja = "-";
				}
				if (array.at(i) == "*")
				{
					if (array.at(i + 1) == "p[" || array.at(i + 1) == "s[")
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
					if (array.at(i + 1) == "p[" || array.at(i + 1) == "s[")
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
	}
	string* tab = new string[2];
	tab[0] = to_string(wynik);
	tab[1] = akcja;
	return tab;
}

void wylicz(string &wyrazenie, float &wynik, vector<string> &historia)
{
	check_minus = false;
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