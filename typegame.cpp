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
void selecttext(){

}
int main(){
    printf("��ӭʹ���˹����ϼ�����ϰϵͳ��\n");
    init();
    selecttext();
    char c=getchar();
    while(c){}
}