//
//  String.cpp
//  EECS381_proj2
//
//  Created by Charlie OConor on 1/31/15.
//  Copyright (c) 2015 Charlie OConor. All rights reserved.
//

#include "String.h"
#include <stdlib.h> // memcpy and memmove
#include <string.h> // strcpy, strlen and strcmp
#include <algorithm> // for std::swap
#include <iostream>

using std::ostream;
using std::istream;

// init static member variables
char String::a_null_byte = '\0';	// to hold a null byte for empty string representation
int  String::number = 0;				// counts number of String objects in existence
int  String::total_allocation = 0;	// counts total amount of memory allocated
bool String::messages_wanted = false;	// whether to output constructor/destructor/operator= messages, initially false

String::~String() noexcept
{
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
    allocation = original.allocation;
    num_elt = original.num_elt;
    
    if ( allocation != 0 )
    {
        cstr = new char[ allocation ];
        strcpy( cstr, original.cstr ); 
    }
    else
    {
        cstr = &a_null_byte; 
    }
}

String::String( const char* cstr_ )
{
    num_elt = static_cast<int>( strlen( cstr_ ) );

    if ( num_elt > 0 )
    {
        allocation = num_elt + 1;
        
        total_allocation += allocation;
        cstr = new char[ allocation ];
        
        strcpy( cstr , cstr_ );
    }
    else
    {
        cstr = &a_null_byte;
        allocation = 0;
    }
    
    number++;
}

String& String::operator= (const String& rhs)
{
    // use the assingment operator with c_str
    *this = rhs.cstr;
    
    return *this;
}

String& String::operator= (const char* rhs)
{
    num_elt = static_cast<int>( strlen( rhs ) );
    
    if ( num_elt > 0 )
    {
        allocation = num_elt + 1;
        total_allocation += allocation;
        
        cstr = new char[ allocation ];
        strcpy( cstr , rhs );
    }
    else
    {
        cstr = &a_null_byte;
        allocation = 0;
    }
    
    return *this;
}

String::String(String&& original) noexcept
{
    swap( original );
}

String& String::operator= (String&& rhs) noexcept
{
    if ( this != &rhs )
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
    check_bounds( i, len );
    
    char* sub_string = new char[ len + 1 ];
    memcpy( sub_string, cstr + i , len );
    sub_string[ len ] = '\0';
    
    // need to remove
    String new_string( sub_string );
    
    delete [] sub_string;
    
    return new_string;
}

void String::remove(int i, int len)
{
    check_bounds( i, len );
    
    // + 1 to get the null term
    memmove( cstr + i , cstr + i + len,  num_elt - i - len + 1 );
    
    // keep track of the size
    num_elt -= len;
}

char& String::operator[] (int i)
{
    check_bounds( i, 0 );
    
    return cstr[ i ];
}

const char& String::operator[] (int i) const
{
    check_bounds( i, 0 );
    
    return cstr[ i ];
}

// Checks to see if i and len are with in the bounds
// throws an "Out of Bounds" String Exception
// use len = 0 to just check i
inline void String::check_bounds( int i, int len ) const
{
    if ( i < 0  || i + len >= num_elt || len < 0 )
        throw String_exception( "Out of Bounds Exception\n" );
}

void String::insert_before(int i, const String& src)
{
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


String& String::operator += (const String& rhs)
{
    *this += rhs.cstr;
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
    allocation = new_alloc;
}


String operator+ (const String& lhs, const String& rhs)
{
    char* temp_str = new char[ lhs.size() + rhs.size() ];
    
    // load in the lhs string excluding the null term
    memcpy( temp_str, lhs.c_str(), lhs.size() );
    
    // load in the rhs with the null bit after the lhs
    memcpy( temp_str + lhs.size(), rhs.c_str(), lhs.size() + 1 );
    
    String new_string( temp_str );
    delete [] temp_str;
    
    return new_string;
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
