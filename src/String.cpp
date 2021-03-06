//
//  String.cpp
//  EECS381_proj2
//
//  Created by Charlie OConor on 1/31/15.
//  Copyright (c) 2015 Charlie OConor. All rights reserved.
//

#include "String.h"
#include <cstdlib> // memcpy and memmove
#include <cstring> // strcpy, strlen and strcmp
#include <algorithm> // for std::swap
#include <iostream>
#include <cassert>

using std::ostream;
using std::istream;
using std::cout;

//global c_str for error messages
static const char* const Subscript_range = "Subscript out of range";
static const char* const Substring_bounds = "Substring bounds invalid";
static const char* const Remove_bounds = "Remove bounds invalid";
static const char* const Insert_range  = "Insertion point out of range";

// init static member variables
char String::a_null_byte = '\0';	// to hold a null byte for empty string representation
int  String::number = 0;				// counts number of String objects in existence
int  String::total_allocation = 0;	// counts total amount of memory allocated
bool String::messages_wanted = false;	// whether to output constructor/destructor/operator= messages, initially false

String::~String() noexcept
{
    if ( messages_wanted )
        cout << "Dtor: \"" << cstr << "\"\n";
    clear();
    number--;
}
    

void String::clear()
{
    if ( allocation > 0 )
    {
        total_allocation -= allocation;
        allocation = 0;
        num_elt = 0;
        delete [] cstr;
        cstr = &a_null_byte;
    }
}
    
String::String(const String& original)
{
    if ( messages_wanted )
        cout << "Copy ctor: \"" << original << "\"\n";
    
    num_elt = original.num_elt;
    
    // give min allocation
    alloc_copy( original.cstr, original.num_elt );
    
    number++;
}
    
String::String( const char* cstr_ )
{
    if ( messages_wanted )
        cout << "Ctor: \"" << cstr_ << "\"\n";
    
    num_elt = strlen( cstr_ );
    
    alloc_copy( cstr_, num_elt );
    number++;
}
    
String& String::operator= (const String& rhs)
{
    if ( messages_wanted )
        cout << "Copy assign from String:  \"" << rhs << "\"\n";
    
    String temp( rhs );
    swap( temp );
    
    return *this;
}
    
String& String::operator= (const char* rhs)
{
    if ( messages_wanted )
        cout << "Assign from C-string:  \"" << rhs << "\"\n";
    
    String temp( rhs );
    swap(  temp );
    
    return *this;
}
    
void String::alloc_copy( const char* cstr_, int size_ )
{
    if ( size_ > 0 )
    {
        allocation = size_ + 1;
        total_allocation += allocation;
        cstr = new char[ allocation ];
        strcpy( cstr, cstr_ );
    }
    else
    {
        allocation = 0;
        cstr = &a_null_byte;
    }
}
    
String::String(String&& original) noexcept
{
    allocation = original.allocation;
    num_elt = original.num_elt;
    cstr = original.cstr;
     
    original.cstr = &a_null_byte;
    original.allocation = 0;
    original.num_elt = 0;
    
    number++;
    
    if ( messages_wanted )
        cout << "Move ctor: \"" << cstr << "\"\n";
}
    
    String& String::operator= (String&& rhs) noexcept
{
    if ( messages_wanted )
        cout << "Move assign from String:  \"" << rhs << "\"\n";
    
    swap( rhs );
    
    return *this;
}
    
    void String::swap(String& other) noexcept
{
    // swap all the member variables
    std::swap( num_elt, other.num_elt );
    std::swap( allocation, other.allocation );
    std::swap( cstr, other.cstr );
}
    
    String String::substring(int i, int len) const
{
    check_bounds( i, len, Substring_bounds );
    
    char* sub_string = new char[ len + 1 ];
    memcpy( sub_string, cstr + i , len );
    sub_string[ len ] = '\0';
    
    String new_string( sub_string );
    
    delete[] sub_string;
    return new_string;
}
    
    void String::remove(int i, int len)
{
    check_bounds( i, len, Remove_bounds );
    
    // + 1 to get the null term
    memmove( cstr + i , cstr + i + len,  num_elt - i - len + 1 );
    
    // keep track of the size
    num_elt -= len;
}
    
