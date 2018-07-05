//
//  main.cpp
//  Charts
//
//  Created by GUSTAVO CAMPOS on 03/07/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//

#include <iostream>   // std::cin, std::cout
#include <string>

#include "Exception.hpp"
#include "Util.hpp"
#include "graphic.hpp"
#include "jpeg"

#include "Images/ericsson.xpm"

int main(int argc, const char * argv[])
{
    VERIFY (argc == 4, "Error, use  nWidth nHeight Color(0xFFFFFF) ", 1);

    int nWidth = atoi (argv[1]);
    int nHeight = atoi (argv [2]);
    
    Graphic gChartContext (nWidth, nHeight);
    
    Color colorBG = MkColor(argv[3]);
    
    gChartContext.DrawFillBox(1, 1, nWidth, nHeight, 0, colorBG);
    
    
    gChartContext.DrawXPM((nWidth/2)-(250/2), (nHeight/2)-(51/2), 1, 1, 250, 51, 200, (const char**) ericsson_landscape3);
    
    jpg
    
}
