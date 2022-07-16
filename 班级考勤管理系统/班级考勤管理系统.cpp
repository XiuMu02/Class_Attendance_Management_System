#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#pragma warning(disable:4996)

enum Sex {                                    //性别
	Man, Woman, Unknow                        //男，女，未知
};
enum Type {                                   //缺勤类型
	Late, Absent, Leave                       //迟到，缺席，请假
};
enum State {                                  //考勤信息状态
	No, Yes                                   //未确认，已确认
};
typedef struct attendanceInfo_node* apointer; //考勤信息结点指针类型
struct attendanceInfo_node {                  //考勤信息结点结构
	int X;                                    //编号，即在链表中的序号
	char num[15];                             //学号
	char name[10];                            //姓名
	tm data;                                  //日期
	int n;                                    //第几节
	char subject[25];                         //课程
	char locale[8];                           //地点
	enum Type type;                           //性质
	enum State state;                         //状态
	apointer next;                            //考勤信息结点指针域
};
typedef apointer alklist;                     //考勤信息单链表类型，即头指针类型
typedef struct studentInfo_node* spointer;    //学生信息结点指针类型
struct studentInfo_node {                     //学生信息结点结构
	int X;                                    //编号，即在链表中的序号
	char name[10];                            //姓名
	enum Sex sex;                             //性别
	char grade[8];                            //年级
	char clas[20];                            //班级
	char num[15];                             //学号
	char password[20];                        //密码
	char phone[15];                           //手机
	char idCard[20];                          //身份证
	int times;                                //缺勤次数(非出席次数)
	spointer next;                            //学生信息结点指针域
};
typedef spointer slklist;                     //学生信息单链表类型，即头指针类型

struct student {                              //临时用学生简易信息
	char name[10];                            //姓名
	char num[15];                             //学号
	int times;                                //缺勤次数(非出席次数)
};

//主要功能函数
void Title(); //标题函数，用于输出标题
void Registe(slklist* studentHead, spointer* studentRear); //注册函数，用于用户注册
void Login(int flag); //登录函数，用于用户登录和管理员登录
void Help(); //帮助函数，用于查看程序使用说明书
void AdminMenu(slklist* studentHead, alklist* attendanceHead, apointer* attendanceRear); //管理员菜单函数，用于显示菜单并选择功能
void UserMenu(spointer sp); //用户菜单函数，用于显示菜单并选择功能
void StudentInfo(); //查看学生信息
void Query(); //查询考勤信息
void Add(); //添加考勤信息
void Delete(); //删除考勤信息
void Modify(); //修改考勤信息
void Statistic(); //统计缺勤人员
void Super(); //超级管理权限，暂时无实用功能
void Init(); //初始化系统
void UserInfo(spointer sp); //查看个人信息
void Confirm(spointer sp); //确认个人考勤
void ChangePassword(spointer sp); //修改密码
//辅助操作函数
void DisplayCursor(int flag); //显示或隐藏光标
void Goto_xy(short x, short y); //定位光标位置到指定坐标
void InputPassword(char* password); //输入密码
void ReadStudentInfo(slklist* studentHead, spointer* studentRear, int flag); //从文件读取学生信息，建立学生信息链表
void WriteStudentInfo(slklist* studentHead); //将学生信息链表写入文件
void ReadAttendanceInfo(alklist* attendanceHead, apointer* attendanceRear, int flag); //从文件读取考勤信息，建立考勤信息链表
void WriteAttendanceInfo(alklist* attendanceHead); //将考勤信息链表写入文件
void Destroy(slklist* studentHead, alklist* attendanceHead); //销毁链表
void QuickSort(int flag, struct student stu[], int left, int right); //快速排序

slklist studentHead = NULL; //学生信息链表头指针
spointer studentRear = NULL; //学生信息链表尾指针
alklist attendanceHead = NULL; //考勤信息链表头指针
apointer attendanceRear = NULL; //考勤信息链表尾指针

//主函数
int main() {
	char choice;
	ReadStudentInfo(&studentHead, &studentRear, 1); //建立学生信息链表
	ReadAttendanceInfo(&attendanceHead, &attendanceRear, 1); //建立考勤信息链表
	SetConsoleTitle(TEXT("◇ 班 级 考 勤 管 理 系 统 ◇")); //设置控制台标题
	do { //欢迎界面
		system("cls");
		printf("\n\t\t\t=====================================================================\n");
		printf("\t\t\t  ===============                                   ===============\n");
		printf("\t\t\t   ◇=========== 欢 迎 使 用 班 级 考 勤 管 理 系 统 ===========◇\n");
		printf("\t\t\t  ===============                                   ===============\n");
		printf("\t\t\t=====================================================================\n\n\n\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                             1.用户模式\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                             2.管理模式\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                             3. 帮  助\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                             4.退出系统\n");
		printf("\t\t\t                        --------------------\n");
		DisplayCursor(0); //隐藏光标
		choice = _getch();
		switch (choice) {
		case '1': //用户模式
			do { //用户登录注册选择界面
				system("cls");
				Title();
				printf("\t\t\t                            请登录或注册\n");
				printf("\t\t\t                        --------------------\n");
				printf("\t\t\t                               1.登录\n");
				printf("\t\t\t                        --------------------\n");
				printf("\t\t\t                               2.注册\n");
				printf("\t\t\t                        --------------------\n");
				printf("\t\t\t                               3.取消\n");
				printf("\t\t\t                        --------------------\n");
				choice = _getch();
				if (choice == '1') { //登录
					Login(0);
					break;
				}
				else if (choice == '2') { //注册
					Registe(&studentHead, &studentRear);
					break;
				}
				else if (choice == '3') //取消，返回欢迎界面
					break;
			} while (1);
			break;
		case '2':Login(1); break; //管理模式
		case '3':Help(); break; //帮助
		case '4':exit(0); //退出系统
		}
	} while (1);
	return 0;
}

//标题函数，用于输出标题
void Title() {
	system("cls");
	printf("\n\t\t\t                    ◇ 班 级 考 勤 管 理 系 统 ◇\n");
	printf("\t\t\t=====================================================================\n\n");
}

