all: buildserver buildclient

buildserver:
	make -f make.BroadcastServer exec

buildclient:
	make -f make.BroadcastClient exec

clean:
	make -f make.BroadcastServer clean
	make -f make.BroadcastClient clean

debug:
	make -f make.BroadcastServer debug
	make -f make.BroadcastClient debug
