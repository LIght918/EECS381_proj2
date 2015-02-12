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
static const char* const Record_Coll = "Record is already a member in the collection!";
static const char* const Record_Not_Coll = "Record is not a member in the collection!";
static const char* const Inval_Title = "Could not read a title!";

static void read_title( istream& is, String& title );

Collection::Collection(const String& name_): name(name_) {}

Collection::Collection( ifstream& is, const Ordered_list<Record*, Less_than_ptr<Record*>>& library )
{
    int num ;
    String title;

    get_white_space( is ); 
    if ( !is.good() || is.eof() )
    {
        throw Error( Invalid_data_message );
    }
    
    is >> name >> num ;
    
    if( !is.good() || num < 0 )
        throw Error( Invalid_data_message );
    
    getline( is, title );
    is.get();
    
    for ( int i = 0; i < num ; ++i )
    {
        try
        {
            read_title( is, title );
            is.get();
        }
        catch ( ... )
        {
            throw Error( Invalid_data_message );
        }
        
        Record prode( title );
        
        auto it = library.find( &prode );
        
        if ( it == library.end() || !is )
            throw Error( Invalid_data_message );
        else
            lib.insert( *it );
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

void Collection::add_member(Record* record_ptr)
{
    if ( lib.find( record_ptr ) != lib.end() )
        throw Error( Record_Coll );
    
    lib.insert( record_ptr );
}

bool Collection::is_member_present(Record* record_ptr) const
{
    return lib.find( record_ptr ) != lib.end();
}

void Collection::remove_member(Record* record_ptr)
{
    auto it = lib.find( record_ptr );
    
    if ( it == lib.end() )
        throw Error( Record_Not_Coll );
    
    lib.erase( it );
}

void Collection::save( ostream& os) const
{
    os << name << " " << lib.size() << "\n";
    
    for ( auto it = lib.begin(); it != lib.end() ; ++it )
    {
        os << (*it)->get_title() << "\n" ;
    }
}

ostream& operator<< (ostream& os, const Collection& collection)
{
    os << "Collection " << collection.name << " contains:" ;
    if ( collection.empty() )
    {
        cout << " None\n";
    }
    else
    {
        cout << "\n";
        for ( auto it = collection.lib.begin(); it != collection.lib.end() ; ++it )
        {
            os << (**it) ;
        }
    }
    return os;
}

