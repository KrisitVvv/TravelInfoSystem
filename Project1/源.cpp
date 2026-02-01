#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <io.h>
#include <random>
#include "PasswordTool.h"
#include "WordStyle.h"
#define FILENAME "info.ini"
#define COLLECT_TABLE "collect.ini"
#define TEMP_FILENAME "temp_info.ini"
#define USER_NAME "user_name.db"

//FILE* fp;
char user_state[6] = "NONE";

//设置FILENAME各项字符大小
struct word {
	char scenic[20] = "0";
	char money[20] = "0";
	//int money;
};

//设置COLLECT_TABLE各项字符大小
struct collect {
	char ticket[20]="0";
	char income[20]="0";
	char scenic[20]="0";
};
//设置TEMP_FILENAME
struct temp_word {
	char scenic[20] = "0";
	char money[20] = "0";
};

struct user {
	char id[20] = "0";
	char password[20] = "0";
};

FILE* CollectOpen(char FileName[]) {
	FILE* cl;
	if ((cl = fopen(FileName, "a")) == NULL) {
		cl = fopen(FileName, "w");
		printf("文件打开失败\n");
		return cl;
	}
	//权限调为追加/更新
	cl = fopen(FileName, "a+");
	return	cl;
}

FILE* TEMP_FileOpen(char FileName[]) {
	FILE* temp_fp;
	if ((temp_fp = fopen(FileName, "a")) == NULL) {
		temp_fp = fopen(FileName, "w");
		printf("文件打开失败\n");
		return temp_fp;
	}
	//权限调为追加/更新
	temp_fp = fopen(FileName, "a+");
	return	temp_fp;
}

FILE* USER_LOGIN(char FileName[]) {
	FILE* user;
	if ((user = fopen(FileName, "a")) == NULL) {
		user = fopen(FileName, "w");
		printf("文件打开失败\n");
		return user;
	}
	//权限调为追加/更新
	user = fopen(FileName, "a+");
	return	user;
}


//文件关闭，刷缓冲区，判断返回值0/EOF	
void FileClose(FILE* fp){
	if (fclose(fp) == 0) {
		//printf("\n安全关闭\n");
	}
	else {
		printf("文件关闭失败\n");
	}
}

//检索文件内含tempscenic的信息
void tra1(){
	FILE* fp;
	system("cls");
	char tempscenic[20];
	bool vb = false;
	struct word temp;
	//权限改为读取
	fp = fopen(FILENAME, "r");
	printf("请输入景点名称:");
	scanf("%s", tempscenic);
	system("cls");
	while (fread(&temp, sizeof(struct word), 1, fp) == 1){
			if (strcmp(temp.scenic, tempscenic) == 0) {
				printf("|----------------------------------------------|\n");
				printf("|景点名称:%-15s 票价:%-15s |\n", temp.scenic, temp.money);
				vb = true;
			}
		}
	printf("|----------------------------------------------|\n");
	if (vb == false) {
		printf("|                 未查询到相关信息             |\n");
		printf("|----------------------------------------------|\n");
	}
	system("pause");
	system("cls");
	printf("       查找完毕!\n");
	FileClose(fp);
}

//反向检索
void tra2(){
	FILE* fp;
	system("cls");
	fp = fopen(FILENAME, "r");
	char tempmoney[20];
	struct word temp;
	bool vb = false;

	printf("请输入票价:");
	scanf("%s", tempmoney);
	system("cls");
	while (fread(&temp, sizeof(struct word), 1, fp) == 1){
		if (strcmp(temp.money,tempmoney)==0){
			printf("|----------------------------------------------|\n");
			printf("|景点名称:%-15s 票价:%-15s \n", temp.scenic, temp.money);
			vb = true;
		}
	}
	printf("|----------------------------------------------|\n");
	if (vb == false) {
		printf("|                 未查询到相关信息             |\n");
		printf("|----------------------------------------------|\n");
	}
	system("pause");
	system("cls");
	FileClose(fp);
}

