compile:
	g++ frame.cpp main.cpp `wx-config --libs std,richtext --cxxflags` -o simple_notepad
clean:
	rm -rf simple_notepad
run:
	./simple_notepad
