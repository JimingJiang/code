#include <afxmt.h>
#include <iostream>
#include <string>
#include <vector>
#include <afxwin.h>
#include "Shlwapi.h"
using namespace std;

#ifndef LOG4CPLUS_STATIC
#define LOG4CPLUS_STATIC
#endif

#include <log4cplus/logger.h> 
#include <log4cplus/fileappender.h> 
#include <log4cplus/consoleappender.h> 
#include <log4cplus/layout.h> 
#include <log4cplus/configurator.h>
using namespace log4cplus; 
using namespace log4cplus::helpers;

#pragma comment(lib, "log4cplusd.lib") 
#pragma comment(lib, "shlwapi.lib") 

//初始化代码
void InitLog4cplus()
{
	string  logconffile;
	TCHAR appPath[256];
	if (GetModuleFileName(NULL,appPath,256) == 0)
	{
		AfxMessageBox("GetCurrentDirectory error");
	}
	PathRemoveFileSpec(appPath);
	logconffile=appPath;
	logconffile+='\\';
	logconffile+="log4cplus.cfg";
	//日志配置文件路径
	cout<<"log4cplus start:"<<logconffile<<endl;
	PropertyConfigurator::doConfigure(_T(logconffile.c_str())); 
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	InitLog4cplus();
	LOG4CPLUS_ERROR(Logger::getRoot(), "Error at WSAStartup()\n");

	string str = "test1";
	LOG4CPLUS_DEBUG(Logger::getRoot(), "Debuging... "<<str);
	return 0;
}
