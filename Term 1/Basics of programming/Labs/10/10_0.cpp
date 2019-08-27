#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "head 10_0.h"
using namespace std;


int menu()
{
	int choice;
	cout << "\n(1) �������� �����\n(2) ������� �����\n(3) ������� Eng-Rus\n(4) ������� Rus-Eng\n(5) �������� �������\n(6) ������ ������� � ����\n(7) ������ ������� �� �����\n(8) ��������� �������\n(9) ���������\n:> ";
	cin >> choice;
	cout << endl;
	return choice;
}



int main()
{
	system("chcp 1251>nul");
	int nWords = 0;
	Dictionary elem;
	Dictionary* dict = NULL;



	cout << "\t\t\t�����-������� �������" << endl << endl;

	while (1)
	{
		switch (menu())
		{
		case 1:				//���������� �����
		{
			int exit = 0;
			while (exit != 2)
			{
				int lang;
				cout << endl << "����? ( (1)Rus,(2)Eng )\n:>";
				cin >> lang;
				cout << endl;
				if (lang == 1)
				{
					cout << "������� �����(Rus): ";
					cin >> elem.rus;
					cout << "������� �������(Eng): ";
					cin >> elem.eng;
				}
				if (lang == 2)
				{
					cout << "������� �����(Eng): ";
					cin >> elem.eng;
					cout << "������� �������(Rus): ";
					cin >> elem.rus;
				}
				cout << endl;
				addWord(dict, nWords, elem);
				memset(elem.rus, 0, 31);
				memset(elem.eng, 0, 31);
				cout << "��� ����? ( (1)�� (2)��� )\n:> ";
				cin >> exit;
			}
			break;
		}
		case 2:				//�������� �����
		{
			int var;
			int exit = 0;
			while (exit != 2)
			{
				int lang;
				cout << endl << "����? ( (1)Rus,(2)Eng )\n:> ";
				cin >> lang;
				if (lang == 1)
				{
					cout << "������� �����(Rus): ";
					cin >> elem.rus;
					var = 1;
				}
				if (lang == 2)
				{
					cout << "������� �����(Eng): ";
					cin >> elem.eng;
					var = 2;
				}
				cout << endl;
				searchWord(dict, nWords, var, elem);
				if (var == 0)
				{
					deleteWord(dict, nWords, elem);
					cout << "\t***���������\n\n";
				}
				memset(elem.rus, 0, 31);
				memset(elem.eng, 0, 31);
				cout << "��� ����? ( (1)�� (2)��� )\n:> ";
				cin >> exit;
			}
			break;
		}
		case 3:				//������� � ENG
		{
			int exit = 0;
			while (exit != 2)
			{
				bool log = 0;
				cout << endl << "������� �����(Eng): ";
				cin >> elem.eng;
				cout << "�������: ";
				for (int i = 0; i < nWords; i++)
				{
					if (*(elem.eng) == *(dict[i].eng))
					{
						cout << dict[i].rus << ", ";
						log = 1;
					}
				}
				cout << "\b\b.\n\n";
				if (log == 0)
					cout << "����� � ������� �� �������...\n\n";
				cout << "��� ����? ( (1)�� (2)��� )\n:> ";
				cin >> exit;
			}
			memset(elem.eng, 0, 31);
			break;
		}
		case 4:				//������� � RUS
		{
			int exit = 0;
			while (exit != 2)
			{
				bool log = 0;
				cout << endl << "������� �����(Rus): ";
				cin >> elem.rus;
				cout << "�������: ";
				for (int i = 0; i < nWords; i++)
				{
					if (*(elem.rus) == *(dict[i].rus))
					{
						cout << dict[i].eng << ", ";
						log = 1;
					}
				}
				cout << "\b\b.\n\n";
				if (log == 0)
					cout << "����� � ������� �� �������...\n\n";
				cout << "��� ����? ( (1)�� (2)��� )\n:> ";
				cin >> exit;
			}
			memset(elem.rus, 0, 31);
			break;
		}
		case 5:				//������ �������
		{
			if (nWords != 0)
			{
				sorting(dict,nWords);
				cout << "�������: " << endl;
				for (int i = 0; i < nWords; i++)
					cout << dict[i];
			}
			else
				cout << "������� ����..." << endl;
			break;
		}
		case 6:				//������ � ����
		{
			ofstream fout("write.txt");
			for (int i = 0; i < nWords; i++)
			{
				fout << dict[i];
			}
			cout << "\t***���������\n";
			fout.close();
			break;
		}
		case 7:				//������ �� �����
		{
			if (nWords != 0) delete[] dict;
			ifstream fin("read.txt", ios::in);
			char line[100];
			while (fin.getline(line, 100))
				nWords++;
			nWords /= 2;
			dict = new Dictionary[nWords];
			fin.clear();
			fin.seekg(0);
			for (int i = 0; i < nWords; i++)
			{
				fin >> dict[i].rus;
				fin >> dict[i].eng;
			}
			cout << "\t***���������\n";
			fin.close();
			break;
		}
		case 8:				//���������
		{
			cleanDict(dict, nWords);
			break;
		}
		case 9:
		{
			delete[] dict;
			return 0;
		}
		default: cout << "\n�������� ������������ ��������..." << endl;
		}
	}

	system("pause");
	return 0;
}