#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_SUBWAY 552
#define MAX_TRANSFER 152
#define MAX_LINE 18
#define INF 9999

typedef struct Subway_Name_NUMBER {
	char number[10]; //���� ��ȣ
	char name[20]; //���� �̸�
}snn;

typedef struct N {
	char name[20]; //
}n;

snn sub[MAX_SUBWAY]; //0���� 551���� ���� �̸��� ��ȣ �Է�
int idx = 0; //������� ���鶧 ���� index
int Subway[MAX_SUBWAY][MAX_SUBWAY]; //����ö �� �������
n transfer[MAX_SUBWAY][MAX_SUBWAY]; //'ȯ������.csv'�� ���� �迭

void subway_name() { //���� 
	FILE* NAME = fopen("���̸�.csv", "r"); //���̸� ������ �����´�
	if (NAME == NULL) { 
		printf("fail"); //������������ fail
		return;
	}
	char buffer[100], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i , indx = 0, count=1;
	//i- 0�̸� ����ȣ��, 1�̸� ���̸��� �����´�.
	//indx - sub�迭 �ε���
	//count - ����� �ѱ�� �����ٺ��� �б� ����
	while (!feof(NAME)) {
		i = 0;
		fgets(buffer, 100, NAME); 
		//����� ���������� count=1�̿��� �Ѿ��
		//�����ٺ��� count=2�� �ǹǷ� �������� �����´�.
		if (count > 1) {
			info = strtok(buffer, ","); //�� ��ȣ�� ,�� �������� �����´�.
			while (info != NULL) { //info�� null�϶�����
				if (i == 0) { //i�� 0�϶� ����ȣ
					strcpy(sub[indx].number, info); //����ü �迭 sub�� number�� ����
				}
				else if (i == 1) { //i�� 1�϶� ���̸�
					strcpy(sub[indx].name, info); //����ü �迭 sub�� name�� ����
				}
				i++; 
				info = strtok(NULL, "\n");//�� �̸��� \n�� �������� �����´�.
			}
			indx++; //����ü �迭 sub�� �ε��� ����
		}
		count++; //����� �ѱ�� ���� ����
	}
	fclose(NAME); //���� �ݱ�
	//printf("name success\n"); //�Լ��� �� ���ư����� Ȯ��
	return;
}

void init() {
	for (int i = 0; i < MAX_SUBWAY; i++)
		for (int j = 0; j < MAX_SUBWAY; j++)
			Subway[i][j] = INF; //�� ������� INF�� �ʱ�ȭ
	//printf("init success"); //�� �ʱ�ȭ �ߴ��� Ȯ��
}

void Line1() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = 0, j = 0, c = 0;
	idx = 0; //�������� idx 0���� ����
	FILE* Line = fopen("1ȣ��.csv", "r"); //1ȣ�� ���� ��������
	if (Line == NULL) {
		printf("fail"); //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line); //������ �� ���� �޴´�.
			if (strlen(buffer) == 3) //������ \n�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ",");
				idx++; //�����鼭 ���� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) { //��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = 0; j < idx-1; j++) { //idx 0~61 (����ȣ)
						Subway[i][j] = atoi(info); //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ","); //���� ��ū �޾ƿ���
					}
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				}
			c++; //����� ������ ���� ����
		}
		fclose(Line); //���� �ݱ�
		idx--; //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("Line1 success\n");
	}
}

void bLine1() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //�������� idx 62���� ����
	FILE* Line = fopen("1����.csv", "r"); //1���� ���� ��������
	if (Line == NULL) {
		printf("fail"); //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) {//Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line); //������ �� ���� �޴´�.
			if (strlen(buffer) == 6) //������ enter�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ",");
				idx++;//�����鼭 ȣ���� �� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) { //��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = fidx; j < idx - 1; j++) { //idx 62~100 (����ȣ)
						Subway[i][j] = atoi(info); //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ","); //���� ��ū �޾ƿ���
					}
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				}
			c++; //����� ������ ���� ����
		}
		fclose(Line);//���� �ݱ�
		idx--;  //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("bLine1 success");
	}
}

void Line2() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = idx, j = 0, c = 0;
	int fidx = idx; ////�������� idx 101���� ����
	FILE* Line = fopen("2ȣ��.csv", "r"); //2ȣ�� ���� ��������
	if (Line == NULL) {
		printf("fail"); //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line); //������ �� ���� �޴´�.
			if (strlen(buffer) == 3) //������ enter�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ",");
				idx++;  //�����鼭 ���� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) { //��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = fidx; j < idx - 1; j++) { //idx 101~143 (����ȣ)
						Subway[i][j] = atoi(info); //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ",");//���� ��ū �޾ƿ���
					}
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				}
			c++; //����� ������ ���� ����
		}
		fclose(Line); //���� �ݱ�
		idx--; //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("Line2 success");
	}
}

