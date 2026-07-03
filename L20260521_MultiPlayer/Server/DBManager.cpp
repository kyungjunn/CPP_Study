#include "DBManager.h"

#include "jdbc/cppconn/exception.h"
#include "jdbc/cppconn/resultset.h"
#include "jdbc/cppconn/statement.h"
#include "jdbc/cppconn/prepared_statement.h"

#include <iostream>

#ifndef _DEBUG
#pragma comment(lib, "mysqlcppconn")
#else
#pragma comment(lib, "debug/mysqlcppconn")
#endif // !_DEBUG


DBManager::DBManager() : MyDriver(nullptr), MyConnection(nullptr)
{
}

bool DBManager::Connect()
{
	try
	{
		// MySQL 연결
		MyDriver = get_driver_instance(); // 드라이버 싱글톤 생성
		MyConnection = MyDriver->connect("tcp://127.0.0.1", "june021124", "rudwns1124");
			
		MyConnection->setSchema("membership"); // DataBase 연결

		return true;
	}
	catch (sql::SQLException e)
	{
		std::cout << "MySQL DB 연결 실패" << std::endl;
		return false;
	}
}

bool DBManager::CreateUser(const std::string& id, const std::string& pw, const std::string& name)
{
	try
	{

	}
	catch (sql::SQLException e)
	{

	}
	return false;
}

bool DBManager::AuthenticateUser(const std::string& id, const std::string& pw)
{
	try
	{
		sql::SQLString Query = "select * from user where user_id = ? and user_pw = ? and is_delete = 'N'";
		sql::PreparedStatement* pstmt = MyConnection->prepareStatement(Query);

		// 값 바인딩
		pstmt->setString(1, id);
		pstmt->setString(2, pw);

		// 쿼리 실행
		sql::ResultSet* MyResultSet = pstmt->executeQuery();

		if (MyResultSet->rowsCount() == 0)
		{
			std::cout << "아이디와 비밀번호가 틀립니다." << std::endl;
			return false;
		}
		else
		{
			std::cout << "로그인 성공 !" << std::endl;

			// 조회된 유저 데이터 순회
			for (; MyResultSet->next();)
			{
				std::cout << MyResultSet->getInt("idx") << std::endl;
				std::cout << MyResultSet->getString("user_id") << std::endl;
				std::cout << MyResultSet->getString("user_pw") << std::endl;
				std::cout << MyResultSet->getString("user_name") << std::endl;
				std::cout << MyResultSet->getString("created_at") << std::endl;
				std::cout << MyResultSet->getString("is_delete") << std::endl;
			}
		}

		return true;
	}
	catch (sql::SQLException e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}

}

