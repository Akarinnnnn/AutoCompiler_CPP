#include "localizition.h"

using namespace std;

#include <cstdio>
//Default stringtables
auto s1 = L"����ָ���ļ����ڵ�����tex�ļ�\n\n\n\n";
auto s2 = L"�����ļ��е�·��\n";//path
auto s3 = L"����mods�ļ��е�·���Կ�ʼת����\n";//modspath
auto s4 = L"==========================��ʼת��========================\n\n";//convert
auto s5 = L"========================��ʼ�����ļ�======================\n\n\n\n";//iterate files
auto s6 = L"�ļ�/�ļ���������";//gamble
auto s8 = L"���";//Done.
auto s9 = L"��ʼ����";
localizition::localizition()
{
	FILE* stable = nullptr;
	auto err = _wfopen_s(&stable, L"stringtables.txt", L"r");
	while (!feof(stable))
	{
		fscanf_s(stable, "%s\n")
	}
}