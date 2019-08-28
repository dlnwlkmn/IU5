//���� dbmsLib_v2.h
#pragma once
#ifndef _dbmsLib_v2_
#define _dbmsLib_v2_
#include <iostream>
#include <fstream>
#include <strstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

using namespace std;
namespace dbmsLib
{
//-----------------����� DBDate----------------------------
  class DBDate
  {	
	  	friend string DateToStr(DBDate& date);
		friend ostream& operator<<(ostream& out,DBDate& date);
		int day, month, year;
		//������� ��� ����������� �������������:
		bool IsLeapYear (int year); //��� ����������?
		int GetDaysInMonth(int month,int year);//���������� ���� � ������
		int DaysInCurYear();//���������� ���� �� ������ ���� �� ������� ����
	public:
		DBDate(string date);//������ ������: dd.mm.yyyy
		DBDate(int d,int m,int y);
		DBDate():day(1),month(1),year(1){};//����������� �� ���������
		//����������� �����������
		DBDate(DBDate& dat):day(dat.day),month(dat.month),year(dat.year){}
		int GetDay();
		int GetMonth();
		int GetYear();
   public:
		bool operator==(DBDate& date);
		bool operator<(DBDate& date); 
		bool operator>(DBDate& date);
		bool operator<= (DBDate& date);
		bool operator>= (DBDate& date);
		bool operator!= (DBDate& date);
		DBDate& operator+=(int days);//���������� � ������� ���� days ����
		DBDate& operator-=(int days);//�������� �� ������� ���� days ����
		int operator-(DBDate& date);//���������� ���� ����� ������� ����� � date
									//���� ������� ���� > date, ��������� < 0.
  };
//==================== ���������� ������ dbmsLib.h ===========================
//TableDataType - ������������ ����� ����� ������ ��: 
enum TableDataType {
	 NoType,
	 Int32,
	 Double,
	 String,
	 Date
};
//Condition - ������������ ������� ���������:
enum Condition{
	Undefined,
	Equal,
	NotEqual,
	Less,
	Greater,
	LessOrEqual,
	GreaterOrEqual
};
const int LENGTH = 24;//����� ����� ������� � ����� �������.
const int DELTA = 20;//����� � 10 ����� ��� ����� ������� � �������. 
//���� ����� ������������, �� ��� ��� �������������� ����� ���������
//�� DELTA ������ ������������� ������� char* data[]. 
//ColumnDesc - �������� ������ � ������� �������: 
//struct ColumnDesc { 
//	char colName[LENGTH];//��� �������
//	TableDataType colType;//��� ������ � ������� �������
//	int length; //������������ ����� ��������, ���������� 
//				//��� ������������� ������ � �������
//}; 
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
//������ ���������� �������:
struct Strip{
	int nField;//����� ����� 
	int* fieldWidth;//������ ����� � ������ (������)
};
  typedef map<string, void*> Row;//��� ������ � ������
  typedef map<string, ColumnDesc> Header;//��� ���������

string GetTabNameFromPath(string path);
string ignoreBlanc(const string str);
void* GetValue(string value, string columnName,Header hdr);
void* SetValue(string value, string columnName,Header hdr);
bool comparator(TableDataType type,void *obj1,Condition condition,void *obj);
int GetLength(ColumnDesc colDesc);
string TabFileExtension(string dbName);
//===============����������� ������� ����� DBTable================
class DBTable{
public:
	DBTable(){};
	TableDataType GetType(char* columnName);
	const char* TypeName(TableDataType type);
	virtual Header GetHeader()=0;
//�� �������� ����� ���������� ���������� ����� (������) ������ (������) � data.
// keyValue-�������� ����� (��������� �� string, int ��� DBDate)
// keyColumnName-��� ��������� ������� (��������� ��� ��������� ����)
//� ������� ����� ���� ��������� ������� � ���������� ��������� ���������� �����:
	virtual vector<int> IndexOfRecord(void* keyValue,string keyColumnName)=0;
	virtual Row GetRow(int index)=0;
	virtual Row operator[](int index)=0;
	virtual string valueToString(Row& row,string columnName)=0;
	virtual int GetSize()=0;
	virtual ~DBTable(){};
	virtual void SetHeader(Header& hdr)=0;
	//������������� ��� �����: fileName="..\\"+dbName+"\\"+tableName+".bin"|".txt"
	virtual void ReadDBTable(string fileName)=0;											
	virtual void WriteDBTable(string fileName)=0;
	virtual void SetTableName(string tName)=0;
	virtual void SetPrimaryKey(string key)=0;
	virtual string GetTableName()=0;
	virtual string GetPrimaryKey()=0;
	virtual void SetFileName(string path)=0;
	virtual string GetFileName()=0;
	virtual void PrintTable(int screenWidth)=0;//screenWidth - ������ ������
	virtual Row CreateRow()=0;
	virtual void AddRow(Row row,int index)=0;
//������� �� ������� �����, � ������� �������� ���� colName � �������� value 
	//������������� ������� cond:
	virtual DBTable* SelfRows(string colName,Condition cond, void* value)=0;
};
//===============class DBTableTxt=============================
class DBTableTxt:public DBTable{
private:
	Header columnHeaders;
	string tableName;
	string primaryKey; 
	vector<Row> data;
	string fileName;
  	public:
		DBTableTxt(){}
		DBTableTxt(string tabName): tableName(tabName){}	
		DBTableTxt(string tabName,Header hdr,string primKey):tableName(tabName),
			columnHeaders(hdr),primaryKey(primKey){}
		~DBTableTxt();//!!!���������� ����������,����� ������,���������� void*,�� �������
		vector<int> IndexOfRecord(void* keyValue,string keyColumnName);
 		string valueToString(Row& row,string columnName);
		void DBTableClear();
		void ReadDBTable(string tabName);//tabName=path+tableName
		void ReadTableBin(string tabName);//������ ������� �� ��������� �����
		void PrintTable(int screenWidth);
		void WriteDBTable(string tabName);//tabName=path+tableName	
		void WriteTableBin(string tabName);//������ ������� � �������� ����
		int GetSize();
		Row operator[](int ind);
		void SetFileName(string path);
		void SetTableName(string tName);
		void SetPrimaryKey(string key);
		string GetFileName();
		string GetTableName();
		string GetPrimaryKey(){return primaryKey;}
		Header GetHeader();
		void SetHeader(Header& hdr);
		Row CreateRow();
		Row GetRow(int index);
		void AddRow(Row row,int index);
		DBTable* SelfRows(string columnName,Condition cond, void* value);
		//����� ���������� �������:
		//screenWidth - ������ ������ (������� ��������)
		//nStrips - ����� ����� � ���������� (�������� ��������)
		//strips[nStrips] - �������� ����� �������: 
		//����� �������� � ������ ������� ������� � ������ (�������� ��������)
		void CreateTableMaket(Strip* &strips,int &nStrips,int screenWidth);
		friend void ReadDBTable1(DBTableTxt& tab,string tabName);//tabName=path+tableName
		friend void WriteDBTable1(DBTableTxt& tab,string tabName);
		friend void PrintTable1(DBTableTxt& tab,int screenWidth);
		//������ ������� � �������� ����:
		friend void WriteTableBin1(DBTableTxt& tab, string tabName);
		//������ ������� �� ��������� �����:
		friend void ReadTableBin1(DBTableTxt& tab,string tabName);
  };
//=====================����� DBTableBin=====================================
class DBTableBin: public DBTable{
	char tabName[LENGTH];
	char primaryKey[LENGTH];//��� ������� �� ���������� ���������� �����
	int nColumn;
	ColumnDesc* header;				
	int nRows; 
	int RowLength();
	int DataBegin();
	int FieldPosition(string colName);//�������� ���� colName �� ������ ������ � ������
	int FieldLength(string colName);//����� ���� colName � ������
	void ResizeData(int deltaRows);
	char** data;		
	int maxRows;//����� ����� � data � ������ DELTA (��� ���������� �������
	//�� ����� ��������������� ������ nRows+DELTA).� ���� �� ������������
	char fileName[80];//� ���� �� ������������. ������������ � ������� ���
	//��������� � �����
	void CreateTableMaket(Strip *&strips,int &nStrips,int screenWidth);
public:
	DBTableBin(){}
	DBTableBin(string tableName);
	DBTableBin(string tableName,Header hdr,string primKey);		
	~DBTableBin(){}
	Header GetHeader();
	void DBTableClear();
	vector<int> IndexOfRecord(void* keyPtr,string keyName);
	int FieldPosInFile(int rowIndex,string columnName);
	Row GetRow(int index);
	Row operator[](int index);
	string valueToString(Row& row,string columnName);
	int GetSize(){return nRows;}
	void SetHeader(Header& hdr);
	void ReadDBTable(string fileName);											
	void WriteDBTable(string fileName);
	void SetTableName(string tName);
	void SetPrimaryKey(string key);
	string GetTableName(){return tabName;}
	string GetPrimaryKey(){return primaryKey;}
	void SetFileName(string path){
		strcpy_s(fileName,80,(path+"//"+tabName+".bin").c_str());
	} 
	string GetFileName(){return fileName;}
	void PrintTable(int screenWidth);
	Row CreateRow();
	void AddRow(Row row,int index);
	DBTable* SelfRows(string colName,Condition cond, void* value);
};
//==============����� DBTableSet============================
struct Relation{//��������� ����� ���� ������
	string relationName;
	string parentTable;
	string parentPrimaryKey;
	string childTable;
	string childSecondaryKey;
};
void PrintRow(Row row,DBTable* tab);
//-------------------------����� DBTableSet---------------------
class DBTableSet
{
private:
	string dbName;
	map<string, DBTable*> db;
public: 
	DBTableSet(){};
	DBTableSet(string name);
	int ReadDB();
	void PrintDB(int numcol);
	void WriteDB();
	string GetDBName(){return dbName;}
	DBTable* operator[](string tableName); 
	Relation GetRelation(string relationName);
	Row ParentRow(Relation& relation,Row& childRow);
	DBTable* ChildRows(Relation& relation,Row& parentRow);
};
}
#endif//_dbmsLib_v2