#include"speech_manager.h"
class Myclass//���ڳ�ǩ�����
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
//��ӡ����
void speech_manager::show_menu()
{
	cout << "********************" << endl;
	cout << "1����ʼ����" << endl;
	cout << "2���鿴�����¼" << endl;
	cout << "3����������¼" << endl;
	cout << "0���˳�����" << endl;
	cout << "********************" << endl;
}
//��ʼ������(��һ�ֱ���)
void speech_manager::Init_data()
{
	if (!this->v_speech.empty())//���ǿյ�
	{
		this->v_speech.clear();
	}
	vector<int>v;
	for (int i = 0; i < 12; i++)
	{
		contestant person;
		string m_name = "ѡ��";
		string temp = "ABCDEFGHIJKL";
		m_name += temp[i];
		person.name = m_name;
		//�Գɼ���ֵ
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
//��������
void speech_manager::game_process()
{
	this->Init_data();//��ʼ������
	//��һ�ֱ���
	this->count = 1;
	this->begin_competition();
	system("pause");
	//�ڶ��ֱ���
	this->count++;
	this->begin_competition();
	cout << "��������" << endl;
	this->save_data();
	cout << "����Ѽ�¼" << endl;
}
//��ʼ����
void speech_manager::begin_competition()
{
	cout << "��" << count << "�ֱ�����ʼ" << endl;
	this->drawing();//��ǩ
	multimap <double, int, greater<double>>mm;//���ڴ��keyΪ�ɼ��Ĺ�ϣ����������(��ϣ����ʱ�ͻ��Զ�����)
	for (vector<int>::iterator it = this->v_speech[this->count - 1].begin(); it != this->v_speech[this->count - 1].end(); it++)
	{
		map<int, contestant>::iterator its = this->m_speech.find(*it);
		its->second.score[this->count - 1] = this->get_score();//��ί���
		mm.insert(make_pair(its->second.score[this->count - 1], its->first));
	}
	vector<int>v2;//���ڴ�ŵ�һ�ֽ�����ı��
	int i = 0;
	cout << "�����ĳ�Ա�Լ��ɼ�" << endl;
	multimap<double, int>::iterator it = mm.begin();
	if (this->count == 1)
	{
		while (i < 6)
		{
			v2.push_back(it->second);//���չ�ϣ�������ѱ�Ÿ�ֵ��v2����
			it++;
			i++;
		}
		for (int i = 0; i < 6; i++)
		{
			map<int, contestant>::iterator its = this->m_speech.find(v2[i]);
			cout << "��� " << v2[i] << " ���� " << its->second.name << " �ɼ� " << its->second.score[0]<< endl;
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
			cout << "��� " << v2[i] << " ���� " << its->second.name << " �ɼ� " << its->second.score[1]<< endl;
		}
	}
	this->v_speech.push_back(v2);
}
//��ί���
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
//��ǩ
void speech_manager::drawing()
{
	cout << "ѡ�������ڳ�ǩ" << endl;
	cout << "-------------------" << endl;
	if (this->count == 1)//��һ�ֱ���
	{
		random_shuffle(this->v_speech[0].begin(), this->v_speech[0].end());
		cout << "��ǩ�Ľ������" << endl;
		for_each(this->v_speech[0].begin(), this->v_speech[0].end(), Myclass());
	}
	else
	{
		random_shuffle(this->v_speech[1].begin(), this->v_speech[1].end());
		cout << "��ǩ�Ľ������" << endl;
		for_each(this->v_speech[1].begin(), this->v_speech[1].end(), Myclass());
	}
	cout << endl;
}
//��������
void speech_manager::save_data()
{
	ofstream ofs;
	//ע�⣺��׺Ϊ.csv���ļ��м䶼Ҫ�á������ָ������������ݵ�ʱ��ҲҪ�ֶ�����
	ofs.open("�������.csv", ios::out | ios::app);
	for (vector<int>::iterator it = this->v_speech[2].begin(); it != this->v_speech[2].end(); it++)
	{
		ofs << *it << "," << this->m_speech[*it].score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	//��һ���¼��Ϻ�Ҫ���������ݶ�����
}
//��ȡ����Ľ��
void speech_manager::read_result()
{
	ifstream ifs("�������.csv", ios::in);
	if (!ifs.is_open())//���ļ�ʧ��
	{
		cout << "�ļ���ʧ��" << endl;
		this->is_empty = true;
		ifs.close();
		return;
	}
	//�ļ������
	char c;
	ifs >> c;
	if (ifs.eof())//��ȡ���ļ�β
	{
		cout << "�ļ�Ϊ��" << endl;
		this->is_empty = true;
		return;
	}
	//�ļ���Ϊ��
	ifs.putback(c);
	this->is_empty = false;
	string data;//��ȡ��ÿһ���������Ϣ
	int start = 0;//ÿ�ν�ȡ�ַ�����λ��
	int number = 0;//�ڼ���
	vector<string>message;//���ÿһ�����Ϣ�����ڴ�Ž���ϣ����
	while (ifs >> data)//��ȡһ��(��)
	{
		start = 0;
		number++;
		string m_data;//��ȡ���ַ���
		int position = -1;//�ҵ���������λ��
		while (true)
		{
			position = data.find(",",start);
			if (position == -1)//��һ�ж�ȡ����
			{
				break;
			}
			m_data = data.substr(start, position - start);//��ȡ���ַ���
			message.push_back(m_data);//����vector����
			start = position+1;
		}
		this->past_result.insert(make_pair(number, message));
		message.clear();
	}
	ifs.close();
	//��ȡ���
	for (map<int, vector<string>>::iterator it = this->past_result.begin(); it != this->past_result.end(); it++)
	{
		cout << "��" << it->first << "��Ľ��" << endl;
		for (int i = 0; i < 6; i+=2)
		{
			cout << "��� " << it->second[i] << " �ɼ� " << it->second[i + 1] << endl;
		}
	}
}
//�������
void speech_manager::clear_data()
{
	cout << "��ȷ���Ƿ�Ҫ���" << endl;
	char choice;
	cout << "�ǣ�y" << endl << "��n" << endl;
	cin >> choice;
	if (choice == 'y')
	{
		this->past_result.clear();//��¼����������������
		ofstream ofs;
		//trunc���԰�֮ǰ���ڵ��ļ�ɾ�����ؽ�
		ofs.open("�������.csv", ios::trunc);
		ofs.close();
		this->m_speech.clear();
		this->v_speech.clear();
		cout << "��ճɹ�" << endl;
	}
	else
	{
		cout << "���ʧ��" << endl;
		return;
	}
}
speech_manager::~speech_manager()
{

}