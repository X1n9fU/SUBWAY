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
	char number[10]; //역의 번호
	char name[20]; //역의 이름
}snn;

typedef struct N {
	char name[20]; //
}n;

snn sub[MAX_SUBWAY]; //0부터 551까지 역의 이름과 번호 입력
int idx = 0; //인접행렬 만들때 사용될 index
int Subway[MAX_SUBWAY][MAX_SUBWAY]; //지하철 총 인접행렬
n transfer[MAX_SUBWAY][MAX_SUBWAY]; //'환승정보.csv'만 담을 배열

void subway_name() { //역의 
	FILE* NAME = fopen("역이름.csv", "r"); //역이름 파일을 가져온다
	if (NAME == NULL) { 
		printf("fail"); //못가져왔을시 fail
		return;
	}
	char buffer[100], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i , indx = 0, count=1;
	//i- 0이면 역번호를, 1이면 역이름을 가져온다.
	//indx - sub배열 인덱스
	//count - 헤더를 넘기고 다음줄부터 읽기 위해
	while (!feof(NAME)) {
		i = 0;
		fgets(buffer, 100, NAME); 
		//헤더를 읽을때에는 count=1이여서 넘어가고
		//다음줄부터 count=2가 되므로 역정보를 가져온다.
		if (count > 1) {
			info = strtok(buffer, ","); //역 번호는 ,를 기준으로 가져온다.
			while (info != NULL) { //info가 null일때까지
				if (i == 0) { //i가 0일때 역번호
					strcpy(sub[indx].number, info); //구조체 배열 sub의 number에 복사
				}
				else if (i == 1) { //i가 1일때 역이름
					strcpy(sub[indx].name, info); //구조체 배열 sub의 name에 복사
				}
				i++; 
				info = strtok(NULL, "\n");//역 이름은 \n를 기준으로 가져온다.
			}
			indx++; //구조체 배열 sub의 인덱스 증가
		}
		count++; //헤더를 넘기기 위해 존재
	}
	fclose(NAME); //파일 닫기
	//printf("name success\n"); //함수가 잘 돌아갔는지 확인
	return;
}

void init() {
	for (int i = 0; i < MAX_SUBWAY; i++)
		for (int j = 0; j < MAX_SUBWAY; j++)
			Subway[i][j] = INF; //총 인접행렬 INF로 초기화
	//printf("init success"); //잘 초기화 했는지 확인
}

void Line1() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = 0, j = 0, c = 0;
	idx = 0; //전역변수 idx 0부터 시작
	FILE* Line = fopen("1호선.csv", "r"); //1호선 파일 가져오기
	if (Line == NULL) {
		printf("fail"); //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line); //파일의 한 줄을 받는다.
			if (strlen(buffer) == 3) //마지막 \n가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ",");
				idx++; //날리면서 역의 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) { //토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = 0; j < idx-1; j++) { //idx 0~61 (열번호)
						Subway[i][j] = atoi(info); //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ","); //다음 토큰 받아오기
					}
					i++; //행 번호도 하나씩 올려준다.
				}
			c++; //헤더를 날리기 위한 변수
		}
		fclose(Line); //파일 닫기
		idx--; //맨 처음 역번호까지 세었으므로 하나 줄여준다.
	//	printf("Line1 success\n");
	}
}

void bLine1() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //전역변수 idx 62부터 시작
	FILE* Line = fopen("1지선.csv", "r"); //1지선 파일 가져오기
	if (Line == NULL) {
		printf("fail"); //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) {//Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line); //파일의 한 줄을 받는다.
			if (strlen(buffer) == 6) //마지막 enter가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ",");
				idx++;//날리면서 호선의 역 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) { //토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = fidx; j < idx - 1; j++) { //idx 62~100 (열번호)
						Subway[i][j] = atoi(info); //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ","); //다음 토큰 받아오기
					}
					i++; //행 번호도 하나씩 올려준다.
				}
			c++; //헤더를 날리기 위한 변수
		}
		fclose(Line);//파일 닫기
		idx--;  //맨 처음 역번호까지 세었으므로 하나 줄여준다.
	//	printf("bLine1 success");
	}
}

