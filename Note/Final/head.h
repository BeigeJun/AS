
#include <windows.h>
#include <windowsx.h>
#include<stdio.h>
#include <tchar.h>

#define      ROW         1000   //   메모장의 세로 크기
#define      COL         100000   //   메모장의 가로 크기

extern HDC hDC;
extern int xPos;
extern int	yPos;                // 현재 위치
extern int yMax,xMax;                // 최대 크기
extern int MaxWord;
extern int BF_MaxWord;
extern int MaxLine;
extern int BF_MaxLine;
extern int en_flag;
extern int de_flag;
extern int de1_flag;
extern int sc_flag, sc1_flag;
extern SCROLLINFO xScrol, yScrol;
extern RECT RT;
extern TCHAR NOTE[ROW][COL];   //   메모장으로 사용할 이차원 배열
extern size_t Line;      //   메모장(이차원 배열)에서의 문자를 저장할 행 위치
extern size_t Word;      //   메모장(이차원 배열)에서의 문자를 저장할 열 위치
extern int F_Line;
extern int BF_Word;
extern int insert_ox;
extern SIZE size,tSize,scrSize,MAX;
extern HANDLE f;
extern int answer;
extern int xM;
extern int yM;
extern SCROLLINFO si;
extern OPENFILENAME OFN, SFN;
extern TCHAR lpstrFile[MAX_PATH];
extern SIZE size;
void BUT_DOW(HWND, LPARAM);
void NEW(HWND);
void SAVE(HWND);
int OPEN(HWND);
void ENTER(HWND);
void BACK(HWND);
void TAB(HWND);
int WRITE(HWND,WPARAM);
void HOME(HWND);
void END(HWND);
void INSERT(HWND);
void DEL(HWND);
void LEFT(HWND);
void RIGHT(HWND);
void UP(HWND);
void DOWN(HWND);
void PAINT(HWND);
void SCRX(HWND hwnd,WPARAM wParam);
void SCRY(HWND hwnd,WPARAM wParam);
