#include "pch.h"
#include "CppUnitTest.h"
#include "RBTree.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		static constexpr int arr[] = { 5, 2, 8, 1, 3, 7, 10, 9, 0, 4, 11, 15, 20,
				25, 30, 35, 40, 45, 12, 50, 55, 60, 65, 70, 75, 80, 85, 29, 21, 22, 23 };
		
		TEST_METHOD(TestMethod1)
		{
			std::ofstream log("log1.txt");
			int r_arr[] = { 1 };
			RBTree<int> tree;
			int size = sizeof(arr) / sizeof(int);
			int r_size = sizeof(r_arr) / sizeof(int);

			for (size_t i = 0; i < size; i++)
			{
				tree.add(arr[i]);
			}
			log << "Before:\n" << tree << "\n\n";
			for (size_t i = 0; i < r_size; i++)
			{
				tree.remove(r_arr[i]);
			}
			log << "After:\n" << tree << "\n\n";
			log.close();
		}

		TEST_METHOD(TestMethod2)
		{
			std::ofstream log("log2.txt");
			int r_arr[] = { 8 };
			RBTree<int> tree;
			int size = sizeof(arr) / sizeof(int);
			int r_size = sizeof(r_arr) / sizeof(int);

			for (size_t i = 0; i < size; i++)
			{
				tree.add(arr[i]);
			}
			log << "Before:\n" << tree << "\n\n";
			for (size_t i = 0; i < r_size; i++)
			{
				tree.remove(r_arr[i]);
			}
			log << "After:\n" << tree << "\n\n";
			log.close();
		}

		TEST_METHOD(TestMethod3)
		{
			std::ofstream log("log3.txt");
			int r_arr[] = { 15 };
			RBTree<int> tree;
			int size = sizeof(arr) / sizeof(int);
			int r_size = sizeof(r_arr) / sizeof(int);

			for (size_t i = 0; i < size; i++)
			{
				tree.add(arr[i]);
			}
			log << "Before:\n" << tree << "\n\n";
			for (size_t i = 0; i < r_size; i++)
			{
				tree.remove(r_arr[i]);
			}
			log << "After:\n" << tree << "\n\n";
			log.close();
		}

		TEST_METHOD(TestMethod4)
		{
			std::ofstream log("log4.txt");
			int arr[] = { 50, 25, 75, 70 };
			int r_arr[] = { 25 };
			RBTree<int> tree;
			int size = sizeof(arr) / sizeof(int);
			int r_size = sizeof(r_arr) / sizeof(int);

			for (size_t i = 0; i < size; i++)
			{
				tree.add(arr[i]);
				log << "Added " << arr[i] <<" :\n" << tree << "\n\n";
			}
			log.flush();
			log << "Before:\n" << tree << "\n\n";
			for (size_t i = 0; i < r_size; i++)
			{
				tree.remove(r_arr[i]);
			}
			log << "After:\n" << tree << "\n\n";
			log.close();
		}
	};
}
