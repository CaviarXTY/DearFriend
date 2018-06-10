#include "DBUtil.h"
#include "sqlite3.h"
#include <string>
#include "cocos2d.h"
#include <fstream>

using namespace std;
using namespace cocos2d;

sqlite3 *pDB = NULL;//���ݿ�ָ��  
char * errMsg = NULL;//������Ϣ  
std::string sqlstr;//SQLָ��  
int result;//sqlite3_exec����ֵ  


//�������ݿ�  
void DBUtil::initDB(const char *db)
{
	//��һ�����ݿ⣬��������ݿⲻ���ڣ��򴴽�һ�����ݿ��ļ�  
	result = sqlite3_open(db, &pDB);
	if (result != SQLITE_OK)
		CCLOG("�����ݿ�ʧ�ܣ�������:%d ������ԭ��:%s\n", result, errMsg);
}


//tableIsExist�Ļص�����  
int isExisted(void * para, int n_column, char ** column_value, char ** column_name)
{
	bool *isExisted_ = (bool*)para;
	*isExisted_ = (**column_value) != '0';
	return 0;
}



//�жϱ���Ƿ����  
bool DBUtil::tableIsExist(string name)
{
	if (pDB != NULL)
	{
		//�жϱ��Ƿ����  
		bool tableIsExisted;
		sqlstr = "select count(type) from sqlite_master where type='table' and name ='" + name + "'";
		result = sqlite3_exec(pDB, sqlstr.c_str(), isExisted, &tableIsExisted, &errMsg);
		return tableIsExisted;
	}
	return false;
}



//�����ݿ����ж���Ϊname�ı�ʾ����ڣ�����������򴴽����ű�  
//@ʾ�����string sqls = "create table user(id integer,username text,password text)";  
void DBUtil::createTable(string sql, string name)
{
	if (!tableIsExist(name))
	{
		//����������IDΪ���������Զ�����  
		result = sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errMsg);
		if (result != SQLITE_OK)
			CCLOG("������ʧ�ܣ�������:%d ������ԭ��:%s\n", result, errMsg);
	}
}


//ɾ�����  
//@ʾ�����sqlstr="drop table name";  
void DBUtil::deleteTable(string sql, string name)
{
	if (tableIsExist(name))
	{
		result = sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errMsg);
		if (result != SQLITE_OK)
			CCLOG("������ʧ�ܣ�������:%d ������ԭ��:%s\n", result, errMsg);
	}
}


//��������  
//@ʾ�����sqlstr=" insert into MyTable_1( name ) values ( '������' ) ";  
void DBUtil::insertData(string sql) {
	result = sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		CCLOG("�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n", result, errMsg);
}


//ɾ������  
//@ʾ�����sqlstr="delete from MyTable_1 where ID = 2";  
void DBUtil::deleteData(string sql)
{
	result = sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		CCLOG("�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n", result, errMsg);
}


//�޸�����  
//@ʾ�����        sqlstr="update MyTable_1 set name='������' where ID = 3";  
void DBUtil::updateData(string sql)
{
	result = sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		CCLOG("�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n", result, errMsg);
}


//getDataCount�Ļص�����  
int loadRecordCount(void * para, int n_column, char ** column_value, char ** column_name)
{
	int *count = (int*)para;
	*count = n_column;
	return 0;
}
//��ȡ��¼������  
//@ʾ�����string sqlsssss = "select count(*) from user";  
//@ʾ�����  ȡ�ñ���ֶε����string sqlsssss = "select * from user";  
int DBUtil::getDataCount(string sql)
{
	int count = 0;
	sqlite3_exec(pDB, sql.c_str(), loadRecordCount, &count, &errMsg);
	return count;
}

//��ѯ����¼
int* DBUtil::getTable(string sql) {
	char** pResult;
	int nRow;
	int nCol;
	//��n�е����ƣ������pResult [nRow] 
	//��n�е�m�е����ݣ������pResult [(nRow+ 1) * nCol + m] 
	result = sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errMsg);
	if (result != SQLITE_OK)
	{
		sqlite3_close(pDB);
		CCLOG("�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n", result, errMsg);
		sqlite3_free(errMsg);
	}

	int nIndex = nCol;
	int *intTemp = new int[nCol*nRow];

	for (int i = 0; i < ((nCol*nRow)); i++)
	{
		intTemp[i] = atoi(pResult[nIndex]); 
		nIndex++;
	}
	sqlite3_free_table(pResult);  //ʹ���������ͷ�Ϊ��¼������ڴ棬������ڴ�й©
	sqlite3_close(pDB);
	return intTemp;
}



//�ر����ݿ�  
void DBUtil::closeDB()
{
	sqlite3_close(pDB);
}