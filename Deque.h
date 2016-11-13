//link to my project on githab
//https://github.com/KaEuAn/Deque-Visual

#include <iostream>

template <typename T>
class Deque {
	static const uint32_t MIN_SIZE = 8;
	static const uint16_t EXP_CONST = 2;
	T* container;
	uint32_t real_size;
	uint32_t first;
	uint32_t last;
	void makeNext(uint32_t& i) const {
		i = (i + 1) % (real_size);
	}
	void makePrevious(uint32_t& i) const {
		i = (i - 1 + real_size) % real_size;
	}

	void tryExtend() {
		if (size() == real_size - 1) {
			T *new_container = new T[real_size * EXP_CONST];
			uint32_t j = 0;
			for (uint32_t i = first; i != last; makeNext(i), ++j) {
				new_container[j] = container[i];
			}
			first = 0;
			last = j;
			T *per = container;
			real_size *= EXP_CONST;
			container = new_container;
			delete[] per;
		}
	}

	void tryMinimize() {
		if (size() * EXP_CONST * EXP_CONST < real_size) {
			T *new_container = new T[real_size / EXP_CONST];
			uint32_t j = 0;
			for (uint32_t i = first; i != last; makeNext(i), ++j) {
				new_container[j] = container[i];
			}
			first = 0;
			last = j;
			real_size /= EXP_CONST;
			T *per = container;
			container = new_container;
			delete[] per;
		}
	}

public:

	Deque() : real_size(MIN_SIZE), first(0), last(0) {
		container = new T[real_size];
	}
	Deque(const Deque& a) {
		real_size = a.real_size;
		container = new T[real_size];
		first = a.first;
		last = a.last;
		for (uint32_t i = first; i != last; a.makeNext(i)) {
			container[i] = a.container[i];
		}
	}

	~Deque() {
		delete[] container;
	}


	template <typename _T>
	class DequeIterator : public std::iterator <std::random_access_iterator_tag, T, std::ptrdiff_t, _T*, _T& > {
		typedef typename std::iterator<std::random_access_iterator_tag, T, std::ptrdiff_t, _T*, _T& >::difference_type differ;

		uint32_t index;
		const Deque<T>* my_deque;
		void makeNext(uint32_t& i) const {
			i = (i + 1) % (my_deque->real_size);
		}
		void makePrevious(uint32_t& i) const {
			i = (i - 1 + my_deque->real_size) % my_deque->real_size;
		}
	public:
		DequeIterator(uint32_t ind, const Deque<T>* deq) : index(ind), my_deque(deq) {}
		DequeIterator(const DequeIterator& x) : index(x.index), my_deque(x.my_deque) {}

		DequeIterator& operator ++() {
			makeNext(index);
			return *this;
		}
		DequeIterator& operator --() {
			makePrevious(index);
			return *this;
		}
		const DequeIterator operator --(int) {
			DequeIterator previous = *this;
			--(*this);
			return previous;
		}
		const DequeIterator operator ++(int) {
			DequeIterator previous = *this;
			++(*this);
			return previous;
		}

		DequeIterator& operator += (const differ& x) {
			index = (index + x) % (my_deque->real_size);
			return *this;
		}
		DequeIterator& operator -= (const differ& x) {
			index = (index - x + my_deque->real_size) % my_deque->real_size;
			return *this;
		}
		DequeIterator operator - (const differ& x) const {
			uint32_t new_index = (index - x + my_deque->real_size) % my_deque->real_size;
			return DequeIterator(new_index, my_deque);
		}
		differ operator - (const DequeIterator& x) const {
			return (index - x.index + my_deque->real_size) % my_deque->real_size;
		}
		DequeIterator operator + (const differ& x) const {
			uint32_t new_index = (index + x) % (my_deque->real_size);
			return DequeIterator(new_index, my_deque);
		}


		bool operator <(const DequeIterator& a) const {
			if (my_deque->first < my_deque->last)
				return index < a.index;
			if (my_deque->first <= index && my_deque->first <= a.index)
				return index < a.index;
			if (my_deque->last > index && my_deque->last > a.index)
				return index < a.index;
			return my_deque->first <= index;

		}
		bool operator >(const DequeIterator& a) const {
			return a < *this;
		}
		bool operator <=(const DequeIterator& a) const {
			return !(a < *this);
		}
		bool operator >=(const DequeIterator& a) const {
			return !(*this < a);
		}
		bool operator ==(const DequeIterator& a) const {
			return index == a.index;
		}
		bool operator !=(const DequeIterator& a) const {
			return index != a.index;
		}
		_T& operator *() const {
			return my_deque->container[index];
		}
		_T* operator ->() {
			return my_deque->container + index;
		}


	};
	typedef DequeIterator<T> iterator;
	typedef DequeIterator<const T> const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;


	const T& back() const {
		uint32_t i = last;
		makePrevious(i);
		return container[i];
	}
	const T& front() const {
		return container[first];
	}

	T& front() {
		return container[first];
	}
	T& back() {
		uint32_t i = last;
		makePrevious(i);
		return container[i];
	}

	bool empty() const {
		return first == last;
	}
	uint32_t size() const {
		return (last - first + real_size) % real_size;
	}

	void push_back(const T x) {
		tryExtend();
		container[last] = x;
		makeNext(last);
	}
	void push_front(const T x) {
		tryExtend();
		makePrevious(first);
		container[first] = x;
	}
	void pop_back() {
		makePrevious(last);
		tryMinimize();
	}
	void pop_front() {
		makeNext(first);
		tryMinimize();
	}

	T& operator [] (uint32_t x) {
		uint32_t i = first + x - 1;
		makeNext(i);
		return container[i];
	}
	const T& operator [] (uint32_t x) const {
		uint32_t i = first + x - 1;
		makeNext(i);
		return container[i];
	}

	iterator begin() {
		return iterator(first, this);
	}
	iterator end() {
		return iterator(last, this);
	}
	const_iterator cbegin() const {
		return const_iterator(first, this);
	}
	const_iterator cend() const {
		return const_iterator(last, this);
	}
	const_iterator begin() const {
		return cbegin();
	}
	const_iterator end() const {
		return cend();
	}
	reverse_iterator rend() {
		return reverse_iterator(begin());
	}
	reverse_iterator rbegin() {
		return reverse_iterator(end());
	}
	const_reverse_iterator crend() const {
		return const_reverse_iterator(cbegin());
	}
	const_reverse_iterator crbegin() const {
		return const_reverse_iterator(cend());
	}
	const_reverse_iterator rend() const {
		return crend();
	}
	const_reverse_iterator rbegin() const {
		return crbegin();
	}




};