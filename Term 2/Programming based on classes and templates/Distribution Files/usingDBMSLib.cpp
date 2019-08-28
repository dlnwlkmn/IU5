#include "dbmsLib_v2_2.h"
using namespace std;
//namespace dbmsLib
//{
dbmsLib::DBDate nulDate("1.1.1");
//--------------------------------------------------
string TabNameExtension(string dbName){
	char buf[8];
	strcpy_s(buf,8,dbName.c_str()+dbName.size()-3);
	if(!strcmp("Bin",buf))
		return ".bin";
	else if(!strcmp("Txt",buf))
		return ".txt";
	else
		cout<<"TabNameExtension(): ������ � ����� �� "<<dbName<<endl;
	system("pause");
	return dbName;	
}
//===========================================
/*���������� ������ �� ������ ������� �� ������. 
�������� ������ � ������� Orders � �� ����� ������ �� ������
������� � ������ � ������� OrderDetails � ������� ����������� 
��������� � ������� Products. 
����� ����� ������� � ������� OrderDetails ������� �������� 
������� ��������� �� ������.
*/
void ExecuteOrder(dbmsLib::DBTableSet& db,int screenWidth)
{ //���������� ������ ������ �� ���������� ���������
	//	string tabName = "Products";
	string dbName = db.GetDBName();
	string path="..\\"+dbName+"\\";
	dbmsLib::Row row=db["Orders"]->CreateRow();
	//�������� ������������� ���������� � row ������� 
	if((*db["Customers"]).IndexOfRecord(row["CustomerID"],"CustomerID").size()==0){
		cout<<"� �� ��� ������ � ������� "<<*(string*)row["CustomerID"]<< endl;
		system("pause");
		return;
	}
	db["Orders"]->AddRow(row,db["Orders"]->GetSize());//������ ������ � �������
	db["Orders"]->PrintTable(screenWidth);//��� ���������� ��� 
	db["Products"]->PrintTable(screenWidth);//���������� ������
	bool isContinue=false;
	do{
		row=db["OrderDetails"]->CreateRow();
		//�������� � ��������� ���������� ������ �� ������
		dbmsLib::Header::iterator it;
		vector<int> indexes=db["Products"]->IndexOfRecord(row["ProductID"],"ProductID");
		//�������� ������������� � �� ���������� � row ��������
		if(indexes.size()==0){
			cout<<"� �� ��� ������ � ��������  "<<*(string*)row["ProductID"]<< endl;
			system("pause");
			return;
		}
		for(int i=0;i<indexes.size();i++){
			if((*(int*)(*db["Products"])[indexes[i]]["UnitInStock"])>=*(int*)row["Quantity"]){
				*(int*)(*db["Products"])[indexes[i]]["UnitInStock"]-=*(int*)row["Quantity"];
				db["OrderDetails"]->AddRow(row,db["OrderDetails"]->GetSize());				
			}
			else{
				cout<<"����� �� ����� ���� ��������, �.�. �� ������ ������ "<<
					*(int*)(*db["Products"])[indexes[i]]["UnitInStock"]
				<<" ������ ������ "<<*(string*)row["ProductID"]<<endl;
				system("pause");
				return;
			}
		}
		//���������� ��������� ���������� ������ row["ProductID"] � ���� � �������� db["Products"],
		//��������� ������ ������ � ������ � ����� (��� ����������� ������� ������� � �����).
		/*int pos=db["Products"].DataBegin()+indexes[0]*db["Products"].RowLength()+
		db["Products"].FieldPosition(string("UnitInStock"));*/
		//int pos=db["Products"]->FieldPosInFile(indexes[0],"UnitInStock");
		//	fInOut.seekp(pos);
		//	fInOut.write((char*)(int*)row["Quantity"],sizeof(int));		
		cout<<"���������� �����? 1/0\n";
		cin>>isContinue;
	}while(isContinue);
	//	fInOut.close();
	db["OrderDetails"]->PrintTable(screenWidth);
	db["Products"]->PrintTable(screenWidth);

	//���������� � �� ��������� � �������� "Orders","OderDetails" � "Products"
	/*db["Orders"]->WriteDBTable("..\\CompanyBin\\Orders.bin");
	db["OrderDetails"]->WriteDBTable("..\\CompanyBin\\OrderDetails.bin");
	db["Products"]->WriteDBTable("..\\CompanyBin\\Products.bin");*/
	db.WriteDB();
}
//---------------------------------------
/*���������� ������ ����, ����������� �� ����� � ��������,
��� ������� ���������, ���� ������� �������� ��� � ������.
*/
dbmsLib::DBTable* StudentBooksList(dbmsLib::DBTableSet& db,int screenWidth)
{
	dbmsLib::Relation relation=db.GetRelation("StudentsAbonements");
	cout<<"������� ��� ��������\n";
	string name;
	cin>>name;
	//cout<<"������� StudentID\n";
	/*int id;
	cin>>id;
	Row selectRow;
	DBTable* selectStudents=db[relation.parentTable]->SelfRows("StudentID",Equal,&id);

	*/
	dbmsLib::Row selectRow;
	dbmsLib::DBTable* selectStudents=db[relation.parentTable]->SelfRows("Name",dbmsLib::Equal,&name);
	int studentID = -1;	
	selectStudents->PrintTable(screenWidth);
	cout<<"������� ID �������� ��� -1, ���� �������� ��� � ������\n";
	cin>>studentID;	
	vector<int> indexes=selectStudents->IndexOfRecord(&studentID,"StudentID");
	if(indexes.size() == 0){
		cout<<"������� "<< name<<" StudentID= "<<studentID<<" �� ������� � ����������\n";
		return db["Students"];
	}
	selectRow=(*selectStudents)[indexes[0]];
	dbmsLib::DBTable* childRowsStAb=db.ChildRows(relation,selectRow);
	cout<<"������� "<< name<<" StudentID= "<<studentID<<" ���� �����:"<<endl;
	childRowsStAb->PrintTable(screenWidth);
	cout<<"�� ����� � �������� "<< name<<":"<<endl;
	dbmsLib::DBTableBin booksAbSt("BooksAbSt",db["Books"]->GetHeader(),db["Books"]->GetPrimaryKey());
	indexes=childRowsStAb->IndexOfRecord(&nulDate,"DateOut");
	for(int i=0;i<indexes.size();i++)
		booksAbSt.AddRow(db.ParentRow(db.GetRelation("BooksAbonements"),(*childRowsStAb)[indexes[i]]),
		booksAbSt.GetSize());
	if(booksAbSt.GetSize()==0)
		cout<<"���� ���."<<endl;
	else
		booksAbSt.PrintTable(screenWidth);
	return &booksAbSt;
}
//----------menu( )---------------------------------  
int menu(string dbName,dbmsLib::DBDate today) 
{
	int action;
	cout<<"\n �� "<<dbName<< "\t ������� "<<today<< endl;
	cout<<"======= ��������� �� ����������������. ������� 0 =======\n";
	cout<<"1 - ������ �� �� �����\t\t 4 - ������������ \n";
	cout<<"2 - ������ ���� ������ ��\t 5 - ������ ������ �� � ����\n";
	cout<<"3 - ������ ������� � ����\t 6 - ������ ���� ��������\n";
	cout<<"7 - ������ ���� ��������\t 9 - ������ ������� �� �����\n"; 
	cout<<"10 - ������ �������\t\t11 - ��������� ���� ������ Hot Dog\n"; 
	cout<<"12 - ������ ������� �� ������\t13 - ������ .txt-������� � .bin-����\n"; 
	cout<<"14 - ������ � .txt-������� �� .bin-�����\n";
	cout<<"\t\t\t8 - �����\n";
	cout<<"===========================================================\n";
	cout<<("������� ����� ��������\n");
	cin>>action;
	while(cin.fail())
	{
		cin.clear();
		cin.ignore(10,'\n');					
		cout<<("������ �������. ��������� ���� ������ ��������\n");
		cin>>action;
	}			
	return action;
}
//=====================================================
void IncreasePriceHotDogBin(dbmsLib::DBTableSet& db){//!!!����� ������, ����� ��������
	//��������� �� ������� � ������� ��, � �� � �� �����.
	//������ ������ � ������� ������ �� � ������, ��� ������������� DBTableBin
	/*��������� ��������� ����� � ��������:
	����� ����� ������� - 4 �����
	��� ������� - 24 �����;
	����� ����� ������� primaryKey - 4 �����
	��� primaryKey - 24 �����;
	����� �������� � ��������� ������� (nColumn) - 4 �����;
	�����: ������ ��������� ������� - 60 ����;
	��������� ������� - nColumn*sizeof(ColumnDesc)= nColumn*72 ����;
	����� ������ ������ - 60 + 72*nColumn + sizeof(int); //sizeof(int) - 
	��� nRows.
	*/
	/*
	1. ������� "�������" ������ ��������� "��������� �� 1.5 ���� �������� Hot Dog",
	���� ����� ����������� ������������� � ���������� ��� ��������� ����� � ������
	��������� ������ ��, ������� ����� �� ���������.
	2. ����� �������� ��������� ������ � ������� � ����� ���������� ������������� 
	��� ������� ������� � ����� ������ ������ � ���������� �� �� ������� ���������
	"��������� �� 1.5 ���� �������� Hot Dog".
	3. ��������� ��������� ��������� ������ � ������� �� �������� ��������� ����� 
	� ������ ��������� ������ ��, ������� ����� �� ���������. 
	*/
	//1. ��������� �� 1.5 ���� �������� Hot Dog 
	string tabName = "Products";
	string dbName = "CompanyBin";
	string path="..\\"+dbName+"\\";
	fstream fInOut;//�������� ��������� ������ �� ����-�����
	fInOut.open((path+tabName+".bin").c_str(),ios::binary|ios::in|ios::out);
	if (!fInOut.is_open())	{ 
		cout<<"������ �������� �����\n"<< endl; 
		system("pause");
		return;
	}
	char primaryKey[dbmsLib::LENGTH+1];
	fInOut.seekg(2*sizeof(int)+dbmsLib::LENGTH);		
	fInOut.read((char*)primaryKey,dbmsLib::LENGTH);
	primaryKey[dbmsLib::LENGTH]='\0';
	string primKey(primaryKey);
	int hdrSize=0;
	fInOut.read((char*)&hdrSize,sizeof(int));
	//��������� �� ����� ��������� ������� � �������� ��� � table.columnHeaders
	dbmsLib::ColumnDesc colDesc;
	dbmsLib::Header hdr;
	dbmsLib::Header::iterator hdrIter;
	//���������� ����� ������ ������� � ������ �
	//�������� �� ������ ������ ������� primaryKey
	int rowLength=0;
	int primaryKeyBegin=0;
	int primaryKeyLength=0;
	for(int i=0; i<hdrSize; i++){
		fInOut.read((char*)&colDesc,sizeof(dbmsLib::ColumnDesc));
		hdr[colDesc.colName]=colDesc;//�������� �����������
		//(� map<string,ColumnDesc> ����������� �������� = )
		if(colDesc.colName==(string)primaryKey){
			primaryKeyBegin=rowLength;
			primaryKeyLength=GetLength(colDesc);
		}
		rowLength += GetLength(colDesc);
	}
	int nRows;//����� ����� � �������
	fInOut.read((char*)&nRows,sizeof(int));
	int headerBegin = sizeof(int)*2 + dbmsLib::LENGTH*2 + sizeof(int);
	int dataBegin = headerBegin + sizeof(dbmsLib::ColumnDesc)*hdrSize + sizeof(int);
	cout<<"��������� ������� "<<tabName<<":\n";
	cout<<"����� �������� hdrSize="<<hdrSize<<"  ����� ����� nRows="<<nRows<<endl;
	cout<<"rowLength="<<rowLength<<" ����; primaryKeyBegin="<<primaryKeyBegin<<
		" ����; primaryKeyLength= "<<primaryKeyLength<<" ����\n";		
	cout<<"headerBegin = "<<headerBegin<<" ����\n";
	cout<<"dataBegin = "<<dataBegin<<" ����\n";
	//����� � ����� ������� ������� ������ � ������ ProductID == "Hot Dog"
	dbmsLib::Row row;
	dbmsLib::Row::iterator rowIter;
	char buf[200];//����� �� ������ �������

	int i=0;//���������� ����� ������ "Hot Dog" � ������� "Products"
	for (i = 0; i < nRows; i++)
	{
		fInOut.seekg(dataBegin+i*rowLength+primaryKeyBegin);
		fInOut.read(buf,primaryKeyLength);
		buf[primaryKeyLength]='\0';
		if(!strcmp("Hot Dog",buf)){
			cout<<"i = "<<i<<" primaryKey = "<<buf<<endl;
			break;
		}
	}
	//���������� �������� ���� "UnitPrice" � ������ ������� "Products"
	fInOut.seekg(dataBegin+i*rowLength);
	int unitPriceBegin=0;
	for(hdrIter=hdr.begin();hdrIter!=hdr.end();hdrIter++){
		if(hdrIter->first==(string)"UnitPrice")
			break;
		unitPriceBegin+=GetLength(hdrIter->second);
	}
	cout<<"unitPriceBegin="<<unitPriceBegin<<endl;
	//��������� ����� ����
	fInOut.seekg(dataBegin+i*rowLength+unitPriceBegin);
	double unitPrice=0;
	fInOut.read((char*)&unitPrice,sizeof(double));
	cout<<"oldPrice="<<unitPrice<<endl;
	unitPrice+=1.5;
	cout<<"newPrice="<<unitPrice<<endl;
	//���������� ����� ���� ������ "Hot Dog" � ���� ��.
	fInOut.seekp(dataBegin+i*rowLength+unitPriceBegin);
	fInOut.write((char*)&unitPrice,sizeof(double));
	fInOut.close();		
}
//=========================================
//��������� ���� ������ � ������� � � ����� � �������������� ������� 
//������� � ������ � �����
void ChaingePrice(dbmsLib::DBTableSet &db, string tabName){
	//	DBTableBin products( tabName);//???����� ����� ��� ����� ��� ��������������
	//������ � ������ ������ ����� ������� ��������� � db["Products"].
	//����� ������ �����: ��� �����������, �� � ������ �������� � ������ ��� 
	//������ ��������� � ����
	string fileName="..\\"+db.GetDBName()+"\\"+tabName+TabNameExtension(db.GetDBName());
	cout<<"��������� ������� "<<tabName<<":\n";
	string primKey("Hot Dog");//�������� ���������� �����, ����� �� �������
	vector<int> indexes=db[tabName]->IndexOfRecord(&primKey,"ProductID");
	int ind=indexes[0];//�.�. "Hot Dog" - primKey, �� indexes.size()=1 
	//��������� ����� ����
	dbmsLib::Row row=(*db[tabName])[ind];
	double price=*(double*)(*db[tabName])[ind]["UnitPrice"];
	cout<<"oldPrice="<<price<<endl;
	//���������� ����� ���� ������ "Hot Dog" � ������� "Products", �� �� � ��.
	//� ������� ���������� ������ �������.
	price=price+1.5;
	row["UnitPrice"]=new double(price);//!!! ����������� new
	db[tabName]->AddRow(row,ind);
	cout<<"newPrice="<<price<<endl;
	//���������� ������� "Products" c ���������� ����� ������ "Hot Dog" � ���� ��.
	db[tabName]->WriteDBTable(fileName);//����������� ����� ����������� �������.
	//��� �� ��������������� ��� ������ �� �����, ��������� ���������� �� ����������.
	//-------------------------------------------------------------
	// ������ � �������� ���� � �������������� ������� �������
	//���������� ����� ���� ������ "Hot Dog" � ���� ��.
	//� ���� ����� ���������� ����� ����� ������. 
	//����� ���������� ���� "UnitPrice" (8 ������) � ������ � ������� ind.
	//int pos=db[tabName]->FieldPosInFile(ind,"UnitPrice");
	//fstream fInOut;//�������� ��������� ������ �� ����-�����
	//fInOut.open(fileName.c_str(),ios::binary|ios::in|ios::out);
	//if (!fInOut.is_open())	{ 
	//	cout<<"������ �������� �����\n"<< endl; 
	//	system("pause");
	//	return;
	//}
	//fInOut.clear();//!!!��������, �� ������ ������, ���� EOF, 
	////������� ����� ������������ � ���������� ������ �����
	//fInOut.seekp(pos);
	//fInOut.write((char*)&price,sizeof(double));
	//fInOut.close();	
}
//==========================================
/*� ������ ������ DBTable, ������� ��������� ����� ������� � ������� ��:
db[tabName].WriteToFileBin(pathBin+tabName), db[tabName].ReadFromFileBin(pathBin+tabName)
db[tabName].WriteToFileTxt(pathTxt+tabName), db[tabName].ReadFromFileTxt(pathTxt+tabName)
db[tabName].WriteToFile(path+tabName) db[tabName].ReadFromFile(path+tabName),
� �������� ��������� ���������� "�������������" ���� � �����. 
��� ������ ������� �� ������� �������� ������ � �����.
������� ������ ������ 
db[tabName].Print(screenWidth) � db[tabName].PrintTable(screenWidth)
��������� ������ ��� �������, ��� ��� ��� ����� ������ �� �������� DBTable, � �� �� ������.
��� ������ DBTableBin � DBTableTxt, ������� ���������� ���������, ������������ ���� � ��� 
�� ����� ������ db[tabName].PrintTable(screenWidth). �������� screenWidth - 
������ ������ � ������.
*/
//-------------------------------------------------------------
void DeliveryBooksToStudents(dbmsLib::DBTableSet &db,int screenWidth){
	/*������ ���� �������� � ����������:
	1. �������� �������� � ����������, ���� �� ��� �� ������� (����. Students).
	2. ��������� ������� ����� � ���������� � �� ����� � ��������. � ���� �� ������ ���� 
	����� ������ ���������� �����(����. Books, Students � Abonements: BookId, StudentId ). 
	3. ����� ������� ������� �������� ������� ���������� ����� � �������������� (����. Books).
	4. ������ ��������� � ������� Books � Abonements. (����� ������� ������� ������ � ������,
	��������� ���������� �������, � �����,���� ��� �������� ��!, ������ ��������� ������ � �� �
	������ ��������� � ���������� ���������� ��������.
	*/

	//������ ���������� ���� ��������
	//	string tabName = "Students";
	cout<<"������� ��� ��������\n";
	string name;
	cin>>name;
	string dbName = db.GetDBName();
	string path="..\\"+dbName+"\\";
	//�������� ������� �������� � �� ���������� 
	if((db["Students"]->IndexOfRecord(&name, "Name").size()==0)){
		//��������"Name"  �� "StudentID"(����� ������������� ������),
		//����� ����� ���� �������� ������������
		cout<<"� �� ��� ������ � �������� "<<name<< endl;
		cout<<"�������� �������� � ������ ��������� ����������? ('y'/'n')"<<endl;
		char choice;
		cin>>choice;
		if(choice=='y'){
			dbmsLib::Row row=db["Students"]->CreateRow();
			db["Students"]->AddRow(row,db["Students"]->GetSize());
		}else return;
	}
	db["Students"]->PrintTable(78);
	int studId;
	cout<<"�������� � ������� StudentID"<<endl;//��� ��� ����� ���� ������������
	cin>>studId;
	bool isContinue=false;
	do{
		db["Books"]->PrintTable(78);
		int bookId;
		cout<<"�������� � ������� BookID"<<endl;
		cin>>bookId;
		// �������� ������� ���������� ����� � ���������� � ���������� � � ��������
		vector<int> indexes=db["Books"]->IndexOfRecord(&bookId,"BookID");
		if(indexes.size()==0){
			cout<<"� ���������� ��� ���� � �������� "<<bookId<<endl;
			return;
		}
		if((*(int*)(*db["Books"])[indexes[0]]["Quantity"])<=
			(*(int*)(*db["Books"])[indexes[0]]["Number"])){
				cout<<"� ���������� ��� ��������� ����������� ���� � �������� "<<bookId<<endl;
				return;
		}
		// �������� ���������� ���������� ����� � ��������: 
		// ������� �� ���� ����� ��� ����, �� ������ �
		dbmsLib::DBTable* studIdBooks=db["Abonements"]->SelfRows("StudentID",dbmsLib::Equal,&studId);
		cout<<"���������� ����, ������� ���������� �������� StudentID="<<studId<<endl;
		studIdBooks->PrintTable(screenWidth);
		dbmsLib::DBTable* studIdBookId=studIdBooks->SelfRows("BookID",dbmsLib::Equal,&bookId);
		vector<int> bookIdIndexes=studIdBookId->IndexOfRecord(&bookId,"BookID");
		if(studIdBookId->GetSize()!=0)
		{
			cout<<"���������� ���� BookID="<<bookId<<" � �������� StudentID="<<studId<<endl;
			studIdBookId->PrintTable(screenWidth);
			dbmsLib::DBDate returnDate("1.1.1");
			//�������� �������� ����� bookId (������� ����� ����� ��������� ��� � ����������
			//���� � �� �� �����).
			for(int i=0; i<bookIdIndexes.size();i++)
				if(*((dbmsLib::DBDate*)(*studIdBookId)[bookIdIndexes[i]]["DateOut"])==returnDate){
					cout<<"����� �� ����� ���� ������, �.�. ��� ���� � �������� "<<name<<endl; 
					return;
				}
		}
		//������ ����� � �������� ��������������� ��������� � ��
		cout<<"���������� ������ � ������� Abonements � �������� ��������� � ������� Books"<<endl;
		dbmsLib::Row row=db["Abonements"]->CreateRow();
		db["Abonements"]->AddRow(row,db["Abonements"]->GetSize());
		vector<int> bookIndexes=db["Books"]->IndexOfRecord(&bookId,"BookID");
		(*((int*)((*db["Books"])[bookIndexes[0]]["Number"])))++;//!!!
		cout<<"���������� � ����������� ���������� ������ �����"<<endl;
		db["Abonements"]->PrintTable(screenWidth);
		db["Books"]->PrintTable(screenWidth);
		cout<<"���������� �����? 1/0\n";
		cin>>isContinue;
	}while(isContinue);
	
	//db["OrderDetails"]->PrintTable(screenWidth,db.GetDBName());
	//db["Products"]->PrintTable(screenWidth,db.GetDBName());

	//���������� � �� ��������� � �������� Abonements,Books � Students
	//db["Abonements"]->WriteDBTable(path+"Abonements.txt");
	//db["Books"]->WriteDBTable(path+"Books.txt");
//	db["Students"]->WriteDBTable(path+"Students.txt");
	db.WriteDB();

}
//-------------------------------------------------------------
void Testing(string dbName,string tabName){
	string path="..\\LibraryBin\\Books.bin";
	dbmsLib::DBTableBin books;
	books.ReadDBTable(path);
	books.PrintTable(64);
	fstream fInOut(path,ios::in|ios::out|ios::binary);
	int bookId=1;
	vector<int> bookIndexes=books.IndexOfRecord(&bookId,"BookID");	
	//���������� ��������� � ������� Books � ����,
	//��������� ������ ������ � ������ � ����� (��� ����������� ������� ������� � �����).
	int pos=books.FieldPosInFile(bookIndexes[0],"Number");
	fInOut.seekp(pos);
	int number=2;
	fInOut.write((char*)&number,sizeof(int));		
	fInOut.close();
	books.ReadDBTable(path);
	books.PrintTable(64);	
}
//--------------------------------------------------------
void main()
{
	system("chcp 1251 > nul");
//	cout<<"������� ��� ��\n";//���������������� ��� �������� ������������ ��� �������
	string dbName("LibraryBin");//("LibraryBin","CompanyBin","LibraryTxt",CompanyTxt);
//	cin>>dbName;
	cout<<dbName<<endl;
	dbmsLib::DBTableSet db(dbName);
	string path="..\\"+dbName+"\\";
	//	cout<<"������� ������� ���� dd.mm.yyyy\n";
	string str("21.04.2018");
	//	cin>>str;
	dbmsLib::DBDate today(str);
	//	cout<<"������� ������ ������ � ��������\n";
	int screenWidth=78;
	//	cin>>screenWidth;
	string tabName="Products";//"Students";"TableRelations";"Abonements";"Books"
	//"Products";"OrderDetails";"Orders";"Customers"
	string pathBin="..\\LibraryBin\\";//CompanyBin, LibraryBin
	while(true)
	{ 
		switch (menu(dbName,today))
		{
		case 1: db.ReadDB();//������ ������ ��. 
			//�� �������� � ����� "..\\"+dbName+". 
			//��� �� ������������ ��� �� Txt, ���� ������� �� �������� � ��������� ������,
			//��� �� Bin, ���� ������� �� �������� � �������� ������. ��������,
			//"LibraryBin","CompanyBin","LibraryTxt","CompanyTxt".
			//������ ������� �������� � ��������� ����� � ������ = <��� �������>+<.txt | .bin>
			//������ ������ ����� �������� ��� ������� � ��� ������� � ��������� ������
			//������ ������ ����� - ��������� �������.
			//��� ����������� ������ - ������ �������. 
			//� �� ������ ���� ������ � ��������� �������� � ����� � ������ DBTables.txt, 
			//� �������� ������ ����� ��������� - � ����� � ������ DataRelations.txt
			break;
		case 2: db.PrintDB(screenWidth);//������ ���� ������ �� (�� 4 ������� � ������)
			break;
		case 3: db[tabName]->WriteDBTable(path+tabName+TabNameExtension( dbName));break;//pathBin
		case 4: Testing(dbName,tabName); break; 
		case 5: db.WriteDB(); break;
		case 6: StudentBooksList(db,screenWidth); break;
		case 7: DeliveryBooksToStudents(db,screenWidth); break;
		case 9:	db[tabName]->ReadDBTable(path+tabName+TabNameExtension( dbName)); break;
		case 10:db[tabName]->PrintTable(screenWidth); 
			//db.GetDBName() - ��� ���������������, ����� ����� ���� �� 
			//������������� DBTableTxt � DBTableBin. 
			break;
		case 11:ChaingePrice(db,tabName); break;
		case 12: ExecuteOrder(db,screenWidth);break;
		case 13:((dbmsLib::DBTableTxt*)db[tabName])->WriteTableBin(pathBin+tabName+".bin");break;
		case 14:((dbmsLib::DBTableTxt*)db[tabName])->ReadTableBin(pathBin+tabName+".bin");break;
		case 8: return;
		default: cout<<(" ���� ������� ����� �� 1 �� 8\n"); break;
		}    	
	}	
	system("pause");
}
