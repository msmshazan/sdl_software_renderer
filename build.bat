@echo off
set CompilerFlags=/Z7 /FC /nologo /Od /EHsc -fp:fast -Gm- -GR- -EHa- /Oi -WX -W4 -wd4189 -wd4706  -wd4244 -wd4127 -wd4505 -wd4100 -wd4201
set LinkerFlags=-subsystem:Console 
set bits=x64
set LibraryLocation= ..\deps\lib\%bits%\

mkdir build > NUL 2> NUL
pushd build
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" %bits%
del *.pdb > NUL 2> NUL
ctime -begin sdl.ctm
cl %CompilerFlags% /MDd ..\code\main.cpp /I..\deps\include  /link -incremental:no %LibraryLocation%SDL2.lib %LibraryLocation%SDL2main.lib opengl32.lib  %LinkerFlags%
ctime -end sdl.ctm
popd
