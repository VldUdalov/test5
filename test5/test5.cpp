// test5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <functional>
#include <Windows.h>
#include <thread>
#include<future>
#include<fstream>
#include<memory>
#include <signal.h>

using namespace std;
struct Arg
{
	int i = 1;
	int  get()&& { return i+1; } // call to this overload is rvalue
	int& get() & { return i; } // call to this overload is lvalue
};

extern "C" int cfun(int&& x)
{
	x++;
	return 2*x;
}

struct MyBind {
	typedef int result_type;
	//int operator()(int a, int b) const { return a + b; }
};

namespace std {
	template<>
	struct is_bind_expression<MyBind> : public true_type {};
}

int f111111(int n1, int n2)
{
	return n1 + n2;
}
//atomic<int> value = 0;
volatile int value = 0;
int loop(bool id)
{
	cout << "Started " << id << endl;
	for (int i = 0; i < 1000; i++)
	{
		Sleep(5);
		if (id) ++value;
		else --value;
	}
	//raise(SIGTERM);
	return value;
}


void memento(int)
{
	int a = 0;
	MessageBoxA(NULL, "Memento mori", "POSIX Signal", NULL);
	return ;
}
void fall()
{
	int* p = 0x00000000;
	*p = 13;
}
void posix_death_signal(int signum)
{
	memento(0);
	signal(signum, SIG_DFL);
	exit(3);
}

struct newdel
{
	~newdel()
{
	 cout << "destruct";

}

};

int main()
{
	int Aff = 0;

	int *nn = new int[10];
	delete nn;

	std::mutex m;
	CRITICAL_SECTION cs;
	InitializeCriticalSection(&cs);
	//signal(SIGSEGV, posix_death_signal);
	//fall();
	//signal(SIGTERM, memento);

	
	//ofstream out("out.txt");
	//streambuf *coutbuf = std::cout.rdbuf(); //save old buf
//	cerr.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

	//vector<int> v{ 1,2,3,4,5,6 };
	//auto is=is_bind_expression<int&&>::value;
	//Arg a;
	//auto fun = mem_fn(Arg::get);
	//int res = 0;
	//int re = 3;
	//thread tr1(loop, true);
	//thread tr2(loop, false);
	auto ass = std::async(std::launch::async, loop, true);
	//tr1.join();
	//tr2.join();
	cout << "waiting " << endl;
	Sleep(5000);
	cout << ass.get();
	//auto binded = bind(cfun,std::placeholders::_1);
	//cerr << "hello";
	//cout << typeid(cfun).name()<<endl;
	
	
	//res = cfun(move(re));
	//res = binded(4);
	//cout << typeid(binded).name();
//	int aaa=Arg().get();
//	for (char i:v )
	//{
	//	cout << i;
	//}
	
    return 0;
}