void bLine2() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //�������� idx 144���� ����
	FILE* Line = fopen("2����.csv", "r");  //2���� ���� ��������
	if (Line == NULL) {
		printf("fail");  //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) {  //Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line); //������ �� ���� �޴´�.
			if (strlen(buffer) == 5) //������ enter�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ",");
				idx++; //�����鼭 ���� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) { //��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = fidx; j < idx - 1; j++) { //idx 144~153 (����ȣ)
						Subway[i][j] = atoi(info); //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ","); //���� ��ū �޾ƿ���
					}
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				} 
			c++;  //����� ������ ���� ����
		}
		fclose(Line);//���� �ݱ�
		idx--;  //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("bLine2 success");
	}
}

void Line3() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //�������� idx 154���� ����
	FILE* Line = fopen("3ȣ��.csv", "r");  //3ȣ�� ���� ��������
	if (Line == NULL) {
		printf("fail"); //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line); //������ �� ���� �޴´�.
			if (strlen(buffer) == 3) //������ enter�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ",");
				idx++; //�����鼭 ���� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) { //��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = fidx; j < idx - 1; j++) { //idx 154~196 (����ȣ)
						Subway[i][j] = atoi(info);  //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ","); //���� ��ū �޾ƿ���
					}
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				}
			c++; //����� ������ ���� ����
		}
		fclose(Line); //���� �ݱ�
		idx--; //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("Line3 success");
	}
}

void Line4() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //�������� idx 197���� ����
	FILE* Line = fopen("4ȣ��.csv", "r"); //4ȣ�� ���� ��������
	if (Line == NULL) {  
		printf("fail"); //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line);  //������ �� ���� �޴´�.
			if (strlen(buffer) == 3) //������ enter�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ","); 
				idx++; //�����鼭 ���� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) {//��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = fidx; j < idx - 1; j++) { //idx  197~244 (����ȣ)
						Subway[i][j] = atoi(info);  //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ",");  //���� ��ū �޾ƿ���
					} 
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				}
			c++;  //����� ������ ���� ����
		}
		fclose(Line); //���� �ݱ�
		idx--; //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("Line4 success");
	}
}

void Line5() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //�������� idx 245���� ����
	FILE* Line = fopen("5ȣ��.csv", "r"); //5ȣ�� ���� ��������
	if (Line == NULL) {
		printf("fail"); //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line);  //������ �� ���� �޴´�.
			if (strlen(buffer) == 3) //������ enter�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ",");
				idx++; //�����鼭 ���� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) {//��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = fidx; j < idx - 1; j++) { //idx 245~288 (����ȣ)
						Subway[i][j] = atoi(info);  //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ",");  //���� ��ū �޾ƿ���
					}
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				}
			c++;  //����� ������ ���� ����
		}
		fclose(Line); //���� �ݱ�
		idx--; //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("Line5 success");
	}
}

void bLine5() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //�������� idx 289���� ����
	FILE* Line = fopen("5����.csv", "r"); //5���� ���� ��������
	if (Line == NULL) {
		printf("fail"); //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line);  //������ �� ���� �޴´�.
			if (strlen(buffer) == 4) //������ enter�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ",");
				idx++; //�����鼭 ���� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) {//��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = fidx; j < idx - 1; j++) { //idx  289~296 (����ȣ)
						Subway[i][j] = atoi(info);  //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ",");  //���� ��ū �޾ƿ���
					}
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				}
			c++;  //����� ������ ���� ����
		}
		fclose(Line); //���� �ݱ�
		idx--; //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("bLine5 success");
	}
}

void Line6() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //�������� idx 297���� ����
	FILE* Line = fopen("6ȣ��.csv", "r"); //6ȣ�� ���� ��������
	if (Line == NULL) {
		printf("fail"); //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line);  //������ �� ���� �޴´�.
			if (strlen(buffer) == 3) //������ enter�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ",");
				idx++; //�����鼭 ���� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) {//��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = fidx; j < idx - 1; j++) { //idx  297~334 (����ȣ)
						Subway[i][j] = atoi(info);  //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ",");  //���� ��ū �޾ƿ���
					}
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				}
			c++;  //����� ������ ���� ����
		}
		fclose(Line); //���� �ݱ�
		idx--; //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("Line6 success");
	}
}

void Line7() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //�������� idx 335���� ����
	FILE* Line = fopen("7ȣ��.csv", "r"); //7ȣ�� ���� ��������
	if (Line == NULL) {  
		printf("fail"); //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line);  //������ �� ���� �޴´�.
			if (strlen(buffer) == 3) //������ enter�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ","); 
				idx++; //�����鼭 ���� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) {//��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = fidx; j < idx - 1; j++) { //idx  335~376 (����ȣ)
						Subway[i][j] = atoi(info);  //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ",");  //���� ��ū �޾ƿ���
					} 
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				}
			c++;  //����� ������ ���� ����
		}
		fclose(Line); //���� �ݱ�
		idx--; //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("Line7 success");
	}
}

void Line8() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //�������� idx 377���� ����
	FILE* Line = fopen("8ȣ��.csv", "r"); //8ȣ�� ���� ��������
	if (Line == NULL) {
		printf("fail"); //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line);  //������ �� ���� �޴´�.
			if (strlen(buffer) == 3) //������ enter�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ",");
				idx++; //�����鼭 ���� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) {//��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = fidx; j < idx - 1; j++) { //idx  377~393 (����ȣ)
						Subway[i][j] = atoi(info);  //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ",");  //���� ��ū �޾ƿ���
					}
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				}
			c++;  //����� ������ ���� ����
		}
		fclose(Line); //���� �ݱ�
		idx--; //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("Line8 success");
	}
}

