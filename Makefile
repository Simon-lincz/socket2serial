.PHONY:all
all:server client serial server2serial copy

server:server.c
	$(CC) -o $@ $^

client:client.c
	$(CC) -o $@ $^

serial:serial.c
	$(CC) -o $@ $^

server2serial:serial_module.h serial_module.c server2serial.c
	$(CC) -o $@ $^

.PHONY:copy
copy:
	mkdir bin
	cp server bin
	cp client bin
	cp serial bin
	cp server2serial bin

.PHONY:clean
clean:
	rm bin -r
