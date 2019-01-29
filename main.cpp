
#include <stdio.h>
#include <windows.h>
//文件加密
void encrypt(char *fileName)
{
	FILE *fp = fopen(fileName, "rb+");
	if (NULL == fp)
	{
		printf("打开文件失败\n");
		return;
		//exit(0);
	}
	printf("成功打开文件\n");
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
	printf("加密完成!\n");
}
//遍历文件夹
void traversalFolder(char *fileName)
{
	//1 设置第一个文件的名字   fileName\*.*   *代表一个任意名字
	char pathName[MAX_PATH];
	sprintf(pathName, "%s\\*.*", fileName);
	printf("%s\n", pathName);
	//printf("%s\\*.*",fileName);
	//2 找这个文件
	WIN32_FIND_DATA findData;
	HANDLE hFile = FindFirstFile(pathName, &findData);
	if (INVALID_HANDLE_VALUE == hFile){
		printf("没找到文件!\n");
		return;
	}
	char temp[MAX_PATH];
	int ret = 1;
#if 1
	while (ret){
		if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY){//是文件夹
			if (findData.cFileName[0] != '.'){//避开 .   和 ..
				//设置文件夹名字   C:\intel
				memset(temp, 0, MAX_PATH);
				sprintf(temp, "%s\\%s", fileName, findData.cFileName);
				printf("文件夹:%s\n", temp);
				//遍历子文件夹
				traversalFolder(temp);
			}
		}
		else{//是文件
			//设置文件名字   C:\key.txt
			memset(temp, 0, MAX_PATH);
			sprintf(temp, "%s\\%s", fileName, findData.cFileName);
			printf("文件:%s\n", temp);
			//加密
			encrypt(temp);
		}

		//找下一个文件
		ret = FindNextFile(hFile, &findData);
	}
#endif
}
int main()
{
	//对单个文件加密
#if 1
	char name[256] = { 0 };
	printf("请输入要加密的文件:");
	scanf("%s", name);
	encrypt(name);
#endif
	//对整个文件夹加密
#if 0
	char currentDirectory[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, currentDirectory);
	traversalFolder(currentDirectory);
#endif
	return 0;
}
