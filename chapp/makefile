TARGET = chapp chappServer
OBJECTS = chapp.o chappServer.o chat_client.o chat_server.o chat.o list.o
THREAD_FLAGS = -pthread
FLAGS = -g -Wall -fPIC $(THREAD_FLAGS)

normal: $(TARGET) run

chapp : chat_client.o chat.o chapp.o
	gcc $(FLAGS) chat_client.o chat.o chapp.o -o chapp
chappServer : chat_server.o chat.o chappServer.o list.o
	gcc $(FLAGS) $(HC) chat_server.o chat.o list.o chappServer.o -o chappServer

chat_client.o : chat_client.c chat_client.h chat.h
	gcc $(FLAGS) -c chat_client.c -o chat_client.o
chat_server.o : chat_server.c chat_server.h chat.h list.h
	gcc $(FLAGS) -c chat_server.c -o chat_server.o
chat.o : chat.c chat.h
	gcc $(FLAGS) -c chat.c -o chat.o

list.o : list.c list.h
	gcc $(FLAGS) -c list.c -o list.o

chapp.o : chapp.c chat_client.h
	gcc $(FLAGS) -c chapp.c -o chapp.o
chappServer.o : chappServer.c chat_server.h list.h
	gcc $(FLAGS) -c chappServer.c -o chappServer.o

clean:
	$(RM) $(TARGET)
	$(RM) $(OBJECTS)

run:
	@echo "Compilation done !\n"
	@echo "run the server : ./chappServer"
	@echo "run the client : ./chapp <hostname>"
  

