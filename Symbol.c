#include "basedata.h"
#include "symbol.h"
#include <conio.h>
#include <string.h>
#include <ctype.h>
char *WORD[WORDLEN]= {"BEGIN","CALL","CONST","DO",
                      "END","IF","ODD","PROCEDURE",
                      "READ","THEN","VAR","WHILE",
                      "WRITE"
                     };//�������ַ�����,���ڽ��������ֱ���תΪ�ַ������
SYMBOL WSYM[WORDLEN]= {BEGINSYM,CALLSYM,CONSTSYM,
                       DOSYM,ENDSYM,IFSYM,ODDSYM,
                       PROCSYM,READSYM,THENSYM,
                       VARSYM,WHILESYM,WRITESYM
                      };//�������ֱ����
char* SNAME[SYMBOLNUM]= {
	"NOL","IDENT","NUMBER","PLUS","MINUS","TIMES",
	"SLASH","ODDSYM","EQL","NEQ","LSS","LEQ","GTR",
	"GEQ","LPAREN","RPAREN","COMMA","SEMICOLON",
	"PERIOD","BECOMES","BEGINSYM","ENDSYM","IFSYM",
	"THENSYM","WHILESYM","WRITESYM","READSYM",
	"DOSYM","CALLSYM","CONSTSYM","VARSYM","PROCSYM"
};
//�����ַ�����,���ڽ��������ֱ���תΪ�ַ������
SYMBOL sym;//�����ʶ�ĵ����ֱ���
char token[MAXIDLEN+1];//�����ʶ��ĵ���
int num;//�����ʶ�������ֵ
char ch;//�����ʶ����ַ�
int col=1,row=1;//��ǰ�к���ֵ
FILE *fd;//ָ��������ļ�
extern FILE *fout;//ָ���Ž���ļ�
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
	}//Ϊ���ַ���һֱ������Ϊ���ַ�
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
		temp[i]=toupper(token[i]);//����ǰ token ���Դ�д��ʽ���� temp ��
	}
	temp[i]='\0';
	for(i=0; i<WORDLEN; i++) {
		if(!strcmp(WORD[i],temp))
			break;
	}//�жϵ�ǰ token �Ƿ��Ǳ�����
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
	Getbc();//�˵����ַ�
	strcpy(token,"");
	if(isalpha(ch)) {
//����ĸ��ͷ���Ǳ�ʶ��
		num=0;
		Concat();
		Getchar();
		while(isalnum(ch)) {
			Concat();
			Getchar();
		}
		Retract();//���ڳ�ǰ�����ˣ����Ի���һ���ַ�
		k=Reserve();//�жϴ˱�ʶ���Ƿ��Ǳ�����
		if(k!=-1) {
			sym=WSYM[k];//���������ֱ������ sym ��
		} else {
			sym=IDENT;//��һ���ʶ���ֱ������ sym ��
		}//end else k!=-1;
	}//end of if isalpha
	else if(isdigit(ch)) {
//�����ֿ�ͷ��Ϊ�޷�������
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
		Retract();//����
		if(flag) { //�����޷���������������ֵ���� num ��
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
				if(ch!='=') {//���󲻸�'=',�����
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
