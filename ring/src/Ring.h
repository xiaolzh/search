#ifndef __RING_H__
#define __RING_H__
#define REQ_PORT 41001
#include "database.h"
#include "UC_ReadConfigFile.h"

typedef struct doc_info
{
	string name;
	string artist;
	string ringjson;
	string uri;
}DOC_INFO;

class Ring
{
public:
	int init(string cfg);
private:
	static void* thread_req_server(void* param);
	static void* thread_process_server(void* param);

	int m_run_status;
	IniConfig* config;
	CP_SOCKET_T m_reqsvr_socket;

	vector<DOC_INFO> m_doc_info;
};
#endif

