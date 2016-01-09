@echo off
"%PythonDir%/\python.exe" ./codegen.py ../Code/messages/ Protocol.xml Cli Game Client
"%PythonDir%/\python.exe" ./codegen.py ../Code/messages/ Protocol.xml Game Cli Server
pause