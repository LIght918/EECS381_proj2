//
//  p2_main.cpp
//  EECS381_proj2
//
//  Created by Charlie OConor on 2/3/15.
//  Copyright (c) 2015 Charlie OConor. All rights reserved.
//

#include "Ordered_list.h"
#include "String.h"
#include <new> // bad_alloc

using std::bad_alloc;

int main( void )
{
    try {

    for (; ; )
    {
        
    }
    } catch ( bad_alloc& ex )
    {
        cout << "Bad allocation\n";
        throw;
    }
    catch( String_exception& ex )
    {
        cout << ex.msg << endl;
        //TODO call quit
    }
    catch( ... )
    {
        cout << "Unknown Error" << endl;
    }
    
    
    return 0;
}