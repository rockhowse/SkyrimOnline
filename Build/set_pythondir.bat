::%1 is a CLA that should be the path of your python.exe executable.
::This will permanently set the PythonDir environment variable, allowing you to run codegen.bat indefinitely
::Eliminates the need to either change the codegen.bat script every time it is edited in any way or enter your python path as a command line argument. 
@echo OFF
setx PythonDir %1

