#ifndef _SYMBOL_H
#define _SYMBOL_H
#include <stdio.h>
#include <stdlib.h>
#define WORDLEN 13 //�����ָ���
#define MAXIDLEN 50 //��ʶ�������
#define SYMBOLNUM 32 //�ֱ������
typedef enum SYMBOL {
    NOL,IDENT,NUMBER,PLUS,MINUS,TIMES,SLASH,
    ODDSYM,EQL,NEQ,LSS,LEQ,GTR,GEQ,LPAREN,
    RPAREN,COMMA,SEMICOLON,PERIOD,BECOMES,
    BEGINSYM,ENDSYM,IFSYM,THENSYM,WHILESYM,
    WRITESYM,READSYM,DOSYM,CALLSYM,CONSTSYM,
    VARSYM,PROCSYM
} SYMBOL;//�����ֱ���
void Getchar(void); //ȡ��һ���ַ�
void Getbc(void); //�統ǰ�ַ�Ϊ���ַ�������ַ�����Ϊ���ַ�ʱֹͣ
void Concat(void); //����ǰ�ַ����� token ��
void Retract(void); //����һ�ַ�
int Reserve(void); //�ж� token ���е����Ƿ��Ǳ�����
int Getsym(void); //�ӵ�ǰ�ļ���ʶ���һ���ʣ������������ͺ�ֵ
void Errorsym(void); //��ӡ������Ϣ
#endif