//
//  DrawChart.cpp
//  Charts
//
//  Created by GUSTAVO CAMPOS on 05/07/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//

#include "DrawChart.hpp"
#include "graphic.hpp"


#include <fcntl.h>

#include <fstream>
#include <cstring>

#include "Images/ericsson.xpm"
#include "Images/ericsson_logo.xpm"


#include <cmath>

extern int errno;

char szVGAValues[16][9] = {
    "00000000", //0
    "0000AA00", //1
    "00AA0000", //2
    "00AAAA00", //3
    "AA000000", //4
    "AA00AA00", //5
    "AA550000", //6
    "AAAAAA00", //7
    "55555500", //8
    "5555FF00", //9
    "55FF5500", //10
    "55FFFF00", //11
    "FF555500", //12
    "FF55FF00", //13
    "FFFF5500", //14
    "FFFFFF00"  //15
};

Color colorVGAValues [16] = {
    { 0x00000000 }, //1
    { 0x0000AA00 }, //2
    { 0x00AA0000 }, //2
    { 0xAA000000 }, //4
    { 0xAA00AA00 }, //5
    { 0xAA550000 }, //6
    { 0x00AAAA00 }, //3
    { 0xAAAAAA00 }, //7
    { 0x55555500 }, //8
    { 0x5555FF00 }, //9
    { 0x55FF5500 }, //10
    { 0xFF555500 }, //12
    { 0xFF55FF00 }, //13
    { 0xFFFF5500 }, //14
    { 0x55FFFF00 }, //11
    { 0xFFFFFF00 }  //15
};

DrawChartException::DrawChartException (std::string strMessage, uint nErrorID): Exception ("iniplus", strMessage, nErrorID)
{}



DrawChart::DrawChart(uint32_t nMaxY) : nMaxY(nMaxY)
{
    
}


void DrawChart::addColumn(const std::string strColumnName)
{
    Verify (vecData.size() == 0, "Error, already adding data.", DC_COLUMN_ADD_DENIED, DrawChartException);
    Verify (vecData.size() < 11, "Error, no more room for Coluns...", DC_COLUMN_MAX_DENIED, DrawChartException);
    
    vecColumns.push_back (strColumnName);
}


void DrawChart::addData(const vector<int> vecDataRow)
{
    //_LOG << "Adding data to vecData:" << (vecData.size()+1) << endl;
    vecData.push_back(vecDataRow);
}


void DrawChart::generateToFile(uint nWidth, uint nHeight, const string strBGColor, const std::string strTitle, const std::string strFileName)
{    
    Graphic objGraphic (nWidth, nHeight);
    
    generate (nWidth, nHeight, strBGColor, strTitle, objGraphic);
    
    uint8_t* pBuffer = objGraphic.getRGBBuffer();
    
    //Util::PrintDataToDebug(pBuffer, (sizeof(uint8_t) * ((objGraphic.GetHeight() * objGraphic.GetWidth()) * 3)));
    
    jpge::params params;
    params.m_quality = 90; //0-100
    params.m_subsampling =  jpge::H2V2;
    params.m_two_pass_flag = false;
    
    
    jpge::compress_image_to_jpeg_file(strFileName.c_str(), objGraphic.GetWidth(), objGraphic.GetHeight(), 3 /*RGB*/, (const uint8_t*) pBuffer, params);
    
    delete [] pBuffer;
}


void DrawChart::generateToString(uint nWidth, uint nHeight, const string strBGColor, const std::string strTitle, std::string &strReturn)
{

}