void Line9() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //�������� idx 394���� ����
	FILE* Line = fopen("9ȣ��.csv", "r"); //9ȣ�� ���� ��������
	if (Line == NULL) {
		printf("fail"); //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line);  //������ �� ���� �޴´�.
			if (strlen(buffer) == 3) //������ enter�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ",");
				idx++; //�����鼭 ���� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) {//��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = fidx; j < idx - 1; j++) { //idx  394~418 (����ȣ)
						Subway[i][j] = atoi(info);  //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ",");  //���� ��ū �޾ƿ���
					}
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				}
			c++;  //����� ������ ���� ����
		}
		fclose(Line); //���� �ݱ�
		idx--; //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("Line9 success");
	}
}

void BdLine() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //�������� idx 419���� ����
	FILE* Line = fopen("�д缱.csv", "r"); //�д缱 ���� ��������
	if (Line == NULL) {
		printf("fail"); //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line);  //������ �� ���� �޴´�.
			if (strlen(buffer) == 4) //������ enter�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ",");
				idx++; //�����鼭 ���� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) {//��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = fidx; j < idx - 1; j++) { //idx 419~ 443 (����ȣ)
						Subway[i][j] = atoi(info);  //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ",");  //���� ��ū �޾ƿ���
					}
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				}
			c++;  //����� ������ ���� ����
		}
		fclose(Line); //���� �ݱ�
		idx--; //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("BdLine success\n");
	}
}

void ILine1() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //�������� idx 444���� ����
	FILE* Line = fopen("��õ1��.csv", "r"); //��õ1ȣ�� ���� ��������
	if (Line == NULL) {
		printf("fail"); //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line);  //������ �� ���� �޴´�.
			if (strlen(buffer) == 4) //������ enter�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ",");
				idx++; //�����鼭 ���� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) {//��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = fidx; j < idx - 1; j++) { //idx  444~472 (����ȣ)
						Subway[i][j] = atoi(info);  //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ",");  //���� ��ū �޾ƿ���
					}
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				}
			c++;  //����� ������ ���� ����
		}
		fclose(Line); //���� �ݱ�
		idx--; //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("ILine1 success\n");
	}
}

void CLine() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //�������� idx 473���� ����
	FILE* Line = fopen("�߾Ӽ�.csv", "r"); //�߾Ӽ� ���� ��������
	if (Line == NULL) {
		printf("fail"); //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line);  //������ �� ���� �޴´�.
			if (strlen(buffer) == 4) //������ enter�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ",");
				idx++; //�����鼭 ���� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) {//��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = fidx; j < idx - 1; j++) { //idx  473~500 (����ȣ)
						Subway[i][j] = atoi(info);  //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ",");  //���� ��ū �޾ƿ���
					}
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				}
			c++;  //����� ������ ���� ����
		}
		fclose(Line); //���� �ݱ�
		idx--; //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("CLine success");
	}
}

void GcLine() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //�������� idx 501���� ����
	FILE* Line = fopen("���ἱ.csv", "r"); //���ἱ ���� ��������
	if (Line == NULL) {
		printf("fail"); //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line);  //������ �� ���� �޴´�.
			if (strlen(buffer) == 4) //������ enter�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ",");
				idx++; //�����鼭 ���� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) {//��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = fidx; j < idx - 1; j++) { //idx  501~521 (����ȣ)
						Subway[i][j] = atoi(info);  //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ",");  //���� ��ū �޾ƿ���
					}
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				}
			c++;  //����� ������ ���� ����
		}
		fclose(Line); //���� �ݱ�
		idx--; //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("GcLine success\n");
	}
}

void GuLine() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //�������� idx 522���� ����
	FILE* Line = fopen("���Ǽ�.csv", "r"); //���Ǽ� ���� ��������
	if (Line == NULL) {
		printf("fail"); //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line);  //������ �� ���� �޴´�.
			if (strlen(buffer) == 4) //������ enter�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ",");
				idx++; //�����鼭 ���� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) {//��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = fidx; j < idx - 1; j++) { //idx  522~541 (����ȣ)
						Subway[i][j] = atoi(info);  //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ",");  //���� ��ū �޾ƿ���
					}
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				}
			c++;  //����� ������ ���� ����
		}
		fclose(Line); //���� �ݱ�
		idx--; //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("GuLine success\n");
	}
}

