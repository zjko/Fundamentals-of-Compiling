#include<stdio.h>
#define bool 	int
#define true 	1
#define false 0


struct {
	
	const char VT[5]={
	//VT�ս������ 
	'1','2','3'
	};
	
	const char VN[5]={
	//���ս������ 
	'1','1'
	};
	const char *P[3][3]={
	//����ʽ��VN��˳���壩 
		{//VN[0]�Ĳ���ʽ����		
			"1","2","3"
		},
		{// VN[1]�Ĳ���ʽ���� 
		"1","2","3"
		},
		{//VN[2]�Ĳ���ʽ���� 
		"2","2","3"
		}
		//.............
	};
	int init(){	
	
		int x = checkSetDuplicate(VT);
		int y = checkSetDuplicate(VN);
		printf("VT=%d\n",x);
		
 		printf("VN=%d\n",y);
 		
	};	
	
	bool checkSetDuplicate(const char *p){
		//true ���ظ�       false û�ظ� 
		//��鼯�������ԣ�ȷ�����ϵ���û���ظ�Ԫ��
		char  HashMap[256]={0};
		do{
			
			
			if(!HashMap||HashMap[*p]!=*p)HashMap[*p]=*p;
			else return true;
			p++;
		}while(!p);
		return false;
	};
	
	
	
}G; 



int main(){
	G.init(); 
 	return 0;
} 
