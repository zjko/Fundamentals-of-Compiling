#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define bool 	int
#define true 	1
#define false 0
#define EMPTY '\1'

//����EMPTY��ʾ�մ�  �մ���'\1'��ʾ 
//����ͨ�� #define �Զ���Ԫ��  ����Ԫ�����෶Χ 0<x<256 
struct {
	const char VT[5]={
	//VT�ս������ 
	'0','1'		//,EMPTY
	};
	const char VN[5]={
	//���ս������ 
	'S'
	};
	char *P[3][3]={
	//����ʽ������VN��Ԫ�ص�˳���壩 
		 
		{//VN[0]�Ĳ���ʽ����		
		"01","0S1"
		
		
		//"(S)",""
		}
		
		/*
		,
		{// VN[1]�Ĳ���ʽ���� 
		"1","2","3"
		},
		{//VN[2]�Ĳ���ʽ���� 
		"2","2","3"
		}
		*/
		//.............
	};
	const char S = 'S';
	
	unsigned char HashMap[256]={0};
	
	
	//����Ԫ���ڼ��ϣ�VT VN���е�λ��  
	//���ؽ��ΪԪ���ڶ�Ӧ���ϵ�λ�� 
	unsigned char index(const char c) {
		
		// ���������Ԫ����ֱ�ӱ��� 
			if(HashMap[c]==0){
				error(1025);	
			}
			
		// ���Ԫ������VN ���� VT 
			if(HashMap[c]>127)return HashMap[c]-128;
			else return HashMap[c]-1; 
	}
	
	
	
	bool initHashMap(){
		/* 
			��ϣ��Ӧ���߱�����������
			��ʶ��ӦԪ������VT��VN
			����VTԪ����VNԪ��
			��ʾVNԪ�صĶ�Ӧ�ķ�����ʽ���ձ�λ�� 
			Ԫ�ز����ڼ��� ��Ϊ0   Ԫ������VT��<128  Ԫ������VN��>=128
			��c����VN  ��HashMap[c]-128Ϊc��VN�е�λ��  
			��c����VT  ��HashMap[c]-1Ϊc��VT�е�λ��   (�ܿ�0)
			
		*/
		//��ϣ��λ��Ϊ�������д�룬����Ԫ���ظ�   ���� 
		for(int i=0;*(VT+i);i++)
			if(!HashMap[*(VT+i)])HashMap[*(VT+i)]=i+1;
			else return true;
		for(int i=0;*(VN+i);i++)
			if(!HashMap[*(VN+i)])HashMap[*(VN+i)]=i+128;
			else return true;
	}
	
	int init(){	
		//																		������� 
		error(initHashMap()										?		2		:0); 
		error(strlen(VT)<=0||strlen(VN)<=0		?		3		:0);
		//���VT����VN�Ƿ�Ϊ�ռ� 
		error(checkS()												?		4		:0); 
		
		
		
		
		
		//�������� 
		showVT();
		showVN();
		DerivationL("00001111","S");
		//--------- 
		
		
	};	
	
	
	//�ж�S��ʼ ���ս���Ƿ���ڼ���VN�� 
	bool checkS(){
		for(int i=0;*(VN+i);i++)
			if(*(VN+i)==S)return false;
		return true;
		
	}
	unsigned checkSet(char c){
		//�ж�Ԫ�������ĸ����ϵ��� 
			if(HashMap[c]==0)return 0;				//	Ԫ�ز������κμ��ϵ��� 
			else if(HashMap[c]<128)return 1;	//	Ԫ�ش�����VT���� 
		 	else return 2;										//	Ԫ�ش�����VN���� 
	}
//	---------------�����ѱ���ϣȡ�� ---------------- 
//		
//	//�жϼ���Ԫ���Ƿ�Ψһ 
//	bool checkSetDuplicate(const char *p){
//		//true ���ظ�       false û�ظ� 
//		//��鼯�������ԣ�ȷ�����ϵ���û���ظ�Ԫ��
//		char  HashMap[256]={0};
//		do{
//			if(!HashMap[*p]||HashMap[*p]!=*p)HashMap[*p]=*p;
//			else return true;
//			p++;
//		}while(*p);
//		return false;
//	};
//	


