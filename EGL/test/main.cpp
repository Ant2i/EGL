#include <EGL/egl.h>
#include <GL/gl.h>

#ifdef WIN32
#include <windows.h>
typedef HWND NativeWindowType;

NativeWindowType createNativeWindow(void)
{

	WNDCLASS	wc;						
	DWORD		dwExStyle;				
	DWORD		dwStyle;				


	auto hInstance			= GetModuleHandle(NULL);				
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	
	wc.lpfnWndProc		= (WNDPROC)DefWindowProc;
	wc.cbClsExtra		= 0;									
	wc.cbWndExtra		= 0;									
	wc.hInstance		= hInstance;							
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			
	wc.hbrBackground	= NULL;									
	wc.lpszMenuName		= NULL;									
	wc.lpszClassName	= "OpenGL";								

	if (RegisterClass(&wc))									
	{
	
	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			
	dwStyle=WS_OVERLAPPEDWINDOW;							

	

	// Create The Window
	HWND hWnd=CreateWindowEx(	dwExStyle,							
								"OpenGL",							
								"",								
								dwStyle |		WS_CLIPSIBLINGS |				WS_CLIPCHILDREN,				
								0, 0,								
								300,	
								300,	
								NULL,								
								NULL,								
								hInstance,							
								NULL);							

							if (hWnd)
					ShowWindow(hWnd,SW_SHOW);						
	return hWnd;		
	}

	return 0;
}

void _sleep(int ms)
{
	Sleep(ms);
}

#endif

static EGLint const config_attribute[] = 
{
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_NONE
};

static EGLint const context_attribute[] =
{
	EGL_CONTEXT_MAJOR_VERSION, 4,
	EGL_CONTEXT_MINOR_VERSION, 2,
	EGL_NONE
};

int main(int argc, char ** argv)
{
        EGLDisplay display;
        EGLConfig config;
        EGLContext context;
        EGLSurface surface;
        NativeWindowType native_window;
        EGLint num_config;

		eglBindAPI(EGL_OPENGL_API);
		/* get an EGL display connection */
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        /* initialize the EGL display connection */
        eglInitialize(display, NULL, NULL);
        /* get an appropriate EGL frame buffer configuration */
        eglChooseConfig(display, config_attribute, &config, 1, &num_config);
        /* create an EGL rendering context */
        context = eglCreateContext(display, config, EGL_NO_CONTEXT, context_attribute);
        /* create a native window */
        native_window = createNativeWindow();
        /* create an EGL window surface */
        surface = eglCreateWindowSurface(display, config, native_window, NULL);
        /* connect the context to the surface */
        eglMakeCurrent(display, surface, surface, context);
        /* clear the color buffer */
        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        eglSwapBuffers(display, surface);
        _sleep(1000);
        return 0;
}