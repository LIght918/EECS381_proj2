

#include "String.h"
#include <iostream>
using namespace std;

void print_info(const String& s);

int main()
{
        String target;
        print_info(target);
        target = target + "abc";
        print_info(target);
        
        
	return 0; 
}

void print_info(const String& s)
{
    cout << "String contains \""  << s.c_str() << "\", length is " << s.size() << ", allocation is " << s.get_allocation() << endl;
}

