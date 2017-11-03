#include "basedata.h"
#include "symbol.h"
#include <conio.h>
#include <string.h>
#include <ctype.h>
char *WORD[WORDLEN]= {"BEGIN","CALL","CONST","DO",
                      "END","IF","ODD","PROCEDURE",
                      "READ","THEN","VAR","WHILE",
                      "WRITE"
                     };//±£Áô×Ö×Ö·û´®±í,ÓÃÓÚ½«±£Áô×ÖÖÖ±ğÂë×ªÎª×Ö·û´®Êä³ö
SYMBOL WSYM[WORDLEN]= {BEGINSYM,CALLSYM,CONSTSYM,
                       DOSYM,ENDSYM,IFSYM,ODDSYM,
                       PROCSYM,READSYM,THENSYM,
                       VARSYM,WHILESYM,WRITESYM
                      };//±£Áô×ÖÖÖ±ğÂë±í
char* SNAME[SYMBOLNUM]= {
	"NOL","IDENT","NUMBER","PLUS","MINUS","TIMES",
	"SLASH","ODDSYM","EQL","NEQ","LSS","LEQ","GTR",
	"GEQ","LPAREN","RPAREN","COMMA","SEMICOLON",
	"PERIOD","BECOMES","BEGINSYM","ENDSYM","IFSYM",
	"THENSYM","WHILESYM","WRITESYM","READSYM",
	"DOSYM","CALLSYM","CONSTSYM","VARSYM","PROCSYM"
};
//µ¥´Ê×Ö·û´®±í,ÓÃÓÚ½«±£Áô×ÖÖÖ±ğÂë×ªÎª×Ö·û´®Êä³ö
SYMBOL sym;			//×î½üÒÑÊ¶µÄµ¥´ÊÖÖ±ğÂë
char token[MAXIDLEN+1];//×î½üÒÑÊ¶±ğµÄµ¥´Ê
int num;	//×î½üÒÑÊ¶±ğµÄÊı×ÖÖµ
char ch;	//×î½üÒÑÊ¶±ğµÄ×Ö·û
int col=1,row=1;//å½“å‰è¡Œå’Œåˆ—å€¼
FILE *fd;//æŒ‡å‘å¾…ç¼–è¯‘æ–‡ä»¶
extern FILE *fout;//æŒ‡å‘å­˜æ”¾ç»“æœæ–‡ä»¶
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
	}//ä¸ºç©ºå­—ç¬¦åˆ™ä¸€ç›´è¯»è‡³ä¸ä¸ºç©ºå­—ç¬¦
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
		temp[i]=toupper(token[i]);//å°†å½“å‰ token å­—ä»¥å¤§å†™å½¢å¼å­˜å…¥ temp ä¸­
	}
	temp[i]='\0';
	for(i=0; i<WORDLEN; i++) {
		if(!strcmp(WORD[i],temp))
			break;
	}//åˆ¤æ–­å½“å‰ token æ˜¯å¦æ˜¯ä¿ç•™å­—
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
	Getbc();//æ»¤æ‰ç™½å­—ç¬¦
	strcpy(token,"");
	if(isalpha(ch)) {
//ä»¥å­—æ¯å¼€å¤´åˆ™æ˜¯æ ‡è¯†ç¬¦
		num=0;
		Concat();
		Getchar();
		while(isalnum(ch)) {
			Concat();
			Getchar();
		}
		Retract();//ç”±äºè¶…å‰æœç´¢äº†ï¼Œæ‰€ä»¥å›é€€ä¸€ä¸ªå­—ç¬¦
		k=Reserve();//åˆ¤æ–­æ­¤æ ‡è¯†ç¬¦æ˜¯å¦æ˜¯ä¿ç•™å­—
		if(k!=-1) {
			sym=WSYM[k];//å°†ä¿ç•™å­—ç§åˆ«ç å­˜å…¥ sym ä¸­
		} else {
			sym=IDENT;//å°†ä¸€èˆ¬æ ‡è¯†ç¬¦ç§åˆ«ç å­˜å…¥ sym ä¸­
		}//end else k!=-1;
	}//end of if isalpha
	else if(isdigit(ch)) {
//ä»¥æ•°å­—å¼€å¤´åˆ™ä¸ºæ— ç¬¦å·æ•´æ•°
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
		Retract();//å›é€€
		if(flag) { //è‹¥æ˜¯æ— ç¬¦å·æ•´æ•°ï¼Œåˆ™å°†æ•´æ•°å€¼å­˜äº num ä¸­
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
				if(ch!='=') { //è‹¥åä¸è·Ÿ'=',åˆ™å›é€€
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
