#include <iostream>
#include <fstream>
#include <iomanip>
const int NL = 3, NS = 200, NW = 12;
const int NotUsed = system("color F0");
using namespace std;

struct list
{
  int wlen; // длина слова
  int num_sogl; // к-во согласных
  char word[NW]; // слово
  int fl=0; // меньше ли количество согл. букв заданного значения
  list *pnext; // указатель на следующий элемент
};

int menu();
int input(char* pt); // ф-ция считывает информацию и возвращает длину текста
void nl_ns_nw(int* pnl, int* pns, int* pnw, char a); // проверка условия лимита количества символов
int taking_number(char text[]);// ф-ция возвращает значение заданное в файле
void processing(list** begin, char text[], int len_text);// ф-ция заносит слова, их длинну и количество согласных букв в однонаправленный список
void print_list(list* begin);// ф-ция выводит состояние списка на экран
bool rus_letter(char a);// Является ли заданный символ русской буквой
bool rus_sogl_letter(char a);// Является ли заданный символ русской согласной буквой
void scan_sogl_letter(list* inform, int min_num_sogl); // Ф-ция сравнивает количество согласных букв в слове, с заданным значением, и выводит слова, у которых количество больше.
void output(char* pt, list* inform, int len_text, int min_num_sogl); // Функция записывает информацию в файл

int main() 
{
	setlocale(LC_ALL, "Russian");
	list* begin = NULL;
	int len_text, choice, fl=1, min_num_sogl;
	char inform[NL * NS], *pt=&inform[0];
	cout << " Программа, по извлечению текста из файла, поиску слов, количество согласных букв в которых не меньше заданного числа в 1 строке файла.\n\n";
	while (fl != 6)
	{
		choice = menu();
		if (fl == choice || choice>=5)
		{
			switch (choice)
			{
			case 1:
			{
				len_text = input(pt);
				min_num_sogl = taking_number(pt);
				fl = 2;
				break;
			}
			case 2:
			{
				processing(&begin, inform, len_text);
				print_list(begin);
				fl = 3;
				break;
			}
			case 3:
			{
				scan_sogl_letter(begin, min_num_sogl);
				fl = 4;
				break;
			}
			case 4:
			{
				output(pt, begin, len_text, min_num_sogl);
				fl = 5;
				break;
			}
			case 5:
			{
				fl = 6;
				cout << " До свидания.\n";
				break;
			}
			default:
				cout << " Данного пункта нет в меню.\n\n";
				break;
			}
		}
		else
		{
			cout << " Пункты меню надо выбирать по порядку.\n\n";
		}
	}
	system("pause");
	return 0;
}

int menu()
{
	system("pause");
	system("cls");
	int choice;
	cout << " Пункты меню надо выбирать по порядку (не считая 5)\n 1) Извлечение информации из исходного файла.\n";
	cout << " 2) Запись слов, их длины, к - во согласных букв из текста в линейный список.\n";
	cout << " 3) Нахождение слов, количество согласных букв в которых не меньше заданного значения.\n";
	cout << " 4) Запись полученной информации в новый файл.\n 5) Выход из программы\n Ваш выбор : ";
	cin >> choice;
	cout << endl;
	return choice;
}

int input(char* pt) 
// ф-ция считывает информацию (текст записывается по указателю) и возвращает длину текста
{
	int nl=0, ns=0, nw=0, *pnl=&nl, *pns = &ns, *pnw = &nw;
	bool f = false;
	ifstream infile("C:\\Users\\User\\Desktop\\ConsoleApplication1\\original text.txt");
	if (infile)
	{
		cout << " Файл 'original text.txt' успешно открыт.\n";
		int i = 0;
		char a;
		cout << " Текст файла:\n\n";
		while (infile.get(a))
		{
			if (!(isdigit(a)))
			{
				f = true;
			}
			if (f)
			{
				try
				{
					nl_ns_nw(pnl, pns, pnw, a);
				}
				catch (int a)
				{
					cout << "\n Ошибка:";
					switch (a)
					{
					case 1:
						cout << " в тексте есть хотя бы одно слово, длина которого превышает " << NW << " символов.";
						break;
					case 2:
						cout << " в тексте есть хотя бы одна строка, длина которой превышает " << NS << " символов.";
						break;
					case 3:
						cout << " количество строк в тексте превышает " << NL << ".";
						break;
					}
					cout << endl;
					exit (3);
				}
			}
			*(pt + i) = a;
			cout << a;
			i++;
		}
		if (a != '.' && a != '!' && a != '?')
		{
			cout << "\n Ошибка: текст заканчивается не точкой ('?','!')." << endl;
			exit(3);
		}
		cout << "\n\n Информация из файла 'original text.txt' успешно извлечена.\n\n";
		infile.close();
		return i;
	}
	else {
		cout << " Ошибка открытия файла\n";
		system("pause");
		exit(1);
	}
}

int taking_number(char text[])
// ф-ция возвращает значение заданное в файле
{
	int min_num_sogl=0, i = 0;
	char num[1];
	for (i; isdigit(text[i]); i++)
	{
		num[0] = text[i];
		min_num_sogl = min_num_sogl*10 + atoi(num);
	}
	return min_num_sogl;
}

void nl_ns_nw(int* pnl, int* pns, int* pnw, char a) 
// проверка условия лимита количества символов
{
	int nl = *pnl, ns = *pns, nw = *pnw;
	if (rus_letter(a))
	{
		nw++;
		ns++;
	}
	else
	{
		if (nw > NW)
		{
			throw 1;
		}
		nw = 0;
		if (a == '\n')
		{
			if (ns > NS)
			{
				throw 2;
			}
			ns = 0;
			nl++;
		}
		else
		{
			ns++;
		}
	}
	if (nl > NL)
	{
		throw 3;
	}
	*pnl = nl, *pns = ns, *pnw = nw;
}

