#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

void start(); //'초기화면'함수
void join(); //'회원가입'함수
void login(); //'로그인'함수
void NonMem(); //비회원 전용 함수
void menu(int * cnt);  //'메인메뉴'함수
void Park(int * cnt);  //'주차하기'함수
void ShowPark(int * cnt); //'주차현황'보기
void NonMemShowPark();  //비회원 전용 주차현황보기 함수
void Service(int * cnt); //'상품주문'함수
void AdmPhone(int * cnt); //'관리자 연락처'함수
void CheckOut(int * cnt); //'계산하기'함수
void RoadStat(int * cnt); //'주변도로상황'함수
void ParkSearch(int * cnt); //'주변주차장 검색'함수
void ParkFee(int * cnt); //'주차요금 보기'함수
void NonMemParkFee(); //비회원 전용 주차요금 보기 함수
void TimeNow(int * cnt); //'현재시간'함수
void Admin(); //'관리자 전용 메뉴' 함수
void AdminMenu(int * cnt); //관리자 전용 메뉴
void AdjAdmin(int * cnt); //관리자 추가 및 수정
void ShowMember(int * cnt); //회원 조회
void DelMember(int * cnt); //회원 삭제
void Income(int * cnt); //수입내역조회
void AddAdmin(int * cnt); //관리자 추가
void DelAdmin(int * cnt); //관리자 삭제
void ChangeGradeAdmin(int * cnt); //관리자 등급 변경
int Re_Check(char memid[20], int * pt);

int PerFee=8000; //주차요금은 전역변수로 선언하여 이 변수만 수정하면 프로그램내에 쓰인 모든 주차요금정보가 갱신된다.
int CarWash=25000, Tire=35000, Refuel=1935;

int main(void)
{
	start();   //start(초기화면)함수 호출
	return 0;
}

void start()
{
	int i;
	system("cls");
	printf("\n\n\n\n\n");
	printf("######################################");
	printf("#######################################\n");
	printf("##									   ##\n");
	printf("##									   ##\n");
	printf("##	주	차	장	관	리	 A 	 P	 P	   ##\n");
	printf("##									   ##\n");
	printf("##									   ##\n");
	printf("######################################");
	printf("#######################################\n");
	printf("\n\n\n\n\n");

	printf("1. 회원가입 \n2. 로그인 \n3. 비회원\n4. 관리자로그인\n5. 종료\n\n");
	printf("Choose: ");
	scanf("%d", &i);  //메뉴의 번호를 받아 변수 i에 저장
	if (i==1) //사용자가 입력한 메뉴의 번호에 맞는 함수 호출
		join();
	else if(i==2)
		login();
	else if(i==3)
		NonMem();
	else if(i==4)
		Admin();
	else if(i==5)
		exit(0);
	else
	{
		puts("유효한 메뉴가 아닙니다.");  //1~4가 아닌 숫자를 입력할 경우 다음과 같은 메세지 출력 후 start함수 재 호출
		puts("Press any key to refresh");
		getch();
		system("cls");
		start();
	}
}

