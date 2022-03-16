#include<cstdio>
#include<fstream>
#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
using namespace std;
char user[100],password[100],mode[10];
int mod=0,nownum=1,loginnownum=0,qed=5,hhh=0;
char chapt[100][100],text[10000],tstdin[10000],histor[10000][4];
int history[100][100],er[10000];
FILE *infor;
void init();
void login(){
    char userr[100][100],passwordd[100][100];bool userokay=false,passokay=false;
    int history[100][100];
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
        fclose(infor);
        if ((infor=fopen("history.txt","a"))==NULL){
            printf("系统错误！请检查安装情况。");
            exit(0); 
        }
        for(int i=1;i<=qed;i++){
            fputs("0000",infor);
        }
        fputc('\n',infor);
        fclose(infor);
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
int selecttext(){
    printf("尊敬的%s,您的练习记录如下\n",user);
    if ((infor=fopen("history.txt","a"))==NULL){
        printf("系统错误！请检查安装情况。");
        exit(0); 
    }
    for(int i=1;i<=nownum;i++){
        for(int j=1;j<=qed;j++){
            char his[4];
            fgets(his,5,infor);
            for(int q=0;q<4;q++)histor[hhh++][q]=his[q];
            history[i][j]=1000*(his[0]-48)+100*(his[1]-48)+10*(his[2]-48)+his[3]-48;
        }
        fgetc(infor);
    }
    for(int i=1;i<=qed;i++){
        printf("您的第%d章的练习进度为%d字\n",i,history[loginnownum][i]);
    }
    int chapter=0;
    while(!chapter){
        printf("请选择您要练习的章节：\n");
        scanf("%d",&chapter);
        if(!chapter)printf("输入错误！请重新输入！\n");
    }
    printf("请输入以下文本，输入 @ 以结束\n");
    return chapter;
}
int main(){
    printf("欢迎使用人工智障键盘练习系统！\n");
    printf("please use this program under GB18030\n");
    init();
    for(int i=1;i<=qed;i++){
        chapt[i][0]='c';chapt[i][1]='h';chapt[i][2]='a';chapt[i][3]='p';chapt[i][4]='t';chapt[i][5]='e';chapt[i][0]='r';
        chapt[i][7]=i+'0';chapt[i][8]='.';chapt[i][9]='t';chapt[i][10]='x';chapt[i][11]='t';
    }
    int chapter=selecttext();
    if ((infor=fopen(chapt[chapter],"a"))==NULL){
        printf("系统错误！请检查安装情况。");
        exit(0); 
    }
    fgets(text,10000,infor);
    fclose(infor);
    printf("%s\n",text);
    char c;int r=0;
    while(c!='@'){
        c=getchar();
        if(c=='\n')c=getchar();
        tstdin[r++]=c;
    }
    int lt=strlen(text)-1,lr=strlen(tstdin)-2;
    int errornum=0;
    double errorrate;
    for(int i=0;i<strlen(text);i++){
        if(text[i]!=tstdin[i]){
            er[++errornum]=i;
        }
    }
    errorrate=errornum/lt;
    printf("您共计输入错误%d个字符，错误率为%.2lf",errornum,errorrate);
    for(int i=1;i<=errornum;i++){
        printf("您在%d个字符处输入有错，原文为 %c ，您的输入为 %c 。\n",er[i],text[i],tstdin[i]);
    }
    char save;
    while(save!='y'||save!='n'){
        printf("您是否要保存本次练习进度？是：y，否：n\n");
        save=getchar();
        if(save!='y'||save!='n')printf("输入错误，请重新选择\n");
    }
    if(save=='y'){
        if ((infor=fopen("history.txt","w"))==NULL){
            printf("系统错误！请检查安装情况。");
            exit(0); 
        }
        int hh=0;
        int wei=(loginnownum-1)*qed+chapter-1;
        for(int q=0;q<4;q++){
            histor[wei][3]=lr%10+'0';
            histor[wei][2]=lr/10%10+'0';
            histor[wei][1]=lr/100%10+'0';
            histor[wei][0]=lr/1000%10+'0';
        }
        for(int i=1;i<=nownum;i++){
            for(int j=1;j<=qed;j++){
                fputs(histor[hh++],infor);
            }
            fputc('\n',infor);
        }
        fclose(infor);
        printf("保存成功！\n");
    }
    printf("期待您的下次使用！\n");
    system("pause");
}