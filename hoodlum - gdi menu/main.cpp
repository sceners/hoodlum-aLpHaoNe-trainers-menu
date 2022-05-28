/* GDI Windows Trainer for HLM
   (c) 2004 aLpHa oNe
   (Trainerengine removed!)
   =========================== */

#include "windows.h"
#include "math.h"
#include "logoundfont.cpp"


HWND destwindow;
bool menustatus=true;
bool status = true;
// void trainer();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{

	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	
	MSG			msg;
	HWND		hWnd;
	WNDCLASS	wc;

	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hbrBackground	= CreateSolidBrush(0x0);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance		= hInstance;
	wc.lpfnWndProc		= WndProc;
	wc.lpszClassName	= "Hoodlum";
	wc.lpszMenuName		= NULL;
	wc.style			= CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	hWnd = CreateWindow(	"Hoodlum",
							"Hoodlum",
							WS_POPUPWINDOW,
							(GetSystemMetrics(SM_CXSCREEN)/2)-250,
							(GetSystemMetrics(SM_CYSCREEN)/2)-200,
							500,
							400,
							NULL,
							NULL,
							hInstance,
							NULL);

//	FC_Initialize(true, modul, 0, 0);
//	FC_StartPlayer();

	Sleep(500);

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);
    
    while(msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
		else		
		{
			SendMessage(hWnd, WM_TIMER, 0, 0);
			Sleep(10);
		}
	}

	destwindow = FindWindow(NULL, "Obscure");
	if (!destwindow)
	{
//		FC_StopPlayer();
	}
	else
	{
//		FC_StopPlayer();
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static PAINTSTRUCT ps;
	static short starsx[300], starsy[300], starsz[300];

	static unsigned long coltab[]=
	{	0xff2200, 0xff4400, 0xff6600, 0xff8800, 0xffaa00, 0xffcc00, 0xffee00, 0xffff00, 
		0xeeff00, 0xccff00, 0xaaff00, 0x88ff00, 0x66ff00, 0x44ff00, 0x22ff00, 0x00ff00, 
		0x00ff22, 0x00ff44, 0x00ff66, 0x00ff88, 0x00ffaa, 0x00ffcc, 0x00ffee, 0x00ffff,
		0x00eeff, 0x00ccff, 0x00aaff, 0x0088ff, 0x0066ff, 0x0044ff, 0x0022ff, 0x0000ff, 	
		0x2200ff, 0x4400ff, 0x6600ff, 0x8800ff, 0xaa00ff, 0xcc00ff, 0xee00ff, 0xff00ff, 	
		0xff00ee, 0xff00cc, 0xff00aa, 0xff0088, 0xff0066, 0xff0044, 0xff0022, 0xff0000
	};
	
	static unsigned long vectorcoltab[256];
	
	static short vector[]=
	{
		 50,  50,  50,
		 50, -50,  50,
		 50, -50, -50,
		 50,  50, -50,

		-50,  50,  50,
		-50, -50,  50,
		-50, -50, -50,
		-50,  50, -50,
	};

	static short calcvector[8*3];

	static unsigned short faces[]=
	{
		0*3, 1*3, 2*3, 3*3,
		5*3, 4*3, 7*3, 6*3,
		0*3, 3*3, 7*3, 4*3,
		2*3, 1*3, 5*3, 6*3,
		0*3, 4*3, 5*3, 1*3,
		7*3, 3*3, 2*3, 6*3,
	};

	// Max 12 (!) lines
	static unsigned char statictext[]=
	{

		"             h o o d l u m\n"
		"            strikes back with:\n"
		"\n"
		"          obscure (c) microids +6\n"
		"\n"
		"      f1: toggle unl. ammo\n"
		"      f2: toggle unl. health\n"
		"      f3: toggle unl. flashlight time\n"
		"      f4: toggle unl. save times\n"
		"      f5: toggle unl. energy drinks\n"
		"      f6: toggle one hit kills\n"
	};

	// * = Pagefinish
	// # = Textfinish
	static unsigned char text[]=
	{
		"    another game / another cry\n"
		"            this time:*"

		"              obscure\n"
		"           (c) microids*"

		"    trained by the mighty duo\n"
		"       siriax and alpha one.*"

		"             hoodlum\n"
		"        definite supremacy!*"

		"     alpha one sends a long\n"
		"    handshake to sheep/ages. :)*"

		"#"
	};
	
	static unsigned char chartab[]="abcdefghijklmnopqrstuvwxyz!\"/:.1234567890+()O ";

	static unsigned short charpos[]=
	{	
		0, 1,  10, 12,
		0, 17, 10, 12,
		0, 29, 10, 12,
		0, 43, 10, 12,
		0, 57, 10, 12,
		0, 70, 9, 12,
		0, 82, 11, 12,
		0, 95, 9, 12,
		0, 108, 5, 12,
		0, 122, 7, 16,
		0, 140, 12, 12,
		0, 154, 8, 13,
		0, 169, 16, 12,
		0, 184, 10, 12,
		0, 197, 11, 12,
		0, 210, 9, 13,
		0, 226, 12, 13,
		0, 240, 9, 13,
		0, 254, 9, 13,
		0, 269, 10, 13,
		0, 285, 10, 13,
		0, 298, 10, 13,
		0, 312, 16, 13,
		0, 325, 10, 13,
		0, 340, 10, 13,
		0, 353, 10, 13,
		15, 1,  8, 15,
		15, 18, 12, 6,
		15, 30, 9, 14,
		15, 44, 12, 14,
		15, 59, 10, 12,
		20, 78, 10, 13,
		20, 99, 10, 13,
		21, 120, 10, 12,
		21, 141	, 10, 12,
		21, 161, 10, 12,
		21, 182, 10, 12,
		21, 202, 10, 13,
		21, 223, 10, 13,
		21, 244, 10, 12,
		21, 266, 10, 12,
		21, 286, 10, 12,
		21, 307, 8, 13,
		19, 327, 8, 13,
		16, 354, 12, 13,
		36, 354, 12, 13
	};

	static POINT vectortable[4];
	static float sinus=0, sin1=0, sin2=0, sin3=0;
	static float tempx, tempy, tempz, tempx2, tempy2, tempz2;
	static unsigned long color = 0;
	static int i, j, k, l, x, y, z, colorbar=0, delay=1, zoom=256, keydelay=15;
	static int x1, x2, x3, y1, y2, y3, z1, z2, z3;
	static int textx=0, texty=450, textptr=0, typerdelay=200;
	static bool typerpause = false, cursorstatus = true;
	static float vectorx=250, vectory=200;
	static DWORD byteswritten;
	static HANDLE file, bitmaplogo;
	static HBRUSH brush;
	static HPEN pen;
	static HDC hdc, hdcpaint, hdcgrafik;
	static HBITMAP bitmap;

	switch (message)
	{

		case WM_CREATE:
			hdc = GetDC(hWnd);
			bitmap = CreateCompatibleBitmap(hdc, 500, 800);
			hdcpaint = CreateCompatibleDC(hdc);
			SelectObject(hdcpaint, bitmap);
			PatBlt(hdcpaint, 0, 0, 500, 800, 0);
			file = CreateFile("gfx.tmp", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_HIDDEN, NULL);
			WriteFile(file, logo, sizeof(logo), &byteswritten, NULL);
			CloseHandle(file);			
			hdcgrafik = CreateCompatibleDC(hdc);
			bitmaplogo = LoadImage(NULL, "gfx.tmp", IMAGE_BITMAP, 151, 370, LR_LOADFROMFILE);
			SelectObject(hdcgrafik, bitmaplogo);
			DeleteFile("gfx.tmp");
			ReleaseDC(hWnd, hdc);

			for (i=0; i<300; i++)
			{
				starsx[i] = rand()%500-250;
				starsy[i] = rand()%500-250;
				starsz[i] = rand()%900;
			}
			
			for (i=0, color=0x003311ff; i<256; i++)
			{
				vectorcoltab[i] = color; 
				color-=0x00000001;
			}	

			for (i=0, k=0, l=500; i<sizeof(statictext); i++)
			{
				if (statictext[i]=='\n') { k=0; l+=16; continue;}
				for (j=0; j<sizeof(chartab); j++) if (statictext[i]==chartab[j]) break;
				j*=4;
				BitBlt(hdcpaint, k, l, charpos[j+2], charpos[j+3], hdcgrafik, charpos[j], charpos[j+1], SRCCOPY);
				k+=charpos[j+2]+1;
			}

			break;


		case WM_ACTIVATE:
			if (LOWORD(wParam)==WA_INACTIVE) { menustatus=true; ShowWindow(hWnd, SW_MINIMIZE); }
			if (LOWORD(wParam)==WA_ACTIVE) { menustatus=false; }
			return 0;

		case WM_TIMER:
			if (keydelay==0) 
			{ 
				keydelay=15; 
				destwindow = FindWindow(NULL, "Obscure");
				if (!destwindow) 
				{ 
					if (status==false)	
					{ 
						status=true;
//						FCp_Start();
					}
				}
				else
				{
					if (status==true)	
					{ 
//						FCp_Stop();
						status=false;						
					}
//				trainer(); 
				}
			}
			else
			{
				keydelay--;
			}
			
			if (menustatus) break;
			
			hdc = GetDC(hWnd);

			// 3D-Stars
			// ========
			
			for (i=0; i<300; i++)
			{	
				z = starsz[i] + 200;
				if (z < 300+200) color = 0xffffff;
				if (z > 600+200) color = 0x666666;
				if (z > 300+200 && z < 600+200) color = 0xbbbbbb;
				x = ( (starsx[i]*350) / z ) +250;	
				y = ( (starsy[i]*350) / z ) +200;	
				if (y<380)	SetPixel(hdcpaint, x, y, color);
				if (starsz[i]>=0) starsz[i]-=3; else starsz[i]=900;
			}

			// Put HLM Logo on Screen
			// ======================

			BitBlt(hdcpaint, 390, 300, 100, 70, hdcgrafik, 37, 0, SRCCOPY);

			// Vectorcube
			// ==========

			for (i=0, x=0; i<8; i++, x+=3) // Calc Points
			{
				tempx = float(vector[x]*cos(sin1) - vector[x+1]*sin(sin1));
				tempy = float(vector[x]*sin(sin1) + vector[x+1]*cos(sin1)); 

				tempy2= float(vector[x+2]*sin(sin2) - tempy*cos(sin2));
				tempz = float(tempy*sin(sin2) + vector[x+2]*cos(sin2));
				
				tempz2 = float(tempz*cos(sin3) - tempx*sin(sin3));
				tempx2 = float(tempz*sin(sin3) + tempx*cos(sin3));
							
		        calcvector[x] = int ( (tempx2*zoom) / (tempz2+220) ) + int(vectorx);
				calcvector[x+1] = int ( (tempy2*zoom) / (tempz2+220) ) + int(vectory);
				calcvector[x+2] = int ( tempz2 ); 
			}

			for (i=0, x=0; i<6; i++, x+=4)
			{
				x1 = calcvector[ faces[x+0]+0 ]; y1 = calcvector[ faces[x+0]+1 ]; z1 = calcvector[ faces[x+0]+2 ]+70;
				x2 = calcvector[ faces[x+1]+0 ]; y2 = calcvector[ faces[x+1]+1 ]; z2 = calcvector[ faces[x+1]+2 ]+70;
				x3 = calcvector[ faces[x+2]+0 ]; y3 = calcvector[ faces[x+2]+1 ]; z3 = calcvector[ faces[x+2]+2 ]+70;
					
		        if ( (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1) < 0) continue;
						
				vectortable[0].x = x1; vectortable[0].y = y1;
				vectortable[1].x = x2; vectortable[1].y = y2;
				vectortable[2].x = x3; vectortable[2].y = y3;
				vectortable[3].x = calcvector[ faces[x+3]+0 ];
				vectortable[3].y = calcvector[ faces[x+3]+1 ];

				color = vectorcoltab[ ( z1+z2+z3+calcvector[ faces[x+3]+2 ] ) / 4  + (220-zoom/2)];

				brush = CreateSolidBrush(color);
				pen = CreatePen(PS_NULL, 1, color);
				SelectObject(hdcpaint, brush);
				SelectObject(hdcpaint, pen);
		
				Polygon(hdcpaint, vectortable, 4);

				DeleteObject(pen);
				DeleteObject(brush);
			}

			vectorx = float( 250 + 200*sin(sin2+45) );
			vectory = float( 200 + 130*cos(sin3) );
			zoom = int (215 + 160*sin(sin3));
			sin1+=.030f; sin2+=.011f; sin3+=.014f;
			
			// Put Alpha & Siriax on Screen
			// ============================

			BitBlt(hdcpaint, 5, 23, 51, 12, hdcgrafik, 36, 95, SRCCOPY);
			BitBlt(hdcpaint, 440, 23, 51, 12, hdcgrafik, 96, 95, SRCCOPY);

			// Put Typer on Screen
			// ===================
		
			BitBlt(hdcpaint, 0, 320, 370, 30, hdcpaint, 0, 450, SRCPAINT);

			// Oldskool-Colorbars
			// ==================

			for (i=0, z=499, y=colorbar; i<500; i+=10, z-=10)
			{
				for (x=0; x<10; x++) 
				{
					SetPixel(hdcpaint, i+x, 20, coltab[y]);
					SetPixel(hdcpaint, z-x, 380, coltab[y]);
				}
				if (y==sizeof(coltab)/4-1) y=0; else y++;
			}
			if (delay==0)
			{
				delay=2;
				if (colorbar==sizeof(coltab)/4-1) colorbar=0; else colorbar++;
			
				// Print Text
				// ==========

				if (typerpause==false)
				{
					if (cursorstatus==true)
					{
						BitBlt(hdcpaint, textx, texty, 12, 13, hdcgrafik, 16, 354, SRCCOPY);
						cursorstatus=false;
					}
					else
					{
						cursorstatus=true;
						PatBlt(hdcpaint, textx, texty, 12, 13, 0); // Cursor wech!
						if (text[textptr]=='*') { typerpause=true; typerdelay=200; break; }
						if (text[textptr]=='\n') { textx=0; texty+=16; textptr++; }
						while (text[textptr]==' ') { textx+=12; textptr++; }
						for (j=0; j<sizeof(chartab); j++) if (text[textptr]==chartab[j]) break;
						j*=4;
						BitBlt(hdcpaint, textx, texty, charpos[j+2], charpos[j+3], hdcgrafik, charpos[j], charpos[j+1], SRCCOPY);
						textx+=charpos[j+2]+1;
						textptr++;
					}
				}
				else
				{
					if (typerdelay==0) 
					{ 
						typerpause=false; 
						textptr++; 
						textx=0; 
						texty=450; 
						PatBlt(hdcpaint, 0, 450, 370, 30, 0);
						if (text[textptr]=='#') textptr=0;

					}
					typerdelay--;
				}
			}
			else
			{
				delay--;
			}

			// Blit the whole stuff to screen
			// ==============================
		
			BitBlt(hdcpaint, 0, 70, 500, 190, hdcpaint, 0, 500, SRCPAINT);
			BitBlt(hdc, 0, 20, 500, 361, hdcpaint, 0, 20, SRCCOPY);
			PatBlt(hdcpaint, 0, 0, 500, 400, 0);

			ReleaseDC(hWnd, hdc);
			return 0;
		
		case WM_LBUTTONDOWN:
			SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, TRUE);
			break;

		
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
				SendMessage(hWnd, WM_CLOSE, 0, 0);
				break;
			}
			break;

		case WM_DESTROY:
			DeleteDC(hdcgrafik);
			DeleteObject(bitmaplogo);
			DeleteDC(hdcpaint);
			DeleteObject(bitmap);
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}