void join()
{
	typedef struct member //회원가입을 받기 위한 회원 정보 구조체
	{
		char id[15];
		char pw[20];
		int carnum;
		char phon[15];
		int order;
	}Member;

	FILE * fp=fopen("member.txt", "at");
	int ret, cnt;
	char exit[]="exit";
	
	Member mem;
	system("cls");
	puts("---------- 회원가입 ----------");
	puts("10자이하의 영문/숫자 조합의 아이디를 입력하십시오.");
	puts("아이디 또는 비밀번호 입력칸에 'exit'라고 입력하면 초기화면으로 이동");
	while(1)
	{
		mem.id[0]=0;mem.id[1]=0;mem.id[2]=0;mem.id[3]=0;mem.id[4]=0;mem.id[5]=0;mem.id[6]=0;mem.id[7]=0;mem.id[8]=0;
		mem.id[9]=0;mem.id[10]=0;mem.id[11]=0;mem.id[12]=0;mem.id[13]=0;mem.id[14]=0;// 각각의 배열요소 초기화...
		printf("아이디: "); scanf("%s", mem.id);
		ret=Re_Check(mem.id, &cnt);//입력받은 아이디를 Re_Check함수로 기존의 회원중 동일한 아이디가 있는지 중복 검사
		if((mem.id[10]>47&&mem.id[10]<58)||(mem.id[10]>64&&mem.id[10]<91)||(mem.id[10]>96&&mem.id[10]<123))
		{   //11번째 배열 요소가 널값이 아닌 알파뱃이나 숫자값을 가지고 있으면 10자를 초과한 것으로 판정
			puts("아이디가 10자를 초과하였습니다.");
			continue;
		}
		else if (!strcmp(mem.id, exit))
		{
			puts("초기화면으로 이동");
			getch();
			start();
		}
		else if(!((mem.id[0]>='0'&&mem.id[0]<='9')||(mem.id[0]>='A'&&mem.id[0]<='Z')||(mem.id[0]>='a'&&mem.id[0]<='z'))
			||!((mem.id[1]>='0'&&mem.id[1]<='9')||(mem.id[1]>='A'&&mem.id[1]<='Z')||(mem.id[1]>='a'&&mem.id[1]<='z')||(mem.id[1]==0))
			||!((mem.id[2]>='0'&&mem.id[2]<='9')||(mem.id[2]>='A'&&mem.id[2]<='Z')||(mem.id[2]>='a'&&mem.id[2]<='z')||(mem.id[2]==0)||(mem.id[2]==-52))
			||!((mem.id[3]>='0'&&mem.id[3]<='9')||(mem.id[3]>='A'&&mem.id[3]<='Z')||(mem.id[3]>='a'&&mem.id[3]<='z')||(mem.id[3]==0)||(mem.id[3]==-52))
			||!((mem.id[4]>='0'&&mem.id[4]<='9')||(mem.id[4]>='A'&&mem.id[4]<='Z')||(mem.id[4]>='a'&&mem.id[4]<='z')||(mem.id[4]==0)||(mem.id[4]==-52))
			||!((mem.id[5]>='0'&&mem.id[5]<='9')||(mem.id[5]>='A'&&mem.id[5]<='Z')||(mem.id[5]>='a'&&mem.id[5]<='z')||(mem.id[5]==0)||(mem.id[5]==-52))
			||!((mem.id[6]>='0'&&mem.id[6]<='9')||(mem.id[6]>='A'&&mem.id[6]<='Z')||(mem.id[6]>='a'&&mem.id[6]<='z')||(mem.id[6]==0)||(mem.id[6]==-52))
			||!((mem.id[7]>='0'&&mem.id[7]<='9')||(mem.id[7]>='A'&&mem.id[7]<='Z')||(mem.id[7]>='a'&&mem.id[7]<='z')||(mem.id[7]==0)||(mem.id[7]==-52))
			||!((mem.id[8]>='0'&&mem.id[8]<='9')||(mem.id[8]>='A'&&mem.id[8]<='Z')||(mem.id[8]>='a'&&mem.id[8]<='z')||(mem.id[8]==0)||(mem.id[8]==-52))
			||!((mem.id[9]>='0'&&mem.id[9]<='9')||(mem.id[9]>='A'&&mem.id[9]<='Z')||(mem.id[9]>='a'&&mem.id[9]<='z')||(mem.id[9]==0)||(mem.id[9]==-52)))
		{  //아이디에 영문/숫자가 아닌 다른 문자가 있는지 검사
			puts("아이디는 영문/숫자 조합으로만 생성할 수 있습니다.");
			continue;
		}
		else if(mem.id[0]==48&&mem.id[1]==0)
		{
			puts("아이디로 숫자 0은 사용할 수 없습니다.");//나중에 회원 삭제시에 회원의 모든 정보를 0으로 초기화 시킬것을
			continue;                                  //염두에 둔 조건
		}
		else if (ret)  //Re_Check함수의 반환값에 따라 아이디 중복여부 판별
		{
			puts("사용할 수 있는 아이디 입니다.");
			break;
		}
		else
		{
			puts("이미 사용중인 아이디 입니다.");
			continue;
		}
		
	}
	puts("15자이하의 영문/숫자 조합으로 비밀번호를 입력하십시오.");
	while(1)
	{
		mem.pw[1]=0;mem.pw[2]=0;mem.pw[3]=0;mem.pw[4]=0;mem.pw[5]=0;mem.pw[6]=0;mem.pw[7]=0;mem.pw[8]=0;mem.pw[9]=0;mem.pw[10]=0;
		mem.pw[11]=0;mem.pw[12]=0;mem.pw[13]=0;mem.pw[14]=0;mem.pw[15]=0;mem.pw[16]=0;mem.pw[17]=0;mem.pw[18]=0;mem.pw[19]=0;mem.pw[0]=0;
		printf("비밀번호: "); scanf("%s", mem.pw);
		if((mem.pw[15]>47&&mem.pw[15]<58)||(mem.pw[15]>64&&mem.pw[15]<91)||(mem.pw[15]>96&&mem.pw[15]<123))
		{//아이디와 마찬가지로 16번째 배열요소 검사
			puts("비밀번호가 15자를 초과하였습니다.");
			continue;
		}
		else if (!strcmp(mem.pw, exit))
		{
			puts("초기화면으로 이동");
			getch();
			start();
		}
		else if(!((mem.pw[0]>='0'&&mem.pw[0]<='9')||(mem.pw[0]>='A'&&mem.pw[0]<='Z')||(mem.pw[0]>='a'&&mem.pw[0]<='z'))
			||!((mem.pw[1]>='0'&&mem.pw[1]<='9')||(mem.pw[1]>='A'&&mem.pw[1]<='Z')||(mem.pw[1]>='a'&&mem.pw[1]<='z')||(mem.pw[1]==0))
			||!((mem.pw[2]>='0'&&mem.pw[2]<='9')||(mem.pw[2]>='A'&&mem.pw[2]<='Z')||(mem.pw[2]>='a'&&mem.pw[2]<='z')||(mem.pw[2]==0)||(mem.pw[2]==-52))
			||!((mem.pw[3]>='0'&&mem.pw[3]<='9')||(mem.pw[3]>='A'&&mem.pw[3]<='Z')||(mem.pw[3]>='a'&&mem.pw[3]<='z')||(mem.pw[3]==0)||(mem.pw[3]==-52))
			||!((mem.pw[4]>='0'&&mem.pw[4]<='9')||(mem.pw[4]>='A'&&mem.pw[4]<='Z')||(mem.pw[4]>='a'&&mem.pw[4]<='z')||(mem.pw[4]==0)||(mem.pw[4]==-52))
			||!((mem.pw[5]>='0'&&mem.pw[5]<='9')||(mem.pw[5]>='A'&&mem.pw[5]<='Z')||(mem.pw[5]>='a'&&mem.pw[5]<='z')||(mem.pw[5]==0)||(mem.pw[5]==-52))
			||!((mem.pw[6]>='0'&&mem.pw[6]<='9')||(mem.pw[6]>='A'&&mem.pw[6]<='Z')||(mem.pw[6]>='a'&&mem.pw[6]<='z')||(mem.pw[6]==0)||(mem.pw[6]==-52))
			||!((mem.pw[7]>='0'&&mem.pw[7]<='9')||(mem.pw[7]>='A'&&mem.pw[7]<='Z')||(mem.pw[7]>='a'&&mem.pw[7]<='z')||(mem.pw[7]==0)||(mem.pw[7]==-52))
			||!((mem.pw[8]>='0'&&mem.pw[8]<='9')||(mem.pw[8]>='A'&&mem.pw[8]<='Z')||(mem.pw[8]>='a'&&mem.pw[8]<='z')||(mem.pw[8]==0)||(mem.pw[8]==-52))
			||!((mem.pw[9]>='0'&&mem.pw[9]<='9')||(mem.pw[9]>='A'&&mem.pw[9]<='Z')||(mem.pw[9]>='a'&&mem.pw[9]<='z')||(mem.pw[9]==0)||(mem.pw[9]==-52))
			||!((mem.pw[10]>='0'&&mem.pw[10]<='9')||(mem.pw[10]>='A'&&mem.pw[10]<='Z')||(mem.pw[10]>='a'&&mem.pw[10]<='z')||(mem.pw[10]==0)||(mem.pw[10]==-52))
			||!((mem.pw[11]>='0'&&mem.pw[11]<='9')||(mem.pw[11]>='A'&&mem.pw[11]<='Z')||(mem.pw[11]>='a'&&mem.pw[11]<='z')||(mem.pw[11]==0)||(mem.pw[11]==-52))
			||!((mem.pw[12]>='0'&&mem.pw[12]<='9')||(mem.pw[12]>='A'&&mem.pw[12]<='Z')||(mem.pw[12]>='a'&&mem.pw[12]<='z')||(mem.pw[12]==0)||(mem.pw[12]==-52))
			||!((mem.pw[13]>='0'&&mem.pw[13]<='9')||(mem.pw[13]>='A'&&mem.pw[13]<='Z')||(mem.pw[13]>='a'&&mem.pw[13]<='z')||(mem.pw[13]==0)||(mem.pw[13]==-52))
			||!((mem.pw[14]>='0'&&mem.pw[14]<='9')||(mem.pw[14]>='A'&&mem.pw[14]<='Z')||(mem.pw[14]>='a'&&mem.pw[14]<='z')||(mem.pw[14]==0)||(mem.pw[14]==-52)))
		{   //비밀번호에 영문/숫자외에 다른 문자가 있는지 검사
			puts("비밀번호는 영문/숫자 조합으로만 생성할 수 있습니다.");
			continue;
		}
		else
			break;
	}
	puts("4자리의 차량번호를 입력하십시오. ex) 1234");
	while(1)
	{
		printf("차량번호: "); scanf("%d", &mem.carnum);
		if(mem.carnum>999&&mem.carnum<10000)  //반드시 4자리의 숫자만 받도록 설정
			break;
		else
		{
			puts("4자리의 차량번호를 올바르게 입력하십시오.");
			continue;
		}
	}
	printf("전화번호(ex. 010-111-1111): "); scanf("%s", mem.phon);
	mem.order=0;

	fprintf(fp, "%-12s %-17s %-6d %-17s %-10d\n", mem.id, mem.pw, mem.carnum, mem.phon, mem.order);
	puts("회원가입이 완료 되었습니다.");
	puts("Press any key to continue");
	getch();
	fclose(fp);
	start();  //start함수 호출
}

int Re_Check(char memid[15], int * cnt)
{
	FILE * fp=fopen("member.txt", "rt");
	typedef struct member //회원가입을 받기 위한 회원 정보 구조체
	{
		char id[15];
		char pw[20];
		int carnum;
		char phon[15];
		int order;
	}Member;
	Member mem;
	*cnt=0;

	while (1)
	{
		fscanf(fp, "%s %s %d %s %d", mem.id, mem.pw, &mem.carnum, mem.phon, &mem.order);
		/*fseek(fp, 67*(*cnt), 0);
		fscanf(fp, "%s\n", tempid);*/
		*cnt += 1;
		if (!strcmp(memid, mem.id))
		{
			return 0;
			break;
		}
		else if (feof(fp))
		{
			return 1;
			break;
		}
		else
			continue;
	}
	fclose(fp);
}
int Re_Check_Admin(char memid[15], int * cnt)//Re_Check함수와 비슷하지만 관리자메뉴를 위해 따로 만든 함수
{
	FILE * fp=fopen("administrator.txt", "rt");

	char tempid[15], temppw[20];
	int grade;
	*cnt=1;
	fscanf(fp, "%s", tempid); //파일로부터 아이디를 입력받음
	if(!strcmp(memid, tempid))//사용자가 입력한 아이디와 비교
	{
		fclose(fp);
		return 0;
	}
	while (1)
	{
		fscanf(fp, "%s %s %d", tempid, temppw, &grade);
		if (!strcmp(memid, tempid))
		{
			fclose(fp);
			return 0;
			break;
		}
		else if (feof(fp))
		{
			fclose(fp);
			return 1;
			break;
		}
		else
			continue;
	}
	fclose(fp);
}
void login()
{
	FILE * fp=fopen("member.txt", "rt"); //회원정보가 저장돼있는 member파일을 열고 파일포인터 fp에 초기화
	typedef struct member //회원정보 구조체
	{
		char id[15];
		char pw[20];
		int carnum;
		char phon[15];
		int order;
	}Member;
	Member mem;
	char id[15], pw[20];
	int cnt, ret, i;
	system("cls");
	printf("---------------로그인---------------\n");
	while(1)
	{
		printf("아이디: "); scanf("%s", id);
		ret=Re_Check(id, &cnt);//Re_Check함수로 입력한 아이디가 member파일에 존재하는지 판별하고, 변수 cnt의 주소값을 넘겨준 뒤
		if(ret)            //한 번 비교할 때 마다 변수 cnt에 ++연산을 하여 몇 번째 아이디인지 알아낸다.
		{
			puts("존재하지 않는 아이디 입니다.\n");
			getch();
			system("cls");
			printf("---------------로그인---------------\n");
			continue;
		}
		else
			break;
	}
	
	printf("비밀번호: "); scanf("%s", pw);
	fseek(fp, 0, SEEK_SET);
	for(i=0; i<cnt; i++) //앞서 수행한Re_Check함수를 통해 몇 번째 회원인지 변수 cnt에 저장돼있으므로 for문을 통해
	{                    //cnt에 저장된 숫자만큼 fscanf문을 반복하면 아이디에 일치하는 비밀번호가 무엇인지 알 수 있다.
		fscanf(fp, "%s %s %d %s %d", mem.id, mem.pw, &mem.carnum, mem.phon, &mem.order);
	}
	if(strcmp(pw, mem.pw))//위의 for문을 통해 알아낸 비밀번호와 사용자가 입력한 비밀번호를 비교한다.
	{
		puts("비밀번호가 일치하지 않습니다.");
		puts("다시 로그인해 주십시오.");
		getch();
		system("cls");
		login();
	}
	else
	{
		printf("%s님 로그인되었습니다.\n", id);
		puts("Press any key to continue");
		getch();
		menu(&cnt);
	}
	fclose(fp);
}

