#include "pch.h"
#include "TEXFileOperation.h"

template<typename T>
inline bool ArrayCompare(T array1[4], const T array2[4], UINT64 count)
{
	//UINT64 p1,p2 =(UINT64*)array1,(UINT64*)array2
	for (UINT64 i = 0; i < count; i++)
	{
		if (*(array1 + i) != *(array2 + i))
		{
			return false;
		}
	}
	return true;
}

void KTEXFileOperation::ReverseByByte(char* p, UINT64 bytecount)//p���ǿ��ת������
{
	char mid = 0;
	for (unsigned long long i = 0; i < (bytecount / 2); i++)
	{
		mid = *(p + (bytecount - i - 1));
		*(p + (bytecount - i - 1)) = *(p + i);
		*(p + i) = mid;
	}
}

using namespace std;

KTEXFileOperation::KTEXFile::KTEXFile()
{
	
}

KTEXFileOperation::KTEXFile::KTEXFile(string InputFileName)
{
	fsTEX.open(InputFileName, ios::in | ios::out | ios::binary);
	cout << "KETXFileOperation::KTEXFile::KTEXFile ����" << InputFileName << endl;
	bool success=true;
	char inputHeader[4]{0};

	if (fsTEX.fail())
	{
		success = false;
		
#ifdef KTEXEXCEPTION
		throw KTEXexception("��ȡʧ��")
#else
		cout << "��ȡʧ��" << endl;
		goto failure;
#endif 

	}
	if (fsTEX.bad())
	{
		success = false;
#ifdef KTEXEXCEPTION
		throw KTEXexception("�ļ���")
#else
		cout << "�ļ���" << endl;
		goto failure;
#endif
	}

	fsTEX.read(inputHeader, 4);//ע�����ţ��ұ����˼���
	ReverseByByte((char*)(&inputHeader),4);
	if (inputHeader == Header.ktexheader)
	{
		success = false;
		cout << "����Klei TEX" << endl;
	}

	if(success)
		cout << "KTEXFileOperation::KTEXFile " << InputFileName << " ���";
	else
		failure:
		cout << "KTEXFileOperation::KTEXFile " << InputFileName << " ʧ��";
}//��������
KTEXFileOperation::KTEXFile::~KTEXFile()
{
	fsTEX.close();
}

inline void KTEXFileOperation::KTEXFile::KTEXFirstBlockGen()
{
	constexpr unsigned int head = 0x4B544558;

	KTEXHeader tempHeader = this->Header;

	tempHeader.platform = head & 0xF;
	tempHeader.pixelformat = (head >> 4) & 0x1F;
	tempHeader.texturetype = (head >> 9) & 0xF;
	tempHeader.mipscount = (head >> 13) & 0x1F;
	tempHeader.flags = (head >> 18) & 3;
	//tempHeader.remainder = (head >> 20) & 0xFFF;

	tempHeader.flags <<= 18;
	tempHeader.mipscount <<= 13;
	tempHeader.texturetype <<= 9;
	tempHeader.pixelformat <<= 4;
	//tempHeader.platform<<=0;
	
	unsigned int* p = &tempHeader.flags;
	for(char i=0;i<=4;i++ )
		Header.firstblock |= *(p+i);
}

bool KTEXFileOperation::KTEXFile::ConvertFromPNG()
{
	using namespace lodepng;
	namespace fs = std::filesystem;
	uc_vector image;//RGBA
	uc_vector ret;
	State imgstate;
	unsigned int wide, height;
	decode(image, wide, height, imgstate, this->vecPNG);

	unsigned char* imgdata=nullptr;
	unsigned char* retdata=nullptr;
	
	ret.resize(wide*height*4);
	
	imgdata = image.data();
	retdata = ret.data();

	ofstream ofstex(output,ios::binary|ios::trunc);
	if(!ofstex.is_open())
		_NOT_OPEN;

	KTEXFirstBlockGen();//���ɵĵ�һ���ݿ���������⣬Ҳ�����㷨����

	ofstex.write("KTEX", 4);
	ofstex.write((char*)(&(Header.firstblock)), 4);//С���ֽ���
	
	//�ļ���ȱһ��mipmap

	switch(Header.pixelformat)//���ظ�ʽ
	{ 
		case (pixfrm.ARGB):
			ofstex.write((char*)image.data(), wide*height);
			break;
		case (pixfrm.DXT1):
			squish::CompressImage(imgdata, wide, height, retdata, squish::kDxt1);
			ofstex.write((char*)ret.data(), wide*height);
			break;
		case (pixfrm.DXT3):
			squish::CompressImage(imgdata, wide, height, retdata, squish::kDxt3);
			ofstex.write((char*)ret.data(), wide*height);
			break;
		case (pixfrm.DXT5):
			squish::CompressImage(imgdata, wide, height, retdata, squish::kDxt5);
			ofstex.write((char*)ret.data(), wide*height);
			break;
	}

	//fsTEX.
	ofstex.close();
	return true;
}

int __fastcall KTEXFileOperation::KTEXFile::LoadPNG(std::string Input)
{
	
	return lodepng::load_file(this->vecPNG, Input);
}

//exception
KTEXFileOperation::KTEXexception::KTEXexception()noexcept
{

}

KTEXFileOperation::KTEXexception::KTEXexception(char * MSG)
{
	this->data.data = MSG;
}

KTEXFileOperation::KTEXexception::~KTEXexception()
{}

const char * KTEXFileOperation::KTEXexception::what()noexcept
{
	return this->data.data;
}

KTEXFileOperation::KTEXexception & KTEXFileOperation::KTEXexception::operator=(KTEXexception a)
{
	// TODO: �ڴ˴����� return ���
	if (this == &a)
	{
		return *this;
	}
	this->data.data = a.data.data;
	this->data.dofree = a.data.dofree;

	return *this;
}