//注册函数，用于用户注册
void Registe(slklist* studentHead, spointer* studentRear) {
	while (1) {
		Title();
		printf("\t\t\t                              用户注册\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("\t\t\t                ┃ 姓    名：                      ┃\n");
		printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
		printf("\t\t\t                ┃ 性    别：                      ┃\n");
		printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
		printf("\t\t\t                ┃ 年    级：                      ┃\n");
		printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
		printf("\t\t\t                ┃ 班    级：                      ┃\n");
		printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
		printf("\t\t\t                ┃ 学    号：                      ┃\n");
		printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
		printf("\t\t\t                ┃ 密    码：                      ┃\n");
		printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
		printf("\t\t\t                ┃ 确认密码：                      ┃\n");
		printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
		printf("\t\t\t                ┃ 手    机：                      ┃\n");
		printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
		printf("\t\t\t                ┃ 身 份 证：                      ┃\n");
		printf("\t\t\t                ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
		spointer sp = NULL, sp1 = (*studentHead)->next;
		int exist = 0; //学号是否已注册
		if ((sp = (spointer)malloc(sizeof(struct studentInfo_node))) == NULL) {
			printf("内存申请出错！\n");
			exit(-1);
		}
		char sexs[10], sex[3], password1[20], choice;
		sp->X = (*studentRear)->X + 1;
		DisplayCursor(1); //显示光标
		Goto_xy(52, 7); //设置光标位置
		scanf("%s", sp->name); //输入姓名
		Goto_xy(52, 9);
		scanf("%s", sexs); //输入性别
		strncpy(sex, sexs, 2);
		sex[2] = '\0';
		if (strcmp("男", sex) == 0)
			sp->sex = Man;
		else if (strcmp("女", sex) == 0)
			sp->sex = Woman;
		else
			sp->sex = Unknow;
		Goto_xy(52, 11);
		scanf("%s", sp->grade); //输入年级
		Goto_xy(52, 13);
		scanf("%s", sp->clas); //输入班级
		Goto_xy(52, 15);
		scanf("%s", sp->num); //输入学号
		while (sp1 != NULL) { //检测学号是否已经注册
			if (strcmp(sp1->num, sp->num) == 0) {
				exist = 1;
				break;
			}
			sp1 = sp1->next;
		}
		if (exist) { //学号已注册
			MessageBeep(MB_ICONHAND); //发出错误警报声
			printf("\n\n\n\n\n\n\n\n\n\n\t\t\t                     该学号已注册，请重新注册！\n\n");
			printf("\t\t\t                          1.确定    2.取消\n");
			DisplayCursor(0); //隐藏光标
			choice = _getch();
			if (choice == '1' || choice == '\r') {
				free(sp);
				continue;
			}
			else
				break;
		}
		Goto_xy(52, 17);
		InputPassword(sp->password); //输入密码
		Goto_xy(52, 19);
		InputPassword(password1); //输入确认密码
		if (strcmp(sp->password, password1) != 0) { //两次密码不相同
			MessageBeep(MB_ICONHAND);
			printf("\n\n\n\n\n\n\n\t\t\t                    两次密码不相同，请重新注册！\n\n");
			printf("\t\t\t                          1.确定    2.取消\n");
			DisplayCursor(0); //隐藏光标
			choice = _getch();
			if (choice == '1' || choice == '\r') {
				free(sp);
				continue;
			}
			else
				break;
		}
		Goto_xy(52, 21);
		scanf("%s", sp->phone); //输入手机
		Goto_xy(52, 23);
		scanf("%s", sp->idCard); //输入身份证
		sp->times = 0;
		sp->next = NULL;
		printf("\n\n\t\t\t                      是否用以上信息进行注册？\n\n");
		printf("\t\t\t                          1.确定    2.取消\n");
		DisplayCursor(0); //隐藏光标
		choice = _getch();
		if (choice == '1' || choice == '\r') {
			(*studentRear)->next = sp;
			*studentRear = sp;
			WriteStudentInfo(studentHead);
			Title();
			printf("\t\t\t                              注册成功\n");
			printf("\t\t\t                        --------------------\n\n\n");
			printf("\t\t\t                     \33[31m请牢记您的账号(学号)和密码\33[0m\n\n");
			printf("\t\t\t                      账号：%s\n", (*studentRear)->num);
			printf("\t\t\t                      密码：%s\n\n\n\n", (*studentRear)->password);
			DisplayCursor(1); //显示光标
			system("pause");
		}
		else
			free(sp);
		break;
	}
}

//登录函数，用于用户登录和管理员登录
void Login(int flag) {
	while (1) {
		Title();
		flag ? printf("\t\t\t                             管理员登录\n") : printf("\t\t\t                              用户登录\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                    ┏━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("\t\t\t                    ┃ 账号：                  ┃\n");
		printf("\t\t\t                    ┣━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
		printf("\t\t\t                    ┃ 密码：                  ┃\n");
		printf("\t\t\t                    ┗━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
		spointer sp = studentHead->next;
		char account[15], password[20];
		char choice;
		int i, j, exist = 0; //exist表示账号是否存在
		DisplayCursor(1); //显示光标
		Goto_xy(52, 7); //设置光标位置
		scanf("%s", account);
		Goto_xy(52, 9);
		InputPassword(password);
		if (flag) { //管理员登录
			if (strcmp("admin", account) == 0 && strcmp("admin", password) == 0) { //登录成功
				DisplayCursor(0); //隐藏光标
				Title();
				printf("\t\t\t                              登录成功\n");
				printf("\t\t\t                        --------------------\n\n\n");
				printf("\t\t\t                      欢迎使用班级考勤管理系统\n\n");
				printf("\t\t\t                       正在进入管理员菜单界面\n\n");
				printf("\t\t\t                      ┏━━━━━━━━━━━━━━━━━━━━━┓\n");
				printf("\t\t\t                      ┃                     ┃\n");
				printf("\t\t\t                      ┗━━━━━━━━━━━━━━━━━━━━━┛\n");
				Goto_xy(48, 13);
				j = 2500;
				for (i = 1; i <= 10; i++) {
					printf("\33[36m★\33[0m");
					Beep(j, 500);
					j -= 200;
				}
				AdminMenu(&studentHead, &attendanceHead, &attendanceRear);
			}
			else { //登录失败
				MessageBeep(MB_ICONHAND);
				printf("\n\n\n\t\t\t                    账号或密码错误，请重新登录！\n\n");
				printf("\t\t\t                          1.确定    2.取消\n");
				DisplayCursor(0); //隐藏光标
				choice = _getch();
				if (choice == '1' || choice == '\r')
					continue;
				else
					break;
			}
		}
		else { //用户登录
			while (sp != NULL) {
				if (strcmp(sp->num, account) == 0)
					break;
				sp = sp->next;
			}
			if (sp != NULL && strcmp(sp->num, account) == 0 && strcmp(sp->password, password) == 0) { //登录成功
				DisplayCursor(0); //隐藏光标
				Title();
				printf("\t\t\t                              登录成功\n");
				printf("\t\t\t                        --------------------\n\n\n");
				printf("\t\t\t                      欢迎使用班级考勤管理系统\n\n");
				printf("\t\t\t                        正在进入用户菜单界面\n\n");
				printf("\t\t\t                      ┏━━━━━━━━━━━━━━━━━━━━━┓\n");
				printf("\t\t\t                      ┃                     ┃\n");
				printf("\t\t\t                      ┗━━━━━━━━━━━━━━━━━━━━━┛\n");
				Goto_xy(48, 13);
				j = 500;
				for (i = 1; i <= 10; i++) {
					printf("\33[36m■\33[0m");
					Beep(j, 500);
					j += 200;
				}
				UserMenu(sp);
			}
			else { //登录失败
				MessageBeep(MB_ICONHAND);
				printf("\n\n\n\t\t\t                    账号或密码错误，请重新登录！\n\n");
				printf("\t\t\t                          1.确定    2.取消\n");
				DisplayCursor(0); //隐藏光标
				choice = _getch();
				if (choice == '1' || choice == '\r')
					continue;
				else
					break;
			}
		}
	}
}

//帮助函数，用于查看程序使用说明书
void Help() {
	char choice;
	int times = 1;
	system("cls");
	printf("\33[10B"); //光标下移10行
	printf("\t\t\t       ■      ■     ■■■■■     ■             ■■■■■\n");
	printf("\t\t\t       ■      ■     ■             ■             ■      ■\n");
	printf("\t\t\t       ■      ■     ■             ■             ■      ■\n");
	printf("\t\t\t       ■■■■■     ■■■■■     ■             ■■■■■\n");
	printf("\t\t\t       ■      ■     ■             ■             ■\n");
	printf("\t\t\t       ■      ■     ■             ■             ■\n");
	printf("\t\t\t       ■      ■     ■■■■■     ■■■■■     ■\n");
	while (times <= 2) {
		printf("\33[7A\33[31m");
		printf("\t\t\t       ■      ■     ■■■■■     ■             ■■■■■\n\t\t\t       ■      ■     ■             ■             ■      ■\n\t\t\t       ■      ■     ■             ■             ■      ■\n\t\t\t       ■■■■■     ■■■■■     ■             ■■■■■\n\t\t\t       ■      ■     ■             ■             ■\n\t\t\t       ■      ■     ■             ■             ■\n\t\t\t       ■      ■     ■■■■■     ■■■■■     ■\n");
		Sleep(300);
		printf("\33[7A\33[32m");
		printf("\t\t\t       ■      ■     ■■■■■     ■             ■■■■■\n\t\t\t       ■      ■     ■             ■             ■      ■\n\t\t\t       ■      ■     ■             ■             ■      ■\n\t\t\t       ■■■■■     ■■■■■     ■             ■■■■■\n\t\t\t       ■      ■     ■             ■             ■\n\t\t\t       ■      ■     ■             ■             ■\n\t\t\t       ■      ■     ■■■■■     ■■■■■     ■\n");
		Sleep(300);
		printf("\33[7A\33[33m");
		printf("\t\t\t       ■      ■     ■■■■■     ■             ■■■■■\n\t\t\t       ■      ■     ■             ■             ■      ■\n\t\t\t       ■      ■     ■             ■             ■      ■\n\t\t\t       ■■■■■     ■■■■■     ■             ■■■■■\n\t\t\t       ■      ■     ■             ■             ■\n\t\t\t       ■      ■     ■             ■             ■\n\t\t\t       ■      ■     ■■■■■     ■■■■■     ■\n");
		Sleep(300);
		printf("\33[7A\33[34m");
		printf("\t\t\t       ■      ■     ■■■■■     ■             ■■■■■\n\t\t\t       ■      ■     ■             ■             ■      ■\n\t\t\t       ■      ■     ■             ■             ■      ■\n\t\t\t       ■■■■■     ■■■■■     ■             ■■■■■\n\t\t\t       ■      ■     ■             ■             ■\n\t\t\t       ■      ■     ■             ■             ■\n\t\t\t       ■      ■     ■■■■■     ■■■■■     ■\n");
		Sleep(300);
		printf("\33[7A\33[35m");
		printf("\t\t\t       ■      ■     ■■■■■     ■             ■■■■■\n\t\t\t       ■      ■     ■             ■             ■      ■\n\t\t\t       ■      ■     ■             ■             ■      ■\n\t\t\t       ■■■■■     ■■■■■     ■             ■■■■■\n\t\t\t       ■      ■     ■             ■             ■\n\t\t\t       ■      ■     ■             ■             ■\n\t\t\t       ■      ■     ■■■■■     ■■■■■     ■\n");
		Sleep(300);
		printf("\33[7A\33[36m");
		printf("\t\t\t       ■      ■     ■■■■■     ■             ■■■■■\n\t\t\t       ■      ■     ■             ■             ■      ■\n\t\t\t       ■      ■     ■             ■             ■      ■\n\t\t\t       ■■■■■     ■■■■■     ■             ■■■■■\n\t\t\t       ■      ■     ■             ■             ■\n\t\t\t       ■      ■     ■             ■             ■\n\t\t\t       ■      ■     ■■■■■     ■■■■■     ■\n");
		Sleep(300);
		printf("\33[0m"); //关闭所有输出属性，恢复至默认
		times++;
	}
	DisplayCursor(1); //显示光标
	Title();
	printf("\t\t\t                                帮助\n");
	printf("\t\t\t                        --------------------\n\n");
	printf("1、选项：在选项界面按相应数字即可进入相应功能界面；在确认&取消选项中，按「1」或「回车」键即为确认，其他键为取消。\n\n");
	printf("2、注册：已注册的学号不允许再注册；相应学生信息允许的最长字符数为：姓名-9，年级-7，班级-19，学号-14，密码-19，手机-14，身份证-19。\n\n");
	printf("3、登录：学生登录使用注册时的学号和密码进行登录；管理员登录使用特定的账号和密码进行登录。\n\n");
	printf("4、. . . . . . \n\n");
	printf("\n按「1」可打开查看详细程序设计说明书，按其他键返回菜单界面. . . ");
	while(1) {
		choice = _getch();
		if (choice == '1')
			system("start 「班级考勤管理系统」程序设计说明书.doc"); //打开程序设计说明书Word文件
		else
			break;
	}
}

//管理员菜单函数，用于显示菜单并选择功能
void AdminMenu(slklist* studentHead, alklist* attendanceHead, apointer* attendanceRear) {
	char choice;
	while (1) {
		Title();
		printf("\t\t\t                         请选择要进行的操作\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           1.查看学生信息\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           2.查询考勤信息\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           3.添加考勤信息\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           4.删除考勤信息\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           5.修改考勤信息\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           6.统计缺勤人员\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           7.超级管理权限\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           8.初始化系统\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           9.退出系统\n");
		printf("\t\t\t                        --------------------\n");
		DisplayCursor(0); //隐藏光标
		choice = _getch();
		switch (choice) {
		case '1':StudentInfo(); break; //查看学生信息
		case '2':Query(); break; //查询考勤信息
		case '3':Add(); break; //添加考勤信息
		case '4':Delete(); break; //删除考勤信息
		case '5':Modify(); break; //修改考勤信息
		case '6':Statistic(); break; //统计缺勤人员
		case '7':Super(); break; //超级管理权限，暂时无实用功能
		case '8':Init(); break; //初始化系统
		case '9':exit(0); //退出系统
		}
	}
}

//用户菜单函数，用于显示菜单并选择功能
void UserMenu(spointer sp) {
	char choice;
	while (1) {
		Title();
		printf("\t\t\t                         请选择要进行的操作\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           1.查看个人信息\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           2.确认个人考勤\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           3.查询考勤信息\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           4.统计缺勤人员\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           5.修改密码\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           6.退出系统\n");
		printf("\t\t\t                        --------------------\n");
		DisplayCursor(0); //隐藏光标
		choice = _getch();
		switch (choice) {
		case '1':UserInfo(sp); break; //查看个人信息
		case '2':Confirm(sp); break; //确认个人考勤
		case '3':Query(); break; //查询考勤信息
		case '4':Statistic(); break; //统计缺勤人员
		case '5':ChangePassword(sp); break; //修改密码
		case '6':exit(0); //退出系统
		}
	}
}

//查看学生信息
void StudentInfo() {
	Title();
	printf("\t\t\t                            查看学生信息\n");
	printf("\t\t\t                        --------------------\n");
	int amount = studentRear->X, n, i = 11;
	spointer sp = studentHead->next;
	DisplayCursor(1); //显示光标
	if (amount == 0)
		printf("系统共存有\33[36m0\33[0m位学生的信息！\n");
	else {
		printf("系统共存有\33[36m%d\33[0m位学生的信息，具体如下：\n\n", amount);
		printf("\t\t\t         ┏━━━━━━━┳━━━━━━━━━━━┳━━━━━━━━━━━━━━━┳━━━━━━━━━━━┓\n");
		printf("\t\t\t         ┃  编号 ┃    姓名   ┃      学号     ┃  缺勤次数 ┃\n");
		while (sp != NULL) {
			printf("\t\t\t         ┣━━━━━━━╋━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━┫\n");
			printf("\t\t\t         ┃       ┃           ┃               ┃           ┃\n");
			Goto_xy(37, i);
			printf("%02d", sp->X);
			Goto_xy(46, i);
			printf("%s", sp->name);
			Goto_xy(56, i);
			printf("%s", sp->num);
			Goto_xy(74, i);
			printf("%d次\n", sp->times);
			i += 2;
			sp = sp->next;
		}
		printf("\t\t\t         ┗━━━━━━━┻━━━━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━━━━┛\n");
		printf("\n请输入要查看的学生编号(输入0可返回菜单界面)：");
		scanf("%d", &n);
		if (n == 0) //返回菜单界面
			return;
		else if (n >= 1 && n <= studentRear->X) {
			Title();
			printf("\t\t\t                            查看学生信息\n");
			printf("\t\t\t                        --------------------\n");
			printf("\t\t\t                ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
			printf("\t\t\t                ┃ 姓    名：                      ┃\n");
			printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
			printf("\t\t\t                ┃ 性    别：                      ┃\n");
			printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
			printf("\t\t\t                ┃ 年    级：                      ┃\n");
			printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
			printf("\t\t\t                ┃ 班    级：                      ┃\n");
			printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
			printf("\t\t\t                ┃ 学    号：                      ┃\n");
			printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
			printf("\t\t\t                ┃ 密    码：                      ┃\n");
			printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
			printf("\t\t\t                ┃ 手    机：                      ┃\n");
			printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
			printf("\t\t\t                ┃ 身 份 证：                      ┃\n");
			printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
			printf("\t\t\t                ┃ 缺勤次数：                      ┃\n");
			printf("\t\t\t                ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
			apointer ap = attendanceHead->next;
			sp = studentHead->next;
			int i = 1;
			while (sp != NULL) {
				if (sp->X == n)
					break;
				sp = sp->next;
			}
			Goto_xy(52, 7);
			printf("%s", sp->name);
			Goto_xy(52, 9);
			if (sp->sex == Man)
				printf("男");
			else if (sp->sex == Woman)
				printf("女");
			else
				printf("未知");
			Goto_xy(52, 11);
			printf("%s", sp->grade);
			Goto_xy(52, 13);
			printf("%s", sp->clas);
			Goto_xy(52, 15);
			printf("%s", sp->num);
			Goto_xy(52, 17);
			printf("%s", sp->password);
			Goto_xy(52, 19);
			printf("%s", sp->phone);
			Goto_xy(52, 21);
			printf("%s", sp->idCard);
			Goto_xy(52, 23);
			printf("%d次", sp->times);
			printf("\n\n");
			if (sp->times != 0) { //该学生考勤信息条数不为0
				printf("该学生共有\33[36m%d\33[0m条考勤信息，具体如下：\n\n", sp->times);
				printf("序号       学号       姓名        日期      第几节    课程              地点    性质    状态\n\n");
				while (ap != NULL) {
					if (strcmp(sp->num, ap->num) == 0) {
						printf(" %02d    %-14s %-8s %04u-%02u-%02u   第%d节   %-18s %-8s ", i, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
						if (ap->type == Late)
							printf("迟到   ");
						else if (ap->type == Absent)
							printf("缺席   ");
						else
							printf("请假   ");
						if (ap->state == No)
							printf("\33[31m未确认\33[0m\n");
						else
							printf("\33[32m已确认\33[0m\n");
						i++;
					}
					ap = ap->next;
				}
			}
			else //该学生考勤信息条数为0
				printf("该学生共有\33[36m0\33[0m条考勤信息！\n");
		}
		else
			printf("\a\n\n\t\t\t                            编号输入错误！\n");
	}
	printf("\n");
	system("pause");
}

//查询考勤信息
void Query() {
	Title();
	printf("\t\t\t                            查询考勤信息\n");
	printf("\t\t\t                        --------------------\n");
	printf("\t\t\t                            1.按条件查询\n");
	printf("\t\t\t                        --------------------\n");
	printf("\t\t\t                            2.查看全部\n");
	printf("\t\t\t                        --------------------\n");
	printf("\t\t\t                            3.取消\n");
	printf("\t\t\t                        --------------------\n");
	char choice;
	apointer ap = attendanceHead->next;
	DisplayCursor(0); //隐藏光标
	while (1) {
		choice = _getch();
		if (choice == '1' || choice == '2' || choice == '3')
			break;
	}
	if (choice == '3') //取消，返回菜单界面
		return;
	else if (choice == '2') { //查看全部考勤信息
		Title();
		printf("\t\t\t                            查询考勤信息\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                              查看全部\n\n");
		printf("系统共存有\33[36m%d\33[0m条考勤信息，具体如下：\n\n", attendanceRear->X);
		printf("编号       学号       姓名        日期      第几节    课程              地点    性质    状态\n\n");
		while (ap != NULL) {
			printf(" %02d    %-14s %-8s %04u-%02u-%02u   第%d节   %-18s %-8s ", ap->X, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
			if (ap->type == Late)
				printf("迟到   ");
			else if (ap->type == Absent)
				printf("缺席   ");
			else
				printf("请假   ");
			if (ap->state == No)
				printf("\33[31m未确认\33[0m\n");
			else
				printf("\33[32m已确认\33[0m\n");
			ap = ap->next;
		}
	}
	else { //按条件查询考勤信息
		enum Type type;
		enum State state;
		char num[15], name[10], data[11], n[3], subject[25], locale[8], type0[5], state0[7], str[5];
		int flag = 1, amount = 0;
		Title();
		printf("\t\t\t                            查询考勤信息\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                             按条件查询\n\n");
		printf("请输入查询参数(未输入的参数将默认输出所有符合项)：\n");
		printf("注：日期格式：xxxx-xx-xx，性质：迟到/缺勤/请假，状态：未确认/已确认\n");
		printf("\t┏━━━━━━━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━━━┳━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━┳━━━━━━━┳━━━━━━━━━┓\n");
		printf("\t┃      学号     ┃   姓名  ┃    日期   ┃ 第几节┃            课程           ┃   地点  ┃  性质 ┃   状态  ┃\n");
		printf("\t┣━━━━━━━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━━━╋━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━╋━━━━━━━╋━━━━━━━━━┫\n");
		printf("\t┃               ┃         ┃           ┃       ┃                           ┃         ┃       ┃         ┃\n");
		printf("\t┗━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━━━┻━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━┻━━━━━━━━━┛\n");
		DisplayCursor(1); //显示光标
		rewind(stdin); //清空键盘缓冲区
		Goto_xy(10, 13); gets_s(num);
		Goto_xy(27, 13); gets_s(name);
		Goto_xy(36, 13); gets_s(data);
		Goto_xy(50, 13); gets_s(n);
		Goto_xy(60, 13); gets_s(subject);
		Goto_xy(85, 13); gets_s(locale);
		Goto_xy(95, 13); gets_s(type0);
		Goto_xy(103, 13); gets_s(state0);
		printf("\n\n编号       学号       姓名        日期      第几节    课程              地点    性质    状态\n\n");
		while (ap != NULL) { //查找符合条件的考勤信息，并输出
			flag = 1;
			if (strcmp(num, "\0") != 0)
				flag = flag && !strcmp(ap->num, num);
			if (strcmp(name, "\0") != 0)
				flag = flag && !strcmp(ap->name, name);
			if (strcmp(data, "\0") != 0) {
				strncpy(str, data, 4);
				flag = flag && (ap->data.tm_year + 1900 == atof(str));
				str[0] = data[5]; str[1] = data[6]; str[2] = '\0';
				flag = flag && (ap->data.tm_mon + 1 == atof(str));
				str[0] = data[8]; str[1] = data[9]; str[2] = '\0';
				flag = flag && (ap->data.tm_mday == atof(str));
			}
			if (strcmp(n, "\0") != 0)
				flag = flag && (ap->n == atof(n));
			if (strcmp(subject, "\0") != 0)
				flag = flag && !strcmp(ap->subject, subject);
			if (strcmp(locale, "\0") != 0)
				flag = flag && !strcmp(ap->locale, locale);
			if (strcmp(type0, "\0") != 0) {
				if (strcmp(type0, "迟到") == 0)
					type = Late;
				if (strcmp(type0, "缺席") == 0)
					type = Absent;
				if (strcmp(type0, "请假") == 0)
					type = Leave;
				flag = flag && (ap->type == type);
			}
			if (strcmp(state0, "\0") != 0) {
				if (strcmp(state0, "未确认") == 0)
					state = No;
				if (strcmp(state0, "已确认") == 0)
					state = Yes;
				flag = flag && (ap->state == state);
			}
			if (flag) {
				amount++;
				printf(" %02d    %-14s %-8s %04u-%02u-%02u   第%d节   %-18s %-8s ", ap->X, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
				if (ap->type == Late)
					printf("迟到   ");
				else if (ap->type == Absent)
					printf("缺席   ");
				else
					printf("请假   ");
				if (ap->state == No)
					printf("\33[31m未确认\33[0m\n");
				else
					printf("\33[32m已确认\33[0m\n");
			}
			ap = ap->next;
		}
		printf("\n\n\t\t\t                     共查询到以上\33[36m%d\33[0m条考勤信息！\n", amount);
	}
	printf("\n");
	DisplayCursor(1); //显示光标
	system("pause");
}

//添加考勤信息
void Add() {
	while (1) {
		int year, month, flag = 0;
		char choice;
		apointer ap;
		spointer sp = studentHead->next;
		if ((ap = (apointer)malloc(sizeof(struct attendanceInfo_node))) == NULL) {
			printf("内存申请出错！\n");
			system("pause");
			return;
		}
		Title();
		printf("\t\t\t                            添加考勤信息\n");
		printf("\t\t\t                        --------------------\n");
		DisplayCursor(1); //显示光标
		ap->X = attendanceRear->X + 1;
		printf("\t\t\t请输入[学号]：");
		scanf("%s", ap->num);
		printf("\t\t\t请输入[姓名]：");
		scanf("%s", ap->name);
		printf("\t\t\t请输入[日期](格式：xxxx-xx-xx)：");
		scanf("%u-%u-%u", &year, &month, &ap->data.tm_mday);
		ap->data.tm_year = year - 1900;
		ap->data.tm_mon = month - 1;
		printf("\t\t\t请输入[第几节]：");
		scanf("%d", &ap->n);
		printf("\t\t\t请输入[课程]：");
		scanf("%s", ap->subject);
		printf("\t\t\t请输入[地点]：");
		scanf("%s", ap->locale);
		printf("\t\t\t请选择[性质]：1.迟到  2.缺席  3.请假\n");
		while (1) {
			DisplayCursor(0); //隐藏光标
			choice = _getch();
			if (choice == '1') {
				ap->type = Late;
				printf("\33[1A\t\t\t请选择[性质]：迟到                   \n\n");
			}
			else if (choice == '2') {
				ap->type = Absent;
				printf("\33[1A\t\t\t请选择[性质]：缺席                   \n\n");
			}
			else if (choice == '3') {
				ap->type = Leave;
				printf("\33[1A\t\t\t请选择[性质]：请假                   \n\n");
			}
			else
				continue;
			break;
		}
		ap->state = No;
		ap->next = NULL;
		printf("编号       学号       姓名        日期      第几节    课程              地点    性质    状态\n\n");
		printf(" %02d    %-14s %-8s %04u-%02u-%02u   第%d节   %-18s %-8s ", ap->X, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
		if (ap->type == Late)
			printf("迟到   ");
		else if (ap->type == Absent)
			printf("缺席   ");
		else
			printf("请假   ");
		printf("\33[31m未确认\33[0m\n\n\n");
		printf("\t\t\t                      是否确定添加该考勤信息？\n\n");
		printf("\t\t\t                          1.确定    2.取消\n");
		choice = _getch();
		if (choice == '1' || choice == '\r') {
			while (sp != NULL) {
				if (strcmp(sp->num, ap->num) == 0 && strcmp(sp->name, ap->name) == 0) {
					sp->times++;
					WriteStudentInfo(&studentHead);
					attendanceRear->next = ap;
					attendanceRear = ap;
					WriteAttendanceInfo(&attendanceHead);
					flag = 1;
					break;
				}
				sp = sp->next;
			}
			if (!flag) {
				printf("\a\n\n\t\t\t                        学号或姓名输入错误！\n\n");
				DisplayCursor(1); //显示光标
				system("pause");
				break;
			}
			printf("\33[3A\t\t\t                                                \n");
			printf("\33[1A\t\t\t                  考勤信息添加成功，是否继续添加？\n\n");
			printf("\t\t\t                          1.确定    2.取消\n");
			choice = _getch();
			if (choice == '1' || choice == '\r')
				continue;
		}
		break;
	}
}

//删除考勤信息
void Delete() {
	Title();
	printf("\t\t\t                            删除考勤信息\n");
	printf("\t\t\t                        --------------------\n");
	int n, amount = attendanceRear->X;
	spointer sp = studentHead->next;
	apointer ap = attendanceHead->next, aq;
	DisplayCursor(1); //显示光标
	if (amount == 0) { //无考勤信息可删除
		printf("系统共存有\33[36m0\33[0m条考勤信息！\n\n");
		system("pause");
		return;
	}
	printf("系统共存有\33[36m%d\33[0m条考勤信息，具体如下：\n\n", amount);
	printf("编号       学号       姓名        日期      第几节    课程              地点    性质    状态\n\n");
	while (ap != NULL) {
		printf(" %02d    %-14s %-8s %04u-%02u-%02u   第%d节   %-18s %-8s ", ap->X, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
		if (ap->type == Late)
			printf("迟到   ");
		else if (ap->type == Absent)
			printf("缺席   ");
		else
			printf("请假   ");
		if (ap->state == No)
			printf("\33[31m未确认\33[0m\n");
		else
			printf("\33[32m已确认\33[0m\n");
		ap = ap->next;
	}
	printf("\n请输入要删除的考勤信息编号(输入0可删除全部，输入-1可返回菜单界面)：");
	scanf("%d", &n);
	if (n == -1) //返回菜单界面
		return;
	else if (n == 0) { //删除全部考勤信息
		while (ap != NULL) {
			aq = ap->next;
			free(ap);
			ap = aq;
		}
		attendanceHead->next = NULL;
		attendanceRear = attendanceHead;
		WriteAttendanceInfo(&attendanceHead);
		while (sp != NULL) {
			sp->times = 0;
			sp = sp->next;
		}
		WriteStudentInfo(&studentHead);
		printf("\n\n\t\t\t                     成功删除以上\33[36m%d\33[0m条考勤信息！\n", amount);
	}
	else if (n >= 1 && n <= amount) { //删除指定编号考勤信息
		ap = attendanceHead->next;
		while (ap != NULL) {
			if (ap->X == n - 1) {
				aq = ap->next;
				ap->next = aq->next;
				sp = studentHead->next;
				while (sp != NULL) {
					if (strcmp(sp->num, aq->num) == 0) {
						sp->times--;
						break;
					}
					sp = sp->next;
				}
				free(aq);
				if (n == amount) //若删除的是尾结点，则尾指针指向新尾结点
					attendanceRear = ap;
				break;
			}
			ap = ap->next;
		}
		ap = ap->next;
		while (ap != NULL) { //在删除结点后的结点编号减一
			ap->X--;
			ap = ap->next;
		}
		WriteAttendanceInfo(&attendanceHead);
		WriteStudentInfo(&studentHead);
		printf("\n\n\t\t\t                    成功删除编号为\33[36m%02d\33[0m的考勤信息！\n", n);
	}
	else
		printf("\a\n\n\t\t\t                            编号输入错误！\n");
	printf("\n");
	system("pause");
}

//修改考勤信息
void Modify() {
	Title();
	printf("\t\t\t                            修改考勤信息\n");
	printf("\t\t\t                        --------------------\n");
	char choice, num0[15], num[15], name[10];
	int n, amount = attendanceRear->X, year, month, flag1 = 0, flag2 = 0;
	spointer sp = studentHead->next;
	apointer ap = attendanceHead->next;
	DisplayCursor(1); //显示光标
	if (amount == 0) { //无考勤信息可修改
		printf("系统共存有\33[36m0\33[0m条考勤信息！\n\n");
		system("pause");
		return;
	}
	printf("系统共存有\33[36m%d\33[0m条考勤信息，具体如下：\n\n", amount);
	printf("编号       学号       姓名        日期      第几节    课程              地点    性质    状态\n\n");
	while (ap != NULL) {
		printf(" %02d    %-14s %-8s %04u-%02u-%02u   第%d节   %-18s %-8s ", ap->X, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
		if (ap->type == Late)
			printf("迟到   ");
		else if (ap->type == Absent)
			printf("缺席   ");
		else
			printf("请假   ");
		if (ap->state == No)
			printf("\33[31m未确认\33[0m\n");
		else
			printf("\33[32m已确认\33[0m\n");
		ap = ap->next;
	}
	printf("\n请输入要修改的考勤信息编号(输入0可返回菜单界面)：");
	scanf("%d", &n);
	if (n == 0) //返回菜单界面
		return;
	else if (n<1 || n>amount) //编号输入错误
		printf("\a\n\n\t\t\t                            编号输入错误！\n");
	else { //修改指定编号考勤信息
		printf("\n编号       学号       姓名        日期      第几节    课程              地点    性质    状态\n\n");
		ap = attendanceHead->next;
		while (ap != NULL) {
			if (ap->X == n) {
				printf(" %02d    %-14s %-8s %04u-%02u-%02u   第%d节   %-18s %-8s ", ap->X, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
				if (ap->type == Late)
					printf("迟到   ");
				else if (ap->type == Absent)
					printf("缺席   ");
				else
					printf("请假   ");
				if (ap->state == No)
					printf("\33[31m未确认\33[0m\n\n");
				else
					printf("\33[32m已确认\33[0m\n\n");
				break;
			}
			ap = ap->next;
		}
		printf("\t\t\t                           请选择修改类型\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           1.修改单个参数\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           2.修改整条考勤\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           3.  取    消\n");
		printf("\t\t\t                        --------------------\n");
		DisplayCursor(0); //隐藏光标
		while (1) {
			choice = _getch();
			if (choice == '1' || choice == '2' || choice == '3')
				break;
		}
		DisplayCursor(1); //显示光标
		if (choice == '3') //取消，返回菜单界面
			return;
		else if (choice == '2') { //修改整条考勤
			printf("\t\t\t请输入新的[学号]：");
			scanf("%s", num);
			printf("\t\t\t请输入新的[姓名]：");
			scanf("%s", name);
			while (sp != NULL) {
				if (strcmp(sp->num, num) == 0 && strcmp(sp->name, name) == 0) {
					flag1 = 1;
					break;
				}
				sp = sp->next;
			}
			if (flag1) { //若新的学号和姓名存在且配对
				if (strcmp(ap->num, num) != 0) { //若修改了该考勤信息的学号和姓名
					flag2 = 1;
					strcpy(num0, ap->num); //记下修改前的学号
					strcpy(ap->num, num);
					strcpy(ap->name, name);
				}
			}
			else { //若新的学号和姓名不存在或不配对
				printf("\a\n\n\t\t\t                        学号或姓名输入错误！\n\n");
				system("pause");
				return;
			}
			printf("\t\t\t请输入新的[日期](格式：xxxx-xx-xx)：");
			scanf("%u-%u-%u", &year, &month, &ap->data.tm_mday);
			ap->data.tm_year = year - 1900;
			ap->data.tm_mon = month - 1;
			printf("\t\t\t请输入新的[第几节]：");
			scanf("%d", &ap->n);
			printf("\t\t\t请输入新的[课程]：");
			scanf("%s", ap->subject);
			printf("\t\t\t请输入新的[地点]：");
			scanf("%s", ap->locale);
			DisplayCursor(0); //隐藏光标
			printf("\t\t\t请选择新的[性质]：1.迟到  2.缺席  3.请假\n");
			while (1) {
				choice = _getch();
				if (choice == '1') {
					ap->type = Late;
					printf("\33[1A\t\t\t请选择新的[性质]：迟到                   \n");
				}
				else if (choice == '2') {
					ap->type = Absent;
					printf("\33[1A\t\t\t请选择新的[性质]：缺席                   \n");
				}
				else if (choice == '3') {
					ap->type = Leave;
					printf("\33[1A\t\t\t请选择新的[性质]：请假                   \n");
				}
				else
					continue;
				break;
			}
			printf("\t\t\t请选择新的[状态]：1.未确认  2.已确认\n");
			while (1) {
				choice = _getch();
				if (choice == '1') {
					ap->state = No;
					printf("\33[1A\t\t\t请选择新的[状态]：未确认              \n");
				}
				else if (choice == '2') {
					ap->state = Yes;
					printf("\33[1A\t\t\t请选择新的[状态]：已确认              \n");
				}
				else
					continue;
				break;
			}
		}
		else { //修改单个参数
			printf("\33[8A\t\t\t                         请选择要修改的参数\n");
			printf("\t\t\t                        --------------------\n");
			printf("\t\t\t                            1.学号和姓名    \n");
			printf("\t\t\t                        --------------------\n");
			printf("\t\t\t                            2.日期          \n");
			printf("\t\t\t                        --------------------\n");
			printf("\t\t\t                            3.第几节        \n");
			printf("\t\t\t                        --------------------\n");
			printf("\t\t\t                            4.课程\n");
			printf("\t\t\t                        --------------------\n");
			printf("\t\t\t                            5.地点\n");
			printf("\t\t\t                        --------------------\n");
			printf("\t\t\t                            6.性质\n");
			printf("\t\t\t                        --------------------\n");
			printf("\t\t\t                            7.状态\n");
			printf("\t\t\t                        --------------------\n");
			DisplayCursor(0); //隐藏光标
			while (1) {
				choice = _getch();
				if (choice >= '1' && choice <= '7')
					break;
			}
			DisplayCursor(1); //显示光标
			switch (choice) {
			case '1':
				printf("\t\t\t请输入新的[学号]：");
				scanf("%s", num);
				printf("\t\t\t请输入新的[姓名]：");
				scanf("%s", name);
				while (sp != NULL) {
					if (strcmp(sp->num, num) == 0 && strcmp(sp->name, name) == 0) {
						flag1 = 1;
						break;
					}
					sp = sp->next;
				}
				if (flag1) { //若新的学号和姓名存在且配对
					if (strcmp(ap->num, num) != 0) { //若修改了该考勤信息的学号和姓名
						flag2 = 1;
						strcpy(num0, ap->num); //记下修改前的学号
						strcpy(ap->num, num);
						strcpy(ap->name, name);
					}
				}
				else { //若新的学号和姓名不存在或不配对
					printf("\a\n\n\t\t\t                        学号或姓名输入错误！\n\n");
					system("pause");
					return;
				}
				break;
			case '2':
				printf("\t\t\t请输入新的[日期](格式：xxxx-xx-xx)：");
				scanf("%u-%u-%u", &year, &month, &ap->data.tm_mday);
				ap->data.tm_year = year - 1900;
				ap->data.tm_mon = month - 1;
				break;
			case '3':
				printf("\t\t\t请输入新的[第几节]：");
				scanf("%d", &ap->n);
				break;
			case '4':
				printf("\t\t\t请输入新的[课程]：");
				scanf("%s", ap->subject);
				break;
			case '5':
				printf("\t\t\t请输入新的[地点]：");
				scanf("%s", ap->locale);
				break;
			case '6':
				printf("\t\t\t请选择新的[性质]：1.迟到  2.缺席  3.请假\n");
				DisplayCursor(0); //隐藏光标
				while (1) {
					choice = _getch();
					if (choice == '1') {
						ap->type = Late;
						printf("\33[1A\t\t\t请选择新的[性质]：迟到                   \n");
					}
					else if (choice == '2') {
						ap->type = Absent;
						printf("\33[1A\t\t\t请选择新的[性质]：缺席                   \n");
					}
					else if (choice == '3') {
						ap->type = Leave;
						printf("\33[1A\t\t\t请选择新的[性质]：请假                   \n");
					}
					else
						continue;
					break;
				}
				break;
			case '7':
				printf("\t\t\t请选择新的[状态]：1.未确认  2.已确认\n");
				DisplayCursor(0); //隐藏光标
				while (1) {
					choice = _getch();
					if (choice == '1') {
						ap->state = No;
						printf("\33[1A\t\t\t请选择新的[状态]：未确认              \n");
					}
					else if (choice == '2') {
						ap->state = Yes;
						printf("\33[1A\t\t\t请选择新的[状态]：已确认              \n");
					}
					else
						continue;
					break;
				}
			}
		}
		printf("\n编号       学号       姓名        日期      第几节    课程              地点    性质    状态\n\n");
		printf(" %02d    %-14s %-8s %04u-%02u-%02u   第%d节   %-18s %-8s ", ap->X, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
		if (ap->type == Late)
			printf("迟到   ");
		else if (ap->type == Absent)
			printf("缺席   ");
		else
			printf("请假   ");
		if (ap->state == No)
			printf("\33[31m未确认\33[0m\n");
		else
			printf("\33[32m已确认\33[0m\n");
		WriteAttendanceInfo(&attendanceHead);
		if (flag2) { //若成功修改了考勤信息的学号和姓名，则进行学生的缺勤次数修改
			sp->times++;
			sp = studentHead->next;
			while (sp != NULL) {
				if (strcmp(num0, sp->num) == 0) {
					sp->times--;
					break;
				}
				sp = sp->next;
			}
			WriteStudentInfo(&studentHead);
		}
		printf("\n\n\t\t\t                    成功修改编号为\33[36m%02d\33[0m的考勤信息！\n", n);
	}
	printf("\n");
	DisplayCursor(1); //显示光标
	system("pause");
}

//统计缺勤人员
void Statistic() {
	int i, j, amount = 0; //缺勤学生总数
	char choice;
	struct student stu[50];
	spointer sp = studentHead->next;
	apointer ap = attendanceHead->next;
	Title();
	printf("\t\t\t                            统计缺勤人员\n");
	printf("\t\t\t                        --------------------\n");
	printf("\t\t\t                            1.按条件统计\n");
	printf("\t\t\t                        --------------------\n");
	printf("\t\t\t                            2.统计全部\n");
	printf("\t\t\t                        --------------------\n");
	printf("\t\t\t                            3.取消\n");
	printf("\t\t\t                        --------------------\n");
	DisplayCursor(0); //隐藏光标
	while (1) {
		choice = _getch();
		if (choice == '1' || choice == '2' || choice == '3')
			break;
	}
	if (choice == '3') //取消，返回菜单界面
		return;
	else if (choice == '2') { //统计全部缺勤人员
		Title();
		printf("\t\t\t                            统计缺勤人员\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                              统计全部\n\n");
		while (sp != NULL) { //记录有缺勤记录的学生到stu数组中
			if (sp->times != 0) {
				strcpy(stu[amount].name, sp->name);
				strcpy(stu[amount].num, sp->num);
				stu[amount].times = sp->times;
				amount++;
			}
			sp = sp->next;
		}
		if (amount == 0)
			printf("共有\33[36m0\33[0m位学生有缺勤(非出席)记录！\n");
		else {
			QuickSort(0, stu, 0, amount);
			printf("共有\33[36m%d\33[0m位学生有缺勤(非出席)记录，具体如下(结果已按缺勤次数降序排序)：\n\n", amount);
			printf("\t\t\t             ┏━━━━━━━━━━━┳━━━━━━━━━━━━━━━┳━━━━━━━━━━━┓\n");
			printf("\t\t\t             ┃    姓名   ┃      学号     ┃  缺勤次数 ┃\n");
			for (i = 0, j = 13; i < amount; i++, j += 2) {
				printf("\t\t\t             ┣━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━┫\n");
				printf("\t\t\t             ┃           ┃               ┃           ┃\n");
				Goto_xy(42, j);
				printf("%s", stu[i].name);
				Goto_xy(52, j);
				printf("%s", stu[i].num);
				Goto_xy(70, j);
				printf("%d次\n", stu[i].times);
			}
			printf("\t\t\t             ┗━━━━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━━━━┛\n");
		}
	}
	else { //按条件统计缺勤人员
		enum Type type;
		enum State state;
		char data[11], n[3], subject[25], locale[8], type0[5], state0[7], str[5];
		int flag = 1;
		Title();
		printf("\t\t\t                            统计缺勤人员\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                             按条件统计\n\n");
		printf("请输入统计参数(未输入的参数将默认取所有符合项)：\n");
		printf("注：日期格式：xxxx-xx-xx，性质：迟到/缺勤/请假，状态：未确认/已确认\n");
		printf("\t\t   ┏━━━━━━━━━━━┳━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━┳━━━━━━━┳━━━━━━━━━┓\n");
		printf("\t\t   ┃    日期   ┃ 第几节┃            课程           ┃   地点  ┃  性质 ┃   状态  ┃\n");
		printf("\t\t   ┣━━━━━━━━━━━╋━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━╋━━━━━━━╋━━━━━━━━━┫\n");
		printf("\t\t   ┃           ┃       ┃                           ┃         ┃       ┃         ┃\n");
		printf("\t\t   ┗━━━━━━━━━━━┻━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━┻━━━━━━━━━┛\n");
		DisplayCursor(1); //显示光标
		rewind(stdin); //清空键盘缓冲区
		Goto_xy(21, 13); gets_s(data);
		Goto_xy(35, 13); gets_s(n);
		Goto_xy(45, 13); gets_s(subject);
		Goto_xy(70, 13); gets_s(locale);
		Goto_xy(80, 13); gets_s(type0);
		Goto_xy(88, 13); gets_s(state0);
		while (ap != NULL) { //查找符合条件的考勤信息，并获取其学生信息
			flag = 1;
			if (strcmp(data, "\0") != 0) {
				strncpy(str, data, 4);
				flag = flag && (ap->data.tm_year + 1900 == atof(str));
				str[0] = data[5]; str[1] = data[6]; str[2] = '\0';
				flag = flag && (ap->data.tm_mon + 1 == atof(str));
				str[0] = data[8]; str[1] = data[9]; str[2] = '\0';
				flag = flag && (ap->data.tm_mday == atof(str));
			}
			if (strcmp(n, "\0") != 0)
				flag = flag && (ap->n == atof(n));
			if (strcmp(subject, "\0") != 0)
				flag = flag && !strcmp(ap->subject, subject);
			if (strcmp(locale, "\0") != 0)
				flag = flag && !strcmp(ap->locale, locale);
			if (strcmp(type0, "\0") != 0) {
				if (strcmp(type0, "迟到") == 0)
					type = Late;
				if (strcmp(type0, "缺席") == 0)
					type = Absent;
				if (strcmp(type0, "请假") == 0)
					type = Leave;
				flag = flag && (ap->type == type);
			}
			if (strcmp(state0, "\0") != 0) {
				if (strcmp(state0, "未确认") == 0)
					state = No;
				if (strcmp(state0, "已确认") == 0)
					state = Yes;
				flag = flag && (ap->state == state);
			}
			if (flag) {
				flag = 0; //stu数组中是否有该缺勤学生信息
				for (i = 0; i < amount; i++) {
					if (strcmp(ap->num, stu[i].num) == 0) {
						flag = 1;
						break;
					}
				}
				if (!flag) { //若无，则添加该学生信息至stu数组
					strcpy(stu[amount].name, ap->name);
					strcpy(stu[amount].num, ap->num);
					amount++;
				}
			}
			ap = ap->next;
		}
		if (amount == 0)
			printf("\n\n共有\33[36m0\33[0m位学生符合以上缺勤记录！\n");
		else {
			QuickSort(1, stu, 0, amount);
			printf("\n\n共有\33[36m%d\33[0m位学生符合以上缺勤记录，具体如下(结果已按学号升序排序)：\n\n", amount);
			printf("\t\t\t                   ┏━━━━━━━━━━━┳━━━━━━━━━━━━━━━┓\n");
			printf("\t\t\t                   ┃    姓名   ┃      学号     ┃\n");
			for (i = 0, j = 21; i < amount; i++, j += 2) {
				printf("\t\t\t                   ┣━━━━━━━━━━━╋━━━━━━━━━━━━━━━┫\n");
				printf("\t\t\t                   ┃           ┃               ┃\n");
				Goto_xy(48, j);
				printf("%s", stu[i].name);
				Goto_xy(58, j);
				printf("%s\n", stu[i].num);
			}
			printf("\t\t\t                   ┗━━━━━━━━━━━┻━━━━━━━━━━━━━━━┛\n");
		}
	}
	printf("\n");
	DisplayCursor(1); //显示光标
	system("pause");
}

//超级管理权限，暂时无实用功能
void Super() {
	while (1) {
		char password[20], choice;
		Title();
		printf("\t\t\t                            超级管理权限\n");
		printf("\t\t\t                        --------------------\n\n\n");
		printf("\t\t\t                  ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("\t\t\t                  ┃ 密码：                      ┃\n");
		printf("\t\t\t                  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
		DisplayCursor(1); //显示光标
		Goto_xy(50, 9);
		InputPassword(password);
		if (strcmp("ADMIN", password) == 0) { //密码正确
			Title();
			printf("\t\t\t                            超级管理权限\n");
			printf("\t\t\t                        --------------------\n\n\n");
			printf("\33[3B\33[31m");
			printf("\t    ■■      ■       ■■       ■■■■■   ■      ■   ■■■■■   ■■      ■       ■■■\n");
			printf("\t    ■ ■     ■     ■    ■         ■       ■      ■       ■       ■ ■     ■     ■      ■\n");
			printf("\t    ■  ■    ■    ■      ■        ■       ■      ■       ■       ■  ■    ■    ■\n");
			printf("\t    ■   ■   ■   ■        ■       ■       ■■■■■       ■       ■   ■   ■   ■\n");
			printf("\t    ■    ■  ■    ■      ■        ■       ■      ■       ■       ■    ■  ■    ■     ■■\n");
			printf("\t    ■     ■ ■     ■    ■         ■       ■      ■       ■       ■     ■ ■     ■      ■\n");
			printf("\t    ■      ■■       ■■           ■       ■      ■   ■■■■■   ■      ■■       ■■■■\n");
			printf("\33[11B\33[0m");
			system("pause");
			break;
		}
		else { //密码错误
			printf("\a\n\n\n\t\t\t                       密码错误，请重新输入！\n\n");
			printf("\t\t\t                          1.确定    2.取消\n");
			DisplayCursor(0); //隐藏光标
			choice = _getch();
			if (choice != '1' && choice != '\r')
				break;
		}
	}
}

//初始化系统
void Init() {
	Title();
	printf("\t\t\t                             初始化系统\n");
	printf("\t\t\t                        --------------------\n\n");
	char choice;
	printf("\t\t\t           是否确定初始化系统，将系统信息还原至最初信息？\n\n");
	printf("\t\t\t                          1.确定    2.取消\n");
	DisplayCursor(0); //隐藏光标
	choice = _getch();
	if (choice == '1' || choice == '\r') {
		Destroy(&studentHead, &attendanceHead); //销毁整个学生链表和考勤链表
		studentHead = NULL;
		studentRear = NULL;
		attendanceHead = NULL;
		attendanceRear = NULL;
		ReadStudentInfo(&studentHead, &studentRear, 0); //建立初始学生信息链表
		ReadAttendanceInfo(&attendanceHead, &attendanceRear, 0); //建立初始考勤信息链表
		WriteStudentInfo(&studentHead);
		WriteAttendanceInfo(&attendanceHead);
		printf("\n\n\t\t\t                          系统初始化成功！\n\n");
		DisplayCursor(1); //显示光标
		system("pause");
	}
}

//查看个人信息
void UserInfo(spointer sp) {
	Title();
	printf("\t\t\t                            查看个人信息\n");
	printf("\t\t\t                        --------------------\n");
	printf("\t\t\t                ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t\t                ┃ 姓    名：                      ┃\n");
	printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t\t                ┃ 性    别：                      ┃\n");
	printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t\t                ┃ 年    级：                      ┃\n");
	printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t\t                ┃ 班    级：                      ┃\n");
	printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t\t                ┃ 学    号：                      ┃\n");
	printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t\t                ┃ 手    机：                      ┃\n");
	printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t\t                ┃ 身 份 证：                      ┃\n");
	printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t\t                ┃ 缺勤次数：                      ┃\n");
	printf("\t\t\t                ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	apointer ap = attendanceHead->next;
	int i = 1;
	Goto_xy(52, 7);
	printf("%s", sp->name);
	Goto_xy(52, 9);
	if (sp->sex == Man)
		printf("男");
	else if (sp->sex == Woman)
		printf("女");
	else
		printf("未知");
	Goto_xy(52, 11);
	printf("%s", sp->grade);
	Goto_xy(52, 13);
	printf("%s", sp->clas);
	Goto_xy(52, 15);
	printf("%s", sp->num);
	Goto_xy(52, 17);
	printf("%s", sp->phone);
	Goto_xy(52, 19);
	printf("%s", sp->idCard);
	Goto_xy(52, 21);
	printf("%d次", sp->times);
	printf("\n\n");
	if (sp->times != 0) { //个人考勤信息条数不为0
		printf("您共有\33[36m%d\33[0m条考勤信息，具体如下：\n\n", sp->times);
		printf("序号       学号       姓名        日期      第几节    课程              地点    性质    状态\n\n");
		while (ap != NULL) {
			if (strcmp(sp->num, ap->num) == 0) {
				printf(" %02d    %-14s %-8s %04u-%02u-%02u   第%d节   %-18s %-8s ", i, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
				if (ap->type == Late)
					printf("迟到   ");
				else if (ap->type == Absent)
					printf("缺席   ");
				else
					printf("请假   ");
				if (ap->state == No)
					printf("\33[31m未确认\33[0m\n");
				else
					printf("\33[32m已确认\33[0m\n");
				i++;
			}
			ap = ap->next;
		}
	}
	else //个人考勤信息条数为0
		printf("您共有\33[36m0\33[0m条考勤信息！\n");
	printf("\n");
	DisplayCursor(1); //显示光标
	system("pause");
}

//确认个人考勤
void Confirm(spointer sp) {
	Title();
	printf("\t\t\t                            确认个人考勤\n");
	printf("\t\t\t                        --------------------\n");
	int amount = 0, n, flag = 0;
	apointer ap = attendanceHead->next;
	DisplayCursor(1); //显示光标
	while (ap != NULL) {
		if (strcmp(sp->num, ap->num) == 0 && ap->state == No)
			amount++;
		ap = ap->next;
	}
	if (amount == 0) //无未确认的个人考勤信息
		printf("您共有\33[36m0\33[0m条未确认的考勤信息！\n");
	else { //有未确认的个人考勤信息
		printf("您共有\33[36m%d\33[0m条未确认的考勤信息，具体如下：\n\n", amount);
		printf("编号       学号       姓名        日期      第几节    课程              地点    性质    状态\n\n");
		ap = attendanceHead->next;
		while (ap != NULL) {
			if (strcmp(sp->num, ap->num) == 0 && ap->state == No) {
				printf(" %02d    %-14s %-8s %04u-%02u-%02u   第%d节   %-18s %-8s ", ap->X, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
				if (ap->type == Late)
					printf("迟到   ");
				else if (ap->type == Absent)
					printf("缺席   ");
				else
					printf("请假   ");
				printf("\33[31m未确认\33[0m\n");
			}
			ap = ap->next;
		}
		printf("\n请输入要确认的考勤信息编号(输入0可确认全部，输入-1可返回菜单界面)：");
		scanf("%d", &n);
		if (n == -1) //返回菜单界面
			return;
		else if (n == 0) { //确认全部个人考勤信息
			ap = attendanceHead->next;
			while (ap != NULL) {
				if (strcmp(sp->num, ap->num) == 0 && ap->state == No)
					ap->state = Yes;
				ap = ap->next;
			}
			WriteAttendanceInfo(&attendanceHead);
			printf("\n\n\t\t\t                     成功确认以上\33[36m%d\33[0m条考勤信息！\n", amount);
		}
		else { //确认指定编号考勤信息
			ap = attendanceHead->next;
			while (ap != NULL) {
				if (strcmp(sp->num, ap->num) == 0 && ap->X == n && ap->state == No) {
					ap->state = Yes;
					flag = 1;
					break;
				}
				ap = ap->next;
			}
			if (flag) { //成功确认指定编号考勤信息
				WriteAttendanceInfo(&attendanceHead);
				printf("\n\n\t\t\t                    成功确认编号为\33[36m%02d\33[0m的考勤信息！\n", n);
			}
			else
				printf("\a\n\n\t\t\t                            编号输入错误！\n");
		}
	}
	printf("\n");
	system("pause");
}

//修改密码
void ChangePassword(spointer sp) {
	while (1) {
		Title();
		printf("\t\t\t                              修改密码\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("\t\t\t                ┃ 旧 密 码：                      ┃\n");
		printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
		printf("\t\t\t                ┃ 新 密 码：                      ┃\n");
		printf("\t\t\t                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
		printf("\t\t\t                ┃ 确认密码：                      ┃\n");
		printf("\t\t\t                ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
		char old[20], neww1[20], neww2[20], choice;
		DisplayCursor(1); //显示光标
		Goto_xy(52, 7);
		InputPassword(old);
		Goto_xy(52, 9);
		InputPassword(neww1);
		Goto_xy(52, 11);
		InputPassword(neww2);
		if (strcmp(sp->password, old) != 0) { //旧密码错误
			MessageBeep(MB_ICONHAND);
			printf("\n\n\n\t\t\t                    旧密码错误，请重新修改密码！\n\n");
			printf("\t\t\t                          1.确定    2.取消\n");
			DisplayCursor(0); //隐藏光标
			choice = _getch();
			if (choice == '1' || choice == '\r')
				continue;
		}
		else if (strcmp(neww1, neww2) != 0) { //两次密码不相同
			MessageBeep(MB_ICONHAND);
			printf("\n\n\n\t\t\t                  两次密码不相同，请重新修改密码！\n\n");
			printf("\t\t\t                          1.确定    2.取消\n");
			DisplayCursor(0); //隐藏光标
			choice = _getch();
			if (choice == '1' || choice == '\r')
				continue;
		}
		else { //旧密码正确，且两次密码相同
			printf("\n\n\n\t\t\t                         是否确定修改密码？\n\n");
			printf("\t\t\t                          1.确定    2.取消\n");
			DisplayCursor(0); //隐藏光标
			choice = _getch();
			if (choice == '1' || choice == '\r') {
				strcpy(sp->password, neww1);
				WriteStudentInfo(&studentHead);
				printf("\n\n\t\t\t                    密码修改成功，请牢记新密码！\n\n");
				DisplayCursor(1); //显示光标
				system("pause");
			}
		}
		break;
	}
}