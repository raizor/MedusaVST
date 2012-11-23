//#include "global.h"
#include "console.h"


#ifdef ENABLE_CONSOLE

using namespace std;

ZDebugConsole::ZDebugConsole()
{
	m_exists = ::AllocConsole() != 0;

	if (!m_exists)
	{
		//::MessageBox(0, TEXT("Couldn't create debug console!"), TEXT("Error"), MB_ICONERROR | MB_OK);
		return;
	}
		

	// sync stdin, stdout, stderr fds up with the new console
	// original source: http://www.halcyon.c...load/guicon.htm
	// changes: removed all warnings by changing types and casting
	// set the screen buffer to be big enough to let us scroll text

	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	::GetConsoleScreenBufferInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = 500;
	::SetConsoleScreenBufferSize(::GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

	// redirect unbuffered STDOUT to the console
	intptr_t	pStdHandle = reinterpret_cast<intptr_t>(::GetStdHandle(STD_OUTPUT_HANDLE));
	int			hConHandle = _open_osfhandle(pStdHandle, _O_TEXT);
	FILE* pFile = _fdopen( hConHandle, "w" );
	*stdout = *pFile;
	setvbuf( stdout, NULL, _IONBF, 0 );

	// redirect unbuffered STDIN to the console	
	pStdHandle = reinterpret_cast<intptr_t>(::GetStdHandle(STD_INPUT_HANDLE));
	hConHandle = _open_osfhandle(pStdHandle, _O_TEXT);
	pFile = _fdopen( hConHandle, "r" );
	*stdin = *pFile;
	setvbuf( stdin, NULL, _IONBF, 0 );

	// redirect unbuffered STDERR to the console
	pStdHandle = reinterpret_cast<intptr_t>(::GetStdHandle(STD_ERROR_HANDLE));
	hConHandle = _open_osfhandle(pStdHandle, _O_TEXT);
	pFile = _fdopen( hConHandle, "w" );	*stderr = *pFile;
	setvbuf( stderr, NULL, _IONBF, 0 );

	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
	// point to console as well	
	ios::sync_with_stdio();
}

ZDebugConsole::~ZDebugConsole()
{
	if (m_exists)
	{
		::FreeConsole();
		m_exists = false;
	}
}  

#endif