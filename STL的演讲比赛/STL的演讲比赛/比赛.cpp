#include"contestant.h"
#include"speech_manager.h"
int main()
{
	srand((unsigned int)time(NULL));
	speech_manager speaker;
	while (1)
	{
		speaker.show_menu();
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 0://�˳�ϵͳ
			exit(0); break;
		case 1://��ʼ����
			speaker.game_process();
			break;
		case 2://�鿴�����¼
			speaker.read_result();
			break;
		case 3://��������¼
			speaker.clear_data();
			break;
		default:
			break;
		}
		system("pause");
		system("cls");
	}
	system("pause");
	return 0;
}