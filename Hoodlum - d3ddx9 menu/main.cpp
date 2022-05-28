// --------------------------------------------------------------------------------
// DX TRAINERMENU FOR HLM
// (C) aLpha oNe 2005
// - Music and Trainerengine removed!
// --------------------------------------------------------------------------------

#include "windows.h"
#include "d3d9.h"
#include "math.h"

// --------------------------------------------------------------------------------
// EXTERNAL STUFF (MUSIC, GFX, FONTS...)
// --------------------------------------------------------------------------------

#include "logoundfont.h"

// --------------------------------------------------------------------------------
// *** TARGET WINDOW FOR GAMEHACKING ;-) ***
// --------------------------------------------------------------------------------

const char* Target_Window = "Pariah";

// --------------------------------------------------------------------------------
// DIRECTX & OTHER FUNCTIONS
// --------------------------------------------------------------------------------
void Raw2Buffer (BYTE* rawptr, ULONG* coltab, int width, int height, ULONG* buffer, int pitch, int sx, int sy);
bool InitDirectX (HWND hWnd);
void QuitDirectX (void);
void Intro();
void Trainer();

// --------------------------------------------------------------------------------
// GLOBALS
// --------------------------------------------------------------------------------

#define customvertex (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define color1 0xf0cccccc
#define color2 0x5044ee22
#define	zoom 140

unsigned char chartab[]="abcdefghijklmnopqrstuvwxyz()!0123456789:-./+ ";


float zoomings[]={40, 60, 80, 100, 120, 140, 240};


const char* scrolltext=
{
	"                                      " // leave these " " spaces ...!

	"hoodlum is back once again with another pretty cool trainer for your gaming enterainment! "
	"    so.......        - pariah (c) digital extreme +5 -              we are out of time so see you all lateron"
	" in one of the next releases.....      credits for this nice menu.....    coding by alpha one.     graphics by h2o. "
	"    music by pink.         thats all...    l8r folks !        "
	"                                      " // leave these " " spaces ...!
	"\0"
};

unsigned char text[]=
{
	"     p a r i a h \n"
	" (c) digital extreme\n"
	"\n"
	"f1 toggle health\n"
	"f2 toggle grenades\n"
	"f3 toggle 1 hit kills\n"
	"f4 toggle ammo\n"
	"f5 toggle health pax\n"
};

struct vertexstruct		{ float x, y, z, rhw; unsigned long color; };

vertexstruct copper[]=
{
						{ 000.0f, 000.0f, 1.0f, 1.0f, 0x00000000 },
                    	{ 060.0f, 000.0f, 1.0f, 1.0f, 0x00ffffff },
                    	{ 060.0f, 400.0f, 1.0f, 1.0f, 0x00ffffff },
                    	{ 000.0f, 400.0f, 1.0f, 1.0f, 0x00000000 },

						{ 440.0f, 000.0f, 1.0f, 1.0f, 0x00ffffff },
                    	{ 500.0f, 000.0f, 1.0f, 1.0f, 0x00000000 },
                    	{ 500.0f, 400.0f, 1.0f, 1.0f, 0x00000000 },
                    	{ 440.0f, 400.0f, 1.0f, 1.0f, 0x00ffffff },

						{ 000.0f, 000.0f, 1.0f, 1.0f, 0x40ffffff },
                    	{ 500.0f, 000.0f, 1.0f, 1.0f, 0x40ffffff },
                    	{ 500.0f, 400.0f, 1.0f, 1.0f, 0x40aa22aa },
                    	{ 000.0f, 400.0f, 1.0f, 1.0f, 0x40ffffff },
};

float starcoords[]=
{
	 2.500000f,  0.000000f,
	 1.011271f,  0.734732f,
	 0.772542f,  2.377641f,
	-0.386271f,  1.188821f,
	-2.022542f,  1.469463f,
	-1.250000f,  0.000000f,
	-2.022542f, -1.469463f,
	-0.386271f, -1.188821f,
	 0.772542f, -2.377641f,
  	 1.011271f, -0.734732f
};

unsigned short starpolys[]=
{
	9,8,7, 7,6,5, 9,1,0, 5,4,3, 3,2,1, 9,3,1, 9,5,3, 9,7,5
};

