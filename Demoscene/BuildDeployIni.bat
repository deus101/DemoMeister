@echo off

Set DeployPath="%~f1"
Set file=%DeployPath%/DemoMeister.ini
Set Section=DeployEditBuild
Set Key=MainProjectPath

Set ProjectDir=MainProjectPath=%~f2
Set ProdName=ProductionName=WCD_1
Set ProdFolder=ProductionFolder=WCD_1_HackSpace

if not exist "%file%" (
  echo There is no ini file.  Write new one:
  echo [%Section%] >> "%file%"
  echo %ProjectDir% >> "%file%"
  echo %ProdName% >> "%file%"
  echo %ProdFolder% >> "%file%"
  goto finished
)

find "[%Section%]" < "%file%" > NUL || (
  echo There is no %Section% section already in file.  Write new one:
  echo [%Section%] >> "%file%"
  echo %ProjectDir% >> "%file%"
  echo %ProdName% >> "%file%"
  echo %ProdFolder% >> "%file%"
  goto finished
)

find "%ProjectDir%" < "%file%" > NUL && (
  echo The new line already exists in the file. Do nothing:
  goto finished
)

echo The %Section% section was found so looking for the line to add after

copy /y "%file%" "%file%.old" >NUL
del "%file%"


for /f "usebackq tokens=1,*eol=|delims==" %%a in (%file%.old) do ( 


	IF /i "%%b"=="" ( echo %%a  >> "%file%" ) ELSE IF /i "%%a"=="%Key%" ( echo found duplicate ) ELSE ( echo %%a=%%b  >> "%file%" ) 
	
		

   IF /i "%%a"=="[%Section%]" (
    echo Found %Section% section, adding line 
		(echo %ProjectDir%) >> "%file%" )
		(echo %ProdName%) >> "%file%" )
		(echo %ProdFolder%) >> "%file%" )

 )
 
 
:finished

echo.
echo Done.