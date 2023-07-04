#include<Windows.h>

extern HDC hdc, saveMemDC, MemDC;
extern HBITMAP saveBit, Bit;
extern int im[100][13];//도형
extern int x,y,r_x,r_y;				//	마우스 좌표를 얻기 위한 변수
extern int Old_x,Old_y;				//	마우스 좌표를 얻기 위한 변수
extern bool Draw;	//	마우스의 눌림 혹은 떼짐을 판단하는 변수
extern int Font_Width;				//	폰트의 두께에 대한 리스트 박스에서 선택된 폰트의 두께
extern HBRUSH Brush;
extern HBRUSH Old_Brush;
extern HPEN Old_Pen;
extern HPEN Pen;
extern int B_Color_r;
extern int B_Color_g;
extern int B_Color_b; 
extern int In_Color_r;
extern int In_Color_g;
extern int In_Color_b;
extern RECT rt;
extern int count;
extern int mode;
extern int paint_mode;
extern int pen_mode;
extern POINT apnt[3];
extern TCHAR free_l[100][7];
extern TCHAR free_xy[100][1000000][2];
extern int box_check;
extern int free_size;
extern int index;
extern OPENFILENAME OFN, SFN;
extern TCHAR lpstrFile[260];
extern BITMAPFILEHEADER HF;
extern BITMAPINFOHEADER HF_info;

void NEW(HWND);
void OPEN(HWND);
void SAVE(HWND);
