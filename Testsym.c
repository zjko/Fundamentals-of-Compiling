#include "basedata.h"
#include "symbol.h"
#include <conio.h>
#include <string.h>
#include <ctype.h>
char *WORD[WORDLEN]= {"BEGIN","CALL","CONST","DO",
                      "END","IF","ODD","PROCEDURE",
                      "READ","THEN","VAR","WHILE",
                      "WRITE"
                     };//保留字字符串表,用于将保留字种别码转为字符串输出
SYMBOL WSYM[WORDLEN]= {BEGINSYM,CALLSYM,CONSTSYM,
                       DOSYM,ENDSYM,IFSYM,ODDSYM,
                       PROCSYM,READSYM,THENSYM,
                       VARSYM,WHILESYM,WRITESYM
                      };//保留字种别码表
char* SNAME[SYMBOLNUM]= {
	"NOL","IDENT","NUMBER","PLUS","MINUS","TIMES",
	"SLASH","ODDSYM","EQL","NEQ","LSS","LEQ","GTR",
	"GEQ","LPAREN","RPAREN","COMMA","SEMICOLON",
	"PERIOD","BECOMES","BEGINSYM","ENDSYM","IFSYM",
	"THENSYM","WHILESYM","WRITESYM","READSYM",
	"DOSYM","CALLSYM","CONSTSYM","VARSYM","PROCSYM"
};
//单词字符串表,用于将保留字种别码转为字符串输出
SYMBOL sym;			//最近已识的单词种别码
char token[MAXIDLEN+1];//最近已识别的单词
int num;	//最近已识别的数字值
char ch;	//最近已识别的字符
int col=1,row=1;//褰撳墠琛屽拰鍒楀��
FILE *fd;//鎸囧悜寰呯紪璇戞枃浠�
extern FILE *fout;//鎸囧悜瀛樻斁缁撴灉鏂囦欢
void Getchar(void) {
	ch=fgetc(fd);
	if(ch!=EOF && ch!='\n')
		col++;
	return;
}
void Getbc(void) {
	while(ch==SPACE ||ch==TABLE ||ch=='\n') {
		if(ch=='\n') {
			row++;
			col=1;
		}
		Getchar();
	}//涓虹┖瀛楃鍒欎竴鐩磋鑷充笉涓虹┖瀛楃
}
void Retract(void) {
	fseek(fd,-1l,SEEK_CUR);
	col--;
}
void Concat(void) {
	char temp[2];
	temp[0]=ch;
	temp[1]='\0';
	strcat(token,temp);
}
int Reserve(void) {
	int i,j;
	char temp[60];
	j=strlen(token);
	for(i=0; i<j; i++) {
		temp[i]=toupper(token[i]);//灏嗗綋鍓� token 瀛椾互澶у啓褰㈠紡瀛樺叆 temp 涓�
	}
	temp[i]='\0';
	for(i=0; i<WORDLEN; i++) {
		if(!strcmp(WORD[i],temp))
			break;
	}//鍒ゆ柇褰撳墠 token 鏄惁鏄繚鐣欏瓧
	if(i>=WORDLEN) i=-1;
	return i;
}
void Errorsym(void) {
	fprintf(fout,
	        "There is error @row: %5d, @col: %5d",
	        row,col);
}
int Getsym(void) {
	int k;
	int flag=TRUE;
	Getchar();
	Getbc();//婊ゆ帀鐧藉瓧绗�
	strcpy(token,"");
	if(isalpha(ch)) {
//浠ュ瓧姣嶅紑澶村垯鏄爣璇嗙
		num=0;
		Concat();
		Getchar();
		while(isalnum(ch)) {
			Concat();
			Getchar();
		}
		Retract();//鐢变簬瓒呭墠鎼滅储浜嗭紝鎵�浠ュ洖閫�涓�涓瓧绗�
		k=Reserve();//鍒ゆ柇姝ゆ爣璇嗙鏄惁鏄繚鐣欏瓧
		if(k!=-1) {
			sym=WSYM[k];//灏嗕繚鐣欏瓧绉嶅埆鐮佸瓨鍏� sym 涓�
		} else {
			sym=IDENT;//灏嗕竴鑸爣璇嗙绉嶅埆鐮佸瓨鍏� sym 涓�
		}//end else k!=-1;
	}//end of if isalpha
	else if(isdigit(ch)) {
//浠ユ暟瀛楀紑澶村垯涓烘棤绗﹀彿鏁存暟
		Concat();
		Getchar();
		while(isdigit(ch)) {
			Concat();
			Getchar();
		}
		if(isalpha(ch)) {
			flag=FALSE;
			while(isalnum(ch)) {
				Concat();
				Getchar();
			}
		}//end of flag=FALSE
		Retract();//鍥為��
		if(flag) { //鑻ユ槸鏃犵鍙锋暣鏁帮紝鍒欏皢鏁存暟鍊煎瓨浜� num 涓�
			sym=NUMBER;
			num=atoi(token);
		}
	}//end of if isdigit
	else {
		num=0;
		switch (ch) {
			case '+':
				Concat();
				sym=PLUS;
				break;
			case '-':
				Concat();
				sym=MINUS;
				break;
			case '*':
				Concat();
				sym=TIMES;
				break;
			case '/':
				Concat();
				sym=SLASH;
				break;
			case '(':
				Concat();
				sym=LPAREN;
				break;
			case ')':
				Concat();
				sym=RPAREN;
				break;
			case '=':
				Concat();
				sym=EQL;
				break;
			case '#':
				Concat();
				sym=NEQ;
				break;
				/*
				ODDSYM,EQL,NEQ,LSS,LEQ,GTR,GEQ,LPAREN,
				RPAREN,COMMA,SEMICOLON,PERIOD,BECOMES,
				*/
			case ',':
				Concat();
				sym=COMMA;
				break;
			case '.':
				Concat();
				sym=PERIOD;
				break;
			case ';':
				Concat();
				sym=SEMICOLON;
				break;
			case '>':
				Concat();
				Getchar();
				if(ch!='=') { //鑻ュ悗涓嶈窡'=',鍒欏洖閫�
					sym=GTR;
					Retract();
				} else {
					Concat();
					sym=GEQ;
				}
				break;
			case '<':
				Concat();
				Getchar();
				if(ch!='=') {
					sym=LSS;
					Retract();
				} else {
					Concat();
					sym=LEQ;
				}
				break;
			case ':':
				Concat();
				Getchar();
				if(ch!='=') {
					flag=FALSE;
					Retract();
				} else {
					Concat();
					sym=BECOMES;
				}
				break;
			default :
				Concat();
				flag=FALSE;
				break;
		}//end of switch else char
	}//end of else char
	return flag;
}
