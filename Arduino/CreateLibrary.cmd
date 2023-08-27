@ECHO OFF

REM ******************************
REM * The project structure is optimized to develop. Therefore the main code of the library 
REM * is in the in the path library/easy/*. To create an installable library the path is wrong. 
REM * This script collect the files and move them to the right positon. 
REM ******************************
REM * Before first use:
REM *   0). Check where "7z.exe" is installed on your computer. 
REM *       Adapt the variable %CompressToolWithPath% according to your installation. 
REM * 
REM * Usage:
REM *   1). Delete old "_ZipLibrary\Easy.zip" 
REM *   2). Double click the script
REM *   3). Rename "_ZipLibrary\Easy.zip" to the according version. --> e.g. "Easy_1.2.3"
REM *       Look into the file "library.properties", version=... --> e.g.: "version=1.2.3"
REM ******************************
REM * (C) 2023 Hans Rothenbuehler, "Sketch made easy for Arduino" 
REM ******************************

ECHO *** Create Archive ***
SET CompressToolWithPath="C:\Program Files\7-zip\7z.exe"
%CompressToolWithPath% a -tzip _ZipLibrary/Easy.zip @"IncludedFiles.txt" -scsWIN


ECHO *** Move files***

%CompressToolWithPath% rn _ZipLibrary/Easy.zip libraries\Easy\keywords.txt Easy\keywords.txt
%CompressToolWithPath% rn _ZipLibrary/Easy.zip libraries\Easy\library.json Easy\library.json
%CompressToolWithPath% rn _ZipLibrary/Easy.zip libraries\Easy\library.properties Easy\library.properties
%CompressToolWithPath% rn _ZipLibrary/Easy.zip README.md Easy\README.md
%CompressToolWithPath% rn _ZipLibrary/Easy.zip LICENSE Easy\LICENSE
%CompressToolWithPath% rn _ZipLibrary/Easy.zip libraries\Easy\src Easy\src
%CompressToolWithPath% rn _ZipLibrary/Easy.zip Example Easy\Examples\Examples
%CompressToolWithPath% rn _ZipLibrary/Easy.zip Model Easy\Examples\Models
%CompressToolWithPath% rn _ZipLibrary/Easy.zip Test Easy\Examples\Tests
%CompressToolWithPath% d _ZipLibrary/Easy.zip libraries\Easy


ECHO *** Finish ****
ECHO Add version into the filename (e.g. "Easy_1.2.3.zip")!
PAUSE