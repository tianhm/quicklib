set RELEASE_DIR=QuickLibDemo已编译可独立运行%date:~0,4%%date:~5,2%%date:~8,2%
del .\dist\*.* /q

rem python.exe setup.py py2exe --includes sip,CTPMarket,CTPMarketType,CTPTrader,CTPTraderType
python.exe setup.py py2exe --includes sip
copy QuickLibMD.ini .\dist\
copy QuickLibTD.ini .\dist\
copy QuickLibMD.dll .\dist\
copy QuickLibTD.dll .\dist\

copy thostmduserapi.dll   .\dist\

copy thosttraderapi.dll   .\dist\

copy TradeTime.ini   .\dist\
copy Instrument.ini  .\dist\


mkdir %RELEASE_DIR%
del .\%RELEASE_DIR%\*.* /q
xcopy .\dist\*.* %RELEASE_DIR%
