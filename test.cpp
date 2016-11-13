#include <iostream>
#include "gtest/gtest.h"
#include "deque.h"
#include <time.h>
#include <deque>

template <typename T>
void makeRandomPush(T x, Deque<T>& my_deque) {
	int one = rand();
	if (one % 2 == 0)
		my_deque.push_back(x);
	else
		my_deque.push_front(x);
}

template <typename T>
void makeRandomPop(Deque<T>& my_deque) {
	int one = rand();
	if (one % 2 == 0)
		my_deque.pop_back();
	else
		my_deque.pop_front();
}

template <typename T>
void makeRandomIndex(Deque<T>& my_deque) {
	my_deque[rand() % my_deque.size()];
}

template <typename T>
void makeRandomOperation(Deque<T>& my_deque) {
	T x;

	if (my_deque.empty()) {
		makeRandomPush<T>(x, my_deque);
	}
	else {
		int one = rand();
		if (one % 3 == 0)
			makeRandomPush<T>(x, my_deque);
		else if (one % 3 == 1)
			makeRandomIndex<T>(my_deque);
		else
			makeRandomPop<T>(my_deque);
	}
	}


class CommonTests : public ::testing::Test {
};
class TimeLimitTests : public ::testing::Test {
};
class PushAndPopTests : public ::testing::Test {
};
class IteratorsTests: public ::testing::Test{};

TEST(CommonTests, first) {
	Deque<int> deq;
	int a[120];
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
	ASSERT_FALSE(deq.empty());
	ASSERT_EQ(deq.size(), 104);
	for (Deque<int>::iterator it = deq.begin(); it != deq.end(); ++it, ++i) {
		ASSERT_EQ(a[i], *it);
		ASSERT_EQ(a[i], deq[i]);
	}
	--i;
	for (std::reverse_iterator<Deque<int>::iterator> it = deq.rbegin(); it != deq.rend(); ++it, --i) {
		ASSERT_EQ(a[i], *it);
		ASSERT_EQ(a[i], deq[i]);
	}
}

TEST(CommonTests, second) {
	Deque<int> deq;
	for (size_t i = 0; i < 45; ++i)
	{
		if (rand() % 2 == 0)
			deq.push_back(rand());
		else
			deq.push_front(rand());
	}
	Deque<int> deq1(deq);
	for (size_t i = 0; i < 45; ++i)
	{
		ASSERT_EQ(deq[i], deq1[i]) << "i is " << i << '\n';
	}
}

template <typename T>
void TLTest(uint32_t operations_count) {
	Deque<T> deq;
	clock_t start = clock();
	for (size_t i = 0; i < operations_count; ++i) {
		T x;
		makeRandomPush<T>(x, deq);
	}
	double time1 = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
	ASSERT_LT(time1, 2.5) << time1 << " - is more than expected. Operators push";
	start = clock();
	for (size_t i = 0; i < operations_count; ++i) {
		int one = rand() % deq.size();
		deq[i];
	}
	double time2 = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
	ASSERT_LT(time2, 2.5) << time2 << " - is more than expected. Operators pop";
	start = clock();
	for (size_t i = 0; i < operations_count; ++i) {
		T x;
		makeRandomPop<T>(deq);
	}
	double time3 = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
	std::cout << "[----------] "<< operations_count << "pushs in " << time1 << " seconds\n"
		<< "[----------] " << operations_count << "[] in " << time2 << " seconds\n"
		<< "[----------] " << operations_count << "pops in " << time3 << " seconds\n";
}

TEST(TimeLimitTests, first) {
	for (size_t i = 30; i < 3000010; i*=10) {
		TLTest<std::pair<int, double> >(i);
	}
}

template <typename T>
void TLTestRandom(uint32_t operations_count) {
	Deque<T> deq;
	clock_t start = clock();
	for (size_t i = 0; i < operations_count; ++i) {
		makeRandomOperation<T>(deq);
	}
	double time = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
	std::cout << "[----------] " << operations_count << "random operation in " << time << " seconds\n";
}

TEST(TimeLimitTests, randomChoiceOperations) {
	for (size_t i = 60; i < 6000010; i *= 10) {
		TLTestRandom<std::pair <std::pair<bool, double>, float> >(i);
	}
}

void oneStep(bool isPush, std::deque<int>& deq, Deque<int>& my_deque) {
	for (size_t i = 0; i < 450; ++i)
	{
		int one = rand();
		if (rand() % 2 == 0) {
			if (isPush) {
				deq.push_back(one);
				my_deque.push_back(one);
			}
			else {
				deq.pop_back();
				my_deque.pop_back();
			}
		} else {
			if (isPush) {
				deq.push_front(one);
				my_deque.push_front(one);
			} else {
				deq.pop_front();
				my_deque.pop_front();
			}
		}
		if (deq.size() < 2)
			continue;
		ASSERT_EQ(deq.size(), my_deque.size());
		one %= deq.size();
		ASSERT_EQ(deq[one], my_deque[one]);
	}
}

TEST(PushAndPopTests, first) {
	std::deque<int> deq;
	Deque<int> my_deque;
	for (size_t i = 0; i < 10; ++i) {
		oneStep(true, deq, my_deque);
		oneStep(false, deq, my_deque);
	}
	for (size_t i = 0; i < 450; ++i)
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
		ASSERT_EQ(deq.size(), my_deque.size());
		one %= deq.size();
		ASSERT_EQ(deq[one], my_deque[one]);
		ASSERT_EQ(deq.back(), my_deque.back());
		ASSERT_EQ(deq.front(), my_deque.front());
		Deque<int> new_deque(my_deque);
		ASSERT_EQ(new_deque.back(), my_deque.back());
		ASSERT_EQ(new_deque.front(), my_deque.front());
		ASSERT_EQ(new_deque[one], my_deque[one]);
	}
}

TEST(IteratorsTests, first) {
	Deque<std::pair<int, int> > deq;
	Deque<std::pair<int, int> > deq2;
	for (size_t i = 0; i < 400; ++i) {
		const std::pair<int, int> one = {i, 2 * i};
		makeRandomPush<std::pair<int, int> >(one, deq);
		makeRandomPush<std::pair<int, int> >(one, deq2);
	}
	std::reverse_iterator< Deque<std::pair<int, int> >::iterator > it = deq.rbegin();
	std::reverse_iterator< Deque<std::pair<int, int> >::const_iterator > it2 = deq.crbegin();
	std::reverse_iterator< Deque<std::pair<int, int> >::iterator > it3 = it;
	it->first += 8;
	ASSERT_EQ((*it), deq.back());
	ASSERT_EQ(it->first, deq[deq.size() - 1].first);
	ASSERT_EQ(*it2, *it);
	it3 += 10;
	ASSERT_EQ(*it3, deq[deq.size() - 11]);
	it3 += (it3 - it);
	ASSERT_EQ(*it3, deq[deq.size() - 21]);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	::testing::FLAGS_gtest_repeat = 3;
	::testing::FLAGS_gtest_break_on_failure = true;
	return RUN_ALL_TESTS();
}