void DrawChart::generate(uint nWidth, uint nHeight, const string strBGColor, const string strTitle,  Graphic& gChartContext)
{
    
    //_LOG << "BGCOLOR: " << strBGColor << ", strTitle: " << strTitle << endl;
    
    Color colorBG = MkColor(strBGColor);
    Color colorBlack = MkColor(0,0,0,0);
    
    //Color colorBG = MkColor(255,255,255);
    gChartContext.DrawFillBox(0, 0, nWidth+1, nHeight, 0, colorBG);
    
    gChartContext.SelectDefaultFont(0);
    gChartContext.GPrint(5, 14, 0, MkColor(0,0,0), strTitle.c_str());
    
    {
        int nY, nX;
        
        for (int nCount=0; nCount < vecColumns.size(); nCount++)
        {
            nX = nWidth - 60; nY = (int) 44 + (nCount*10);
            
            gChartContext.DrawFillBox(nX-10, nY-8, nX-2, nY+1, 0, colorVGAValues [nCount+1]);
            
            gChartContext.GPrint(&nX, &nY, 0, colorBlack, vecColumns [nCount].c_str());
        }
    }
    
    int nDataWidth = nWidth - 80;
    int nDataHeight = nHeight - 40;
    
    for (int nCount=35; nCount < 35+nDataHeight; nCount += 5)
        gChartContext.DrawLine(10, nCount, nDataWidth, nCount, 230, colorBlack);
    
    for (int nCount=10; nCount < nDataWidth; nCount += 5)
        gChartContext.DrawLine(nCount, 35, nCount, 35+nDataHeight, 230, colorBlack);
    
    //_LOG << "vecDataSize: " << ((nDataWidth / (int)vecData.size())) << endl;
    
    uint nDataPace = ((nDataWidth / (int)vecData.size()) < 0) ? 1 / ((double) nDataWidth / (int)vecData.size()) : 1;
    double nXPace = ((nDataWidth / (int)vecData.size()) < 0) ? 1 : ((double) nDataWidth / (int)vecData.size());
    
    //_LOG << "aqui..." << endl;

    gChartContext.DrawBox(10, 35, nDataWidth, nHeight - 5, 0, colorVGAValues [0]);
    
    string strValue = to_string(nMaxY);
    {
        int nX, nY;
        
        gChartContext.GPrint(&(nX = 2), &(nY=33), 0, colorBlack, strValue.c_str());
        gChartContext.GPrint(&(nX = 2), &(nY=nHeight-5), 0, colorBlack, "0");
    }
    
    
    
    int nY2, nY;
    double nX, nX2;
    
    int nValue, nItem;
    
    if (vecData.size() == 0)
        return;
                                
    for (int nCurrentLine=0; nCurrentLine < vecData[0].size(); nCurrentLine++)
    {
        nX = 10; nY = nHeight-5;

        for (int nCount=0; nCount < vecData.size(); nCount += nDataPace)
        {
            nItem = vecData[nCount][nCurrentLine];
            nValue = (nItem >= 0 ? (nItem <= nMaxY ? nItem : nMaxY ): 0);
            nValue = ((nDataHeight)*nValue) / nMaxY;
            
            nX2 = nX + nXPace;
            nY2 = (nHeight - 5) - (int) nValue;
         
            nX2 = nX2 > nDataWidth ? nDataWidth : nX2;
            
           // fprintf (stderr, "X:[%f], Y:[%d], X2:[%f], Y2:[%d] - PaceX:[%f], DataPace:[%d] - Height:[%d] - nDataWidth:[%d] nValue[%d], nItem:[%d]\n", nX, nY, nX2, nY2, nXPace, nDataPace, nHeight - 20, nDataWidth, nValue, nItem);
            
            gChartContext.DrawLine(nX, nY, nX2, nY2, 0, colorVGAValues [nCurrentLine + 1]);
            
            nX = nX2; nY = nY2;
        }
    }
    
    gChartContext.DrawXPM((nWidth/2)-(250/2), (nHeight/2)-(51/2), 1, 1, 250, 51, 240, (const char**) ericsson_landscape3);
    gChartContext.DrawXPM(nWidth-51, nHeight-51, 1, 1, 50, 50, 20, (const char**) ericsson_logo);

}




void DrawChart::Clear()
{
    vecColumns.clear();
    vecData.clear();
}




