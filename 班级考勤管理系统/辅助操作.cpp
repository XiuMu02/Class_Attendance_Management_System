#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#pragma warning(disable:4996)

enum Sex {                                    //�Ա�
	Man, Woman, Unknow                        //�У�Ů��δ֪
};
enum Type {                                   //ȱ������
	Late, Absent, Leave                       //�ٵ���ȱϯ�����
};
enum State {                                  //������Ϣ״̬
	No, Yes                                   //δȷ�ϣ���ȷ��
};
typedef struct attendanceInfo_node* apointer; //������Ϣ���ָ������
struct attendanceInfo_node {                  //������Ϣ���ṹ
	int X;                                    //��ţ����������е����
	char num[15];                             //ѧ��
	char name[10];                            //����
	tm data;                                  //����
	int n;                                    //�ڼ���
	char subject[25];                         //�γ�
	char locale[8];                           //�ص�
	enum Type type;                           //����
	enum State state;                         //״̬
	apointer next;                            //������Ϣ���ָ����
};
typedef apointer alklist;                     //������Ϣ���������ͣ���ͷָ������
typedef struct studentInfo_node* spointer;    //ѧ����Ϣ���ָ������
struct studentInfo_node {                     //ѧ����Ϣ���ṹ
	int X;                                    //��ţ����������е����
	char name[10];                            //����
	enum Sex sex;                             //�Ա�
	char grade[8];                            //�꼶
	char clas[20];                            //�༶
	char num[15];                             //ѧ��
	char password[20];                        //����
	char phone[15];                           //�ֻ�
	char idCard[20];                          //���֤
	int times;                                //ȱ�ڴ���(�ǳ�ϯ����)
	spointer next;                            //ѧ����Ϣ���ָ����
};
typedef spointer slklist;                     //ѧ����Ϣ���������ͣ���ͷָ������

struct student {                              //��ʱ��ѧ��������Ϣ
	char name[10];                            //����
	char num[15];                             //ѧ��
	int times;                                //ȱ�ڴ���(�ǳ�ϯ����)
};

//��ʾ�����ع��
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

//��λ���λ�õ�ָ������
void Goto_xy(short x, short y) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { x,y };
    SetConsoleCursorPosition(hOut, pos);
}

//��������
void InputPassword(char* password) {
	int i = 0;
	char ch;
	while ((ch = _getch()) != '\r') { //����س������ѭ��
		if (ch != '\b') { //�������BACKSPACE������洢1λ���벢���*��
			*(password + i) = ch;
			i++;
			printf("*");
			fflush(stdin); //������뻺����
		}
		if (ch == '\b' && i != 0) { //������BACKSPACE�������볤��Ϊ��0�����ɾ
			i--;
			printf("\b \b");
		}
	}
	*(password + i) = '\0'; //�ַ�����β�����\0
	fflush(stdin);
}

//���ļ���ȡѧ����Ϣ������ѧ����Ϣ����
void ReadStudentInfo(slklist* studentHead, spointer* studentRear, int flag) {
	FILE* fp;
	spointer sp; //����ָ�����
	if (flag) {
		if ((fp = fopen("ѧ����Ϣ.txt", "rb")) == NULL) { //���ļ�
			printf("ѧ����Ϣ�ļ��򿪳���\n");
			return;
		}
	}
	else {
		if ((fp = fopen("��ʼѧ����Ϣ.txt", "rb")) == NULL) { //���ļ�
			printf("��ʼѧ����Ϣ�ļ��򿪳���\n");
			return;
		}
	}
	//��ȡ�ļ�����ȡѧ����Ϣ����������
	while (!feof(fp)) { //�ļ�δ��ȡ��ĩβ
		if ((sp = (spointer)malloc(sizeof(struct studentInfo_node))) == NULL) {
			printf("�ڴ��������\n");
			fclose(fp);
			return;
		}
		if (fread(sp, sizeof(struct studentInfo_node), 1, fp) != 1) { //����ĩβ���߳���,����ѭ��
			free(sp);
			break;
		}
		if (*studentHead == NULL)
			*studentHead = *studentRear = sp; //ͷָ��ָ��ͷ��㣬βָ���ֵָ��ͷ���
		else {
			(*studentRear)->next = sp;
			*studentRear = sp;
		}
	}
	fclose(fp); //�ر��ļ�
}

