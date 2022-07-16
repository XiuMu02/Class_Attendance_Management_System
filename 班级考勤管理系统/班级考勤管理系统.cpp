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

//��Ҫ���ܺ���
void Title(); //���⺯���������������
void Registe(slklist* studentHead, spointer* studentRear); //ע�ắ���������û�ע��
void Login(int flag); //��¼�����������û���¼�͹���Ա��¼
void Help(); //�������������ڲ鿴����ʹ��˵����
void AdminMenu(slklist* studentHead, alklist* attendanceHead, apointer* attendanceRear); //����Ա�˵�������������ʾ�˵���ѡ����
void UserMenu(spointer sp); //�û��˵�������������ʾ�˵���ѡ����
void StudentInfo(); //�鿴ѧ����Ϣ
void Query(); //��ѯ������Ϣ
void Add(); //��ӿ�����Ϣ
void Delete(); //ɾ��������Ϣ
void Modify(); //�޸Ŀ�����Ϣ
void Statistic(); //ͳ��ȱ����Ա
void Super(); //��������Ȩ�ޣ���ʱ��ʵ�ù���
void Init(); //��ʼ��ϵͳ
void UserInfo(spointer sp); //�鿴������Ϣ
void Confirm(spointer sp); //ȷ�ϸ��˿���
void ChangePassword(spointer sp); //�޸�����
//������������
void DisplayCursor(int flag); //��ʾ�����ع��
void Goto_xy(short x, short y); //��λ���λ�õ�ָ������
void InputPassword(char* password); //��������
void ReadStudentInfo(slklist* studentHead, spointer* studentRear, int flag); //���ļ���ȡѧ����Ϣ������ѧ����Ϣ����
void WriteStudentInfo(slklist* studentHead); //��ѧ����Ϣ����д���ļ�
void ReadAttendanceInfo(alklist* attendanceHead, apointer* attendanceRear, int flag); //���ļ���ȡ������Ϣ������������Ϣ����
void WriteAttendanceInfo(alklist* attendanceHead); //��������Ϣ����д���ļ�
void Destroy(slklist* studentHead, alklist* attendanceHead); //��������
void QuickSort(int flag, struct student stu[], int left, int right); //��������

slklist studentHead = NULL; //ѧ����Ϣ����ͷָ��
spointer studentRear = NULL; //ѧ����Ϣ����βָ��
alklist attendanceHead = NULL; //������Ϣ����ͷָ��
apointer attendanceRear = NULL; //������Ϣ����βָ��

//������
int main() {
	char choice;
	ReadStudentInfo(&studentHead, &studentRear, 1); //����ѧ����Ϣ����
	ReadAttendanceInfo(&attendanceHead, &attendanceRear, 1); //����������Ϣ����
	SetConsoleTitle(TEXT("�� �� �� �� �� �� �� ϵ ͳ ��")); //���ÿ���̨����
	do { //��ӭ����
		system("cls");
		printf("\n\t\t\t=====================================================================\n");
		printf("\t\t\t  ===============                                   ===============\n");
		printf("\t\t\t   ��=========== �� ӭ ʹ �� �� �� �� �� �� �� ϵ ͳ ===========��\n");
		printf("\t\t\t  ===============                                   ===============\n");
		printf("\t\t\t=====================================================================\n\n\n\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                             1.�û�ģʽ\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                             2.����ģʽ\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                             3. ��  ��\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                             4.�˳�ϵͳ\n");
		printf("\t\t\t                        --------------------\n");
		DisplayCursor(0); //���ع��
		choice = _getch();
		switch (choice) {
		case '1': //�û�ģʽ
			do { //�û���¼ע��ѡ�����
				system("cls");
				Title();
				printf("\t\t\t                            ���¼��ע��\n");
				printf("\t\t\t                        --------------------\n");
				printf("\t\t\t                               1.��¼\n");
				printf("\t\t\t                        --------------------\n");
				printf("\t\t\t                               2.ע��\n");
				printf("\t\t\t                        --------------------\n");
				printf("\t\t\t                               3.ȡ��\n");
				printf("\t\t\t                        --------------------\n");
				choice = _getch();
				if (choice == '1') { //��¼
					Login(0);
					break;
				}
				else if (choice == '2') { //ע��
					Registe(&studentHead, &studentRear);
					break;
				}
				else if (choice == '3') //ȡ�������ػ�ӭ����
					break;
			} while (1);
			break;
		case '2':Login(1); break; //����ģʽ
		case '3':Help(); break; //����
		case '4':exit(0); //�˳�ϵͳ
		}
	} while (1);
	return 0;
}

//���⺯���������������
void Title() {
	system("cls");
	printf("\n\t\t\t                    �� �� �� �� �� �� �� ϵ ͳ ��\n");
	printf("\t\t\t=====================================================================\n\n");
}

//ע�ắ���������û�ע��
void Registe(slklist* studentHead, spointer* studentRear) {
	while (1) {
		Title();
		printf("\t\t\t                              �û�ע��\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                ����������������������������������������������������������������������\n");
		printf("\t\t\t                �� ��    ����                      ��\n");
		printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
		printf("\t\t\t                �� ��    ��                      ��\n");
		printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
		printf("\t\t\t                �� ��    ����                      ��\n");
		printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
		printf("\t\t\t                �� ��    ����                      ��\n");
		printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
		printf("\t\t\t                �� ѧ    �ţ�                      ��\n");
		printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
		printf("\t\t\t                �� ��    �룺                      ��\n");
		printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
		printf("\t\t\t                �� ȷ�����룺                      ��\n");
		printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
		printf("\t\t\t                �� ��    ����                      ��\n");
		printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
		printf("\t\t\t                �� �� �� ֤��                      ��\n");
		printf("\t\t\t                ����������������������������������������������������������������������\n");
		spointer sp = NULL, sp1 = (*studentHead)->next;
		int exist = 0; //ѧ���Ƿ���ע��
		if ((sp = (spointer)malloc(sizeof(struct studentInfo_node))) == NULL) {
			printf("�ڴ��������\n");
			exit(-1);
		}
		char sexs[10], sex[3], password1[20], choice;
		sp->X = (*studentRear)->X + 1;
		DisplayCursor(1); //��ʾ���
		Goto_xy(52, 7); //���ù��λ��
		scanf("%s", sp->name); //��������
		Goto_xy(52, 9);
		scanf("%s", sexs); //�����Ա�
		strncpy(sex, sexs, 2);
		sex[2] = '\0';
		if (strcmp("��", sex) == 0)
			sp->sex = Man;
		else if (strcmp("Ů", sex) == 0)
			sp->sex = Woman;
		else
			sp->sex = Unknow;
		Goto_xy(52, 11);
		scanf("%s", sp->grade); //�����꼶
		Goto_xy(52, 13);
		scanf("%s", sp->clas); //����༶
		Goto_xy(52, 15);
		scanf("%s", sp->num); //����ѧ��
		while (sp1 != NULL) { //���ѧ���Ƿ��Ѿ�ע��
			if (strcmp(sp1->num, sp->num) == 0) {
				exist = 1;
				break;
			}
			sp1 = sp1->next;
		}
		if (exist) { //ѧ����ע��
			MessageBeep(MB_ICONHAND); //�������󾯱���
			printf("\n\n\n\n\n\n\n\n\n\n\t\t\t                     ��ѧ����ע�ᣬ������ע�ᣡ\n\n");
			printf("\t\t\t                          1.ȷ��    2.ȡ��\n");
			DisplayCursor(0); //���ع��
			choice = _getch();
			if (choice == '1' || choice == '\r') {
				free(sp);
				continue;
			}
			else
				break;
		}
		Goto_xy(52, 17);
		InputPassword(sp->password); //��������
		Goto_xy(52, 19);
		InputPassword(password1); //����ȷ������
		if (strcmp(sp->password, password1) != 0) { //�������벻��ͬ
			MessageBeep(MB_ICONHAND);
			printf("\n\n\n\n\n\n\n\t\t\t                    �������벻��ͬ��������ע�ᣡ\n\n");
			printf("\t\t\t                          1.ȷ��    2.ȡ��\n");
			DisplayCursor(0); //���ع��
			choice = _getch();
			if (choice == '1' || choice == '\r') {
				free(sp);
				continue;
			}
			else
				break;
		}
		Goto_xy(52, 21);
		scanf("%s", sp->phone); //�����ֻ�
		Goto_xy(52, 23);
		scanf("%s", sp->idCard); //�������֤
		sp->times = 0;
		sp->next = NULL;
		printf("\n\n\t\t\t                      �Ƿ���������Ϣ����ע�᣿\n\n");
		printf("\t\t\t                          1.ȷ��    2.ȡ��\n");
		DisplayCursor(0); //���ع��
		choice = _getch();
		if (choice == '1' || choice == '\r') {
			(*studentRear)->next = sp;
			*studentRear = sp;
			WriteStudentInfo(studentHead);
			Title();
			printf("\t\t\t                              ע��ɹ�\n");
			printf("\t\t\t                        --------------------\n\n\n");
			printf("\t\t\t                     \33[31m���μ������˺�(ѧ��)������\33[0m\n\n");
			printf("\t\t\t                      �˺ţ�%s\n", (*studentRear)->num);
			printf("\t\t\t                      ���룺%s\n\n\n\n", (*studentRear)->password);
			DisplayCursor(1); //��ʾ���
			system("pause");
		}
		else
			free(sp);
		break;
	}
}

