#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
vector<string> vec;
int get_lindex(int temp)		//返回某个问题的左树的坐标
{
	if (temp == 1)
		return 2;
	int a[13] = { 1,3,7,15,31,63,127,255,511,1023,2047,4095,8191 };		//列举部分2^n-1的值
	int j = 0;
	while (temp > a[j])
	{
		j++;
	}
	return a[j] + 2 * (temp - a[j - 1]) - 1;
}

void input_file()			//将txt文件打开并按行输入到vector中
{
	vec.push_back("begin");
	string temp;
	ifstream infile;
	infile.open("lol.txt");		//打开txt文件，从第一行开始写入进vec中
	while (!infile.eof())
	{
		getline(infile, temp);
		vec.push_back(temp);
	}
	infile.close();			//关闭txt文件
}
void output_file()			//将原txt文件里的内容擦除，然后将更改（学习）后的新的vec的内容按行输出到txt
{
	int i = 1;
	ofstream outfile;
	outfile.open("lol.txt", ios::trunc);	//打开并擦除原文件
	for (i; i < vec.size(); i++)
	{
		outfile << vec[i] << endl;
	}
	outfile.close();		//关闭txt文件
}
void test()			//历遍树
{
	int flag = 1;				//设定flag，作为指针
	char c;
	string a, b;
	while (vec[flag][0] != '0')		//确定循环结束条件（txt文件中的树结束后的下一个左树为0或-1）
	{
		cout << vec[flag] << endl;
		cin >> c;
		if (c == 'y')			//输入y，则flag移动到下一个左树
		{
			flag = get_lindex(flag);
		}
		else if (c == 'n')		//输入n，则flag移动到下一个右树
		{
			if (vec[get_lindex(flag) + 1][0] == '0' || vec[get_lindex(flag) + 1][0] == '-1')	//若原树已经结束，答案却不正确，则进行学习，用输入的问题替换原位置的英雄名字
			{																					//输入的回答进入下一个y，原名字进入下一个n
				cout << "请输入可以寻找到它的问题以及该英雄的名字:" << endl;
				cin >> a >> b;
				vec[get_lindex(flag) + 1] = vec[flag];
				vec[flag] = a;
				vec[get_lindex(flag)] = b;
				vec[get_lindex(get_lindex(flag) + 1) + 1] = -1;
				break;
			}
			flag = get_lindex(flag) + 1;							//若原树还未结束，则指针指向右树
	}
	else
		{
			cout << "输入错误，请重新输入:" << endl;				//输入不为y或n时的提示
		}
	}
}
int main()
{
	//有关测试的说明
	cout << "这是一个以“LOL的英雄”为主题的测试" << endl << "请现在心里想一个lol的英雄，然后根据提示输入y或n" << endl << "本测试的英雄版本为s8赛季比赛版本" << endl << endl;
	input_file();
	test();
	output_file();
	return 0;
}
