#include "NotePicker.h"
#include <chrono>
#include <random>


NotePicker::NotePicker()
	: notes {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"},
	distribution(0, notes.size()-1)
{
}

unsigned int NotePicker::pickIndex()
{
	seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	return distribution(generator);
}

char* NotePicker::note(unsigned int index)
{
	return notes[index];
}
