vpath %.cpp src src/core
vpath %.h src src/core

objdir = build
objects = $(addsuffix .o, $(addprefix $(objdir)/, test AudioPlayer NotePicker \
	  SignalGenerator SignalReader))


bin/test: bin/ $(objdir) $(objects)
	g++ $(objects) lib/libportaudio.a lib/*.o -lrt -lm -lasound -pthread \
		-o $@

bin/ :
	mkdir bin/

$(objdir) : 
	mkdir $(objdir)

$(objdir)/test.o : test.cpp AudioPlayer.h NotePicker.h SignalGenerator.h
	g++ -c -I include/ src/test.cpp -o $@

$(objdir)/AudioPlayer.o : AudioPlayer.h AudioPlayer.cpp
	g++ -c -I include/ src/core/AudioPlayer.cpp -o $@

$(objdir)/NotePicker.o : NotePicker.h NotePicker.cpp
	g++ -c src/core/NotePicker.cpp -o $@

$(objdir)/SignalGenerator.o : SignalReader.h SignalGenerator.h \
	 SignalGenerator.cpp
	g++ -c src/core/SignalGenerator.cpp -o $@

$(objdir)/SignalReader.o : SignalReader.h SignalReader.cpp
	g++ -c src/core/SignalReader.cpp -o $@


.PHONY : clean
clean : 
	-rm bin/test $(objects)
	-rmdir bin/
	-rmdir $(objdir)
