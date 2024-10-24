all: buildserver buildclient

buildserver:
	make -f make.Server exec

buildclient:
	make -f make.Client exec

clean:
	make -f make.Server clean
	make -f make.Client clean

debug:
	make -f make.Server debug
	make -f make.Client debug
