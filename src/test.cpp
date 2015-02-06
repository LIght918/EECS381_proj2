

#include "String.h"
#include <iostream>
using namespace std;

void print_info(const String& s);

int main()
{
	String s; 
	print_info( s ); 
	
	String s1( "test");
	print_info( s1 ); 
	
	{
		String s2( s1 ); 
		print_info( s2 );
	}
	
	cout << s1 << endl; 
	
	
	String s3{ move( s1 ) };
	print_info( s3 ); 
	
	return 0; 
}

void print_info(const String& s)
{
    cout << "String contains \""  << s.c_str() << "\", length is " << s.size() << ", allocation is " << s.get_allocation() << endl;
}

