#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define bool 	int
#define true 	1
#define false 0
#define EMPTY '\1'
//定义EMPTY表示空串  空串用'\1'表示 

struct {
	
	const char VT[5]={
	//VT终结符集合    空串用  
	'(',')',EMPTY
	};
	
	const char VN[5]={
	//非终结符集合 
	'S'
	};
	const char *P[3][3]={
	//产生式（VN的顺序定义） 
		{//VN[0]的产生式集合		
		"(S)",""
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
	
	char HashMap[256]={0};
	//初始化HashMap  对应元素属于VT则用1表示 属于VN则用2表示 0表示不存在此元素 
	bool initHashMap(){
		/* 
		注意：上次编程到这里  ZJKO
		哈希表应当具备如下能力：
			标识对应元素属于VT∪VN
			区分VT元素与VN元素
			表示VN元素的对应文法产生式对照表位置 
		*/
		//哈希表位置为空则可以写入，否则元素重复   报错 
		for(int i=0;*(VT+i);i++)
			if(!HashMap[*(VT+i)])HashMap[*(VT+i)]=1;
			else return true;
		for(int i=0;*(VN+i);i++)
			if(!HashMap[*(VN+i)])HashMap[*(VN+i)]=2;
			else return true;
		
	}
	
	int init(){	
		//																		错误代码 
		
		error(initHashMap()										?		2		:0); 
		error(strlen(VT)<=0||strlen(VN)<=0		?		3		:0);
		//检查VT或者VN是否为空集 
		error(checkS()												?		4		:0); 
	};	
	
	
	//判断S起始 非终结符是否存在集合VN中 
	bool checkS(){
		for(int i=0;*(VN+i);i++)
			if(*(VN+i)==S)return false;
		return true;
		
	}
//	---------------功能已被哈希表取代 ---------------- 
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
	void DerivationL(const char * Rstr,const int Rlen,char * S){
		 
		 
		if(strlen(S)>Rlen)return ;
//		
//		if() {
//			
//		}
		
		
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
		switch(err){
			case 0:return;
			case 2:puts("终结符集合VT或者非终结符集合VN非法,VT与VN中不能出现相同的元素");break;
			case 3:puts("非终结符集合或终结符集合不能为空集");break;
			case 4:puts("起始非终结符S非法");break;
			
			
			
			
			
			
			
			
			default :printf("程序崩溃，错误代码%x\n",err);
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
