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

//显示或隐藏光标
void DisplayCursor(int flag) {
	CONSOLE_CURSOR_INFO cursor;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (flag) {
		cursor.dwSize = 25;
		cursor.bVisible = 1;
	}
	else {
		cursor.dwSize = 25;
		cursor.bVisible = 0;
	}
	SetConsoleCursorInfo(hOut, &cursor);
}

//定位光标位置到指定坐标
void Goto_xy(short x, short y) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { x,y };
    SetConsoleCursorPosition(hOut, pos);
}

//输入密码
void InputPassword(char* password) {
	int i = 0;
	char ch;
	while ((ch = _getch()) != '\r') { //输入回车则结束循环
		if (ch != '\b') { //若输入非BACKSPACE键，则存储1位密码并输出*号
			*(password + i) = ch;
			i++;
			printf("*");
			fflush(stdin); //清空输入缓冲区
		}
		if (ch == '\b' && i != 0) { //若输入BACKSPACE键且密码长度为非0，则回删
			i--;
			printf("\b \b");
		}
	}
	*(password + i) = '\0'; //字符串结尾需添加\0
	fflush(stdin);
}

//从文件读取学生信息，建立学生信息链表
void ReadStudentInfo(slklist* studentHead, spointer* studentRear, int flag) {
	FILE* fp;
	spointer sp; //工作指针变量
	if (flag) {
		if ((fp = fopen("学生信息.txt", "rb")) == NULL) { //打开文件
			printf("学生信息文件打开出错！\n");
			return;
		}
	}
	else {
		if ((fp = fopen("初始学生信息.txt", "rb")) == NULL) { //打开文件
			printf("初始学生信息文件打开出错！\n");
			return;
		}
	}
	//读取文件，获取学生信息，建立链表
	while (!feof(fp)) { //文件未读取到末尾
		if ((sp = (spointer)malloc(sizeof(struct studentInfo_node))) == NULL) {
			printf("内存申请出错！\n");
			fclose(fp);
			return;
		}
		if (fread(sp, sizeof(struct studentInfo_node), 1, fp) != 1) { //读到末尾或者出错,跳出循环
			free(sp);
			break;
		}
		if (*studentHead == NULL)
			*studentHead = *studentRear = sp; //头指针指向头结点，尾指针初值指向头结点
		else {
			(*studentRear)->next = sp;
			*studentRear = sp;
		}
	}
	fclose(fp); //关闭文件
}

//将学生信息链表写入文件
void WriteStudentInfo(slklist* studentHead) {
	FILE* fp;
	spointer sp = *studentHead;
	if ((fp = fopen("学生信息.txt", "wb")) == NULL) {
		printf("学生信息文件打开出错！\n");
		return;
	}
	while (sp != NULL) {
		if (fwrite(sp, sizeof(struct studentInfo_node), 1, fp) != 1) {
			printf("文件写入出错！\n");
			fclose(fp);
			return;
		}
		sp = sp->next;
	}
	fclose(fp);//关闭文件
}

//从文件读取考勤信息，建立考勤信息链表
void ReadAttendanceInfo(alklist* attendanceHead, apointer* attendanceRear, int flag) {
	FILE* fp;
	apointer ap; //工作指针变量
	if (flag) {
		if ((fp = fopen("考勤信息.txt", "rb")) == NULL) { //打开文件
			printf("考勤信息文件打开出错！\n");
			return;
		}
	}
	else {
		if ((fp = fopen("初始考勤信息.txt", "rb")) == NULL) { //打开文件
			printf("初始考勤信息文件打开出错！\n");
			return;
		}
	}
	//读取文件，获取考勤信息，建立链表
	while (!feof(fp)) { //文件未读取到末尾
		if ((ap = (apointer)malloc(sizeof(struct attendanceInfo_node))) == NULL) {
			printf("内存申请出错！\n");
			fclose(fp);
			return;
		}
		if (fread(ap, sizeof(struct attendanceInfo_node), 1, fp) != 1) { //读到末尾或者出错,跳出循环
			free(ap);
			break;
		}
		if (*attendanceHead == NULL)
			*attendanceHead = *attendanceRear = ap; //头指针指向头结点，尾指针初值指向头结点
		else {
			(*attendanceRear)->next = ap;
			*attendanceRear = ap;
		}
	}
	fclose(fp); //关闭文件
}

//将考勤信息链表写入文件
void WriteAttendanceInfo(alklist* attendanceHead) {
	FILE* fp;
	apointer ap = *attendanceHead;
	if ((fp = fopen("考勤信息.txt", "wb")) == NULL) {
		printf("考勤信息文件打开出错！\n");
		return;
	}
	while (ap != NULL) {
		if (fwrite(ap, sizeof(struct attendanceInfo_node), 1, fp) != 1) {
			printf("文件写入出错！\n");
			fclose(fp);
			return;
		}
		ap = ap->next;
	}
	fclose(fp);//关闭文件
}

//销毁链表
void Destroy(slklist* studentHead, alklist* attendanceHead) {
	spointer sp, sq;
	sp = *studentHead; //从头结点开始
	while (sp != NULL) {
		sq = sp->next; //下一个结点
		free(sp);
		sp = sq;
	}
	apointer ap, aq;
	ap = *attendanceHead; //从头结点开始
	while (ap != NULL) {
		aq = ap->next; //下一个结点
		free(ap);
		ap = aq;
	}
}

//快速排序
void QuickSort(int flag, struct student stu[], int left, int right) {
	int i, j;
	struct student t;
	if (left > right)
		return;
	i = left;
	j = right;
	while (i != j) {
		if (flag) { //按学号升序排序
			while (strcmp(stu[j].num, stu[left].num) >= 0 && i < j) //先从右往左找
				j--;
			while (strcmp(stu[i].num, stu[left].num) <= 0 && i < j) //再从左往右找
				i++;
		}
		else { //按缺勤次数降序排序
			while (stu[j].times <= stu[left].times && i < j) //先从右往左找
				j--;
			while (stu[i].times >= stu[left].times && i < j) //再从左往右找
				i++;
		}
		if (i < j) { //当i和j没有相遇时，交换两个数在数组中的位置
			t = stu[i];
			stu[i] = stu[j];
			stu[j] = t;
		}
	}
	//基准数归位
	t = stu[left];
	stu[left] = stu[i];
	stu[i] = t;
	QuickSort(flag, stu, left, i - 1); //继续处理左边的
	QuickSort(flag, stu, i + 1, right); //继续处理右边的
}