void AirLine() {
	char buffer[MAX_SUBWAY], * info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //�������� idx 542���� ����
	FILE* Line = fopen("����ö��.csv", "r"); //����ö�� ���� ��������
	if (Line == NULL) {
		printf("fail"); //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line�� null�϶�����
			fgets(buffer, MAX_SUBWAY, Line);  //������ �� ���� �޴´�.
			if (strlen(buffer) == 3) //������ enter�� �־� ���� �����ߴٰ� ���� ���� ���� ���̷� ������ while���� ���� �� �ְ� ��
				break;
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (c == 0 && info != NULL) { //��� ������
				info = strtok(NULL, ",");
				idx++; //�����鼭 ���� ���� ���� 
			}
			if (c > 0) //��� ������ ���� �ٺ��� �̰����� �´�.
				while (info != NULL) {//��ū�� null�϶� ����
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ����� ���̰� ���´�.
					for (j = fidx; j < idx - 1; j++) { //idx 542~551 (����ȣ)
						Subway[i][j] = atoi(info);  //���� ��ū�� �� ������Ŀ� �������� �ִ´�.
						info = strtok(NULL, ",");  //���� ��ū �޾ƿ���
					}
					i++; //�� ��ȣ�� �ϳ��� �÷��ش�.
				}
			c++;  //����� ������ ���� ����
		}
		fclose(Line); //���� �ݱ�
		idx--; //�� ó�� ����ȣ���� �������Ƿ� �ϳ� �ٿ��ش�.
	//	printf("AirLine success\n");
	}
}

void putData() {
	Line1();
	bLine1();
	Line2();
	bLine2();
	Line3();
	Line4();
	Line5();
	bLine5();
	Line6();
	Line7();
	Line8();
	Line9();
	BdLine();
	ILine1();
	CLine();
	GcLine();
	GuLine();
	AirLine();
	//�����͵��� �ִ� �Լ�
}

void Transfer() {
	char buffer[INF],*info;
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = 0, j = 0;
	int index = 0,xidx=0,yidx=0;
	char *x, *y;
	FILE* Line = fopen("ȯ������.csv", "r");  //ȯ������ ���� ��������
	if (Line == NULL) {
		printf("fail");   //�������� ������ ��� fail���
		exit(0);
	}
	else {
		while (!feof(Line)) {  //Line�� null�϶�����
			fgets(buffer, INF, Line);  //������ �� ���� �޴´�.
			j = 0;  //�� ��ȣ �ʱ�ȭ
			info = strtok(buffer, ","); //,�� �������� ��ū �������� -> ����ȣ�� ���´�
			while (info != NULL) { //��ū�� null�϶� ����
				strcpy(transfer[i][j].name,info); //ȯ�������� ���� �迭�� �������� �ִ´�.
				if (j == 149) { //���������� \n�� �־ 
					info = strtok(NULL, "\n"); //\n�� �����ش�.
				}
				else {
					info = strtok(NULL, ","); //,�� �������� ��ū �������� -> ��� ����
				}
				j++; //�� ��ȣ �ϳ��� �÷��ش�.
			}
			i++; //�� ��ȣ �ϳ��� �÷��ش�.
		}
		fclose(Line); //���� �ݱ�

	}
	for (int k = 1; k <= i; k++)
		for (j = 1; j <= i; j++) {
			int t = atoi(transfer[k][j].name); //�� ������ ���� �Ÿ������� ���� t�� �ִ´� �׷��� ��, �� 1���� ����
			if (t != INF && t!=0 ) { //t�� 9999�� 0�� �ƴϸ�
				x = transfer[k][0].name; 
				y = transfer[0][j].name; //�� ������ ��� ���� ���� �������� �˱�����
				//�� ������ ó�� ��(k,0)�� ��(0,j)�� ������ x,y�� �־��ش�. 
				index = 0;
				while (index < MAX_SUBWAY) { 
					if (strcmp(sub[index].number,x)==0)
						xidx = index; 
					if (strcmp(sub[index].number,y)==0)
						yidx = index;
					index++;
				}
				//����ö���� 0~551�ε����� ǥ���� �迭�� ������ ��� ���� �ϳ��� ���ϸ鼭
				//x,y�� ����ȣ�� ���� �ε����� �����´�.
				//�� �ε����� xidx,yidx�� �־��ش�.
				Subway[xidx][yidx] = t;
				//������Ŀ� �ش�Ǵ� �� ������ t���� �־��ش�.
			}
		}
	printf("transfer success");
}

int numbering(int j) {
	if (j >= 0 && j < 62)
		return 0;
	else if (j < 101)
		return 1;
	else if (j < 144)
		return 2;
	else if (j < 154)
		return 3;
	else if (j < 197)
		return 4;
	else if (j < 245)
		return 5;
	else if (j < 289)
		return 6;
	else if (j < 297)
		return 7;
	else if (j < 335)
		return 8;
	else if (j < 377)
		return 9;
	else if (j < 394)
		return 10;
	else if (j < 419)
		return 11;
	else if (j < 444)
		return 12;
	else if (j < 473)
		return 13;
	else if (j < 501)
		return 14;
	else if (j < 522)
		return 15;
	else if (j < 542)
		return 16;
	else if (j < 552)
		return 17;
} //�ش� �ε����� ���� ��ȣ���� �ִ� ������ �����ϴ� �Լ�

int distance[MAX_SUBWAY]; /* �����������κ����� �ִܰ�� �Ÿ� */
int found[MAX_SUBWAY]; /* �湮�� �� ǥ�� */
int path[MAX_SUBWAY]; /*�� ǥ��*/
int visited[MAX_LINE]; /*�湮�� ����(ȣ��) ǥ��*/

