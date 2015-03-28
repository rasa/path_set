all:
	VCBuild.exe /nologo path_set.vcproj /rebuild

clean:
	VCBuild.exe /nologo path_set.vcproj /clean
	
upgrade:
	devenv path_set.sln /upgrade

.PHONY:	all clean upgrade

