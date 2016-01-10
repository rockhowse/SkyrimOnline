@echo off
py ./codegen.py ../Code/messages/ Protocol.xml Cli Game Client
py ./codegen.py ../Code/messages/ Protocol.xml Game Cli Server
pause