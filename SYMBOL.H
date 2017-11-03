#ifndef _SYMBOL_H
#define _SYMBOL_H
#include <stdio.h>
#include <stdlib.h>
#define WORDLEN 13 //保留字个数
#define MAXIDLEN 50 //标识符最长长度
#define SYMBOLNUM 32 //种别码个数
typedef enum SYMBOL {
    NOL,IDENT,NUMBER,PLUS,MINUS,TIMES,SLASH,
    ODDSYM,EQL,NEQ,LSS,LEQ,GTR,GEQ,LPAREN,
    RPAREN,COMMA,SEMICOLON,PERIOD,BECOMES,
    BEGINSYM,ENDSYM,IFSYM,THENSYM,WHILESYM,
    WRITESYM,READSYM,DOSYM,CALLSYM,CONSTSYM,
    VARSYM,PROCSYM
} SYMBOL;//定义种别码
void Getchar(void); //取下一个字符
void Getbc(void); //如当前字符为白字符，则读字符至不为白字符时停止
void Concat(void); //将当前字符加入 token 字
void Retract(void); //回退一字符
int Reserve(void); //判断 token 字中单词是否是保留字
int Getsym(void); //从当前文件中识别出一单词，并给出其类型和值
void Errorsym(void); //打印错误信息
#endif
