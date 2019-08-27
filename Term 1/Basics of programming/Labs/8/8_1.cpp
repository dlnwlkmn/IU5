#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <fstream>
#include <ctime>
#include <Windows.h>
#include "head8_1.h"
using namespace std;

struct Stats
{
	ifstream fin1, fin2;
	unsigned char letter;					//�������� �����
	int variant;				//���-�� ��������������
	int quantity;
	int codes[256];	//�������� ���� ��������
	Stats();  
	void stats(char* fName1, char* fName2, int n, int &skip);	//����� ���������� � ����������
	void Cout(int skip);		//������

};
Stats::Stats()	//���������
{
	for (int i = 0; i < 256; i++)	//��������� �������
		codes[i] = NULL;
}
void Stats::stats(char* fName1, char* fName2, int n, int& skip)
{

	fin1.open(fName1);
	fin2.open(fName2);
	quantity = 0;
	char ch1, ch2;
	cout << "������� ������: ";
	cin >> letter;
	for (int i = 0; fin1.get(ch1); i++)
	{
		fin2.get(ch2);
		if (letter == ch1)
		{
			int j = (unsigned char)ch2;
			codes[j] += 1;
			skip = 1;
			quantity++;
		}
	}

	fin1.close();
	fin2.close();
}

void Stats::Cout(int skip)
{
	if (skip == 0)	//����� ����������� � ������
	{
		cout << "������ � ������ �� �����������! " << endl << endl;
		
	}
	else
	{
		cout << "���-�� �������� '" << letter << "' � �������� ������: " << quantity << endl << endl;
		int w = 3;
		cout << setw(3) << "�   ";
		for (int j = 0; j < 16; j++) cout << setw(w) << (j + 1);
		cout << "\n____________________________________________________\n";

		for (int i = 0; i < 256; i++)
		{
			if (i % 16 == 0)
			{
				cout << endl;
				cout << setw(3) << (i / 16) + 1 << "|";
			}
			cout << setw(w) << codes[i];
		}
		cout << endl << endl;
		for (int i = 0; i < 256; i++)
		{
			if (codes[i] != 0)
			{
				cout << "char(" << i << ") " << char(i) << "  -  " << codes[i] << endl;
			}
		}
			for (int i = 0; i < 256; i++)
		{
			codes[i] = NULL;
		}
		cout << endl << endl;
	}
}

int menu(int d)
{
	int choice;
	if(d == 1)
		cout << "(1)����������� (2)����������� (3)��������� ������ ������ (4)������������ ����\n(5)��������� (6)����� (7)��������� \> ";
	if(d == 2)
		cout << "(1)����������� (2)����������� (3)������ ���� (4)������������ ����\n(5)��������� (6)����� (7)��������� \> ";
	cin >> choice;
	cout << endl;
	return choice;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");
	srand(NULL);
	int n;						//����������� �������
	int exit1 = 1, exit2 = 1;	//����� �� ������ while				
	int a, b;					//������� �������
	char *keys;					//��������� �� ������ ������
	int count = 1;				// ������� �������� "������"
	int menuDeff = 1;			//��� ����
	int skip = 1;
	char FName1[12] = "Massege.txt";	//���� ������
	char FName2[12] = "Code.txt";	//���� ������ �����
	char FName3[12] = "Result.txt";	//���� ������ �����������
	Stats letter;
	cout << "\t\t\t\t����������\n\n";
	cout << "����� �� ���������? ( (1)�� (2)��� ): ";
	cin >> n;
	if (n == 2)
	{
		cout << "������� �������� ����� ������: ";
		cin >> FName1;
		cout << "������� �������� ����� ������: ";
		cin >> FName2;
	}

	ifstream fin(FName1, ios::binary);						//������
	ofstream fout(FName2, ios::binary);						//������
	if (!fin.is_open())
	{
		cout << "�������� �������� ����� ������...\n";
		system("pause");
		return 1;
	}
	else
	{
		cout << "����� �������!\n";
	}

	createKeys(FName1, keys, n);		//������ ������ ������
	fin.close();
	fout.close();
	while (exit2 == 1)
	{
		cout << "////////////////////////////////////////////////////////////////////////////////";
		cout << "((" << count << "))" << endl;
		exit1 = 1;
		while (exit1 == 1)
		{	
			switch (menu(menuDeff))
			{
			case 1:	//�����������
			{
				fin.open(FName1,ios::binary);
				fout.open(FName2,ios::binary);
				int nKey = 0;
				char ch = fin.get();
				while(fin)
				{
					
					fout.put(ch^keys[nKey%256]);
					ch = fin.get();
					nKey++;
				}
				if (nKey) cout << "*** ������������\n\n";
				fin.close();
				fout.close();
				break;
			}
			case 2:	//������������
			{
				fin.open(FName2, ios::binary);
				fout.open(FName3, ios::binary);
				int nKey = 0;
				char ch = fin.get();
				while (fin)
				{

					fout.put(ch^keys[nKey % 256]);
					ch = fin.get();
					nKey++;
				}
				if (nKey) cout << "*** �������������\n\n";
				fin.close();
				fout.close();
				break;
			}
			case 3:	//� ������(����� ������ ������)
			{
				if (menuDeff == 1)
				{
					exit1 = 0;
					menuDeff = 2;
					count++;
					cout << "������� �������� �����������(a, b): ";
					cin >> a >> b;
					Keys(keys, n, a, b);
					break;
				}
				if(menuDeff==2)
				{
					menuDeff = 1;
					exit1 = 0;
					count++;
					createKeys(FName1, keys, n);
					break;
				}
			}
			case 4:	//���������
			{
				system("notepad");
				cout << argv[0] << endl << endl;
				break;

			}
			case 5:	//����� ���������(.exe)
			{
				exit1 = 0;
				exit2 = 0;
				cout << "�����!" << endl << endl;
				break;
			}
			case 6:	//����� ������� ������
			{
				printKeys(keys, n);					//������ ������� ������
				break;
			}
			case 7:	//�����������
			{
				int skip;
				char ex;
				cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*����������* \n";
				do {
					skip = 0;
					letter.stats(FName1, FName2, n, skip);
					letter.Cout(skip);
					cout << "�����?(y/n) ";
					cin >> ex;
					cout << endl;
				} while (ex != 'y');
				cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
				break;
			}
			}
		}
	}
	
	delete[] keys;
	system("pause");
	return 0;
}

