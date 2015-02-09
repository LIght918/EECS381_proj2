//
//  Utility.cpp
//  EECS381_proj2
//
//  Created by Charlie OConor on 1/31/15.
//  Copyright (c) 2015 Charlie OConor. All rights reserved.
//

#include "Utility.h"
#include "String.h"
#include <sstream>
#include <iostream>

using std::istream;
using std::stringstream;

void read_title( istream& is, String& title )
{
    String temp;
    getline( is , title );
    

    stringstream ss;
    ss << title;
    
    ss >> title;
    
    while ( ss.good() )
    {
        ss >> temp;
        title += temp + " ";
    }
}

