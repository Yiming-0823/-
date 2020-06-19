#define _CRT_SECURE_NO_WARNINGS//����scanf����
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define true 1
#define false 0

//����������
//***************
typedef int bool;
typedef struct Goods
{
	char name[100]; // ���� 
	int count; // ���� 

}Goods, * Good;

//��������Ӧ����ģ�飬��ʾ��ǰ����һ������Ϊcount��name��Ʒ
bool add_goods(char name[], int count);
//���¿����Ϣ����Ӧ���ӿ���ӹ��ܣ���name��Ʒ����count����
bool add_count(char name[], int count);
//���¿���б���Ӧ������Ʒ�ӹ��ܣ�����name
bool add_to_list(char name[], int count);

//��������Ӧ����ģ�飬��ʾ��ǰ����һ������Ϊcount��name��Ʒ
bool delete_goods(char name[], int count);
//���¿����Ϣ����Ӧ���ٿ���ӹ��ܣ���name��Ʒ����count����
bool delete_count(char name[], int count);
//���¿���б���Ӧɾ����Ʒ�ӹ��ܣ�ɾ����Ʒ�б���name��Ʒ
bool delete_from_list(char name[]);

///��ʾ��ǰ����б�������Ʒ����������
void show_goods();
//�鿴�ֿ��е�name��Ʒ
Good find_goods(char name[]);
//�ļ���ȡ
void open_file();
//�ļ�����
void save_file();
//�ѳ��������¼д����־�ļ���
void write_log(char name[], int count, int flag);

struct Goods GOODS[100];
int S = 0;  //������-1�������±�

//��⺯��

bool add_goods(char name[], int count)
{
	Good good;
	good = find_goods(name);

	if (good->count == 0) {//�ж��Ƿ��иû���
		add_to_list(name, count);
	}
	else {//û�иû�������
		add_count(name, count);
	}
	printf("\t���ɹ���\n");
	write_log(name, count, 1);
	save_file();
	return true;
}

//���¿����Ϣ����Ӧ���ӿ���ӹ��ܣ���name��Ʒ����count����
bool add_count(char name[], int count)
{
	Good good;
	good = find_goods(name);
	good->count += count;
	return true;
}
//���¿���б���Ӧ������Ʒ�ӹ��ܣ�����name
bool add_to_list(char name[], int count)
{
	S++;//�������һ
	strcpy(GOODS[S].name, name);//ֱ��������β����û���
	GOODS[S].count = count;
	return true;
}
//���⺯��
bool delete_goods(char name[], int count)
{
	Good good;
	good = find_goods(name);

	if (count > good->count && good->count != 0) {//�жϻ�����ͳ�����
		printf("\t���ﲻ��\n");
		return false;
	}
	else
		if (good->count == 0)//û�иû�������
		{
			printf("\tû�д˻���\n");
			return false;
		}
		else//���Գ�������
		{
			delete_count(name, count);
			if (good->count == 0)//�����������
			{
				printf("\t������㣬ɾ���û�����Ϣ��\n");
				delete_from_list(name);
			}
		}
	printf("\t����ɹ���\n");
	write_log(name, count, 0);
	save_file();
	return true;
}
//���¿����Ϣ����Ӧ���ٿ���ӹ��ܣ���name��Ʒ����count����
bool delete_count(char name[], int count)
{

	Good good;
	good = find_goods(name);
	good->count -= count;
	return true;
}
//���¿���б���Ӧɾ����Ʒ�ӹ��ܣ�ɾ����Ʒ�б���name��Ʒ
bool delete_from_list(char name[])
{
	int i;
	for (i = 0; i <= S; i++) {
		if (strcmp(name, GOODS[i].name) == 0) {
			break;
		}
	}
	for (; i <= S; i++) {
		GOODS[i] = GOODS[i + 1];//��Ҫɾ���Ļ��￪ʼ���ú�һ������ǰһ�� 
	}
	S--;//������������һ�� 
	return true;
}


