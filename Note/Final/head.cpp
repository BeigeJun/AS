
#include "head.h"

void BUT_DOW(HWND hwnd, LPARAM lParam)
{
		GetTextExtentPoint(hDC, NOTE[Line], xPos, &scrSize);
		xM = LOWORD(lParam) + scrSize.cx;
		yM = HIWORD(lParam)+(16*yPos);

		Line = yM/16;

		if(Line > F_Line){
			Line = F_Line;
			Word = lstrlen(NOTE[Line]);
			InvalidateRect( hwnd, NULL, TRUE );
		}
		else
		{
			GetTextExtentPoint(hDC, NOTE[Line],lstrlen(NOTE[Line]), &tSize);
			if(tSize.cx >= xM)
			{
				SIZE size2;
					for(int i = 0 ; i <= lstrlen(NOTE[Line]); i ++)
					{
						GetTextExtentPoint(hDC, NOTE[Line],i, &size2);
						if(size2.cx < xM)
						{
							Word = i;
						}
					}
				
				InvalidateRect( hwnd, NULL, TRUE );
			}
			else
				{
					Word = lstrlen(NOTE[Line]);
					InvalidateRect( hwnd, NULL, TRUE );
				}
			}
}
void NEW(HWND hwnd)
{

	memset(NOTE,0,sizeof(NOTE));
	Line = 0;
	Word =0;
	InvalidateRect(hwnd, NULL, TRUE);

}
void SAVE(HWND hwnd)
	{
			memset(&SFN, 0, sizeof(OPENFILENAME));
			SFN.lStructSize = sizeof(OPENFILENAME);
			SFN.hwndOwner = hwnd;
			SFN.lpstrFilter = _T("모든 파일(*.*) \0*.*\0텍스트 파일(*.txt) \0*.txt\0");
			SFN.lpstrFile =lpstrFile;
			SFN.nMaxFile = MAX_PATH;
			DWORD dwRead;
			TCHAR strRead[MAX_PATH];
			WORD dw = 0xFEFF;
			HANDLE f;

			int index = 0;
			if(GetSaveFileName(&SFN) != 0){
				f = CreateFile(SFN.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL);

				for(int i=0; i<=F_Line; i++){
					for(int j=0; lstrlen(NOTE[i]) > j; j++){
						strRead[index] = NOTE[i][j];
						index++;
					}
					if(i != F_Line)
					{
						strRead[index] = '\n';
						index ++;
					}
				}
				WriteFile(f, strRead, index, &dwRead, NULL); 
				CloseHandle(f);
			}
		}
int OPEN(HWND hwnd)
{
			NEW(hwnd);
			HANDLE hFile;
			DWORD dwRead;
			DWORD count = 0;
			TCHAR strRead[MAX_PATH];
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner=hwnd;
			OFN.lpstrFilter=_T("모든 파일(*.*) \0*.*\0텍스트 파일(*.txt) \0*.txt\0");
			OFN.lpstrFile=lpstrFile;
			OFN.nMaxFile=ROW;



			if (GetOpenFileName(&OFN)!=0) {
				hFile = CreateFile(OFN.lpstrFile, GENERIC_READ, 0, NULL,
				OPEN_EXISTING, 0, NULL);

				ReadFile(hFile, strRead, MAX_PATH, &dwRead, NULL); // buf에 파일크기만큼 저장

				for(int i=0; i<lstrlen(strRead); i++)
					{
						if(strRead[i] ==10)
						{
							NOTE[Line][Word] = NULL;
							Line++;
							F_Line++;
							count++;
							Word = 0;
						}
						else if(count == dwRead)
						{
							CloseHandle(hFile); // 이제 필요없어진 핸들은 닫는다
							InvalidateRect(hwnd, NULL, TRUE); // WM_PAINT를 발생시킨다
							return 0;
						}
						else
						{	
							NOTE[Line][Word] = strRead[i];
							count++;
							Word++;
						}
					}
					return 0;
			}
}
void ENTER(HWND hwnd)
		{
		passenter = 1;
				  if(Line != F_Line)
				  {
						for(int i = F_Line ; i != Line; i--)
						{
							for(int j = lstrlen(NOTE[i]) ; j > 0 ; j-- )
							 {
								NOTE[i+1][j-1] = NOTE[i][j-1];
								NOTE[i][j-1]=NULL;
							 }
						}
						if(lstrlen(NOTE[Line]) != Word)
						{
							for(int i = lstrlen(NOTE[Line]) ; i > Word ; i--)
							{
								NOTE[Line+1][i-Word-1] = NOTE[Line][i-1];
								NOTE[Line][i-1]=NULL;
							}
						}
				  }
				  else
				  {
					  if(lstrlen(NOTE[Line]) != Word)
						{
							for(int i = lstrlen(NOTE[Line]) ; i > Word ; i--)
							{
								NOTE[Line+1][i-Word-1] = NOTE[Line][i-1];
								NOTE[Line][i-1]=NULL;
							}
						}
					  else
					  {}
				  }
				  Line++; F_Line++; Word = 0; en_flag =1;
				  GetTextExtentPoint(hDC, NOTE[Line], Word, &size);
                  SetCaretPos(size.cx, Line*16);
                  InvalidateRect( hwnd, NULL, TRUE );
				}
