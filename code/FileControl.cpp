#include "FileControl.h"




FileControl::FileControl()
{
	cout << "文件操作";
}

//读取文件
string FileControl::LoadInf(string filename, string key) {
	ifstream in(filename);
	char ch[20];
	string str[20];
	int i = 0;
	while (!in.eof()) {
		in.getline(ch, 20);
		str[i] = ch;
		if (str[i].find(key, 0) == 0) {
			return str[i];
		}
		i++;
	}
	in.close();
	return "";
}

//改写文件
void modifyFile(string fileName, string name, string value) {

	string out_name = fileName + ".tmp";

	ifstream in(fileName);
	ofstream out(out_name);
	char ch[20];
	string str[20];
	int i = 0;
	while (!in.eof()) {
		in.getline(ch, 20);
		str[i] = ch;
		if (str[i].find(name, 0) == 0) {
			str[i] = name + "=" + value;
		}
		out << str[i] << endl;
		i++;
	}
	in.close();
	out.close();

	const char*fn = fileName.c_str();	//转格式 remove()参数用const char*
	const char*tmp = out_name.c_str();
	remove(fn);//删除文件  
	rename(tmp, fn);//将b.txt重命名为c.txt  
}

