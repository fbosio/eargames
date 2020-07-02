objects = build/test.o build/AudioPlayer.o build/NotePicker.o \
	  build/SignalGenerator.o build/SignalReader.o


bin/test: bin/ build/ $(objects)
	g++ $(objects) lib/libportaudio.a lib/*.o -lrt -lm -lasound -pthread -o bin/test

bin/ :
	mkdir bin/

build/ : 
	mkdir build/

build/test.o : src/test.cpp src/core/AudioPlayer.h src/core/NotePicker.h src/core/SignalGenerator.h
	g++ -c -I include/ src/test.cpp -o build/test.o

build/AudioPlayer.o : src/core/AudioPlayer.h src/core/AudioPlayer.cpp
	g++ -c -I include/ src/core/AudioPlayer.cpp -o build/AudioPlayer.o

build/NotePicker.o : src/core/NotePicker.h src/core/NotePicker.cpp
	g++ -c src/core/NotePicker.cpp -o build/NotePicker.o

build/SignalGenerator.o : src/core/SignalReader.h src/core/SignalGenerator.h src/core/SignalGenerator.cpp
	g++ -c src/core/SignalGenerator.cpp -o build/SignalGenerator.o

build/SignalReader.o : src/core/SignalReader.h src/core/SignalReader.cpp
	g++ -c src/core/SignalReader.cpp -o build/SignalReader.o


.PHONY : clean
clean : 
	-rm eargame $(objects)
	-rmdir bin/
	-rmdir build/
