#pragma once
namespace TEXFileOperation
{ 
	struct TEXHeader
	{
		//const char ktex[] = { 'K','T','E','X' };
		const unsigned int ktexheader =0x //(unsigned int)"KTEX";//��֪���ܲ��ܱ���ͨ��//FNMDP

	};
	class TEXFileOperation
	{
		TEXFileOperation(TEXHeader inputHeader);
	};
}