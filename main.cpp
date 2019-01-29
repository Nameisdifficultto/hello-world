
#include <stdio.h>
#include <windows.h>
//�ļ�����
void encrypt(char *fileName)
{
	FILE *fp = fopen(fileName, "rb+");
	if (NULL == fp)
	{
		printf("���ļ�ʧ��\n");
		return;
		//exit(0);
	}
	printf("�ɹ����ļ�\n");
	int len = 0;
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	for (int i = 0; i < len;++i)
	{
		if (i%2==0)
			fseek(fp, 0, SEEK_CUR);
		char data = fgetc(fp) ^ 255;
		fseek(fp, -1, SEEK_CUR);
		fputc(data, fp);
	}
	fclose(fp);
	printf("�������!\n");
}
//�����ļ���
void traversalFolder(char *fileName)
{
	//1 ���õ�һ���ļ�������   fileName\*.*   *����һ����������
	char pathName[MAX_PATH];
	sprintf(pathName, "%s\\*.*", fileName);
	printf("%s\n", pathName);
	//printf("%s\\*.*",fileName);
	//2 ������ļ�
	WIN32_FIND_DATA findData;
	HANDLE hFile = FindFirstFile(pathName, &findData);
	if (INVALID_HANDLE_VALUE == hFile){
		printf("û�ҵ��ļ�!\n");
		return;
	}
	char temp[MAX_PATH];
	int ret = 1;
#if 1
	while (ret){
		if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY){//���ļ���
			if (findData.cFileName[0] != '.'){//�ܿ� .   �� ..
				//�����ļ�������   C:\intel
				memset(temp, 0, MAX_PATH);
				sprintf(temp, "%s\\%s", fileName, findData.cFileName);
				printf("�ļ���:%s\n", temp);
				//�������ļ���
				traversalFolder(temp);
			}
		}
		else{//���ļ�
			//�����ļ�����   C:\key.txt
			memset(temp, 0, MAX_PATH);
			sprintf(temp, "%s\\%s", fileName, findData.cFileName);
			printf("�ļ�:%s\n", temp);
			//����
			encrypt(temp);
		}

		//����һ���ļ�
		ret = FindNextFile(hFile, &findData);
	}
#endif
}
int main()
{
	//�Ե����ļ�����
#if 1
	char name[256] = { 0 };
	printf("������Ҫ���ܵ��ļ�:");
	scanf("%s", name);
	encrypt(name);
#endif
	//�������ļ��м���
#if 0
	char currentDirectory[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, currentDirectory);
	traversalFolder(currentDirectory);
#endif
	return 0;
}
