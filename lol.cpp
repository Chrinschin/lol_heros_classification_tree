#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
vector<string> vec;
int get_lindex(int temp)		//����ĳ�����������������
{
	if (temp == 1)
		return 2;
	int a[13] = { 1,3,7,15,31,63,127,255,511,1023,2047,4095,8191 };		//�оٲ���2^n-1��ֵ
	int j = 0;
	while (temp > a[j])
	{
		j++;
	}
	return a[j] + 2 * (temp - a[j - 1]) - 1;
}

void input_file()			//��txt�ļ��򿪲��������뵽vector��
{
	vec.push_back("begin");
	string temp;
	ifstream infile;
	infile.open("lol.txt");		//��txt�ļ����ӵ�һ�п�ʼд���vec��
	while (!infile.eof())
	{
		getline(infile, temp);
		vec.push_back(temp);
	}
	infile.close();			//�ر�txt�ļ�
}
void output_file()			//��ԭtxt�ļ�������ݲ�����Ȼ�󽫸��ģ�ѧϰ������µ�vec�����ݰ��������txt
{
	int i = 1;
	ofstream outfile;
	outfile.open("lol.txt", ios::trunc);	//�򿪲�����ԭ�ļ�
	for (i; i < vec.size(); i++)
	{
		outfile << vec[i] << endl;
	}
	outfile.close();		//�ر�txt�ļ�
}
void test()			//������
{
	int flag = 1;				//�趨flag����Ϊָ��
	char c;
	string a, b;
	while (vec[flag][0] != '0')		//ȷ��ѭ������������txt�ļ��е������������һ������Ϊ0��-1��
	{
		cout << vec[flag] << endl;
		cin >> c;
		if (c == 'y')			//����y����flag�ƶ�����һ������
		{
			flag = get_lindex(flag);
		}
		else if (c == 'n')		//����n����flag�ƶ�����һ������
		{
			if (vec[get_lindex(flag) + 1][0] == '0' || vec[get_lindex(flag) + 1][0] == '-1')	//��ԭ���Ѿ���������ȴ����ȷ�������ѧϰ��������������滻ԭλ�õ�Ӣ������
			{																					//����Ļش������һ��y��ԭ���ֽ�����һ��n
				cout << "���������Ѱ�ҵ����������Լ���Ӣ�۵�����:" << endl;
				cin >> a >> b;
				vec[get_lindex(flag) + 1] = vec[flag];
				vec[flag] = a;
				vec[get_lindex(flag)] = b;
				vec[get_lindex(get_lindex(flag) + 1) + 1] = -1;
				break;
			}
			flag = get_lindex(flag) + 1;							//��ԭ����δ��������ָ��ָ������
	}
	else
		{
			cout << "�����������������:" << endl;				//���벻Ϊy��nʱ����ʾ
		}
	}
}
int main()
{
	//�йز��Ե�˵��
	cout << "����һ���ԡ�LOL��Ӣ�ۡ�Ϊ����Ĳ���" << endl << "������������һ��lol��Ӣ�ۣ�Ȼ�������ʾ����y��n" << endl << "�����Ե�Ӣ�۰汾Ϊs8���������汾" << endl << endl;
	input_file();
	test();
	output_file();
	return 0;
}
