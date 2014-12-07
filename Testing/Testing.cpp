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

TEST(SubjectTesting, SetSubLecitonTesting)
{
	Subject t;
	cout << "Choose Lection, all the other parametrs: 1 ";
	t.setSub("math", 1);
	EXPECT_EQ(1, t.kol);
	EXPECT_EQ("math", t.name);
	EXPECT_EQ(1, t.ptr[0]->getquan());
	EXPECT_EQ(1, t.ptr[0]->type());
};

TEST(SubjectTesting, SetSubSeminarTesting)
{
	Subject t;
	cout << "Choose Seminar, all the other parametrs: 1 ";
	t.setSub("math", 1);
	EXPECT_EQ(1, t.kol);
	EXPECT_EQ("math", t.name);
	EXPECT_EQ(1, t.ptr[0]->getquan());
	EXPECT_EQ(2, t.ptr[0]->type());
};

TEST(SubjectTesting, SetSubLaboratoryTesting)
{
	Subject t;
	cout << "Choose Labora,tory all the other parametrs: 1 ";
	t.setSub("math", 1);
	EXPECT_EQ(1, t.kol);
	EXPECT_EQ("math", t.name);
	EXPECT_EQ(1, t.ptr[0]->getquan());
	EXPECT_EQ(3, t.ptr[0]->type());
};

int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

