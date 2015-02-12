//
//  p2_main.cpp
//  EECS381_proj2
//
//  Created by Charlie OConor on 2/3/15.
//  Copyright (c) 2015 Charlie OConor. All rights reserved.
//

#include "Ordered_list.h"
#include "String.h"
#include "Collection.h"
#include "Record.h"
#include "Utility.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <new> // bad_alloc

using std::bad_alloc;
using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;
using std::istream;

static const char* const Unrecognized = "Unrecognized command!";
static const char* const Dup_Rec = "Library already has a record with this title!";
static const char* const Dup_Member = "Catalog already has a collection with this name!";
static const char* const Member_Coll = "Cannot delete a record that is a member of a collection!";
static const char* const Coll_Not_Empty = "Cannot clear all records unless all collections are empty!";
static const char* const No_Rec_title = "No record with that title!";
static const char* const No_Rec_ID = "No record with that ID!";
static const char* const No_Coll = "No collection with that name!";
static const char* const Inval_int = "Could not read an integer value!";
static const char* const Open_file = "Could not open file!";
static const char* const Invalid_data_message = "Invalid data found in file!";
static const char* const Inval_Title = "Could not read a title!";

struct Less_than_Recrod_ptr {
    bool operator()(const Record* p1, const Record* p2) const {return p1->get_ID() < p2->get_ID();}
};

/*
 *
 *  Function Declarations
 *
 *  top level functions - called from main()
 *
 */

static void find_record_print( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title );

static void add_record( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title, Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID);

static void add_coll( Ordered_list<Collection>& catalog );

static void delete_record( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title, Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID,
                          Ordered_list<Collection>& catalog);

static void delete_collection( Ordered_list<Collection>& catalog );

static void print_collection_main( Ordered_list<Collection>& catalog );

static void print_record( Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID);

static void print_allocation( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title, Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID,
                             Ordered_list<Collection>& catalog);

static void print_catalog(Ordered_list<Collection>& catalog);
static void print_lib( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title );

static void remove_member(  Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID, Ordered_list<Collection>& catalog );
static void add_member(  Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID, Ordered_list<Collection>& catalog );


static void modify_rating( Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID);

static void clear_library( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title, Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID,
                          Ordered_list<Collection>& catalog );

static void clear_all( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title, Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID,
                      Ordered_list<Collection>& catalog);

static void delete_dynamic_mem( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title );

static void load_from_file( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title, Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID,
                           Ordered_list<Collection>& catalog );

static void save_all_to_file( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title, Ordered_list<Collection>& catalog);

static void clear_catalog(Ordered_list<Collection>& catalog);

Ordered_list<Record*, Less_than_Recrod_ptr>::Iterator  get_record_by_id( Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID );
Ordered_list<Record*, Less_than_ptr<Record*>>::Iterator  get_record_by_title( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title );
Ordered_list<Collection>::Iterator get_collection_by_name( Ordered_list<Collection>& catalog );


static char get_command_char( void );

static void read_title( std::istream& is, String& title );