//��ʾ��ǰ����б�������Ʒ����������
void show_goods()
{
	int i;
	char c;
	printf("\t����\t����\n");
	for (i = 0; i <= S; i++)//��������
	{
		printf("\t%s\t %d\n", GOODS[i].name, GOODS[i].count);
	}
	printf("\n\n");
}

//���Һ���
Good find_goods(char name[])
{
	int i;
	Good good;
	for (i = 0; i <= S; i++)
	{
		if (strcmp(name, GOODS[i].name) == 0) {//�����ж��Ƿ��ҵ�
			return &GOODS[i];
		}
	}

	return  &GOODS[S + 1];
}

//���ļ�

void open_file()
{
	S = 0;//�����±�
	char file[20] = "D:\cangku.txt";//�ļ�·��
	FILE* fp;
	if ((fp = fopen(file, "r")) != NULL) {
		while (!feof(fp)) {//������ʾ
			if ((fscanf(fp, "%s\t%d\n", &GOODS[S].name, &GOODS[S].count)) == EOF)//�ļ�������ʶ
				break;
			//���ļ���Ϣ
			S++;
		}
		S--;
	}
	else
	{
		printf("�ļ���Ϣ��ȡʧ�ܣ�\n");
	}
	fclose(fp);
}

void save_file()
{
	char file[20] = "D:\cangku.txt";//�ļ�·��
	FILE* fp;
	int i;
	if ((fp = fopen(file, "w")) != NULL) {
		for (i = 0; i <= S; i++) {//������ʾ
			(fprintf(fp, "%s\t%d\n", GOODS[i].name, GOODS[i].count));
			//д�ļ���Ϣ
		}
		printf("\t�ļ���Ϣ����ɹ���\n");
	}
	else printf("\t�ļ���Ϣ����ʧ�ܣ�\n");
	fclose(fp);
}

void write_log(char name[], int count, int flag) //flag�����ж��ǳ��ⷿ���ǽ��ⷿ flag=1Ϊ��⣬flag=0Ϊ���� 
{
	FILE* fp;//�򿪵��ļ�
	time_t timep;//ʱ��
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);//��ȡ��ǰʱ��

	if ((fp = fopen("D:\log.txt", "a")) == NULL) {//׷���ļ���Ϣ 
		printf("\tд����־ʧ��");
	}
	else
	{
		if (flag == 0)
			fprintf(fp, "%d/%d/%d--%d:%d\t���⣺%s��������%d\n", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, name, count);
		else
			fprintf(fp, "%d/%d/%d--%d:%d\t��⣺%s��������%d\n", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, name, count);
	}
	fclose(fp);
}

int main()
{
	open_file();
	char name[20];
	int count = 0;
	///���˵� 
	while (1)
	{
		printf(" \t| ==================|\n");
		printf(" \t| 1���������       |\n");
		printf(" \t| 2���������       |\n");
		printf(" \t| 3����ʾ�����     |\n");
		printf(" \t| 4����ѯ����       |\n");
		printf(" \t| 0���˳�           |\n");
		printf(" \t| ==================|\n");
		printf("\t��ѡ��");
		int a;
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			printf("\t��������Ʒ����:");
			scanf("%s", name);
			printf("\t��������Ʒ����:");
			scanf("%d", &count);
			add_goods(name, count);
			break;
		case 2:
			printf("\t��������Ʒ����:");
			scanf("%s", name);
			printf("\t��������Ʒ����:");
			scanf("%d", &count);
			delete_goods(name, count);
			break;

		case 3:
			show_goods();
			break;
		case 4:
			printf("\t��������Ҫ��ѯ���������:");
			scanf("%s", &name);
			Good good = find_goods(name);
			if (good->count == 0) {
				printf("\tû�д˻�Ʒ\n");
				break;
			}
			printf("\t���ƣ� % s\n\t������ % d\n", good->name, good->count);
			break;
		case 0:
			exit(0);
		}
	}
	return 0;
}

