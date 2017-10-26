#include<stdio.h>
#define bool 	int
#define true 	1
#define false 0


struct {
	
	const char VT[5]={
	//VT终结符集合 
	'1','2','3'
	};
	
	const char VN[5]={
	//非终结符集合 
	'1','1'
	};
	const char *P[3][3]={
	//产生式（VN的顺序定义） 
		{//VN[0]的产生式集合		
			"1","2","3"
		},
		{// VN[1]的产生式集合 
		"1","2","3"
		},
		{//VN[2]的产生式集合 
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
		//true 有重复       false 没重复 
		//检查集合完整性，确定集合当中没有重复元素
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