int main( void )
{
    Ordered_list<Collection> catalog;
    Ordered_list<Record*, Less_than_ptr<Record*>> lib_title;
    Ordered_list<Record*, Less_than_Recrod_ptr> lib_ID;
    
    try
    {
        char first_command, second_command;
        
        for ( ; ; )
        {
            try {
                cout << "\nEnter command: ";
                
                first_command  = get_command_char();
                second_command = get_command_char();
                
                //TODO remove this
                //cout << "Command is :" << first_command << second_command << "\n";
                
                switch ( first_command )
                {
                    case 'f':
                        switch ( second_command ) {
                            case 'r':
                                //find record
                                find_record_print( lib_title );
                                break;
                            default:
                                throw Error( Unrecognized );
                                break;
                        }
                        break;
                    case 'p' : /* print */
                        switch ( second_command )
                    {
                        case 'r' :
                            print_record( lib_ID );
                            break;
                        case 'L':
                            print_lib( lib_title );
                            break;
                        case 'C':
                             print_catalog( catalog );
                            
                            break;
                        case 'a': /* allocation */
                            print_allocation(lib_title, lib_ID, catalog);
                            break;
                        case 'c':
                            print_collection_main( catalog );
                            break;
                        default:
                            throw Error( Unrecognized );;
                            break;
                    }
                        break;
                    case 'm': /* modify (rating only) */
                        switch ( second_command )
                    {
                        case 'r':
                            modify_rating( lib_ID );
                            break;
                        default:
                            throw Error( Unrecognized );;
                            break;
                    }
                        break;
                    case 'a' : /* add */
                        switch ( second_command )
                    {
                        case 'r' :
                            add_record( lib_title, lib_ID );
                            break;
                        case 'c':
                            add_coll( catalog );
                            break;
                        case 'm':
                            add_member(lib_ID, catalog);
                            break;
                        default:
                            throw Error( Unrecognized );
                            break;
                    }
                        break;
                    case 'd': /* delete */
                        switch ( second_command )
                    {
                        case 'r' :
                            delete_record(lib_title, lib_ID, catalog);
                            break;
                        case 'c':
                            delete_collection( catalog );
                            break;
                        case 'm':
                            //delete_m
                            remove_member(lib_ID, catalog);
                            break;
                        default:
                            throw Error( Unrecognized );;
                            break;
                    }
                        break;
                    case 'c': /* clear */
                        switch ( second_command )
                    {
                        case 'L':
                            clear_library( lib_title, lib_ID, catalog );
                            break;
                        case 'C':
                            clear_catalog( catalog );
                            break;
                        case 'A':
                            clear_all(lib_title, lib_ID, catalog );
                            break;
                        default:
                            throw Error( Unrecognized );;
                            break;
                    }
                        break;
                    case 's': /* save */
                        switch ( second_command ) {
                            case 'A':
                                save_all_to_file( lib_title, catalog );
                                break;
                            default:
                                throw Error( Unrecognized );;
                                break;
                        }
                        break;
                    case 'r': /* restore */
                        switch ( second_command ) {
                            case 'A':
                                load_from_file( lib_title, lib_ID, catalog );
                                break;
                            default:
                                throw Error( Unrecognized );;
                                break;
                        }
                        break;
                    case 'q':
                        switch ( second_command )
                    {
                        case 'q':
                            // clean up memory
                            delete_dynamic_mem( lib_title );
                            cout << "All data deleted\nDone\n";
                            return 0;
                            break;
                        default:
                            throw Error( Unrecognized );
                            break;
                    }
                    default:
                        throw Error( Unrecognized );
                        break;
                }
            }
            catch ( Error& ex )
            {
                String temp;
                cout << ex.msg << "\n";
                cin.clear();
                getline( cin, temp );
            }
        }
    }
    catch ( bad_alloc& ex )
    {
        cout << "Bad allocation\n";
        delete_dynamic_mem( lib_title );
        throw;
    }
    catch( String_exception& ex )
    {
        cout << ex.msg << "\n";
        delete_dynamic_mem( lib_title );
    }
    catch( ... )
    {
        cout << "Unknown Error" << "\n";
        delete_dynamic_mem( lib_title );
    }
    
    return 0;
}


static void find_record_print( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title )
{
    auto it = get_record_by_title( lib_title );
    cout << **it;
}

static void add_record( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title, Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID)
{
    String medium, title;
    
    cin >> medium;
    
    read_title( cin , title ) ;
    
    Record::save_ID_counter();
    Record* new_rec = new Record( medium, title );
    
    if ( lib_title.find( new_rec ) != lib_title.end() )
    {
        delete new_rec;
        Record::restore_ID_counter();
        throw Error( Dup_Rec );
    }
    
    lib_ID.insert( new_rec );
    lib_title.insert( new_rec );
    
    assert( !lib_ID.empty() );
    assert( !lib_title.empty() );
    
    cout << "Record "<< new_rec->get_ID() << " added\n";
}

static void add_coll( Ordered_list<Collection>& catalog )
{
    String name;
    cin >> name;
    
    Collection new_coll( name );
    
    if ( catalog.find( new_coll ) != catalog.end() )
    {
        throw Error( Dup_Member );
    }
    
    catalog.insert( new_coll );
    
    cout << "Collection " << name <<  " added\n";
}