void Line2() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = idx, j = 0, c = 0;
	int fidx = idx; ////전역변수 idx 101부터 시작
	FILE* Line = fopen("2호선.csv", "r"); //2호선 파일 가져오기
	if (Line == NULL) {
		printf("fail"); //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line); //파일의 한 줄을 받는다.
			if (strlen(buffer) == 3) //마지막 enter가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ",");
				idx++;  //날리면서 역의 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) { //토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = fidx; j < idx - 1; j++) { //idx 101~143 (열번호)
						Subway[i][j] = atoi(info); //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ",");//다음 토큰 받아오기
					}
					i++; //행 번호도 하나씩 올려준다.
				}
			c++; //헤더를 날리기 위한 변수
		}
		fclose(Line); //파일 닫기
		idx--; //맨 처음 역번호까지 세었으므로 하나 줄여준다.
	//	printf("Line2 success");
	}
}

void bLine2() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //전역변수 idx 144부터 시작
	FILE* Line = fopen("2지선.csv", "r");  //2지선 파일 가져오기
	if (Line == NULL) {
		printf("fail");  //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) {  //Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line); //파일의 한 줄을 받는다.
			if (strlen(buffer) == 5) //마지막 enter가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ",");
				idx++; //날리면서 역의 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) { //토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = fidx; j < idx - 1; j++) { //idx 144~153 (열번호)
						Subway[i][j] = atoi(info); //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ","); //다음 토큰 받아오기
					}
					i++; //행 번호도 하나씩 올려준다.
				} 
			c++;  //헤더를 날리기 위한 변수
		}
		fclose(Line);//파일 닫기
		idx--;  //맨 처음 역번호까지 세었으므로 하나 줄여준다.
	//	printf("bLine2 success");
	}
}

void Line3() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //전역변수 idx 154부터 시작
	FILE* Line = fopen("3호선.csv", "r");  //3호선 파일 가져오기
	if (Line == NULL) {
		printf("fail"); //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line); //파일의 한 줄을 받는다.
			if (strlen(buffer) == 3) //마지막 enter가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ",");
				idx++; //날리면서 역의 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) { //토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = fidx; j < idx - 1; j++) { //idx 154~196 (열번호)
						Subway[i][j] = atoi(info);  //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ","); //다음 토큰 받아오기
					}
					i++; //행 번호도 하나씩 올려준다.
				}
			c++; //헤더를 날리기 위한 변수
		}
		fclose(Line); //파일 닫기
		idx--; //맨 처음 역번호까지 세었으므로 하나 줄여준다.
	//	printf("Line3 success");
	}
}

void Line4() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //전역변수 idx 197부터 시작
	FILE* Line = fopen("4호선.csv", "r"); //4호선 파일 가져오기
	if (Line == NULL) {  
		printf("fail"); //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line);  //파일의 한 줄을 받는다.
			if (strlen(buffer) == 3) //마지막 enter가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ","); 
				idx++; //날리면서 역의 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) {//토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = fidx; j < idx - 1; j++) { //idx  197~244 (열번호)
						Subway[i][j] = atoi(info);  //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ",");  //다음 토큰 받아오기
					} 
					i++; //행 번호도 하나씩 올려준다.
				}
			c++;  //헤더를 날리기 위한 변수
		}
		fclose(Line); //파일 닫기
		idx--; //맨 처음 역번호까지 세었으므로 하나 줄여준다.
	//	printf("Line4 success");
	}
}

void Line5() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //전역변수 idx 245부터 시작
	FILE* Line = fopen("5호선.csv", "r"); //5호선 파일 가져오기
	if (Line == NULL) {
		printf("fail"); //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line);  //파일의 한 줄을 받는다.
			if (strlen(buffer) == 3) //마지막 enter가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ",");
				idx++; //날리면서 역의 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) {//토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = fidx; j < idx - 1; j++) { //idx 245~288 (열번호)
						Subway[i][j] = atoi(info);  //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ",");  //다음 토큰 받아오기
					}
					i++; //행 번호도 하나씩 올려준다.
				}
			c++;  //헤더를 날리기 위한 변수
		}
		fclose(Line); //파일 닫기
		idx--; //맨 처음 역번호까지 세었으므로 하나 줄여준다.
	//	printf("Line5 success");
	}
}

void bLine5() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //전역변수 idx 289부터 시작
	FILE* Line = fopen("5지선.csv", "r"); //5지선 파일 가져오기
	if (Line == NULL) {
		printf("fail"); //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line);  //파일의 한 줄을 받는다.
			if (strlen(buffer) == 4) //마지막 enter가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ",");
				idx++; //날리면서 역의 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) {//토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = fidx; j < idx - 1; j++) { //idx  289~296 (열번호)
						Subway[i][j] = atoi(info);  //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ",");  //다음 토큰 받아오기
					}
					i++; //행 번호도 하나씩 올려준다.
				}
			c++;  //헤더를 날리기 위한 변수
		}
		fclose(Line); //파일 닫기
		idx--; //맨 처음 역번호까지 세었으므로 하나 줄여준다.
	//	printf("bLine5 success");
	}
}

