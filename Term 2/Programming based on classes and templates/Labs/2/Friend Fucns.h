#pragma once
#ifndef FRIENF_FUNCS_H
#define FRIENF_FUNCS_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;
using namespace myLyb;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void myLyb::ReadDBTable1(myLyb::DBTableTxt& tab,string fileName)
//void DBMSFuncs1::ReadDBTableTxt1(myLyb::DBTableTxt& tab,string fileName)
{
	

	ifstream fin(fileName.c_str(), ios::in);
	if(fin.fail())
	{
		cout << "\n���-�� ����� �� ���... ������ �������� �����!\n" << endl;
		return;
	}
	tab.SetFileName(fileName);

	vector<ColumnDesc> strArray;//����� ��� ������ ������ ��������� ������� �� �����
	char line[200];
	char *token, *next_token, delims[] = "|";
	fin.getline(line, 200); //������ ������ ������
	next_token=line;
	token = strtok_s(next_token, delims, &next_token);
	tab.tableName = token;
	token = strtok_s(next_token, delims, &next_token);
	tab.primaryKey = token;
	

	fin.getline(line, 200); //������ ��������� �������
	next_token=line;
	
	ColumnDesc colHdr;//����� ��� ������ ��������� ������ ������� �������

	while( (token = strtok_s( next_token, delims, &next_token)) != NULL ) //���� �� ������ (��������) � ������
	{
		strcpy_s(colHdr.colName,token);
		token = strtok_s( next_token, delims, &next_token);
		//colHdr.colType=GetType(token);
		token = strtok_s( next_token, delims, &next_token);
		colHdr.length=atoi(token);
		strArray.push_back(colHdr);	//�������� ������ � ������� new, �������� � 	
									//�� ��������� ������� (colHdr) � ��������� ��������� �� �����  � ����� �������		
	}
	Header hdr;
	for (unsigned int  j = 0; j < strArray.size() ;  j ++)
	{
	         hdr[strArray[j].colName]=strArray[j];// !!! ������������� �������� ����������
	}
	tab.SetHeader(hdr);

	tab.data.clear();//����� ������ ���������� vector (��� ����������� ���������� ������)
	while (fin.getline(line, 200))
	{		
		Row row=*(new Row());	//����� ��� ������������ ������ ������� ���������� ������ ��� �������� ���� map
		int j = 0;
		token = strtok_s( line, delims, &next_token);
		
		while(token) //���� �� �������� (������) � ������
		{
			string value=token;
			//���������� ���� � ������ � ��������������� ����
			//strArray[j] - ��� ������� � ��������� �������
		row[strArray[j].colName]= GetValue(value,strArray[j].colName,tab.columnHeaders);		
		j=j++;						//������ ���������� ������� � ������� strArray
			token = strtok_s( next_token, delims, &next_token);
		}
		tab.data.push_back(row);//�������� ������ ������ � �������
	}

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void myLyb::WriteDBTable1(myLyb::DBTableTxt& tab,string fileName)
//void DBMSFuncs1::WriteDBTableTxt1(myLyb::DBTableTxt& tab,string fileName)
{
	ofstream fout(fileName+".txt", ios::out);
	if(fout.fail())
	{
		cout << "\n���-�� ����� �� ���... ������ �������� �����!\n" << endl;
		return;
	}
	string Type[] = {"NoType","Int32","Double","String","Date"};	//������ ����� ��� enum
	Header::iterator iter, iterWhile;								//���������
	fout << tab.tableName << "|" << tab.primaryKey << endl;			//������ �������� ������� � primaryKey
	iter = tab.columnHeaders.begin();			//�������� � ������ 
	iterWhile = iter;
	int n = 0;
	while(iterWhile!=tab.columnHeaders.end())						//������ ������ ������ � ���� � ���������� ���������� 
	{
		fout << iter->second.colName << "|" << Type[iter->second.colType] << "|" << iter->second.length;
		iter++;
		iterWhile++;
		n++;			//������� ���-�� ��������
		if(iterWhile!=tab.columnHeaders.end())
			fout << "|";
	}
	fout << "\n";
	for(int i = 0; i < tab.data.size(); i++)	//���� �� ������� �������
	{
		iter = tab.columnHeaders.begin();
		for(int j = 0; j < n; j++)				//���� �� ��������� i-� ������ j-�� �������
		{
			fout << tab.valueToString(tab[i],iter->second.colName);
			if(n-1 != j)
				fout << "|";
			iter++;
		}
		fout << endl;
	}
	
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void myLyb::PrintTable1(myLyb::DBTableTxt& tab, int screenSize)
//void DBMSFuncs1::PrintDBTable1(myLyb::DBTableTxt& tab, int screenSize)
{
	int n = 0;
	string Type[] = {"NoType","Int32","Double","String","Date"};	//������ ����� ��� enum
	Header::iterator iter, iterSave, iterTake;
	int Edge;
	Strip* strips;
	int nStrips;
	tab.CreateTableMaket(strips, nStrips, screenSize);

	for(int i = 0; i < nStrips; i++)//���� �� ������� ������ �������
	{
		Edge = screenSize - 1;//��� ������ ������������ ����� ������������� 
		if(i == 0)
			cout << "\n������� " << tab.tableName << endl;
		else
			cout << "\n����������� ������� " << tab.tableName << endl;

		for(int j = 0; j < Edge; j++)	//���� ����. �����
			cout << "=";
		cout << endl;

		if(i == 0)
			iter = tab.columnHeaders.begin();
		else
			iter = iterTake;
		for(int j = 0; j < strips[i].nField; j++)//������ ������ ������ ��������� �������
		{
			cout << setw(strips[i].fieldWidth[j]) << iter->second.colName;
			iter++;
		}
		iterSave = iter;//���������� �������� ���������
		cout << endl;

		if(i == 0)
			iter = tab.columnHeaders.begin();
		else
			iter = iterTake;
		for(int j = 0; j < strips[i].nField; j++)//������ ������ ������ ��������� �������
		{
			cout << setw(strips[i].fieldWidth[j]) << Type[iter->second.colType];
			iter++;
		}
		cout << endl;

		for(int j = 0; j < Edge; j++)	//���� ����. �����
				cout << "-";
		cout << endl;

		for(int j = 0; j < tab.data.size(); j++)	//���� �� ������� �������
		{
			if(i == 0)
				iter = tab.columnHeaders.begin();
			else
				iter = iterTake;
			for(int k = 0; k < strips[i].nField; k++)				//���� �� ��������� ������ j-�� �������
			{
				cout << setw(strips[i].fieldWidth[k]) << tab.valueToString(tab[j],iter->second.colName);
				iter++;
			}
			cout << endl;
		}

		for(int j = 0; j < Edge; j++)	//���� ����. �����
			cout << "=";
		cout << endl;
		iterTake = iterSave;
	}
}

#endif //FRIENF_FUNCS_H