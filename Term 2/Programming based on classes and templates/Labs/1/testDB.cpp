#include <iostream>
#include "dbmsLib_v2.h"

using namespace std;

int menu(){
	cout<<"\tMenu\n";
	cout<<"\t(1) - ������\n";
	cout<<"\t(2) - ������\n";
	cout<<"\t(3) - �������� ������\n";
	cout<<"\t(4) - ������ ��������� � ����\n";
	cout<<"\t(5) - �������� ������\n";
	cout<<"\t(6) - ������ �������\n";
	cout<<"\t(7) - ������������ �� ����� �����\n";
	cout<<"\t(8) - �����\n";
	cout<<"\t(9) - Test\n";
	int choice;
	cout<<"\t�������� ��������: ";
	cin>>choice;
	while(cin.fail()){
	cout<<"������ �����. ��������� ����\n";	
	cin.clear();
	cin.ignore(10,'\n');
	cin>>choice;
	}
	return choice;
}

int main()
{
	system("chcp 1251>nul");
	DBMSFuncs::DBTableTxt tab;
	DBMSFuncs::Row row;
	string temp2, temp3, tabName, path = "..\\LibraryTxt\\";
	int temp1;
	int a;
	while(true)
	{
		switch(menu())
		{
		case 1:
		{
			cout << "\nEnter tab Name: ";
			cin >> tabName;
			tab.ReadTableTxt(path+tabName);
			break;
		}
		case 2:
		{
			tab.PrintTable(80);
			break;
		}
		case 3:
		{
			row = tab.CreateRow();
			tab.AddRow(row);
			break;
		}
		case 4:
		{
			tab.WriteTableTxt(path+tabName);
			break;
		}
		case 5:
		{
			cout << "������� ����� ������(������� � 0):> ";
			cin >> temp1;
			cout << "������� �������� �������:> ";
			cin >> temp2;
			cout << "������� ���������:> ";
			cin >> temp3;
			if(tab.GetHeader()[temp2].colType == 1)
			{
				a = atoi(temp3.c_str());
				tab[temp1][temp2] = &a;
			}
			else
				tab[temp1][temp2] = &temp3;
			break;
		}
		case 6:

			cout << "������� ����� ������ ��������:> ";
			cin >> temp1;
			cout << endl << "������� ���������� ��������: " << tab.valueToString(tab[temp1],"Name") << endl << endl;
			break;

		case 7:
		{
			int n = tab.GetSize();
			for(int i = 0; i < tab.GetSize(); i++)
			{
				(*(int*)tab[i]["Quantity"])++;
			}

			break;
		}
		case 8:
		{
			system("pause");
			return 0;
			break;
		}
		case 9:
		{
			break;
		}
		default:
		{
			break;
		}

		}
	}
}

































