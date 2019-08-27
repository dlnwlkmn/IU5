#include <iostream>
#include <iomanip>
using namespace std;

//double **Reverse(double **Matr, int n)
//{
//	double a, b, c;
//	double *str = new double[2 * n];		//������ ��� ���������
//
//	// �������� ��������� �������
//	double **Matr_Ed = new double *[n];
//	for (int i = 0; i < n; i++)
//		Matr_Ed[i] = new double[n];
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < n; j++)
//		{
//			if (i == j) Matr_Ed[i][j] = 1;
//			else Matr_Ed[i][j] = 0;
//		}
//
//	// �������� ��������������� �������
//	double **Matr_Rashir = new double *[n];
//	for (int i = 0; i < n; i++)
//		Matr_Rashir[i] = new double[2 * n];
//
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < (2 * n); j++)
//		{
//			if (j < n)
//				Matr_Rashir[i][j] = Matr[i][j];
//			else Matr_Rashir[i][j] = Matr_Ed[i][j - n];
//		}
//
//	// ������ ���
//	for (int i = 0; i < n; i++)                          //� ����� ����� ���������� ������� ����������� �������
//	{
//		if (Matr_Rashir[i][i] == 0)
//		{
//			for (int j = i + 1; j < n; j++)
//			{
//				if (Matr_Rashir[j][i] != 0)
//				{
//					for (int k = 0; k < n * 2; k++)
//					{
//						c = Matr_Rashir[j][k];
//						Matr_Rashir[j][k] = Matr_Rashir[i][k];
//						Matr_Rashir[i][k] = c;
//					}
//					break;
//				}
//			}
//		}
//		for (int j = i; j < n; j++)                      //��� ���������� ������(k-����) � ������������ ���������= 1 � ���������� ��� ���(����������)= 0
//		{
//			if (j == i)                                 //��������� ������(k-���) ���� ����� � ������� �� �������� �������� ��� ������������� ���������
//			{
//				for (int k = 0; k < 2 * n; k++)
//					str[k] = Matr_Rashir[j][k];
//			}
//
//			for (int k = i; k < 2 * n; k++)                //� ����� ����� ����������������� ������
//			{
//				if (j == i)
//				{
//					if (k == i) a = Matr_Rashir[i][i];      //��������� �������� ������� �������� i-��� ������
//					Matr_Rashir[j][k] = Matr_Rashir[j][k] / a;  //����� ������ j-��� ������� i-��� ������ �� �������� ������� �������� ��� ��������� ������ �� ���������
//				}
//				else {
//					if (k == i) b = Matr_Rashir[j][k];
//					Matr_Rashir[j][k] = Matr_Rashir[j][k] - str[k] * b / a;  //�������� �������� ��� ������������� ���������
//				}
//			}
//		}
//	}
//	// �������� ���(������ ���, ������ �������� ����� ������� ��������)
//	for (int i = n - 1; i >= 0; i--)
//		for (int j = i; j >= 0; j--)
//		{
//			if (j == i)
//			{
//				for (int k = 0; k < 2 * n; k++)
//					str[k] = Matr_Rashir[j][k];
//			}
//
//			for (int k = i; k < 2 * n; k++)
//			{
//				if (j == i)
//				{
//					if (k == i) a = Matr_Rashir[i][i];
//					Matr_Rashir[i][k] = Matr_Rashir[j][k] / a;
//				}
//				else {
//					if (k == i) b = Matr_Rashir[j][k];
//					Matr_Rashir[i][k] = Matr_Rashir[j][k] - str[k] * b / a;
//				}
//			}
//		}
//
//	double **mat_ob = new double*[n];
//	for (int i = 0; i < n; i++)
//		mat_ob[i] = new double[n];
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < n; j++)
//			mat_ob[i][j] = Matr_Rashir[i][j + n];
//
//	return mat_ob;
//}




