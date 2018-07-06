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
#include "Images/ericsson_logo.xpm"

int nFD = 0;

void write_jpg (const unsigned char* buff, const unsigned size)
{
    write(nFD, (const void*) buff, size);
}

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
    uint nCount = 0;
    vector<string> vecData;
    string strValue = "";
    
    while (cin.getline (szLine, sizeof(szLine)-1) && ++nCount)
    {
        strValue.assign(szLine, strlen(szLine));
        
        if (nCount == 1)
        {
            _LOG << "Line1: [" << szLine << "]" << endl;
            
            Util::getCSVlikeParser (strValue, ";", 1, vecData);
            
            for (string& strItem : vecData)
            {
                _LOG << "Data: " << strItem << endl;
            }
                
        }
    }
    
    
    isInput = &cin;
    
    Graphic gChartContext (nWidth, nHeight);
    
    Color colorBG = MkColor(argv[3]);
    
    gChartContext.DrawFillBox(0, 0, nWidth, nHeight, 0, colorBG);
    
    
    gChartContext.DrawXPM((nWidth/2)-(250/2), (nHeight/2)-(51/2), 1, 1, 250, 51, 240, (const char**) ericsson_landscape3);
    //gChartContext.DrawXPM(nWidth-51, nHeight-51, 1, 1, 50, 50, 10, (const char**) ericsson_logo);
    
    gChartContext.SelectDefaultFont(0);
    gChartContext.GPrint(5, 14, 0, MkColor(0,0,0), strChartName.c_str());
    
    
    VERIFY ((nFD = open (strName.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0664)) > 0, "Error: " << std::strerror(errno) << endl, 1);
    

    void (*f)(const unsigned char* buff, const unsigned size) = write_jpg;
    
    jpeg jpegImage (&gChartContext);
    
    
    //jpegImage.CompressImage(f);

    
    jpegImage.CompressImage([&](const unsigned char* buff, const unsigned size) -> void
                            {
                                write(nFD, (const void*) buff, size);
                            });
    
}
