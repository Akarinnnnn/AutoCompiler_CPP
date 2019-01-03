#include "pch.h"

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <exception>

#include "basetsd.h"//exists in VC++

#include "ImageOpreration.h"
//wchar_t = 2B(16 bits)
constexpr UINT64 PNG_HEADER =  0x89504E470D0A1A0A;//8Bytes



using namespace std;

namespace ImageOperation
{
	bool ExportImage(
		std::wstring InputPNGName//png only
	)
	{
		wifstream InputFile(InputPNGName, ios::binary);
		if (!InputFile.good())
		{
			wcout << L"�ļ���" << endl;
			return false;
		}
		UINT64 inputHeader;
		InputFile.read((wchar_t*)&inputHeader, 4);
		if (inputHeader == PNG_HEADER)
		{
			wcout << L"����PNG�ļ�ͷ" << endl;
			return false;
		}
		InputFile.seekg(16);
		UINT32 Width = 0;
		UINT32 Height = 0;

		InputFile.read((wchar_t*)&Width, 2);
		InputFile.seekg(2, ios::cur);
		InputFile.read((wchar_t*)&Height, 2);

		if (!(Width - 1 & Width) && (Height - 1 & Height)/*&&(Width==Height)*/)
		{
			wcout << L"��������2���������ݣ�û������" << endl;
			return false;
		}
		//TODO: Convert Code
		return true;
	}

	bool Convert(std::wstring sourcefile, std::wstring destfile)
	{
		return false;
	}
}


template<typename T>
bool ArrayCompare(T array1, T array2,UINT64 length1)//���鳤�ȳ�ʵһ�㣬��bug�����
{
	for (UINT64 i=0;; i++)
	{
		if (*(array1+i) != *(array2+i))
			return false;
	}
	return true;
}