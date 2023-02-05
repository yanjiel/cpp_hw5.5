#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<typeinfo>
#include<format>
using namespace std;


int f(double d) { return static_cast <int> (2 * d); }



template<typename T1, typename T2>
class Counter {
public:
	static int count;
	Counter():count(0){}
	Counter(T1(*func)(T2), bool direct_yn) {
		count = 0;
		fun = move(func);
	}

	T1 operator()(T2 arg) const {
		count += 1;
		return (*fun)(forward<T2>(arg));
	}
private:
	T1(*fun) (T2) = NULL;
};

template <typename T1, typename T2>
int Counter<T1, T2>::count = 0;

template<typename T1, typename T2>
class Counter2 {
public:
	Counter2() {}
	Counter2(T1(*func)(T2), bool direct_yn = false) {
		fun = func;
	}

	T1 operator()(T2 arg) const {
		return (*fun)(forward<T2>(arg));
	}
private:
	T1(*fun) (T2) = NULL;
};


int main() {

	Counter cf(f,true);
	cf(1.3); cf(2.4);
	cout << format("f was called {} times\n", cf.count);

	Counter cf(f, false);
	cf(1.3); cf(2.4);
	//cout << format("f was called {} times\n", cf.count);////should throw error
}