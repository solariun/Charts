//
//  DrawChart.hpp
//  Charts
//
//  Created by GUSTAVO CAMPOS on 05/07/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//

#ifndef DrawChart_hpp
#define DrawChart_hpp

#include <stdio.h>

#include <string>
#include <istream>
#include <vector>
#include <array>

#include "Exception.hpp"
#include "Util.hpp"
#include "graphic.hpp"
#include "jpeg.hpp"
#include "Util.hpp"


class DrawChartException : Exception
{
public:
    DrawChartException (std::string strMessage, uint nErrorID);
};

class DrawChart
{
public:
    DrawChart ();
    
private:
    vector<string> vecColumns;
    vector<vector<int>> vecData;
    
};


#endif /* DrawChart_hpp */

