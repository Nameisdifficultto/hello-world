// A星寻路.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>

#define MAP_ROW 6
#define MAP_COL 8
using std::vector;

int arr[MAP_ROW][MAP_COL] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 1, 0, 1, 0, 0},
	{ 0, 0, 0, 1, 0, 0, 1, 0},
	{ 0, 0, 0, 1, 1, 0, 1, 0},
	{ 0, 0, 0, 1, 0, 1, 1, 0},
	{ 0, 0, 0, 1, 0, 0, 0, 0}
};

enum PathDir{ left_up, up, right_up, left, right, left_down, down, right_down };
struct Point
{
	int row, col;
	bool operator!=(Point const& point)
	{
		if (row == point.row&&col == point.col)
			return false;
		return true;
	}
};
struct F
{
	int g, h;//g表示从初始节点到任意节点的代价   h表示从初始节点到目标节点的代价
	PathDir dir;
	int val;
};
struct PathData
{
	Point point;
	int f;
	PathData *father;
	vector<PathData *> childNode;
};

bool isMove(Point myPoint)
{
	if (myPoint.row >= 0 && myPoint.row < MAP_ROW&&myPoint.col >= 0 && myPoint.col < MAP_COL)
	{
		if (arr[myPoint.row][myPoint.col] == 0)
			return true;
	}
	return false;
}

void clearTree(PathData *& root)
{
	if (root)
	{
		for (size_t i = 0; i < root->childNode.size(); ++i)
			clearTree(root->childNode[i]);
		delete root;
		root = nullptr;
	}
}

void sort(vector<PathData *> &pd)
{
	PathData * temp;
	size_t j;
	//删除父节点
	pd[0] = pd.back();
	pd.pop_back();
	for (size_t i = 1; i < pd.size(); ++i)
	{
		temp = pd[i];
		j = i;
		while (j > 0 && (pd[j - 1]->f > temp->f))
		{
			pd[j] = pd[j - 1];
			j--;
		}
		pd[j] = temp;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	F point_f[MAP_ROW][MAP_COL], tempPoint_f;

	Point beginPoint = { 1, 1 };
	Point endPoint = { 5, 7 };
	//初始化资源
	for (int i = 0; i < MAP_ROW; ++i)
	{
		for (int j = 0; j < MAP_COL; ++j)
		{
			point_f[i][j].dir = left_up;
			point_f[i][j].g = 0;
			point_f[i][j].h = (endPoint.row - i + endPoint.col - j) * 10;
			point_f[i][j].val = arr[i][j];
		}
	}
	tempPoint_f = point_f[beginPoint.row][beginPoint.col];
	//初始化起点
	point_f[beginPoint.row][beginPoint.col].g = 0;
	point_f[beginPoint.row][beginPoint.col].h = 90;
	point_f[beginPoint.row][beginPoint.col].dir = left_up;
	//初始化根节点
	PathData *root = new PathData;
	root->father = nullptr;
	root->point = beginPoint;
	root->f = point_f[beginPoint.row][beginPoint.col].h + point_f[beginPoint.row][beginPoint.col].g;

	vector<PathData *> tempNodeList;//记录孩子节点
	vector<PathData *> list;
	list.push_back(root);

	Point tempPoint;
	while (true)
	{
		int j;
		for (j = 0; j < 8; ++j)
		{
			tempPoint = list[0]->point;
			switch (j)
			{
			case left_up:
				tempPoint.row--;
				tempPoint.col--;
				tempPoint_f.g = point_f[list[0]->point.row][list[0]->point.col].g + 14;//将父节点的g值加上
				break;
			case up:
				tempPoint.row--;
				tempPoint_f.g = point_f[list[0]->point.row][list[0]->point.col].g + 10;
				break;
			case right_up:
				tempPoint.row--;
				tempPoint.col++;
				tempPoint_f.g = point_f[list[0]->point.row][list[0]->point.col].g + 14;
				break;
			case left:
				tempPoint.col--;
				tempPoint_f.g = point_f[list[0]->point.row][list[0]->point.col].g + 10;
				break;
			case right:
				tempPoint.col++;
				tempPoint_f.g = point_f[list[0]->point.row][list[0]->point.col].g + 10;
				break;
			case left_down:
				tempPoint.row++;
				tempPoint.col--;
				tempPoint_f.g = point_f[list[0]->point.row][list[0]->point.col].g + 14;
				break;
			case down:
				tempPoint.row++;
				tempPoint_f.g = point_f[list[0]->point.row][list[0]->point.col].g + 10;
				break;
			case right_down:
				tempPoint.row++;
				tempPoint.col++;
				tempPoint_f.g = point_f[list[0]->point.row][list[0]->point.col].g + 14;
				break;
			}

			if (isMove(tempPoint))
			{
				//覆盖初始值
				if (point_f[tempPoint.row][tempPoint.col].g == 0 && tempPoint != beginPoint)
					point_f[tempPoint.row][tempPoint.col].g = tempPoint_f.g;

				PathData *pNode = NULL;
				//如果出现更短路径更新路径
				if (tempPoint_f.g <= point_f[tempPoint.row][tempPoint.col].g)
				{
					pNode = new PathData;
					pNode->point = tempPoint;

					point_f[tempPoint.row][tempPoint.col].g = tempPoint_f.g;
					pNode->f = point_f[tempPoint.row][tempPoint.col].g + point_f[tempPoint.row][tempPoint.col].h;

					//建立父子关系
					pNode->father = list[0];
					list[0]->childNode.push_back(pNode);
					tempNodeList.push_back(pNode);

					list.push_back(pNode);
				}

				if (tempPoint.row == endPoint.row && tempPoint.col == endPoint.col)
				{
					//表示找到终点
					PathData *tempNode = pNode;
					while (tempNode)
					{
						printf("row = %d, col = %d\n", tempNode->point.row, tempNode->point.col);
						tempNode = tempNode->father;
					}
					goto LABLE;
				}
			}
		}
		//排序
		sort(list);

		if (list.size() == 0)//没有路了，没有找终点，下一次的待搜索的数组为空
			break;
		tempNodeList.clear();//清空下一次待搜索的数组
	}
LABLE:
	clearTree(root);
	return 0;
}