typedef struct GraphNode {
	int vertex; //ȣ�� ��ȣ�� �������� ����
	struct GraphNode* link; 
}GraphNode;

GraphNode *subway[MAX_LINE]; //ȣ������ ȯ���� �� �ִ� ȣ������ ������ ��������Ʈ


// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
void insert_edge(int u, int v)
{
	GraphNode* node;
	if (u >= MAX_LINE || v >= MAX_LINE) //u,v�� ȣ���� �� �������� ������ ����
	{
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v; //ȣ�� �ֱ�
	node->link = subway[u]; //���� ȣ���� ����Ʈ�� �����ͼ�
	subway[u] = node; //�ش� ȣ���� �������ش�.

	//��������Ʈ�� �����ϴ� ����
}


int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX; 
	minpos = -1;
	//�ּұ���, �ε��� �ʱ�ȭ
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) { //�湮���� ���� ���̸鼭 ���̰� �ּ��� ���� ������
			min = distance[i]; //�� ���̷� min ������Ʈ
			minpos = i; //�� ���� �ε����� minpos ������Ʈ
		}
	return minpos; //�ּ� �Ÿ��� ��� �ε��� ��ȯ
}

void shortest_path(int start)
{
	int i, u, w;
	for (i = 0; i < MAX_SUBWAY; i++) /* �ʱ�ȭ */
	{
		path[i] = start;
		distance[i] = Subway[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE; /* ���� ���� �湮 ǥ�� */
	distance[start] = 0;
	path[start] = -1; //�����ϴ� �� -1
	for (i = 0; i < MAX_SUBWAY - 1; i++) {
		u = choose(distance, MAX_SUBWAY, found); //�ּҰ��� �ִ� �ε���
		found[u] = TRUE; //�湮 ǥ��
		for (w = 0; w < MAX_SUBWAY; w++)
			if (!found[w])
				if (distance[u] + Subway[u][w] < distance[w]) { //�ش� ���� ������ ���� ���� �ش� ���ں��� ������
					distance[w] = distance[u] + Subway[u][w]; //������Ʈ
					path[w] = u; //��� ����
				}
	}
}

void shortest_path_t(int start) {
	int i, u, w;
	for (i = 0; i < MAX_SUBWAY; i++) /* �ʱ�ȭ */
	{
		path[i] = start;
		distance[i] = Subway[start][i];
	}
	found[start] = TRUE; /* ���� ���� �湮 ǥ�� */
	distance[start] = 0;
	path[start] = -1; //�����ϴ� �� -1
	for (i = 0; i < MAX_SUBWAY - 1; i++) {
		u = choose(distance, MAX_SUBWAY, found); //�ּҰ��� �ִ� �ε���
		found[u] = TRUE; //�湮 ǥ��
		for (w = 0; w < MAX_SUBWAY; w++)
			if (!found[w])
				if (distance[u] + Subway[u][w] < distance[w]) { //�ش� ���� ������ ���� ���� �ش� �Ÿ����� ª����
					distance[w] = distance[u] + Subway[u][w]; //������Ʈ
					path[w] = u; //��� ����
				}
	}
}

void print_path(int start, int end) {
	int result[MAX_SUBWAY]; //����� ���� �迭
	int k = end; //�������� �ִ´�.
	int index=0, time = 0, m = 0,tr=0; 
	//index- ��߿��� �ִ� �ε����� ���� ����
	//time - ȯ���� ������ �ɸ��� �ð�
	//tr - ȯ�½ð�
	char *line=(char*)malloc(sizeof(char)); //ȣ�������� ���� ����
	for (int i = 0; i < MAX_SUBWAY; i++) {
		result[i] = k; 
		int tmp = path[k];
		if (tmp == -1) {//-1�̸� ��߿��� �����Ѱ�
			index = i; //��߿��� �ִ� �ε���
			break;
		}
		k = tmp;
	} //result�迭�� ���������� ��߿� ������ path�迭�� �������鼭 ������ ��θ� �����Ѵ�.

	for (int num = index; num >=0; num--) { //result�迭�� ��߿����� ���������� �Ųٷ� ����Ǿ��ִ�. 
		//�׷��� index�� �ϳ��� �ٿ����鼭 for�� ����
		int j = result[num]; //result�迭���� �ش� �ε����� �ִ� ������ ���� �ε���
		if (j >= 0 && j < 62)
			strcpy(line, "1ȣ��");
		else if (j < 101)
			strcpy(line, "1����");
		else if (j < 144)
			strcpy(line, "2ȣ��");
		else if (j < 154)
			strcpy(line, "2����");
		else if (j < 197)
			strcpy(line, "3ȣ��");
		else if (j < 245)
			strcpy(line, "4ȣ��");
		else if (j < 289)
			strcpy(line, "5ȣ��");
		else if (j < 297)
			strcpy(line, "5����");
		else if (j < 335)
			strcpy(line, "6ȣ��");
		else if (j < 377)
			strcpy(line, "7ȣ��");
		else if (j < 394)
			strcpy(line, "8ȣ��");
		else if (j < 419)
			strcpy(line, "9ȣ��");
		else if (j < 444)
			strcpy(line, "�д缱");
		else if (j < 473)
			strcpy(line, "��õ1ȣ��");
		else if (j < 501)
			strcpy(line, "�߾Ӽ�");
		else if (j < 522)
			strcpy(line, "���ἱ");
		else if (j < 542)
			strcpy(line, "���Ǽ�");
		else if (j < 552)
			strcpy(line, "����ö��");
		//���� �ε����� ���� � ȣ������ line ������ ����
		m++; //������ ���� ���� ���� ����
		if (num==0)//�ε����� ���� �����ϸ� �������� ���
			printf("-><%s> %s <����>\n", line, sub[j].name); //ȣ���� �� ���
		else if (strcmp(sub[j].name, sub[result[num-1]].name) == 0) {
			//ȯ�¿��� �����ϸ� ���� �ΰ��� ��µǹǷ�
			//���� ���̸��� ������ �� �̸��� ������ if���� ���´�
			if (num == index) { //ȯ�¿��� ��߿��̸�?
				continue; //�� �ΰ��� ���� �̸��̹Ƿ� ���� �ε������� ����ϰ� �Ѵ�.
			}
			if (num - 1 == 0) { //�������̸�?
				printf("-><%s> %s <����>\n", line, sub[j].name); //������ ȣ���� �� ���
				break; //���� ������ ���� ȯ�¿� �����̹Ƿ� ������� �ʰ� �ݺ����� �������´�.
			}
			
				int ran = rand() % Subway[result[num-1]][j] + 1; //������Ŀ��� �ش� �ε����� �ִ� ���ڷ�
				//1~(�ش����)�� ���� �߻�
				tr = tr + ran; //ȯ�½ð��� ���� ���ϱ�
				strcpy(line, "ȯ�� : �ҿ�ð�");
				printf("-><%s %d ��> %s\n", line, ran, sub[j].name); //ȯ�� ��� �ɸ����� ���
				num--; //�׳� �Ѿ�� ȯ�¿��� �ѹ��� ����ǹǷ� num�� �ϳ� �� �ٿ��� �Ѿ�� �Ѵ�.
			
		}
		else { //�����ϱ� ��
			time = time + Subway[j][result[num-1]]; //�ش� �ε����� �ִ� ���ڸ� �ð��� �����ش�.
			printf("-><%s> %s\n", line, sub[j].name); //ȣ���� �� ���
		}
	}
	printf("�ҿ�ð� : %d (%d + ȯ�� �ҿ�ð� : %d) ��\n",time+tr,time,tr); //�ɸ� �ð� ���
	printf("������ �� : %d��", m); //������ �� ���
}

void make_list() {
	for (int v = 0; v < MAX_LINE; v++)
		subway[v] = NULL; //ȣ�� ��������Ʈ�� �ʱ�ȭ�ϴ� ����
	char buffer[INF], * info; 
	//������ ���� buffer�迭, ��ū�� ���� info
	int i = 0, j = 0;
	int index, xidx = 0, yidx = 0;
	//xidx - �ش� ��ġ�� ù ���� ����ȣ�� �ε����� �ٲ� ������ ����
	//yidx - �ش� ��ġ�� ù ���� ����ȣ�� �ε����� �ٲ� ������ ����
	char* x, * y;

	for (int k = 1; k < MAX_TRANSFER; k++)
		for (j = 1; j < MAX_TRANSFER; j++) { 
			int t = atoi(transfer[k][j].name); //�� ������ ���� �Ÿ������� ���� t�� �ִ´�
			if (t != INF && t != 0) { //t�� 9999�� 0�� �ƴϸ�
				x = transfer[k][0].name;
				y = transfer[0][j].name; //�� ������ ��� ���� ���� �������� �˱�����
				//�� ������ ó�� ��� ���� ������ x,y�� �־��ش�. 
				index = 0;
				while (index < MAX_SUBWAY) {
					if (strcmp(sub[index].number, x) == 0)
						xidx = index;
					if (strcmp(sub[index].number, y) == 0)
						yidx = index;
					index++;
				}
				//����ö���� 0~551�ε����� ǥ���� �迭�� ������ �ϳ��� ���ϸ鼭
				//������ �� �ε����� xidx,yidx�� �־��ش�.
				xidx = numbering(xidx);
				yidx = numbering(yidx);
				//�� �ε����� ��ȣ�������� �����Ѵ�. (1~18)
				insert_edge(xidx, yidx); //xidxȣ�� ��������Ʈ��
				//yidx edge�� �߰��Ѵ�.
			}
		}	
}

int pass[MAX_LINE]; //�������� �ִ� ȣ���� ã���鼭 ����ġ�� ȣ������ ��� ���� �迭
int lindex = 0;

int mintransfer(int s, int e) {

	GraphNode* w;
	//�� �ε����� ȣ�� ��ȣ �ҷ�����
	visited[s] = TRUE; // ���� v�� �湮 ǥ��
	//printf("���� %d -> ", s); // �湮�� ���� ���
	for (w = subway[s]; w; w = w->link)// ���� ���� Ž��
		if (w->vertex == e) { //�ش� ��������Ʈ�� �������� �ִ� ȣ���� ������
			pass[lindex]= w->vertex; //index�迭�� ȣ�������� �ִ´�
			return e; 
		}
	if (w == NULL) { //�����ϴ� ȣ���� ���ٸ�
		for (w = subway[s]; w; w = w->link) {
			if (!visited[w->vertex]) {
				pass[lindex++] = w->vertex; //�� ��������Ʈ�� �湮���� ���� ȣ���� ������

				//index�� �� ȣ�� ������ �ְ�
				//�� ȣ���� �������� �ϴ� ��������Ʈ���� (����Լ� ������)
				if (mintransfer(w->vertex, e) == e)
					return e; //���ϴ� ȣ���� �߰��ϸ� �ٷ� ����Լ� ��� ����������
			}
		}
	}
}

int fintransfer(int s, int e, int t, int sta[10]) {
	GraphNode* w;
	int j = 0;
	t = t - 1;
	while (t > -1) { //t�� 0�� �ɶ�����
		for (w = subway[s]; w; w = w->link) {
			if (w->vertex == pass[t]) {
				sta[j] = w->vertex;
				return j+1;
				//��߿��� �ִ� ȣ���� �������� �ִ� ȣ���� ���� ���� ȣ���� �ִ��� Ȯ��
				//������ sta�迭�� �ִ´�.
				//�ش� �ε���+1�� ��ȯ
			}
		}	
		sta[j++] = pass[t--];
		//������ sta�迭�� �ְ�
		//�� ���� ȣ���� �ִ��� Ȯ���ϱ� ���� index�迭�� �ε����� �ϳ� �ٿ��ش�.

	}
	//�׷� ���� sta�迭���� ��߿����� ���������� ���� ����ġ�� ȣ������ ����Ǿ��ִ�
}

int main(void)
{
	subway_name(); //���� ����ü �迭 ���� sub�� �� �̸��� ��ȣ�� �־��ش�.
	//�� �̸� ��ȣ �ε����� �����ϱ�
	init();
	putData();
	//�� ���� ������ 2���� �迭�� �ֱ�
	Transfer();
	//ȯ������ 2���� �迭�� �ֱ�
	printf("\n");

	char start[50];
	char end[50];
	int i,j, s = -1, e = -1, num=0;
	//s,e - ���� �ε���
	//num - ��� ��ȣ
	int u, v, d;
	//u-��߿��� �ִ� ȣ��
	//v-�������� �ִ� ȣ��
	//d-�ε����� �޴� ����
	int way[10] = { '\0' };
	//����ġ�� ȣ���� ���� �迭
	int cmp1=1, cmp2=1;
	//�� �̸��� ����� �Ǿ����� Ȯ���ϴ� ����
	printf("��߿��� �Է����ּ���: ");
	scanf("%s",start);
	printf("�������� �Է����ּ���: ");
	scanf("%s", end);

	while (cmp1 == 1 || cmp2 == 1 || s==e) { //�Է��� ����� �ȵǾ������ �ٽ� �ۼ��ϱ�
		cmp1 = 1; cmp2 = 1; //�ٽ� 1�� �ʱ�ȭ
		i = 0;
		while (i < MAX_SUBWAY) {
			if (strcmp(start, sub[i].name) == 0) {
				cmp1 = 0;
				s = i;
			}
			if (strcmp(end, sub[i].name) == 0) {
				cmp2 = 0;
				e = i;
			}
			i++; 
		}
		//�� �̸��� ����� �ԷµǾ����� cmp1,cmp2�� 0���� �������� �ƴҰ�� 1�� ������
		if (cmp1 == 1 || cmp2 == 1) {
			printf("<�� �̸��� �߸��Ǿ����ϴ�! �ٽ� �Է����ּ���!>\n\n");
			printf("��߿��� �Է����ּ���: ");
			scanf("%s", start);

			printf("�������� �Է����ּ���: ");
			scanf("%s", end);
		}
		if (cmp1==0 && cmp2==0 && s == e) { //�Ѵ� �Է��� �� �Ǿ����� �� �̸��� �������
			printf("\n<��߿��� �������� �����ϴ�! �ٽ� �Է����ּ���!>\n\n");
			printf("��߿��� �Է����ּ���: ");
			scanf("%s", start);

			printf("�������� �Է����ּ���: ");
			scanf("%s", end);
		}
	}	
	printf("���? 1.�ִܰ�� 2.�ּ�ȯ��\n:");
	scanf("%d", &num);

	switch (num) {
	case 1: //�ִܰ�� ���
		shortest_path(s);
		printf("�ִܰ��\n<���>\n");
		print_path(s, e);
		break;
	case 2: //�ּ�ȯ�� ���
		make_list(); //ȯ�� ��������Ʈ �����
		u = numbering(s);
		v = numbering(e);
		//��߿��� �������� ȣ������ �ٲ��ֱ�
		for (int i = 0; i < MAX_SUBWAY; i++) found[i] = TRUE;
		if (u == v) { //���� ȣ���̸� �ִܰŸ�=�ּ�ȯ��
			switch (u) {
			case 0:
				for (int i = 0; i < 62; i++)
					found[i] = FALSE;
				break;
			case 1:
				for (int i = 62; i < 101; i++)
					found[i] = FALSE;
				break;
			case 2:
				for (int i = 101; i < 144; i++)
					found[i] = FALSE;
				break;
			case 3:
				for (int i = 144; i < 154; i++)
					found[i] = FALSE;
				break;
			case 4:
				for (int i = 154; i < 197; i++)
					found[i] = FALSE;
				break;
			case 5:
				for (int i = 197; i < 245; i++)
					found[i] = FALSE;
				break;
			case 6:
				for (int i = 245; i < 289; i++)
					found[i] = FALSE;
				break;
			case 7:
				for (int i = 289; i < 297; i++)
					found[i] = FALSE;
				break;
			case 8:
				for (int i = 297; i < 335; i++)
					found[i] = FALSE;
				break;
			case 9:
				for (int i = 335; i < 377; i++)
					found[i] = FALSE;
				break;
			case 10:
				for (int i = 377; i < 394; i++)
					found[i] = FALSE;
				break;
			case 11:
				for (int i = 394; i < 419; i++)
					found[i] = FALSE;
				break;
			case 12:
				for (int i = 419; i < 444; i++)
					found[i] = FALSE;
				break;
			case 13:
				for (int i = 444; i < 473; i++)
					found[i] = FALSE;
				break;
			case 14:
				for (int i = 473; i < 501; i++)
					found[i] = FALSE;
				break;
			case 15:
				for (int i = 501; i < 522; i++)
					found[i] = FALSE;
				break;
			case 16:
				for (int i = 522; i < 542; i++)
					found[i] = FALSE;
				break;
			case 17:
				for (int i = 542; i < 552; i++)
					found[i] = FALSE;
				break;
			}//ȯ�� ��� �����ϰ� ��� �湮ǥ���ϱ�
			shortest_path_t(s);
			print_path(s, e);
		}
		else { 
			mintransfer(u, v);
			//�ּ�ȯ���ϴ� ȣ������ �����´�
			d = fintransfer(u, v, lindex, way);
			//d - way�� �ε���
			way[d++] = u; 
			way[d] = v;
			//��߿��� �ִ� ȣ����, �������� �ִ� ȣ���� way�迭�� �־��ش�.
			for (int i = 0; i < MAX_SUBWAY; i++)
				found[i] = TRUE; //��� �湮�ߴٰ� �ʱ�ȭ���ְ�
			int j = 0;
			while (j <= d) { //way�� ����Ǿ��ִ� ȣ���� ���鸸 �湮 ���� �ʾҴٰ� ǥ���Ѵ�.
				switch (way[j++]) {
				case 0:
					for (int i = 0; i < 62; i++)
						found[i] = FALSE;
					break;
				case 1:
					for (int i = 62; i < 101; i++)
						found[i] = FALSE;
					break;
				case 2:
					for (int i = 101; i < 144; i++)
						found[i] = FALSE;
					break;
				case 3:
					for (int i = 144; i < 154; i++)
						found[i] = FALSE;
					break;
				case 4:
					for (int i = 154; i < 197; i++)
						found[i] = FALSE;
					break;
				case 5:
					for (int i = 197; i < 245; i++)
						found[i] = FALSE;
					break;
				case 6:
					for (int i = 245; i < 289; i++)
						found[i] = FALSE;
					break;
				case 7:
					for (int i = 289; i < 297; i++)
						found[i] = FALSE;
					break;
				case 8:
					for (int i = 297; i < 335; i++)
						found[i] = FALSE;
					break;
				case 9:
					for (int i = 335; i < 377; i++)
						found[i] = FALSE;
					break;
				case 10:
					for (int i = 377; i < 394; i++)
						found[i] = FALSE;
					break;
				case 11:
					for (int i = 394; i < 419; i++)
						found[i] = FALSE;
					break;
				case 12:
					for (int i = 419; i < 444; i++)
						found[i] = FALSE;
					break;
				case 13:
					for (int i = 444; i < 473; i++)
						found[i] = FALSE;
					break;
				case 14:
					for (int i = 473; i < 501; i++)
						found[i] = FALSE;
					break;
				case 15:
					for (int i = 501; i < 522; i++)
						found[i] = FALSE;
					break;
				case 16:
					for (int i = 522; i < 542; i++)
						found[i] = FALSE;
					break;
				case 17:
					for (int i = 542; i < 552; i++)
						found[i] = FALSE;
					break;
				}//ȯ�� ��� �����ϰ� ��� �湮ǥ���ϱ�
			}
			shortest_path_t(s); //�湮���� ���� ���鸸 Ȯ���ϸ鼭 �ִܰŸ� ����
			print_path(s, e); //������ path�� ���
		}
		break;
	}

	return 0;
}