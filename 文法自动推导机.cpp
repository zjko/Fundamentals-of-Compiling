#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define bool 	int
#define true 	1
#define false 0
#define EMPTY '\1'
//����EMPTY��ʾ�մ�  �մ���'\1'��ʾ 

struct {
	
	const char VT[5]={
	//VT�ս������    �մ���  
	'(',')',EMPTY
	};
	
	const char VN[5]={
	//���ս������ 
	'S'
	};
	const char *P[3][3]={
	//����ʽ��VN��˳���壩 
		{//VN[0]�Ĳ���ʽ����		
		"(S)",""
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
	
	char HashMap[256]={0};
	//��ʼ��HashMap  ��ӦԪ������VT����1��ʾ ����VN����2��ʾ 0��ʾ�����ڴ�Ԫ�� 
	bool initHashMap(){
		/* 
		ע�⣺�ϴα�̵�����  ZJKO
		��ϣ��Ӧ���߱�����������
			��ʶ��ӦԪ������VT��VN
			����VTԪ����VNԪ��
			��ʾVNԪ�صĶ�Ӧ�ķ�����ʽ���ձ�λ�� 
		*/
		//��ϣ��λ��Ϊ�������д�룬����Ԫ���ظ�   ���� 
		for(int i=0;*(VT+i);i++)
			if(!HashMap[*(VT+i)])HashMap[*(VT+i)]=1;
			else return true;
		for(int i=0;*(VN+i);i++)
			if(!HashMap[*(VN+i)])HashMap[*(VN+i)]=2;
			else return true;
		
	}
	
	int init(){	
		//																		������� 
		
		error(initHashMap()										?		2		:0); 
		error(strlen(VT)<=0||strlen(VN)<=0		?		3		:0);
		//���VT����VN�Ƿ�Ϊ�ռ� 
		error(checkS()												?		4		:0); 
	};	
	
	
	//�ж�S��ʼ ���ս���Ƿ���ڼ���VN�� 
	bool checkS(){
		for(int i=0;*(VN+i);i++)
			if(*(VN+i)==S)return false;
		return true;
		
	}
//	---------------�����ѱ���ϣ��ȡ�� ---------------- 
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
	void DerivationL(const char * Rstr,const int Rlen,char * S){
		 
		 
		if(strlen(S)>Rlen)return ;
//		
//		if() {
//			
//		}
		
		
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
		switch(err){
			case 0:return;
			case 2:puts("�ս������VT���߷��ս������VN�Ƿ�,VT��VN�в��ܳ�����ͬ��Ԫ��");break;
			case 3:puts("���ս�����ϻ��ս�����ϲ���Ϊ�ռ�");break;
			case 4:puts("��ʼ���ս��S�Ƿ�");break;
			
			
			
			
			
			
			
			
			default :printf("����������������%x\n",err);
		}
		exit(0) ;
	}
}G; 



int main(){
	
	G.init(); 
	G.showVT();
	G.showVN();
	
	
 	return 0;
} 
