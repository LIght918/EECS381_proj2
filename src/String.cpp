//
//  String.cpp
//  EECS381_proj2
//
//  Created by Charlie OConor on 1/31/15.
//  Copyright (c) 2015 Charlie OConor. All rights reserved.
//

#include "String.h"
#include <stdlib.h>
#include <string.h>


char String::a_null_byte = '\0';	// to hold a null byte for empty string representation

/* Variables for monitoring functions - not part of a normal implementation. */
/* But used here for demonstration and testing purposes. */
int String::number = 0;				// counts number of String objects in existence
int String::total_allocation = 0;	// counts total amount of memory allocated
bool String::messages_wanted = false ;	// whether to output constructor/destructor/operator= messages, initially false

String::~String() noexcept
{
    if( num_elt > 0 )
        delete [] cstr;
}

String::String(const String& original)
{
    String( original.c_str() );
}

String::String( const char* cstr_ )
{
    num_elt = static_cast<int>( strlen( cstr_ ) );

    if ( num_elt > 0 )
    {
        allocation = num_elt + 1;
        total_allocation += allocation;
        
        cstr = new char( allocation );
        strcpy( cstr , cstr_ );
    }
    else
    {
        cstr = &a_null_byte;
        allocation = 0;
    }
    
    number++;
}

String::String(String&& original) noexcept
{
    /* keep a copy of the data */
    int num_elt_ = original.num_elt;
    int allocation_ = original.allocation;
    char* cstr_ = original.cstr;
    
    /* set the original to defaul values */
    original.num_elt = 0;
    original.allocation = 0;
    original.cstr = &a_null_byte;
    
    /* init the new string */
    num_elt = num_elt_;
    allocation = allocation_;
    cstr = cstr_;
}


String& String::operator= (const String& rhs)
{
    num_elt = rhs.num_elt;
    allocation = rhs.allocation;
    
    if ( num_elt > 0 )
    {
        cstr = new char( allocation );
        strcpy( cstr , rhs.cstr );
    }
    else
    {
        cstr = &a_null_byte;
    }
    
    return *this;
}

String& String::operator= (const char* rhs)
{
    num_elt = static_cast<int>( strlen( rhs ) );
    
    if ( num_elt > 0 )
    {
        allocation = num_elt + 1;
        total_allocation += allocation;
        
        cstr = new char( allocation );
        strcpy( cstr , rhs );
    }
    else
    {
        cstr = &a_null_byte;
        allocation = 0;
    }
    
    return *this;
}

String& String::operator= (String&& rhs) noexcept
{
    /* keep a copy of the data */
    int num_elt_ = rhs.num_elt;
    int allocation_ = rhs.allocation;
    char* cstr_ = rhs.cstr;
    
    /* set the original to defaul values */
    rhs.num_elt = 0;
    rhs.allocation = 0;
    rhs.cstr = &a_null_byte;
    
    /* init the new string */
    num_elt = num_elt_;
    allocation = allocation_;
    cstr = cstr_;
    
    return *this;
}

/* combine these functions */
char& String::operator[] (int i)
{
    if ( i < 0  || i >= num_elt )
    {
        throw String_exception( "Out of Bounds Exception\n" );
    }
    
    return cstr[ i ];
}

const char& String::operator[] (int i) const
{
    if ( i < 0  || i >= num_elt )
    {
        throw String_exception( "Out of Bounds Exception\n" );
    }
    
    return cstr[ i ];
}

String String::substring(int i, int len) const
{
    check_bounds( i, len );
    
    char sub_string[ len + 1 ];
    memcpy( sub_string, cstr + i , len );
    sub_string[ len ] = '\0';
    
    return String( sub_string );
}

void String::clear()
{
    if ( num_elt > 0 )
        delete [] cstr;
    
    num_elt = 0;
    allocation = 0;
    cstr = &a_null_byte;
}

void String::remove(int i, int len)
{
    check_bounds( i, len );
    
}


void String::check_bounds( int i, int len ) const
{
    if ( i < 0  || i + len >= num_elt )
        throw String_exception( "Out of Bounds Exception\n" );
}

