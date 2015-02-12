//
//  Utility.cpp
//  EECS381_proj2
//
//  Created by Charlie OConor on 1/31/15.
//  Copyright (c) 2015 Charlie OConor. All rights reserved.
//

#include "Utility.h"

#include <iostream>
#include <fstream>
using std::ifstream;

void get_white_space( ifstream& is )
{   
    // load chars until we get one that it not white space
    while ( isspace( is.peek() ) && is.good() )
    {
        is.get();
    }
}