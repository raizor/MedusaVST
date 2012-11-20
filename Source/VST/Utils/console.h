#ifndef __ZDEBUGCONSOLE_H__
#define __ZDEBUGCONSOLE_H__

// From gamedev.net: http://www.gamedev.net/topic/157913-separate-console-window/

// Creates a debug console that lasts the duration of the DebugConsole object
// lifetime, and syncs stdin/stdout/stderr and the C++ streams to print there.

class ZDebugConsole
{
public:
	ZDebugConsole();
	~ZDebugConsole();
private:
	bool	m_exists;
};
#endif //__ZDEBUGCONSOLE_H__
