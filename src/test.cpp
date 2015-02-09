
#include "String.h"
#include <iostream>
using namespace std;

void print_info(const String& s);

// this function outputs the number and memory usage of all strings
void print_String_info();

void test_fn1();
String test_fn2();
String test_fn3(String s);


int main()
{
	String::set_messages_wanted(true);
	{
    cout << "\nDemonstrate call and return by value" << endl;
    String a("initial a"), b("initial b"), c("initial c");
	cout << "Call a function with a call-by-value argument that returns that same variable" << endl;
	b = test_fn3(a);
	/*cout << "function call result: " << b << endl;
    cout << "Call the same function with an argument of a + b" << endl;
    c = test_fn3(a + b);
    cout << "function call result: " << c << endl;
    cout << "a:" << a << " b:" << b << " c:" << c << endl;*/
    print_String_info();
    }
	return 0; 
}

void print_info(const String& s)
{
    cout << "String contains \""  << s.c_str() << "\", length is " << s.size() << ", allocation is " << s.get_allocation() << endl;
}

void print_String_info()
{
	cout << String::get_number() << " Strings using " << String::get_total_allocation() << " bytes"  << endl;
}
void test_fn1()
{
	cout << "in test_fn1:" << endl;
	String s1("Good morning!");
	String s2("Good night!");
	cout << s1 << s2 << endl;
	// check number of strings now existing
	print_String_info();
}

/*
In addition to eliding constructor calls in initialization, almost all compilers will also perform the Return Value Optimization (RVO)
to eliminate the copy or move construction of the returned value;
instead of building the return value in a local variable and then copying it out into the unnamed returned
variable in the the caller's stack space, the compiler builds the local variable in that same
returned variable space, thereby saving a copy or move construction. This happens in the function below.
 */

String test_fn2()
{
    cout << "in test_fn2" << endl;
    String s("xxx");
    cout << "test_fn2 returning: " << s << endl;
    return s;
}

/*
But in the type of function shown below, where the returned value is the same variable as the input parameter,
The RVO cannot be done! The variable s can't be placed both in the local stack space of the parameter and in the caller's stack space 
for the returned value. This forces the compiler to call a copy or move constructor to get the returned value into 
the returned variable space.
*/

String test_fn3(String s)
{
	cout << "test_fn3 got:" << s << endl;
	// check number of strings now existing
	print_String_info();
    s = "!!!";
	cout << "test_fn3 returning: " << s << endl;
	print_String_info();
	return s;
}

