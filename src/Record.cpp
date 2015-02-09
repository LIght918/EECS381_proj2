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

static const char* const Invalid_data_message = "Invalid data found in file!";

int Record::ID_counter = 0 ;
int Record::backup_ID_counter = 0;

Record::Record(const String& medium_, const String& title_):
            ID( ++ID_counter ),title( title_ ),medium( medium_ ) {}

Record::Record( const String& title_ ):ID(0), title(title_){}

Record::Record( int ID_ ):ID(0){}

Record::Record( ifstream& is )
{
    is >> ID >> medium >> rating;
    read_title( is, title );
    if ( !is.good() )
    {
        // TODO check this works
        throw Error( Invalid_data_message );
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
    
    if ( record.rating )
        os << " u ";
    else
        os << " " << record.rating << " ";
    
    os << record.title << "\n";
    
    return os;
}
