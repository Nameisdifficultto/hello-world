// class08.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


//深度寻路  基于图的
//深度优先搜索

//规则：沿着一个固定的方向来查找，到了岔路口才又一次选择方向，如果碰到了死胡同退回上一个岔路口重新选择方向
//				(走过的路不再重走)

//需要用到的辅助的信息：
//地图  二维数组，二维数组里面每一个元素可以代表一种状态
//容器	1、用来保存寻路中找到的路径点（行列值）；2、对这个路径点要进行增删改查；3、在深度中用的容器为栈
//辅助数组	1、资源数据一般不能直接改；2、对资源数组进行一些标记，可能会修改资源数组，还可能资源数组无法完全表述清楚当点节点的信息


//1、准备地图
//1表示是障碍  0表示可以通行  在代码中一次走一个节点，这个节点就是二维数组中的一个行列值
#define MAP_ROW 10
#define MAP_COL 10

//2、准备容器  准备做为一个类模板
#include "MyStack.h"

//3、准备一个结构，是用来表示每一个路径点的坐标
struct MyPoint
{
	//int x, y;
	int row, col;//row表示行，col表示列
};

//4、准备一个辅助数组  第1是因为资源数组不可以被修改；第2是资源数组无法完整表述所需要用到的数据
enum Path_Dir{ p_up, p_down, p_left, p_right };

struct MyPathNode
{
	bool		isFind;//表示当前行列值所代表的节点，是否被访问过
	Path_Dir	dir;//表示当前行列值需要行进的下一个方向
	int			val;//保存资源数组的所有原始路径点的信息
};

//准备一个函数，用来判断坐标是否可以通行
bool isMove(MyPathNode p[][MAP_COL],int row,int col)
{
	if (row < 0 || row >= MAP_ROW || col < 0 || col >= MAP_COL)//判断行列是否处于越界位置
		return false;//如果越界直接返回，不用进数组，也是不能移动

	if (p[row][col].isFind == true //证明当前坐标已经被访问
		|| p[row][col].val != 0)//证明当前坐标的值不为0，表示不可通行
		return false;

	return true;
}

