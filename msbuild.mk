all:
	MSBuild.exe /nologo path_set.sln /p:Configuration=Debug
	MSBuild.exe /nologo path_set.sln /p:Configuration=Release

clean:
	MSBuild.exe /nologo path_set.sln /p:Configuration=Debug   /t:clean
	MSBuild.exe /nologo path_set.sln /p:Configuration=Release /t:clean

upgrade:
	devenv path_set.sln /upgrade
	
.PHONY:	all clean upgrade


