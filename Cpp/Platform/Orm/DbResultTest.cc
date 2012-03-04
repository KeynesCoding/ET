// Copyright: All Rights Reserved
// Author: egametang@gmail.com (tanghai)

#include <gtest/gtest.h>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include "Orm/DbHelper.h"
#include "Orm/DbResult.h"
#include "Orm/Select.h"
#include "Orm/Person.pb.h"
#include "Orm/Exception.h"

namespace Egametang {

class DbResultTest: public testing::Test
{
};

TEST_F(DbResultTest, One)
{
	try
	{
		DbHelper dbHelper("tcp://192.168.1.104:3306", "root", "111111");

		DbResultPtr result = dbHelper.Execute(
				Select<Person>(Column("*")).
				Where(Column("age") > 10)
			);

		boost::shared_ptr<Person> person;
		result->One(person);
	}
	catch (Exception& e)
	{
		if (const std::string* str=boost::get_error_info<ConnectionErrStr>(e))
		{
			LOG(FATAL) << *str;
		}
	}
}

} // namespace Egametang

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	google::InitGoogleLogging(argv[0]);
	google::ParseCommandLineFlags(&argc, &argv, true);
	return RUN_ALL_TESTS();
}
