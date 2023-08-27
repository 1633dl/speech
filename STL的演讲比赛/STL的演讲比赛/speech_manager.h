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
//��������Ĺ���
class speech_manager
{
public:
	//�洢3��vector�������ֱ��ŵ�һ��12��Ա���ı�ţ��ڶ��ֽ�����6��ѡ�ֵı�ţ������ֽ���3��ѡ�ֵı��
	vector<vector<int>>v_speech;

	//��ϣ���ű�źͶ�Ӧ��ѡ����
	map<int, contestant>m_speech;
	int count;//����������
	//�����ϣ�����ڴ�������Ľ����ͽ��
	map<int, vector<string>>past_result;
	bool is_empty;//�ж��ļ��Ƿ�Ϊ��

	speech_manager();
	void game_process();//��������
	void show_menu();//��ʾ�˵�
	void Init_data();//��ʼ������
	void begin_competition();//��ʼ����
	void drawing();//��ǩ
	double get_score();//��ί���
	void read_result();//��ȡ����Ľ��
	void save_data();//����ÿһ��Ľ��
	void clear_data();//�������
	~speech_manager();
};