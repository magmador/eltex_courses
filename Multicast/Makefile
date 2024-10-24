all: buildserver buildclient

buildserver:
	make -f make.MulticastSender exec

buildclient:
	make -f make.MulticastReceiver exec

clean:
	make -f make.MulticastSender clean
	make -f make.MulticastReceiver clean

debug:
	make -f make.MulticastSender debug
	make -f make.MulticastReceiver debug