//��¼�����������û���¼�͹���Ա��¼
void Login(int flag) {
	while (1) {
		Title();
		flag ? printf("\t\t\t                             ����Ա��¼\n") : printf("\t\t\t                              �û���¼\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                    ������������������������������������������������������\n");
		printf("\t\t\t                    �� �˺ţ�                  ��\n");
		printf("\t\t\t                    �ǩ���������������������������������������������������\n");
		printf("\t\t\t                    �� ���룺                  ��\n");
		printf("\t\t\t                    ������������������������������������������������������\n");
		spointer sp = studentHead->next;
		char account[15], password[20];
		char choice;
		int i, j, exist = 0; //exist��ʾ�˺��Ƿ����
		DisplayCursor(1); //��ʾ���
		Goto_xy(52, 7); //���ù��λ��
		scanf("%s", account);
		Goto_xy(52, 9);
		InputPassword(password);
		if (flag) { //����Ա��¼
			if (strcmp("admin", account) == 0 && strcmp("admin", password) == 0) { //��¼�ɹ�
				DisplayCursor(0); //���ع��
				Title();
				printf("\t\t\t                              ��¼�ɹ�\n");
				printf("\t\t\t                        --------------------\n\n\n");
				printf("\t\t\t                      ��ӭʹ�ð༶���ڹ���ϵͳ\n\n");
				printf("\t\t\t                       ���ڽ������Ա�˵�����\n\n");
				printf("\t\t\t                      ����������������������������������������������\n");
				printf("\t\t\t                      ��                     ��\n");
				printf("\t\t\t                      ����������������������������������������������\n");
				Goto_xy(48, 13);
				j = 2500;
				for (i = 1; i <= 10; i++) {
					printf("\33[36m��\33[0m");
					Beep(j, 500);
					j -= 200;
				}
				AdminMenu(&studentHead, &attendanceHead, &attendanceRear);
			}
			else { //��¼ʧ��
				MessageBeep(MB_ICONHAND);
				printf("\n\n\n\t\t\t                    �˺Ż�������������µ�¼��\n\n");
				printf("\t\t\t                          1.ȷ��    2.ȡ��\n");
				DisplayCursor(0); //���ع��
				choice = _getch();
				if (choice == '1' || choice == '\r')
					continue;
				else
					break;
			}
		}
		else { //�û���¼
			while (sp != NULL) {
				if (strcmp(sp->num, account) == 0)
					break;
				sp = sp->next;
			}
			if (sp != NULL && strcmp(sp->num, account) == 0 && strcmp(sp->password, password) == 0) { //��¼�ɹ�
				DisplayCursor(0); //���ع��
				Title();
				printf("\t\t\t                              ��¼�ɹ�\n");
				printf("\t\t\t                        --------------------\n\n\n");
				printf("\t\t\t                      ��ӭʹ�ð༶���ڹ���ϵͳ\n\n");
				printf("\t\t\t                        ���ڽ����û��˵�����\n\n");
				printf("\t\t\t                      ����������������������������������������������\n");
				printf("\t\t\t                      ��                     ��\n");
				printf("\t\t\t                      ����������������������������������������������\n");
				Goto_xy(48, 13);
				j = 500;
				for (i = 1; i <= 10; i++) {
					printf("\33[36m��\33[0m");
					Beep(j, 500);
					j += 200;
				}
				UserMenu(sp);
			}
			else { //��¼ʧ��
				MessageBeep(MB_ICONHAND);
				printf("\n\n\n\t\t\t                    �˺Ż�������������µ�¼��\n\n");
				printf("\t\t\t                          1.ȷ��    2.ȡ��\n");
				DisplayCursor(0); //���ع��
				choice = _getch();
				if (choice == '1' || choice == '\r')
					continue;
				else
					break;
			}
		}
	}
}

//�������������ڲ鿴����ʹ��˵����
void Help() {
	char choice;
	int times = 1;
	system("cls");
	printf("\33[10B"); //�������10��
	printf("\t\t\t       ��      ��     ����������     ��             ����������\n");
	printf("\t\t\t       ��      ��     ��             ��             ��      ��\n");
	printf("\t\t\t       ��      ��     ��             ��             ��      ��\n");
	printf("\t\t\t       ����������     ����������     ��             ����������\n");
	printf("\t\t\t       ��      ��     ��             ��             ��\n");
	printf("\t\t\t       ��      ��     ��             ��             ��\n");
	printf("\t\t\t       ��      ��     ����������     ����������     ��\n");
	while (times <= 2) {
		printf("\33[7A\33[31m");
		printf("\t\t\t       ��      ��     ����������     ��             ����������\n\t\t\t       ��      ��     ��             ��             ��      ��\n\t\t\t       ��      ��     ��             ��             ��      ��\n\t\t\t       ����������     ����������     ��             ����������\n\t\t\t       ��      ��     ��             ��             ��\n\t\t\t       ��      ��     ��             ��             ��\n\t\t\t       ��      ��     ����������     ����������     ��\n");
		Sleep(300);
		printf("\33[7A\33[32m");
		printf("\t\t\t       ��      ��     ����������     ��             ����������\n\t\t\t       ��      ��     ��             ��             ��      ��\n\t\t\t       ��      ��     ��             ��             ��      ��\n\t\t\t       ����������     ����������     ��             ����������\n\t\t\t       ��      ��     ��             ��             ��\n\t\t\t       ��      ��     ��             ��             ��\n\t\t\t       ��      ��     ����������     ����������     ��\n");
		Sleep(300);
		printf("\33[7A\33[33m");
		printf("\t\t\t       ��      ��     ����������     ��             ����������\n\t\t\t       ��      ��     ��             ��             ��      ��\n\t\t\t       ��      ��     ��             ��             ��      ��\n\t\t\t       ����������     ����������     ��             ����������\n\t\t\t       ��      ��     ��             ��             ��\n\t\t\t       ��      ��     ��             ��             ��\n\t\t\t       ��      ��     ����������     ����������     ��\n");
		Sleep(300);
		printf("\33[7A\33[34m");
		printf("\t\t\t       ��      ��     ����������     ��             ����������\n\t\t\t       ��      ��     ��             ��             ��      ��\n\t\t\t       ��      ��     ��             ��             ��      ��\n\t\t\t       ����������     ����������     ��             ����������\n\t\t\t       ��      ��     ��             ��             ��\n\t\t\t       ��      ��     ��             ��             ��\n\t\t\t       ��      ��     ����������     ����������     ��\n");
		Sleep(300);
		printf("\33[7A\33[35m");
		printf("\t\t\t       ��      ��     ����������     ��             ����������\n\t\t\t       ��      ��     ��             ��             ��      ��\n\t\t\t       ��      ��     ��             ��             ��      ��\n\t\t\t       ����������     ����������     ��             ����������\n\t\t\t       ��      ��     ��             ��             ��\n\t\t\t       ��      ��     ��             ��             ��\n\t\t\t       ��      ��     ����������     ����������     ��\n");
		Sleep(300);
		printf("\33[7A\33[36m");
		printf("\t\t\t       ��      ��     ����������     ��             ����������\n\t\t\t       ��      ��     ��             ��             ��      ��\n\t\t\t       ��      ��     ��             ��             ��      ��\n\t\t\t       ����������     ����������     ��             ����������\n\t\t\t       ��      ��     ��             ��             ��\n\t\t\t       ��      ��     ��             ��             ��\n\t\t\t       ��      ��     ����������     ����������     ��\n");
		Sleep(300);
		printf("\33[0m"); //�ر�����������ԣ��ָ���Ĭ��
		times++;
	}
	DisplayCursor(1); //��ʾ���
	Title();
	printf("\t\t\t                                ����\n");
	printf("\t\t\t                        --------------------\n\n");
	printf("1��ѡ���ѡ����水��Ӧ���ּ��ɽ�����Ӧ���ܽ��棻��ȷ��&ȡ��ѡ���У�����1���򡸻س�������Ϊȷ�ϣ�������Ϊȡ����\n\n");
	printf("2��ע�᣺��ע���ѧ�Ų�������ע�᣻��Ӧѧ����Ϣ�������ַ���Ϊ������-9���꼶-7���༶-19��ѧ��-14������-19���ֻ�-14�����֤-19��\n\n");
	printf("3����¼��ѧ����¼ʹ��ע��ʱ��ѧ�ź�������е�¼������Ա��¼ʹ���ض����˺ź�������е�¼��\n\n");
	printf("4��. . . . . . \n\n");
	printf("\n����1���ɴ򿪲鿴��ϸ�������˵���飬�����������ز˵�����. . . ");
	while(1) {
		choice = _getch();
		if (choice == '1')
			system("start ���༶���ڹ���ϵͳ���������˵����.doc"); //�򿪳������˵����Word�ļ�
		else
			break;
	}
}

