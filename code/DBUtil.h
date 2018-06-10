#include <string>


using namespace std;
class DBUtil {


public:

	/************************************************************
	��װ sqlite3����
	************************************************************/
	//��������һ��db���ݿ� dbΪ���ݿ������  
	//  �����ݿ�  
	static void initDB(const char *db);

	//�����жϱ���Ƿ����  
	// name:��ʾ����  
	static bool tableIsExist(string name);


	//��������һ������Ϊname�ı�񣬴���ʱ����ƥ��ʱ���иñ�Ĵ�����������򲻴���  
	//������  
	static void createTable(string sql, string name);

	//����ɾ��һ�ű���Ϊname�ı��ɾ��ʱ����ƥ���Ƿ��иñ�Ĵ��������������ִ��ɾ������  
	//ɾ������  
	static void deleteTable(string sql, string name);

	//��������в���һ������  
	//����һ������  
	static void insertData(string sql);

	//���������ɾ��һ������  
	//ɾ��һ������  
	static void deleteData(string sql);

	//����������޸�һ������  
	// �޸�һ������  
	static void updateData(string sql);

	//��ȡһ����¼������  
	// ��ü�¼������  
	static int getDataCount(string sql);

	//��ȡ��
	static int* getTable(string sql);

	//�رմ򿪵����ݿ�  
	static void closeDB();

};