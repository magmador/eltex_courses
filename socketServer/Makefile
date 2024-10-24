all: precreated queue socketServer

clean: queue-clean precreated-clean socketServer-clean

queue-clean:
	make -C QueueServer clean

precreated-clean:
	make -C PreCreated1-1 clean

socketServer-clean:
	make -C socketServer1-1 clean

queue:
	make -C QueueServer

precreated:
	make -C PreCreated1-1

socketServer:
	make -C socketServer1-1
