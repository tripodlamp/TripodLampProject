// Sio.cpp: implementation of the CSio class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "sio.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define USE_CONSOLE 1


CSio::CSio()
{
	com_port=-1;
	baud_rate=4800;
	rts_state=0;
	hCom=INVALID_HANDLE_VALUE;
}

CSio::~CSio()
{
	Close();
}

bool CSio::Open()
{
	if(hCom!=INVALID_HANDLE_VALUE)
		return 1;
	char com_name[20];
	sprintf(com_name,"COM%d",com_port);
	hCom=CreateFileA(com_name,GENERIC_WRITE|GENERIC_READ,0,0,OPEN_EXISTING,0,0);
	if(hCom!=INVALID_HANDLE_VALUE)
	{
		DCB dcb;
		COMMTIMEOUTS cto;
		if(SetupComm(hCom,4096,0))
		{
			memset(&dcb,0,sizeof(dcb));
			dcb.DCBlength=sizeof(dcb);
			dcb.BaudRate=baud_rate;
			dcb.fBinary=TRUE;
			dcb.fDtrControl=DTR_CONTROL_DISABLE;
			dcb.fRtsControl=rts_state?RTS_CONTROL_ENABLE:RTS_CONTROL_DISABLE;
			dcb.fOutxCtsFlow=0;
			dcb.ByteSize=8;
			dcb.Parity=NOPARITY;
			dcb.StopBits=ONESTOPBIT;
			cto.ReadIntervalTimeout=MAXDWORD;
			cto.ReadTotalTimeoutMultiplier=0;
			cto.ReadTotalTimeoutConstant=20;
			cto.WriteTotalTimeoutMultiplier=0;
			cto.WriteTotalTimeoutConstant=0;
			if(!SetCommState(hCom,&dcb)||!SetCommTimeouts(hCom,&cto))
			{
				Close();
			}
		}
		else
		{
			Close();
		}
	}
	return hCom!=INVALID_HANDLE_VALUE;
}

void CSio::Close()
{
	if(hCom!=INVALID_HANDLE_VALUE)
		CloseHandle(hCom);
	hCom=INVALID_HANDLE_VALUE;
}

bool CSio::Write(const byte* send_buf,unsigned send_len)
{
	if(hCom==INVALID_HANDLE_VALUE)
		return 0;
	unsigned long l;
	if(send_len==0)
		send_len=strlen((char*)send_buf);
	return WriteFile(hCom,send_buf,send_len,&l,0)&&((unsigned)l)==send_len;
}

unsigned CSio::Read(byte* buf,unsigned len,double timeout /* =-1 */)
{
	if(hCom==INVALID_HANDLE_VALUE)
		return 0;
	if(timeout<0) timeout=double(len)/baud_rate*15+0.2;
	unsigned long l=0;
	clock_t t=clock();
	do{
		unsigned long ll;
		ReadFile(hCom,&buf[l],len-l,&ll,0);
		l+=ll;
	}while(l<(unsigned long)len && (clock()-t)/CLK_TCK<timeout);
	return (unsigned)l;
}


void CSio::Purge()
{
	if(hCom==INVALID_HANDLE_VALUE)
		return;
	PurgeComm(hCom,PURGE_RXCLEAR);
}

void CSio::SetComPort(int comport)
{
	if(hCom!=INVALID_HANDLE_VALUE)
		Close();
	com_port=comport;
}

bool CSio::SetBaudRate(int baudrate)
{
	if(baud_rate==baudrate)
		return 1;
	baud_rate=baudrate;
	if(hCom==INVALID_HANDLE_VALUE)
		return 0;
	DCB dcb;
	dcb.DCBlength=sizeof(dcb);
	if(GetCommState(hCom,&dcb))
	{
		dcb.BaudRate=baud_rate;
		return SetCommState(hCom,&dcb)?1:0;
	}
	return 0;
}

void CSio::SetRtsState(int rtsstate)
{
	rts_state=rtsstate;
	if(hCom==INVALID_HANDLE_VALUE)
		return;
	EscapeCommFunction(hCom,rts_state?SETRTS:CLRRTS);
}
