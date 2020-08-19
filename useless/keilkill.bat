@echo off

echo Cleaning.
echo Cleaning..

del ..\*bak /s 1>nul 2>nul
del ..\*obj /s  1>nul  2>nul
del ..\*plg /s  1>nul  2>nul
del ..\*rpt /s  1>nul  2>nul
del ..\*tmp /s  1>nul  2>nul
del ..\*o /s  1>nul  2>nul
del ..\*htm /s  1>nul  2>nul
del ..\*lst /s  1>nul  2>nul
del ..\*lnp /s  1>nul  2>nul
del ..\*m51 /s  1>nul  2>nul

echo Cleaning_OK

exit
