md ..\cocostemp
call cocos.bat new zombie -l cpp -d ..\cocostemp
xcopy /s /y ..\cocostemp\zombie .
RD /s /q ..\cocostemp
git clean -f
git checkout .