//���� DBMSFuncsLib.h
#pragma once
#ifndef _DBMSFuncsLib_
#define _DBMSFuncsLib_
#include <iostream>
#include <strstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <string>

using namespace std;
namespace DBMSFuncs
{
//-----------------����� DBDate----------------------------
  class DBDate
  {	
		static const int arrDays[13];
		friend string DateToStr(DBDate& date);
		friend ostream& operator<<(ostream& out,DBDate& date);
		int day, month, year;
	public:
		DBDate(string date);//������ ������: dd.mm.yyyy
		DBDate(int d,int m,int y);
		DBDate():day(0),month(0),year(0){};//����������� �� ���������
		DBDate(DBDate& dat):day(dat.day),month(dat.month),year(dat.year){}
		int GetDay();
		int GetMonth();
		int GetYear();
		bool IsLeapYear (int year); //��� ����������?
		int GetDaysInMonth(int month,int year);//���������� ���� � ������
		int DaysInCurYear();//���������� ���� �� ������ ���� �� ������� ����
		bool operator==(DBDate& date);
		bool operator<(DBDate& date); 
		bool operator>(DBDate& date);
		bool operator<= (DBDate& date);
		bool operator>= (DBDate& date);
		bool operator!= (DBDate& date);
		DBDate& operator+=(int days);//���������� � ������� ���� days ����
		DBDate& operator-=(int days);//�������� �� ������� ���� days ����
		int operator-(DBDate& date);	//���������� ���� ����� ������� ����� � date
									//���� ������� ���� > date, ��������� < 0.
  };
//======TableDataType-������������ ����� ����� ������ ��====== 
enum TableDataType {
 NoType,
 Int32,
 Double,
 String,
 Date
};
//const int DELTA = 10;//����� � 10 ����� ��� ����� ������� � �������. 
//���� ����� ������������, �� ��� ��� �������������� ����� �������� 
//������� � ���� � ����� ��������� �.
const int LENGTH = 24;//������ ����� ��� ����� ������� � ����� �������. 
//��� ������������ ���� ��� ������������ ������� �������.
//ColumnDesc - �������� ������ � ������� ������� 
//������ ���� string ����� ���������� ����� (length) ������ ������ �������, 
//�� � ������ �������� �� ����� ����� ����������. 
  struct ColumnDesc { 
	char colName[LENGTH];//��� �������
	TableDataType colType;//��� ������ � ������� �������
	int length; //������������ ����� �������� � ��������� ������������� 
	//������ �������, ������� ������������ '\0' ��� ���� String
	ColumnDesc(){};
	ColumnDesc( char * name, TableDataType type, int len){ 
		strcpy_s(colName,name);
		colType=type;
		length=len; 
	} 
}; 
  struct Strip{//������ ���������� �������
			int nField;//����� ����� 
			int* fieldWidth;//������ ����� � �������� ������  
		};					//� ������ ���������� � ����� ����� �������
  typedef map<string, void*> Row;
  typedef map<string, ColumnDesc> Header;
  enum Condition{Undefined,Equal,NotEqual,Less,Greater,LessOrEqual,GreaterOrEqual};
  TableDataType GetType(string columnName,Header hdr );
  string GetTabNameFromPath(string path);
  string ignoreBlanc(const string str);
  void* GetValue(string value, string columnName,Header hdr);
  bool comparator(TableDataType type,void *obj1,Condition condition,void *obj);
  class DBTableTxt;
 // Row CreateRow(DBTableTxt tab);
  //--------------------����� DBTableTxt-----------------------------
  class DBTableTxt
  {
	private:
		string tableName;
		string primaryKey;//��� �������, ����������� ��������� ������ (�������� �����
	//� ���� ������� ������ ���� �����������). ��������� ������ � "��������" ��������. ��� 
	//�������� ������ �� ������� �������� ���������� ����� � ����� ������� �� �����������.
	//�� "���������������" ��������, ���������� � ����������� �� ��� �������� ������
	//����� ��������� ���� "������-��-������", �� �� ������������ (� ����� ��� ���). 
	//������� "���������������" ������: Abonements, OrderDetails. � ��� ������ 
	//���������������� ����������� ������ ����������� ������. 
	//�������� �� ��������� "NoPrimaryKey" ����� ������������ ��� ������� ����, ��� ������
	//DBTableTxt ������ � ��������������� ��������. 
	//��� ������� � ��� ���������� ����� ������� ����� ������� � ������ ������
	//���������� �����. ������ ������ ���������� ����� �������� ������� �������.
	//� ����� "DBTables" ����� ������� ����� ������ � ��������� ��.
		string fileName;
		Header columnHeaders;
		vector<Row> data;
	public:
		DBTableTxt(){}
		DBTableTxt(string tabName): tableName(tabName){}
		~DBTableTxt(){}
 		string valueToString(Row& row,string columnName);
		void ReadTableTxt(string tabName);//tabName=path+tableName
		void ReadTableBin(string tabName);//������ ������� �� ��������� �����
		void PrintTable(int screenWidth/*,string dbName*/);
		void WriteTableTxt(string tabName);//tabName=path+tableName	
		void WriteTableBin(string tabName);//������ ������� � �������� ����
		int GetSize();
		Row& operator[](int ind);				
		string GetTableName();
		string GetPrimaryKey(){return primaryKey;}
		Header GetHeader();
		void SetHeader(Header& hdr);
		void SetFileName(string path){fileName=path+"//"+tableName+".txt";} 
		string GetFileName(){return fileName;}
		Row CreateRow();
		void AddRow(Row row);
		DBTableTxt SelfRows(string columnName,Condition cond, void* value);
		//����� ���������� �������:
		//screenWidth - ������ ������ (������� ��������)
		//nStrips - ����� ����� � ���������� (�������� ��������)
		//strips[nStrips] - �������� ����� �������: 
		//����� �������� � ������ ������� ������� � ������ (�������� ��������)
		void CreateTableMaket(Strip* &strips,int &nStrips,int screenWidth);
		friend void WriteDBTableTxt1(DBTableTxt& tab,string fileName);
		friend void WriteDBTableBin1(DBTableTxt& tab,string fileName);
		friend void PrintDBTable1(DBTableTxt& tab,int screenSize);
		friend void ReadDBTableTxt1(DBTableTxt& tab,string fileName);
		friend void ReadDBTableBin1(DBTableTxt& tab,string fileName); 
		friend DBTableTxt SelfRows1(DBTableTxt& tab,string columnName,Condition cond, void* value);
  };
 //-----------------------����� Relation----------------------
  class Relation//��������� ����� ���� ������
    {
		public:
			Relation();
			string relationName;
			string parentTable;
			string parentPrimaryKey;
			string childTable;
			string childSecondaryKey;
    };
//-------------------------����� DBTableSet---------------------
 class DBTableSet
 {
    private:
		string dbName;
	    map<string, DBTableTxt> db;
	public: 
			DBTableSet(){};
			DBTableSet(string name);
			int ReadDB();
			void PrintDB(int screenWidth);
			void WriteDB();
			string GetDBName(){return dbName;}
			DBTableTxt& operator[](string tableName) { return db[tableName]; }
			Relation GetRelation(string relationName);
			Row ParentRow(Relation& relation,Row& childRow);
			DBTableTxt ChildRows(Relation& relation,Row& parentRow);
  };
}
#endif //_DBMSFuncsLib_