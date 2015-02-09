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

#define MAX_RATING 5
#define MIN_RATING 1

using std::ifstream;
using std::ostream;

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
}

void Record::set_rating(int rating_)
{
    if ( rating_ < MIN_RATING || rating_ > MAX_RATING )
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