void BACK(HWND hwnd)
	{
		
			   while(1)
			   {
               if ( Line == 0 && Word == 0 )
               {break;}

				passchar = 0;
               if( Word == 0 )
               {                                              //중간줄 삭제
					
						BF_Word = lstrlen(NOTE[Line-1]);

						for(int i = lstrlen(NOTE[Line]); i >= 0 ; i--)
						{
							NOTE[Line-1][i+BF_Word] = NOTE[Line][i];
							NOTE[Line][i] = NULL;
							
						}
						if(F_Line>Line)
						{
							for(int i = Line; F_Line > i ; i++)
							{
								for(int j = lstrlen(NOTE[i+1]) ; 0 <= j ; j--)
								{
									NOTE[i][j] = NOTE[i+1][j];
									NOTE[i+1][j] = NULL;
								}
							}
						}
						F_Line--;
						Line--;
						de_flag = 1;
						Word = BF_Word;
						GetTextExtentPoint(hDC, NOTE[Line],Word, &size);
						SetCaretPos(size.cx, Line*16);
						InvalidateRect( hwnd, NULL, TRUE );
						break;
               }

               else
               {
				  if(lstrlen(NOTE[Line])==Word)
				  {
					NOTE[Line][--Word] = NULL;
				  }
				  else
				  {
					  for(int i = Word - 1; i < lstrlen(NOTE[Line]) ; i++)
					  {
						NOTE[Line][i] = NOTE[Line][i+1];
					  }
					  NOTE[Line][lstrlen(NOTE[Line])] = NULL;
					  Word--;
				  }
				  de1_flag = 1;
				  GetTextExtentPoint(hDC, NOTE[Line], Word, &size);
			      SetCaretPos(size.cx, Line*16);
                  InvalidateRect( hwnd, NULL, TRUE );
				  break;
               }
            }
}
void TAB(HWND hwnd)
	{
		wr_flag = 1;
					if(Word == lstrlen(NOTE[Line]))
					{
						for(int i = 0 ; i < 8 ; i++)
						{
							NOTE[Line][Word + i] = ' ';
						}
					}
					else
					{
						for(int i = lstrlen(NOTE[Line]) ; i > Word ; i--)
						{
							NOTE[Line][i+7] = NOTE[Line][i-1];
						}
						for(int i = 0 ; i < 8 ; i++)
						{
							NOTE[Line][Word + i] = ' ';
						}
					}
					Word = Word + 8;
					GetTextExtentPoint(hDC, NOTE[Line], Word, &size);
					SetCaretPos(size.cx, Line*16);
					InvalidateRect(hwnd, NULL, TRUE);
				}
int WRITE(HWND hwnd,WPARAM wParam)
{
	if(lstrlen(NOTE[Line])==Word)   // 맨 끝에서 입력할 때
				{
					if( Line < ROW )
					{
						NOTE[Line][Word] = (TCHAR)wParam;         
						NOTE[Line][Word + 1] = NULL;         
						Word++;
						wr_flag = 1;

			
            
				   /*   막바지일때 아무것도 안하기 */
						if ( Word == COL )
						{
							return 0;			      
						}
					}
				 }
				 else if(lstrlen(NOTE[Line])!=Word)       //중간에서 입력할때
				 {
					 if(insert_ox == 0)
					 {
						 for(int i = lstrlen(NOTE[Line]) ; i>Word ; i--)
						 {
							 NOTE[Line][i] = NOTE[Line][i-1];
						 }
						 NOTE[Line][Word] = (TCHAR)wParam;                  
						 Word++;
						 wr_flag = 1;
						 InvalidateRect( hwnd, NULL, TRUE );
					 }
					 else
					 {
						 NOTE[Line][Word] = (TCHAR)wParam;
						 Word++;
						 InvalidateRect( hwnd, NULL, TRUE );
					 }
			 
			 
				 }
				 GetTextExtentPoint(hDC, NOTE[Line], Word, &size);
				 SetCaretPos(size.cx, Line*16);
			     InvalidateRect( hwnd, NULL, TRUE );
			}
