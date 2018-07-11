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
#include <fstream>

#include "Exception.hpp"
#include "Util.hpp"
#include "graphic.hpp"
#include "jpeg.hpp"
#include "Util.hpp"


enum DrawChartError
{
    DC_COLUMN_ADD_DENIED = 10,
    
    DC_GENERATE_FILE_OPEN_ERROR = 20,
    DC_GENERATE_FILE_ERR_READING
};


/*
 * Creating writing structure for jpge
 */

class jpegFile : public jpeg
{
private:
    
    string strFile;
    ofstream ofFile;
    
    int nFD;
public:
    
    jpegFile (Graphic& pGraphic, const string strFile);
    ~jpegFile ();
    
    void write_jpeg(const uint8_t*, const uint32_t) override;

};


class DrawChartException : public Exception
{
public:
    DrawChartException (std::string strMessage, uint nErrorID);
};


class DrawChart
{
private:
    vector<string> vecColumns;
    vector<vector<unsigned long long>> vecData;
    
    void generate(uint nWidth, uint nHeight, const string strBGColor, const string strTitle, Graphic& refGraphic, jpeg& refJPEG);
        

public:
    DrawChart ();
    
    void addColumn(const string strColumnName);
    void addData(vector<unsigned long long> vecDataRow);
    
    void generateToFile(uint nWidth, uint nHeight, const string strBGColor, const string strTitle, const string strFileName);
    void generateToString(uint nWidth, uint nHeight, const string strBGColor, const string strTitle, string& strReturn);
    
    void Clear();
};


#endif /* DrawChart_hpp */

