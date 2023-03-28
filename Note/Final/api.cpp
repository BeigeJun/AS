
//WndClass정의(윈도우의 기반이 되는 클래스를 정의한다) -> CreateWindow(메모리상에 윈도우를 만든다) -> ShowWindow(화면상에 윈도우를 표시한다) -> 메시지루프(사용자로부터 메시
#include <windows.h>
#include <windowsx.h>
#include<stdio.h>
#include <tchar.h>
#include "resource.h"
#include "head.h"


#define      ROW         1000   //   메모장의 세로 크기
#define      COL         100000   //   메모장의 가로 크기

//size_t 는 unsigned int 이며, 문자열이나 메모리의 사이즈를 나타낼 때 사용합니다. "unsigned int"를
//typedef unsigned int size_t;
//이렇게 size_t 라는 이름으로 정의해 놓은 것입니다.

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
         WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("메모장");         // LPCSTR = char *

///////////////////////////시작점///////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, //WINAPI : 윈도우 프로그램이라는 의미
         LPSTR lpszCmdLine, int nCmdShow)                   //hInstance : 운영체제의 커널이 응용 프로그램에 부여한 ID ex) 메모장1 메모장2
{                                                 //szCmdLine : 커멘트라인 상에서 프로그램 구동 시 전달된 문자열
   HWND   hwnd;                                     //iCmdShow : 윈도우가 화면에 출력될 형태 
   WNDCLASS WndClass;                                  //WndClass 라는 구조체 정의                            


   WndClass.style         = CS_HREDRAW | CS_VREDRAW;          //출력스타일 : 수직/수평의 변화시 다시 그림      //Horizontal, Vertical 
   WndClass.lpfnWndProc   = WndProc;                      //프로시저 함수명   
   WndClass.cbClsExtra      = 0;                         //O/S 사용 여분 메모리 (Class)
   WndClass.cbWndExtra      = 0;                         //O/s 사용 여분 메모리 (Window)
   WndClass.hInstance      = hInstance;                   //응용 프로그램 ID
   WndClass.hIcon         = LoadIcon(NULL, IDI_QUESTION);        //아이콘 유형
   WndClass.hCursor      = LoadCursor(NULL, IDC_ARROW);       //커서 유형
   WndClass.hbrBackground   = (HBRUSH)GetStockObject(WHITE_BRUSH);//배경색   
   WndClass.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU1);                         //메뉴 이름
   WndClass.lpszClassName   = lpszClass;                   //클래스 이름
   RegisterClass(&WndClass);                            //앞서 정의한 윈도우 클래스의 주소 // os 에다가 지금 이 클래스를 등록시킴 

   hwnd = CreateWindow(lpszClass,                         //윈도우가 생성되면 핸들(hwnd)이 반환      //실제 윈도우를 만들기 시작 
      lpszClass,                        
        WS_OVERLAPPEDWINDOW| WS_VSCROLL | WS_HSCROLL,                        
        100,              //x좌표                   
        100,              //y좌표             
        640,              //너비
        480,              //높이     
        NULL,                         
        NULL,                                    
        hInstance,                            
        NULL                                          //생성된 윈도우 정보
   );
   ShowWindow(hwnd, nCmdShow);                            //윈도우의 화면 출력
   UpdateWindow(hwnd);                                  //O/S 에 WM_PAINT 메시지 전송


   MSG msg;
   memset( &msg, 0, sizeof(msg) );
   while(GetMessage(&msg, NULL, 0, 0))                      //WinProc()에서 PostQuitMessage() 호출 때까지 처리 이 함수가 읽어들인 메시지가 프로그램을 종료하라는 WM_Quit일경우 Fail 리턴.
   {                                              // 
      TranslateMessage(&msg);                                  //키보드 입력 메시지를 가공하여 프로그램에서 쉽게 쓸 수 있도록 해 준다. 
                                                 //윈도우즈는 키보드의 어떤 키가 눌러졌다거나 떨어졌을 때 키보드 메시지를 발생시키는데 이 함수는 키보드의 눌림(WM_KEYDOWN)과 떨어짐(WM_KEYUP)이 
                                                 //연속적으로 발생할 때 문자가 입력되었다는 메시지(WM_CHAR)를 만드는 역할을 한다. 예를 들어 A키를 누른 후 다시 A키를 떼면 A문자가 입력되었다는 메시지를 만들어 낸다.
      
      
      DispatchMessage(&msg);                            //WinMain -> WinProc  
                                                 //시스템 메시지 큐에서 꺼낸 메시지를 프로그램의 메시지 처리 함수(WndProc)로 전달한다. 
                                                 //이 함수에 의해 메시지가 프로그램으로 전달되며 프로그램에서는 전달된 메시지를 점검하여 다음 동작을 결정하게 된다.
                                                 //메시지 루프에서 하는 일은 메시지를 꺼내고, 필요한 경우 약간 형태를 바꾼 후 응용 프로그램으로 전달하는 것 뿐이다. 이 과정은 WM_QUIT 메시지가 전달될 때까지, 
                                                               //즉 프로그램이 종료될때까지 반복된다. 결국 메시지 루프가 하는 일이란 메시지 큐에서 메시지를 꺼내 메시지 처리 함수로 보내주는 것 뿐이다.
                                                 //실제 메시지 처리는 별도의 메시지 처리 함수(WndProc)에서 수행한다. 메시지는 시스템의 변화에 대한 정보이며 MSG라는 구조체에 보관된다. MSG 구조체는 다음과 같이 정의되어 있다.
   }
   return (int)msg.wParam;
}

