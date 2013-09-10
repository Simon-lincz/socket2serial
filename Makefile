.PHONY:all
all:server client serial server2serial

server:server.c
	gcc -o $@ $^

client:client.c
	gcc -o $@ $^

serial:serial.c
	gcc -o $@ $^

server2serial:serial_module.h serial_module.c server2serial.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm client server serial	server2serial
