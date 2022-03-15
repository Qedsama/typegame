#include<cstdio>
#include<fstream>
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
char user[100],password[100],mode[10];
int mod=0,nownum=1,loginnownum=0;
FILE *infor;
void init();
void login(){
    char userr[100][100],passwordd[100][100];bool userokay=false,passokay=false;
    int usernum=0;
    printf("登录：请输入您的账号：\n");
    scanf("%s",user);
    if ((infor=fopen("users.txt","r"))==NULL){
        printf("系统错误！请检查安装情况。"); 
        exit(0);
    }
    for(int i=1;i<=nownum;i++){
        fgets(userr[i],100,infor);
        userr[i][strlen(userr[i])-1]='\0';
        fgets(passwordd[i],100,infor);
        passwordd[i][strlen(passwordd[i])-1]='\0';
        if(!strcmp(userr[i],user)){
            userokay=true;
            usernum=i;
        }
    }
    if(!userokay){
        fclose(infor);
        printf("该账号尚未注册！请先注册！\n");
        init();
        return;
    }
    else{
        printf("请输入密码：\n");
        scanf("%s",password);
        if(!strcmp(passwordd[usernum],password)){
                passokay=true;
        }
        if(passokay){ 
            fclose(infor);
            printf("登录成功！\n");
            loginnownum=usernum;
            return;
        }
        else{
            fclose(infor);
            printf("密码输入错误！请重新输入账号密码。\n");
            login();
            return;
        }
    }
}
void signup(){
    printf("注册：请输入您的账号\n");
    scanf("%s",user);
    printf("请输入您的密码\n");
    scanf("%s",password);
    char p[100];
    printf("请确认您的密码\n");
    scanf("%s",p);
    if(!strcmp(password,p)){
        nownum++;
        if ((infor=fopen("users.txt","a"))==NULL){
            printf("系统错误！请检查安装情况。");
            exit(0); 
        }
        fputs(user,infor);fputc('\n',infor);
        fputs(password,infor);fputc('\n',infor);
        printf("注册成功！请重新登录。\n");
        login();
        return;
    }
    else{
        printf("输入密码错误！请重新注册。\n");
        signup();
        return;
    }
}
void init(){
    while(!mod){
        printf("输入login以登录账号，输入signup以注册账号。\n");
        scanf("%s",mode);
        if(!strcmp(mode,"login\0"))mod=1;
        else if(!strcmp(mode,"signup\0"))mod=2;
        else mod=0;
        if(!mod)printf("输入错误！请重新选择。\n");
    }
    if(mod==1)login();
    else if(mod==2){signup();loginnownum=nownum;}
}
void selecttext(){

}
int main(){
    printf("欢迎使用人工智障键盘练习系统！\n");
    init();
    selecttext();
    char c=getchar();
    while(c){}
}