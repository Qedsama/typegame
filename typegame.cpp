#include<cstdio>
#include<fstream>
#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
using namespace std;
char user[100],password[100],mode[10];
int mod=0,nownum=0,loginnownum=0,qed=5,hhh=0,iii=0;
char chapt[100][100],text[10000],tstdin[10000],histor[10000][5];
int history[100][100],er[10000];
FILE *infor;
void init();
void login(){
    char userr[100][100],passwordd[100][100];bool userokay=false,passokay=false;
    int history[100][100];
    int usernum=0;
    printf("��¼�������������˺ţ�\n");
    scanf("%s",user);
    if ((infor=fopen("users.txt","r"))==NULL){
        printf("ϵͳ�������鰲װ�����"); 
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
        printf("���˺���δע�ᣡ����ע�ᣡ\n");
        init();
        return;
    }
    else{
        printf("���������룺\n");
        scanf("%s",password);
        if(!strcmp(passwordd[usernum],password)){
                passokay=true;
        }
        if(passokay){ 
            fclose(infor);
            printf("��¼�ɹ���\n");
            loginnownum=usernum;
            return;
        }
        else{
            fclose(infor);
            printf("����������������������˺����롣\n");
            login();
            return;
        }
    }
}
void signup(){
    printf("ע�᣺�����������˺�\n");
    scanf("%s",user);
    if ((infor=fopen("users.txt","r"))==NULL){
        printf("ϵͳ�������鰲װ�����");
        exit(0); 
    }
    char chongfu[10000][100];
    for(int i=1;i<=nownum;i++){
        fgets(chongfu[i],10000,infor);
        chongfu[i][strlen(chongfu[i])-1]='\0';
    }
    fclose(infor);
    for(int i=1;i<=nownum;i++){
        if(strcmp(user,chongfu[i])==0){
            printf("�û�������������ע�ᣡ\n");
            signup();
            return;
        }
    }    
    printf("��������������\n");
    scanf("%s",password);
    char p[100];
    printf("��ȷ����������\n");
    scanf("%s",p);
    if(!strcmp(password,p)){
        nownum++;
        if ((infor=fopen("users.txt","a"))==NULL){
            printf("ϵͳ�������鰲װ�����");
            exit(0); 
        }
        fputs(user,infor);fputc('\n',infor);
        fputs(password,infor);fputc('\n',infor);
        fclose(infor);
        if ((infor=fopen("history.txt","a"))==NULL){
            printf("ϵͳ�������鰲װ�����");
            exit(0); 
        }
        for(int i=1;i<=qed;i++){
            fputs("0000",infor);
        }
        fputc('\n',infor);
        fclose(infor);
        printf("ע��ɹ��������µ�¼��\n");
        login();
        return;
    }
    else{
        printf("�����������������ע�ᡣ\n");
        signup();
        return;
    }
}
void init(){
    while(!mod){
        printf("����login�Ե�¼�˺ţ�����signup��ע���˺š�\n");
        scanf("%s",mode);
        if(!strcmp(mode,"login\0"))mod=1;
        else if(!strcmp(mode,"signup\0"))mod=2;
        else mod=0;
        if(!mod)printf("�������������ѡ��\n");
    }
    if(mod==1)login();
    else if(mod==2){signup();loginnownum=nownum;}
}
int selecttext(){
    printf("�𾴵�%s,������ϰ��¼����\n",user);
    if ((infor=fopen("history.txt","r"))==NULL){
        printf("ϵͳ�������鰲װ�����");
        exit(0); 
    }
    for(int i=1;i<=nownum;i++){
        for(int j=1;j<=qed;j++){
            char his[5];
            fgets(his,5,infor);
            for(int q=0;q<4;q++)histor[hhh][q]=his[q];
            hhh++;
            history[i][j]=1000*(his[0]-'0')+100*(his[1]-'0')+10*(his[2]-'0')+his[3]-'0';
        }
        fgetc(infor);
    }
    fclose(infor);
    for(int i=1;i<=qed;i++){
        printf("���ĵ�%d�µ���ϰ����Ϊ%d��\n",i,history[loginnownum][i]>0?history[loginnownum][i]:0);
    }
    int chapter=0;
    while(!chapter){
        printf("��ѡ����Ҫ��ϰ���½ڣ�\n");
        scanf("%d",&chapter);
        if(!chapter)printf("����������������룡\n");
    }
    printf("�����������ı������� @ �Խ���\n");
    return chapter;
}
int main(){
    printf("��ӭʹ���˹����ϼ�����ϰϵͳ��\n");
    printf("please use this program under GB18030\n");
    init();
    const char str[100]={"chapter1.txt"};
    for(int i=1;i<=qed;i++){
        strcat(chapt[i],str);
        chapt[i][7]=i+'0';
    }
    int chapter=selecttext();
    if ((infor=fopen(chapt[chapter],"r"))==NULL){
        printf("ϵͳ�������鰲װ�����");
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
    int lt=strlen(text),lr=strlen(tstdin)-1;
    int errornum=0;
    double errorrate;
    for(int i=0;i<strlen(text);i++){
        if(text[i]!=tstdin[i]){
            er[++errornum]=i;
        }
    }
    errorrate=(double)errornum/(double)lt;
    printf("debug:%d %d\n",errornum,lt);
    printf("�������������%d���ַ���������Ϊ%.3lf\n",errornum,errorrate);
    for(int i=1;i<=errornum;i++){
        printf("����%d���ַ��������д�ԭ��Ϊ %c ����������Ϊ %c ��\n",er[i],text[i],tstdin[i]);
    }
    char save='\0';
    while(save!='y'&&save!='n'){
        printf("���Ƿ�Ҫ���汾����ϰ���ȣ��ǣ�y����n\n");
        scanf("%c",&save);
        if(save=='y'||save=='n')break;
        if(save!='y'&&save!='n')printf("�������������ѡ��\n");
    }
    if(save=='y'){
        if ((infor=fopen("history.txt","w"))==NULL){
            printf("ϵͳ�������鰲װ�����");
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
                int sk=0;
                while(sk<4){fputc(histor[hh][sk],infor);sk++;}  
                hh++;
            }
            fputc('\n',infor);
        }
        fclose(infor);
        printf("����ɹ���\n");
    }
    printf("�ڴ������´�ʹ�ã�\n");
    system("pause");
}