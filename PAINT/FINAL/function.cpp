#include "Function.h"

void NEW(HWND hwnd)
{
			MessageBox(hwnd, TEXT("새로 만들기"),TEXT("메시지 박스"),MB_YESNO);
			FillRect(MemDC, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));
			FillRect(saveMemDC, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));
			FillRect(hdc, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));
			im[0][0] = NULL;
			free_l[0][0] = NULL;
			free_xy[0][0][0] = NULL;
			box_check = 1;
			count = 0;
			InvalidateRect(hwnd, NULL, false);
}

void OPEN(HWND hwnd)
	{
			box_check = 1;
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hwnd;
			OFN.lpstrFilter = TEXT(" 비트맵 파일(.bmp)\0*.bmp\0 vi 파일(.vi)\0*.vi\0");
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = MAX_PATH;
			HANDLE f;
			DWORD dwRead;
			BYTE* Data;
			//vi
			HANDLE vi_f;
			TCHAR *str;
			INT strsize;
			strsize =0;
			//vi end
			int answer;

			if(GetOpenFileName(&OFN) != 0){
				if(OFN.nFilterIndex == 1){ //선택한 파일이 비트맵일 때
					answer = MessageBox(hwnd, TEXT("선택한 파일을 불러오겠습니까?"), TEXT("파일 열기"),MB_YESNO);
					if(answer == IDYES){
						f = CreateFile(OFN.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
						ReadFile(f, &HF, sizeof(BITMAPFILEHEADER), &dwRead, NULL); //14바이트
						ReadFile(f, &HF_info, sizeof(BITMAPINFOHEADER), &dwRead, NULL); //40바이트
						Old_x = 0;
						Old_y = HF_info.biHeight - 1; //왼쪽아래부터 그려지기때문이고 배열이니까 1뺴줌
					}


					if(HF_info.biBitCount == 8){
						RGBQUAD pRGB[256];
						ReadFile(f, pRGB, sizeof(RGBQUAD) * 256, &dwRead, NULL);

						Data = new BYTE[HF_info.biSizeImage];
						ReadFile(f, Data, HF_info.biSizeImage, &dwRead, NULL);
						BYTE R_data;

						int widthstep = 4 - (HF_info.biWidth % 4);
						if(widthstep == 4)
							widthstep = 0;
						for (int i=0 ; i < HF_info.biSizeImage ; i++){
							R_data = Data[i];
							SetPixel(MemDC, Old_x, Old_y, RGB(pRGB[R_data].rgbRed, pRGB[R_data].rgbGreen, pRGB[R_data].rgbBlue));
							SetPixel(saveMemDC, Old_x, Old_y, RGB(pRGB[R_data].rgbRed, pRGB[R_data].rgbGreen, pRGB[R_data].rgbBlue));
							Old_x++;

							if(Old_x == HF_info.biWidth){
								Old_x = 0;
								Old_y--;
								i += widthstep;
							}
						}
						InvalidateRect(hwnd, NULL, FALSE);
					}

					else if(HF_info.biBitCount == 24){
						int widthstep = 4 - (HF_info.biWidth % 4);
						if(widthstep == 4)
							widthstep = 0;

						int widthstep_count = 0;
						

						HF_info.biSizeImage = HF.bfSize - HF.bfOffBits;
						Data = new BYTE[HF_info.biSizeImage + 3];

						ReadFile(f, Data, HF_info.biSizeImage, &dwRead, NULL);

						for (int i = 0; i < HF_info.biWidth*HF_info.biHeight; i++)//전체 돌기
						{
							if (i != 0 && i % HF_info.biWidth == 0 )
							{
								Old_x = 0;
								Old_y--;
								widthstep_count++;
							}
							SetPixel(MemDC, Old_x, Old_y, RGB(Data[(i*3)+(widthstep_count*widthstep)+2], Data[(i*3)+(widthstep_count*widthstep)+1], Data[(i*3)+(widthstep_count*widthstep)]));//그리기
							SetPixel(saveMemDC, Old_x, Old_y, RGB(Data[(i*3)+(widthstep_count*widthstep)+2], Data[(i*3)+(widthstep_count*widthstep)+1], Data[(i*3)+(widthstep_count*widthstep)]));
							// i*3 은 1픽셀이 3바이트라서, count*widthstep 허수의 개수를 계산하기 위함, +2 +1은 bgr 순서라서
							//점을 찍어주는 함수 SetPixel(hdc, nXPos(좌표), nYPos(좌표), clrref(칼라)) 
							//색은 RGB순이 아니라 BGR순이다. 줄이 뛰어 넘을 떄 마다 00이 껴있어서 뛰어줘야한다.
							Old_x++;
						}
						InvalidateRect(hwnd, NULL, FALSE);
						CloseHandle(f);
					}
				}
				else if(OFN.nFilterIndex == 2){
					hdc = GetDC(hwnd);
					FillRect(saveMemDC, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH)); //도화지 색 변경
					FillRect(MemDC, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH)); //도화지 색 변경

					vi_f = CreateFile(lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
					str = (TCHAR*)malloc(22);
					ReadFile(vi_f, str, 22, &dwRead, NULL);
					str[dwRead/2] = NULL;
					
					count = 0;
					index= 0;
					if(str[index++] == 0xFEFF){			// 유니코드라면..
						count += (str[index++]-48)*10 ;
						count += (str[index++]-48);
						index++; // , 넘겨주기
						strsize += (str[index++] - 48)*100000;
						strsize += (str[index++] - 48)*10000;
						strsize += (str[index++] - 48)*1000;
						strsize += (str[index++] - 48)*100;
						strsize += (str[index++] - 48)*10;
						strsize += str[index++] - 48;
						index++; // \n 넘겨주기

						str = (TCHAR*)malloc(strsize*4);
						ReadFile(vi_f, str, strsize*4, &dwRead, NULL);
						index = 0;
		
						for(int i=0; i<count; i++){		// 그리는 갯수
							paint_mode = 0;
							x = 0;
							y = 0;
							Old_x = 0;
							Old_y = 0;
							pen_mode = 0;
							Font_Width = 0;
							B_Color_r = 0;
							B_Color_g = 0;
							B_Color_b = 0;
							In_Color_r = 0;
							In_Color_g = 0;
							In_Color_b = 0;
							if(str[index+3] != 48){		// 연필이 아니라면
								for(int j=0; j<13; j++){
									int count_1 = 1000;
									while(count_1!=0){
										
										switch(j){
										case 0: 
											paint_mode += (str[index++] - 48) * count_1;
											im[i][0] = paint_mode;
											break; 
										case 1:
											x += (str[index++] - 48) * count_1;
											im[i][1] = x;
											break;
										case 2:
											y += (str[index++] - 48) * count_1;
											im[i][2] = y;
											break;
										case 3:
											Old_x += (str[index++] - 48) * count_1;
											im[i][3] = Old_x;
											break;
										case 4:
											Old_y += (str[index++] - 48) * count_1;
											im[i][4] = Old_y;
											break;
										case 5:
											pen_mode += (str[index++] - 48) * count_1;
											im[i][5] =  pen_mode;
											break;
										case 6:
											Font_Width += (str[index++] - 48) * count_1;
											im[i][6] = Font_Width;
											break;
										case 7:
											B_Color_r += (str[index++] - 48) * count_1;
											im[i][7] = B_Color_r;
											break;
										case 8:
											B_Color_g += (str[index++] - 48) * count_1;
											im[i][8] = B_Color_g;
											break;
										case 9:
											B_Color_b += (str[index++] - 48) * count_1;
											im[i][9] = B_Color_b;
											break;
										case 10:
											In_Color_r += (str[index++] - 48) * count_1;
											im[i][10] = In_Color_r;
											break;
										case 11:
											In_Color_g += (str[index++] - 48) * count_1;
											im[i][11] = In_Color_g;
											break;
										case 12:
											In_Color_b += (str[index++] - 48) * count_1;
											im[i][12] = In_Color_b;
											break;
										}
										count_1 /= 10;
									}
									index++; // ,를 넘겨주기 위함.
								}
							}
							else{
								free_size = 0;
								paint_mode = 0;
								pen_mode = 0;
								Font_Width = 0;
								B_Color_r = 0;
								B_Color_g = 0;
								B_Color_b = 0;
								x = 0;
								y = 0;
	
								for(int k=0; k<7; k++){
									int count = 1000;
									while(str[index] != ','){
										switch(k){
										case 0:
											paint_mode += (str[index++] - 48) * count;
											free_l[i][0] = paint_mode;
											break;
										case 1:
											free_size += (str[index++] - 48) * count;
											free_l[i][1] = free_size;
											break;
										case 2:
											pen_mode += (str[index++] - 48) * count;
											free_l[i][2] = pen_mode;
											break;
										case 3:
											Font_Width += (str[index++] - 48) * count;
											free_l[i][3] = Font_Width;
											break;
										case 4:
											B_Color_r += (str[index++] - 48) * count;
											free_l[i][4] = B_Color_r;
											break;
										case 5:
											B_Color_g += (str[index++] - 48) * count;
											free_l[i][5] = B_Color_g;
											break;
										case 6:
											B_Color_b += (str[index++] - 48) * count;
											free_l[i][6] = B_Color_b;
											break;
										default:
											break;
										}
										count /= 10;
									}
									index++; // ,를 넘겨주기 위함.
								}
								index++; // \n 넘기기
								Pen = CreatePen( pen_mode, Font_Width, RGB(B_Color_r, B_Color_g, B_Color_b) );
								Old_Pen = (HPEN)SelectObject(MemDC, Pen);

								x = (str[index++] - 48)*1000;
								x += (str[index++] - 48)*100;
								x += (str[index++] - 48)*10;
								x += (str[index++] - 48);
								free_xy[i][0][0] = x;
								index++; // ',' 넘기기
								y = (str[index++] - 48)*1000;
								y += (str[index++] - 48)*100;
								y += (str[index++] - 48)*10;
								y += (str[index++] - 48);
								free_xy[i][0][1] = y;
								index++; // ',' 넘기기

								for(int n=1; n<free_size; n++){	// ox에서 n을 1번 사용함.
									Old_x = (str[index++] - 48)*1000;
									Old_x += (str[index++] - 48)*100;
									Old_x += (str[index++] - 48)*10;
									Old_x += (str[index++] - 48);
									free_xy[i][n][0] = Old_x;
									index++; // ',' 넘기기
									Old_y = (str[index++] - 48)*1000;
									Old_y += (str[index++] - 48)*100;
									Old_y += (str[index++] - 48)*10;
									Old_y += (str[index++] - 48);
									free_xy[i][n][1] = Old_y;
									index++; // ',' 넘기기
									MoveToEx(MemDC, x, y, NULL);
									LineTo(MemDC, Old_x, Old_y);
									x = Old_x;
									y = Old_y;
								}
							}
							
							if(paint_mode != 0){
								BitBlt(MemDC,0,0,rt.right, rt.bottom, saveMemDC,0,0,SRCCOPY);

								

								Pen = CreatePen(pen_mode, Font_Width, RGB(B_Color_r,B_Color_g,B_Color_b));
								Old_Pen = (HPEN)SelectObject(MemDC, Pen);

								

								if(B_Color_r == 255 && B_Color_b == 255 && B_Color_g == 255)
									Brush = (HBRUSH)GetStockObject(NULL_BRUSH);
								else
									Brush = CreateSolidBrush(RGB(In_Color_r, In_Color_g, In_Color_b));
									Old_Brush = (HBRUSH)SelectObject(MemDC, Brush);
								switch(paint_mode){

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
							}// if(select != 1)

							BitBlt(hdc, 0, 0, rt.right, rt.bottom, MemDC, 0, 0, SRCCOPY);
							BitBlt(saveMemDC,0,0,rt.right, rt.bottom, hdc,0,0,SRCCOPY);
							index++; // \n을 넘기기 위함
						}
					}
				}
			}
		}


void SAVE(HWND hwnd)
{
			box_check = 1;
			memset(&SFN, 0, sizeof(OPENFILENAME));
			SFN.lStructSize = sizeof(OPENFILENAME);
			SFN.hwndOwner = hwnd;
			SFN.lpstrFilter = TEXT(" 8비트 비트맵 파일(*.bmp)\0*.bmp\0 24비트비트맵(*.bmp)\0*.bmp\0 vi 파일(*.vi)\0*.vi");
			SFN.lpstrFile = lpstrFile;
			SFN.nMaxFile = MAX_PATH;
			HANDLE fp;
			HANDLE FP;
	
			DWORD dwRead;
		//vi
			HANDLE vi_fp;
			TCHAR *strRead;
			INT resize;
			resize = 0;
			index = 0;
			//vi end

			if(GetSaveFileName(&SFN) != 0) //다이얼로그 열기
			{
				
				if(SFN.nFilterIndex == 1) //8비트 비트맵
				{
					BITMAP bitmap;
					COLORREF color;
					RGBQUAD pal[256];
					int temp_pal[1024]={0, 0, 0, 0, 0, 0, 128, 0, 0, 128, 0, 0, 0, 128, 128, 0, 128, 0, 0, 0, 128, 0, 128, 0, 128, 128, 0, 0, 192, 192, 192, 0, 192, 220, 192, 0, 240, 202, 166, 0, 0, 32, 64, 0, 0, 32, 96, 0, 0, 32, 128, 0, 0, 32, 160, 0, 0, 32, 192, 0, 0, 32, 224, 0, 0, 64, 0, 0, 0, 64, 32, 0, 0, 64, 64, 0, 0, 64, 96, 0, 0, 64, 128, 0, 0, 64, 160, 0, 0, 64, 192, 0, 0, 64, 224, 0, 0, 96, 0, 0, 0, 96, 32, 0, 0, 96, 64, 0, 0, 96, 96, 0, 0, 96, 128, 0, 0, 96, 160, 0, 0, 96, 192, 0, 0, 96, 224, 0, 0, 128, 0, 0, 0, 128, 32, 0, 0, 128, 64, 0, 0, 128, 96, 0, 0, 128, 128, 0, 0, 128, 160, 0, 0, 128, 192, 0, 0, 128, 224, 0, 0, 160, 0, 0, 0, 160, 32, 0, 0, 160, 64, 0, 0, 160, 96, 0, 0, 160, 128, 0, 0, 160, 160, 0, 0, 160, 192, 0, 0, 160, 224, 0, 0, 192, 0, 0, 0, 192, 32, 0, 0, 192, 64, 0, 0, 192, 96, 0, 0, 192, 128, 0, 0, 192, 160, 0, 0, 192, 192, 0, 0, 192, 224, 0, 0, 224, 0, 0, 0, 224, 32, 0, 0, 224, 64, 0, 0, 224, 96, 0, 0, 224, 128, 0, 0, 224, 160, 0, 0, 224, 192, 0, 0, 224, 224, 0, 64, 0, 0, 0, 64, 0, 32, 0, 64, 0, 64, 0, 64, 0, 96, 0, 64, 0, 128, 0, 64, 0, 160, 0, 64, 0, 192, 0, 64, 0, 224, 0, 64, 32, 0, 0, 64, 32, 32, 0, 64, 32, 64, 0, 64, 32,96, 0, 64, 32, 128, 0, 64, 32, 160, 0, 64, 32, 192, 0, 64, 32, 224, 0, 64, 64, 0, 0, 64, 64, 32, 0, 64, 64, 64, 0, 64, 64, 96, 0, 64, 64, 128, 0, 64, 64, 160, 0, 64, 64, 192, 0, 64, 64, 224, 0, 64, 96, 0, 0, 64, 96, 32, 0, 64, 96, 64, 0, 64, 96, 96, 0, 64, 96, 128, 0, 64, 96, 160, 0, 64, 96, 192, 0, 64, 96, 224, 0, 64, 128, 0, 0, 64, 128, 32, 0, 64, 128, 64, 0, 64, 128, 96, 0, 64, 128, 128, 0, 64, 128, 160, 0, 64, 128, 192, 0, 64, 128, 224, 0, 64, 160, 0, 0, 64, 160, 32, 0, 64, 160, 64, 0, 64, 160, 96, 0, 64, 160, 128, 0, 64, 160, 160, 0, 64, 160, 192, 0, 64, 160, 224, 0, 64, 192, 0, 0, 64, 192, 32, 0, 64, 192, 64, 0, 64, 192, 96, 0, 64, 192, 128, 0, 64, 192, 160, 0, 64, 192, 192, 0, 64, 192, 224, 0, 64, 224, 0, 0, 64, 224, 32, 0, 64, 224, 64, 0, 64, 224, 96, 0, 64, 224, 128, 0, 64, 224, 160, 0, 64, 224, 192, 0, 64, 224, 224, 0, 128, 0, 0, 0, 128, 0, 32, 0, 128, 0, 64, 0, 128, 0, 96, 0, 128, 0, 128, 0, 128, 0, 160, 0, 128, 0, 192, 0, 128, 0, 224, 0, 128, 32, 0, 0, 128, 32, 32, 0, 128, 32, 64, 0, 128, 32, 96, 0, 128, 32, 128, 0, 128, 32, 160, 0, 128, 32, 192, 0, 128, 32, 224, 0, 128, 64, 0, 0, 128, 64, 32, 0, 128, 64, 64, 0, 128, 64, 96, 0, 128, 64, 128, 0, 128, 64, 160, 0, 128, 64, 192, 0, 128, 64, 224, 0, 128, 96, 0, 0, 128, 96, 32, 0, 128, 96, 64, 0, 128, 96, 96, 0, 128, 96, 128, 0, 128, 96, 160, 0, 128, 96, 192, 0, 128, 96, 224, 0, 128, 128, 0, 0, 128, 128, 32, 0, 128, 128, 64, 0, 128, 128, 96, 0, 128, 128, 128, 0, 128, 128, 160, 0, 128, 128, 192, 0, 128, 128, 224, 0, 128, 160, 0, 0, 128, 160, 32, 0, 128, 160, 64, 0, 128, 160, 96, 0, 128, 160, 128, 0, 128, 160, 160, 0, 128, 160, 192, 0, 128, 160, 224, 0, 128, 192, 0, 0, 128, 192, 32, 0, 128, 192, 64, 0, 128, 192, 96, 0, 128, 192, 128, 0, 128, 192, 160, 0, 128, 192, 192, 0, 128, 192, 224, 0, 128, 224, 0, 0, 128, 224, 32, 0, 128, 224, 64, 0, 128, 224, 96, 0, 128, 224, 128, 0, 128, 224, 160, 0, 128, 224, 192, 0, 128, 224, 224, 0, 192, 0, 0, 0, 192, 0, 32, 0, 192, 0, 64, 0, 192, 0, 96, 0, 192, 0, 128, 0, 192, 0, 160, 0, 192, 0, 192, 0, 192, 0, 224, 0, 192, 32, 0, 0, 192, 32, 32, 0, 192, 32, 64, 0, 192, 32, 96, 0, 192, 32, 128, 0, 192, 32, 160, 0, 192, 32, 192, 0, 192, 32, 224, 0, 192, 64, 0, 0, 192, 64, 32, 0, 192, 64, 64, 0, 192, 64, 96, 0, 192, 64, 128, 0, 192, 64, 160, 0, 192, 64, 192, 0, 192, 64, 224, 0, 192, 96, 0, 0, 192, 96, 32, 0, 192, 96, 64, 0, 192, 96, 96, 0, 192, 96, 128, 0, 192, 96, 160, 0, 192, 96, 192, 0, 192, 96, 224, 0, 192, 128, 0, 0, 192, 128, 32, 0, 192, 128, 64, 0, 192, 128, 96, 0, 192, 128, 128, 0,  192, 128, 160, 0, 192, 128, 192, 0, 192, 128, 224, 0, 192, 160, 0, 0, 192, 160, 32, 0, 192, 160, 64, 0, 192, 160, 96, 0, 192, 160, 128, 0, 192, 160, 160, 0, 192, 160, 192, 0, 192, 160, 224, 0, 192, 192, 0, 0, 192, 192, 32, 0, 192, 192, 64, 0, 192, 192, 96, 0, 192, 192, 128, 0, 192, 192, 160, 0, 240, 251, 255, 0, 164, 160, 160, 0, 128, 128, 128, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 255, 255, 0, 255, 0, 0, 0, 255, 0, 255, 0, 255, 255, 0, 0, 255, 255, 255, 0};
			
				/*	int temp_pal[64]={0, 0, 0, 0, 
										0,0,128,0,
										0,128,0,0,
										0,128,128,0,
										128,0,0,0,
										128,0,128,0,
										128,128,0,0,
										128,128,128,0,
										192,192,192,0,
										0,0,255,0,
										0,255,0,0,
										0,255,255,0,
										255,0,0,0,
										255,0,255,0,
										255,255,0,0,
										255,255,255,0};
					*/
					GetObject(saveBit, sizeof(BITMAP), &bitmap);//비트맵 핸들이 가진 비트맵 정보를 BITMAP구조체에 저장한다

					HF_info.biSize = sizeof(BITMAPINFOHEADER);
					HF_info.biWidth = bitmap.bmWidth;//비트맵 가로
					HF_info.biHeight = bitmap.bmHeight;//비트맵 세로
					HF_info.biPlanes = 1; //1로 고정
					HF_info.biBitCount = 8;
					HF_info.biCompression = BI_RGB;//압축되지 않은 비트맵 (BI_RGB)
					/*hinfo.biSizeImage = 0;*///비트맵이면 0
					HF_info.biXPelsPerMeter = 0;//미터당 가로픽셀수 -> 시스템은 사용안함
					HF_info.biYPelsPerMeter = 0;//미터당 세로픽셀수 -> 시스템은 사용안함
					HF_info.biClrUsed = 0;//0일 경우 비트맵은 사용 가능한 모든 색상을 다 사용한다. 
					HF_info.biClrImportant = 0;//0일 경우 비트맵은 사용 가능한 모든 색상을 다 사용되어야한다.
			
					int widthstep = 4 - (HF_info.biWidth % 4);
					if(widthstep == 4)
						widthstep = 0;
					HF.bfSize = (widthstep * HF_info.biHeight) + (HF_info.biWidth * HF_info.biHeight) + 1078;				// 비트맵 파일 전체의 크기
					HF.bfOffBits = 1078;																			// 픽셀 데이터의 시작 주소																		
					HF_info.biSizeImage = HF.bfSize - 1078;
					HF.bfType = 0x4d42;//파일의 형태를 지정하는 매직 넘버이며 반드기 BM(bmp 파일의 전체 크기)이어야 한다(0x42, 0x4d)
					HF.bfReserved1 = 0;
					HF.bfReserved2 = 0;
		
					fp = CreateFile(lpstrFile, GENERIC_WRITE, 0, NULL,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); // write = 쓰기전용, always는 파일이 존재할 경우 덮어쓰기, normal 속성지정x
		
					WriteFile(fp, &HF, sizeof(HF), &dwRead, NULL);//헤더
					WriteFile(fp, &HF_info, sizeof(HF_info), &dwRead, NULL);//헤더랑 내용	

					int z =0;
					for(int i = 0; i < 256 ; i++)
					{
						pal[i].rgbBlue = temp_pal[z];
						z++;
						pal[i].rgbGreen = temp_pal[z];
						z++;
						pal[i].rgbRed = temp_pal[z];
						z++;
						pal[i].rgbReserved = temp_pal[z];
						z++;
					}
					WriteFile(fp,(char*)&pal,sizeof(RGBQUAD)*256,&dwRead,NULL); // 팔레트 작성

					int b,g,r;
					int zero = 0;
					int x=0, y=0;
					for (y = rt.bottom-1; y >= 0; y--)
					{
						for (x = 0; x < rt.right; x++)
						{

							color = GetPixel(saveMemDC, x, y);
							b = color &  255;
							color = color >> 8;
							g = color & 255;
							color = color >> 8;
							r = color & 255;
							// 각 rgb값 찾았음
							for(int num = 0; num < 256; num++){ // 팔레트에 있는 색이면 삽입
								if(pal[num].rgbBlue == r && pal[num].rgbGreen == g && pal[num].rgbRed == b){
									WriteFile(fp,(char*)&num,1,&dwRead,NULL);
									break;
								}
							}
							for(int temp = 0; temp < widthstep/2; temp++){
									WriteFile(fp, (char*)zero, 1, &dwRead, NULL);
							}
						}// 한줄 다 작성
						x = 0;
					}	
					CloseHandle(fp);
				}
				
				else if(SFN.nFilterIndex == 2){ //24비트 비트맵
					BITMAP bit; //비트맵 구조체를 선언한다
			
					hdc = GetDC(NULL);
					int  r, g, b;

					GetObject(saveBit, sizeof(BITMAP), &bit);//비트맵 핸들이 가진 비트맵 정보를 BITMAP구조체에 저장한다

					HF_info.biSize = sizeof(BITMAPINFOHEADER);//구조체의 크기
					HF_info.biWidth = bit.bmWidth;//비트맵 가로
					HF_info.biHeight = bit.bmHeight;//비트맵 세로
					HF_info.biPlanes = 1; //1로 고정
					HF_info.biBitCount = 24;
					HF_info.biCompression = BI_RGB;//압축되지 않은 비트맵 (BI_RGB)
					/*hinfo.biSizeImage = 0;*///비트맵이면 0
					HF_info.biXPelsPerMeter = 0;//미터당 가로픽셀수 -> 시스템은 사용안함
					HF_info.biYPelsPerMeter = 0;//미터당 세로픽셀수 -> 시스템은 사용안함
					HF_info.biClrUsed = 0;//0일 경우 비트맵은 사용 가능한 모든 색상을 다 사용한다. 
					HF_info.biClrImportant = 0;//0일 경우 비트맵은 사용 가능한 모든 색상을 다 사용되어야한다.
					int widthstep = 4 - (HF_info.biWidth * 3 % 4);
					if (widthstep == 4) 
						widthstep = 0;
			
					HF.bfSize = (widthstep * HF_info.biHeight) + (HF_info.biWidth * HF_info.biHeight *3 ) + 54;		// 비트맵 파일 전체의 크기
					HF.bfOffBits = 54;																					// 픽셀 데이터의 시작 주소																	
					HF_info.biSizeImage = HF.bfSize - 54;

					HF.bfType = 0x4d42;
			
					HF.bfReserved1 = 0;
					HF.bfReserved2 = 0;
			
					FP = CreateFile(lpstrFile, GENERIC_WRITE, 0, NULL,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); // write = 쓰기전용, always는 파일이 존재할 경우 덮어쓰기, normal 속성지정x
				    WriteFile(FP, &HF, sizeof(HF), &dwRead, NULL);//헤더
					WriteFile(FP, &HF_info, sizeof(HF_info), &dwRead, NULL);//헤더랑 내용	
					COLORREF color;
					for (int y = rt.bottom-1; y >= 0; y--)
					{
						for (int k = 0; k < rt.right; k++)
						{
							color = GetPixel(saveMemDC, k, y);
							b = color & 255;
							color = color >> 8;
							g = color & 255;
							color = color >> 8;
							r = color & 255;
							WriteFile(FP,(char*)&r,1,&color,NULL);
							WriteFile(FP,(char*)&g,1,&color,NULL);
							WriteFile(FP,(char*)&b,1,&color,NULL);
						}
						for (int temp = widthstep; temp > 0; temp--)
							{
								int step = 0;
								WriteFile(fp,(char*)&step, 1, &color, NULL);
							}
					}
					CloseHandle(FP);
					BitBlt(saveMemDC, 0, 0, rt.right, rt.bottom, hdc, 0, 0, SRCCOPY);
					BitBlt(MemDC, 0, 0, rt.right, rt.bottom, saveMemDC, 0, 0, SRCCOPY);
					BitBlt(hdc, 0, 0, rt.right, rt.bottom, MemDC, 0, 0, SRCCOPY);
				}

				else if(SFN.nFilterIndex == 3){ //vi 저장
					int size = 0;
					vi_fp = CreateFile(lpstrFile, GENERIC_WRITE, 0, NULL,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
					for(int i=0; i<count; i++){
						if(free_l[i][0] != 0)
							size += 13*5+1;
						else
							size += (7*5) + (free_l[i][1] * 10) +2;
					}
					strRead = (TCHAR*)malloc(size+10);

					strRead[index++] = 0xFEFF; //유니코드(빅 에디안)
					strRead[index++] = (count/10)+48; //int->tchar
					strRead[index++] = (count%10)+48;
					strRead[index++] = ',';//여기까지 그린 개체 수
					strRead[index++] = (size/100000)%100000 + 48;
					strRead[index++] = (size/10000)%10000 + 48;
					strRead[index++] = (size/1000)%1000 + 48;
					strRead[index++] = (size/100)%100 + 48;
					strRead[index++] = (size/10)%10 + 48;
					strRead[index++] = size%10 + 48; //동적할당한 크기
					strRead[index++] = '\n';
					for(int a = 0; a < count ; a++)
					{
						if(im[a][0] != 0 && free_l[a][0] == 0){  //im[a][0] != 0 && free_l[a][0] == 0 
							for(int b = 0; b < 13 ; b++)
							{
								strRead[index++] = (im[a][b]/1000) +48; //페인트 모드, 좌표 4번,팬 모드, 폰트 크기, 선 색 3번, 안 색 3번
								strRead[index++] = (im[a][b]/100)%10 +48;
								strRead[index++] = (im[a][b]/10)%10 +48;
								strRead[index++] = (im[a][b]%10) +48;
								strRead[index++] = ',';
							}
						}
						else{
							for(int k=0; k<7; k++){									// 설정
								strRead[index++] = (free_l[a][k]/1000) + 48;
								strRead[index++] = (free_l[a][k]/100)%10 + 48;
								strRead[index++] = (free_l[a][k]/10)%10 + 48;
								strRead[index++] = (free_l[a][k]%10) + 48;
								strRead[index++] = ',';
							}
							strRead[index++] = '\n';

							for(int j=0; j<free_l[a][1]; j++){						// 좌표
								strRead[index++] = (free_xy[a][j][0]/1000) + 48;
								strRead[index++] = (free_xy[a][j][0]/100)%10 + 48;
								strRead[index++] = (free_xy[a][j][0]/10)%10 + 48;
								strRead[index++] = (free_xy[a][j][0]%10) + 48;
								strRead[index++] = ',';

								strRead[index++] = (free_xy[a][j][1]/1000) + 48;
								strRead[index++] = (free_xy[a][j][1]/100)%10 + 48;
								strRead[index++] = (free_xy[a][j][1]/10)%10 + 48;
								strRead[index++] = (free_xy[a][j][1]%10) + 48;
								strRead[index++] = ',';
							}
						}
						strRead[index++] = '\n';
					}					
					WriteFile(vi_fp, strRead, index*2, &dwRead, NULL);
					strRead[resize+10] = NULL;
					CloseHandle(vi_fp);

				}

				
			}
}
