// SockLx.h : Version 1.1��֧��Unicode��֧��VS2015��VC6���뻷����
//Author:������ʦ��װ�� ��֧��Linux������
//������ʦ΢����http://t.qq.com/richmain ������ʦ΢�ţ�richmain
//������õ�����Ŀ������Ƶ�̳̣����¼http://www.baojy.com
//////////////////////////////////////////////////////////////////////
#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>

#ifdef _WIN32
#include <WinSock2.h>
#include <process.h>
#ifdef _UNICODE
#include <WS2tcpip.h>
#endif
typedef int socklen_t;
typedef void RET_TYPE;
#else
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
typedef unsigned int SOCKET;
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL            *PBOOL;
typedef BOOL             *LPBOOL;
typedef BYTE            *PBYTE;
typedef BYTE             *LPBYTE;
typedef int             *PINT;
typedef int              *LPINT;
typedef WORD            *PWORD;
typedef WORD             *LPWORD;
typedef long             *LPLONG;
typedef DWORD           *PDWORD;
typedef DWORD            *LPDWORD;
typedef void             *LPVOID;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;
typedef const char* LPCTSTR;
typedef char* LPTSTR;
typedef void* RET_TYPE;
inline int GetLastError()
{
	return errno;
}
#define closesocket(x) close(x)


#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif
#endif
//MFC������CScoket����̫֧�ֿ���̨����֧�ֶ��߳�
class CSockLx
{
protected:
	SOCKET m_hSocket;//���ĳ�Ա����
public:
	operator SOCKET() const
	{
		return m_hSocket;
	}
	BOOL Create(UINT nSocketPort = 0, int nSocketType = SOCK_STREAM
		, LPCTSTR lpszSocketAddress = NULL);

	BOOL Accept(CSockLx& rConnectedSocket, LPTSTR szIP = NULL, UINT *nPort = NULL);
	BOOL Connect(LPCTSTR lpszHostAddress, UINT nHostPort);
	BOOL Listen(int nConnectionBacklog = 5)
	{
		return !listen(m_hSocket, nConnectionBacklog);
	}
	int SendTo(const void* lpBuf, int nBufLen, UINT nHostPort, LPCTSTR lpszHostAddress = NULL, int nFlags = 0);

	int ReceiveFrom(void* lpBuf, int nBufLen, LPTSTR rSocketAddress, UINT& rSocketPort, int nFlags = 0);

	int Send(const void* lpBuf, int nBufLen, int nFlags = 0)
	{
		return send(m_hSocket, (LPCSTR)lpBuf, nBufLen, nFlags);
	}
	int Receive(void* lpBuf, int nBufLen, int nFlags = 0)
	{
		return recv(m_hSocket, (LPSTR)lpBuf, nBufLen, nFlags);
	}
	BOOL GetPeerName(LPTSTR rSocketAddress, UINT& rSocketPort);
	BOOL GetSockName(LPTSTR rSocketAddress, UINT& rSocketPort);

	void Close()
	{
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
	}

#ifdef _UNICODE
	inline static void Pton(LPCTSTR sHostAddr, IN_ADDR &in)
	{
		InetPton(AF_INET, sHostAddr, &in);
	}
	inline void Ntop(IN_ADDR &in, LPTSTR sHostAddr)
	{
		InetNtop(AF_INET, &in, sHostAddr, 20);
	}

#else
	inline void Pton(LPCSTR sHostAddr, IN_ADDR &in)
	{
		in.s_addr = inet_addr(sHostAddr);
	}
	inline void Ntop(IN_ADDR &in, LPTSTR sHostAddr)
	{
		strcpy(sHostAddr, inet_ntoa(in));
	}
#endif

	CSockLx();
	virtual ~CSockLx();
};