//信息录入版块
void inp(){
	FILE* fp;
	FILE* cl;
	FILE* temp_fp;
	struct word temp;
	struct collect temp2;
	int choose2;
	char tempscenic[20];
	int tempmoney;
	int tempticket;
	char tempscenic2[20];
	char tempmoney2[20];
	char tempscenic3[20];
	int tempsum;
	int key = 1;
	HideCursor(0);
Add:
	system("cls");
	color(7);
	printf("|--------------------|\n");
	printf("|重庆旅游信息管理系统|\n");
	printf("|--------------------|\n");
	if (key == 0) key = 4;
	if (key % 4 == 1) color(9); else color(7); printf("|   1 添加景点信息   |\n");
	if (key % 4 == 2) color(9); else color(7); printf("|   2 删除景点信息   |\n");
	if (key % 4 == 3) color(9); else color(7); printf("|   3 修改景点信息   |\n");
	if (key % 4 == 0) color(9); else color(7); printf("|   0 返回上一级     |\n");
	color(7);
	printf("|--------------------|\n");
	int ch = 1;
	while (1) {
		ch = getch();
		if (ch == 224) continue;
		if (ch == 80) key++;
		if (ch == 72) key--;

		if (ch == 13) {
			choose2 = key;
			HideCursor(1);
			goto Add_Choose;
		}
		system("cls");
		goto Add;
	}




	Add_Choose:
	switch (choose2%4) {
	//添加景点
	case 1:
		fp = fopen(FILENAME, "r+");
		cl = fopen(COLLECT_TABLE, "r+");
		printf("请输入景点名称:");
		scanf("%s", tempscenic);
		while (fread(&temp, sizeof(struct word), 1, fp) == 1) {
			if (strcmp(temp.scenic, tempscenic) == 0) {
				system("cls");
				printf("     已存在该景点\n");
				FileClose(fp);
				FileClose(cl);
				goto Add;
				break;
			}
		}
		fclose(fp);
		printf("请输入对应票价:");
		scanf("%d", &tempmoney);
		fp = fopen(FILENAME, "a+");
		strcpy(temp.scenic, tempscenic);
		snprintf(temp.money, sizeof(struct word), "%d", tempmoney);
		printf("请输入对应售票数:");
		scanf("%d", &tempticket);
		strcpy(temp2.scenic, tempscenic);
		snprintf(temp2.ticket, sizeof(struct collect), "%d", tempticket);
		fwrite(&temp, sizeof(struct word), 1, fp);
		tempsum = tempmoney * tempticket;
		snprintf(temp2.income, sizeof(struct collect), "%d", tempsum);
		cl = fopen(COLLECT_TABLE, "a+");
		fwrite(&temp2, sizeof(struct collect), 1, cl);
		FileClose(cl);
		FileClose(fp);
		system("cls");
		printf("       添加完成\n");
		break;

	//删除景点
	case 2:
		fp = fopen(FILENAME, "r+");
		temp_fp = fopen(TEMP_FILENAME,"w+");
		printf("请输入要删除的景点\n");
		scanf("%s", tempscenic3);
		while (fread(&temp, sizeof(struct word), 1, fp) == 1) {
				if (strcmp(temp.scenic, tempscenic3) == 0) {
					strcpy(temp.scenic, "null");
					strcpy(temp.money, "null");
				}
				fwrite(&temp, sizeof(struct temp_word), 1, temp_fp);
			}
		system("cls");
		printf("       删除成功\n");
		FileClose(temp_fp);
		FileClose(fp);
		remove(".\\info.ini");
		rename(TEMP_FILENAME, "info.ini");
		break;

	//修改景点信息
	case 3:
		//权限改为覆写
		temp_fp = fopen(TEMP_FILENAME, "w+");
		fp = fopen(FILENAME, "r+");
		printf("请输入修改的景点名称:");
		scanf("%s", tempscenic2);
		printf("请输入修改后的票价:");
		scanf("%s", tempmoney2);
		while (fread(&temp, sizeof(struct word), 1, fp) == 1) {
			if (strcmp(temp.scenic, tempscenic2) == 0) {
				strcpy(temp.scenic, tempscenic2);
				strcpy(temp.money, tempmoney2);
			}
			fwrite(&temp, sizeof(struct temp_word), 1, temp_fp);
		}
		FileClose(temp_fp);
		FileClose(fp);
		if (remove(FILENAME) == 0) {
			rename(TEMP_FILENAME, "info.ini");
			system("cls");
			printf("       修改完成\n");
		}
		else {
			perror("Sorry!The file cannot be deleted!Because:\n");
		}
		break;
	case 0:system("cls"); break;
	}
}

