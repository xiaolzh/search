#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <cstdio>
#include <cstdlib>
#include <mysql.h>
#include <string>
#include <vector>
#include "UH_Define.h"
#include <iostream>
using namespace std;

static MYSQL mysql;
static bool connect(string host, string port, string username, string password, string database)
{
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, host.c_str(), username.c_str(), password.c_str(), database.c_str(), 
				atoi(port.c_str()), NULL, CLIENT_FOUND_ROWS))
	{
		cout <<"connect to database error." <<endl;
		return false;
	}
	cout <<"connect to database successfully!" <<endl;
	return true;
}

static bool query(string sql, vector<vector<string> >& result)
{
	int i, ret, row, column;
	MYSQL_RES *res = NULL;
	MYSQL_FIELD* field = NULL;;
	MYSQL_ROW result_row;

	mysql_query(&mysql, "set names gb2312");
	ret = mysql_query(&mysql, sql.c_str());
	if (ret)
	{
		cout <<"exec sql error." <<endl;
		mysql_close(&mysql);
		return false;
	}
	res = mysql_store_result(&mysql);
	if (res)
	{
		column = mysql_num_fields(res);
		row = mysql_num_rows(res);
		cout <<"query results " <<row <<" rows" <<endl;
		for (i = 0; field = mysql_fetch_field(res); i++)
		{
			cout <<field->name <<"\t";
		}
		cout <<endl;

		while (result_row = mysql_fetch_row(res))
		{
			vector<string> temp;
			for (i = 0; i < column; i++)
			{
				temp.push_back(string(result_row[i]));
			}
			result.push_back(temp);
		}
	}
	mysql_close(&mysql);
	return true;
}
#endif

