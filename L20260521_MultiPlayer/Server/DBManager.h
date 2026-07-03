#pragma once

#include "jdbc/mysql_connection.h"
#include "jdbc/cppconn/driver.h"

#include <string>

class DBManager
{
public :
	DBManager();

	// MySQL 연결
	bool Connect();

	// 회원가입
	bool CreateUser(const std::string& id, const std::string& pw, const std::string& name);

	// 로그인
	bool AuthenticateUser(const std::string& id, const std::string& pw);
	

private:
	sql::Driver* MyDriver;
	sql::Connection* MyConnection;
};

