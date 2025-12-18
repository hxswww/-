#include<iostream>
#include<vector>
#include<conio.h>
#include<random>
#include<cctype>
using namespace std;

	//做一个4*4的矩阵，用来存放数据,空格用0来表示
vector<vector<int>>martix(4, vector<int>(4, 0));//以前的地图
vector<vector<int>>pre(4, vector<int>(4, 0));//之前的地图
bool is_over = false;//判断是否结束		
int sum = 0;//分数
	//输出显示
void show() {
	system("cls");	
	cout << "---------------------------------" << endl;
    for (int i = 0; i < 4; i++) {
		cout << "|\t|\t|\t|\t|\n|";
		for (int j = 0; j < 4; j++) {	//数字区
			if (martix[i][j] != 0)
				cout << "   "<<martix[i][j] << "\t|";
			else		
				cout << " \t|";	
		}
		cout << "\n|\t|\t|\t|\t|\n|";
		cout <<  "--------------------------------\n";
	}
}
//是不是要引入一个标记该位置有没有被占的地图？
//感觉没必要，更加麻烦了，直接判断其是否为0便可

void move() {
	char ch = ' ';
	//获取输入
		ch = _getch();
		ch = tolower(ch);

		//大体思路，先将所有元素进行平移，然后在判断临近方向是不是有相同的元素，再做一次循环使其融合
		//还有特殊的情况，即一行或一列上同时有四个相同的元素，那么就记录一下融合次数，若有两次就再单独对这一行列进行一次平移

		/////划掉上述思路，我在后面发现先融合再平移更为简单


		if (ch == 'w') {//up

			//融合
			//做三层循环，一层推进横坐标，另外两层做选择循环来找纵坐标的融合
			//e,还要防止连续融合的情款，比如2,2,4,8按左会触发连续，需要一个break跳出融合的循环
			for (int x = 0;x < 4 ;x++ ) {//横坐标
				for (int y1 = 0; y1 < 3; y1++) {//靠上的纵坐标
					int count = 0;
					for (int y2 = y1 + 1; y2 < 4; y2++) {//靠下的纵
						int temp = martix[y2][x];
						if (martix[y1][x] == martix[y2][x]) {
							martix[y1][x] *= 2;//靠上的融合*2
							sum += martix[y1][x];
							martix[y2][x] = 0;//靠下的清0
							count += 1;
						}
						if (count == 1 ||temp) //融合过一次后略过此靠上节点的后续融合
							break;
					}

				}
			}

			//平移
			for (int x = 0; x < 4; x++) {//横坐标
				for (int y1 = 3; y1 >0; y1--) {
					for (int y2 = 0; y2 < y1; y2++) {
						if (martix[y2][x] == 0) {
							martix[y2][x] = martix[y2+1][x];//复制移动
							martix[y2+1][x] = 0;//原位置清零
						}
					}
				}
			}
		}

		//下和上的融合逻辑可以通用，只不过要改正一下平移的逻辑
		if (ch == 's') {//down
			for (int x = 0;x < 4 ;x++ ) {//横坐标
				for (int y1 = 0; y1 < 3; y1++) {//靠上的纵坐标
					int count = 0;
					for (int y2 = y1 + 1; y2 < 4; y2++) {//靠下的纵
						int temp = martix[y2][x];
						if (martix[y1][x] == martix[y2][x]) {
							martix[y1][x] *= 2;//靠上的融合*2
							sum += martix[y1][x];
							martix[y2][x] = 0;//靠下的清0
							count += 1;
						}
						if (count == 1||temp)
							break;
					}
				}
			}
		
			//平移
			for (int x = 0; x < 4;x++ ) {//横坐标
				for (int y1 = 0; y1 <3 ; y1++) {//从第三行开始执行，依次向上
					for (int y2 = 3; y2 > y1; y2--) {
						if (martix[y2][x] == 0) {//下方的位置不存在时才动
							martix[y2][x] = martix[y2-1][x];//复制移动
							martix[y2-1][x] = 0;//原位置清零
						}
					}
				}
			}
		}
		if (ch == 'a') {//left
			//ε=(´ο｀*)))唉要做重复工作了，我最讨厌这些了    ...当我没说，在敲得时候会继续想，刚刚就又找到了漏洞
			for (int y = 0; y < 4; y++) {//逐步推进纵坐标
				for (int x1 = 0; x1 < 3; x1++) {//靠左的横坐标
					int count = 0;
					for (int x2 = x1 + 1; x2 < 4; x2++) {//靠右的横坐标
						int temp = martix[y][x2];
						if (martix[y][x1] == martix[y][x2]) {
							martix[y][x1] *= 2;
							sum += martix[y][x1];
							martix[y][x2] = 0;
							count += 1;
						}
						if (count == 1||temp)
							break;
					}
				}
			}

			//平移
			for (int y = 0; y < 4; y++) {//逐步推进纵坐标
				for (int x1 = 2; x1 >=0; x1--) {//靠左的横坐标
					for (int x2 = 0; x2 <= x1; x2++) {
						if (martix[y][x2] == 0) {
							martix[y][x2] = martix[y][x2+1];//移
							martix[y][x2+1] = 0;//清零
						}
					}
				}
			}

		}
		if (ch == 'd') {//right
			for (int y = 0; y < 4; y++) {//逐步推进纵坐标
				for (int x1 = 0; x1 < 3; x1++) {//靠左的横坐标
					int count = 0;
					for (int x2 = x1 + 1; x2 < 4; x2++) {//靠右的横坐标
						int temp = martix[y][x2];
						if (martix[y][x1] == martix[y][x2]) {
							martix[y][x1] *= 2;
							sum += martix[y][x1];
							martix[y][x2] = 0;
							count += 1;
						}
						if (count == 1 || temp)
							break;
					}
				}
			}
			//平移
			for (int y = 0; y < 4; y++) {//逐步推进纵坐标
				for (int x1 = 0 ; x1 <3; x1++) {//靠左的横坐标
					for (int x2 = 3; x2>x1; x2--) {
						if (martix[y][x2] == 0) {
							martix[y][x2] = martix[y][x2-1];//移
							martix[y][x2-1] = 0;//清零
						}
					}
				}
			}
		}	
}

//随机生成，判断游戏是否结束可以在收集空白坐标的时候顺便做了
void generate() {
	//先收集所有空坐标，加入到容器当中
	vector<pair<int, int>>space;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (martix[i][j] == 0)
				space.push_back({ i,j });
		}
	}

	//设置随机数,这个直接找网上的
	if (!space.empty()) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, space.size() - 1);
		int random = dis(gen);
		int new_i = space[random].first;
		int new_j = space[random].second;
		martix[new_i][new_j] = 2;
	}
	else {
		is_over = true;
	}
}

int main() {

	generate();
		//每次获取到键后对界面进行一次更新，并再次将二维矩阵给输出
	while (!is_over) {	
		int count = 0;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				pre[i][j] = martix[i][j];			
			}//还需要判断移动是否生效，以免不移动时仍旧生成随机数，将两个地图直接进行对比即可
		}
		move();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (pre[i][j] != martix[i][j])
					count += 1;

			}
		}
		if(count!=0)
		  generate();
        show();
		cout << endl << endl << endl << "得分：" << sum;//计分板
	}
	return 0;
}
