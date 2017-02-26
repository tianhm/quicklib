 


set RELEASE_DIR=QuickLib-%date:~0,4%%date:~5,2%%date:~8,2%


del .\dist\*.* /q

rem python.exe setup.py py2exe --includes sip,CTPMarket,CTPMarketType,PyCTPTrader,PyCTPType
python.exe setup.py py2exe --includes sip

 

copy QuickLibMD.dll .\dist\
copy QuickLibTD.dll .\dist\
copy QuickLibMonitor.dll .\dist\

copy QuickLibMD.ini .\dist\
copy QuickLibTD.ini .\dist\

copy TradeTime.ini .\dist\





mkdir %RELEASE_DIR%
del .\%RELEASE_DIR%\*.* /q
xcopy .\dist\*.* %RELEASE_DIR%
