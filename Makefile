vpath %.a lib
vpath %.cpp src src/core
vpath %.h src src/core

objdir = build
objects = $(addsuffix .o, $(addprefix $(objdir)/, test AudioPlayer NotePicker \
	  SignalGenerator SignalReader))


bin/test: libportaudio.a bin/ $(objdir) $(objects)
	g++ $(objects) $< lib/*.o -lrt -lm -lasound -pthread -o $@

bin/ :
	mkdir bin/

$(objdir) : 
	mkdir $(objdir)

$(objdir)/test.o : test.cpp AudioPlayer.h NotePicker.h SignalGenerator.h
	g++ -c -I include/ $< -o $@

$(objdir)/AudioPlayer.o : AudioPlayer.cpp AudioPlayer.h
	g++ -c -I include/ $< -o $@

$(objdir)/NotePicker.o : NotePicker.cpp NotePicker.h
	g++ -c $< -o $@

$(objdir)/SignalGenerator.o : SignalGenerator.cpp SignalReader.h \
	 SignalGenerator.h
	g++ -c $< -o $@

$(objdir)/SignalReader.o : SignalReader.cpp SignalReader.h
	g++ -c $< -o $@


.PHONY : clean
clean : 
	-rm bin/test $(objects)
	-rmdir bin/
	-rmdir $(objdir)
