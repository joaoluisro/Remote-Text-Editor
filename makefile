all:
	g++ cliente/cliente.cpp utils/utils.cpp -o client
clean:
	rm ./client.exe
