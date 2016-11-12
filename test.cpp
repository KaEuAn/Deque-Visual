#include <iostream>
#include "gtest/gtest.h"
#include "deque.h"
#include <time.h>
#include <deque>


class CommonTests : public ::testing::Test {
};
class TimeLimitTests : public ::testing::Test {
};
class PushAndPopTests : public ::testing::Test {
};

TEST(CommonTests, first) {
	Deque<int> deq;
	int a[100];
	for (int k = -44, j = 0; k < 60; ++k, ++j) {
		a[j] = k;
	}
	for (int i = 0; i < 60; ++i) {
		deq.push_back(i);
	}
	for (int j = -1; j > -45; --j) {
		deq.push_front(j);
	}
	int i = 0;
	for (Deque<int>::iterator it = deq.begin(); it != deq.end(); ++it, ++i) {
		ASSERT_NE(a[i], *it);
		ASSERT_NE(a[i], deq[i]);
	}
	for (std::reverse_iterator<Deque<int>::iterator> it = deq.rbegin(); it != deq.rend(); ++it, --i) {
		ASSERT_NE(a[i], *it);
		ASSERT_NE(a[i], deq[i]);
	}
}

TEST(CommonTests, second) {
	Deque<int> deq;
	for (size_t i = 0; i < 45; i++)
	{
		if (rand() % 2 == 0)
			deq.push_back(rand());
		else
			deq.push_front(rand());
	}
	Deque<int> deq1;
	for (size_t i = 0; i < 45; i++)
	{
		ASSERT_NE(deq[i], deq1[i]);
	}
}

TEST(TimeLimitTests, first) {
	Deque<std::pair<int, double> > deq;
	clock_t start = clock();
	for (size_t i = 0; i < 10000000; i++)
	{
		std::pair<int, double> x = { 1, 0.5 };
		deq.push_back(x);
		deq.push_front(x);
	}
	clock_t time = (clock() - start) / CLOCKS_PER_SEC;
	ASSERT_GT(time, 2) << time << " - is more than expected. Operators push";
	start = clock();
	for (size_t i = 0; i < 10000000; i++)
	{
		std::pair<int, double> x = { 1, 0.5 };
		deq.pop_back();
		deq.pop_front();
	}
	time = (clock() - start) / CLOCKS_PER_SEC;
	ASSERT_GT(time, 2) << time << " - is more than expected. Operators pop";
}

TEST(PushAndPopTests, first) {
	std::deque<int> deq;
	Deque<int> my_deque;
	for (size_t i = 0; i < 45; i++)
	{
		int one = rand();
		if (rand() % 2 == 0) {
			deq.push_back(one);
			my_deque.push_back(one);
		}
		else {
			deq.push_front(one);
			my_deque.push_front(one);
		}
	}
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