struct index            { unsigned long p1, p2, p3, color; };
float cpoints[14*3];
float points[]=
{
     // front side
    -200.0f,  200.0f,  200.0f,
     200.0f,  200.0f,  200.0f,
     200.0f, -200.0f,  200.0f,
    -200.0f, -200.0f,  200.0f,

     // back side
    -200.0f,  200.0f, -200.0f,
     200.0f,  200.0f, -200.0f,
     200.0f, -200.0f, -200.0f,
    -200.0f, -200.0f, -200.0f,

     // middle points
     000.0f,  000.0f,  315.0f,
     000.0f,  000.0f, -315.0f,
     000.0f,  315.0f,  000.0f,
     000.0f, -315.0f,  000.0f,
     315.0f,  000.0f,  000.0f,
    -315.0f,  000.0f,  000.0f

};

index indices[]=
{
    // bottom
    {  2*03,  6*03, 11*03, color1 },
    {  2*03, 11*03,  3*03, color2 },
    { 11*03,  7*03,  3*03, color1 },
    {  6*03,  7*03, 11*03, color2 },

    // top
    {  0*03,  4*03, 10*03, color1 },
    {  0*03, 10*03,  1*03, color2 },
    { 10*03,  5*03,  1*03, color1 },
    {  4*03,  5*03, 10*03, color2 },

    // front
    { 0*03,   1*03,  8*03, color1 },
    { 1*03,   2*03,  8*03, color2 },
    { 8*03,   2*03,  3*03, color1 },
    { 0*03,   8*03,  3*03, color2 },

    // back
    { 5*03,   4*03,  9*03, color1 },
    { 5*03,   9*03,  6*03, color2 },
    { 9*03,   7*03,  6*03, color1 },
    { 4*03,   7*03,  9*03, color2 },

    // left
    { 4*03,   0*03, 13*03, color2 },
    { 4*03,  13*03,  7*03, color1 },
    { 3*03,   7*03, 13*03, color2 },
    { 3*03,  13*03,  0*03, color1 },

    // right
    { 1*03,   5*03, 12*03, color2 },
    { 5*03,   6*03, 12*03, color1 },
    {12*03,   6*03,  2*03, color2 },
    { 1*03,  12*03,  2*03, color1 },
};

LPDIRECT3D9				lpD3D = 0;
LPDIRECT3DDEVICE9		lpD3DDevice = 0;
LPDIRECT3DSURFACE9		lpD3DBackbuffer = 0, lpD3DOffscreen = 0;
LPDIRECT3DVERTEXBUFFER9	lpD3DVertexbuffer = 0;
LPDIRECT3DINDEXBUFFER9	lpD3DIndexbuffer = 0;
D3DLOCKED_RECT			LockedRect;
D3DPRESENT_PARAMETERS	PParams;
HWND					destwindow;
bool					gamestarted = false;
bool					active = true;
vertexstruct*			Vertexbufferpointer;
void*					Indexbufferpointer;
RECT					rect1 = { 0, 0, 470, 175 };
RECT					rect2 = { 10, 0, 480, 175 };
RECT					srcrect = { 0, 180, 16, 196 };
RECT					destrect = { 0, 200, 16, 216 };
ULONG*		        	memoryptr;
UINT        			memorypitch;
UINT                    i, j, k, l, scrollpos=16, scrollptr=0, scrollsize=0, keydelay=20;
float					starsine1=0, starsine2=0;
float                   sin1=0, sin2=0, sin3=0, sinus1=0, sinus2=0;
float                   tempx, tempy, tempz, tempx2, tempy2, tempz2;

// --------------------------------------------------------------------------------
// CREATING THE TARGET WINDOW FOR DX
// --------------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	MSG			msg;
	HWND		hWnd;
	WNDCLASS	wc;

	wc.hInstance		= hInstance;
	wc.lpszClassName	= "Hoodlum";
	wc.lpfnWndProc		= WndProc;
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.lpszMenuName		= NULL;
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;

	scrollsize			= strlen(scrolltext)-36;

	RegisterClass(&wc);

	hWnd = CreateWindow(	"Hoodlum",
							"Definite Supremacy!",
							WS_POPUPWINDOW,
							(GetSystemMetrics(SM_CXSCREEN)/2)-250,
							(GetSystemMetrics(SM_CYSCREEN)/2)-200,
							500,
							400,
							NULL,
							NULL,
							hInstance,
							NULL);

  	// Choose Fullscreen or windowed Mode
    ZeroMemory(&PParams, sizeof(PParams));

	if (!InitDirectX(hWnd))
	{
		MessageBox(0, "What the...?!", "Couldnմ set up DirectX.", 0);
		return msg.wParam;;
	}

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
			if (gamestarted==false)
			{
				if (active)
				{
					Intro();
				}
				else
				{
					Sleep(1);
				}
			}
			else
			{
				Sleep(20);
			}
    	}
	}

	QuitDirectX();
	return msg.wParam;
}

