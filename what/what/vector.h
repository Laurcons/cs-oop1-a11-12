#pragma once

namespace bub {

	// Dynamic array
	template <class T>
	class vector {
	private:
		T* elem;
		int length;
		int capacity;
	public:
		// Creates a vector.
		vector();
		// Copies a vector.
		vector(const vector&);
		// Destroys a vector.
		~vector();
		// Adds an element to the vector.
		void add(T elem);
		// Adds an element to the vector.
		vector operator+(const T);
		// Removes an element at a certain position in the vector.
		void remove(int);
		// Returns the element at the position in the vector. Negative values are allowed.
		T& at(int) const;
		// Returns the element at the position in the vector. Negative values are allowed.
		T& operator[](int) const;
		// Assigns a vector to itself.
		vector operator=(const vector&);
		// Returns the amount of items in the vector.
		int size() const;

		class iterator {
			T* pointer;
		public:
			iterator(T* p) : pointer(p) {}

			T& operator*() const { return *this->pointer; }
			T* operator->() const { return this->pointer; }

			iterator& operator++() { this->pointer++; return *this; }

			friend bool operator==(const iterator& a, const iterator& b) {
				return a.pointer == b.pointer;
			}
			friend bool operator!=(const iterator& a, const iterator& b) {
				return a.pointer != b.pointer;
			}
		};

		// Returns a begin iterator on the vector.
		iterator begin() { return iterator(&this->elem[0]); }
		// Returns an end iterator on the vector.
		iterator end() { return iterator(&this->elem[this->length]); }
	};

	template <class T>
	vector<T>::vector() {
		this->capacity = 3;
		this->length = 0;
		this->elem = DBG_NEW T[3];
	}

	template <class T>
	vector<T>::~vector() {
		delete[] this->elem;
	}

	template <class T>
	vector<T>::vector(const vector<T>& v) {
		this->length = v.length;
		this->capacity = v.capacity;
		this->elem = DBG_NEW T[this->capacity];
		for (int i = 0; i < v.length; i++) {
			this->elem[i] = v.elem[i];
		}
	}

	template <class T>
	vector<T> vector<T>::operator=(const vector<T>& v) {
		this->length = v.length;
		this->capacity = v.capacity;
		delete[] this->elem;
		this->elem = DBG_NEW T[this->capacity];
		for (int i = 0; i < v.length; i++) {
			this->elem[i] = v.elem[i];
		}
		return *this;
	}

	template <class T>
	void vector<T>::add(T elem) {
		// resize if necessary
		if (this->length == this->capacity) {
			this->capacity *= 2;
			T* oldp = this->elem;
			this->elem = DBG_NEW T[this->capacity];
			for (int i = 0; i < this->length; i++) {
				this->elem[i] = oldp[i];
			}
			delete[] oldp;
		}
		// add element
		this->elem[this->length] = elem;
		this->length++;
	}

	template <class T>
	vector<T> vector<T>::operator+(const T elem) {
		vector<T> newv = *this;
		newv.add(elem);
		return newv;
	}

	template <class T>
	void vector<T>::remove(int pos) {
		for (int i = pos; i < this->length - 1; i++)
			this->elem[i] = this->elem[i + 1];
		this->length--;
	}

	template <class T>
	T& vector<T>::at(int pos) const {
		if (pos < 0)
			pos = this->length + pos;
		return this->elem[pos];
	}

	template <class T>
	T& vector<T>::operator[](int pos) const {
		return this->at(pos);
	}

	template <class T>
	int vector<T>::size() const { return this->length; }

}