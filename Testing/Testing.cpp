// Testing.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "..\Library_3\Assoc.h"
#include "..\Library_3\LessonType.h"
#include "..\Library_3\Template.h"
#include "gtest\gtest.h"

TEST(LaboratoriesTesting, CheckConstructorDefaultInitialization)
{
	Laboratories t;
	EXPECT_DOUBLE_EQ(1, t.index);
	EXPECT_DOUBLE_EQ(15, t.capacity);
};

TEST(LaboratoriesTesting, CheckConstructor)
{
	Laboratories t(1, 10);
	EXPECT_DOUBLE_EQ(1, t.index);
	EXPECT_DOUBLE_EQ(10, t.capacity);
};

TEST(LectionTesting, ConstructorTesting)
{
	

};

int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