void Line6() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //전역변수 idx 297부터 시작
	FILE* Line = fopen("6호선.csv", "r"); //6호선 파일 가져오기
	if (Line == NULL) {
		printf("fail"); //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line);  //파일의 한 줄을 받는다.
			if (strlen(buffer) == 3) //마지막 enter가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ",");
				idx++; //날리면서 역의 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) {//토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = fidx; j < idx - 1; j++) { //idx  297~334 (열번호)
						Subway[i][j] = atoi(info);  //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ",");  //다음 토큰 받아오기
					}
					i++; //행 번호도 하나씩 올려준다.
				}
			c++;  //헤더를 날리기 위한 변수
		}
		fclose(Line); //파일 닫기
		idx--; //맨 처음 역번호까지 세었으므로 하나 줄여준다.
	//	printf("Line6 success");
	}
}

void Line7() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //전역변수 idx 335부터 시작
	FILE* Line = fopen("7호선.csv", "r"); //7호선 파일 가져오기
	if (Line == NULL) {  
		printf("fail"); //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line);  //파일의 한 줄을 받는다.
			if (strlen(buffer) == 3) //마지막 enter가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ","); 
				idx++; //날리면서 역의 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) {//토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = fidx; j < idx - 1; j++) { //idx  335~376 (열번호)
						Subway[i][j] = atoi(info);  //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ",");  //다음 토큰 받아오기
					} 
					i++; //행 번호도 하나씩 올려준다.
				}
			c++;  //헤더를 날리기 위한 변수
		}
		fclose(Line); //파일 닫기
		idx--; //맨 처음 역번호까지 세었으므로 하나 줄여준다.
	//	printf("Line7 success");
	}
}

void Line8() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //전역변수 idx 377부터 시작
	FILE* Line = fopen("8호선.csv", "r"); //8호선 파일 가져오기
	if (Line == NULL) {
		printf("fail"); //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line);  //파일의 한 줄을 받는다.
			if (strlen(buffer) == 3) //마지막 enter가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ",");
				idx++; //날리면서 역의 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) {//토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = fidx; j < idx - 1; j++) { //idx  377~393 (열번호)
						Subway[i][j] = atoi(info);  //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ",");  //다음 토큰 받아오기
					}
					i++; //행 번호도 하나씩 올려준다.
				}
			c++;  //헤더를 날리기 위한 변수
		}
		fclose(Line); //파일 닫기
		idx--; //맨 처음 역번호까지 세었으므로 하나 줄여준다.
	//	printf("Line8 success");
	}
}

void Line9() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //전역변수 idx 394부터 시작
	FILE* Line = fopen("9호선.csv", "r"); //9호선 파일 가져오기
	if (Line == NULL) {
		printf("fail"); //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line);  //파일의 한 줄을 받는다.
			if (strlen(buffer) == 3) //마지막 enter가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ",");
				idx++; //날리면서 역의 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) {//토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = fidx; j < idx - 1; j++) { //idx  394~418 (열번호)
						Subway[i][j] = atoi(info);  //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ",");  //다음 토큰 받아오기
					}
					i++; //행 번호도 하나씩 올려준다.
				}
			c++;  //헤더를 날리기 위한 변수
		}
		fclose(Line); //파일 닫기
		idx--; //맨 처음 역번호까지 세었으므로 하나 줄여준다.
	//	printf("Line9 success");
	}
}

void BdLine() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //전역변수 idx 419부터 시작
	FILE* Line = fopen("분당선.csv", "r"); //분당선 파일 가져오기
	if (Line == NULL) {
		printf("fail"); //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line);  //파일의 한 줄을 받는다.
			if (strlen(buffer) == 4) //마지막 enter가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ",");
				idx++; //날리면서 역의 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) {//토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = fidx; j < idx - 1; j++) { //idx 419~ 443 (열번호)
						Subway[i][j] = atoi(info);  //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ",");  //다음 토큰 받아오기
					}
					i++; //행 번호도 하나씩 올려준다.
				}
			c++;  //헤더를 날리기 위한 변수
		}
		fclose(Line); //파일 닫기
		idx--; //맨 처음 역번호까지 세었으므로 하나 줄여준다.
	//	printf("BdLine success\n");
	}
}

