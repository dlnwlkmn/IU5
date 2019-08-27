#include <iostream>
#include <iomanip>
#include "head 9.1.h"

using namespace std;

int menu()
{
	int choice;
	cout << "����:\n\n";
	cout << "(1) ���������� �������� �������\n(2) ����\n(3) ���������\n:> ";
	cin >> choice;
	return choice;
}
void printM(double**, int);


int main()
{
	setlocale(LC_ALL, "ru");
	cout << "\t\t\t\t== ������� � ���� ==\n";

	while (true)
	{
		switch (menu())
		{
		case 1:
		{
			int n;
			cout << "////////////////////////////////////////////////////////////////////////////////";
			cout << "(1) ���������� �������� �������\n\n";
			cout << "������� ������ �������\n:>  ";
			cin >> n;

			double **Matr = new double *[n];
			for (int i = 0; i < n; i++)
				Matr[i] = new double[n];

			cout << "\n������� �������� �������\n:> ";
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					cin >> Matr[i][j];
			cout << " �������: \n";
			printM(Matr, n);

			double **Matr_Reverse = Reverse(Matr, n);
			cout << " �������� �������: \n";
			printM(Matr_Reverse, n);

			Proverka(Matr, Matr_Reverse, n);
			cout << "\n////////////////////////////////////////////////////////////////////////////////";
			break;
		}
		case 2:
		{
			cout << "////////////////////////////////////////////////////////////////////////////////";
			cout << "(2) ������� ������� ���������\n\n";
			SLAU();
			cout << "\n////////////////////////////////////////////////////////////////////////////////";
			break;
		}
		case 3:
			system("pause"); return false;
		}
	}
//	cout << "������� ������ ������� ";
//	cin >> n;
//
//	double **Matr = new double *[n];
//	for (int i = 0; i < n; i++)
//		Matr[i] = new double[n];
//
//
//	cout << "\n������� �������� �������\n";
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < n; j++)
//			cin >> Matr[i][j];
//
//
//	double **Matr_Reverse = Reverse(Matr, n);
//	cout << " �������� �������: \n";
//	printM(Matr_Reverse, n);
//	
//	Proverka(Matr, Matr_Reverse, n);                     //�������� ����������
//
////-------------------------------------------------------------------------����� II---------------------------------------------------------------------
////------------------------------------------------------------------------������� ����------------------------------------------------------------------
//	cout << "\n������� ������� ���������.\n";
//	SLAU();
	system("Pause");
	return 0;
}

void printM(double** matr, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << setw(5) << fixed << setprecision(1) << matr[i][j] << "   ";
		cout << "\n";
	}
}