static void delete_record( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title, Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID,
                          Ordered_list<Collection>& catalog)
{
    auto it_title = get_record_by_title( lib_title );
    Record* rec = *it_title; 

    for ( auto it : catalog )
    {
        if( it.is_member_present( *it_title ) )
        {
            throw Error( Member_Coll );
        }
    }
    
    Record prode_ID( (*it_title)->get_ID() );
    auto it_ID = lib_ID.find( &prode_ID );
    
    cout << "Record "<< (*it_ID)->get_ID() << " " << (*it_ID)->get_title() << " deleted\n";

    lib_ID.erase( it_ID );
    lib_title.erase( it_title );
    
    
    
    //clean up mem
    delete rec;
}

static void delete_collection( Ordered_list<Collection>& catalog )
{
    auto it = get_collection_by_name( catalog );
    
    cout << "Collection " << it->get_name() <<  " deleted\n" ;
    catalog.erase( it );
}

static void print_collection_main( Ordered_list<Collection>& catalog )
{
    auto it = get_collection_by_name( catalog );
    
    cout << *it ;
}

static void print_record( Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID)
{ 
    auto it = get_record_by_id( lib_ID );
    
    cout << **it;
}

static void print_lib( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title )
{
    if ( lib_title.empty() )
    {
        cout << "Library is empty\n"; 
    }
    else
    {
        cout << "Library contains " << lib_title.size() << " records:\n";
        
        for (auto it = lib_title.begin(); it != lib_title.end(); ++it )
        {
            cout << **it ;
        }
    }

}

static void print_catalog(Ordered_list<Collection>& catalog)
{
    if ( catalog.empty() )
    {
        cout << "Catalog is empty\n";
    }
    else
    {
        cout << "Catalog contains " <<  catalog.size() << " collections:\n";
        for ( auto it : catalog )
        {
            cout << it;
        }
    }
}

static void print_allocation( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title, Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID,
                             Ordered_list<Collection>& catalog)
{
    cout << "Memory allocations:\n"
        "Records: " << lib_ID.size() << "\n"
        "Collections: " << catalog.size() << "\n"
        "Lists: "  << g_Ordered_list_count << "\n"
        "List Nodes: "  << g_Ordered_list_Node_count << "\n"
        "Strings: "     << String::get_number() << " with " << String::get_total_allocation() << " bytes total\n";
}

static void remove_member(  Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID, Ordered_list<Collection>& catalog )
{
    
    auto it_c = get_collection_by_name( catalog );
    auto it_r = get_record_by_id( lib_ID );
    
    it_c->remove_member( *it_r );
    cout << "Member "<< (*it_r)->get_ID() << " " << (*it_r)->get_title() << " deleted\n";
}


static void add_member(  Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID, Ordered_list<Collection>& catalog )
{
    auto it_c = get_collection_by_name( catalog );
    auto it_r = get_record_by_id( lib_ID );
    
    it_c->add_member( *it_r );
    cout << "Member "<< (*it_r)->get_ID() << " " << (*it_r)->get_title() << " added\n";
}


static void modify_rating( Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID)
{
    auto it = get_record_by_id( lib_ID );
    
    int new_rating;
    cin >> new_rating;
    if ( !cin )
    {
        throw Error( Inval_int );
    }
    
    (*it)->set_rating( new_rating );
    cout << "Rating for record " << (*it)->get_ID() <<  " changed to " << new_rating << "\n";
}

static void clear_library( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title, Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID,
                          Ordered_list<Collection>& catalog )
{
    for ( auto it = catalog.begin(); it != catalog.end(); ++it )
    {
        if ( !it->empty() )
        {
            throw Error( Coll_Not_Empty );
        }
    }
    
    Record::reset_ID_counter();
    delete_dynamic_mem( lib_title );
    
    lib_ID.clear();
    lib_title.clear();
    cout << "All records deleted\n";
}

