#include <iostream>
#include <gtest/gtest.h>
using namespace std;

int main(int * argc, char ** argv)
{
	cout << "Goodle Test";
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
