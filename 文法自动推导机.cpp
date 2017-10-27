#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define bool 	int
#define true 	1
#define false 0
#define EMPTY '\1'

//定义EMPTY表示空串  空串用'\1'表示 
//可以通过 #define 自定义元素  所有元素种类范围 0<x<256 
struct {
	const char VT[5]={
	//VT终结符集合 
	'0','1'		//,EMPTY
	};
	const char VN[5]={
	//非终结符集合 
	'S'
	};
	char *P[3][3]={
	//产生式（按照VN中元素的顺序定义） 
		 
		{//VN[0]的产生式集合		
		"01","0S1"
		
		
		//"(S)",""
		}
		
		/*
		,
		{// VN[1]的产生式集合 
		"1","2","3"
		},
		{//VN[2]的产生式集合 
		"2","2","3"
		}
		*/
		//.............
	};
	const char S = 'S';
	
	unsigned char HashMap[256]={0};
	
	
	//检索元素在集合（VT VN）中的位置  
	//返回结果为元素在对应集合的位置 
	unsigned char index(const char c) {
		
		// 如果不存在元素则直接报错 
			if(HashMap[c]==0){
				error(1025);	
			}
			
		// 检查元素属于VN 还是 VT 
			if(HashMap[c]>127)return HashMap[c]-128;
			else return HashMap[c]-1; 
	}
	
	
	
	bool initHashMap(){
		/* 
			哈希表应当具备如下能力：
			标识对应元素属于VT∪VN
			区分VT元素与VN元素
			表示VN元素的对应文法产生式对照表位置 
			元素不属于集合 则为0   元素属于VT则<128  元素属于VN则>=128
			若c属于VN  则HashMap[c]-128为c在VN中的位置  
			若c属于VT  则HashMap[c]-1为c在VT中的位置   (避开0)
			
		*/
		//哈希表位置为空则可以写入，否则元素重复   报错 
		for(int i=0;*(VT+i);i++)
			if(!HashMap[*(VT+i)])HashMap[*(VT+i)]=i+1;
			else return true;
		for(int i=0;*(VN+i);i++)
			if(!HashMap[*(VN+i)])HashMap[*(VN+i)]=i+128;
			else return true;
	}
	
	int init(){	
		//																		错误代码 
		error(initHashMap()										?		2		:0); 
		error(strlen(VT)<=0||strlen(VN)<=0		?		3		:0);
		//检查VT或者VN是否为空集 
		error(checkS()												?		4		:0); 
		
		
		
		
		
		//函数测试 
		showVT();
		showVN();
		DerivationL("00001111","S");
		//--------- 
		
		
	};	
	
	
	//判断S起始 非终结符是否存在集合VN中 
	bool checkS(){
		for(int i=0;*(VN+i);i++)
			if(*(VN+i)==S)return false;
		return true;
		
	}
	unsigned checkSet(char c){
		//判断元素是在哪个集合当中 
			if(HashMap[c]==0)return 0;				//	元素不存在任何集合当中 
			else if(HashMap[c]<128)return 1;	//	元素存在于VT当中 
		 	else return 2;										//	元素存在于VN当中 
	}
//	---------------功能已被哈希取代 ---------------- 
//		
//	//判断集合元素是否唯一 
//	bool checkSetDuplicate(const char *p){
//		//true 有重复       false 没重复 
//		//检查集合完整性，确定集合当中没有重复元素
//		char  HashMap[256]={0};
//		do{
//			if(!HashMap[*p]||HashMap[*p]!=*p)HashMap[*p]=*p;
//			else return true;
//			p++;
//		}while(*p);
//		return false;
//	};
//	


	//最左推导  最左推导出Rstr Rlen为结果字符串长度  S为起始符    输出推导过程 
	void DerivationL(const char * Rstr,char * S){
		/*	*Rstr 为目标串   *S当前串 
		*/
		puts("进入");
		printf("Rstr = %s\nS = %s\n----------------\n",Rstr,S);
		
		
		
		 if(strlen(Rstr)<strlen(S))return ;//正在推导的串串长不能长于结果串
		 
		 printf("fadsfsad");
		 for(int i=0;Rstr[i]&&S[i];i++){
		 	printf("Rstr[i] = %c  S[i] = %c  i = %d \n------------------\n",Rstr[i],S[i],i);
		 	
		 	if(Rstr[i] != S[i]) {
		 		//若不相等 则进行推导 
		 		if(checkSet(S[i])==1) return;//若第一个元素是终结符 且与目标串不匹配则说明推导过程错误。
				//若第一个元素是非终结符 则进行递归推导 
		 		
		 		
					
				 for(int j=0;*P[index(S[i])][j];j++){
				 	
//				 	printf("--Rstr=%s  %s\n",Rstr,strcat(P[index(*S)][j],(S+1)));
//				 	puts("--进入递归");
					printf("J = %d\n",j);
					if(*P[index(S[i])][j]==EMPTY){
						puts("进入1234");
						DerivationL(Rstr,S+i+1)	;						 		
						puts("出来1234");
					}
					else if(S[i+1])	{
				 	
				 			
//				 		printf("%s  -   %s   ?   %s\n",Rstr+i,P[index(S[i])][j],(S+i+1));
				 			char p[255]="";
				 			strcat(p,P[index(S[i])][j]);
							puts("崩溃之前1");				 		
				 			DerivationL(Rstr+i,strcat(p,(S+i+1)))	;
				 			puts("出来之前1");				 		

					 }else{
						puts("崩溃之2");
							DerivationL(Rstr+i,P[index(S[i])][j])	;
							 
						puts("出来之前2");				 		
					}	
//						if(Rstr[i+1]&&S[i+1])break; 
				 }	
				 puts("上面的循环结束了");
			 }
		 }
		 puts("退出来了");
	}
	
	
	
	
	//最右推导 
	void DerivationR(const char * str){
		
	}
	//最左规约 
	void StatuteL(const char * str){
	
	}
	//最右规约 
	void StatuteR(const char * str){
	
	}
	
	
	
	
	
	
	
	
	
	
	void showVT() {
		puts("VT 集合的内容为：");
		for(int i=0;*(VT+i);i++)printf(*(VT+i)==EMPTY?"空字符\t":"%c\t",*(VT+i));
		putchar('\n');
	}
	void showVN() {
		puts("VN 集合的内容为：");
		for(int i=0;*(VN+i);i++)printf("%c\t",*(VN+i));
		putchar('\n');
	}
	
	
	void error(int err){
		//0表示无错误，1~1024表示致命错误（退出程序）  >1024 表示一般错误（可以继续运行） 
		switch(err){
			case 0:return;
			case 2:puts("终结符集合VT或者非终结符集合VN非法,VT与VN中不能出现相同的元素");exit(0) ;
			case 3:puts("非终结符集合或终结符集合不能为空集");exit(0) ;
			case 4:puts("起始非终结符S非法");exit(0) ;
			
			
			
			
			
			
			case 1025:puts("检索失败，此元素不存在") ;break; 
			
			
			
			
			
			
			
			default :printf("程序崩溃，错误代码%x\n",err);
		}
		
	}
}G; 



int main(){
	
	G.init(); 

	
	
 	return 0;
} 