void NonMem() //비회원 메뉴 함수
{
	int i;
	system("cls");
	puts("---------------비회원 메뉴---------------");
	printf("1. 주차현황 조회 \n2. 주차요금 조회 \n3. 회원가입 \n4. 돌아가기 \n5. 종료\n");
	printf("Choose: "); scanf("%d", &i);
	switch(i)
	{
	case 1:
		NonMemShowPark();
		break;
	case 2:
		NonMemParkFee();
		break;
	case 3:
		join();
		break;
	case 4:
		start();
		break;
	case 5:
		exit(0);
		break;
	default:
		printf("유효하지 않은 메뉴입니다. 다시 선택해 주세요.\n");
		puts("Press any key to refresh");
		getch();
		NonMem();
	}
}

void NonMemShowPark()
{
	FILE * fp=fopen("parkstatus.txt", "rt");
	char park[3][10][10][7];
	int i, j, k, score;
	int cnt;

	for(i=0;i<3;i++)  //파일에 저장돼잇는 주차현황정보를 배열로 불러옴
	{
		for(j=0;j<10;j++)
		{
			fscanf(fp, "%s %s %s %s %s %s %s %s %s %s", park[i][j][0], park[i][j][1], park[i][j][2], park[i][j][3], park[i][j][4],
				park[i][j][5], park[i][j][6], park[i][j][7], park[i][j][8], park[i][j][9]);
		}
	}
	system("cls");
	puts("---------------주차현황---------------");
	printf("몇 층의 주차현황을 보시겠습니까?: ");
	scanf("%d", &score);

	if(score<1||score>3)
	{
		puts("본 주차장은 총 3층으로 구성되어있습니다.");
		puts("1~3의 층 수를 다시 입력해 주십시오.");
		getch();
		NonMemShowPark();
	}

	for(j=0;j<10;j++)
	{
		for(k=0;k<10;k++)
		{
			printf("%7s", park[score-1][j][k]);
		}
		printf("\n");
	}
	printf("\n\n");
	puts("1. 다른 층의 주차현황 보기"); puts("2. 돌아가기");
	printf("Choose: "); scanf("%d", &i);
	switch(i)
	{
		case 1:
			puts("Press any key to continue");
			getch();
			NonMemShowPark();
			break;
		case 2:
			puts("Press any key to continue");
			getch();
			NonMem();
			break;
		default:
			puts("유효하지 않는 메뉴입니다.");
			puts("Press any key to refresh");
			getch();
			NonMemShowPark();
	}
}

void NonMemParkFee()
{
	system("cls");

	puts("---------------주차 요금---------------");
	printf("\n");
	printf("시간당 요금: %d원\n\n", PerFee);

	puts("Press any key to return");
	getch();
	NonMem();
}

void menu(int * cnt) //메인메뉴함수
{
	int i;
	system("cls");
	printf("---------------메뉴---------------\n");
	puts("1. 주차하기            2. 주차현황 보기");
	puts("3. 서비스(상품) 주문   4. 관리자 연락처");
	puts("5. 요금계산            6. 현재 도로 상황");
	puts("7. 근접한 주차장 검색  8. 주차 요금");
	puts("9. 현재 시간 보기      10. 로그아웃");
	puts("11. 종료");
	printf("choose: "); scanf("%d", &i);
	switch (i)
	{
		case 1:
			Park(cnt); //'주차하기'함수 호출
			break;
		case 2:
			ShowPark(cnt);//'주차현황보기'함수 호출
			break;
		case 3:
			Service(cnt); //'상품주문'함수 호출
			break;
		case 4:
			AdmPhone(cnt);//'관리자연락처'함수 호출
			break;
		case 5:
			CheckOut(cnt);//'요금계산'함수 호출
			break;
		case 6:
			RoadStat(cnt);//'주변도로상황'함수 호출
			break;
		case 7:
			ParkSearch(cnt);//'주변주차장검색'함수 호출
			break;
		case 8:
			ParkFee(cnt);//'주차장요금'함수 호출
			break;
		case 9:
			TimeNow(cnt);//'현재시간'함수 호출
			break;
		case 10:
			start();//start함수 호출
			break;
		case 11:
			exit(0);//프로그램종료
			break;
		default:
			printf("유효한 메뉴가 아닙니다.\n");
			printf("1 ~ 11 사이의 메뉴를 선택해 주십시오\n");
			puts("Press any key to refresh");
			getch();
			menu(cnt);
	}
}

