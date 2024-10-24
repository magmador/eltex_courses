all: buildserver buildclient

buildserver:
	make -f make.server exec

buildclient:
	make -f make.client exec

clean:
	make -f make.server clean
	make -f make.client clean

debug:
	make -f make.server debug
	make -f make.client debug
