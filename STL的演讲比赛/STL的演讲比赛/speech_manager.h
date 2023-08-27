#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include<string>
#include<algorithm>
#include<numeric>
#include"contestant.h"
#include<functional>
#include<fstream>
#include<Windows.h>
#include<ctime>
//整个程序的管理
class speech_manager
{
public:
	//存储3个vector容器，分别存放第一轮12个员工的编号，第二轮晋级的6名选手的编号，第三轮晋级3名选手的编号
	vector<vector<int>>v_speech;

	//哈希表存放编号和对应的选手类
	map<int, contestant>m_speech;
	int count;//比赛的轮数
	//这个哈希表用于储存往届的结束和结果
	map<int, vector<string>>past_result;
	bool is_empty;//判断文件是否为空

	speech_manager();
	void game_process();//比赛流程
	void show_menu();//显示菜单
	void Init_data();//初始化数据
	void begin_competition();//开始比赛
	void drawing();//抽签
	double get_score();//评委打分
	void read_result();//读取往届的结果
	void save_data();//保存每一届的结果
	void clear_data();//清空数据
	~speech_manager();
};