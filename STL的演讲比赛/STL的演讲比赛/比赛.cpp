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
		case 0://退出系统
			exit(0); break;
		case 1://开始比赛
			speaker.game_process();
			break;
		case 2://查看往届记录
			speaker.read_result();
			break;
		case 3://清空往届记录
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