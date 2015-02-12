//
//  Record.cpp
//  EECS381_proj2
//
//  Created by Charlie OConor on 1/31/15.
//  Copyright (c) 2015 Charlie OConor. All rights reserved.
//

#include "Record.h"
#include "Utility.h"
#include "String.h"
#include <iostream>
#include <fstream>

static const int Max_Rating =  5;
static const int Min_Rating =  1;

using std::ifstream;
using std::ostream;
using std::istream;

static const char* const Invalid_data_message = "Invalid data found in file!";
static const char* const Inval_Title = "Could not read a title!";

int Record::ID_counter = 0 ;
int Record::backup_ID_counter = 0;

static void read_title( istream& is, String& title );

Record::Record(const String& medium_, const String& title_):
            ID( ++ID_counter ),title( title_ ),medium( medium_ ) {}

Record::Record( const String& title_ ):ID(0), title(title_){}

Record::Record( int ID_ ):ID( ID_){}

Record::Record( ifstream& is )
{
    get_white_space( is ); 
    if ( is.eof() )
    {
        throw Error( Invalid_data_message );
    }
    
    try {
        is >> ID >> medium >> rating;
        
        if ( !is.good() )
        {
            throw Error( Invalid_data_message );
        }
        
        if ( ID > ID_counter )
        {
            ID_counter = ID;
        }
        
        read_title( is, title );
        if ( !is.good() )
        {
            throw Error( Invalid_data_message );
        }
    }
    catch ( ... )
    {
        throw Error( Invalid_data_message );
    }
}

static void read_title( istream& is, String& title )
{
    title.clear();
    char c;
    bool last_was_space = true;
    
    while( is.peek() != '\n' && is.good() )
    {
        if ( isspace( c = is.get() ) )
        {
            if ( !last_was_space )
            {
                title += c;
            }
            
            last_was_space = true;
        }
        else
        {
            last_was_space = false;
            title += c;
        }
    }
    
    
    
    if ( title.size() <= 0  )
    {
        throw Error( Inval_Title );
    }
    
    
    if ( isspace( title[ title.size() - 1 ] ) )
    {
        title.remove( title.size() - 1 , 1 );
    }
}

void Record::set_rating(int rating_)
{
    if ( rating_ < Min_Rating || rating_ >  Max_Rating )
    {
        throw Error( "Rating is out of range!" );
    }
    rating = rating_;
}

void Record::save(std::ostream& os) const
{
    os << ID << ' ' << medium << ' ' << rating << ' ' << title << '\n';
}

ostream& operator<< ( ostream& os, const Record& record)
{
    os << record.ID << ": " << record.medium ;
    
    if ( record.rating == 0 )
        os << " u ";
    else
        os << " " << record.rating << " ";
    
    os << record.title << "\n";
    
    return os;
}
