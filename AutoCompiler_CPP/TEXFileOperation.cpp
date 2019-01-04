#include "pch.h"
#include "TEXFileOperation.h"

using namespace std;

KTEXFileOperation::KTEXFile::KTEXFile()
{
	
}
KTEXFileOperation::KTEXFile::KTEXFile(wstring InputFileName)
{
	ifsTEX.open(InputFileName,ios::binary);
	bool success=true;
	if (ifsTEX.bad())
	{
		success = false;
		wcout << L"�ļ���/��ȡʧ��" << endl;
	}

	unsigned int inputHeader;
	//fsTEX.seekg(0);
	ifsTEX.read((char*)(&inputHeader), 4);//ע�����ţ��ұ����˼���
	inputHeader >>= 16;
	if (inputHeader != Header.ktexheader)
	{
		success = false;
		wcout << L"����Klei TEX" << endl;
	}





	if(success)
		wcout << L"KTEXFileOperation::KTEXFile " << InputFileName << L" ���";
	else
		wcout << L"KTEXFileOperation::KTEXFile " << InputFileName << L" ʧ��";
}
KTEXFileOperation::KTEXFile::~KTEXFile()
{
	ifsTEX.close();
	ofsTEX.close();
}
