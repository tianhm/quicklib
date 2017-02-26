 


set RELEASE_DIR=QuickLibAShare已编译可独立运行%date:~0,4%%date:~5,2%%date:~8,2%


del .\dist\*.* /q

rem python.exe setup.py py2exe --includes sip,CTPMarket,CTPMarketType,PyCTPTrader,PyCTPType
python.exe setup.py py2exe --includes sip

 
 
QuickLibAShareMD .\dist\

copy QuickLibAShareMD.dll .\dist\
copy  QuickLibMD.ini .\dist\
copy InstrumentList.csv .\dist\

   

mkdir %RELEASE_DIR%
del .\%RELEASE_DIR%\*.* /q
xcopy .\dist\*.* %RELEASE_DIR%
