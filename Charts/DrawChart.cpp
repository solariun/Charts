//
//  DrawChart.cpp
//  Charts
//
//  Created by GUSTAVO CAMPOS on 05/07/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//

#include "DrawChart.hpp"
#include "graphic.hpp"
#include "jpeg.hpp"

#include <fcntl.h>

#include <fstream>
#include <cstring>

#include "Images/ericsson.xpm"
#include "Images/ericsson_logo.xpm"

extern int errno;

DrawChartException::DrawChartException (std::string strMessage, uint nErrorID): Exception ("iniplus", strMessage, nErrorID)
{}



DrawChart::DrawChart()
{}


void DrawChart::addColumn(const std::string strColumnName)
{
    Verify (vecData.size() == 0, "Error, already adding data.", DC_COLUMN_ADD_DENIED, DrawChartException);
    
    vecColumns.push_back (strColumnName);
}


void DrawChart::addData(const vector<unsigned long long> vecDataRow)
{
    vecData.push_back(vecDataRow);
}


void DrawChart::generateToFile(uint nWidth, uint nHeight, const string strBGColor, const std::string strTitle, const std::string strFileName)
{    
    Graphic objGraphic (nWidth, nHeight);
    jpegFile objJPEGFile (objGraphic, strFileName);
    
    generate (nWidth, nHeight, strBGColor, strTitle, objGraphic, objJPEGFile);
}


void DrawChart::generateToString(uint nWidth, uint nHeight, const string strBGColor, const std::string strTitle, std::string &strReturn)
{

}


void DrawChart::generate(uint nWidth, uint nHeight, const string strBGColor, const string strTitle,  Graphic& gChartContext, jpeg& jpegImage)
{
    
    _LOG << "BGCOLOR: " << strBGColor << ", strTitle: " << strTitle << endl;
    
    //Color colorBG = MkColor(strBGColor);
    Color colorBG = MkColor(255,255,255,0);
    
    gChartContext.DrawFillBox(0, 0, nWidth, nHeight, 0, colorBG);

    gChartContext.DrawXPM((nWidth/2)-(250/2), (nHeight/2)-(51/2), 1, 1, 250, 51, 10, (const char**) ericsson_landscape3);
    gChartContext.DrawXPM(nWidth-51, nHeight-51, 1, 1, 50, 50, 10, (const char**) ericsson_logo);
    
    gChartContext.SelectDefaultFont(0);
    gChartContext.GPrint(5, 14, 0, MkColor(0,0,0), strTitle.c_str());
    
    //vector<uint8_t> pJPGdata;
    
    jpegImage.CompressImage();
}




void DrawChart::Clear()
{
    vecColumns.clear();
    vecData.clear();
}


/*
 * JPEG file save procedures
 */


jpegFile::jpegFile(Graphic& pGraphic, const std::string strFile): jpeg(pGraphic), strFile(strFile)
{
    ofFile.open(strFile.c_str(), ios_base::trunc | ios_base::binary);
    
    Verify (ofFile.is_open(), "ERROR: " + std::strerror(errno), DC_GENERATE_FILE_OPEN_ERROR, DrawChartException);
    
    //Verify ((nFD = open (strFile.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0664)) > 0, "Error: " + std::strerror(errno), 1, DrawChartException);
}


jpegFile::~jpegFile()
{
    ofFile.close();
}


void jpegFile::write_jpeg(const uint8_t* pData, const uint32_t nDataSize)
{
    _LOG << "Writting: [" << nDataSize << "]" << endl;
    
    Verify (ofFile.write((const char*) pData, nDataSize), "Error: " + std::strerror(errno), DC_GENERATE_FILE_ERR_READING, DrawChartException);
}

