#pragma once
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
class FileControl
{
public:
	FileControl();

	//��ȡ�ļ�
	string LoadInf(string filename, string key);

	//��Щ�ļ�
	void modifyFile(string fileName, string name, string value);

};