void HOME(HWND hwnd)
{
	SetCaretPos(0, Line*16);
	Word = 0;
	xPos = 0;
	InvalidateRect(hwnd, NULL, TRUE);
}
void END( HWND hwnd)
{
	Word = lstrlen(NOTE[Line]);
	InvalidateRect(hwnd, NULL, TRUE);
}
void INSERT(HWND hwnd)
{
	if(insert_ox == 0)
	{insert_ox = 1;}
	else
	{insert_ox = 0;}
}
void DEL(HWND hwnd)
	{
						if(Line != F_Line)
						{
							if(Word == lstrlen(NOTE[Line]))
							{
								int j = lstrlen(NOTE[Line+1])-1;
								for(int i = lstrlen(NOTE[Line+1])-1 ; i >= 0 ; i--)
								{

									NOTE[Line][lstrlen(NOTE[Line])+j] = NOTE[Line+1][i];
									NOTE[Line+1][i] = NULL;
									j--;
								}
								for(int i = Line+1; F_Line > i; i++)
								{
									for(int j = lstrlen(NOTE[i+1]) ; 0 <= j ; j--)
									{
										NOTE[i][j] = NOTE[i+1][j];
										NOTE[i+1][j] = NULL;
									}
								}
								F_Line--;
								de_flag = 1;
								GetTextExtentPoint(hDC, NOTE[Line],Word, &size);
								SetCaretPos(size.cx, Line*16);
								InvalidateRect( hwnd, NULL, TRUE );
							}
							else
							{
								for(int i = Word +1 ; i < lstrlen(NOTE[Line]) ; i++)
								{
									NOTE[Line][i-1] = NOTE[Line][i];
								}
								NOTE[Line][lstrlen(NOTE[Line])-1] = NULL;
								de1_flag = 1;
								InvalidateRect(hwnd, NULL, TRUE);
							}
						}
						else
						{
							if(Word == lstrlen(NOTE[Line]))
							{
							}
							else
							{
								for(int i = Word +1 ; i < lstrlen(NOTE[Line]) ; i++)
									{
										NOTE[Line][i-1] = NOTE[Line][i];
									}
									NOTE[Line][lstrlen(NOTE[Line])-1] = NULL;
									de1_flag = 1;
									InvalidateRect(hwnd, NULL, TRUE);
							}
						}
					}