//����Ա�˵�������������ʾ�˵���ѡ����
void AdminMenu(slklist* studentHead, alklist* attendanceHead, apointer* attendanceRear) {
	char choice;
	while (1) {
		Title();
		printf("\t\t\t                         ��ѡ��Ҫ���еĲ���\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           1.�鿴ѧ����Ϣ\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           2.��ѯ������Ϣ\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           3.��ӿ�����Ϣ\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           4.ɾ��������Ϣ\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           5.�޸Ŀ�����Ϣ\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           6.ͳ��ȱ����Ա\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           7.��������Ȩ��\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           8.��ʼ��ϵͳ\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           9.�˳�ϵͳ\n");
		printf("\t\t\t                        --------------------\n");
		DisplayCursor(0); //���ع��
		choice = _getch();
		switch (choice) {
		case '1':StudentInfo(); break; //�鿴ѧ����Ϣ
		case '2':Query(); break; //��ѯ������Ϣ
		case '3':Add(); break; //��ӿ�����Ϣ
		case '4':Delete(); break; //ɾ��������Ϣ
		case '5':Modify(); break; //�޸Ŀ�����Ϣ
		case '6':Statistic(); break; //ͳ��ȱ����Ա
		case '7':Super(); break; //��������Ȩ�ޣ���ʱ��ʵ�ù���
		case '8':Init(); break; //��ʼ��ϵͳ
		case '9':exit(0); //�˳�ϵͳ
		}
	}
}

//�û��˵�������������ʾ�˵���ѡ����
void UserMenu(spointer sp) {
	char choice;
	while (1) {
		Title();
		printf("\t\t\t                         ��ѡ��Ҫ���еĲ���\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           1.�鿴������Ϣ\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           2.ȷ�ϸ��˿���\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           3.��ѯ������Ϣ\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           4.ͳ��ȱ����Ա\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           5.�޸�����\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           6.�˳�ϵͳ\n");
		printf("\t\t\t                        --------------------\n");
		DisplayCursor(0); //���ع��
		choice = _getch();
		switch (choice) {
		case '1':UserInfo(sp); break; //�鿴������Ϣ
		case '2':Confirm(sp); break; //ȷ�ϸ��˿���
		case '3':Query(); break; //��ѯ������Ϣ
		case '4':Statistic(); break; //ͳ��ȱ����Ա
		case '5':ChangePassword(sp); break; //�޸�����
		case '6':exit(0); //�˳�ϵͳ
		}
	}
}

