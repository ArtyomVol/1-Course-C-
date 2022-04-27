#include <iostream>
#include <fstream>
#include <iomanip>
const int NotUsed = system("color F0");
using namespace std;
#define N 6

int menu();
double** input(double** pm, int M);// ф-ция заполняет матрицу (двумерный массив) значениями из файла
double** creating_matrix(int M);// ф-ция создаёт матрицу (двумерный массив), с пользовательским размером
int matrix_dimension();// ф-ция возвращает размерность матрицы (число), вводимую пользователем
void matrix_print(double** pm, int M);// ф-ция выводит на консоль матрицу (двумерный массив)
double find_min_sum(double** pm, int M);//ищет мин. сумму модулей элементов диагоналей, параллельных побочной диагонали и выводит все суммы
void output(double** pm, int M, double minsum);// запись в файл и вывод на консоль матрицу и мин. модулей элементов диагоналей, параллельных побочной диагонали

int main()
{
	setlocale(LC_ALL, "Russian");
	double minsum, ** pm = {};
	int M, choice, fl=1;
	cout << " Программа создаёт квадратную матрицу, находит минимум среди сум модулей элементов диагоналей, параллельных побочной диагонали, и выводит эту информацию в файл.\n";
	while (fl != 6)
	{
		choice = menu();
		if (fl == choice || choice >= 5)
		{
			switch (choice)
			{
			case 1:
			{
				M = matrix_dimension();
				pm = creating_matrix(M);
				fl = 2;
				break;
			}
			case 2:
			{
				pm = input(pm, M);
				matrix_print(pm, M);
				fl = 3;
				break;
			}
			case 3:
			{
				minsum = find_min_sum(pm, M);
				fl = 4;
				break;
			}
			case 4:
			{
				output(pm, M, minsum);
				fl = 5;
				break;
			}
			case 5:
			{
				cout << " До свидания.\n";
				fl = 6;
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
	cout << " Пункты меню надо выбирать по порядку (не считая 5)\n 1) Подготовка квадратной матрицы на заполнение (ввод размерности).\n";
	cout << " 2) Извлечение информации из исходного файла, и заполнение квадратной матрицы ею.\n";
	cout << " 3) Нахождение минимума среди сумм модулей элементов диагоналей, параллельных побочной диагонали.\n";
	cout << " 4) Запись полученной информации в новый файл.\n 5) Выход из программы.\n Ваш выбор : ";
	cin >> choice;
	cout << endl;
	return choice;
}

double** input(double** pm, int M)
// ф-ция заполняет матрицу (двумерный массив) значениями из файла
{
	char a, A[N];
	int i = 0, j = 0;
	ifstream infile("C:\\Users\\User\\Desktop\\ConsoleApplication2\\matrix.txt");
	if (infile)
	{
		cout << " Файл 'matrix.txt' успешно открыт.\n";
		infile.get(a);
		for (i; i < M && !(isspace(a)); i++)
		{
			for (j = 0; j < M && !(isspace(a)); j++) 
			{
				for (int k = 0; !(isspace(a)) && a != EOF; k++)
				{
					A[k] = a;
					infile.get(a);
				}
				infile.get(a);
				pm[i][j] = atof(A);
				for (int k = 0; k < N; k++)
				{
					A[k] = ' ';
				}
			}
		}
		if (j == M)
		{
			j = 0;
		}
		else
		{
			i--;
		}
		while ((i * M + j) < M * M)
		{
			for (int i0 = 0; i < M; i++, i0++)
			{
				for (int j0 = 0; j < M; j++, j0++)
				{
					pm[i][j] = pm[i0][j0];
				}
				j = 0;
			}
		}
		cout << " Информация из файла 'matrix.txt' успешно извлечена.\n";
		infile.close();
	}
	else {
		cout << " Ошибка открытия файла\n";
		system("pause");
		exit(1);
	}
	return pm;
}

double** creating_matrix(int M)
// ф-ция создаёт матрицу (двумерный массив), с пользовательским размером
{
	double** pm = new double* [M];
	for (int i = 0; i < M; i++) {
		pm[i] = new double[M];
	}
	return pm;
}

int matrix_dimension()
// ф-ция возвращает размерность матрицы (число), вводимую пользователем
{
	int M;
	cout << " Введите размерность квадратной матрицы: ";
	cin >> M;
	return M;
}

void matrix_print(double** pm, int M)
// ф-ция выводит матрицу (двумерный массив)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << setw(6) << pm[i][j];
		}
		cout << endl;
	}
}

double find_min_sum(double** pm, int M)
//ищет мин. сумму модулей элементов диагоналей, параллельных побочной диагонали и выводит все суммы
{
	double sum, minsum = 999;
	cout << " Матрица:\n";
	matrix_print(pm, M);
	for (int j = 0; j < M - 1; j++) {
		sum = 0;
		for (int i = 0, j0 = j; i <= j; i++, j0--) 
		{
			sum += abs(pm[i][j0]);
		}
		cout << " Сумма модулей элементов в " << j + 1 << " диагонали параллельной побочной диагонали, и находящейся выше неё равна: " << sum << endl;
		if (sum < minsum)
		{
			minsum = sum;
		}
	}
	for (int i = 1; i < M; i++) {
		sum = 0;
		for (int j = M - 1, i0 = i; i0 < M; j--, i0++) 
		{
			sum += abs(pm[i0][j]);
		}
		cout << " Сумма модулей элементов в " << i << " диагонали параллельной побочной диагонали, и находящейся ниже неё равна: " << sum << endl;
		if (sum < minsum)
		{
			minsum = sum;
		}
	}
	cout << " Минимум среди сумм модулей элементов диагоналей, параллельных побочной диагонали матрицы равен: " << minsum << endl;
	return minsum;
}

void output(double** pm, int M, double minsum)
// запись в файл и вывод на консоль матрицу и мин. модулей элементов диагоналей, параллельных побочной диагонали
{
	ofstream outfile("C:\\Users\\User\\Desktop\\ConsoleApplication2\\information.txt");
	if (outfile) {
		cout << " Файл 'information.txt' успешно открыт. В него записывается информация:\n";
		outfile << " Матрица:\n";
		cout << " Матрица:\n";
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < M; j++)
			{
				outfile << setw(6) << pm[i][j];
				cout << setw(6) << pm[i][j];
			}
			outfile << endl;
			cout << endl;
		}
		outfile << "\n Минимум среди сумм модулей элементов диагоналей, параллельных побочной диагонали матрицы равен: " << minsum << endl;
		cout << "\n Минимум среди сумм модулей элементов диагоналей, параллельных побочной диагонали матрицы равен: " << minsum << endl;
		cout << "\n Информация в файл 'information.txt' успешно записана.\n";
	}
	else {
		cout << " Ошибка открытия файла.";
		exit(2);
	}
}