char& String::operator[] (int i)
{
    check_bounds( i, 0, Subscript_range );
    
    return cstr[ i ];
}
    
const char& String::operator[] (int i) const
{
    check_bounds( i, 0, Subscript_range );
    
    return cstr[ i ];
}
    
    // Checks to see if i and len are with in the bounds
    // throws an "Out of Bounds" String Exception
// use len = 0 to just check i
inline void String::check_bounds( int i, int len, const char* message ) const
{
    if ( i < 0  || i + len > num_elt || i >= num_elt || len < 0 )
    {
        throw String_exception( message );
    }
}
    
    
void String::insert_before(int i, const String& src)
{

    if ( i < 0  || i > num_elt  )
    {
        throw String_exception( Insert_range );
    }

    if ( allocation < num_elt + src.size() + 1 )
        grow( src.size() );
    
    // make space for the insert
    memmove( cstr + src.size() + i , cstr + i, num_elt - i + 1);
    // move the instered string in
    memcpy( cstr + i , src.cstr , src.num_elt );
    
    num_elt += src.num_elt;
}
    
    String& String::operator += (char rhs)
{
    if ( allocation < num_elt + 2 )
        grow( 1 );
    
    cstr[ num_elt++ ] = rhs;
    cstr[ num_elt ] = '\0';
    
    return *this;
}
    
    String& String::operator += (const String& rhs)
{
    *this += rhs.cstr;
    return *this;
}
    
    String& String::operator += (const char* rhs)
{
    int rhs_lenght = strlen( rhs );
    
    if ( allocation < num_elt + 1 + rhs_lenght )
        grow( rhs_lenght );
    
    memcpy( cstr + num_elt, rhs, rhs_lenght );
    
    num_elt += rhs_lenght;
    cstr[ num_elt ] = '\0';
    return *this;
}
    
    void String::grow( int n )
{
    int new_alloc = 2 * ( num_elt + n + 1 );
    char* new_array = new char[ new_alloc ];
    
    memcpy(new_array, cstr, num_elt + 1 );
    
    // clean up memory if its allocated
    if ( allocation > 0 )
        delete [] cstr;
    
    cstr = new_array;
    total_allocation += new_alloc - allocation;
    allocation = new_alloc;
}
    
    
    String operator+ (const String& lhs, const String& rhs)
{
    String new_string( lhs );
    
    new_string += rhs;
    
    return std::move( new_string ) ;
}
    
    // compare lhs and rhs strings; constructor will convert a C-string literal to a String.
    // comparison is based on std::strcmp result compared to 0
    bool operator== (const String& lhs, const String& rhs)
{
    return strcmp( lhs.c_str(), rhs.c_str() ) == 0;
}
    
    bool operator!= (const String& lhs, const String& rhs)
{
    return strcmp( lhs.c_str(), rhs.c_str() ) != 0;
}
    
    bool operator< (const String& lhs, const String& rhs)
{
    return strcmp( lhs.c_str(), rhs.c_str() ) < 0 ;
}
    
    bool operator> (const String& lhs, const String& rhs)
{
    return strcmp( lhs.c_str(), rhs.c_str() ) > 0 ;
}
    
    ostream& operator<< (ostream& os, const String& str)
{
    os << str.c_str();
    return os;
}
    
    
    istream& operator>> ( istream& is, String& str)
{
    char c;
    str.clear();
    // read in all the leading whitespace
    while ( isspace( c = is.get() ) && is.good() ) ;
    
    str += c;
    
    while ( !isspace( is.peek() ) )
    {
        // add each char as read
        str += is.get();
    }
    
    return is;
}
    
    
    
    istream& getline( istream& is, String& str)
{
    str.clear();
    
    while( is.peek() != '\n' && is.good() )
    {
        str += is.get();
    }
    return is;
}