double** Reverse(double** Matr, int n)
{
	double a, b, c;
	double *arr = new double[2 * n];

	double **Matr_Ed = new double *[n];				//���������
	for (int i = 0; i < n; i++)
		Matr_Ed[i] = new double[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j) Matr_Ed[i][j] = 1;
			else Matr_Ed[i][j] = 0;
		}

	double **Matr_Rashir = new double *[n];			//����������� (���������������)
	for (int i = 0; i < n; i++)
		Matr_Rashir[i] = new double[2 * n];

	for (int i = 0; i < n; i++)						//���������� ����������� �������
		for (int j = 0; j < (2 * n); j++)
		{
			if (j < n)
				Matr_Rashir[i][j] = Matr[i][j];
			else Matr_Rashir[i][j] = Matr_Ed[i][j - n];
		}

	for (int i = 0; i < n; i++)                         //������ ��� (� ����� ���������� �������� ����������� �������) 
	{
		if (Matr_Rashir[i][i] == 0)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (Matr_Rashir[j][i] != 0)
				{
					for (int k = 0; k < n * 2; k++)
					{
						c = Matr_Rashir[j][k];
						Matr_Rashir[j][k] = Matr_Rashir[i][k];
						Matr_Rashir[i][k] = c;
					}
					break;
				}
			}
		}
		for (int j = i; j < n; j++)                      //��� ���������� ������ (i-����) � ������������ ���������= 1 � ���������� ��� ���(����������)= 0
		{
			if (j == i)                                 //��������� ������ (i-���) ��� ��������� ��������� ��� ������� ���������� (� ���������)
			{
				for (int k = 0; k < 2 * n; k++)
					arr[k] = Matr_Rashir[j][k];
			}

			for (int k = i; k < 2 * n; k++)                //� ������ i-�� �������� (�������� for) ��� ����������������� ������
			{
				if (j == i)
				{
					if (k == i)
						a = Matr_Rashir[i][i];      //��������� �������� ������� �������� j-��� ������
					Matr_Rashir[j][k] = Matr_Rashir[j][k] / a;  //����� ������ k-��� ������� j-��� ������ �� �������� ������� �������� ��� ��������� ������ �� ������� ���������
				}
				else
				{
					if (k == i)
						b = Matr_Rashir[j][k];
					Matr_Rashir[j][k] = Matr_Rashir[j][k] - arr[k] * b / a;  //�������� �������� ��� ������� ���������� 
				}
			}
		}
	}

	for (int i = n - 1; i >= 0; i--)					//�������� ��� (�������� ������ ������� ��������)
		for (int j = i; j >= 0; j--)
		{
			if (j == i)
			{
				for (int k = 0; k < 2 * n; k++)
					arr[k] = Matr_Rashir[j][k];
			}

			for (int k = i; k < 2 * n; k++)
			{
				if (j == i)
				{
					if (k == i) a = Matr_Rashir[i][i];
					Matr_Rashir[j][k] = Matr_Rashir[j][k] / a;
				}
				else {
					if (k == i) b = Matr_Rashir[j][k];
					Matr_Rashir[j][k] = Matr_Rashir[j][k] - arr[k] * b / a;
				}
			}
		}
	double **Reverse_Matr = new double*[n];
	for (int i = 0; i < n; i++)
		Reverse_Matr[i] = new double[n];
	for (int i = 0; i < n; i++)				//�������� �������� ������� � �� ���������������� � ����� ������
		for (int j = 0; j < n; j++)
			Reverse_Matr[i][j] = Matr_Rashir[i][j + n];

	return Reverse_Matr;

	
}

void Proverka(double **Matr1, double **Matr2, int n)
{
	double s;
	double **Matr_Ed = new double *[n];
	for (int i = 0; i < n; i++)
		Matr_Ed[i] = new double[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			s = 0;
			for (int k = 0; k < n; k++)
				s = s + Matr1[i][k] * Matr2[k][j];							//�������� "������ �� �������"
			if (i == j)Matr_Ed[i][j] = 1; else               
				Matr_Ed[i][j] = s;

		}

	}

	cout << " ��������� �������� �� ��������: \n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << setw(8) << fixed << setprecision(2) << abs(Matr_Ed[i][j]) << "   ";
		cout << "\n";
	}
}

void Korny(double **Matr1, double *Matr2, int n)
{
	double s;
	double *Korni = new double[n];
	for (int i = 0; i < n; i++)
	{
		s = 0;
		for (int j = 0; j < n; j++)
		{
			s = s + Matr1[i][j] * Matr2[j];
		}
		Korni[i] = s;
	}

	cout << "\n����� ����:\n";
	for (int i = 0; i < n; i++)
		cout << "x" << i + 1 << " = " << Korni[i] << "\n";
}


void SLAU()
{
	int n;
	cout << "������� ���������� ��������� � �������\n:> ";
	cin >> n;
	double **Matr_Koef = new double *[n];					//������� ������������
	for (int i = 0; i < n; i++)
		Matr_Koef[i] = new double[n];

	for (int i = 0; i < n; i++)
	{
		cout << "������� ������������ " << i + 1 << "-�� ���������\n(" << n << " ��.):> ";
		for (int j = 0; j < n; j++)
			cin >> Matr_Koef[i][j];
	}
	double **Matr_Koef_Reverse = Reverse(Matr_Koef, n);		//������� �������� ������� ������������
	double *Svobodnye = new double[n];						//������ ��������� ������
	cout << "������� ��������� ����� ���������\n:> ";
	for (int j = 0; j < n; j++)
		cin >> Svobodnye[j];
	Korny(Matr_Koef_Reverse, Svobodnye, n);
}