//�鿴ѧ����Ϣ
void StudentInfo() {
	Title();
	printf("\t\t\t                            �鿴ѧ����Ϣ\n");
	printf("\t\t\t                        --------------------\n");
	int amount = studentRear->X, n, i = 11;
	spointer sp = studentHead->next;
	DisplayCursor(1); //��ʾ���
	if (amount == 0)
		printf("ϵͳ������\33[36m0\33[0mλѧ������Ϣ��\n");
	else {
		printf("ϵͳ������\33[36m%d\33[0mλѧ������Ϣ���������£�\n\n", amount);
		printf("\t\t\t         �����������������ש����������������������ש������������������������������ש�����������������������\n");
		printf("\t\t\t         ��  ��� ��    ����   ��      ѧ��     ��  ȱ�ڴ��� ��\n");
		while (sp != NULL) {
			printf("\t\t\t         �ǩ��������������贈���������������������贈�����������������������������贈����������������������\n");
			printf("\t\t\t         ��       ��           ��               ��           ��\n");
			Goto_xy(37, i);
			printf("%02d", sp->X);
			Goto_xy(46, i);
			printf("%s", sp->name);
			Goto_xy(56, i);
			printf("%s", sp->num);
			Goto_xy(74, i);
			printf("%d��\n", sp->times);
			i += 2;
			sp = sp->next;
		}
		printf("\t\t\t         �����������������ߩ����������������������ߩ������������������������������ߩ�����������������������\n");
		printf("\n������Ҫ�鿴��ѧ�����(����0�ɷ��ز˵�����)��");
		scanf("%d", &n);
		if (n == 0) //���ز˵�����
			return;
		else if (n >= 1 && n <= studentRear->X) {
			Title();
			printf("\t\t\t                            �鿴ѧ����Ϣ\n");
			printf("\t\t\t                        --------------------\n");
			printf("\t\t\t                ����������������������������������������������������������������������\n");
			printf("\t\t\t                �� ��    ����                      ��\n");
			printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
			printf("\t\t\t                �� ��    ��                      ��\n");
			printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
			printf("\t\t\t                �� ��    ����                      ��\n");
			printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
			printf("\t\t\t                �� ��    ����                      ��\n");
			printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
			printf("\t\t\t                �� ѧ    �ţ�                      ��\n");
			printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
			printf("\t\t\t                �� ��    �룺                      ��\n");
			printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
			printf("\t\t\t                �� ��    ����                      ��\n");
			printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
			printf("\t\t\t                �� �� �� ֤��                      ��\n");
			printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
			printf("\t\t\t                �� ȱ�ڴ�����                      ��\n");
			printf("\t\t\t                ����������������������������������������������������������������������\n");
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
				printf("��");
			else if (sp->sex == Woman)
				printf("Ů");
			else
				printf("δ֪");
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
			printf("%d��", sp->times);
			printf("\n\n");
			if (sp->times != 0) { //��ѧ��������Ϣ������Ϊ0
				printf("��ѧ������\33[36m%d\33[0m��������Ϣ���������£�\n\n", sp->times);
				printf("���       ѧ��       ����        ����      �ڼ���    �γ�              �ص�    ����    ״̬\n\n");
				while (ap != NULL) {
					if (strcmp(sp->num, ap->num) == 0) {
						printf(" %02d    %-14s %-8s %04u-%02u-%02u   ��%d��   %-18s %-8s ", i, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
						if (ap->type == Late)
							printf("�ٵ�   ");
						else if (ap->type == Absent)
							printf("ȱϯ   ");
						else
							printf("���   ");
						if (ap->state == No)
							printf("\33[31mδȷ��\33[0m\n");
						else
							printf("\33[32m��ȷ��\33[0m\n");
						i++;
					}
					ap = ap->next;
				}
			}
			else //��ѧ��������Ϣ����Ϊ0
				printf("��ѧ������\33[36m0\33[0m��������Ϣ��\n");
		}
		else
			printf("\a\n\n\t\t\t                            ����������\n");
	}
	printf("\n");
	system("pause");
}

//��ѯ������Ϣ
void Query() {
	Title();
	printf("\t\t\t                            ��ѯ������Ϣ\n");
	printf("\t\t\t                        --------------------\n");
	printf("\t\t\t                            1.��������ѯ\n");
	printf("\t\t\t                        --------------------\n");
	printf("\t\t\t                            2.�鿴ȫ��\n");
	printf("\t\t\t                        --------------------\n");
	printf("\t\t\t                            3.ȡ��\n");
	printf("\t\t\t                        --------------------\n");
	char choice;
	apointer ap = attendanceHead->next;
	DisplayCursor(0); //���ع��
	while (1) {
		choice = _getch();
		if (choice == '1' || choice == '2' || choice == '3')
			break;
	}
	if (choice == '3') //ȡ�������ز˵�����
		return;
	else if (choice == '2') { //�鿴ȫ��������Ϣ
		Title();
		printf("\t\t\t                            ��ѯ������Ϣ\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                              �鿴ȫ��\n\n");
		printf("ϵͳ������\33[36m%d\33[0m��������Ϣ���������£�\n\n", attendanceRear->X);
		printf("���       ѧ��       ����        ����      �ڼ���    �γ�              �ص�    ����    ״̬\n\n");
		while (ap != NULL) {
			printf(" %02d    %-14s %-8s %04u-%02u-%02u   ��%d��   %-18s %-8s ", ap->X, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
			if (ap->type == Late)
				printf("�ٵ�   ");
			else if (ap->type == Absent)
				printf("ȱϯ   ");
			else
				printf("���   ");
			if (ap->state == No)
				printf("\33[31mδȷ��\33[0m\n");
			else
				printf("\33[32m��ȷ��\33[0m\n");
			ap = ap->next;
		}
	}
	else { //��������ѯ������Ϣ
		enum Type type;
		enum State state;
		char num[15], name[10], data[11], n[3], subject[25], locale[8], type0[5], state0[7], str[5];
		int flag = 1, amount = 0;
		Title();
		printf("\t\t\t                            ��ѯ������Ϣ\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                             ��������ѯ\n\n");
		printf("�������ѯ����(δ����Ĳ�����Ĭ��������з�����)��\n");
		printf("ע�����ڸ�ʽ��xxxx-xx-xx�����ʣ��ٵ�/ȱ��/��٣�״̬��δȷ��/��ȷ��\n");
		printf("\t���������������������������������ש������������������ש����������������������ש��������������ש������������������������������������������������������ש������������������ש��������������ש�������������������\n");
		printf("\t��      ѧ��     ��   ����  ��    ����   �� �ڼ��ک�            �γ�           ��   �ص�  ��  ���� ��   ״̬  ��\n");
		printf("\t�ǩ������������������������������贈�����������������贈���������������������贈�������������贈�����������������������������������������������������贈�����������������贈�������������贈������������������\n");
		printf("\t��               ��         ��           ��       ��                           ��         ��       ��         ��\n");
		printf("\t���������������������������������ߩ������������������ߩ����������������������ߩ��������������ߩ������������������������������������������������������ߩ������������������ߩ��������������ߩ�������������������\n");
		DisplayCursor(1); //��ʾ���
		rewind(stdin); //��ռ��̻�����
		Goto_xy(10, 13); gets_s(num);
		Goto_xy(27, 13); gets_s(name);
		Goto_xy(36, 13); gets_s(data);
		Goto_xy(50, 13); gets_s(n);
		Goto_xy(60, 13); gets_s(subject);
		Goto_xy(85, 13); gets_s(locale);
		Goto_xy(95, 13); gets_s(type0);
		Goto_xy(103, 13); gets_s(state0);
		printf("\n\n���       ѧ��       ����        ����      �ڼ���    �γ�              �ص�    ����    ״̬\n\n");
		while (ap != NULL) { //���ҷ��������Ŀ�����Ϣ�������
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
				if (strcmp(type0, "�ٵ�") == 0)
					type = Late;
				if (strcmp(type0, "ȱϯ") == 0)
					type = Absent;
				if (strcmp(type0, "���") == 0)
					type = Leave;
				flag = flag && (ap->type == type);
			}
			if (strcmp(state0, "\0") != 0) {
				if (strcmp(state0, "δȷ��") == 0)
					state = No;
				if (strcmp(state0, "��ȷ��") == 0)
					state = Yes;
				flag = flag && (ap->state == state);
			}
			if (flag) {
				amount++;
				printf(" %02d    %-14s %-8s %04u-%02u-%02u   ��%d��   %-18s %-8s ", ap->X, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
				if (ap->type == Late)
					printf("�ٵ�   ");
				else if (ap->type == Absent)
					printf("ȱϯ   ");
				else
					printf("���   ");
				if (ap->state == No)
					printf("\33[31mδȷ��\33[0m\n");
				else
					printf("\33[32m��ȷ��\33[0m\n");
			}
			ap = ap->next;
		}
		printf("\n\n\t\t\t                     ����ѯ������\33[36m%d\33[0m��������Ϣ��\n", amount);
	}
	printf("\n");
	DisplayCursor(1); //��ʾ���
	system("pause");
}

//��ӿ�����Ϣ
void Add() {
	while (1) {
		int year, month, flag = 0;
		char choice;
		apointer ap;
		spointer sp = studentHead->next;
		if ((ap = (apointer)malloc(sizeof(struct attendanceInfo_node))) == NULL) {
			printf("�ڴ��������\n");
			system("pause");
			return;
		}
		Title();
		printf("\t\t\t                            ��ӿ�����Ϣ\n");
		printf("\t\t\t                        --------------------\n");
		DisplayCursor(1); //��ʾ���
		ap->X = attendanceRear->X + 1;
		printf("\t\t\t������[ѧ��]��");
		scanf("%s", ap->num);
		printf("\t\t\t������[����]��");
		scanf("%s", ap->name);
		printf("\t\t\t������[����](��ʽ��xxxx-xx-xx)��");
		scanf("%u-%u-%u", &year, &month, &ap->data.tm_mday);
		ap->data.tm_year = year - 1900;
		ap->data.tm_mon = month - 1;
		printf("\t\t\t������[�ڼ���]��");
		scanf("%d", &ap->n);
		printf("\t\t\t������[�γ�]��");
		scanf("%s", ap->subject);
		printf("\t\t\t������[�ص�]��");
		scanf("%s", ap->locale);
		printf("\t\t\t��ѡ��[����]��1.�ٵ�  2.ȱϯ  3.���\n");
		while (1) {
			DisplayCursor(0); //���ع��
			choice = _getch();
			if (choice == '1') {
				ap->type = Late;
				printf("\33[1A\t\t\t��ѡ��[����]���ٵ�                   \n\n");
			}
			else if (choice == '2') {
				ap->type = Absent;
				printf("\33[1A\t\t\t��ѡ��[����]��ȱϯ                   \n\n");
			}
			else if (choice == '3') {
				ap->type = Leave;
				printf("\33[1A\t\t\t��ѡ��[����]�����                   \n\n");
			}
			else
				continue;
			break;
		}
		ap->state = No;
		ap->next = NULL;
		printf("���       ѧ��       ����        ����      �ڼ���    �γ�              �ص�    ����    ״̬\n\n");
		printf(" %02d    %-14s %-8s %04u-%02u-%02u   ��%d��   %-18s %-8s ", ap->X, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
		if (ap->type == Late)
			printf("�ٵ�   ");
		else if (ap->type == Absent)
			printf("ȱϯ   ");
		else
			printf("���   ");
		printf("\33[31mδȷ��\33[0m\n\n\n");
		printf("\t\t\t                      �Ƿ�ȷ����Ӹÿ�����Ϣ��\n\n");
		printf("\t\t\t                          1.ȷ��    2.ȡ��\n");
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
				printf("\a\n\n\t\t\t                        ѧ�Ż������������\n\n");
				DisplayCursor(1); //��ʾ���
				system("pause");
				break;
			}
			printf("\33[3A\t\t\t                                                \n");
			printf("\33[1A\t\t\t                  ������Ϣ��ӳɹ����Ƿ������ӣ�\n\n");
			printf("\t\t\t                          1.ȷ��    2.ȡ��\n");
			choice = _getch();
			if (choice == '1' || choice == '\r')
				continue;
		}
		break;
	}
}

//ɾ��������Ϣ
void Delete() {
	Title();
	printf("\t\t\t                            ɾ��������Ϣ\n");
	printf("\t\t\t                        --------------------\n");
	int n, amount = attendanceRear->X;
	spointer sp = studentHead->next;
	apointer ap = attendanceHead->next, aq;
	DisplayCursor(1); //��ʾ���
	if (amount == 0) { //�޿�����Ϣ��ɾ��
		printf("ϵͳ������\33[36m0\33[0m��������Ϣ��\n\n");
		system("pause");
		return;
	}
	printf("ϵͳ������\33[36m%d\33[0m��������Ϣ���������£�\n\n", amount);
	printf("���       ѧ��       ����        ����      �ڼ���    �γ�              �ص�    ����    ״̬\n\n");
	while (ap != NULL) {
		printf(" %02d    %-14s %-8s %04u-%02u-%02u   ��%d��   %-18s %-8s ", ap->X, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
		if (ap->type == Late)
			printf("�ٵ�   ");
		else if (ap->type == Absent)
			printf("ȱϯ   ");
		else
			printf("���   ");
		if (ap->state == No)
			printf("\33[31mδȷ��\33[0m\n");
		else
			printf("\33[32m��ȷ��\33[0m\n");
		ap = ap->next;
	}
	printf("\n������Ҫɾ���Ŀ�����Ϣ���(����0��ɾ��ȫ��������-1�ɷ��ز˵�����)��");
	scanf("%d", &n);
	if (n == -1) //���ز˵�����
		return;
	else if (n == 0) { //ɾ��ȫ��������Ϣ
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
		printf("\n\n\t\t\t                     �ɹ�ɾ������\33[36m%d\33[0m��������Ϣ��\n", amount);
	}
	else if (n >= 1 && n <= amount) { //ɾ��ָ����ſ�����Ϣ
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
				if (n == amount) //��ɾ������β��㣬��βָ��ָ����β���
					attendanceRear = ap;
				break;
			}
			ap = ap->next;
		}
		ap = ap->next;
		while (ap != NULL) { //��ɾ������Ľ���ż�һ
			ap->X--;
			ap = ap->next;
		}
		WriteAttendanceInfo(&attendanceHead);
		WriteStudentInfo(&studentHead);
		printf("\n\n\t\t\t                    �ɹ�ɾ�����Ϊ\33[36m%02d\33[0m�Ŀ�����Ϣ��\n", n);
	}
	else
		printf("\a\n\n\t\t\t                            ����������\n");
	printf("\n");
	system("pause");
}

