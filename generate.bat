md ..\cocostemp
cocos.bat new zombie -l cpp -d ..\cocostemp
xcopy /s ..\cocostemp\zombie .
RD /s ..\cocostemp
git clean -f