void processing(list** begin, char text[], int len_text)
// ф-ция заносит слова, их длинну и количество согласных букв в однонаправленный список
{
	*begin = new list;
	(*begin)->pnext = NULL;
	list* end = *begin;
	int len, num_sogl;
	for (int i = 0; i < len_text; i++)
	{
		end->pnext = new list;
		if (rus_letter(text[i]))
		{
			len = 0;
			num_sogl = 0;
			while (rus_letter(text[i]))
			{
				end->word[len] = text[i];
				if (rus_sogl_letter(text[i]))
				{
					num_sogl++;
				}
				len++;
				i++;
			}
			end->num_sogl = num_sogl;
			end->wlen = len;
			end = end->pnext;
			end->pnext = NULL;
		}
	}
}

void print_list(list* begin)
// ф-ция выводит состояние списка на экран
{
	list*print = begin;
	cout << " Cостояние сформированного линейного списка:\n";
	cout << " (слово | количество согласных букв в слове) ->\n";
	for (int i = 0; print->pnext; i++)
	{
		cout << " ( ";
		for (int j = 0; j < print->wlen; j++)
		{
			cout << print->word[j];
		}
		cout << " | " << print->num_sogl << " ) -> ";
		print = print->pnext;
	}
	cout << "NULL\n\n";
}

bool rus_letter(char a)
// Является ли заданный символ русской буквой
{
	char letters[64] = { 'а','б','в','г','д','е','ё','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я','А','Б','В','Г','Д','Е','Ё','Ж','З','И','Й','К','Л','М','Н','О','П','Р','С','Т','У','Ф','Х','Ц','Ч','Ш','Щ','Ы','Э','Ю','Я' };
	for (int i = 0; i < 64; i++)
	{
		if (a == letters[i])
		{
			return true;
		}
	}
	return false;

}

bool rus_sogl_letter(char a)
// Является ли заданный символ русской согласной буквой
{
	char letters[42] = { 'б','в','г','д','ж','з','й','к','л','м','н','п','р','с','т','ф','х','ц','ч','ш','щ','Б','В','Г','Д','Ж','З','Й','К','Л','М','Н','П','Р','С','Т','Ф','Х','Ц','Ч','Ш','Щ' };
	for (int i = 0; i < 42; i++)
	{
		if (a == letters[i])
		{
			return true;
		}
	}
	return false;
}

void scan_sogl_letter(list* inform, int min_num_sogl)
// Ф-ция сравнивает количество согласных букв в слове, с заданным значением, и выводит слова, у которых количество больше.
{
	list* words = inform;
	bool f = false;
	while (words->pnext)
	{
		if (words->num_sogl > min_num_sogl)
		{
			if (f)
			{
				cout << ", ";
			}
			else
			{
				cout << " Слова, количество согласных букв в которых больше " << min_num_sogl << ": ";
			}
			for (int i = 0; i < words->wlen; i++)
			{
				cout << words->word[i];
			}
			f = true;
			words->fl = 1;
		}
		words = words->pnext;
	}
	if (!f)
	{
		cout << " В тексте нет слов, в которых количество согласных букв больше чем " << min_num_sogl;
		inform->fl = 2;
	}
	cout << ".\n\n";
}

void output(char* pt, list* inform, int len_text, int min_num_sogl)
// Функция записывает информацию в файл
{
	list* print = inform;
	bool f = false;
	ofstream outfile("C:\\Users\\User\\Desktop\\ConsoleApplication1\\new text.txt");
	if (outfile) {
		cout << " Файл 'new text.txt' успешно открыт. В него записывается информация:\n";
		outfile << " Исходный файл:\n";
		cout << " Исходный файл:\n";
		for (int i = 0; i < len_text; i++)
		{
			outfile << *(pt + i);
			cout << *(pt + i);
		}
		outfile << "\n\n Cостояние сформированного линейного списка:\n";
		cout << "\n\n Cостояние сформированного линейного списка:\n";
		outfile << " (слово | количество согласных букв в слове) ->\n";
		cout << " (слово | количество согласных букв в слове) ->\n";
		for (int i = 0; print->pnext; i++)
		{
			outfile << " ( ";
			cout << " ( ";
			for (int j = 0; j < print->wlen; j++)
			{
				outfile << print->word[j];
				cout << print->word[j];
			}
			outfile << " | " << print->num_sogl << " ) -> ";
			cout << " | " << print->num_sogl << " ) -> ";
			print = print->pnext;
		}
		outfile << "NULL\n\n";
		cout << "NULL\n\n"; 
		print = inform;
		if (print->fl == 2)
		{
			cout << " В тексте нет слов, в которых количество согласных букв больше чем " << min_num_sogl;
		}
		else
		{
			outfile << " Слова, количество согласных букв в которых больше " << min_num_sogl << ": ";
			cout << " Слова, количество согласных букв в которых больше " << min_num_sogl << ": ";
			while (print->pnext)
			{
				if (print->fl)
				{
					if (f)
					{
						outfile << ", ";
						cout << ", ";
					}
					for (int i = 0; i < print->wlen; i++)
					{
						outfile << print->word[i];
						cout << print->word[i];
					}
					f = true;
				}
				print = print->pnext;
			}
		}
		outfile << ".\n";
		cout << ".\n\n Информация в файл 'new text.txt' успешно записана.\n";
	}
	else {
		cout << " Ошибка открытия файла.";
		exit(2);
	}
}