//�޸Ŀ�����Ϣ
void Modify() {
	Title();
	printf("\t\t\t                            �޸Ŀ�����Ϣ\n");
	printf("\t\t\t                        --------------------\n");
	char choice, num0[15], num[15], name[10];
	int n, amount = attendanceRear->X, year, month, flag1 = 0, flag2 = 0;
	spointer sp = studentHead->next;
	apointer ap = attendanceHead->next;
	DisplayCursor(1); //��ʾ���
	if (amount == 0) { //�޿�����Ϣ���޸�
		printf("ϵͳ������\33[36m0\33[0m��������Ϣ��\n\n");
		system("pause");
		return;
	}
	printf("ϵͳ������\33[36m%d\33[0m��������Ϣ���������£�\n\n", amount);
	printf("���       ѧ��       ����        ����      �ڼ���    �γ�              �ص�    ����    ״̬\n\n");
	while (ap != NULL) {
		printf(" %02d    %-14s %-8s %04u-%02u-%02u   ��%d��   %-18s %-8s ", ap->X, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
		if (ap->type == Late)
			printf("�ٵ�   ");
		else if (ap->type == Absent)
			printf("ȱϯ   ");
		else
			printf("���   ");
		if (ap->state == No)
			printf("\33[31mδȷ��\33[0m\n");
		else
			printf("\33[32m��ȷ��\33[0m\n");
		ap = ap->next;
	}
	printf("\n������Ҫ�޸ĵĿ�����Ϣ���(����0�ɷ��ز˵�����)��");
	scanf("%d", &n);
	if (n == 0) //���ز˵�����
		return;
	else if (n<1 || n>amount) //����������
		printf("\a\n\n\t\t\t                            ����������\n");
	else { //�޸�ָ����ſ�����Ϣ
		printf("\n���       ѧ��       ����        ����      �ڼ���    �γ�              �ص�    ����    ״̬\n\n");
		ap = attendanceHead->next;
		while (ap != NULL) {
			if (ap->X == n) {
				printf(" %02d    %-14s %-8s %04u-%02u-%02u   ��%d��   %-18s %-8s ", ap->X, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
				if (ap->type == Late)
					printf("�ٵ�   ");
				else if (ap->type == Absent)
					printf("ȱϯ   ");
				else
					printf("���   ");
				if (ap->state == No)
					printf("\33[31mδȷ��\33[0m\n\n");
				else
					printf("\33[32m��ȷ��\33[0m\n\n");
				break;
			}
			ap = ap->next;
		}
		printf("\t\t\t                           ��ѡ���޸�����\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           1.�޸ĵ�������\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           2.�޸���������\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                           3.  ȡ    ��\n");
		printf("\t\t\t                        --------------------\n");
		DisplayCursor(0); //���ع��
		while (1) {
			choice = _getch();
			if (choice == '1' || choice == '2' || choice == '3')
				break;
		}
		DisplayCursor(1); //��ʾ���
		if (choice == '3') //ȡ�������ز˵�����
			return;
		else if (choice == '2') { //�޸���������
			printf("\t\t\t�������µ�[ѧ��]��");
			scanf("%s", num);
			printf("\t\t\t�������µ�[����]��");
			scanf("%s", name);
			while (sp != NULL) {
				if (strcmp(sp->num, num) == 0 && strcmp(sp->name, name) == 0) {
					flag1 = 1;
					break;
				}
				sp = sp->next;
			}
			if (flag1) { //���µ�ѧ�ź��������������
				if (strcmp(ap->num, num) != 0) { //���޸��˸ÿ�����Ϣ��ѧ�ź�����
					flag2 = 1;
					strcpy(num0, ap->num); //�����޸�ǰ��ѧ��
					strcpy(ap->num, num);
					strcpy(ap->name, name);
				}
			}
			else { //���µ�ѧ�ź����������ڻ����
				printf("\a\n\n\t\t\t                        ѧ�Ż������������\n\n");
				system("pause");
				return;
			}
			printf("\t\t\t�������µ�[����](��ʽ��xxxx-xx-xx)��");
			scanf("%u-%u-%u", &year, &month, &ap->data.tm_mday);
			ap->data.tm_year = year - 1900;
			ap->data.tm_mon = month - 1;
			printf("\t\t\t�������µ�[�ڼ���]��");
			scanf("%d", &ap->n);
			printf("\t\t\t�������µ�[�γ�]��");
			scanf("%s", ap->subject);
			printf("\t\t\t�������µ�[�ص�]��");
			scanf("%s", ap->locale);
			DisplayCursor(0); //���ع��
			printf("\t\t\t��ѡ���µ�[����]��1.�ٵ�  2.ȱϯ  3.���\n");
			while (1) {
				choice = _getch();
				if (choice == '1') {
					ap->type = Late;
					printf("\33[1A\t\t\t��ѡ���µ�[����]���ٵ�                   \n");
				}
				else if (choice == '2') {
					ap->type = Absent;
					printf("\33[1A\t\t\t��ѡ���µ�[����]��ȱϯ                   \n");
				}
				else if (choice == '3') {
					ap->type = Leave;
					printf("\33[1A\t\t\t��ѡ���µ�[����]�����                   \n");
				}
				else
					continue;
				break;
			}
			printf("\t\t\t��ѡ���µ�[״̬]��1.δȷ��  2.��ȷ��\n");
			while (1) {
				choice = _getch();
				if (choice == '1') {
					ap->state = No;
					printf("\33[1A\t\t\t��ѡ���µ�[״̬]��δȷ��              \n");
				}
				else if (choice == '2') {
					ap->state = Yes;
					printf("\33[1A\t\t\t��ѡ���µ�[״̬]����ȷ��              \n");
				}
				else
					continue;
				break;
			}
		}
		else { //�޸ĵ�������
			printf("\33[8A\t\t\t                         ��ѡ��Ҫ�޸ĵĲ���\n");
			printf("\t\t\t                        --------------------\n");
			printf("\t\t\t                            1.ѧ�ź�����    \n");
			printf("\t\t\t                        --------------------\n");
			printf("\t\t\t                            2.����          \n");
			printf("\t\t\t                        --------------------\n");
			printf("\t\t\t                            3.�ڼ���        \n");
			printf("\t\t\t                        --------------------\n");
			printf("\t\t\t                            4.�γ�\n");
			printf("\t\t\t                        --------------------\n");
			printf("\t\t\t                            5.�ص�\n");
			printf("\t\t\t                        --------------------\n");
			printf("\t\t\t                            6.����\n");
			printf("\t\t\t                        --------------------\n");
			printf("\t\t\t                            7.״̬\n");
			printf("\t\t\t                        --------------------\n");
			DisplayCursor(0); //���ع��
			while (1) {
				choice = _getch();
				if (choice >= '1' && choice <= '7')
					break;
			}
			DisplayCursor(1); //��ʾ���
			switch (choice) {
			case '1':
				printf("\t\t\t�������µ�[ѧ��]��");
				scanf("%s", num);
				printf("\t\t\t�������µ�[����]��");
				scanf("%s", name);
				while (sp != NULL) {
					if (strcmp(sp->num, num) == 0 && strcmp(sp->name, name) == 0) {
						flag1 = 1;
						break;
					}
					sp = sp->next;
				}
				if (flag1) { //���µ�ѧ�ź��������������
					if (strcmp(ap->num, num) != 0) { //���޸��˸ÿ�����Ϣ��ѧ�ź�����
						flag2 = 1;
						strcpy(num0, ap->num); //�����޸�ǰ��ѧ��
						strcpy(ap->num, num);
						strcpy(ap->name, name);
					}
				}
				else { //���µ�ѧ�ź����������ڻ����
					printf("\a\n\n\t\t\t                        ѧ�Ż������������\n\n");
					system("pause");
					return;
				}
				break;
			case '2':
				printf("\t\t\t�������µ�[����](��ʽ��xxxx-xx-xx)��");
				scanf("%u-%u-%u", &year, &month, &ap->data.tm_mday);
				ap->data.tm_year = year - 1900;
				ap->data.tm_mon = month - 1;
				break;
			case '3':
				printf("\t\t\t�������µ�[�ڼ���]��");
				scanf("%d", &ap->n);
				break;
			case '4':
				printf("\t\t\t�������µ�[�γ�]��");
				scanf("%s", ap->subject);
				break;
			case '5':
				printf("\t\t\t�������µ�[�ص�]��");
				scanf("%s", ap->locale);
				break;
			case '6':
				printf("\t\t\t��ѡ���µ�[����]��1.�ٵ�  2.ȱϯ  3.���\n");
				DisplayCursor(0); //���ع��
				while (1) {
					choice = _getch();
					if (choice == '1') {
						ap->type = Late;
						printf("\33[1A\t\t\t��ѡ���µ�[����]���ٵ�                   \n");
					}
					else if (choice == '2') {
						ap->type = Absent;
						printf("\33[1A\t\t\t��ѡ���µ�[����]��ȱϯ                   \n");
					}
					else if (choice == '3') {
						ap->type = Leave;
						printf("\33[1A\t\t\t��ѡ���µ�[����]�����                   \n");
					}
					else
						continue;
					break;
				}
				break;
			case '7':
				printf("\t\t\t��ѡ���µ�[״̬]��1.δȷ��  2.��ȷ��\n");
				DisplayCursor(0); //���ع��
				while (1) {
					choice = _getch();
					if (choice == '1') {
						ap->state = No;
						printf("\33[1A\t\t\t��ѡ���µ�[״̬]��δȷ��              \n");
					}
					else if (choice == '2') {
						ap->state = Yes;
						printf("\33[1A\t\t\t��ѡ���µ�[״̬]����ȷ��              \n");
					}
					else
						continue;
					break;
				}
			}
		}
		printf("\n���       ѧ��       ����        ����      �ڼ���    �γ�              �ص�    ����    ״̬\n\n");
		printf(" %02d    %-14s %-8s %04u-%02u-%02u   ��%d��   %-18s %-8s ", ap->X, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
		if (ap->type == Late)
			printf("�ٵ�   ");
		else if (ap->type == Absent)
			printf("ȱϯ   ");
		else
			printf("���   ");
		if (ap->state == No)
			printf("\33[31mδȷ��\33[0m\n");
		else
			printf("\33[32m��ȷ��\33[0m\n");
		WriteAttendanceInfo(&attendanceHead);
		if (flag2) { //���ɹ��޸��˿�����Ϣ��ѧ�ź������������ѧ����ȱ�ڴ����޸�
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
		printf("\n\n\t\t\t                    �ɹ��޸ı��Ϊ\33[36m%02d\33[0m�Ŀ�����Ϣ��\n", n);
	}
	printf("\n");
	DisplayCursor(1); //��ʾ���
	system("pause");
}

//ͳ��ȱ����Ա
void Statistic() {
	int i, j, amount = 0; //ȱ��ѧ������
	char choice;
	struct student stu[50];
	spointer sp = studentHead->next;
	apointer ap = attendanceHead->next;
	Title();
	printf("\t\t\t                            ͳ��ȱ����Ա\n");
	printf("\t\t\t                        --------------------\n");
	printf("\t\t\t                            1.������ͳ��\n");
	printf("\t\t\t                        --------------------\n");
	printf("\t\t\t                            2.ͳ��ȫ��\n");
	printf("\t\t\t                        --------------------\n");
	printf("\t\t\t                            3.ȡ��\n");
	printf("\t\t\t                        --------------------\n");
	DisplayCursor(0); //���ع��
	while (1) {
		choice = _getch();
		if (choice == '1' || choice == '2' || choice == '3')
			break;
	}
	if (choice == '3') //ȡ�������ز˵�����
		return;
	else if (choice == '2') { //ͳ��ȫ��ȱ����Ա
		Title();
		printf("\t\t\t                            ͳ��ȱ����Ա\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                              ͳ��ȫ��\n\n");
		while (sp != NULL) { //��¼��ȱ�ڼ�¼��ѧ����stu������
			if (sp->times != 0) {
				strcpy(stu[amount].name, sp->name);
				strcpy(stu[amount].num, sp->num);
				stu[amount].times = sp->times;
				amount++;
			}
			sp = sp->next;
		}
		if (amount == 0)
			printf("����\33[36m0\33[0mλѧ����ȱ��(�ǳ�ϯ)��¼��\n");
		else {
			QuickSort(0, stu, 0, amount);
			printf("����\33[36m%d\33[0mλѧ����ȱ��(�ǳ�ϯ)��¼����������(����Ѱ�ȱ�ڴ�����������)��\n\n", amount);
			printf("\t\t\t             �������������������������ש������������������������������ש�����������������������\n");
			printf("\t\t\t             ��    ����   ��      ѧ��     ��  ȱ�ڴ��� ��\n");
			for (i = 0, j = 13; i < amount; i++, j += 2) {
				printf("\t\t\t             �ǩ����������������������贈�����������������������������贈����������������������\n");
				printf("\t\t\t             ��           ��               ��           ��\n");
				Goto_xy(42, j);
				printf("%s", stu[i].name);
				Goto_xy(52, j);
				printf("%s", stu[i].num);
				Goto_xy(70, j);
				printf("%d��\n", stu[i].times);
			}
			printf("\t\t\t             �������������������������ߩ������������������������������ߩ�����������������������\n");
		}
	}
	else { //������ͳ��ȱ����Ա
		enum Type type;
		enum State state;
		char data[11], n[3], subject[25], locale[8], type0[5], state0[7], str[5];
		int flag = 1;
		Title();
		printf("\t\t\t                            ͳ��ȱ����Ա\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                             ������ͳ��\n\n");
		printf("������ͳ�Ʋ���(δ����Ĳ�����Ĭ��ȡ���з�����)��\n");
		printf("ע�����ڸ�ʽ��xxxx-xx-xx�����ʣ��ٵ�/ȱ��/��٣�״̬��δȷ��/��ȷ��\n");
		printf("\t\t   �������������������������ש��������������ש������������������������������������������������������ש������������������ש��������������ש�������������������\n");
		printf("\t\t   ��    ����   �� �ڼ��ک�            �γ�           ��   �ص�  ��  ���� ��   ״̬  ��\n");
		printf("\t\t   �ǩ����������������������贈�������������贈�����������������������������������������������������贈�����������������贈�������������贈������������������\n");
		printf("\t\t   ��           ��       ��                           ��         ��       ��         ��\n");
		printf("\t\t   �������������������������ߩ��������������ߩ������������������������������������������������������ߩ������������������ߩ��������������ߩ�������������������\n");
		DisplayCursor(1); //��ʾ���
		rewind(stdin); //��ռ��̻�����
		Goto_xy(21, 13); gets_s(data);
		Goto_xy(35, 13); gets_s(n);
		Goto_xy(45, 13); gets_s(subject);
		Goto_xy(70, 13); gets_s(locale);
		Goto_xy(80, 13); gets_s(type0);
		Goto_xy(88, 13); gets_s(state0);
		while (ap != NULL) { //���ҷ��������Ŀ�����Ϣ������ȡ��ѧ����Ϣ
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
				if (strcmp(type0, "�ٵ�") == 0)
					type = Late;
				if (strcmp(type0, "ȱϯ") == 0)
					type = Absent;
				if (strcmp(type0, "���") == 0)
					type = Leave;
				flag = flag && (ap->type == type);
			}
			if (strcmp(state0, "\0") != 0) {
				if (strcmp(state0, "δȷ��") == 0)
					state = No;
				if (strcmp(state0, "��ȷ��") == 0)
					state = Yes;
				flag = flag && (ap->state == state);
			}
			if (flag) {
				flag = 0; //stu�������Ƿ��и�ȱ��ѧ����Ϣ
				for (i = 0; i < amount; i++) {
					if (strcmp(ap->num, stu[i].num) == 0) {
						flag = 1;
						break;
					}
				}
				if (!flag) { //���ޣ�����Ӹ�ѧ����Ϣ��stu����
					strcpy(stu[amount].name, ap->name);
					strcpy(stu[amount].num, ap->num);
					amount++;
				}
			}
			ap = ap->next;
		}
		if (amount == 0)
			printf("\n\n����\33[36m0\33[0mλѧ����������ȱ�ڼ�¼��\n");
		else {
			QuickSort(1, stu, 0, amount);
			printf("\n\n����\33[36m%d\33[0mλѧ����������ȱ�ڼ�¼����������(����Ѱ�ѧ����������)��\n\n", amount);
			printf("\t\t\t                   �������������������������ש�������������������������������\n");
			printf("\t\t\t                   ��    ����   ��      ѧ��     ��\n");
			for (i = 0, j = 21; i < amount; i++, j += 2) {
				printf("\t\t\t                   �ǩ����������������������贈������������������������������\n");
				printf("\t\t\t                   ��           ��               ��\n");
				Goto_xy(48, j);
				printf("%s", stu[i].name);
				Goto_xy(58, j);
				printf("%s\n", stu[i].num);
			}
			printf("\t\t\t                   �������������������������ߩ�������������������������������\n");
		}
	}
	printf("\n");
	DisplayCursor(1); //��ʾ���
	system("pause");
}

//��������Ȩ�ޣ���ʱ��ʵ�ù���
void Super() {
	while (1) {
		char password[20], choice;
		Title();
		printf("\t\t\t                            ��������Ȩ��\n");
		printf("\t\t\t                        --------------------\n\n\n");
		printf("\t\t\t                  ��������������������������������������������������������������\n");
		printf("\t\t\t                  �� ���룺                      ��\n");
		printf("\t\t\t                  ��������������������������������������������������������������\n");
		DisplayCursor(1); //��ʾ���
		Goto_xy(50, 9);
		InputPassword(password);
		if (strcmp("ADMIN", password) == 0) { //������ȷ
			Title();
			printf("\t\t\t                            ��������Ȩ��\n");
			printf("\t\t\t                        --------------------\n\n\n");
			printf("\33[3B\33[31m");
			printf("\t    ����      ��       ����       ����������   ��      ��   ����������   ����      ��       ������\n");
			printf("\t    �� ��     ��     ��    ��         ��       ��      ��       ��       �� ��     ��     ��      ��\n");
			printf("\t    ��  ��    ��    ��      ��        ��       ��      ��       ��       ��  ��    ��    ��\n");
			printf("\t    ��   ��   ��   ��        ��       ��       ����������       ��       ��   ��   ��   ��\n");
			printf("\t    ��    ��  ��    ��      ��        ��       ��      ��       ��       ��    ��  ��    ��     ����\n");
			printf("\t    ��     �� ��     ��    ��         ��       ��      ��       ��       ��     �� ��     ��      ��\n");
			printf("\t    ��      ����       ����           ��       ��      ��   ����������   ��      ����       ��������\n");
			printf("\33[11B\33[0m");
			system("pause");
			break;
		}
		else { //�������
			printf("\a\n\n\n\t\t\t                       ����������������룡\n\n");
			printf("\t\t\t                          1.ȷ��    2.ȡ��\n");
			DisplayCursor(0); //���ع��
			choice = _getch();
			if (choice != '1' && choice != '\r')
				break;
		}
	}
}

//��ʼ��ϵͳ
void Init() {
	Title();
	printf("\t\t\t                             ��ʼ��ϵͳ\n");
	printf("\t\t\t                        --------------------\n\n");
	char choice;
	printf("\t\t\t           �Ƿ�ȷ����ʼ��ϵͳ����ϵͳ��Ϣ��ԭ�������Ϣ��\n\n");
	printf("\t\t\t                          1.ȷ��    2.ȡ��\n");
	DisplayCursor(0); //���ع��
	choice = _getch();
	if (choice == '1' || choice == '\r') {
		Destroy(&studentHead, &attendanceHead); //��������ѧ������Ϳ�������
		studentHead = NULL;
		studentRear = NULL;
		attendanceHead = NULL;
		attendanceRear = NULL;
		ReadStudentInfo(&studentHead, &studentRear, 0); //������ʼѧ����Ϣ����
		ReadAttendanceInfo(&attendanceHead, &attendanceRear, 0); //������ʼ������Ϣ����
		WriteStudentInfo(&studentHead);
		WriteAttendanceInfo(&attendanceHead);
		printf("\n\n\t\t\t                          ϵͳ��ʼ���ɹ���\n\n");
		DisplayCursor(1); //��ʾ���
		system("pause");
	}
}

//�鿴������Ϣ
void UserInfo(spointer sp) {
	Title();
	printf("\t\t\t                            �鿴������Ϣ\n");
	printf("\t\t\t                        --------------------\n");
	printf("\t\t\t                ����������������������������������������������������������������������\n");
	printf("\t\t\t                �� ��    ����                      ��\n");
	printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
	printf("\t\t\t                �� ��    ��                      ��\n");
	printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
	printf("\t\t\t                �� ��    ����                      ��\n");
	printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
	printf("\t\t\t                �� ��    ����                      ��\n");
	printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
	printf("\t\t\t                �� ѧ    �ţ�                      ��\n");
	printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
	printf("\t\t\t                �� ��    ����                      ��\n");
	printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
	printf("\t\t\t                �� �� �� ֤��                      ��\n");
	printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
	printf("\t\t\t                �� ȱ�ڴ�����                      ��\n");
	printf("\t\t\t                ����������������������������������������������������������������������\n");
	apointer ap = attendanceHead->next;
	int i = 1;
	Goto_xy(52, 7);
	printf("%s", sp->name);
	Goto_xy(52, 9);
	if (sp->sex == Man)
		printf("��");
	else if (sp->sex == Woman)
		printf("Ů");
	else
		printf("δ֪");
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
	printf("%d��", sp->times);
	printf("\n\n");
	if (sp->times != 0) { //���˿�����Ϣ������Ϊ0
		printf("������\33[36m%d\33[0m��������Ϣ���������£�\n\n", sp->times);
		printf("���       ѧ��       ����        ����      �ڼ���    �γ�              �ص�    ����    ״̬\n\n");
		while (ap != NULL) {
			if (strcmp(sp->num, ap->num) == 0) {
				printf(" %02d    %-14s %-8s %04u-%02u-%02u   ��%d��   %-18s %-8s ", i, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
				if (ap->type == Late)
					printf("�ٵ�   ");
				else if (ap->type == Absent)
					printf("ȱϯ   ");
				else
					printf("���   ");
				if (ap->state == No)
					printf("\33[31mδȷ��\33[0m\n");
				else
					printf("\33[32m��ȷ��\33[0m\n");
				i++;
			}
			ap = ap->next;
		}
	}
	else //���˿�����Ϣ����Ϊ0
		printf("������\33[36m0\33[0m��������Ϣ��\n");
	printf("\n");
	DisplayCursor(1); //��ʾ���
	system("pause");
}

//ȷ�ϸ��˿���
void Confirm(spointer sp) {
	Title();
	printf("\t\t\t                            ȷ�ϸ��˿���\n");
	printf("\t\t\t                        --------------------\n");
	int amount = 0, n, flag = 0;
	apointer ap = attendanceHead->next;
	DisplayCursor(1); //��ʾ���
	while (ap != NULL) {
		if (strcmp(sp->num, ap->num) == 0 && ap->state == No)
			amount++;
		ap = ap->next;
	}
	if (amount == 0) //��δȷ�ϵĸ��˿�����Ϣ
		printf("������\33[36m0\33[0m��δȷ�ϵĿ�����Ϣ��\n");
	else { //��δȷ�ϵĸ��˿�����Ϣ
		printf("������\33[36m%d\33[0m��δȷ�ϵĿ�����Ϣ���������£�\n\n", amount);
		printf("���       ѧ��       ����        ����      �ڼ���    �γ�              �ص�    ����    ״̬\n\n");
		ap = attendanceHead->next;
		while (ap != NULL) {
			if (strcmp(sp->num, ap->num) == 0 && ap->state == No) {
				printf(" %02d    %-14s %-8s %04u-%02u-%02u   ��%d��   %-18s %-8s ", ap->X, ap->num, ap->name, ap->data.tm_year + 1900, ap->data.tm_mon + 1, ap->data.tm_mday, ap->n, ap->subject, ap->locale);
				if (ap->type == Late)
					printf("�ٵ�   ");
				else if (ap->type == Absent)
					printf("ȱϯ   ");
				else
					printf("���   ");
				printf("\33[31mδȷ��\33[0m\n");
			}
			ap = ap->next;
		}
		printf("\n������Ҫȷ�ϵĿ�����Ϣ���(����0��ȷ��ȫ��������-1�ɷ��ز˵�����)��");
		scanf("%d", &n);
		if (n == -1) //���ز˵�����
			return;
		else if (n == 0) { //ȷ��ȫ�����˿�����Ϣ
			ap = attendanceHead->next;
			while (ap != NULL) {
				if (strcmp(sp->num, ap->num) == 0 && ap->state == No)
					ap->state = Yes;
				ap = ap->next;
			}
			WriteAttendanceInfo(&attendanceHead);
			printf("\n\n\t\t\t                     �ɹ�ȷ������\33[36m%d\33[0m��������Ϣ��\n", amount);
		}
		else { //ȷ��ָ����ſ�����Ϣ
			ap = attendanceHead->next;
			while (ap != NULL) {
				if (strcmp(sp->num, ap->num) == 0 && ap->X == n && ap->state == No) {
					ap->state = Yes;
					flag = 1;
					break;
				}
				ap = ap->next;
			}
			if (flag) { //�ɹ�ȷ��ָ����ſ�����Ϣ
				WriteAttendanceInfo(&attendanceHead);
				printf("\n\n\t\t\t                    �ɹ�ȷ�ϱ��Ϊ\33[36m%02d\33[0m�Ŀ�����Ϣ��\n", n);
			}
			else
				printf("\a\n\n\t\t\t                            ����������\n");
		}
	}
	printf("\n");
	system("pause");
}

//�޸�����
void ChangePassword(spointer sp) {
	while (1) {
		Title();
		printf("\t\t\t                              �޸�����\n");
		printf("\t\t\t                        --------------------\n");
		printf("\t\t\t                ����������������������������������������������������������������������\n");
		printf("\t\t\t                �� �� �� �룺                      ��\n");
		printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
		printf("\t\t\t                �� �� �� �룺                      ��\n");
		printf("\t\t\t                �ǩ�������������������������������������������������������������������\n");
		printf("\t\t\t                �� ȷ�����룺                      ��\n");
		printf("\t\t\t                ����������������������������������������������������������������������\n");
		char old[20], neww1[20], neww2[20], choice;
		DisplayCursor(1); //��ʾ���
		Goto_xy(52, 7);
		InputPassword(old);
		Goto_xy(52, 9);
		InputPassword(neww1);
		Goto_xy(52, 11);
		InputPassword(neww2);
		if (strcmp(sp->password, old) != 0) { //���������
			MessageBeep(MB_ICONHAND);
			printf("\n\n\n\t\t\t                    ����������������޸����룡\n\n");
			printf("\t\t\t                          1.ȷ��    2.ȡ��\n");
			DisplayCursor(0); //���ع��
			choice = _getch();
			if (choice == '1' || choice == '\r')
				continue;
		}
		else if (strcmp(neww1, neww2) != 0) { //�������벻��ͬ
			MessageBeep(MB_ICONHAND);
			printf("\n\n\n\t\t\t                  �������벻��ͬ���������޸����룡\n\n");
			printf("\t\t\t                          1.ȷ��    2.ȡ��\n");
			DisplayCursor(0); //���ع��
			choice = _getch();
			if (choice == '1' || choice == '\r')
				continue;
		}
		else { //��������ȷ��������������ͬ
			printf("\n\n\n\t\t\t                         �Ƿ�ȷ���޸����룿\n\n");
			printf("\t\t\t                          1.ȷ��    2.ȡ��\n");
			DisplayCursor(0); //���ع��
			choice = _getch();
			if (choice == '1' || choice == '\r') {
				strcpy(sp->password, neww1);
				WriteStudentInfo(&studentHead);
				printf("\n\n\t\t\t                    �����޸ĳɹ������μ������룡\n\n");
				DisplayCursor(1); //��ʾ���
				system("pause");
			}
		}
		break;
	}
}