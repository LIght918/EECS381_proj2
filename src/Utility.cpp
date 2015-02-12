//
//  Utility.cpp
//  EECS381_proj2
//
//  Created by Charlie OConor on 1/31/15.
//  Copyright (c) 2015 Charlie OConor. All rights reserved.
//

#include "Utility.h"
#include "String.h"
#include <cstring>
#include <sstream>
#include <iostream>

using std::istream;
using std::stringstream;
using std::cout;
using std::endl; 

static const char* const Inval_Title = "Could not read a title!";


void read_title( istream& is, String& title )
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