void Park(int * cnt)
{
	FILE * fp1=fopen("park.txt", "at");
	FILE * fp2=fopen("park.txt", "rt");
	FILE * fp3=fopen("parkstatus.txt", "rt");
	FILE * fp4=fopen("parkstatus.txt", "r+");//주차현황 정보를 갱신하기위한 파일포인터 fp4
	FILE * fp5=fopen("member.txt", "rt");
	typedef struct member //회원정보 구조체
	{
		char id[15];
		char pw[20];
		int carnum;
		char phon[15];
		int order;
	}Member;
	Member mem;
	char park[3][10][10][7];
	char seatnum[5];
	int i, j, k, score, tc=*cnt;
	int tmpcnt, tmpi, tmpj, tmpk, tmptime;
	char tmpid[15];
	system("cls");
	puts("---------------주차하기---------------");

	for(i=0;i<3;i++)  //파일에 저장된 주차현황정보를 다차원배열 park에 저장
	{
		for(j=0;j<10;j++)
		{
			fscanf(fp3, "%s %s %s %s %s %s %s %s %s %s", park[i][j][0], park[i][j][1], park[i][j][2], park[i][j][3], park[i][j][4],
				park[i][j][5], park[i][j][6], park[i][j][7], park[i][j][8], park[i][j][9]);
		}
	}
	while(1) //로그인한 회원이 현재 주차중인지를 판별해 만약 현재 주차중이면 또 다시 주차할 수 없도록한다.
	{
		fscanf(fp2, "%d %d %d %d %d", &tmpcnt, &tmpi, &tmpj, &tmpk, &tmptime);
		if(*cnt==tmpcnt)
		{
			while(tc)  //cnt변수만큼 fscanf문을 실행시켜 해당 회원의 정보를 입력받는다.
			{
				fscanf(fp5, "%s %s %d %s %d", mem.id, mem.pw, &mem.carnum, mem.phon, &mem.order);
				tc--;
			}
			printf("%s님은 이미 %s자리에 주차중 입니다.\n", mem.id, park[tmpi][tmpj][tmpk]);
			puts("Press any key to refresh");
			getch();
			menu(cnt);
		}
		else if(feof(fp2)) //파일의 끝에 도달했을 경우 무한루프를 빠져나간다.
			break;
		else
			continue;
	}
	printf("주차할 층을 입력하십시오.(1~3층): ");
	scanf("%d", &score); //주차할 층을 입력받아 변수 score에 저장
	if (!(score>=1&&score<=3))
	{
		puts("저희 주차장은 총 3층으로 구성되어 있습니다.");puts("1~3사이의 숫자 중 선택해 주십시오.");
		getch();
		fclose(fp1); fclose(fp2); fclose(fp3); fclose(fp4); fclose(fp5);
		Park(cnt);
	}
	
	for(j=0;j<10;j++)
	{
		for(k=0;k<10;k++)
		{
			printf("%7s", park[score-1][j][k]);//총 3층으로 구성된 주차장에서 앞서 입력받은 층의 정보만 출력한다.
		}                                      //(모든 층의 정보를 한 번에 출력하면 양이 많아 눈아프고 알아보기 힘듬)
		printf("\n");
	}
	printf("\n\n");
	printf("콜론(:)을 기준으로 좌측은 자리 고유이름이고, 우측은 주차 여부를 나타냅니다.\n");
	printf("콜론(:)오른쪽의 숫자가 0이면 주차가능하고, 1이면 이미 주차된 자리입니다.\n");
	printf("주차를 원하는 자리의 고유이름을 입력하십시오: ");
	scanf("%s", seatnum);  //주차를 원하는 자리의 고유이름을 입력받아 배열seatnum에 저장
	if(!(seatnum[0]>='A'&&seatnum[0]<='C')||!(seatnum[1]>='A'&&seatnum[1]<='J')||!(seatnum[2]>='0'&&seatnum[2]<='9'))
	{  //사용자가 입력한 자리 이름이 올바른 형식인지 검사
		puts("올바른 자리 이름이 아닙니다.");
		getch();
		fclose(fp1); fclose(fp2); fclose(fp3); fclose(fp4); fclose(fp5);
		Park(cnt);
	}
	i=seatnum[0]-65; j=seatnum[1]-65; k=seatnum[2]-48; //각각의 배열요소에서 적절한 연산을 통하여 배열의 길이 값을 계산
	if (park[i][j][k][4]=='1') //만약 사용자가 입력한 자리의 고유이름의 마지막 숫자가 1인경우는 이미 주차돼있는 좌석이므로
	{                          //다른 자리선택을 요구
		puts("이미 주차된 자리입니다. 다른 자리를 선택해주십시오.");
		puts("Press any key to refresh");
		getch();
		fclose(fp1); fclose(fp2); fclose(fp3); fclose(fp4); fclose(fp5);
		Park(cnt);
	}

	park[i][j][k][4]='1';  //주차가 됐으므로 자리 고유이름의 마지막 숫자를 0에서 1로고침
	fprintf(fp1, "%-5d %d %d %d %-15d\n", *cnt, i, j, k, time(NULL)); //주차정보를 파일에 저장
	                                 //각각의 정보-(cnt)는 회원번호, (i, j, k)는 배열번호, 그리고 (time(NULL))현재시간 정보를 저장
	for(i=0;i<3;i++)//수정된 주차현황 정보를 다시 파일에 갱신
	{
		for(j=0;j<10;j++)
		{
			for(k=0;k<10;k++)
			{
				fprintf(fp4, "%s ", park[i][j][k]);
			}
			fprintf(fp4, "\n");
		}
	}
	printf("%s자리에 주차등록 완료되었습니다. 현 시간부터 주차요금이 계산됩니다.\n", seatnum);
	puts("Press any key to continue");
	getch();
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	menu(cnt);
}

void ShowPark(int * cnt)
{
	FILE * fp=fopen("parkstatus.txt", "rt");
	char park[3][10][10][7];
	int i, j, k, score;

	for(i=0;i<3;i++)
	{
		for(j=0;j<10;j++)
		{
			fscanf(fp, "%s %s %s %s %s %s %s %s %s %s", park[i][j][0], park[i][j][1], park[i][j][2], park[i][j][3], park[i][j][4],
				park[i][j][5], park[i][j][6], park[i][j][7], park[i][j][8], park[i][j][9]);
		}
	}
	system("cls");
	puts("---------------주차현황---------------");
	printf("몇 층의 주차현황을 보시겠습니까?: ");
	scanf("%d", &score);
	if(score<1||score>3)
	{
		puts("본 주차장은 총 3층으로 구성되어있습니다.");
		puts("1~3의 층 수를 다시 입력해 주십시오.");
		getch();
		ShowPark(cnt);
	}

	for(j=0;j<10;j++)
	{
		for(k=0;k<10;k++)
		{
			printf("%7s", park[score-1][j][k]);
		}
		printf("\n");
	}
	printf("\n\n");
	puts("1. 다른 층의 주차현황 보기"); puts("2. 돌아가기");
	printf("Choose: "); scanf("%d", &i);
	switch(i)
	{
		case 1:
			puts("Press any key to continue");
			getch();
			ShowPark(cnt);
			break;
		case 2:
			puts("Press any key to continue");
			getch();
			menu(cnt);
			break;
		default:
			puts("유효하지 않는 메뉴입니다.");
			puts("Press any key to refresh");
			getch();
			ShowPark(cnt);
	}
}

void Service(int * cnt)
{
	FILE * fp1=fopen("member.txt", "rt");
	FILE * fp2=fopen("member.txt", "r+");
	FILE * fp3=fopen("park.txt", "rt");
	typedef struct member
	{
		char id[15];
		char pw[20];
		int carnum;
		char phon[15];
		int order;
	}Member;
	Member mem;
	int i=0, n, oil;
	int tmpcnt, a, b, c, StartT;
	int tc=*cnt;
	while(tc)
	{
		fscanf(fp1, "%s %s %d %s %d\n", mem.id, mem.pw, &mem.carnum, mem.phon, &mem.order);
		tc--;
	}

	while(1)//*cnt는 회원의 바코드와도 같은 개념으로 모든 함수에서 서로 넘겨줌으로서 한 번 로그인한 회원이 계속해서
	{      //로그인되어있는 효과를 주고, 다른 파일에서 회원의 정보와 연결시켜주는 다리 역할도 한다.(매우 중요한 변수이기 때문에 코딩 과정에서 변수 값이 누락되지 않도록 주의)
		fscanf(fp3, "%d %d %d %d %d", &tmpcnt, &a, &b, &c, &StartT);
		if(*cnt==tmpcnt)
			break;
		else if(feof(fp3))//주차장을 이용 중이지 않은경우 서비스상품 또한 이용할 수 없다.(여기서 제공하는 서비스는 각각의 주차자리에 설치된 자동화 기기를 통해서 제공되기 때문에 주차를 하지 않고서는 이용할 수 없음)
		{  //park.txt파일에 저장된 cnt변수값과 현재 접속죽인 회원의 cnt변수값을 대조해봄으로서 주차장을 이용중인지 알 수 있다.
			system("cls");
			puts("---------------서비스 주문---------------");
			puts("본 상품은 저희 주차장에 주차 중인 고객을 대상으로 하는 부가서비스 상품이므로");
			puts("저희 주차장에 주차하지 않은 고객님은 주문하실 수 없습니다.");
			puts("먼저 '주차하기'메뉴를 통해 차량을 주차해 주시기 바랍니다.");
			puts("Press any key to return");
			getch();
			fclose(fp1); fclose(fp2); fclose(fp3);
			menu(cnt);
		}
		else
			continue;
	}
	system("cls");
	puts("---------------서비스 주문---------------");
	printf("1. 세차(%d원) \n2. 주유(리터당 %d원) \n3. 타이어 교체(%d원)\n4. 돌아가기\n", CarWash, Refuel, Tire);
	printf("Choose: "); scanf("%d", &i);
	switch (i)
	{
	case 1:
		puts("세차비용은 주차요금에 합산청구됩니다. 정말 주문하시겠습니까?");
		puts("1. Yes    2. No");
		printf("Choose: "); scanf("%d", &n);
		if (n==1)
		{
			mem.order += CarWash;
			fseek(fp2, 67*(*cnt-1)+56+(*cnt-1), 0);//fseek문으로 member파일에있는 order정보에 접근하여 갱신한다.
			fprintf(fp2, "%-10d", mem.order);
			puts("주문이 완료 되었습니다.");
			getch();
			fclose(fp1); fclose(fp2); fclose(fp3);
			menu(cnt);
		}
		else if(n==2)
		{
			puts("주문이 취소 되었습니다.");
			getch();
			fclose(fp1); fclose(fp2); fclose(fp3);
			Service(cnt);
		}
		else
		{
			puts("유효하지 않은 선택입니다. 다시 주문해 주십시오.");
			getch();
			fclose(fp1); fclose(fp2); fclose(fp3);
			Service(cnt);
		}
		break;
	case 2:
		puts("주유비용은 주차요금에 합산청구됩니다. 정말 주문하시겠습니까?");
		puts("1. Yes    2. No");
		printf("Choose: "); scanf("%d", &n);
		if(n==1)
		{
			printf("몇 리터 주유 하시겠습니까? "); scanf("%d", &oil);
			mem.order += (Refuel*oil);
			fseek(fp2, 67*(*cnt-1)+56+(*cnt-1), 0);
			fprintf(fp2, "%-10d", mem.order);
			puts("주문이 완료 되었습니다.");
			getch();
			fclose(fp1); fclose(fp2); fclose(fp3);
			menu(cnt);
		}
		else if(n==2)
		{
			puts("주문이 취소 되었습니다.");
			getch();
			fclose(fp1); fclose(fp2); fclose(fp3);
			Service(cnt);
		}
		else
		{
			puts("유효하지 않은 선택입니다. 다시 주문해 주십시오.");
			getch();
			fclose(fp1); fclose(fp2); fclose(fp3);
			Service(cnt);
		}
		break;
	case 3:
		puts("타이어 교체비용은 주차요금에 합산청구됩니다. 정말 주문하시겠습니까?");
		puts("1. Yes    2. No");
		printf("Choose: "); scanf("%d", &n);
		if (n==1)
		{
			mem.order += Tire;
			fseek(fp2, 67*(*cnt-1)+56+(*cnt-1), 0);
			fprintf(fp2, "%-10d", mem.order);
			puts("주문이 완료 되었습니다.");
			getch();
			fclose(fp1); fclose(fp2); fclose(fp3);
			menu(cnt);
		}
		else if(n==2)
		{
			puts("주문이 취소 되었습니다.");
			getch();
			fclose(fp1); fclose(fp2); fclose(fp3);
			Service(cnt);
		}
		else
		{
			puts("유효하지 않은 선택입니다. 다시 주문해 주십시오.");
			getch();
			fclose(fp1); fclose(fp2); fclose(fp3);
			Service(cnt);
		}
		break;
	case 4:
		puts("Press any key to return");
		getch();
		fclose(fp1); fclose(fp2); fclose(fp3);
		menu(cnt);
		break;
	default:
		puts("존재하지 않는 메뉴입니다.");
		getch();
		fclose(fp1); fclose(fp2); fclose(fp3);
		Service(cnt);
	}
}