static void clear_all( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title, Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID,
                      Ordered_list<Collection>& catalog)
{
    catalog.clear();
    delete_dynamic_mem( lib_title );
    lib_ID.clear();
    lib_title.clear();
    cout << "All data deleted\n";
}

static void delete_dynamic_mem( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title )
{
    for ( auto it : lib_title )
    {
        delete it;
    }
}

static void load_from_file( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title, Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID,
                           Ordered_list<Collection>& catalog )
{
    String file_name;
    
    cin >> file_name;
    ifstream is( file_name.c_str() );
    
    if( !is.is_open() )
    {
        throw Error( Open_file );
    }
    
    Record::save_ID_counter();
    Record::reset_ID_counter();
    
    Ordered_list< Record*, Less_than_ptr<Record*> > lib_title_temp ( move( lib_title ) );
    Ordered_list< Record*, Less_than_Recrod_ptr > lib_ID_temp( move( lib_ID ) );
    Ordered_list< Collection > catalog_temp( move( catalog ) );
    
    try
    {
        int num;
        is >> num;
        
        if ( !is )
        {
            throw Error( Invalid_data_message );
        }
        
        for ( int i = 0; i < num ; ++i )
        {
            Record* new_rec = new Record( is );
            lib_title.insert( new_rec );
            lib_ID.insert( new_rec );
        }
        
        is >> num;
        
        if ( !is )
        {
            throw Error( Invalid_data_message );
        }
        
        for ( int i = 0; i < num ; ++i )
        {
            Collection new_coll( is, lib_title );
            catalog.insert( new_coll );
        }
        is.close();
    }
    catch ( Error& er )
    {
        Record::restore_ID_counter();
        
        delete_dynamic_mem( lib_title );
        
        lib_title = move( lib_title_temp );
        lib_ID = move( lib_ID_temp );
        catalog = move( catalog_temp );
        
        
        is.close();
        throw;
    }
    
    delete_dynamic_mem( lib_title_temp );
    cout << "Data loaded\n";
}

static void save_all_to_file( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title, Ordered_list<Collection>& catalog)
{
    String file_name;
    cin >> file_name;
    ofstream os( file_name.c_str() );
    
    if( !os.is_open() )
    {
        throw Error( Open_file );
    }
    
    try
    {
        os << lib_title.size() << "\n";
        
        for ( auto it : lib_title )
        {
            it->save( os );
        }
        
        os << catalog.size() << "\n" ;
        
        for ( auto it : catalog )
        {
            it.save( os ) ;
        }
    }
    catch ( ... )
    {
        os.close();
        throw;
    }
    
    os.close();
    cout << "Data saved\n";
}


Ordered_list<Record*, Less_than_Recrod_ptr>::Iterator  get_record_by_id( Ordered_list<Record*,Less_than_Recrod_ptr>& lib_ID )
{
    int ID;
    cin >> ID;
    
    if ( !cin )
        throw Error( Inval_int );
    
    Record probe( ID );
    auto it = lib_ID.find( &probe );
    
    if ( it == lib_ID.end() )
    {
        throw Error( No_Rec_ID );
    }
    
    return it;
}

Ordered_list<Record*, Less_than_ptr<Record*>>::Iterator  get_record_by_title( Ordered_list<Record*, Less_than_ptr<Record*>>& lib_title )
{
    String title;
    
    read_title( cin, title );
    
    Record probe( title );
    auto it = lib_title.find( &probe );
    
    if ( it == lib_title.end() )
        throw Error( No_Rec_title );
    
    return it;
}

Ordered_list<Collection>::Iterator get_collection_by_name( Ordered_list<Collection>& catalog )
{
    String name;
    
    cin >> name;
    Collection probe( name );
    
    auto it = catalog.find( probe );
    
    if ( it == catalog.end() )
    {
        throw Error( No_Coll );
    }
    return it;
}



static void clear_catalog(Ordered_list<Collection>& catalog)
{
    catalog.clear();
    cout << "All collections deleted\n";
}

static char get_command_char( void )
{
    int c;
    
    // load chars until we get one that it not white space
    while ( ( ( c = cin.get() ) > 0 ) && isspace( c ) ) ;
    
    
    return c;
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
