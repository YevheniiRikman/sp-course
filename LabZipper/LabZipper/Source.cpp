#include <stdio.h>
#include <locale.h>
#include <tchar.h>
#include <Windows.h>
#include <iostream>
#include <string>

#define FILE_MAX_LENGTH 1024

using namespace std;


int main(int argc, char *argv[]) {
	
	setlocale(0, "");
	HANDLE in;//���������� ������ � ����������� ����� ��������� ��������
	HANDLE out;//���������� ������ �� ������������ ������ ��������� ��������
	HANDLE read;//���������� ������ �� ��������� � ������ � pipe
	HANDLE write;//���������� ������ � ������� �� pipe
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = true;
	saAttr.lpSecurityDescriptor = nullptr;

	//CreatePipe(&in, &write, &saAttr, 0);   //������ ���� ������ � ����������� ����� ��������� ���������
	CreatePipe(&read, &out, &saAttr, 0);   //������ ���� ������ �� ������������ ������ ��������� ���������

	//������� �������� �������
	STARTUPINFO si;//��������� ��� CreateProcess
	ZeroMemory(&si, sizeof(STARTUPINFO));//�������� si
	si.hStdOutput = out;//��������� pipe-����������� ��� ��������� ���������
	   
	si.dwFlags |= STARTF_USESTDHANDLES;

	PROCESS_INFORMATION pi;//��������� ��� CreateProcess
	WCHAR args[] = L"7za.exe e archive.zip";
	int operation;
	char* res;

	char path[1024];
	
	while (1)
	{
		char comm[1024] = "7za.exe";
		cout << "�������� ��������: " << endl << "1)����������" << endl << "2)��������" << endl << "3)�����" << endl;
		cin >> operation;
		if (operation == 1)
		{
			cout << "������� ���� � �����:";
			cin >> path;
			char comm1[] = " e ";
			strcat(comm, comm1);
			strcat(comm, path);
			system("cls");
		}
		else if (operation == 2)
		{
			cout << "������� ���� � �����:";
			cin >> path;
			cout << "������� ��� ������:";
			char arname[128];
			cin >> arname;
			char ftype[] = ".zip ";
			char comm1[] = " a ";
			strcat(comm, comm1);
			strcat(comm, arname);
			strcat(comm, ftype);
			strcat(comm, path);
			system("cls");
		}
		else if (operation == 3)
		{
			return 0;
		}
		else
		{
			system("cls");
		}
		CreateProcess(NULL, comm, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);//��������� ������� code.exe

	//���� ������ �� pipe � ����������� ����� ��������� ��������
		unsigned long bread = 0;   //���-�� ����������� ����
		char dat[] = "10 20";//������
		int n = string(dat).size() + 1;//������ ����� � ������
		WaitForSingleObject(pi.hProcess, INFINITE);
		
		//����� ������ �� ������������ ������ ��������� �������� � pipe
		char buf[2048]; //����� ������
		ReadFile(read, buf, 2047, &bread, NULL);
		DWORD lp;
		GetExitCodeProcess(pi.hProcess, (&lp));
		char *istr;
		char str2[] = "Everything is Ok";
		//����� ������
		istr = strstr(buf, str2);
		cout << "Result: ";
		if (istr == NULL)
		{
			cout << "Error!!!!!";
		}
		else
			cout << "Everything is OK" << endl;
		
		//������ �� ������������ ������ � �����
		buf[bread] = '\0';
	}
	return 0;
}