void AdmPhone(int * cnt)
{
	system("cls");

	puts("---------------관리자 연락처---------------");
	printf("총 관리자(5TEAM): 010-5555-5555 \n기술 지원팀: 010-1111-1111 \n고객 센터: 070-8282-8282\n\n");

	puts("Press any key to return");
	getch();
	menu(cnt);
}

void CheckOut(int * cnt)
{
	FILE * fp1=fopen("member.txt", "rt");
	FILE * fp2=fopen("park.txt", "rt");
	FILE * fp3=fopen("member.txt", "r+");
	FILE * fp4=fopen("park.txt", "r+");
	FILE * fp5=fopen("parkstatus.txt", "rt");
	FILE * fp6=fopen("income.txt", "at");
	FILE * fp7=fopen("parkstatus.txt", "r+");
	time_t ltime;
	struct tm * today;
	typedef struct member
	{
		char id[20];
		char pw[20];
		int carnum;
		char phon[15];
		int order;
	}Member;
	Member mem;
	char park[3][10][10][7];
	int a, b, c, StartT, tmpcnt;
	int total, i;
	int choose;
	int j, k, l, tc=*cnt;

	system("cls");
	puts("---------------요금계산---------------");
	for(j=0;j<3;j++)//파일에 저장돼있는 주차현황정보를 불러들임
	{
		for(k=0;k<10;k++)
		{
			fscanf(fp5, "%s %s %s %s %s %s %s %s %s %s", park[j][k][0], park[j][k][1], park[j][k][2], park[j][k][3],
				park[j][k][4], park[j][k][5], park[j][k][6], park[j][k][7], park[j][k][8], park[j][k][9]);
		}
	}
	i=0;
	while(tc)//여기서 tc는 cnt변수의 값을 넘겨받은함수 cnt변수를 쓰지 않은 이유는 cnt변수의 값이 변하지 않도록 조심하기위해
	{
		fscanf(fp1, "%s %s %d %s %d", mem.id, mem.pw, &mem.carnum, mem.phon, &mem.order);
		tc--;
	}
	while(1)
	{
		//fseek(fp2, 28*i, 0);
		fscanf(fp2, "%d %d %d %d %d", &tmpcnt, &a, &b, &c, &StartT);//park파일안에 서식화된 자료들 중 첫 번째 데이터는 cnt변수이므로
		if(*cnt==tmpcnt)                                     //현재 사용자의 cnt변수와 대조해 봄으로서 현재 사용자의 주차정보를 불러올 수 있다.
		{
			total=((time(NULL)-StartT)*(PerFee/3600))+mem.order;
			printf("%s님의 현재까지의 이용 요금은 %d원 입니다.\n", mem.id, total);
			break;
		}
		else if(feof(fp2))//만약 현재 사용자의 cnt변수와 일치하는 값이 없다면 주차를 하지 않은 것!
		{
			printf("%s님의 이용내역이 없습니다.\n", mem.id);
			getch();
			fclose(fp1); fclose(fp2); fclose(fp3); fclose(fp4);
			menu(cnt);
		}
		else
		{
			i++;
			continue;
		}
	}
	i=0;
	printf("1. 결제하기 \n2. 돌아가기\n");
	printf("Choose: "); scanf("%d", &choose);
	if(choose==1)
	{
		fseek(fp3, 67*(*cnt-1)+56+(*cnt-1), 0);//결제하기를 선택하면 member파일의 주문정보를 0으로 초기화한다.
		fprintf(fp3, "0         ");
		while(1)
		{
			fscanf(fp4, "%d %d %d %d %d", &tmpcnt, &a, &b, &c, &StartT);
			i++;
			if(*cnt==tmpcnt)
				break;
		}
		park[a][b][c][4]='0'; //결제를 하면 사용자가 사용했던 자리는 다시 빈 자리가 되므로 자리 이름의 마지막 숫자(콜론 오른쪽 값)를 다시 0으로 바꿔준다.
		for(j=0;j<3;j++)
		{
			for(k=0;k<10;k++)
			{
				for(l=0;l<10;l++)
				{
					fprintf(fp7, "%s ", park[j][k][l]);//바뀐 주차현황 정보를 파일에 갱신한다.
				}
				fprintf(fp7, "\n");
			}
		}
		time(&ltime);
		today = localtime(&ltime);
		fprintf(fp6, "%04d %02d %02d %-12s %-15d\n", today->tm_year+1900, today->tm_mon+1, today->tm_mday, mem.id, total);
		fseek(fp4, 29*(i-1), 0);   //시간값과 결제한 고객의 아이디, 그리고 금액을 income파일에 저장
		fprintf(fp4, "0     ");   //관리자메뉴에서 수입내역 조회에 쓰기위해서
		puts("결제가 완료 되었습니다.");
		getch();
		fclose(fp1); fclose(fp2); fclose(fp3); fclose(fp4); fclose(fp5); fclose(fp6); fclose(fp7);
		menu(cnt);//fclose를 제때 안 해주면 바로 정보가 갱신되지 않는 문제가 발생했었음!!
	}
	else if(choose==2)
	{
		puts("Press any key to return");
		getch();
		fclose(fp1); fclose(fp2); fclose(fp3); fclose(fp4); fclose(fp5); fclose(fp6); fclose(fp7);
		menu(cnt);
	}
	else
	{
		puts("유효하지 않는 메뉴입니다.");
		getch();
		fclose(fp1); fclose(fp2); fclose(fp3); fclose(fp4); fclose(fp5); fclose(fp6); fclose(fp7);
		CheckOut(cnt);
	}
}

