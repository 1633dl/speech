#include"speech_manager.h"
class Myclass//用于抽签后遍历
{
public:
	void operator()(int a)
	{
		cout << a << " ";
	}
};
speech_manager::speech_manager()
{
}
//打印标题
void speech_manager::show_menu()
{
	cout << "********************" << endl;
	cout << "1、开始比赛" << endl;
	cout << "2、查看往届记录" << endl;
	cout << "3、清空往届记录" << endl;
	cout << "0、退出程序" << endl;
	cout << "********************" << endl;
}
//初始化数据(第一轮比赛)
void speech_manager::Init_data()
{
	if (!this->v_speech.empty())//不是空的
	{
		this->v_speech.clear();
	}
	vector<int>v;
	for (int i = 0; i < 12; i++)
	{
		contestant person;
		string m_name = "选手";
		string temp = "ABCDEFGHIJKL";
		m_name += temp[i];
		person.name = m_name;
		//对成绩赋值
		for (int j = 0; j < 2; j++)
		{
			person.score[j] = 0;
		}
		int id = 1000;
		v.push_back(id + i);
		this->m_speech.insert(make_pair(id + i, person));
	}
	this->v_speech.push_back(v);
}
//比赛流程
void speech_manager::game_process()
{
	this->Init_data();//初始化数据
	//第一轮比赛
	this->count = 1;
	this->begin_competition();
	system("pause");
	//第二轮比赛
	this->count++;
	this->begin_competition();
	cout << "比赛结束" << endl;
	this->save_data();
	cout << "结果已记录" << endl;
}
//开始比赛
void speech_manager::begin_competition()
{
	cout << "第" << count << "轮比赛开始" << endl;
	this->drawing();//抽签
	multimap <double, int, greater<double>>mm;//用于存放key为成绩的哈希表，便于排序(哈希表创建时就会自动排序)
	for (vector<int>::iterator it = this->v_speech[this->count - 1].begin(); it != this->v_speech[this->count - 1].end(); it++)
	{
		map<int, contestant>::iterator its = this->m_speech.find(*it);
		its->second.score[this->count - 1] = this->get_score();//评委打分
		mm.insert(make_pair(its->second.score[this->count - 1], its->first));
	}
	vector<int>v2;//用于存放第一轮晋级后的编号
	int i = 0;
	cout << "晋级的成员以及成绩" << endl;
	multimap<double, int>::iterator it = mm.begin();
	if (this->count == 1)
	{
		while (i < 6)
		{
			v2.push_back(it->second);//按照哈希表的排序把编号赋值给v2容器
			it++;
			i++;
		}
		for (int i = 0; i < 6; i++)
		{
			map<int, contestant>::iterator its = this->m_speech.find(v2[i]);
			cout << "编号 " << v2[i] << " 姓名 " << its->second.name << " 成绩 " << its->second.score[0]<< endl;
		}

	}
	else
	{
		while (i < 3)
		{
			v2.push_back(it->second);
			it++;
			i++;
		}
		for (int i = 0; i < 3; i++)
		{
			map<int, contestant>::iterator its = this->m_speech.find(v2[i]);
			cout << "编号 " << v2[i] << " 姓名 " << its->second.name << " 成绩 " << its->second.score[1]<< endl;
		}
	}
	this->v_speech.push_back(v2);
}
//评委打分
double speech_manager::get_score()
{
	vector<int>v;
	for (int i = 0; i < 5; i++)
	{
		int temp = rand() % 50 + 51;
		v.push_back(temp);
	}
	sort(v.begin(), v.end());
	v.erase(v.begin());
	v.pop_back();
	double end = accumulate(v.begin(), v.end(), 0);
	return end/3;
}
//抽签
void speech_manager::drawing()
{
	cout << "选手们正在抽签" << endl;
	cout << "-------------------" << endl;
	if (this->count == 1)//第一轮比赛
	{
		random_shuffle(this->v_speech[0].begin(), this->v_speech[0].end());
		cout << "抽签的结果如下" << endl;
		for_each(this->v_speech[0].begin(), this->v_speech[0].end(), Myclass());
	}
	else
	{
		random_shuffle(this->v_speech[1].begin(), this->v_speech[1].end());
		cout << "抽签的结果如下" << endl;
		for_each(this->v_speech[1].begin(), this->v_speech[1].end(), Myclass());
	}
	cout << endl;
}
//保留数据
void speech_manager::save_data()
{
	ofstream ofs;
	//注意：后缀为.csv的文件中间都要用“，”分隔开，存入数据的时候也要手动填上
	ofs.open("比赛结果.csv", ios::out | ios::app);
	for (vector<int>::iterator it = this->v_speech[2].begin(); it != this->v_speech[2].end(); it++)
	{
		ofs << *it << "," << this->m_speech[*it].score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	//这一届记录完毕后要把所有数据都归零
}
//读取往届的结果
void speech_manager::read_result()
{
	ifstream ifs("比赛结果.csv", ios::in);
	if (!ifs.is_open())//打开文件失败
	{
		cout << "文件打开失败" << endl;
		this->is_empty = true;
		ifs.close();
		return;
	}
	//文件被清空
	char c;
	ifs >> c;
	if (ifs.eof())//读取到文件尾
	{
		cout << "文件为空" << endl;
		this->is_empty = true;
		return;
	}
	//文件不为空
	ifs.putback(c);
	this->is_empty = false;
	string data;//读取的每一届的所有信息
	int start = 0;//每次截取字符串的位置
	int number = 0;//第几届
	vector<string>message;//存放每一届的信息，便于存放进哈希表中
	while (ifs >> data)//读取一行(届)
	{
		start = 0;
		number++;
		string m_data;//截取的字符串
		int position = -1;//找到“，”的位置
		while (true)
		{
			position = data.find(",",start);
			if (position == -1)//这一行读取完了
			{
				break;
			}
			m_data = data.substr(start, position - start);//截取的字符串
			message.push_back(m_data);//放入vector容器
			start = position+1;
		}
		this->past_result.insert(make_pair(number, message));
		message.clear();
	}
	ifs.close();
	//读取完毕
	for (map<int, vector<string>>::iterator it = this->past_result.begin(); it != this->past_result.end(); it++)
	{
		cout << "第" << it->first << "届的结果" << endl;
		for (int i = 0; i < 6; i+=2)
		{
			cout << "编号 " << it->second[i] << " 成绩 " << it->second[i + 1] << endl;
		}
	}
}
//清空数据
void speech_manager::clear_data()
{
	cout << "请确认是否要清空" << endl;
	char choice;
	cout << "是：y" << endl << "否：n" << endl;
	cin >> choice;
	if (choice == 'y')
	{
		this->past_result.clear();//记录往届比赛的容器清空
		ofstream ofs;
		//trunc可以把之前存在的文件删除并重建
		ofs.open("比赛结果.csv", ios::trunc);
		ofs.close();
		this->m_speech.clear();
		this->v_speech.clear();
		cout << "清空成功" << endl;
	}
	else
	{
		cout << "清空失败" << endl;
		return;
	}
}
speech_manager::~speech_manager()
{

}