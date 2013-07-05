setlocal
set arch=%1%
if "%arch%" == "" (
  echo.
  echo Error: Arch is not set.
  exit 1
)
if "%STAFF_HOME%" == "" (
  echo.
  echo Error: STAFF_HOME is not set.
  exit 1
)
set PATH=%STAFF_HOME%\lib;%STAFF_HOME%\bin;%PATH%
%STAFF_HOME%\bin\staff_codegen -u -tclient -csrc devicemgmt.h onvif.h xmlmime.h .h b.h ws_addr.h bf.h xml.h t.h include.h
endlocal