void RoadStat(int * cnt)
{
	char a[6][70]={{"주변 도로가 복잡 합니다"},
	{"주변 도로가 한산 합니다"},
	{"주변 도로에 사고가 있습니다"},
	{"주변 도로가 정체 중입니다. 우회하십시오."},
	{"GPS신호가 약합니다. 잠시 후 다시 시도하십시오."},
	{"주변 도로가 공사 중이오니 우회하십시오."}};
	int temp;

	system("cls");
	printf("---------------현재 도로 상황---------------\n\n");
	srand(time(NULL));

	temp =(rand()%(6-0)+0); //랜덤함수를 이용해 임의로 메세지를 뿌려줌

	printf("%s\n\n",a[temp]);
	puts("Press any key to return");
	getch();
	menu(cnt);
}

void ParkSearch(int * cnt)  //도로정보와 마찬가지
{
	char b[4][80] ={"한강 주차장이 가장 가깝습니다.","마포 주차장이 가장 가깝습니다.","성남 주차장이 가장 가깝습니다.", "송파 공영주차장이 가장 가깝습니다."};
	int temp;

	system("cls");
	printf("---------------주변 주차장 검색---------------\n\n");
	srand(time(NULL));

	temp =(rand()%(4-0)+0);

	printf("%s\n\n",b[temp]);
	puts("Press any key to return");
	getch();
	menu(cnt);
}

void ParkFee(int * cnt)
{
	system("cls");

	puts("---------------주차 요금---------------");
	printf("\n");
	printf("시간당 요금: %d원\n\n", PerFee);

	puts("Press any key to return");
	getch();
	menu(cnt);
}

void TimeNow(int * cnt)
{
	int i=0;
	time_t ltime;
	struct tm * today;
	int OldSec=0;

	system("cls");
	while (i<1)
	{
		printf("---------------현재시간---------------\n");
		time(&ltime);
		today = localtime(&ltime);
		if (OldSec != today->tm_sec)
		{
			printf("현재시간: %04d-%02d-%02d %02d:%02d\n", today->tm_year+1900,
				today->tm_mon+1, today->tm_mday, today->tm_hour, today->tm_min);
			OldSec = today->tm_sec;//현재 시간을 출력
			i++;
		}
	}
	puts("Press any key to return");
	getch();
	menu(cnt);
}

void Admin()
{
	FILE * fp=fopen("administrator.txt", "rt");
	
	char id[15], pw[20];
	char tempid[15], temppw[20];
	char exit[]="exit";
	int tempgrade;
	int cnt=0;

	system("cls");
	puts("---------------관리자 로그인---------------");
	puts("관리자 메뉴로 진입하기 위해서는 관리자 아이디로 로그인 해야 합니다.");
	puts("아이디 또는 비밀번호란에 'exit'를 치면 초기화면으로 갈 수 있습니다.");
	printf("관리자 아이디: "); scanf("%s", id);
	while(1)
	{
		fscanf(fp, "%s %s %d", tempid, temppw, &tempgrade);
		cnt++;
		if(!strcmp(id, tempid))
			break;
		else if (!strcmp(id, exit))
		{
			puts("초기화면으로 돌아갑니다.");
			getch();
			fclose(fp);
			start();
		}
		else if(feof(fp))
		{
			puts("일치하는 아이디가 없습니다.");
			getch();
			fclose(fp);
			Admin();
		}
		else
			continue;
	}
	while(1)
	{
		printf("비밀번호: "); scanf("%s", pw);
		if(!strcmp(pw, temppw))
			break;
		else if(!strcmp(pw, exit))
		{
			puts("초기화면으로 돌아갑니다.");
			getch();
			fclose(fp);
			start();
		}
		else
		{
			puts("비밀번호가 일치하지 않습니다.");
			continue;
		}
	}
	puts("Press any key to continue");
	getch();
	fclose(fp);
	AdminMenu(&cnt);
}

void AdminMenu(int * cnt)//사실 관리자메뉴에서 cnt변수는 그닥 필요가 없었다. (관리자는 요금을 결제하거나 주문을 하지도 않고, 계정 자체에서도 많은 정보를 갖고있지 않기 때문에)
{
	int n;
	system("cls");
	puts("---------------관리자 메뉴---------------");
	
	printf("1. 관리자 추가/삭제 및 등급변경\n2. 회원정보 조회\n3, 회원 삭제\n4. 수입내역\n5. 돌아가기\n");
	printf("Choose: "); scanf("%d", &n);
	if(n==1)
		AdjAdmin(cnt);
	else if(n==2)
		ShowMember(cnt);
	else if(n==3)
		DelMember(cnt);
	else if(n==4)
		Income(cnt);
	else if(n==5)
		start();
	else
	{
		puts("1~5사이의 메뉴를 선택해 주십시오.");
		getch();
		AdminMenu(cnt);
	}
}

void AdjAdmin(int * cnt)
{
	FILE * fp=fopen("administrator.txt", "rt");
	int grade, n;
	n=*cnt;
	n-=2;
	if(*cnt==1)
	{
		fseek(fp, 31, 0);
		fscanf(fp, "%d", &grade);
	}
	else if (*cnt==2)
	{
		fseek(fp, 35, 0);
		fseek(fp, 31, 1);
		fscanf(fp, "%d", &grade);
	}
	else
	{
		fseek(fp, 35, 0);
		while(n)
		{
			fseek(fp, 35, 1);
			n--;
		}
		fseek(fp, 31, 1);
		fscanf(fp, "%d", &grade);
	}
	if (grade>1)
	{
		puts("이 메뉴는 총관리자(Grade==1)만 접근할 수 있습니다.");
		getch();
		fclose(fp);
		AdminMenu(cnt);
	}

	system("cls");
	puts("---------------관리자 추가/삭제 및 등급변경---------------");
	puts("1. 관리자 추가");
	puts("2. 관리자 삭제");
	puts("3. 관리자 등급변경");
	puts("4. 돌아가기");
	printf("Choose: "); scanf("%d", &n);
	if(n==1)
		AddAdmin(cnt);
	else if(n==2)
		DelAdmin(cnt);
	else if(n==3)
		ChangeGradeAdmin(cnt);
	else if(n==4)
	{
		puts("Press any key to return");
		getch();
		fclose(fp);
		AdminMenu(cnt);
	}
	else
	{
		puts("1~4사이의 메뉴를 선택해 주십시오.");
		getch();
		fclose(fp);
		AdjAdmin(cnt);
	}
}

