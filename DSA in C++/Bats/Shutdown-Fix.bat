@echo off
title Shutdown
echo Trying to shut down this PC...
echo.

REM Method 1: standard shutdown command
shutdown /s /t 0
if %errorlevel%==0 goto done
echo.
echo [Method 1 failed - error code %errorlevel%]

REM Method 2: force-close apps
shutdown /s /f /t 0
if %errorlevel%==0 goto done
echo.
echo [Method 2 failed - error code %errorlevel%]

REM Method 3: PowerShell
powershell -NoProfile -Command "Stop-Computer -Force"
if %errorlevel%==0 goto done
echo.
echo [Method 3 failed - error code %errorlevel%]

echo.
echo The PC did not shut down. Take a photo or copy the messages above.
echo Common causes: a managed/work/school PC that blocks shutdown from scripts,
echo or an account without shutdown permission.
pause
exit /b 1

:done
exit /b 0