	//�����Ƶ�  �����Ƶ���Rstr RlenΪ����ַ�������  SΪ��ʼ��    ����Ƶ����� 
	void DerivationL(const char * Rstr,char * S){
		/*	*Rstr ΪĿ�괮   *S��ǰ�� 
		*/
		puts("����");
		printf("Rstr = %s\nS = %s\n----------------\n",Rstr,S);
		
		
		
		 if(strlen(Rstr)<strlen(S))return ;//�����Ƶ��Ĵ��������ܳ��ڽ����
		 
		 printf("fadsfsad");
		 for(int i=0;Rstr[i]&&S[i];i++){
		 	printf("Rstr[i] = %c  S[i] = %c  i = %d \n------------------\n",Rstr[i],S[i],i);
		 	
		 	if(Rstr[i] != S[i]) {
		 		//������� ������Ƶ� 
		 		if(checkSet(S[i])==1) return;//����һ��Ԫ�����ս�� ����Ŀ�괮��ƥ����˵���Ƶ����̴���
				//����һ��Ԫ���Ƿ��ս�� ����еݹ��Ƶ� 
		 		
		 		
					
				 for(int j=0;*P[index(S[i])][j];j++){
				 	
//				 	printf("--Rstr=%s  %s\n",Rstr,strcat(P[index(*S)][j],(S+1)));
//				 	puts("--����ݹ�");
					printf("J = %d\n",j);
					if(*P[index(S[i])][j]==EMPTY){
						puts("����1234");
						DerivationL(Rstr,S+i+1)	;						 		
						puts("����1234");
					}
					else if(S[i+1])	{
				 	
				 			
//				 		printf("%s  -   %s   ?   %s\n",Rstr+i,P[index(S[i])][j],(S+i+1));
				 			char p[255]="";
				 			strcat(p,P[index(S[i])][j]);
							puts("����֮ǰ1");				 		
				 			DerivationL(Rstr+i,strcat(p,(S+i+1)))	;
				 			puts("����֮ǰ1");				 		

					 }else{
						puts("����֮2");
							DerivationL(Rstr+i,P[index(S[i])][j])	;
							 
						puts("����֮ǰ2");				 		
					}	
//						if(Rstr[i+1]&&S[i+1])break; 
				 }	
				 puts("�����ѭ��������");
			 }
		 }
		 puts("�˳�����");
	}
	
	
	
	
	//�����Ƶ� 
	void DerivationR(const char * str){
		
	}
	//�����Լ 
	void StatuteL(const char * str){
	
	}
	//���ҹ�Լ 
	void StatuteR(const char * str){
	
	}
	
	
	
	
	
	
	
	
	
	
	void showVT() {
		puts("VT ���ϵ�����Ϊ��");
		for(int i=0;*(VT+i);i++)printf(*(VT+i)==EMPTY?"���ַ�\t":"%c\t",*(VT+i));
		putchar('\n');
	}
	void showVN() {
		puts("VN ���ϵ�����Ϊ��");
		for(int i=0;*(VN+i);i++)printf("%c\t",*(VN+i));
		putchar('\n');
	}
	
	
	void error(int err){
		//0��ʾ�޴���1~1024��ʾ���������˳�����  >1024 ��ʾһ����󣨿��Լ������У� 
		switch(err){
			case 0:return;
			case 2:puts("�ս������VT���߷��ս������VN�Ƿ�,VT��VN�в��ܳ�����ͬ��Ԫ��");exit(0) ;
			case 3:puts("���ս�����ϻ��ս�����ϲ���Ϊ�ռ�");exit(0) ;
			case 4:puts("��ʼ���ս��S�Ƿ�");exit(0) ;
			
			
			
			
			
			
			case 1025:puts("����ʧ�ܣ���Ԫ�ز�����") ;break; 
			
			
			
			
			
			
			
			default :printf("����������������%x\n",err);
		}
		
	}
}G; 



int main(){
	
	G.init(); 

	
	
 	return 0;
} 