void AddAdmin(int * cnt)
{
	FILE * fp=fopen("administrator.txt", "at");
	char id[15], pw[20];
	int grade, ret, tempcnt=0, n;
	system("cls");
	puts("---------------관리자 추가---------------");
	while(1)
	{
		id[0]=0;id[1]=0;id[2]=0;id[3]=0;id[4]=0;id[5]=0;id[6]=0;id[7]=0;id[8]=0;
		id[9]=0;id[10]=0;id[11]=0;id[12]=0;id[13]=0;id[14]=0;
		printf("아이디: "); scanf("%s", id);

		ret=Re_Check_Admin(id, &tempcnt);
		
		if((id[10]>47&&id[10]<58)||(id[10]>64&&id[10]<91)||(id[10]>96&&id[10]<123))
		{
			puts("아이디가 10자를 초과하였습니다.");
			continue;
		}
		else if(!((id[0]>='0'&&id[0]<='9')||(id[0]>='A'&&id[0]<='Z')||(id[0]>='a'&&id[0]<='z'))
			||!((id[1]>='0'&&id[1]<='9')||(id[1]>='A'&&id[1]<='Z')||(id[1]>='a'&&id[1]<='z')||(id[1]==0))
			||!((id[2]>='0'&&id[2]<='9')||(id[2]>='A'&&id[2]<='Z')||(id[2]>='a'&&id[2]<='z')||(id[2]==0)||(id[2]==-52))
			||!((id[3]>='0'&&id[3]<='9')||(id[3]>='A'&&id[3]<='Z')||(id[3]>='a'&&id[3]<='z')||(id[3]==0)||(id[3]==-52))
			||!((id[4]>='0'&&id[4]<='9')||(id[4]>='A'&&id[4]<='Z')||(id[4]>='a'&&id[4]<='z')||(id[4]==0)||(id[4]==-52))
			||!((id[5]>='0'&&id[5]<='9')||(id[5]>='A'&&id[5]<='Z')||(id[5]>='a'&&id[5]<='z')||(id[5]==0)||(id[5]==-52))
			||!((id[6]>='0'&&id[6]<='9')||(id[6]>='A'&&id[6]<='Z')||(id[6]>='a'&&id[6]<='z')||(id[6]==0)||(id[6]==-52))
			||!((id[7]>='0'&&id[7]<='9')||(id[7]>='A'&&id[7]<='Z')||(id[7]>='a'&&id[7]<='z')||(id[7]==0)||(id[7]==-52))
			||!((id[8]>='0'&&id[8]<='9')||(id[8]>='A'&&id[8]<='Z')||(id[8]>='a'&&id[8]<='z')||(id[8]==0)||(id[8]==-52))
			||!((id[9]>='0'&&id[9]<='9')||(id[9]>='A'&&id[9]<='Z')||(id[9]>='a'&&id[9]<='z')||(id[9]==0)||(id[9]==-52)))
		{
			puts("아이디는 영문/숫자 조합으로만 생성할 수 있습니다.");
			continue;
		}
		else if(id[0]==48&&id[1]==0)
		{
			puts("아이디로 숫자 0은 사용할 수 없습니다.");
			continue;
		}
		else if (ret)
		{
			puts("사용할 수 있는 아이디 입니다.");
			break;
		}
		else
		{
			puts("이미 사용중인 아이디 입니다.");
			continue;
		}
		
	}
	puts("15자이하의 영문/숫자 조합으로 비밀번호를 입력하십시오.");
	while(1)
	{
		pw[1]=0;pw[2]=0;pw[3]=0;pw[4]=0;pw[5]=0;pw[6]=0;pw[7]=0;pw[8]=0;pw[9]=0;pw[10]=0;
		pw[11]=0;pw[12]=0;pw[13]=0;pw[14]=0;pw[15]=0;pw[16]=0;pw[17]=0;pw[18]=0;pw[19]=0;pw[0]=0;
		printf("비밀번호: "); scanf("%s", pw);
		if((pw[15]>47&&pw[15]<58)||(pw[15]>64&&pw[15]<91)||(pw[15]>96&&pw[15]<123))
		{
			puts("비밀번호가 15자를 초과하였습니다.");
			continue;
		}
		else if(!((pw[0]>='0'&&pw[0]<='9')||(pw[0]>='A'&&pw[0]<='Z')||(pw[0]>='a'&&pw[0]<='z'))
			||!((pw[1]>='0'&&pw[1]<='9')||(pw[1]>='A'&&pw[1]<='Z')||(pw[1]>='a'&&pw[1]<='z')||(pw[1]==0))
			||!((pw[2]>='0'&&pw[2]<='9')||(pw[2]>='A'&&pw[2]<='Z')||(pw[2]>='a'&&pw[2]<='z')||(pw[2]==0)||(pw[2]==-52))
			||!((pw[3]>='0'&&pw[3]<='9')||(pw[3]>='A'&&pw[3]<='Z')||(pw[3]>='a'&&pw[3]<='z')||(pw[3]==0)||(pw[3]==-52))
			||!((pw[4]>='0'&&pw[4]<='9')||(pw[4]>='A'&&pw[4]<='Z')||(pw[4]>='a'&&pw[4]<='z')||(pw[4]==0)||(pw[4]==-52))
			||!((pw[5]>='0'&&pw[5]<='9')||(pw[5]>='A'&&pw[5]<='Z')||(pw[5]>='a'&&pw[5]<='z')||(pw[5]==0)||(pw[5]==-52))
			||!((pw[6]>='0'&&pw[6]<='9')||(pw[6]>='A'&&pw[6]<='Z')||(pw[6]>='a'&&pw[6]<='z')||(pw[6]==0)||(pw[6]==-52))
			||!((pw[7]>='0'&&pw[7]<='9')||(pw[7]>='A'&&pw[7]<='Z')||(pw[7]>='a'&&pw[7]<='z')||(pw[7]==0)||(pw[7]==-52))
			||!((pw[8]>='0'&&pw[8]<='9')||(pw[8]>='A'&&pw[8]<='Z')||(pw[8]>='a'&&pw[8]<='z')||(pw[8]==0)||(pw[8]==-52))
			||!((pw[9]>='0'&&pw[9]<='9')||(pw[9]>='A'&&pw[9]<='Z')||(pw[9]>='a'&&pw[9]<='z')||(pw[9]==0)||(pw[9]==-52))
			||!((pw[10]>='0'&&pw[10]<='9')||(pw[10]>='A'&&pw[10]<='Z')||(pw[10]>='a'&&pw[10]<='z')||(pw[10]==0)||(pw[10]==-52))
			||!((pw[11]>='0'&&pw[11]<='9')||(pw[11]>='A'&&pw[11]<='Z')||(pw[11]>='a'&&pw[11]<='z')||(pw[11]==0)||(pw[11]==-52))
			||!((pw[12]>='0'&&pw[12]<='9')||(pw[12]>='A'&&pw[12]<='Z')||(pw[12]>='a'&&pw[12]<='z')||(pw[12]==0)||(pw[12]==-52))
			||!((pw[13]>='0'&&pw[13]<='9')||(pw[13]>='A'&&pw[13]<='Z')||(pw[13]>='a'&&pw[13]<='z')||(pw[13]==0)||(pw[13]==-52))
			||!((pw[14]>='0'&&pw[14]<='9')||(pw[14]>='A'&&pw[14]<='Z')||(pw[14]>='a'&&pw[14]<='z')||(pw[14]==0)||(pw[14]==-52)))
		{
			puts("비밀번호는 영문/숫자 조합으로만 생성할 수 있습니다.");
			continue;
		}
		else
			break;
	}
	puts("1->최고관리자 2->중간관리자 3->일반관리자");//관리자에게 등급을 부여, 등급에 따라 접근할 수 있는 메뉴가 다름
	printf("관리자의 등급: "); scanf("%d", &grade);
	fprintf(fp, "%-12s %-17s %-2d\n", id, pw, grade);
	puts("관리자 추가 완료.\n");
	puts("1. 관리자 등급에 대해서 더 알아보기");
	puts("2. 돌아가기");
	printf("Choose: "); scanf("%d", &n);
	if(n==1)
	{
		puts("1등급, 2등급, 3등급으로 관리자 등급을 나누고 등급에 따라 접근할 수 있는 관리자 전용메뉴가");
		puts("제한적일 수 있습니다. 1등급 관리자는 모든 관리자 전용메뉴를 접근할 수 있고, 2등급 관리자는");
		puts("관리자 추가/제거 및 등급변경 메뉴를 제외한 모든 메뉴에 접근 가능합니다. ");
		puts("3등급 관리자는 회원정보 조회 및 수입내역 조회 메뉴에만 접근 가능합니다.");
		puts("Press any key to return");
		getch();
		fclose(fp);
		AdminMenu(cnt);
	}
	else if (n==2)
	{
		puts("Press any key to return");
		getch();
		fclose(fp);
		AdjAdmin(cnt);
	}
}

void DelAdmin(int * cnt)
{
	FILE * fp1=fopen("administrator.txt", "rt");
	FILE * fp2=fopen("administrator.txt", "r+");
	
	char id[15];
	char tempid[15], temppw[20];
	int grade, tc=0, n;
	int i=0, j=0, k=0;
	system("cls");
	puts("---------------관리자 계정 삭제---------------");
	puts("1. 관리자 삭제"); puts("2. 돌아가기");
	printf("Choose: "); scanf("%d", &n);
	if(n==1)
	{
		printf("삭제할 관리자 아이디: "); scanf("%s", id);
		while(1)
		{
			fscanf(fp1, "%s %s %d", tempid, temppw, &grade);
			tc++;
			if(!strcmp(id, tempid))
				break;
			else if(feof(fp1))
			{
				puts("등록되지 않은 아이디입니다.");
				getch();
				fclose(fp1); fclose(fp2);
				DelAdmin(cnt);
			}
			else
				continue;
		}
		fseek(fp2, 35, 0);
		if(tc>2)
		{
			n=tc-2;
			while(n)
			{
				fseek(fp2, 35, 1);
				n--;
			}
		}
		fprintf(fp2, "%-12d %-17d %-2d", i, j, k);
		puts("삭제가 완료되었습니다.");
		getch();
		fclose(fp1); fclose(fp2);
		AdjAdmin(cnt);
	}
	else if(n==2)
	{
		puts("Press any key to return");
		getch();
		fclose(fp1); fclose(fp2);
		AdjAdmin(cnt);
	}
	else
	{
		puts("1~2사이의 메뉴를 선택해 주세요");
		getch();
		fclose(fp1); fclose(fp2);
		DelAdmin(cnt);
	}

}

