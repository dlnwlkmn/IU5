#include <iostream>
using namespace std;

int main()  // ����� ������ n ����� ��������� �� 5 � �� ��������� �� m
{

	system("chcp 1251>nul");
	char povtor;

	do {

		int n, m, sum = 0; // n ����-�� ���. �����, m "����������"

		cout << "������� n: ";
		cin >> n;
		cout << "������� m: ";
		cin >> m;

		if (n < m)
		{
			cout << "N ������ ���� ������ M!!!";
			system("pause");
			return 0;
		}
		for (int i = 1; i < n; i++)
		{
			if (i % 5 == 0 && i%m != 0)
			{
				sum += i;
				cout << sum << ", ";
			}
		}
		cout << "���������: " << sum << endl;

		cout << "����������!? (y/n)" << endl;
		cin >> povtor;

	} while (povtor == 'y');

	system("pause");

	return 0;

}