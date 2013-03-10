// Sio.h: interface for the CSio class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIO_H__3CB10975_CDB0_4E3E_9A45_11F1BFD7088D__INCLUDED_)
#define AFX_SIO_H__3CB10975_CDB0_4E3E_9A45_11F1BFD7088D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

typedef unsigned char byte;

class CSio  
{
public:
	CSio();
	~CSio();
	bool Open();
	void Close();
	void SetComPort(int);
	bool SetBaudRate(int);
	void SetRtsState(int);
	bool Write(const byte*,unsigned);
	unsigned Read(byte*,unsigned,double=-1);
	void Purge();
	bool IsOpen()
		{return hCom!=INVALID_HANDLE_VALUE;}
protected:
	int com_port;
	int baud_rate;
	int rts_state;
	HANDLE hCom;
};

#endif // !defined(AFX_SIO_H__3CB10975_CDB0_4E3E_9A45_11F1BFD7088D__INCLUDED_)
