all:
	g++ -w src/user_interface.cpp ConexaoRawSocket.c src/editorlib.cpp -o main
	g++ -w src/server.cpp ConexaoRawSocket.c src/editorlib.cpp -o server
clean:
	rm ./editorAPI.exe
