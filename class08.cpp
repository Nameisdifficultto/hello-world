// class08.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


//���Ѱ·  ����ͼ��
//�����������

//��������һ���̶��ķ��������ң����˲�·�ڲ���һ��ѡ�����������������ͬ�˻���һ����·������ѡ����
//				(�߹���·��������)

//��Ҫ�õ��ĸ�������Ϣ��
//��ͼ  ��ά���飬��ά��������ÿһ��Ԫ�ؿ��Դ���һ��״̬
//����	1����������Ѱ·���ҵ���·���㣨����ֵ����2�������·����Ҫ������ɾ�Ĳ飻3����������õ�����Ϊջ
//��������	1����Դ����һ�㲻��ֱ�Ӹģ�2������Դ�������һЩ��ǣ����ܻ��޸���Դ���飬��������Դ�����޷���ȫ�����������ڵ����Ϣ


//1��׼����ͼ
//1��ʾ���ϰ�  0��ʾ����ͨ��  �ڴ�����һ����һ���ڵ㣬����ڵ���Ƕ�ά�����е�һ������ֵ
#define MAP_ROW 10
#define MAP_COL 10

//2��׼������  ׼����Ϊһ����ģ��
#include "MyStack.h"

//3��׼��һ���ṹ����������ʾÿһ��·���������
struct MyPoint
{
	//int x, y;
	int row, col;//row��ʾ�У�col��ʾ��
};

//4��׼��һ����������  ��1����Ϊ��Դ���鲻���Ա��޸ģ���2����Դ�����޷�������������Ҫ�õ�������
enum Path_Dir{ p_up, p_down, p_left, p_right };

struct MyPathNode
{
	bool		isFind;//��ʾ��ǰ����ֵ������Ľڵ㣬�Ƿ񱻷��ʹ�
	Path_Dir	dir;//��ʾ��ǰ����ֵ��Ҫ�н�����һ������
	int			val;//������Դ���������ԭʼ·�������Ϣ
};

//׼��һ�������������ж������Ƿ����ͨ��
bool isMove(MyPathNode p[][MAP_COL],int row,int col)
{
	if (row < 0 || row >= MAP_ROW || col < 0 || col >= MAP_COL)//�ж������Ƿ���Խ��λ��
		return false;//���Խ��ֱ�ӷ��أ����ý����飬Ҳ�ǲ����ƶ�

	if (p[row][col].isFind == true //֤����ǰ�����Ѿ�������
		|| p[row][col].val != 0)//֤����ǰ�����ֵ��Ϊ0����ʾ����ͨ��
		return false;

	return true;
}

//���Ѱ·����һ��·�������ͨ���յ������£���һ�����ҵ�·���ģ�Ϊʲô��

int _tmain(int argc, _TCHAR* argv[])
{
	int mapArr[MAP_ROW][MAP_COL] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 1, 0, 0, 0, 0, 1 },
		{ 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 },
		{ 1, 1, 0, 0, 0, 0, 1, 1, 0, 1 },
		{ 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 },
		{ 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 },
		{ 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 },
		{ 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 },
		{ 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	//��5��
	MyPathNode pathArr[MAP_ROW][MAP_COL];//׼��һ������Դ����һģһ����С�ĸ�������
	for (int i = 0; i < MAP_ROW; ++i)
	{
		for (int j = 0; j < MAP_COL; ++j)
		{
			pathArr[i][j].isFind = false;//ÿһ��·����λ�ó�ʼ������û�з��ʵ�
			//�ݶ�������Ⱥ����Ϊ�ϣ����£���(ע�⣺�����������Ӱ����Ѱ·�Ĺ��̣����¿����ҵ��Ĳ������·��)
			pathArr[i][j].dir = p_up;//�����Զ��壬������ÿһ��·�����λ�ó�ʼ��һ���������Ϸ��� 
			pathArr[i][j].val = mapArr[i][j];//����Դ�����ÿһ��·�������Ϣ���ƹ���
		}
	}

	//��6��
	//�趨�����յ�
	MyPoint beginPoint = { 1, 1 };
	MyPoint endPoint = {1,1};

	//��7��
	//ͨ���������������
	CMyStack<MyPoint> ms;
	ms.push(beginPoint);//�����ѹ��ջ�У�ͨ��ջ�е������Լ�����������ڵ�

	//��8��  ��ʼѰ·
	//׼��һ����ʱ����㣬�������浱ǰ����һ��λ�ã�Ȼ�����λ���Ƿ�����һ����ͨ��λ��
	MyPoint NearPoint = beginPoint;
	while (true)//��ȷ��ѭ���Ĵ�������ȷ��ͨ�����ٴβ������ҵ�һ��·��������ȷ��û��·��
	{
		switch (pathArr[NearPoint.row][NearPoint.col].dir)//�жϵ�ǰ�������ķ��� 
		{
		case p_up:
			////if (pathArr[NearPoint.row - 1][NearPoint.col].isFind == false //֤����ǰ����û�б�����
			////	&& pathArr[NearPoint.row - 1][NearPoint.col].val == 0)//֤����ǰ�����ֵΪ0����ʾ��ͨ��
			//if (isMove(pathArr, NearPoint.row - 1, NearPoint.col))
			//{
			//	pathArr[NearPoint.row][NearPoint.col].dir = p_left;
			//	//��������������ǲ��Ǳ�ʾ{NearPoint.row - 1,NearPoint.col}���������ƶ��������
			//	pathArr[NearPoint.row][NearPoint.col].isFind = true;//��ǰ����������ʼ��Ҫ��Ϊ�ѷ���
			//	MyPoint tempPoint = { NearPoint.row - 1, NearPoint.col };
			//	ms.push(tempPoint);//��ջ��ջ�б������п����ƶ���������
			//	NearPoint = tempPoint;//�ѵ�ǰ���Ƶ����ĵ㣬������һ����������ʼλ��
			//}
			//else
			//	pathArr[NearPoint.row][NearPoint.col].dir = p_left;

			pathArr[NearPoint.row][NearPoint.col].dir = p_down;//�������������������������һ����������
			if (isMove(pathArr, NearPoint.row - 1, NearPoint.col))
			{
				//��������������ǲ��Ǳ�ʾ{NearPoint.row - 1,NearPoint.col}���������ƶ��������
				pathArr[NearPoint.row][NearPoint.col].isFind = true;//��ǰ����������ʼ��Ҫ��Ϊ�ѷ���
				MyPoint tempPoint = { NearPoint.row - 1, NearPoint.col };
				ms.push(tempPoint);//��ջ��ջ�б������п����ƶ���������
				NearPoint = tempPoint;//�ѵ�ǰ���Ƶ����ĵ㣬������һ����������ʼλ��
			}
			break;
		case  p_left:
			pathArr[NearPoint.row][NearPoint.col].dir = p_right;//�������������������������һ����������
			if (isMove(pathArr, NearPoint.row, NearPoint.col - 1))
			{
				//��������������ǲ��Ǳ�ʾ{NearPoint.row - 1,NearPoint.col}���������ƶ��������
				pathArr[NearPoint.row][NearPoint.col].isFind = true;//��ǰ����������ʼ��Ҫ��Ϊ�ѷ���
				MyPoint tempPoint = { NearPoint.row, NearPoint.col - 1 };
				ms.push(tempPoint);//��ջ��ջ�б������п����ƶ���������
				NearPoint = tempPoint;//�ѵ�ǰ���Ƶ����ĵ㣬������һ����������ʼλ��
			}
			break;
		case p_down:
			pathArr[NearPoint.row][NearPoint.col].dir = p_left;//�������������������������һ����������
			if (isMove(pathArr, NearPoint.row + 1, NearPoint.col))
			{
				//��������������ǲ��Ǳ�ʾ{NearPoint.row - 1,NearPoint.col}���������ƶ��������
				pathArr[NearPoint.row][NearPoint.col].isFind = true;//��ǰ����������ʼ��Ҫ��Ϊ�ѷ���
				MyPoint tempPoint = { NearPoint.row + 1, NearPoint.col };
				ms.push(tempPoint);//��ջ��ջ�б������п����ƶ���������
				NearPoint = tempPoint;//�ѵ�ǰ���Ƶ����ĵ㣬������һ����������ʼλ��
			}
			break;
		case p_right:
			//�������һ������������û����һ��������
			if (isMove(pathArr, NearPoint.row, NearPoint.col + 1))
			{
				//��������������ǲ��Ǳ�ʾ{NearPoint.row - 1,NearPoint.col}���������ƶ��������
				pathArr[NearPoint.row][NearPoint.col].isFind = true;//��ǰ����������ʼ��Ҫ��Ϊ�ѷ���
				MyPoint tempPoint = { NearPoint.row, NearPoint.col + 1 };
				ms.push(tempPoint);//��ջ��ջ�б������п����ƶ���������
				NearPoint = tempPoint;//�ѵ�ǰ���Ƶ����ĵ㣬������һ����������ʼλ��
			}
			else
			{
				//��������������������һ������ͬ����ջ
				MyPoint tempPoint = ms.GetTop();//�ȵõ����ջ��
				//������ջ���Ѿ������ʣ���ֹ��ջ֮���µ�ջ��Ԫ�ؼ����������λ�ã������ѭ��
				pathArr[tempPoint.row][tempPoint.col].isFind = true;

				ms.pop();//ֱ����ջ
				if (!ms.empty())//�ж�ջ�գ���ֹ��ջ��û���ҵ�·��ʱ��ջ����Խ�磩
					NearPoint = ms.GetTop();//�õ��µ�ջ��Ԫ��
			}
			break;
		}
		//�ж��Ƿ��ҵ��յ㣨��·��
		if (NearPoint.row == endPoint.row && NearPoint.col == endPoint.col)
			break;;//�ҵ��յ�
		if (ms.empty())
			break;//��ʾ����Ϊ�գ�û��·��
	}

	//�����·����ӡ��·����
	while (!ms.empty())
	{
		MyPoint tempPoint = ms.GetTop();
		printf("row = %d, col = %d\n",tempPoint.row,tempPoint.col);
		ms.pop();
	}

	return 0;
}

