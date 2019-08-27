#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "DZlib.h"
using namespace std;

int menu()
{
	int choice;
	cout << "\n(1) ���� ������\n(2) ���������� ��������� Text()\n(3) ������\n(4) �����������\n(5) ������� �19\n(6) ���������\n:> ";
	cin >> choice;
	cout << endl;
	cin.clear();
	cin.ignore(20, '\n');
	return choice;
}

void var19(Text&);

int main()
{
	system("chcp 1251>nul");
	ifstream fin("text.txt",ifstream::binary);
	Sentence sent;
	Text txt;
	char* str = NULL;
	char line[100000] = { NULL };

	cout << "\t\t\t\t==��==\n";
	while (1)
	{
		switch (menu())
		{
		case 1:		//���� ������
		{
			int choice;
			cout << "(1) � ����������\n(2) �� �����\n:>";
			cin >> choice;
			if (choice == 1)
			{
				str = inputText();
				break;
			}
			if (choice == 2)
			{
				fin.clear();
				fin.seekg(0);
				fin.getline(line, 1000);
				str = line;
				cout << "\n\t***���������\n";
				break;
			}
			cout << "Error#5^_3\n";
			break;
		}
		case 2:		//������ � TEXT
		{
			txt = GetText(str);
			cout << txt << "���-�� �����������: " << txt.nSentences << endl;
			break;
		}
		case 3:		//����� �� �����
		{
			cout << txt << "���-�� �����������: " << txt.nSentences << endl;
			break;
		}
		case 4:		//������������
		{

			cout << "�����" << endl << endl;
			break;
		}
		case 5:		//������� 19
		{
			var19(txt);
			break;
		}
		case 6:		//���������
		{
			cout << "��������\n\n";
			system("pause");
			return 0;
		}
		}
	}
	fin.close();
	system("pause");
	return 0;
}

void var19(Text& txt)
{
	int choice;
	int nSents, nWords;
	nSents = txt.nSentences;
	for (int i = 0; i < nSents; i++)
		LastWord(txt, i);
	char* word;
	cout << "\n(1) ������� ����� ����������� � ���������\n(2) ��� ����� � ������ ���������� ������� �������� ������� � ����������\n:>";
	cin >> choice;
	if (choice == 1)
	{
		DeleteWords(txt);
		cout << "\t***���������" << endl;
	}
	else if (choice == 2)
	{
		for (int i = 0; i < nSents; i++)
		{
			nWords = txt.sentence[i].nWords;
			for (int j = 0; j < nWords; j++)
			{
				if ((j + 1) % 2 == 0)
				{
					Swap(txt, j, i);
				}

			}
		}
		cout << "\t***���������" << endl;
	}
}

