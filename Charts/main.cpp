//
//  main.cpp
//  Charts
//
//  Created by GUSTAVO CAMPOS on 03/07/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//

#include <iostream>   // std::cin, std::cout
#include <string>

#include <stdio.h>
#include <fcntl.h>
#include <istream>
#include <vector>

#include "Exception.hpp"
#include "Util.hpp"
#include "graphic.hpp"
#include "jpeg.hpp"
#include "Util.hpp"

#include "Images/ericsson.xpm"

int main(int argc, const char * argv[])
{
    VERIFY (argc == 6, "Error, use  nWidth nHeight ColorRGBA(FFFFFF00) 'Title' 'file_name.jpg' ", 1);

    int nWidth = atoi (argv[1]);
    int nHeight = atoi (argv [2]);
    
    string strChartName = argv[4];
    string strName = argv[5];
    
    
    istream* isInput;
    
    char chCinbuffer [64 * 1024]; // 64k buffer
    
    cin.rdbuf()->pubsetbuf(chCinbuffer, sizeof (chCinbuffer));
    
    char szLine [2048];
    uint nCount = 1;
    vector<string> vecData;
    string strValue = "";
    
    while (cin.getline (szLine, sizeof(szLine)-1) && nCount++)
    {
        strValue.assign(szLine, strlen(szLine));
        
        if (nCount == 1)
        {
            Util::getCSVlikeParser (strValue, ";", 1, vecData);
        }
    }
    
    
    isInput = &cin;
    
    Graphic gChartContext (nWidth, nHeight);
    
    Color colorBG = MkColor(argv[3]);
    
    gChartContext.DrawFillBox(0, 0, nWidth, nHeight, 0, colorBG);
    
    
    gChartContext.DrawXPM((nWidth/2)-(250/2), (nHeight/2)-(51/2), 1, 1, 250, 51, 240, (const char**) ericsson_landscape3);
    
    gChartContext.SelectDefaultFont(0);
    gChartContext.GPrint(5, 14, 0, MkColor(0,0,0), strChartName.c_str());
    
    
    int nFD = 0;
    
    VERIFY ((nFD = open (strName.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0664)) > 0, "Error: " << std::strerror(errno) << endl, 1);
    
    
    jpeg jpegImage (&gChartContext, nFD);
    
    jpegImage.CompressImage();
    
}
