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
#include <cerrno>

#include "Exception.hpp"
#include "Util.hpp"

#include "DrawChart.hpp"

#include "Images/ericsson.xpm"
#include "Images/ericsson_logo.xpm"




int main(int argc, const char * argv[])
{
    VERIFY (argc == 6, "Error, use  nWidth nHeight ColorRGBA(FFFFFF00) 'Title' 'file_name.jpg' ", 1);

    uint nWidth = atoi (argv[1]);
    uint nHeight = atoi (argv [2]);

    DrawChart objDrawChart;
    
    Util::PrintStandardTypeSizes();
    
    
    //char chCinbuffer [64 * 1024]; // 64k buffer
    
    //cin.rdbuf()->pubsetbuf(chCinbuffer, sizeof (chCinbuffer));
    
    char szLine [2048];
    uint nCount = 0;
    
    vector<string> vecData;
    vector<unsigned long long> vecRow;
    
    string strValue = "";
    
    while (cin.getline (szLine, sizeof(szLine)-1) && ++nCount)
    {
        strValue.assign(szLine, strlen(szLine));
        
        if (nCount == 1)
        {
            _LOG << "Header: [" << szLine << "]" << endl;
            
            Util::getCSVlikeParser (strValue, ";", 1, vecData);
            
            for (const string& strItem : vecData)
            {
                _LOG << "  Header Data: " << strItem << endl;
                
                objDrawChart.addColumn(strItem);
            }
                
        }
        else
        {
            _LOG << "Row Line: [" << szLine << "]" << endl;
            
            Util::getCSVlikeParser (strValue, ";", 1, vecData);
            
            vecRow.clear();
            
            for (const string& strItem : vecData)
            {
                _LOG << "  Row Data: " << strItem << endl;
                
                vecRow.push_back (std::strtoull(strItem.c_str(), nullptr, 10));
            }
        }
    }
    

    objDrawChart.generateToFile(nWidth, nHeight, argv[3], argv[4], argv[5]);
    
    
    const string strBGColor = argv[3];
    const string strTitle = argv[4];
    
    
 /*
    _LOG << "BGCOLOR: " << strBGColor << ", strTitle: " << strTitle << endl;
    
    Graphic gChartContext (nWidth, nHeight);
    
    Color colorBG = MkColor(strBGColor);
    
    gChartContext.DrawFillBox(0, 0, nWidth, nHeight, 0, colorBG);
    
    gChartContext.DrawXPM((nWidth/2)-(250/2), (nHeight/2)-(51/2), 1, 1, 250, 51, 240, (const char**) ericsson_landscape3);
    //gChartContext.DrawXPM(nWidth-51, nHeight-51, 1, 1, 50, 50, 10, (const char**) ericsson_logo);
    
    gChartContext.SelectDefaultFont(0);
    gChartContext.GPrint(5, 14, 0, MkColor(0,0,0), strTitle.c_str());
    
    VERIFY ((nFD = open (argv[5], O_WRONLY | O_CREAT | O_TRUNC, 0664)) > 0, "Error: " << std::strerror(errno) << endl, 1);
    
    jpeg jpegImage (&gChartContext);
    jpegImage.CompressImage(write_jpg);
    
    close(nFD);
  */
}
