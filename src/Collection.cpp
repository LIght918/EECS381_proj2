//
//  Collection.cpp
//  EECS381_proj2
//
//  Created by Charlie OConor on 1/31/15.
//  Copyright (c) 2015 Charlie OConor. All rights reserved.
//

#include "Collection.h"
#include "Utility.h"
#include "String.h"
#include "Record.h"
#include <iostream>
#include <fstream>

using std::ifstream;
using std::ostream;

static const char* const Invalid_data_message = "Invalid data found in file!";

Collection::Collection(const String& name_): name(name_) {}

Collection::Collection( ifstream& is, const Ordered_list<Record*, Less_than_ptr<Record*>>& library )
{
    int num = -1;
    String title;
    
    is >> name >> num ;
    
    if( !is || num < 0 )
        throw Error( Invalid_data_message );
    
    for ( int i = 0; i < num ; ++i )
    {
        read_title( is, title );
        Record prode( title );
        
        auto it = library.find( &prode );
        
        if ( it == library.end() || !is )
            throw Error( Invalid_data_message );
        else
            lib.insert( *it );
    }
}


void Collection::add_member(Record* record_ptr)
{
    lib.insert( record_ptr );
}

bool Collection::is_member_present(Record* record_ptr) const
{
    return lib.find(record_ptr ) == lib.end();
}

void Collection::remove_member(Record* record_ptr)
{
    auto it = lib.find( record_ptr );
    
    lib.erase( it );
}

void Collection::save( ostream& os) const
{
    os << *this;
}

ostream& operator<< (ostream& os, const Collection& collection)
{
    os << collection.name << " " << collection.lib.size() << "\n";
    
    for ( auto it = collection.lib.begin(); it != collection.lib.end() ; ++it )
    {
        os << (*it)->get_title() << "\n" ;
    }
    
    return os;
}

