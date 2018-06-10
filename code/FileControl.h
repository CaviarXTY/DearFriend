#pragma once
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
class FileControl
{
public:
	FileControl();

	//读取文件
	string LoadInf(string filename, string key);

	//改些文件
	void modifyFile(string fileName, string name, string value);

};