// --------------------------------------------------------------------------------
// THE WINDOW PROCEDURE
// --------------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_ACTIVATE:
			if (LOWORD(wParam)==WA_INACTIVE) { active=false; ShowWindow(hWnd, SW_MINIMIZE); }
			if (LOWORD(wParam)==WA_ACTIVE) { active=true; }
			if (LOWORD(wParam)==WA_CLICKACTIVE) { active=true; }
			return 0;

		case WM_CREATE:
			SetTimer(hWnd, 1, 100, (TIMERPROC) NULL);
			break;

		case WM_TIMER:
			destwindow = FindWindow(NULL, Target_Window);
			if (gamestarted==false)
			{
				if (destwindow)
				{
					gamestarted = true;
					ShowWindow(hWnd, SW_HIDE);
				}
			}
			else
			{
				if (!destwindow)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
					gamestarted = false;
				}
				else
				{
					// Trainer();
				}
			}
			break;

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
			KillTimer(hWnd, 1);
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

// --------------------------------------------------------------------------------
// INIT DIRECTX
// --------------------------------------------------------------------------------

bool InitDirectX(HWND hWnd)
{
    // Create the Direct3D Object
   lpD3D = Direct3DCreate9(D3D_SDK_VERSION);
   	if (lpD3D == 0) return false;

    // Creating the Direct3D-Device, setting up Displayparameters
   	PParams.SwapEffect				= D3DSWAPEFFECT_DISCARD;
    PParams.hDeviceWindow			= hWnd;
   	PParams.Flags					= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
   	PParams.BackBufferWidth			= 500;
   	PParams.BackBufferHeight		= 400;
   	PParams.BackBufferFormat		= D3DFMT_X8R8G8B8;
   	PParams.EnableAutoDepthStencil	= false;
    PParams.Windowed = true;
   	PParams.PresentationInterval	= D3DPRESENT_INTERVAL_ONE;

    if(FAILED(lpD3D->CreateDevice(  D3DADAPTER_DEFAULT,
                                    D3DDEVTYPE_HAL,
                                    hWnd,
                                    D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                    &PParams,
                                    &lpD3DDevice))) return false;

	// Getting Pointer to Backbuffer Surface
	lpD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &lpD3DBackbuffer);
	if (lpD3DBackbuffer==0) return false;

	// Create Offscreen Surface
	lpD3DDevice->CreateOffscreenPlainSurface(   500,
                                                220,
                                                D3DFMT_X8R8G8B8,
                                                D3DPOOL_DEFAULT,
                                                &lpD3DOffscreen,
                                                NULL);
	if (lpD3DOffscreen==0) return false;

	// Copy Logo and Font to Offscreen
	lpD3DOffscreen->LockRect(&LockedRect, 0, 0);
	memoryptr = (unsigned long*)LockedRect.pBits;
	memorypitch = LockedRect.Pitch/4;
	Raw2Buffer(    gfx_logo,
	               (ULONG*)colortable_logo,
	               500,
	               220,
	               memoryptr,
	               memorypitch,
                   0,
                   0 );
	lpD3DOffscreen->UnlockRect();

	// Create the Vertexbuffer
	lpD3DDevice->CreateVertexBuffer(    24*(3*sizeof(vertexstruct)),
                                        D3DUSAGE_WRITEONLY,
                                        customvertex,
                                        D3DPOOL_DEFAULT,
                                        &lpD3DVertexbuffer,
                                        NULL);
	if (lpD3DVertexbuffer==0) return false;

	// Create the Indexbuffer
	lpD3DDevice->CreateIndexBuffer(     8*6,
                                        NULL,
                                        D3DFMT_INDEX16,
                                        D3DPOOL_DEFAULT,
                                        &lpD3DIndexbuffer,
                                        NULL);
	if (lpD3DIndexbuffer==0) return false;
	lpD3DIndexbuffer->Lock(0, 0, (void**)&Indexbufferpointer, 0);
	memcpy(Indexbufferpointer, starpolys, 8*6);
	lpD3DIndexbuffer->Unlock();

	// Setting up Vertexformat & Rendermode
	lpD3DDevice->SetFVF(customvertex);
	lpD3DDevice->SetStreamSource(0, lpD3DVertexbuffer, 0, sizeof(vertexstruct));
	lpD3DDevice->SetIndices(lpD3DIndexbuffer);
	lpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	lpD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	return true;
}

