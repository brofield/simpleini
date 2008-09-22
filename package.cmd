set VERSION=4.8.2

set SEVENZIP="C:\Program Files\7-Zip\7z.exe"

FOR /F "tokens=*" %%G IN ('DIR /AD /B /S Debug*') DO (
    DEL /S /Q "%%G"
    RD "%%G"
)
FOR /F "tokens=*" %%G IN ('DIR /AD /B /S Release*') DO (
    DEL /S /Q "%%G"
    RD "%%G"
)
DEL /Q "SimpleIni.ncb"
ATTRIB -H "SimpleIni.suo"
DEL /Q "SimpleIni.suo"
DEL /Q "SimpleIni.opt"
START "Generate documentation" /WAIT SimpleIni.doxy
cd ..
del simpleini-%VERSION%.zip
%SEVENZIP% a -tzip -r- -x!simpleini\.svn simpleini-%VERSION%.zip simpleini\*
del simpleini-doc.zip
%SEVENZIP% a -tzip -r simpleini-doc.zip simpleini-doc\*
cd simpleini