//double **Reverse(double **mat, int n)
//{
//	double a, b, c;
//	double *mas = new double[2 * n];
//
//	// �������� ��������� �������
//	double **mat_ed = new double *[n];
//	for (int i = 0; i < n; i++)
//		mat_ed[i] = new double[n];
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < n; j++)
//		{
//			if (i == j) mat_ed[i][j] = 1;
//			else mat_ed[i][j] = 0;
//		}
//
//	// �������� ��������������� �������
//	double **mat_help = new double *[n];
//	for (int i = 0; i < n; i++)
//		mat_help[i] = new double[2 * n];
//
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < (2 * n); j++)
//		{
//			if (j < n)
//				mat_help[i][j] = mat[i][j];
//			else mat_help[i][j] = mat_ed[i][j - n];
//		}
//
//	// ������ ���
//	for (int k = 0; k < n; k++)                          //� ����� ����� ���������� ������� ����������� �������
//	{
//		if (mat_help[k][k] == 0)
//		{
//			for (int i = k + 1; i < n; i++)
//			{
//				if (mat_help[i][k] != 0)
//				{
//					for (int j = 0; j < n * 2; j++)
//					{
//						c = mat_help[i][j];
//						mat_help[i][j] = mat_help[k][j];
//						mat_help[k][j] = c;
//					}
//					break;
//				}
//			}
//		}
//		for (int i = k; i < n; i++)                      //��� ���������� ������(k-����) � ������������ ���������= 1 � ���������� ��� ���(����������)= 0
//		{
//			if (i == k)                                 //��������� ������(k-���) ���� ����� � ������� �� �������� �������� ��� ������������� ���������
//			{
//				for (int j = 0; j < 2 * n; j++)
//					mas[j] = mat_help[i][j];
//			}
//
//			for (int j = k; j < 2 * n; j++)                //� ����� ����� ����������������� ������
//			{
//				if (i == k)
//				{
//					if (j == k) a = mat_help[k][k];      //��������� �������� ������� �������� i-��� ������
//					mat_help[i][j] = mat_help[i][j] / a;  //����� ������ j-��� ������� i-��� ������ �� �������� ������� �������� ��� ��������� ������ �� ���������
//				}
//				else {
//					if (j == k) b = mat_help[i][j];
//					mat_help[i][j] = mat_help[i][j] - mas[j] * b / a;  //�������� �������� ��� ������������� ���������
//				}
//			}
//		}
//	}
//	// �������� ���(������ ���, ������ �������� ����� ������� ��������)
//	for (int k = n - 1; k >= 0; k--)
//		for (int i = k; i >= 0; i--)
//		{
//			if (i == k)
//			{
//				for (int j = 0; j < 2 * n; j++)
//					mas[j] = mat_help[i][j];
//			}
//
//			for (int j = k; j < 2 * n; j++)
//			{
//				if (i == k)
//				{
//					if (j == k) a = mat_help[k][k];
//					mat_help[i][j] = mat_help[i][j] / a;
//				}
//				else {
//					if (j == k) b = mat_help[i][j];
//					mat_help[i][j] = mat_help[i][j] - mas[j] * b / a;
//				}
//			}
//		}
//
//	double **mat_ob = new double*[n];
//	for (int i = 0; i < n; i++)
//		mat_ob[i] = new double[n];
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < n; j++)
//			mat_ob[i][j] = mat_help[i][j + n];
//
//	return mat_ob;
//}
//
//void Proverka(double **mat1, double **mat2, int n)
//{
//	double s;
//	double **mat = new double *[n];
//	for (int i = 0; i < n; i++)
//		mat[i] = new double[n];
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//			s = 0;
//			for (int k = 0; k < n; k++)
//				s = s + mat1[i][k] * mat2[k][j];
//			if (i == j)mat[i][j] = 1; else                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//				mat[i][j] = s;
//
//		}
//
//	}
//
//	cout << " ��������� �������� �� ��������: \n";
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n; j++)
//			cout << setw(8) << fixed << setprecision(3) << abs(mat[i][j]) << "   ";
//		cout << "\n";
//	}
//}
//
//void Proverka(double **mat1, double *mat2, int n)
//{
//	double s;
//	double *mat = new double[n];
//	for (int i = 0; i < n; i++)
//	{
//		s = 0;
//		for (int j = 0; j < n; j++)
//		{
//			s = s + mat1[i][j] * mat2[j];
//		}
//		mat[i] = s;
//	}
//
//	cout << "\n���������:\n";
//	for (int i = 0; i < n; i++)
//		cout << "x" << i + 1 << " = " << mat[i] << "\n";
//}
//
//
//void SLAU()
//{
//	int n;
//	cout << "������� ���������� ��������� � ������� - ";
//	cin >> n;
//	double **mat = new double *[n];
//	for (int i = 0; i < n; i++)
//		mat[i] = new double[n];
//
//	for (int i = 0; i < n; i++)
//	{
//		cout << "������� ������������ ���������: " << i + 1 << "\n";
//		for (int j = 0; j < n; j++)
//			cin >> mat[i][j];
//	}
//	double **mat_ob = Reverse(mat, n);
//	double *svob = new double[n];
//	cout << "������� ��������� ����� ���������:\n";
//	for (int j = 0; j < n; j++)
//		cin >> svob[j];
//	Proverka(mat_ob, svob, n);
//}