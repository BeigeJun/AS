#include <windows.h>
#include "resource.h"
#include "Function.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
			WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("메모짱");			// LPCSTR = char *

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, //WINAPI : 윈도우 프로그램이라는 의미
		   LPSTR lpszCmdLine, int nCmdShow)						 //hInstance : 운영체제의 커널이 응용 프로그램에 부여한 ID
{																 //szCmdLine : 커멘트라인 상에서 프로그램 구동 시 전달된 문자열
	HWND	hwnd;												 //iCmdShow : 윈도우가 화면에 출력될 형태
	MSG		msg;
	WNDCLASS WndClass;											 //WndClass 라는 구조체 정의									 
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;			 //출력스타일 : 수직/수평의 변화시 다시 그림		//Horizontal, Vertical 
	WndClass.lpfnWndProc	= WndProc;							 //프로시저 함수명	
	WndClass.cbClsExtra		= 0;								 //O/S 사용 여분 메모리 (Class)
	WndClass.cbWndExtra		= 0;								 //O/s 사용 여분 메모리 (Window)
	WndClass.hInstance		= hInstance;						 //응용 프로그램 ID
	WndClass.hIcon			= LoadIcon(NULL, IDI_QUESTION);	 //아이콘 유형
	WndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);		 //커서 유형
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);//배경색   
	WndClass.lpszMenuName	= MAKEINTRESOURCE(IDR_MENU1); 							 //메뉴 이름
	WndClass.lpszClassName	= lpszClass;						 //클래스 이름
	RegisterClass(&WndClass);									 //앞서 정의한 윈도우 클래스의 주소 // os 에다가 지금 이 클래스를 등록시킴 

	hwnd = CreateWindow(lpszClass,								 //윈도우가 생성되면 핸들(hwnd)이 반환		//실제 윈도우를 만들기 시작 
		lpszClass,                        
        WS_OVERLAPPEDWINDOW,                        
        100,              //x좌표                   
        100,
		1400,              //너비
        700,              //높이     
        NULL,                         
        NULL,                                    
        hInstance,                            
        NULL     												 //생성된 윈도우 정보
	);
	ShowWindow(hwnd, nCmdShow);									 //윈도우의 화면 출력
	UpdateWindow(hwnd);											 //O/S 에 WM_PAINT 메시지 전송

	while(GetMessage(&msg, NULL, 0, 0))							 //WinProc()에서 PostQuitMessage() 호출 때까지 처리
	{															 // 
		TranslateMessage(&msg);
		DispatchMessage(&msg);									 //WinMain -> WinProc  
	}
	return (int)msg.wParam;
}

