#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <exception>
#include "lodepng.h"
#include "squish.h"
//#include <filesystem>
#ifdef KTEXEXCEPTION //Ҫ�����쳣�Ͷ������
#define _FAIL throw std::runtime_error("��ȡʧ��")
#define _BAD throw std::runtime_error("�ļ���")
#define _NOT_OPEN throw std::runtime_error("��ʧ��")
#define _WH_OUT_OF_RANGE throw std::out_of_range("ͼƬ��/�߳���65535")
#define _UNKPIXEL throw std::invalid_argument("δ֪���ظ�ʽ")
#else
#define _FAIL return false;
#define _BAD return false
#define _NOT_OPEN return false
#define _WH_OUT_OF_RANGE return false
#define _UNKPIXEL return false
#endif

namespace KTEXFileOperation
{
	
	struct  //platform
	{
		char pc = 12;
		char xb360 = 11;
		char ps3 = 10;
		char unk = 0;
	}constexpr platfrm;
	struct  //pixel form
	{
		char ARGB = 4;
		char DXT1 = 0;
		char DXT3 = 1;
		char DXT5 = 2;
		char unk = 7;
	}constexpr pixfrm;
	struct  //texture type
	{
		char d1 = 1;//1d
		char d2 = 2;//2d
		char d3 = 3;//3d
		char cube = 4;//cubemap
	}constexpr textyp;
	typedef std::vector<unsigned char> uc_vector;
	
	struct KTEXHeader
	{
		const char ktexheader[4] = { 0x4B,0x54,0x45,0x58 };//�ļ�ͷ,"KTEX",��ACSIIֵ��ʾ
		//����
		unsigned int flags = 0;
		unsigned int mips = 1;
		unsigned int texturetype = (unsigned int)textyp.d1;
		unsigned int pixelformat = (unsigned int)pixfrm.DXT5;
		unsigned int platform = (unsigned int)platfrm.pc;
		//unsigned int remainder = 0;
		//unsigned int remainder;
		//end
		//��һ���ݿ�
		unsigned int firstblock=0xFFF00000;//�ṹ��ͼKTEX_HEADER.bmp(��껭������)
		//0x3FF 12bit, flags 2bit, mipscount 5bit, textype 4byte
		//pixelformat 5bit, platform 4bit
	};

	struct mipmap
	{
		unsigned short width=0;
		unsigned short height=0;
		unsigned short Z=1;//Z Axis
		uc_vector* pdata;
	};
	typedef std::vector<mipmap> mipmap_vector;
	typedef std::vector<uc_vector> imgs;
	class KTEXFile
	{
	public:
		bool ConvertFromPNG();
		int __fastcall LoadPNG(std::string InputPngFileName);//ʹ��lodepng 
		//KTEXFile(std::string InputKtexFileName);//���� KTEX,ûŪ��
		KTEXFile();
		~KTEXFile();
		
		std::string output;//����ļ�λ��

		KTEXHeader Header;
	private:
		int __fastcall KTEXMipmapGen(mipmap& target,uc_vector argb_image,unsigned short width,unsigned short height,unsigned short pitch);
		void KTEXFirstBlockGen();
		void __fastcall multimipmapgen(KTEXFileOperation::mipmap_vector mipmaps, imgs inputimgs);

		std::fstream fsTEX;
		mipmap_vector vec_mipmaps;
		imgs vec_imgs;
		uc_vector vecPNG;
		mipmap mipmap;//��ʱ����
	};

}