void ChangeGradeAdmin(int * cnt)
{
	FILE * fp1=fopen("administrator.txt", "rt");
	FILE * fp2=fopen("administrator.txt", "r+");
	int n, i;
	char id[15];
	char tempid[15], temppw[20];
	int grade, tempgrade, tc=0;
	system("cls");
	puts("---------------관리자 등급 변경---------------");
	puts("1. 관리자 등급 변경"); puts("2. 돌아가기");
	printf("Choose: "); scanf("%d", &i);
	if(i==1)
	{
		printf("변경 할 아이디: "); scanf("%s", id);
		while(1)
		{
			fscanf(fp1, "%s %s %d", tempid, temppw, &grade);
			tc++;
			if(!strcmp(id, tempid))
				break;
			else if(feof(fp1))
			{
				puts("등록되지 않은 아이디입니다.");
				getch();
				fclose(fp1); fclose(fp2);
				DelAdmin(cnt);
			}
			else
				continue;
		}
		tempgrade=grade;
		printf("현재 %d 등급의 관리자 계정입니다.\n", grade);
		printf("몇 등급으로 바꾸시겠습니까?: "); scanf("%d", &grade);
		if (tempgrade == grade)
		{
			puts("바꾸시려는 등급과 현재의 등급이 똑같습니다.");
			getch();
			fclose(fp1); fclose(fp2);
			ChangeGradeAdmin(cnt);
		}
		if(tc==1)
		{
			fseek(fp2, 31, 0);
			fprintf(fp2, "%-2d", grade);
			puts("변경 완료 됐습니다.");
			getch();
			fclose(fp1); fclose(fp2);
			AdjAdmin(cnt);
		}
		else if(tc==2)
		{
			fseek(fp2, 35, 0);
			fseek(fp2, 31, 1);
			fprintf(fp2, "%-2d", grade);
			puts("변경 완료 됐습니다.");
			getch();
			fclose(fp1); fclose(fp2);
			AdjAdmin(cnt);
		}
		else
		{
			n=tc-2;
			fseek(fp2, 35, 0);
			while(n)
			{
				fseek(fp2, 35, 1);
				n--;
			}
			fseek(fp2, 31, 1);
			fprintf(fp2, "%-2d", grade);
			puts("변경 완료 됐습니다.");
			getch();
			fclose(fp1); fclose(fp2);
			AdjAdmin(cnt);
		}
	}
	else if(i==2)
	{
		puts("Press any key to return");
		getch();
		fclose(fp1); fclose(fp2);
		AdjAdmin(cnt);
	}
	else
	{
		puts("1~2 중의 숫자 메뉴를 선택해 주십시오.");
		getch();
		fclose(fp1); fclose(fp2);
		ChangeGradeAdmin(cnt);
	}
}

void ShowMember(int * cnt)
{
	FILE * fp=fopen("member.txt", "rt");
	typedef struct member
	{
		char id[20];
		char pw[20];
		int carnum;
		char phon[15];
		int order;
	}Member;
	Member mem;
	int tc=0, i;
	system("cls");
	puts("---------------회원조회---------------");
	printf("아이디   비밀번호   차량번호     전화번호\n");
	while(1)
	{
		fscanf(fp, "%s %s %d %s %d", mem.id, mem.pw, &mem.carnum, mem.phon, &mem.order);
		tc++;
		if(feof(fp))
			break;
	}
	fseek(fp, 0, 0);
	tc-=1;
	for(i=0; i<tc; i++)
	{
		fscanf(fp, "%s %s %d %s %d\n", mem.id, mem.pw, &mem.carnum, mem.phon, &mem.order);
		printf("%-8s %-10s %-12d %-17s\n", mem.id, mem.pw, mem.carnum, mem.phon);
	}
	puts("1. 회원 삭제"); puts("2. 돌아가기");
	printf("Choose: "); scanf("%d", &i);
	if (i==1)
	{
		fclose(fp);
		DelMember(cnt);
	}
	else if(i==2)
	{
		fclose(fp);
		AdminMenu(cnt);
	}
	else
	{
		puts("1~2사이의 메뉴를 선택해 주십시오.");
		getch();
		fclose(fp);
		ShowMember(cnt);
	}
}

void DelMember(int * cnt)
{
	FILE * fp=fopen("administrator.txt", "rt");
	FILE * fp1=fopen("member.txt", "rt");
	FILE * fp2=fopen("member.txt", "r+");
	int i, n, grade;
	char id[15];
	typedef struct member
	{
		char id[20];
		char pw[20];
		int carnum;
		char phon[15];
		int order;
	}Member;
	Member mem;
	int tc=0;

	n=*cnt; n-=2;
	if(*cnt==1)
	{
		fseek(fp, 31, 0);
		fscanf(fp, "%d", &grade);
	}
	else if (*cnt==2)
	{
		fseek(fp, 35, 0);
		fseek(fp, 31, 1);
		fscanf(fp, "%d", &grade);
	}
	else
	{
		fseek(fp, 35, 0);
		while(n)
		{
			fseek(fp, 35, 1);
			n--;
		}
		fseek(fp, 31, 1);
		fscanf(fp, "%d", &grade);
	}
	if (grade>1)
	{
		puts("이 메뉴는 총관리자 또는 중간관리자(Grade 2 이상)만 접근할 수 있습니다.");
		getch();
		fclose(fp);
		AdminMenu(cnt);
	}
	system("cls");
	puts("---------------일반회원 계정 삭제---------------");
	puts("1. 회원 조회"); puts("2. 회원 삭제"); puts("3. 돌아가기");
	printf("Choose: "); scanf("%d", &i);

	if(i==1)
	{
		ShowMember(cnt);
	}
	else if(i==2)
	{
		printf("삭제할 회원 아이디: "); scanf("%s", id);
		while(1)
		{
			fscanf(fp1, "%s %s %d %s %d", mem.id, mem.pw, &mem.carnum, mem.phon, &mem.order);
			tc++;
			if(!strcmp(id, mem.id))
				break;
			else if(feof(fp1))
			{
				puts("등록되지 않은 아이디입니다.");
				getch();
				fclose(fp1); fclose(fp2);
				DelMember(cnt);
			}
			else
				continue;
		}
		n=tc; n-=2;
		if(tc==1)
		{
			fprintf(fp2, "%-12d %-17d %-6d %-17d %-10d", 0, 0, 0, 0, 0);
			puts("삭제 완료!");
			getch();
			fclose(fp1); fclose(fp2);
			AdminMenu(cnt);
		}
		else if(tc==2)
		{
			fseek(fp2, 68, 0); //fseek함수는 자칫 잘못하면 파일안의 데이터를 뒤죽박죽으로 만들 수가 있어 사용함에있어 매우 조심스러웠다.
			fprintf(fp2, "%-12d %-17d %-6d %-17d %-10d", 0, 0, 0, 0, 0);
			puts("삭제 완료!");
			getch();
			fclose(fp1); fclose(fp2);
			AdminMenu(cnt);
		}
		else
		{
			fseek(fp2, 68, 0);
			while(n)
			{
				fseek(fp2, 68, 1);
				n--;
			}
			fprintf(fp2, "%-12d %-17d %-6d %-17d %-10d", 0, 0, 0, 0, 0);
			puts("삭제 완료!");
			getch();
			fclose(fp1); fclose(fp2);
			AdminMenu(cnt);
		}
	}
}

void Income(int * cnt)
{
	FILE * fp=fopen("income.txt", "rt"); 

	int year, month, day, income, total=0, tc=0;
	char id[15];
	system("cls");
	puts("---------------소득 내역 조회---------------");
	while(1)
	{
		fscanf(fp, "%d %d %d %s %d", &year, &month, &day, id, &income);
		tc++;
		if (feof(fp))
			break;
	}
	tc-=1;
	fseek(fp, 0, 0);
	while(tc)
	{
		fscanf(fp, "%d %d %d %s %d", &year, &month, &day, id, &income);
		total += income;
		printf("%d년 %d월 %d일 아이디: %s  금액: %d원\n", year, month, day, id, income);
		tc--;
	}
	printf("총 계: %d원\n", total);
	puts("Press any key to return");
	getch();
	fclose(fp);
	AdminMenu(cnt);

}