//汇总界面
void sum() {
	system("cls");
	FILE* cl;
	//创建info文件
	if ((cl = fopen(COLLECT_TABLE, "a")) == NULL) {
		//fclose(fp);
		cl = fopen(COLLECT_TABLE, "w");
		fclose(cl);
	}
	else {
		fclose(cl);
	}
	cl = fopen(COLLECT_TABLE, "r+");
	struct collect temp2;
	int num;
	bool vb = false;
	char scenicsum[20] = "0";
	int key = 1;
	HideCursor(0);
Sum_Choose:
	color(7);
	printf("|--------------------|\n");
	printf("|重庆旅游信息管理系统|\n");
	printf("|--------------------|\n");
	if (key == 0) key = 3;
	if (key % 3 == 1) color(9); else color(7);printf("|  1 查询全部数据    |\n");
	if(key % 3 == 2) color(9); else color(7); printf("|  2 查询单个景点信息|\n");
	if(key % 3 == 0) color(9); else color(7); printf("|  0 返回上一级      |\n");
	color(7);
	printf("|--------------------|\n");
	int ch = 1;
	while (1) {
		ch = getch();
		if (ch == 224) continue;
		if (ch == 80) key++;
		if (ch == 72) key--;

		if (ch == 13) {
			num = key;
			HideCursor(1);
			goto Sum_Background_Choose;
		}
		system("cls");
		goto Sum_Choose;
	}

	Sum_Background_Choose:
	switch (num%3) {
	case 1:
		system("cls");
		printf("|------------------------------------------------------------|\n");
		while (fread(&temp2, sizeof(struct collect), 1, cl) == 1) {
			printf("| 景点名称:%-10s 售出量:%-10s 总销售额:%-10s  | \n", temp2.scenic, temp2.ticket,temp2.income);
			printf("|------------------------------------------------------------|\n");
			vb = true;
		}
		if (vb == false) {
			printf("|                    未查询到相关信息                        |\n");
			printf("|------------------------------------------------------------|\n");
		}
		FileClose(cl);
		system("pause");
		system("cls");
		break;
	case 2:
		system("cls");
		printf("请输入景点名称:");
		scanf("%s", scenicsum);
		system("cls");
		printf("|------------------------------------------------------------|\n");
		while (fread(&temp2, sizeof(struct collect), 1, cl) == 1) {
			if (strcmp(temp2.scenic, scenicsum) == 0) {
				printf("| 景点名称:%-10s 售出量:%-10s 总销售额:%-10s  | \n", temp2.scenic, temp2.ticket, temp2.income);
				vb = true;
			}
		}
		if (vb == false) {
			if (vb == false) printf("|                    未查询到相关信息                        |\n");
		}
		printf("|------------------------------------------------------------|\n");
		system("pause");
		system("cls");
		printf("查找完毕!\n");
		FileClose(cl);
	case 0:system("cls"); break;
	}
}

//登陆菜单
int login() {
LoginMenu:
	FILE* user;
	user = fopen(USER_NAME, "a+");
	int login_choose = 99;
	int key = 1;
	HideCursor(0);
	while (login_choose != 0) {
	Login_Choose:
		color(7);
		printf("|--------------------|\n");
		printf("|重庆旅游信息管理系统|\n");
		printf("|--------------------|\n");
		if (key == 0) key = 3;
		if (key%3 == 1) color(9); else color(7); printf("|     1 用户登录     |\n");
		if (key%3 == 2) color(9); else color(7); printf("|     2 用户注册     |\n");
		if (key%3 == 0) color(9); else color(7); printf("|     0 退出系统     |\n");
		color(7);
		printf("|--------------------|\n");
		int ch=1;
		while (1) {
			ch = getch();
			if (ch == 224) continue;
			if (ch == 80) key++;
			if (ch == 72) key--;
			
			if (ch == 13) {
				login_choose = key;
				HideCursor(1);
				goto Background_Choose;
			}
			system("cls");
			goto Login_Choose;
		}
		Background_Choose:
		switch (login_choose%3) {
		case 0: exit(0);
		case 1:
			system("cls");
			goto Login; 
			break;
		case 2:
			system("cls");
			goto Register;
			break;
		}
	}

//登录部分
	Login:
	char tempuser[20] = "0";
	char tempuserpassword[20] = "0";
	struct user user_temp;

	printf("请输入你的账号：\n");
	scanf("%s", tempuser);
	printf("请输入你的密码：\n");
	getPassword(tempuserpassword);
	bool vb_user = false;
	while (fread(&user_temp, sizeof(struct user), 1, user) == 1) {
		if (vb_user == true) break;
		if (strcmp(user_temp.id, tempuser) == 0 && strcmp(user_temp.password, tempuserpassword) == 0) {
			vb_user = true;
			if (strcmp(user_temp.id, "admin") == 0) {
				strcpy(user_state, "ADMIN");
			}
			else {
				strcpy(user_state, "USER");
			}
		}
	}
	if (vb_user == false) {
		system("cls");
		printf(" 登录失败，请重新登录\n");
		goto LoginMenu;
	}
	FileClose(user);
	system("cls");
	printf("      登录成功\n");
	return 1;

//注册部分
Register:
	char tempRegisterid[20]="0";
	char tempRegisterpassword[20]="0";
	char tempRegisterpassword_Confirm[20]="0";
	char tempverify[5]="0";
	char verify[5] = "0";

	printf("请输入账号:");
	scanf("%s", tempRegisterid);
	printf("请输入密码:");
	getPassword(tempRegisterpassword);
	printf("请再次输入密码:");
	getPassword(tempRegisterpassword_Confirm);
	if (strcmp(tempRegisterpassword, tempRegisterpassword_Confirm) != 0) {
		system("cls");
		printf("两次密码不一致，请重新输入\n");
		goto Register;
	}
	else {
		while (fread(&user_temp, sizeof(struct user), 1, user) == 1) {
			if (strcmp(user_temp.id, tempRegisterid) == 0) {
				system("cls");
				printf("     已存在该账号\n");
				goto LoginMenu;
			}
		}
			Verify:
				srand(time(NULL));
				for (int i = 0; i < 4; i++) {
					int t = rand() % 3;
					if (t == 0) verify[i] = rand() % 26 + 97;
					else if (t == 1) verify[i] = rand() % 26 + 65;
					else if (t == 2) verify[i] = rand() % 10 + 48;
				}
				printf("验证码是：%s\n请输入验证码：", verify);
				scanf("%s", tempverify);
				for (int i = 0; i < 4; i++) {
					if (tempverify[i] == '\0') break;
					if (tempverify[i] >= 'a' && tempverify[i] <= 'z') {
						tempverify[i] = tempverify[i] - 32;
					}
				}
				for (int i = 0; i < 4; i++) {
					if (verify[i] == '\0') break;
					if (verify[i] >= 'a' && verify[i] <= 'z') {
						verify[i] = verify[i] - 32;
					}
				}
				if (strcmp(verify, tempverify) == 0) {
					strcpy(user_temp.id, tempRegisterid);
					strcpy(user_temp.password, tempRegisterpassword);
					if (fwrite(&user_temp, sizeof(struct user), 1, user) == 1) {
						system("cls");
						printf("       注册成功\n");		
					}
					else {
						system("cls");
						printf("       注册失败");
						goto LoginMenu;
					}
				}
				else {
					printf("验证码错误，请重新输入\n");
					goto Verify;
				}
				FileClose(user);
				goto LoginMenu;
			}
		}

