all: buildserver buildclient

buildserver:
	make -f make.server exec

buildclient:
	make -f make.ClientTcp exec
	make -f make.ClientUdp exec

clean:
	make -f make.server clean
	make -f make.ClientTcp clean
	make -f make.ClientUdp clean

debug:
	make -f make.server debug
	make -f make.ClientTcp debug
	make -f make.ClientUdp debug