void ILine1() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //전역변수 idx 444부터 시작
	FILE* Line = fopen("인천1선.csv", "r"); //인천1호선 파일 가져오기
	if (Line == NULL) {
		printf("fail"); //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line);  //파일의 한 줄을 받는다.
			if (strlen(buffer) == 4) //마지막 enter가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ",");
				idx++; //날리면서 역의 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) {//토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = fidx; j < idx - 1; j++) { //idx  444~472 (열번호)
						Subway[i][j] = atoi(info);  //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ",");  //다음 토큰 받아오기
					}
					i++; //행 번호도 하나씩 올려준다.
				}
			c++;  //헤더를 날리기 위한 변수
		}
		fclose(Line); //파일 닫기
		idx--; //맨 처음 역번호까지 세었으므로 하나 줄여준다.
	//	printf("ILine1 success\n");
	}
}

void CLine() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //전역변수 idx 473부터 시작
	FILE* Line = fopen("중앙선.csv", "r"); //중앙선 파일 가져오기
	if (Line == NULL) {
		printf("fail"); //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line);  //파일의 한 줄을 받는다.
			if (strlen(buffer) == 4) //마지막 enter가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ",");
				idx++; //날리면서 역의 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) {//토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = fidx; j < idx - 1; j++) { //idx  473~500 (열번호)
						Subway[i][j] = atoi(info);  //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ",");  //다음 토큰 받아오기
					}
					i++; //행 번호도 하나씩 올려준다.
				}
			c++;  //헤더를 날리기 위한 변수
		}
		fclose(Line); //파일 닫기
		idx--; //맨 처음 역번호까지 세었으므로 하나 줄여준다.
	//	printf("CLine success");
	}
}

void GcLine() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //전역변수 idx 501부터 시작
	FILE* Line = fopen("경춘선.csv", "r"); //경춘선 파일 가져오기
	if (Line == NULL) {
		printf("fail"); //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line);  //파일의 한 줄을 받는다.
			if (strlen(buffer) == 4) //마지막 enter가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ",");
				idx++; //날리면서 역의 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) {//토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = fidx; j < idx - 1; j++) { //idx  501~521 (열번호)
						Subway[i][j] = atoi(info);  //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ",");  //다음 토큰 받아오기
					}
					i++; //행 번호도 하나씩 올려준다.
				}
			c++;  //헤더를 날리기 위한 변수
		}
		fclose(Line); //파일 닫기
		idx--; //맨 처음 역번호까지 세었으므로 하나 줄여준다.
	//	printf("GcLine success\n");
	}
}

void GuLine() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //전역변수 idx 522부터 시작
	FILE* Line = fopen("경의선.csv", "r"); //경의선 파일 가져오기
	if (Line == NULL) {
		printf("fail"); //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line);  //파일의 한 줄을 받는다.
			if (strlen(buffer) == 4) //마지막 enter가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ",");
				idx++; //날리면서 역의 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) {//토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = fidx; j < idx - 1; j++) { //idx  522~541 (열번호)
						Subway[i][j] = atoi(info);  //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ",");  //다음 토큰 받아오기
					}
					i++; //행 번호도 하나씩 올려준다.
				}
			c++;  //헤더를 날리기 위한 변수
		}
		fclose(Line); //파일 닫기
		idx--; //맨 처음 역번호까지 세었으므로 하나 줄여준다.
	//	printf("GuLine success\n");
	}
}

void AirLine() {
	char buffer[MAX_SUBWAY], * info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = idx, j = 0, c = 0;
	int fidx = idx; //전역변수 idx 542부터 시작
	FILE* Line = fopen("공항철도.csv", "r"); //공항철도 파일 가져오기
	if (Line == NULL) {
		printf("fail"); //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) { //Line이 null일때까지
			fgets(buffer, MAX_SUBWAY, Line);  //파일의 한 줄을 받는다.
			if (strlen(buffer) == 3) //마지막 enter가 있어 끝에 도달했다고 뜨지 않음 따라서 길이로 따져서 while문을 나올 수 있게 함
				break;
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (c == 0 && info != NULL) { //헤더 날리기
				info = strtok(NULL, ",");
				idx++; //날리면서 역의 개수 세기 
			}
			if (c > 0) //헤더 날리고 다음 줄부터 이곳으로 온다.
				while (info != NULL) {//토큰이 null일때 까지
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로의 길이가 나온다.
					for (j = fidx; j < idx - 1; j++) { //idx 542~551 (열번호)
						Subway[i][j] = atoi(info);  //길이 토큰을 총 인접행렬에 차곡차곡 넣는다.
						info = strtok(NULL, ",");  //다음 토큰 받아오기
					}
					i++; //행 번호도 하나씩 올려준다.
				}
			c++;  //헤더를 날리기 위한 변수
		}
		fclose(Line); //파일 닫기
		idx--; //맨 처음 역번호까지 세었으므로 하나 줄여준다.
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
	//데이터들을 넣는 함수
}