//主界面
int main(){
	if (strcmp(user_state, "NONE") == 0) {
		login();
	}

	FILE* fp;
	//创建info文件
	if ((fp=fopen(FILENAME,"a")) == NULL) {
		//fclose(fp);
		fp = fopen(FILENAME, "w");
		fclose(fp);
	}
	else {
		fclose(fp);
	}
	
	int choose=99;
	int key = 1;
Main_Choose:
	while (choose != 0){
		HideCursor(0);
		printf("|--------------------|\n");
		printf("|重庆旅游信息管理系统|\n");
		printf("|--------------------|\n");
		if (strcmp(user_state, "ADMIN") == 0) {
			if (key == 0) key = 6;
			if (key % 6 == 1) color(9); else color(7); printf("|   1 景点票价查询   |\n");
			if (key % 6 == 2) color(9); else color(7); printf("|   2 票价反查询     |\n");
			if (key % 6 == 3) color(9); else color(7); printf("|   3 信息录入与删除 |\n");
			if (key % 6 == 4) color(9); else color(7); printf("|   4 售票信息汇总   |\n");
			if (key % 6 == 5) color(9); else color(7); printf("|   5 退出登录       |\n");
			if (key % 6 == 0) color(9); else color(7); printf("|   0 退出系统       |\n");
		}
		else {
			if (key == 0) key = 5;
			if (key % 5 == 1) color(9); else color(7); printf("|   1 景点票价查询   |\n");
			if (key % 5 == 2) color(9); else color(7); printf("|   2 票价反查询     |\n");
			if (key % 5 == 3) color(9); else color(7); printf("|   3 信息录入与删除 |\n");
			if (key % 5 == 4) color(9); else color(7); printf("|   4 退出登录       |\n");
			if (key % 5 == 0) color(9); else color(7); printf("|   0 退出系统       |\n");
		}
		color(7);
		printf("|--------------------|\n");
		int ch = 1;
		while (1) {
			ch = getch();
			if (ch == 224) continue;
			//printf("%d\n", ch);
			if (ch == 80) key++;
			if (ch == 72) key--;
			if (ch == 13) {
				choose = key;
				HideCursor(1);
				goto Main_Background_Choose;
			}
			printf("%d", key);
			system("cls");
			goto Main_Choose;
		}
	Main_Background_Choose:
		if (strcmp(user_state, "ADMIN") == 0) choose = choose % 6;
		else choose = choose % 5;
		switch (choose){
		case 0:return 0; break;
		case 1:tra1(); break;
		case 2:tra2(); break;
		case 3:inp(); break;
		case 4:
			if (strcmp(user_state, "ADMIN") == 0) {
			sum();
			break;
			}
			else {
				system("cls");
				strcpy(user_state, "NONE");
				key = 1;
				login();
				break;
			}
		case 5:
			if ((strcmp(user_state, "ADMIN") != 0)) {
				system("cls");
				printf("     请重新输入\n");
			}
			else {
				system("cls");
				strcpy(user_state, "NONE");
				key = 1;
				login();
				break;
			}
		}
	}
}