//深度寻路在有一条路径从起点通往终点的情况下，不一定能找到路径的，为什么？

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

	//第5步
	MyPathNode pathArr[MAP_ROW][MAP_COL];//准备一个和资源数组一模一样大小的辅助数组
	for (int i = 0; i < MAP_ROW; ++i)
	{
		for (int j = 0; j < MAP_COL; ++j)
		{
			pathArr[i][j].isFind = false;//每一个路径点位置初始化都是没有访问的
			//暂定方向的先后次序为上，左，下，右(注意：这个方向严重影响了寻路的过程，导致可能找到的不是最短路径)
			pathArr[i][j].dir = p_up;//可以自定义，在这里每一个路径点的位置初始下一个方向是上方向 
			pathArr[i][j].val = mapArr[i][j];//把资源数组的每一个路径点的信息复制过来
		}
	}

	//第6步
	//设定起点和终点
	MyPoint beginPoint = { 1, 1 };
	MyPoint endPoint = {1,1};

	//第7步
	//通过容器来保存起点
	CMyStack<MyPoint> ms;
	ms.push(beginPoint);//把起点压入栈中，通过栈中的起点可以继续保存后续节点

	//第8步  开始寻路
	//准备一个临时坐标点，用来保存当前是哪一个位置，然后这个位置是否有下一个可通行位置
	MyPoint NearPoint = beginPoint;
	while (true)//不确定循环的次数，不确定通过多少次操作能找到一条路径，或者确定没有路径
	{
		switch (pathArr[NearPoint.row][NearPoint.col].dir)//判断当前待搜索的方向 
		{
		case p_up:
			////if (pathArr[NearPoint.row - 1][NearPoint.col].isFind == false //证明当前坐标没有被访问
			////	&& pathArr[NearPoint.row - 1][NearPoint.col].val == 0)//证明当前坐标的值为0，表示可通行
			//if (isMove(pathArr, NearPoint.row - 1, NearPoint.col))
			//{
			//	pathArr[NearPoint.row][NearPoint.col].dir = p_left;
			//	//如果条件进来，是不是表示{NearPoint.row - 1,NearPoint.col}这个点可以移动到这个点
			//	pathArr[NearPoint.row][NearPoint.col].isFind = true;//当前的搜索的起始点要改为已访问
			//	MyPoint tempPoint = { NearPoint.row - 1, NearPoint.col };
			//	ms.push(tempPoint);//入栈，栈中保存所有可以移动到的坐标
			//	NearPoint = tempPoint;//把当前可移到到的点，当成下一个搜索的起始位置
			//}
			//else
			//	pathArr[NearPoint.row][NearPoint.col].dir = p_left;

			pathArr[NearPoint.row][NearPoint.col].dir = p_down;//进来这个方向，立马把搜索点的下一个方向标记上
			if (isMove(pathArr, NearPoint.row - 1, NearPoint.col))
			{
				//如果条件进来，是不是表示{NearPoint.row - 1,NearPoint.col}这个点可以移动到这个点
				pathArr[NearPoint.row][NearPoint.col].isFind = true;//当前的搜索的起始点要改为已访问
				MyPoint tempPoint = { NearPoint.row - 1, NearPoint.col };
				ms.push(tempPoint);//入栈，栈中保存所有可以移动到的坐标
				NearPoint = tempPoint;//把当前可移到到的点，当成下一个搜索的起始位置
			}
			break;
		case  p_left:
			pathArr[NearPoint.row][NearPoint.col].dir = p_right;//进来这个方向，立马把搜索点的下一个方向标记上
			if (isMove(pathArr, NearPoint.row, NearPoint.col - 1))
			{
				//如果条件进来，是不是表示{NearPoint.row - 1,NearPoint.col}这个点可以移动到这个点
				pathArr[NearPoint.row][NearPoint.col].isFind = true;//当前的搜索的起始点要改为已访问
				MyPoint tempPoint = { NearPoint.row, NearPoint.col - 1 };
				ms.push(tempPoint);//入栈，栈中保存所有可以移动到的坐标
				NearPoint = tempPoint;//把当前可移到到的点，当成下一个搜索的起始位置
			}
			break;
		case p_down:
			pathArr[NearPoint.row][NearPoint.col].dir = p_left;//进来这个方向，立马把搜索点的下一个方向标记上
			if (isMove(pathArr, NearPoint.row + 1, NearPoint.col))
			{
				//如果条件进来，是不是表示{NearPoint.row - 1,NearPoint.col}这个点可以移动到这个点
				pathArr[NearPoint.row][NearPoint.col].isFind = true;//当前的搜索的起始点要改为已访问
				MyPoint tempPoint = { NearPoint.row + 1, NearPoint.col };
				ms.push(tempPoint);//入栈，栈中保存所有可以移动到的坐标
				NearPoint = tempPoint;//把当前可移到到的点，当成下一个搜索的起始位置
			}
			break;
		case p_right:
			//这是最后一个方向搜索，没有下一步方向了
			if (isMove(pathArr, NearPoint.row, NearPoint.col + 1))
			{
				//如果条件进来，是不是表示{NearPoint.row - 1,NearPoint.col}这个点可以移动到这个点
				pathArr[NearPoint.row][NearPoint.col].isFind = true;//当前的搜索的起始点要改为已访问
				MyPoint tempPoint = { NearPoint.row, NearPoint.col + 1 };
				ms.push(tempPoint);//入栈，栈中保存所有可以移动到的坐标
				NearPoint = tempPoint;//把当前可移到到的点，当成下一个搜索的起始位置
			}
			else
			{
				//进到这里，就是这个坐标是一个死胡同，退栈
				MyPoint tempPoint = ms.GetTop();//先得到这个栈顶
				//标记这个栈顶已经被访问，防止退栈之后，新的栈顶元素继续访问这个位置，造成死循环
				pathArr[tempPoint.row][tempPoint.col].isFind = true;

				ms.pop();//直接退栈
				if (!ms.empty())//判断栈空，防止空栈（没有找到路径时，栈访问越界）
					NearPoint = ms.GetTop();//得到新的栈顶元素
			}
			break;
		}
		//判断是否找到终点（有路）
		if (NearPoint.row == endPoint.row && NearPoint.col == endPoint.col)
			break;;//找到终点
		if (ms.empty())
			break;//表示容器为空，没有路径
	}

	//如果有路，打印出路径点
	while (!ms.empty())
	{
		MyPoint tempPoint = ms.GetTop();
		printf("row = %d, col = %d\n",tempPoint.row,tempPoint.col);
		ms.pop();
	}

	return 0;
}

