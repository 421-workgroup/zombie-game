md ..\cocostemp
call cocos.bat new zombie -l cpp -d ..\cocostemp
xcopy /s /y ..\cocostemp\zombie .
RD /s /y ..\cocostemp
git clean -f