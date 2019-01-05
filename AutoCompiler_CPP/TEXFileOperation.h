#pragma once
#include "basetsd.h"
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <iostream>
#include "lodepng.h"
#include "ImageOpreration.h"

namespace KTEXFileOperation
{ 
	struct  //platform
	{
		char pc = 12;
		char xb360 = 11;
		char ps3 = 10;
		char unk = 0;
	}platfrm;
	struct  //pixel form
	{
		char ARGB = 4;
		char DXT1 = 0;
		char DXT3 = 1;
		char DXT5 = 2;
		char unk = 7;
	}pixfrm;
	struct  //texture type
	{
		char d1 = 1;//1d
		char d2 = 2;//2d
		char d3 = 3;//3d
		char cube = 4;//cubemap
	}textyp;
	typedef std::vector<unsigned char> uc_vector;
	struct KTEXHeader
	{
		const unsigned int ktexheader = 0x4B544558;//�ļ�ͷ,"KTEX",��ACSIIֵ��ʾ
		//����
		unsigned int platform = (unsigned int)platfrm.pc;
		unsigned int pixelformat = (unsigned int)pixfrm.DXT3;
		unsigned int texturetype = (unsigned int)textyp.d2;
		unsigned int mipscount = 0;
		unsigned int flags = 0;
		unsigned int remainder = 0;
		//unsigned int remainder;
		//end
		//��һ���ݿ�
		unsigned int firstblock=0x3FF00000;//�ṹ��ͼKTEX_HEADER.bmp(��껭������)
		//0x3FF 12bit, flags 2bit, mipscount 5bit, textype 4byte
		//pixelformat 5bit, platform 4bit
	};

	struct mipmap
	{
		unsigned short width;//X axis
		unsigned short height;//Y axis
		unsigned short Z;
		std::iostream* data;
	};
	

	struct PNGPIXEL//a,r,g,b
	{
		unsigned char
			*A,
			*R,
			*G,
			*B;
	};

	class KTEXFile
	{
	public:

		bool ConvertFromPNG(uc_vector inputvec);//Warning: This function will clear fsTEX
		void setoutput(wstring);
		KTEXFile(std::wstring InputFileName);
		KTEXFile();
		~KTEXFile();
	private:
		void KTEXHeaderGen();
		wstring output;
		std::fstream fsTEX;
		KTEXHeader Header;
		uc_vector vecPNG;
	};
	void movepixel(PNGPIXEL& p);
	void movepixel(PNGPIXEL& p,int count);
}