HDC hDC;
int xPos = 0;
int	yPos = 0;                // 현재 위치
int yMax,xMax;                // 최대 크기
int xInc, yInc;

RECT RT;
TCHAR NOTE[ROW][COL] = { 0, };   //   메모장으로 사용할 이차원 배열
size_t Line = 0;      //   메모장(이차원 배열)에서의 문자를 저장할 행 위치
size_t Word = 0;      //   메모장(이차원 배열)에서의 문자를 저장할 열 위치
int F_Line = 0;
int BF_Word = 0;
int insert_ox = 0;
int MaxWord = 0;
int BF_MaxWord = 0;
int MaxLine = 0;
int BF_MaxLine = 0;
int en_flag = 0;
int de_flag = 0;
int de1_flag = 0;
int wr_flag = 0;
int sc_flag = 0;
int sc1_flag = 0;
SIZE size,tSize,scrSize,MAX;
HANDLE f;
int passchar = 0, passenter = 0, pass = 0, passend =0, passscroll=0;
int answer;
int xM = 0;
int yM = 0;
SCROLLINFO si;
OPENFILENAME OFN, SFN;
TCHAR lpstrFile[MAX_PATH]="\0";
SCROLLINFO xScrol, yScrol;


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)     
{
	hDC = GetDC(hwnd);


    switch (iMsg) 
   {
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


    case WM_CREATE:                           //메모장을 만드는 순간 메뉴버튼 생성
		break;

	case WM_HSCROLL:
				sc_flag = 1;
                SCRX(hwnd,wParam);
				InvalidateRect(hwnd, NULL, TRUE);
                break;

    case WM_VSCROLL:
			    sc1_flag = 1;
                SCRY(hwnd,wParam);
				InvalidateRect(hwnd, NULL, TRUE);
                break;

	case WM_SIZE:
				if(HIWORD(lParam) >= 12)				// rt.bottom이 - 값이 되는 것을 방지.
					RT.bottom = HIWORD(lParam) - 12;
				GetClientRect(hwnd, &RT);
				xScrol.cbSize = sizeof(SCROLLINFO);
				xScrol.fMask = SIF_ALL | SIF_DISABLENOSCROLL;
	            xScrol.nMin = 0;
				xScrol.nMax = RT.right;
				xScrol.nPage = RT.right;

				yScrol.cbSize = sizeof(SCROLLINFO);
				yScrol.fMask = SIF_ALL | SIF_DISABLENOSCROLL;
	            yScrol.nMin = 0;
				yScrol.nMax = RT.bottom;
				yScrol.nPage = RT.bottom;

				SetScrollInfo(hwnd, SB_VERT,&xScrol,TRUE);
				SetScrollPos(hwnd, SB_VERT, xPos, TRUE);

				SetScrollInfo(hwnd, SB_HORZ,&yScrol,TRUE);
				SetScrollPos(hwnd, SB_HORZ, yPos, TRUE);

	case WM_LBUTTONDOWN:
		{
			BUT_DOW(hwnd,lParam);
			break;
		}

	case WM_COMMAND:
		switch(LOWORD(wParam)){

		case ID_MENU_NEW:
			NEW(hwnd);
			break;

		case ID_MENU_OPEN:
			OPEN(hwnd);
			break;
	
		case ID_MENU_SAVE:
			SAVE(hwnd);
			break;
		
		case ID_MENU_EXIT:
			PostQuitMessage(0);
			break;
		}
    case WM_SETFOCUS:                                   //처음 캐럿을 만들어주는 문자가 시작하는 위치
            CreateCaret(hwnd, (HBITMAP) NULL, 2, 12); 
            SetCaretPos(0, 0); 
            ShowCaret(hwnd); 
            break; 

    case WM_KILLFOCUS:
            HideCaret(hwnd); // 캐럿 숨기기
            DestroyCaret(); // 캐럿 파괴
            break;

    case WM_CHAR:
      {
         switch(wParam)
         {

            case VK_RETURN:   //   엔터 키가 눌린 경우
				ENTER(hwnd);
				break;

            case VK_BACK:   //   백스페이스 키가 눌린 경우
				BACK(hwnd);
				break;

			case VK_TAB:
				TAB(hwnd);
				break;

			default:
				WRITE(hwnd,wParam);
				break;
		 }
	  }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	case WM_KEYDOWN:
				switch(wParam){
				case VK_HOME:       // Home 
					HOME(hwnd);
		            break; 

			    case VK_END:        // End 
					END(hwnd);
					break; 

				case VK_INSERT:
					INSERT(hwnd);
					break;
				
				case VK_DELETE:
					DEL(hwnd);
					break;
 
				case VK_LEFT:       // Left arrow
					LEFT(hwnd);
					break; 
 
				case VK_RIGHT:      // Right arrow
					RIGHT(hwnd);
					break; 
 
				case VK_UP:         // Up arrow 
					UP(hwnd);
					break; 
 
				case VK_DOWN:       // Down arrow 
					DOWN(hwnd);
					break; 
			}

	case WM_PAINT:
      {
		 PAINTSTRUCT ps;
	     hDC = BeginPaint(hwnd, &ps);
		 BF_MaxWord = MaxWord;
	for(int i = 0; i<=F_Line; i++){
		if(lstrlen(NOTE[i])>MaxWord){
			MaxWord = lstrlen(NOTE[i]);
			MaxLine = Line;
			GetTextExtentPoint(hDC, NOTE[i], MaxWord, &MAX);
		}
	}


      GetTextExtentPoint(hDC,NOTE[Line],Word,&size);
	  GetTextExtentPoint(hDC, NOTE[Line], xPos, &scrSize); //그 줄의 스크롤 길이만큼의 크기
			 // x 스크롤 크기
      if(RT.right < MAX.cx){
          if(Line == MaxLine)
          {
             if(de1_flag == 1)
             {
               xScrol.nMax--;
             }
             else if(wr_flag == 1)
             {
                xScrol.nMax++;
             }
             SetScrollPos(hwnd, SB_HORZ, xPos, TRUE);
          }
      }
      else if (RT.right >= MAX.cx)
      {
         SetScrollPos(hwnd, SB_HORZ, xPos, TRUE);
      }



			 // y 스크롤 크기
		if((RT.bottom < 16*F_Line)){
			if(en_flag == 1)
			{
				yScrol.nMax++;
			}
			else if(de_flag==1)
			{
				yScrol.nMax--;
			}
			SetScrollPos(hwnd, SB_VERT, yPos, TRUE);
		}
		else if( 0 > 16*F_Line && de_flag){
			
			SetScrollPos(hwnd, SB_VERT, yPos, TRUE);
		}

        de_flag =0, en_flag =0, de1_flag =0, wr_flag =0;

		SetCaretPos(size.cx - scrSize.cx, 16*(Line - yPos));

		yScrol.nPos = yPos;
		SetScrollInfo(hwnd, SB_VERT, &yScrol, TRUE);

		xScrol.nPos = xPos;
		SetScrollInfo(hwnd, SB_HORZ, &xScrol, TRUE);

		for(int i = yPos; i <= F_Line; i ++){
			TextOut(hDC, -scrSize.cx,  16*(i-yPos), NOTE[i], lstrlen(NOTE[i]));			//도화지, x 좌표 ,y좌표, 출력내용, 출력할 사이즈
		}
		EndPaint(hwnd, &ps);
		break;
      }
   
   
   
   
    case WM_CLOSE:         //프로그램 종료 처리 // 예를들어 동적할당들을 했으면 꼭 해지를 해야함
      int num = MessageBox(hwnd, TEXT("저장하시겠습니까?"),TEXT("메시지 박스"),MB_YESNO);
      switch(num){
         case IDYES:
			SAVE(hwnd);
            PostQuitMessage(0);
            break;
         case IDNO:
            PostQuitMessage(0);
            break;
         }
      }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   return DefWindowProc(hwnd, iMsg, wParam, lParam);          //CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달
}