//��ѧ����Ϣ����д���ļ�
void WriteStudentInfo(slklist* studentHead) {
	FILE* fp;
	spointer sp = *studentHead;
	if ((fp = fopen("ѧ����Ϣ.txt", "wb")) == NULL) {
		printf("ѧ����Ϣ�ļ��򿪳���\n");
		return;
	}
	while (sp != NULL) {
		if (fwrite(sp, sizeof(struct studentInfo_node), 1, fp) != 1) {
			printf("�ļ�д�����\n");
			fclose(fp);
			return;
		}
		sp = sp->next;
	}
	fclose(fp);//�ر��ļ�
}

//���ļ���ȡ������Ϣ������������Ϣ����
void ReadAttendanceInfo(alklist* attendanceHead, apointer* attendanceRear, int flag) {
	FILE* fp;
	apointer ap; //����ָ�����
	if (flag) {
		if ((fp = fopen("������Ϣ.txt", "rb")) == NULL) { //���ļ�
			printf("������Ϣ�ļ��򿪳���\n");
			return;
		}
	}
	else {
		if ((fp = fopen("��ʼ������Ϣ.txt", "rb")) == NULL) { //���ļ�
			printf("��ʼ������Ϣ�ļ��򿪳���\n");
			return;
		}
	}
	//��ȡ�ļ�����ȡ������Ϣ����������
	while (!feof(fp)) { //�ļ�δ��ȡ��ĩβ
		if ((ap = (apointer)malloc(sizeof(struct attendanceInfo_node))) == NULL) {
			printf("�ڴ��������\n");
			fclose(fp);
			return;
		}
		if (fread(ap, sizeof(struct attendanceInfo_node), 1, fp) != 1) { //����ĩβ���߳���,����ѭ��
			free(ap);
			break;
		}
		if (*attendanceHead == NULL)
			*attendanceHead = *attendanceRear = ap; //ͷָ��ָ��ͷ��㣬βָ���ֵָ��ͷ���
		else {
			(*attendanceRear)->next = ap;
			*attendanceRear = ap;
		}
	}
	fclose(fp); //�ر��ļ�
}

//��������Ϣ����д���ļ�
void WriteAttendanceInfo(alklist* attendanceHead) {
	FILE* fp;
	apointer ap = *attendanceHead;
	if ((fp = fopen("������Ϣ.txt", "wb")) == NULL) {
		printf("������Ϣ�ļ��򿪳���\n");
		return;
	}
	while (ap != NULL) {
		if (fwrite(ap, sizeof(struct attendanceInfo_node), 1, fp) != 1) {
			printf("�ļ�д�����\n");
			fclose(fp);
			return;
		}
		ap = ap->next;
	}
	fclose(fp);//�ر��ļ�
}

//��������
void Destroy(slklist* studentHead, alklist* attendanceHead) {
	spointer sp, sq;
	sp = *studentHead; //��ͷ��㿪ʼ
	while (sp != NULL) {
		sq = sp->next; //��һ�����
		free(sp);
		sp = sq;
	}
	apointer ap, aq;
	ap = *attendanceHead; //��ͷ��㿪ʼ
	while (ap != NULL) {
		aq = ap->next; //��һ�����
		free(ap);
		ap = aq;
	}
}

//��������
void QuickSort(int flag, struct student stu[], int left, int right) {
	int i, j;
	struct student t;
	if (left > right)
		return;
	i = left;
	j = right;
	while (i != j) {
		if (flag) { //��ѧ����������
			while (strcmp(stu[j].num, stu[left].num) >= 0 && i < j) //�ȴ���������
				j--;
			while (strcmp(stu[i].num, stu[left].num) <= 0 && i < j) //�ٴ���������
				i++;
		}
		else { //��ȱ�ڴ�����������
			while (stu[j].times <= stu[left].times && i < j) //�ȴ���������
				j--;
			while (stu[i].times >= stu[left].times && i < j) //�ٴ���������
				i++;
		}
		if (i < j) { //��i��jû������ʱ�������������������е�λ��
			t = stu[i];
			stu[i] = stu[j];
			stu[j] = t;
		}
	}
	//��׼����λ
	t = stu[left];
	stu[left] = stu[i];
	stu[i] = t;
	QuickSort(flag, stu, left, i - 1); //����������ߵ�
	QuickSort(flag, stu, i + 1, right); //���������ұߵ�
}