void Transfer() {
	char buffer[INF],*info;
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = 0, j = 0;
	int index = 0,xidx=0,yidx=0;
	char *x, *y;
	FILE* Line = fopen("환승정보.csv", "r");  //환승정보 파일 가져오기
	if (Line == NULL) {
		printf("fail");   //가져오기 실패한 경우 fail출력
		exit(0);
	}
	else {
		while (!feof(Line)) {  //Line이 null일때까지
			fgets(buffer, INF, Line);  //파일의 한 줄을 받는다.
			j = 0;  //열 번호 초기화
			info = strtok(buffer, ","); //,를 기준으로 토큰 가져오기 -> 역번호가 나온다
			while (info != NULL) { //토큰이 null일때 까지
				strcpy(transfer[i][j].name,info); //환승정보만 넣을 배열에 차곡차곡 넣는다.
				if (j == 149) { //마지막에는 \n가 있어서 
					info = strtok(NULL, "\n"); //\n로 끊어준다.
				}
				else {
					info = strtok(NULL, ","); //,를 기준으로 토큰 가져오기 -> 경로 길이
				}
				j++; //열 번호 하나씩 올려준다.
			}
			i++; //행 번호 하나씩 올려준다.
		}
		fclose(Line); //파일 닫기

	}
	for (int k = 1; k <= i; k++)
		for (j = 1; j <= i; j++) {
			int t = atoi(transfer[k][j].name); //역 정보를 빼고 거리정보만 빼서 t에 넣는다 그래서 행, 열 1부터 시작
			if (t != INF && t!=0 ) { //t가 9999와 0이 아니면
				x = transfer[k][0].name; 
				y = transfer[0][j].name; //그 지점이 어디서 어디로 가는 지점인지 알기위해
				//그 지점의 처음 행(k,0)과 열(0,j)을 꺼내서 x,y에 넣어준다. 
				index = 0;
				while (index < MAX_SUBWAY) { 
					if (strcmp(sub[index].number,x)==0)
						xidx = index; 
					if (strcmp(sub[index].number,y)==0)
						yidx = index;
					index++;
				}
				//지하철역을 0~551인덱스로 표현한 배열을 가져와 모든 역을 하나씩 비교하면서
				//x,y와 역번호가 같은 인덱스를 가져온다.
				//그 인덱스를 xidx,yidx에 넣어준다.
				Subway[xidx][yidx] = t;
				//인접행렬에 해당되는 그 지점에 t값을 넣어준다.
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
} //해당 인덱스의 역이 몇호선에 있는 역인지 구별하는 함수

int distance[MAX_SUBWAY]; /* 시작정점으로부터의 최단경로 거리 */
int found[MAX_SUBWAY]; /* 방문한 역 표시 */
int path[MAX_SUBWAY]; /*길 표시*/
int visited[MAX_LINE]; /*방문된 정점(호선) 표시*/

typedef struct GraphNode {
	int vertex; //호선 번호를 정점으로 놓기
	struct GraphNode* link; 
}GraphNode;

GraphNode *subway[MAX_LINE]; //호선에서 환승할 수 있는 호선들을 연결한 인접리스트


// 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
void insert_edge(int u, int v)
{
	GraphNode* node;
	if (u >= MAX_LINE || v >= MAX_LINE) //u,v가 호선들 중 존재하지 않으면 오류
	{
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v; //호선 넣기
	node->link = subway[u]; //시작 호선의 리스트를 가져와서
	subway[u] = node; //해당 호선을 연결해준다.

	//인접리스트를 연결하는 과정
}


int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX; 
	minpos = -1;
	//최소길이, 인덱스 초기화
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) { //방문하지 않은 역이면서 길이가 최소인 곳이 있으면
			min = distance[i]; //그 길이로 min 업데이트
			minpos = i; //그 곳의 인덱스로 minpos 업데이트
		}
	return minpos; //최소 거리가 담긴 인덱스 반환
}

void shortest_path(int start)
{
	int i, u, w;
	for (i = 0; i < MAX_SUBWAY; i++) /* 초기화 */
	{
		path[i] = start;
		distance[i] = Subway[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE; /* 시작 정점 방문 표시 */
	distance[start] = 0;
	path[start] = -1; //시작하는 곳 -1
	for (i = 0; i < MAX_SUBWAY - 1; i++) {
		u = choose(distance, MAX_SUBWAY, found); //최소값이 있는 인덱스
		found[u] = TRUE; //방문 표시
		for (w = 0; w < MAX_SUBWAY; w++)
			if (!found[w])
				if (distance[u] + Subway[u][w] < distance[w]) { //해당 역을 지나서 가는 곳이 해당 숫자보다 작으면
					distance[w] = distance[u] + Subway[u][w]; //업데이트
					path[w] = u; //경로 저장
				}
	}
}

void shortest_path_t(int start) {
	int i, u, w;
	for (i = 0; i < MAX_SUBWAY; i++) /* 초기화 */
	{
		path[i] = start;
		distance[i] = Subway[start][i];
	}
	found[start] = TRUE; /* 시작 정점 방문 표시 */
	distance[start] = 0;
	path[start] = -1; //시작하는 곳 -1
	for (i = 0; i < MAX_SUBWAY - 1; i++) {
		u = choose(distance, MAX_SUBWAY, found); //최소값이 있는 인덱스
		found[u] = TRUE; //방문 표시
		for (w = 0; w < MAX_SUBWAY; w++)
			if (!found[w])
				if (distance[u] + Subway[u][w] < distance[w]) { //해당 역을 지나서 가는 곳이 해당 거리보다 짧으면
					distance[w] = distance[u] + Subway[u][w]; //업데이트
					path[w] = u; //경로 저장
				}
	}
}

void print_path(int start, int end) {
	int result[MAX_SUBWAY]; //결과를 넣을 배열
	int k = end; //도착역을 넣는다.
	int index=0, time = 0, m = 0,tr=0; 
	//index- 출발역이 있는 인덱스를 넣을 변수
	//time - 환승을 제외한 걸리는 시간
	//tr - 환승시간
	char *line=(char*)malloc(sizeof(char)); //호선정보를 넣을 변수
	for (int i = 0; i < MAX_SUBWAY; i++) {
		result[i] = k; 
		int tmp = path[k];
		if (tmp == -1) {//-1이면 출발역에 도달한것
			index = i; //출발역이 있는 인덱스
			break;
		}
		k = tmp;
	} //result배열에 도착역부터 출발역 순으로 path배열을 돌려가면서 지나온 경로를 저장한다.

	for (int num = index; num >=0; num--) { //result배열에 출발역부터 도착역까지 거꾸로 저장되어있다. 
		//그러니 index를 하나씩 줄여가면서 for문 진행
		int j = result[num]; //result배열에서 해당 인덱스에 있는 정보는 역의 인덱스
		if (j >= 0 && j < 62)
			strcpy(line, "1호선");
		else if (j < 101)
			strcpy(line, "1지선");
		else if (j < 144)
			strcpy(line, "2호선");
		else if (j < 154)
			strcpy(line, "2지선");
		else if (j < 197)
			strcpy(line, "3호선");
		else if (j < 245)
			strcpy(line, "4호선");
		else if (j < 289)
			strcpy(line, "5호선");
		else if (j < 297)
			strcpy(line, "5지선");
		else if (j < 335)
			strcpy(line, "6호선");
		else if (j < 377)
			strcpy(line, "7호선");
		else if (j < 394)
			strcpy(line, "8호선");
		else if (j < 419)
			strcpy(line, "9호선");
		else if (j < 444)
			strcpy(line, "분당선");
		else if (j < 473)
			strcpy(line, "인천1호선");
		else if (j < 501)
			strcpy(line, "중앙선");
		else if (j < 522)
			strcpy(line, "경춘선");
		else if (j < 542)
			strcpy(line, "경의선");
		else if (j < 552)
			strcpy(line, "공항철도");
		//역의 인덱스에 따라 어떤 호선인지 line 변수에 저장
		m++; //정거장 수를 세기 위한 변수
		if (num==0)//인덱스가 끝에 도달하면 도착으로 출력
			printf("-><%s> %s <도착>\n", line, sub[j].name); //호선과 역 출력
		else if (strcmp(sub[j].name, sub[result[num-1]].name) == 0) {
			//환승역에 도착하면 역이 두개가 출력되므로
			//현재 역이름과 다음의 역 이름이 같을때 if문에 들어온다
			if (num == index) { //환승역이 출발역이면?
				continue; //역 두개가 같은 이름이므로 다음 인덱스부터 출력하게 한다.
			}
			if (num - 1 == 0) { //도착역이면?
				printf("-><%s> %s <도착>\n", line, sub[j].name); //마지막 호선과 역 출력
				break; //다음 정보는 같은 환승역 정보이므로 출력하지 않고 반복문을 빠져나온다.
			}
			
				int ran = rand() % Subway[result[num-1]][j] + 1; //인접행렬에서 해당 인덱스에 있는 숫자로
				//1~(해당숫자)의 난수 발생
				tr = tr + ran; //환승시간에 난수 더하기
				strcpy(line, "환승 : 소요시간");
				printf("-><%s %d 분> %s\n", line, ran, sub[j].name); //환승 몇분 걸리는지 출력
				num--; //그냥 넘어가면 환승역이 한번더 출려되므로 num을 하나 더 줄여서 넘어가게 한다.
			
		}
		else { //도착하기 전
			time = time + Subway[j][result[num-1]]; //해당 인덱스에 있는 숫자를 시간에 더해준다.
			printf("-><%s> %s\n", line, sub[j].name); //호선과 역 출력
		}
	}
	printf("소요시간 : %d (%d + 환승 소요시간 : %d) 분\n",time+tr,time,tr); //걸린 시간 출력
	printf("정거장 수 : %d개", m); //정거장 수 출력
}

void make_list() {
	for (int v = 0; v < MAX_LINE; v++)
		subway[v] = NULL; //호선 인접리스트를 초기화하는 과정
	char buffer[INF], * info; 
	//한줄을 담을 buffer배열, 토큰을 담을 info
	int i = 0, j = 0;
	int index, xidx = 0, yidx = 0;
	//xidx - 해당 위치의 첫 행의 역번호를 인덱스로 바꿔 저장한 변수
	//yidx - 해당 위치의 첫 열의 역번호를 인덱스로 바꿔 저장한 변수
	char* x, * y;

	for (int k = 1; k < MAX_TRANSFER; k++)
		for (j = 1; j < MAX_TRANSFER; j++) { 
			int t = atoi(transfer[k][j].name); //역 정보를 빼고 거리정보만 빼서 t에 넣는다
			if (t != INF && t != 0) { //t가 9999와 0이 아니면
				x = transfer[k][0].name;
				y = transfer[0][j].name; //그 지점이 어디서 어디로 가는 지점인지 알기위해
				//그 지점의 처음 행과 열을 꺼내서 x,y에 넣어준다. 
				index = 0;
				while (index < MAX_SUBWAY) {
					if (strcmp(sub[index].number, x) == 0)
						xidx = index;
					if (strcmp(sub[index].number, y) == 0)
						yidx = index;
					index++;
				}
				//지하철역을 0~551인덱스로 표현한 배열을 가져와 하나씩 비교하면서
				//같으면 그 인덱스를 xidx,yidx에 넣어준다.
				xidx = numbering(xidx);
				yidx = numbering(yidx);
				//그 인덱스가 몇호선인지를 구별한다. (1~18)
				insert_edge(xidx, yidx); //xidx호선 인접리스트에
				//yidx edge를 추가한다.
			}
		}	
}

int pass[MAX_LINE]; //도착역이 있는 호선을 찾으면서 지나치는 호선들을 모두 넣을 배열
int lindex = 0;

int mintransfer(int s, int e) {

	GraphNode* w;
	//역 인덱스로 호선 번호 불러오기
	visited[s] = TRUE; // 정점 v의 방문 표시
	//printf("정점 %d -> ", s); // 방문한 정점 출력
	for (w = subway[s]; w; w = w->link)// 인접 정점 탐색
		if (w->vertex == e) { //해당 인접리스트에 도착역이 있는 호선이 있으면
			pass[lindex]= w->vertex; //index배열에 호선정보를 넣는다
			return e; 
		}
	if (w == NULL) { //도착하는 호선이 없다면
		for (w = subway[s]; w; w = w->link) {
			if (!visited[w->vertex]) {
				pass[lindex++] = w->vertex; //그 인접리스트에 방문하지 않은 호선이 있으면

				//index에 그 호선 정보를 넣고
				//그 호선을 시작으로 하는 인접리스트가기 (재귀함수 돌리기)
				if (mintransfer(w->vertex, e) == e)
					return e; //원하는 호선을 발견하면 바로 재귀함수 모두 빠져나오기
			}
		}
	}
}

int fintransfer(int s, int e, int t, int sta[10]) {
	GraphNode* w;
	int j = 0;
	t = t - 1;
	while (t > -1) { //t가 0이 될때까지
		for (w = subway[s]; w; w = w->link) {
			if (w->vertex == pass[t]) {
				sta[j] = w->vertex;
				return j+1;
				//출발역이 있는 호선에 도착역이 있는 호선을 가기 전의 호선이 있는지 확인
				//있으면 sta배열에 넣는다.
				//해당 인덱스+1을 반환
			}
		}	
		sta[j++] = pass[t--];
		//없으면 sta배열에 넣고
		//그 전전 호선이 있는지 확인하기 위해 index배열의 인덱스를 하나 줄여준다.

	}
	//그럼 현재 sta배열에는 출발역에서 도착역으로 갈때 지나치는 호선들이 저장되어있다
}

int main(void)
{
	subway_name(); //전역 구조체 배열 변수 sub에 역 이름과 번호를 넣어준다.
	//역 이름 번호 인덱스로 구별하기
	init();
	putData();
	//역 별로 데이터 2차원 배열에 넣기
	Transfer();
	//환승정보 2차원 배열에 넣기
	printf("\n");

	char start[50];
	char end[50];
	int i,j, s = -1, e = -1, num=0;
	//s,e - 역의 인덱스
	//num - 방식 번호
	int u, v, d;
	//u-출발역이 있는 호선
	//v-도착역이 있는 호선
	//d-인덱스를 받는 변수
	int way[10] = { '\0' };
	//지나치는 호선을 담을 배열
	int cmp1=1, cmp2=1;
	//역 이름이 제대로 되었는지 확인하는 변수
	printf("출발역을 입력해주세요: ");
	scanf("%s",start);
	printf("도착역을 입력해주세요: ");
	scanf("%s", end);

	while (cmp1 == 1 || cmp2 == 1 || s==e) { //입력이 제대로 안되었을경우 다시 작성하기
		cmp1 = 1; cmp2 = 1; //다시 1로 초기화
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
		//역 이름이 제대로 입력되었으면 cmp1,cmp2가 0으로 변하지만 아닐경우 1이 유지됌
		if (cmp1 == 1 || cmp2 == 1) {
			printf("<역 이름이 잘못되었습니다! 다시 입력해주세요!>\n\n");
			printf("출발역을 입력해주세요: ");
			scanf("%s", start);

			printf("도착역을 입력해주세요: ");
			scanf("%s", end);
		}
		if (cmp1==0 && cmp2==0 && s == e) { //둘다 입력이 잘 되었지만 역 이름이 같을경우
			printf("\n<출발역과 도착역이 같습니다! 다시 입력해주세요!>\n\n");
			printf("출발역을 입력해주세요: ");
			scanf("%s", start);

			printf("도착역을 입력해주세요: ");
			scanf("%s", end);
		}
	}	
	printf("방식? 1.최단경로 2.최소환승\n:");
	scanf("%d", &num);

	switch (num) {
	case 1: //최단경로 출력
		shortest_path(s);
		printf("최단경로\n<출발>\n");
		print_path(s, e);
		break;
	case 2: //최소환승 출력
		make_list(); //환승 인접리스트 만들기
		u = numbering(s);
		v = numbering(e);
		//출발역과 도착역을 호선으로 바꿔주기
		for (int i = 0; i < MAX_SUBWAY; i++) found[i] = TRUE;
		if (u == v) { //같은 호선이면 최단거리=최소환승
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
			}//환승 경로 제외하고 모두 방문표시하기
			shortest_path_t(s);
			print_path(s, e);
		}
		else { 
			mintransfer(u, v);
			//최소환승하는 호선들을 가져온다
			d = fintransfer(u, v, lindex, way);
			//d - way의 인덱스
			way[d++] = u; 
			way[d] = v;
			//출발역이 있는 호선과, 도착역이 있는 호선을 way배열에 넣어준다.
			for (int i = 0; i < MAX_SUBWAY; i++)
				found[i] = TRUE; //모두 방문했다고 초기화해주고
			int j = 0;
			while (j <= d) { //way에 저장되어있는 호선의 역들만 방문 하지 않았다고 표시한다.
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
				}//환승 경로 제외하고 모두 방문표시하기
			}
			shortest_path_t(s); //방문하지 않은 역들만 확인하면서 최단거리 생성
			print_path(s, e); //생성된 path를 출력
		}
		break;
	}

	return 0;
}