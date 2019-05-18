#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <iostream>
 
using namespace std;
 
/*��������*/
void InitSbox(unsigned char sbox[]); 
void KeyExpansion(unsigned char key[], char *k, int len);
void UpsetSbox(unsigned char sbox[], unsigned char key[]);
void DataProcess(unsigned char sbox[], FILE *fp1, FILE *fp2);
void DataEncrypt(char *k, unsigned char *key, unsigned char *sbox, FILE *fp1, FILE *fp2);
void DataDecrypt(char *k1, unsigned char *key, unsigned char *sbox, FILE *fp1, FILE *fp2);
 
/*��ʼ��S��*/
void InitSbox(unsigned char sbox[]){
	for(int i = 0; i < 256; i++)  sbox[i] = i;
}
 
/*��Կ���256����*/
void KeyExpansion(unsigned char key[], char *k, int len){
	if(len <= 256){
		for(int i = 0; i < 256; i++) key[i] = k[i % len];
	}
	if(len > 256){
		for(int i = 0; i < 256; i++) key[i] = k[i];
	}
}
 
/*����S��*/ 
void UpsetSbox(unsigned char sbox[], unsigned char key[]){
	int j = 0;
	unsigned char temp;
	int n;
	for(int i = 0; i < 256; i++){
		n = j + (int)sbox[i] + (int)key[i];
		j = n % 256;
		temp = sbox[i];
		sbox[i] = sbox[j];
		sbox[j] = temp;
	}
}
 
/*�ӽ�������*/ 
void DataProcess(unsigned char sbox[], FILE *fp1, FILE *fp2){
	int i, j;
	i = 0; j = 0;
	char ch = fgetc(fp1);
	while(ch != EOF){
		i = (i + 1) % 256;
		int temp2 = j + (int)sbox[i];
		j = temp2 % 256;
		unsigned char temp;
		temp = sbox[i];
		sbox[i] = sbox[j];
		sbox[j] = temp;
		int temp1 = (int)sbox[i] + (int)sbox[j];
		int t = temp1 % 256;
		char k = sbox[t];
		char cipherchar = ch ^ k;
		fputc(cipherchar, fp2);
		ch = fgetc(fp1);
	}
}
 
/*�����ܺ���*/
void DataEncrypt(char *k, unsigned char *key, unsigned char *sbox, FILE *fp1, FILE *fp2) {
	int len = strlen(k);
    KeyExpansion(key, k, len);
    InitSbox(sbox);
    UpsetSbox(sbox, key);
    DataProcess(sbox, fp1, fp2);
    fclose(fp1);
    fclose(fp2);
    printf("\n���ܳɹ�!\n\n");
}
 
/*�����ܺ���*/ 
void DataDecrypt(char *k1, unsigned char *key, unsigned char *sbox, FILE *fp1, FILE *fp2) {
	int len = strlen(k1);
    KeyExpansion(key, k1, len);
    InitSbox(sbox);
    UpsetSbox(sbox, key);
    DataProcess(sbox, fp1, fp2);
    fclose(fp1);
    fclose(fp2);
    printf("\n���ܳɹ�!\n\n");
}
 
main(){
	char *k = (char *)malloc(25 * sizeof(char));
	char *k1 = (char *)malloc(25 * sizeof(char));
	unsigned char key[256] = {0x00};
	unsigned char sbox[256] = {0x00};
	FILE *fp1, *fp2;
    int flag = 1;
    int choice;
    do{
    	printf("*****************************RC4���ܽ����ļ�************************************");
        printf("\n"); 
        printf("                             1.�����ļ�\n\n");
        printf("                             2.�����ļ�\n\n");
	    printf("                             3.�˳�\n\n"); 
	    printf("��ѡ��Ҫ���еĲ���:");
	    scanf("%d",&choice);
	    switch(choice){
		    case 1: fp1 = fopen("Դ�ļ�.txt","r");
		            if(fp1 == NULL){
    	                printf("��Դ�ļ�ʧ��!\n");
    	                getchar();
    	                exit(0);
                    }
                    fp2 = fopen("���ܺ��ļ�.txt","w");
                    if(fp2 == NULL){
    	                printf("�򿪼��ܺ��ļ�ʧ��!\n");
    	                getchar();
    	                exit(0);
                    }
			        printf("\n�����������Կ:");
	                cin >> k;
	                DataEncrypt(k, key, sbox, fp1, fp2);
                    break;
			case 2: fp1 = fopen("���ܺ��ļ�.txt","r");
			        if(fp1 == NULL){
    	                printf("�򿪼��ܺ��ļ�ʧ��!\n");
    	                getchar();
    	                exit(0);
                    }
			        fp2 = fopen("���ܺ��ļ�.txt","w");
			        if(fp2 == NULL){
    	                printf("�򿪽��ܺ��ļ�ʧ��!\n");
    	                getchar();
    	                exit(0);
                    }
                    printf("\n�����������Կ:");
                    cin >> k1;
                    DataDecrypt(k1, key, sbox, fp1, fp2);
                    break;
            case 3: flag = 0;break;
            default : printf("\n�������Ϸ�!\n\n");
	    }
    }while(flag);
}

