vpath %.a lib
vpath %.cpp src src/core
vpath %.h src src/core

objdir = build
objects = $(addsuffix .o, $(addprefix $(objdir)/, AudioPlayer NotePicker \
	  SignalGenerator SignalReader))

bin/game: libportaudio.a bin/ $(objdir) $(objects) $(objdir)/game.o
	g++ $(objects) $(objdir)/game.o $< lib/*.o -lrt -lm -lasound -pthread \
		-o $@

bin/test: libportaudio.a bin/ $(objdir) $(objects) $(objdir)/test.o
	g++ $(objects) $(objdir)/test.o $< lib/*.o -lrt -lm -lasound -pthread \
		-o $@

bin/ :
	mkdir bin/

$(objdir) : 
	mkdir $(objdir)

$(objdir)/game.o : main.cpp AudioPlayer.h NotePicker.h SignalGenerator.h
	g++ -c -I include/ $< -o $@

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
	-rm bin/game bin/test $(objects) $(objdir)/game.o $(objdir)/test.o
	-rmdir bin/
	-rmdir $(objdir)
