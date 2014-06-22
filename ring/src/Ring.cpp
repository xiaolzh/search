#include "Ring.h"

int Ring::init(string cfg)
{
	int ret;
	config = new IniConfig(cfg.c_str());
	string host = config->get("SERVER", "host");
	string port = config->get("SERVER", "port");

	cout <<"host: " <<host <<endl;
	cout <<"host: " <<port <<endl;
	m_run_status = 1;	
	ret = cp_listen_socket(m_reqsvr_socket, REQ_PORT);
	if (ret != 0)
	{
		cout <<"init request socket error." <<endl;
		return -1;
	}
	//ret = cp_create_thread(thread_process_server, (void*) this);
	//if (ret != 0)
	//{
	//	cout <<"start process thread error." <<endl;
	//	return -2;
	//}
	ret = cp_create_thread(thread_req_server, (void*) this);
	if (ret != 0)
	{
		cout <<"start req thread error." <<endl;
		return -3;
	}
	return 0;
}
void* Ring::thread_req_server(void* param)
{
	Ring* _this = static_cast<Ring*>(param);
	CP_SOCKET_T client_sock = -1;

	while (_this->m_run_status)
	{
		int ret = cp_accept_socket(_this->m_reqsvr_socket, client_sock);
		if (ret != 0)
		{
			continue;
		}
		cp_set_overtime(client_sock, 5000);
	}
}

void* Ring::thread_process_server(void* param)
{
	Ring* _this = static_cast<Ring*>(param);
	string host = _this->config->get("SERVER", "host");
	string port = _this->config->get("SERVER", "port");
	string username = _this->config->get("SERVER", "username");
	string password = _this->config->get("SERVER", "password");
	string database = _this->config->get("SERVER", "database");
	string sql = _this->config->get("SERVER", "sql");
	vector<vector<string> > results;
	DOC_INFO single_doc;

	while (_this->m_run_status)
	{
		if (false == connect(host, port, username, password, database))
		{
			sleep(5);
			continue;
		}
		if (false == query(sql, results))
		{
			sleep(5);
			continue;
		}
		for (size_t i = 0; i < results.size(); i++)
		{
			single_doc.name = results[i][0];
			single_doc.artist = results[i][1];
			single_doc.ringjson = results[i][2];
			single_doc.uri = results[i][3];

			_this->m_doc_info.push_back(single_doc);
		}
		sleep(3600);
	}
}

