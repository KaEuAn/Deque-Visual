#include <iostream>
#include "gtest/gtest.h"
#include "deque.h"
#include <time.h>


class IteratorsTests : public ::testing::Test {
};
class TimeLimitTests : public ::testing::Test {
};

TEST(IteratorsTests, first) {
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
	ASSERT_GT(time, 2) << time;
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
