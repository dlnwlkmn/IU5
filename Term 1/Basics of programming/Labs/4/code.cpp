#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	int j = 1, l = 0;
	char exit1, exit2, koef;
	double f1, f2;
	cout << "����� ������ ��������� x-cos(x)\n '������� ������� ���������'\n '������� �������'\n '������� ����������� �������' \n";
	do {
		int i, k;
		double x, a, b, c, eps;
		cout << " \n" << j << "." << l << ")\n" << " \n";
		cout << "������� �������� ����������: ";
		cin >> eps;
		cout << "������� ������� �� ��� Ox (a,b): ";
		cin >> a >> b;
		cout << " \n";
		if (a == b)														//��������� ��������
		{
			cout << "a �� ������ ���� ����� b, ������� ������!";
			system("pause");
			return 0;
		}
		if (a > b)
		{
			cout << "a ������ ���� ������ b, ������� ������!";
			system("pause");
			return 0;
		}																//��������� �������� *

		i = 0;															//����� �������
		x = a;
		f1 = a - cos(a);
		f2 = b - cos(b);
		if (((f1*f2) < 0))
		{
		do
		{
			x = x - ((x - cos(x)) / (sin(x) + 1));
			i++;
		} while (abs(x - cos(x)));
		cout << "(*) ����� �������: \n" << " \n";
		cout << "    ������: " << setprecision(10) << x << endl;
		cout << "    ������ �� " << i << " ���(-a;-��.) \n" << " \n";
		}
		else
			{
				cout << "(*) ����� ������� ��������: \n" << " \n";
				cout << "    ������ ���, ��� �������� ������ ��� x = 0 \n" << " \n";
			}


		i = 0;															//����� ������� ��������
		x = a;
		f1 = a - cos(a);
		f2 = b - cos(b);
		if (((f1*f2) < 0))
		{
		do
		{
			x = x - (x - cos(x));
			i++;
		} while (abs(x - cos(x)) > eps);
		cout << "(*) ����� ������� ��������: \n" << " \n";
		cout << "    ������: " << setprecision(10) << x << endl;
		cout << "    ������ �� " << i << " ���(-�;-��.) \n" << " \n";
		}
		else
			{
				cout << "(*) ����� ������� ��������: \n" << " \n";
				cout << "    ������ ���, ��� �������� ������ ��� x = 0 \n" << " \n";
			}


		i = 0;															//����� ����������� �������
		double z;
		f1 = a - cos(a);
		f2 = b - cos(b);
		if (((f1*f2) < 0))
		{
		do
		{
			c = (a + b) / 2;
			if (((a - cos(a))*(c - cos(c)) > 0))
				a = c;
			else
				b = c;
			z = (a + b) / 2;
			i++;
		} while (abs(b - a) > eps);
		x = z;
		cout << "(*) ����� ����������� �������: \n" << " \n";
		cout << "    ������: " << setprecision(10) << x << endl;
		cout << "    ������ �� " << i << " ���(-�;-��.)\n" << " \n";
		}
		else
			{
				cout << "(*) ����� ������� ��������: \n" << " \n";
				cout << "    ������ ���, ��� �������� ������ ��� x = 0 \n" << " \n";
			}

		cout << "    ������ ���������? (y/n) ";
		cin >> exit1;
		l++;
	} while (exit1 == 'y');
	cout << "������ ����������� � ������������ k? (y/n): ";
	cin >> koef;
	cout << " \n";

	if (koef == 'y')
	{
		l = 0;
		j = 2;
		int n = 1000;
		double f1, f2;
		cout << "����� ������ ��������� x-k*cos(x)\n '������� ������� ���������'\n '������� �������'\n '������� ����������� �������' \n";
		do {
			int i, k;
			double x, a, b, c, eps;
			cout << " \n" << j << "." << l << ")\n" << " \n";
			cout << "������� �������� ����������: ";
			cin >> eps;
			cout << "������� ���������� k: ";
			cin >> k;
			cout << "������� ������� �� ��� Ox (a,b): ";
			cin >> a >> b;
			cout << " \n";
			if (a == b)																//�������� ��������� k
			{
				cout << "a �� ������ ���� ����� b, ������� ������!";
				system("pause");
				return 0;
			}
			if (a > b)
			{
				cout << "a ������ ���� ������ b, ������� ������!";
				system("pause");
				return 0;
			}																		//�������� ��������� k *

																					//����� ������� (k)
			i = 0;
			x = a;
			f1 = a - (k*cos(a));
			f2 = b - (k*cos(b));
			if (((f1*f2) < 0))
			{
				do
				{
					x = x - ((x - (k*cos(x))) / ((k*sin(x)) + 1));
					i++;
				} while ((abs(x - (k*cos(x)))) && (i < n));
				cout << "(*) ����� �������: \n" << " \n";
				cout << "    ������: " << setprecision(10) << x << endl;
				cout << "    ������ �� " << i << " ���(-a;-��.) \n" << " \n";
			}
			else
			{
				cout << "(*) ����� ������� ��������: \n" << " \n";
				cout << "    ������ ���, ��� �������� ������ ��� x = 0 \n" << " \n";
			}


			i = 0;																	//����� ������� �������� (k)
			x = a;
			f1 = a - (k*cos(a));
			f2 = b - (k*cos(b));
			if (((f1*f2) < 0))
			{
				do
				{
					x = x - (x - (k*cos(x)));
					i++;
				} while ((abs(x - (k*cos(x))) > eps) && (i < 12));
				cout << "(*) ����� ������� ��������: \n" << " \n";
				cout << "    ������: " << setprecision(10) << x << endl;
				cout << "    ������ �� " << i << " ���(-�;-��.) \n" << " \n";
			}
			else
			{
				cout << "(*) ����� ������� ��������: \n" << " \n";
				cout << "    ������ ���, ��� �������� ������ ��� x = 0 \n" << " \n";
			}

			i = 0;																	//����� ����������� ������� (k)
			double z;
			f1 = a - (k*cos(a));
			f2 = b - (k*cos(b));
			if (((f1*f2) < 0))
			{
				do
				{
					c = (a + b) / 2;
					if (((a - (k*cos(a)))*(c - (k*cos(c))) > 0))
						a = c;
					else
						b = c;
					z = (a + b) / 2;
					i++;
				} while (abs(b - a) > eps);
				x = z;
				cout << "(*) ����� ����������� �������: \n" << " \n";
				cout << "    ������: " << setprecision(10) << x << endl;
				cout << "    ������ �� " << i << " ���(-�;-��.)\n" << " \n";
			}
			else
			{
				cout << "(*) ����� ������� ��������: \n" << " \n";
				cout << "    ������ ���, ��� �������� ������ ��� x = 0 \n" << " \n";
			}

			cout << "    ������ ���������? (y/n) ";
			cin >> exit2;
			l++;
		} while (exit2 == 'y');
	}
	system("pause");

	return 0;
}