void LEFT(HWND hwnd)
{
	if(Word==0)
					{
						if(Line!=0)
						{
							Line--;
							Word = lstrlen(NOTE[Line]);
						}
					}
					else
					{
						Word--;
					}
					GetTextExtentPoint(hDC, NOTE[Line], Word, &size);
					SetCaretPos(size.cx, Line*16);
					InvalidateRect(hwnd, NULL, TRUE);
}
void RIGHT(HWND hwnd)
{
	if(Word == lstrlen(NOTE[Line]))
					{
						if(Line!=F_Line)
						{
							Line++;
							Word = 0;
						}
						else if(Line == F_Line)
						{}
					}
					else{
						Word++;
					}
					GetTextExtentPoint(hDC, NOTE[Line], Word, &size);
					SetCaretPos(size.cx, Line*16);
					InvalidateRect(hwnd, NULL, TRUE);
}
void UP(HWND hwnd)
{
	if(Line != 0)
					{
						if(lstrlen(NOTE[Line-1])<Word)
						{
							Word = lstrlen(NOTE[Line-1]);
						}
						Line--;
					}
					GetTextExtentPoint(hDC, NOTE[Line], Word, &size);
					SetCaretPos(size.cx, Line*16);
					InvalidateRect(hwnd, NULL, TRUE);
}
void DOWN(HWND hwnd)
{
	if(Line != F_Line)
					{
						if(lstrlen(NOTE[Line+1])<Word)
						{
							Word = lstrlen(NOTE[Line+1]);
						}
						Line++;
					}
					else if(Line==F_Line)
					{}
					GetTextExtentPoint(hDC, NOTE[Line], Word, &size);
					SetCaretPos(size.cx, Line*16);
					InvalidateRect(hwnd, NULL, TRUE);
}
void SCRX(HWND hwnd,WPARAM wParam)
{
	switch (LOWORD(wParam))
                {
                case SB_LINELEFT:
                        xPos = max(0,xPos-5);
                        break;
                case SB_LINERIGHT:
                        xPos = min(COL,xPos+5);
                        break;
                case SB_PAGELEFT:
                        xPos = max(0,xPos-5);
                        break;
                case SB_PAGERIGHT:
                        xPos = min(COL,xPos+5);
                        break;
                case SB_THUMBTRACK:
                        xPos = HIWORD(wParam);
						while(RT.right + xPos > xScrol.nMax)
							xPos--;
                        break;
                }
}
void SCRY(HWND hwnd,WPARAM wParam)
{
	switch ( LOWORD(wParam) )
                {
                case SB_LINEUP:
                        yPos = max(0,yPos - 1);
                        break;
                case SB_LINEDOWN:
                        yPos = min(ROW,yPos+1);
                        break;
                case SB_PAGEUP:
                        yPos = max(0,yPos - 1);
                        break;
                case SB_PAGEDOWN:
                        yPos = min(ROW,yPos+1);
                        break;
                case SB_THUMBTRACK:
                        yPos = HIWORD(wParam);
						while(RT.bottom+yPos-12 > yScrol.nMax)
							yPos--;
                        break;
                }
}
void PAINT(HWND hwnd) 
{
PAINTSTRUCT ps;
hDC = BeginPaint(hwnd, &ps);
		 GetClientRect(hwnd, &RT);
		 SetScrollInfo(hwnd,SB_HORZ,&xScrol,TRUE);
		 SetScrollInfo(hwnd,SB_VERT,&yScrol,TRUE);
         //   이차원 배열의 각 행들이 문자열이므로, 행을 탐색해서 문자열 출력
		 BF_MaxWord = MaxWord;
		 BF_MaxLine = MaxLine;
         for( int i = 0; i < F_Line+1; i++ )
         {

			if(MaxWord < lstrlen(NOTE[i]))
			{
				MaxWord = lstrlen(NOTE[i]);
				MaxLine = i;
				GetTextExtentPoint(hDC,NOTE[Line],MaxWord,&MAX);
			}
            TextOut( hDC, -xPos,16*(i-yPos) , NOTE[i], lstrlen( NOTE[i] ) );
         }

		GetTextExtentPoint(hDC,NOTE[Line],Word,&size);

		if(RT.bottom < 16 * F_Line)
		{

			if(en_flag == 1)
			{
				yScrol.nPage--;
				en_flag = 0;
				SetScrollPos(hwnd, SB_VERT, yPos, TRUE);
			}	
			else if (de_flag == 1)
			{
				yScrol.nPage++;
				de_flag = 0;
				SetScrollPos(hwnd, SB_VERT, yPos, TRUE);
			}
		}
		else if(0 > MaxLine){
			yScrol.nPage = 1;
			SetScrollPos(hwnd, SB_VERT, yPos, TRUE);
		}
		if(sc1_flag == 1)
		{
			SetScrollPos(hwnd, SB_VERT, yPos, TRUE);
		}

		if(RT.right <= MAX.cx){
			if(Line == MaxLine)
			{
				if(MaxWord > BF_MaxWord)
				{
				xScrol.nPage--;
				SetScrollPos(hwnd, SB_HORZ, xPos, TRUE);
				}
				else if(MaxWord >! BF_MaxWord)
				{
					if(xScrol.nPage != RT.right)
					{
						MaxWord = BF_MaxWord;
						if(de1_flag == 1)
						{
						xScrol.nPage++;
						de1_flag = 0;
						SetScrollPos(hwnd, SB_HORZ, xPos, TRUE);
						}
					}
					else
					{
						MaxWord = BF_MaxWord;
						xScrol.nPage = RT.right;
						SetScrollPos(hwnd, SB_HORZ, xPos, TRUE);
					}
				}
				if(sc_flag == 1)
				{
					SetScrollPos(hwnd, SB_HORZ, xPos, TRUE);
				}
			}
		}
		else if(1 > xScrol.nPage){
			xScrol.nPage = 1;
			SetScrollPos(hwnd, SB_HORZ, xPos, TRUE);
		}
         EndPaint( hwnd, &ps );
      }
