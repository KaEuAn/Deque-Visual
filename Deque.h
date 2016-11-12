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
			real_size *= EXP_CONST;
			uint32_t j = 0;
			for (uint32_t i = first; i != last; makeNext(i), ++j) {
				new_container[i] = container[i];
			}
			first = 0;
			last = j;
			T *per = container;
			container = new_container;
			delete[] per;
		}
	}

	void tryMinimize() {
		if (size() * EXP_CONST * EXP_CONST < real_size) {
			T *new_container = new T[real_size / EXP_CONST];
			real_size /= EXP_CONST;
			uint32_t j = 0;
			for (uint32_t i = first; i != last; makeNext(i), ++j) {
				new_container[j] = container[i];
			}
			first = 0;
			last = j;
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
	}

	~Deque() {
		delete[] container;
	}


	template <typename _T>
	class DequeIterator : public std::iterator <std::random_access_iterator_tag, T> {
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

		DequeIterator& operator ++ () {
			makeNext(index);
			return *this;
		}
		DequeIterator& operator -- () {
			makePrevious(index);
			return *this;
		}
		DequeIterator& operator += (int n) {
			index += n - 1;
			makeNext(index);
			return *this;
		}
		DequeIterator& operator -= (int n) {
			index -= n - 1;
			makePrevious(index);
			return *this;
		}
		int operator - (const DequeIterator& a) const {
			return (index - a.index);
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
		T& operator * () const {
			return my_deque->container[index];
		}
	};
	typedef DequeIterator<T> iterator;
	typedef DequeIterator<const T> citerator;
	typedef std::reverse_iterator<iterator> riterator;
	typedef std::reverse_iterator<citerator> criterator;



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

	void push_back(T& x) {
		tryExtend();
		container[last] = x;
		makeNext(last);
	}
	void push_front(T& x) {
		tryExtend();
		makePrevious(first);
		container[first] = x;
	}
	void pop_back(T& x) {
		makePrevious(last);
		tryMinimize();
	}
	void pop_front(T& x) {
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
	citerator cbegin() const {
		return citerator(first, this);
	}
	citerator cend() const {
		return citerator(last, this);
	}
	citerator begin() const {
		return cbegin();
	}
	citerator end() const {
		return cend();
	}
	riterator rend() {
		return riterator(begin());
	}
	riterator rbegin() {
		return riterator(end());
	}
	criterator crend() const {
		return criterator(cbegin());
	}
	criterator crbegin() const {
		return criterator(cend());
	}
	criterator rend() const {
		return crend();
	}
	criterator rbegin() const {
		return crbegin();
	}




};