HDC hdc, saveMemDC, MemDC; // DC 3개 생성->두 개만 쓰면 색 겹쳤을 때 반전 해결 어려움
HBITMAP saveBit, Bit;
int im[100][13];//도형
int x,y,r_x,r_y;				//	마우스 좌표를 얻기 위한 변수
int Old_x,Old_y;				//	마우스 좌표를 얻기 위한 변수
bool Draw = FALSE;	//	마우스의 눌림 혹은 떼짐을 판단하는 변수
int Font_Width = 1;				//	폰트의 두께에 대한 리스트 박스에서 선택된 폰트의 두께
HBRUSH Brush = NULL;
HBRUSH Old_Brush = NULL;
HPEN Old_Pen = NULL;
HPEN Pen = NULL;
int B_Color_r = 0;
int B_Color_g = 0;
int B_Color_b = 0; 
int In_Color_r = 255;
int In_Color_g = 255;
int In_Color_b = 255;
RECT rt;
int count =0;
int mode = 0;
int paint_mode = 0;
int pen_mode = 0;
POINT apnt[3];
TCHAR free_l[100][7];
TCHAR free_xy[100][1000000][2];
int box_check = 0;
int free_size =0;
int index;
OPENFILENAME OFN,SFN;
TCHAR lpstrFile[260];
BITMAPFILEHEADER HF;
BITMAPINFOHEADER HF_info;
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)     
{
	switch (iMsg) 
	{
	case WM_CREATE:			// 윈도우가 생성 (처음생성 될경우) // 단 한번 실행됨 
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rt);

		//hdc를 기반으로 메모리DC 생성.
		saveMemDC = CreateCompatibleDC(hdc);
		MemDC = CreateCompatibleDC(hdc);


		//hdc에 그림을 저장해 둔다.
		saveBit = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		Bit = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		 

		//DC는 메모리 DC일때만 교체가 가능하다.
		(HBITMAP)SelectObject(saveMemDC, saveBit);
		(HBITMAP)SelectObject(MemDC, Bit);


		//색칠하기.
		FillRect(saveMemDC, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));
		FillRect(MemDC, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));


		break;

	case WM_COMMAND:
		switch(LOWORD(wParam)){

		case 40001:
			NEW(hwnd);
			break;

		case 40002:
			OPEN(hwnd);
			break;

			//저장
		case 40003:
			SAVE(hwnd);
			break;
		
			//끝내기
		case 40004:
			PostQuitMessage(0);
			break;

			//원
		case 40005:
			box_check = 1;
			paint_mode = 2;
			break;

			//삼각형
		case 40006:
			box_check = 1;
			paint_mode = 3;
			break;

			//사각형
		case 40007:
			box_check = 1;
			paint_mode= 4;
			break;

		case 40008:
			box_check = 1;
			paint_mode = 1;
			break;

		case 40009:
			box_check = 1;
			paint_mode = 0;
			break;

		case 40010:
			box_check = 1;
			pen_mode = 1;
			break;

		case 40011:
			box_check = 1;
			pen_mode = 2;
			break;

		case 40012:
			box_check = 1;
			pen_mode = 0;
			break;

		case 40013:
			box_check = 1;
			Font_Width = 1;
			break;

		case 40014:
			box_check = 1;
			Font_Width = 3;
			break;

		case 40015:
			box_check = 1;
			Font_Width = 5;
			break;

		case 40016:
			box_check = 1;
			B_Color_r = 255;
			B_Color_g = 0;
			B_Color_b = 0;
			break;

		case 40017:
			box_check = 1;
			B_Color_r = 0;
			B_Color_g = 255;
			B_Color_b = 0;
			break;

		case 40018:
			box_check = 1;
			B_Color_r = 0;
			B_Color_g = 0;
			B_Color_b = 255;
			break;

		case 40019:
			box_check = 1;
			B_Color_r = 255;
			B_Color_g = 255;
			B_Color_b = 255;
			break;

		case 40020:
			box_check = 1;
			B_Color_r = 0;
			B_Color_g = 0;
			B_Color_b = 0;
			break;

		case 40021:
			box_check = 1;
			B_Color_r = 255;
			B_Color_g = 255;
			B_Color_b = 255;
			break;

		case 40022:
			MessageBox(hwnd, TEXT("채우기"),TEXT("메시지 박스"),MB_YESNO);
			break;

		case 40023:
			box_check = 1;
			In_Color_r = 255;
			In_Color_g = 0;
			In_Color_b = 0;
			break;

		case 40024:
			box_check = 1;
			In_Color_r = 0;
			In_Color_g = 255;
			In_Color_b = 0;
			break;

		case 40025:
			box_check = 1;
			In_Color_r = 0;
			In_Color_g = 0;
			In_Color_b = 255;
			break;

		case 40026:
			box_check = 1;
			In_Color_r = 0;
			In_Color_g = 0;
			In_Color_b = 0;
			break;

		case 40027:
			box_check = 1;
			In_Color_r = 255;
			In_Color_g = 255;
			In_Color_b = 255;
			break;

		}

	case WM_LBUTTONDOWN:	//	마우스 누름
		{

			if(box_check == 1){
				box_check = 0;
				break;
			}
			else{
			//	좌표를 얻어와야 한다.
			Old_x = LOWORD(lParam);
			Old_y = HIWORD(lParam);
			
			//	마우스가 눌려 있다.
			Draw = TRUE;

			break;
			}
		}
		
		//	그림 그리는 중( 마우스가 눌린 상태에서만 )
		case WM_MOUSEMOVE:		//	마우스 이동
		{
			if(Draw)
			{
				x = LOWORD(lParam);
				y = HIWORD(lParam);
				InvalidateRect(hwnd, NULL, false);
			}
			break;
		}
		
		//	그림 그리기 끝
		case WM_LBUTTONUP:
		{
			BitBlt(saveMemDC, 0, 0, rt.right, rt.bottom, hdc, 0, 0, SRCCOPY);
			Draw = FALSE;
			if(paint_mode !=0){
				im[count][0] = paint_mode;
				im[count][1] = x;
				im[count][2] = y;
				im[count][3] = Old_x;
				im[count][4] = Old_y;
				im[count][5] = pen_mode;
				im[count][6] = Font_Width;
				im[count][7] = B_Color_r;
				im[count][8] = B_Color_g;
				im[count][9] = B_Color_b;
				im[count][10] = In_Color_r;
				im[count][11] = In_Color_g;
				im[count][12] = In_Color_b;


				count++;
			}
				else{ //자유선일때
				free_xy[count][free_size][0] = x;
				free_xy[count][free_size++][1] = y;
				free_l[count][0] = paint_mode;
				free_l[count][1] = free_size;
				free_l[count][2] = pen_mode;
				free_l[count][3] = Font_Width;
				free_l[count][4] = B_Color_r;
				free_l[count][5] = B_Color_g;
				free_l[count][6] = B_Color_b;
				free_size = 0;
				count++;
			}
			break;
		}

		case WM_RBUTTONUP:
			hdc = GetDC(hwnd);
			r_x = LOWORD(lParam);
			r_y = HIWORD(lParam);

		

			int count_;
			count_ = count;
			BitBlt(MemDC, 0, 0, rt.right, rt.bottom, saveMemDC, 0, 0, SRCCOPY);
			for(int i = count_ -1;i>=0; i--){
				if(r_x < im[i][1] && r_x > im[i][3] && r_y < im[i][2] && r_y > im[i][4]){//좌표에 걸리면
					Pen = CreatePen(im[i][5], im[i][6],RGB(im[i][7],im[i][8],im[i][9]) );
					Old_Pen = (HPEN)SelectObject(MemDC, Pen);

					Brush = CreateSolidBrush(RGB(im[i][10],im[i][11],im[i][12]));
					Old_Brush = (HBRUSH)SelectObject(MemDC, Brush);
					switch(im[i][0]){
					case 2:
						Ellipse(MemDC,  im[i][1], im[i][2], im[i][3], im[i][4]);
						break;
		
					case 3: 
						apnt[0].x = (im[i][1] + im[i][3])/2;
						apnt[0].y = im[i][4];
						apnt[1].x = im[i][3];
						apnt[1].y = im[i][2];
						apnt[2].x = im[i][1];
						apnt[2].y = im[i][2];
						Polygon(MemDC, apnt, 3);
						break;

					case 4:
						Rectangle(MemDC,im[i][1],im[i][2], im[i][3], im[i][4]);
						break;

					}
				}
			}
			BitBlt(hdc, 0, 0, rt.right, rt.bottom, MemDC, 0, 0, SRCCOPY);
			BitBlt(saveMemDC, 0, 0, rt.right, rt.bottom, hdc, 0, 0, SRCCOPY);
			break;

		case WM_PAINT:
			PAINTSTRUCT ps;

			Pen = CreatePen(pen_mode, Font_Width, RGB(B_Color_r,B_Color_g,B_Color_b));
			Old_Pen = (HPEN)SelectObject(MemDC, Pen);

			Brush = CreateSolidBrush(RGB(In_Color_r,In_Color_g,In_Color_b));
			Old_Brush = (HBRUSH)SelectObject(MemDC, Brush);

			if(paint_mode != 0)
				BitBlt(MemDC, 0, 0, rt.right, rt.bottom,saveMemDC , 0, 0, SRCCOPY); 

			switch(paint_mode){
			if(Draw == TRUE){
			
			case 0 :
					{
						if(x==0&&y==0)
							break;
						MoveToEx( MemDC, Old_x, Old_y, NULL );
						LineTo( MemDC, x, y);

						free_xy[count][free_size][0] = x;
						free_xy[count][free_size++][1] = y;

						Old_x = x;
						Old_y = y;
						break;
					}

			case 1 : 
					{
						MoveToEx( MemDC, Old_x, Old_y, NULL );
						LineTo( MemDC, x, y);
						break;
					}


			case 2:
					{
						Ellipse(MemDC,  x, y, Old_x, Old_y);
						break;
					}
			case 3:
					{
						apnt[0].x = (x + Old_x)/2;
						apnt[0].y = Old_y;
						apnt[1].x = x;
						apnt[1].y = y;
						apnt[2].x = Old_x;
						apnt[2].y = y;
						Polygon(MemDC, apnt, 3);
						break;
					}
			case 4:
					{
						Rectangle(MemDC, x, y, Old_x, Old_y);
						break;
					}
				}

			}
			
			BitBlt(hdc, 0, 0, rt.right, rt.bottom, MemDC, 0, 0, SRCCOPY);
			EndPaint(hwnd, &ps);
			break;


	case WM_DESTROY:			//프로그램 종료 처리 // 예를들어 동적할당들을 했으면 꼭 해지를 해야함
		{
			PostQuitMessage(0);
			break;
		}
	} 
	return DefWindowProc(hwnd, iMsg, wParam, lParam);			 //CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달
}
