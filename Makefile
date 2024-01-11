CC=g++
EXEC=sfml_app

$(EXEC): src/main.cpp
	$(CC) -o $(EXEC) src/main.cpp -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm $(EXEC)