// --------------------------------------------------------------------------------
// QUIT DIRECTX
// --------------------------------------------------------------------------------

void QuitDirectX()
{
    if (lpD3DOffscreen != 0)	lpD3DOffscreen->Release();
    if (lpD3DVertexbuffer != 0)	lpD3DVertexbuffer->Release();
    if (lpD3DIndexbuffer != 0)	lpD3DIndexbuffer->Release();
    if (lpD3DBackbuffer != 0)	lpD3DBackbuffer->Release();
    if (lpD3DDevice != 0)		lpD3DDevice->Release();
    if (lpD3D != 0)				lpD3D->Release();
}

// --------------------------------------------------------------------------------
// MAIN INTRO CODE
// --------------------------------------------------------------------------------

void Intro()
{
	// Clear Backbuffer
	lpD3DDevice->Clear(0, 0, D3DCLEAR_TARGET, 0x002f5051, 1.0f, 0);

	// Copy Logo
    lpD3DDevice->StretchRect(lpD3DOffscreen, &rect1, lpD3DBackbuffer, &rect2, D3DTEXF_NONE);

	// Type Text
	destrect.left	= 160;
	destrect.right	= 176;
	destrect.top	= 170;
	destrect.bottom	= 186;

	for (i=0; i<sizeof(text); i++)
	{
		if(text[i]=='\n')
		{
			destrect.left = 160;	destrect.right	= 176;
			destrect.top  += 16;	destrect.bottom	+= 16;
			continue;
		}

		for(j=0; text[i]!=chartab[j]; j++);
		if (j>30)
		{
			srcrect.top = 197;		srcrect.bottom	= 213;
			j-=31;
		}
		else
		{
			srcrect.top = 180;		srcrect.bottom	= 196;
		}

		srcrect.left = j*16;
		srcrect.right = j*16+16;
		lpD3DDevice->StretchRect(lpD3DOffscreen, &srcrect, lpD3DBackbuffer, &destrect, D3DTEXF_NONE);
		destrect.left +=15;
		destrect.right +=15;
	}

	// Scrolltext
	destrect.left	= scrollpos;
	destrect.right	= scrollpos+16;
    sinus1			= sinus2;

	for (i=scrollptr; i<scrollptr+33; i++)
	{
		for(j=0; scrolltext[i]!=chartab[j]; j++);
		if (j>30)
		{
			srcrect.top = 197;		srcrect.bottom	= 213;
			j-=31;
		}
		else
		{
			srcrect.top = 180;		srcrect.bottom	= 196;
		}
		srcrect.left = j*16;
		srcrect.right = j*16+16;
		destrect.top	= int(359+20*cos(sinus1));
		destrect.bottom	= destrect.top + 15;
		lpD3DDevice->StretchRect(lpD3DOffscreen, &srcrect, lpD3DBackbuffer, &destrect, D3DTEXF_NONE);
		destrect.left +=15;
		destrect.right +=15;
		sinus1+=.4f;
	}

	sinus2+=.1f;
	scrollpos--;
	if (scrollpos==1)
	{
		scrollpos=16; scrollptr++; sinus2+=.4f;
		if (scrollptr==scrollsize) scrollptr=0;
	}

	// Begin of rendering
	lpD3DDevice->BeginScene();

	// Draw Star
  	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	lpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
	starsine1 = starsine2;
	for (k=0; k<5; k++)
	{
		zoomings[k] = float( (k*10)+80+60*sin(starsine1) );

		lpD3DVertexbuffer->Lock(0, 0, (void**)&Vertexbufferpointer, 0);
		for (i=0, j=0; i<10; i++, j+=2)
		{
			Vertexbufferpointer[i].y     = ( (starcoords[j+1]*sin(starsine1) + starcoords[j+0]*cos(starsine1)) * zoomings[k]) + ( 250+50*sin(sin3));
			Vertexbufferpointer[i].x     = ( (starcoords[j+1]*cos(starsine1) - starcoords[j+0]*sin(starsine1)) * zoomings[k]) + ( 350+50*cos(sin2));;
			Vertexbufferpointer[i].z     = 1.0f;
			Vertexbufferpointer[i].color = 0x00778833;
			Vertexbufferpointer[i].rhw	 = 1.0f;
		}
		starsine1+=.5f;
		lpD3DVertexbuffer->Unlock();
		lpD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 10, 0, 5);
	}
	starsine2+=.04f;

    // Rotate Points
    for (i=0, j=0; i<14; i++, j+=3)
    {
		tempx         = float (points[j]*cos(sin1) - points[j+1]*sin(sin1) );
		tempy         = float (points[j]*sin(sin1) + points[j+1]*cos(sin1) );

		tempy2        = float (points[j+2]*sin(sin2) - tempy*cos(sin2) );
		tempz         = float (tempy*sin(sin2) + points[j+2]*cos(sin2) );

		tempz2        = float (tempz*cos(sin3) - tempx*sin(sin3) );
		tempx2        = float (tempz*sin(sin3) + tempx*cos(sin3) );

        cpoints[j+0]  = float ( (tempx2*200) / (tempz2+900) + 80 );
		cpoints[j+1]  = float ( (tempy2*200) / (tempz2+900) + 250 );
		cpoints[j+2]  = tempz2;
	}

    // Fill Indexbuffer
	lpD3DVertexbuffer->Lock(0, 0, (void**)&Vertexbufferpointer, 0);
    for (i=0, j=0; i<24; i++, j+=3)
    {
           Vertexbufferpointer[j+0].x     = cpoints[ indices[i].p1 + 0 ];
           Vertexbufferpointer[j+0].y     = cpoints[ indices[i].p1 + 1 ];
           Vertexbufferpointer[j+0].z     = cpoints[ indices[i].p1 + 2 ];
           Vertexbufferpointer[j+0].rhw   = 1.0f;

           Vertexbufferpointer[j+1].x     = cpoints[ indices[i].p2 + 0 ];
           Vertexbufferpointer[j+1].y     = cpoints[ indices[i].p2 + 1 ];
           Vertexbufferpointer[j+1].z     = cpoints[ indices[i].p2 + 2 ];
           Vertexbufferpointer[j+1].rhw   = 1.0f;

           Vertexbufferpointer[j+2].x     = cpoints[ indices[i].p3 + 0 ];
           Vertexbufferpointer[j+2].y     = cpoints[ indices[i].p3 + 1 ];
           Vertexbufferpointer[j+2].z     = cpoints[ indices[i].p3 + 2 ];
           Vertexbufferpointer[j+2].rhw   = 1.0f;

           Vertexbufferpointer[j+0].color = indices[i].color;
           Vertexbufferpointer[j+1].color = indices[i].color;
           Vertexbufferpointer[j+2].color = indices[i].color;
           Vertexbufferpointer[j+2].rhw   = 1.0f;
    }
    lpD3DVertexbuffer->Unlock();

	// Draw Glenz Vector
    lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
    lpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
  	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    for (i=0; i<6; i++) lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, i*12, 4);
  	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	for (i=0; i<6; i++) lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, i*12, 4);

	// Draw Copper ;)
    lpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
  	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	lpD3DVertexbuffer->Lock(0, 0, (void**)&Vertexbufferpointer, 0);
	memcpy(Vertexbufferpointer, copper, sizeof(copper));
	lpD3DVertexbuffer->Unlock();
    lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 8, 2);
    lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);
    lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 4, 2);

	// End of Rendering
	lpD3DDevice->EndScene();

	// Movement
    sin1 += .045f;
	sin2 += .02f;
	sin3 += .015f;

	// Swap Front- & Backbuffer
	lpD3DDevice->Present(0, 0, 0, 0);
}

// --------------------------------------------------------------------------------
// LOAD RAW BITMAPS TO SCREEN- OR TEXTUREBUFFER
// --------------------------------------------------------------------------------

void Raw2Buffer(BYTE* rawptr, ULONG* coltab, int width, int height, ULONG* buffer, int pitch, int sx, int sy)
{
    ULONG xrgb;
    coltab+=6; // .pal - Header not needed!

    for (int a = sy * pitch; a < (sy + height) * pitch; a+=pitch)
    {
        for (int b = sx; b < sx + width; b++)
        {
            xrgb        = coltab[*rawptr++]<<8;
            buffer[a+b] = ((xrgb&0xFF000000)>>24)|((xrgb&0xFF0000)>>8)|((xrgb&0xFF00)<<8)|((xrgb&0xFF)<<24);
        }
    }

}
