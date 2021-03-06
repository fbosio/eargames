#include "core/AudioPlayer.h"
#include "core/NotePicker.h"
#include "core/SignalGenerator.h"
#include <cmath>
#include <iostream>


// Calculate frequency of a note in the central octave using the equal-tone
// temperament scale
float hertzFromNumber(int semitoneNumber)
{
	return 440 * pow(2, (semitoneNumber-9)/12.0);
}

int main(int, char* [])
{
	// Pick an int between 0 and 11 which is a note in the central octave.
	NotePicker picker;
	int noteIndex = picker.pickIndex();

	// Define discrete points of a sine wave and create a reader for them
	const auto samplingFrequency = 44100;
	const auto lowestFrequency = 16;
	SignalGenerator generator(samplingFrequency, lowestFrequency);
	auto reader = generator.generate(hertzFromNumber(noteIndex));

	// Create a player that will use the sine wave of the reader
	const auto duration = 1;
	const auto bufferSize = 512;
	AudioPlayer player(reader, duration, samplingFrequency, bufferSize);


	// Play music notes and scales
	std::cout << "Some random note: " << picker.note(noteIndex) << '\n';
	player.play();

	noteIndex = picker.pickIndex();
	reader.setStep(hertzFromNumber(noteIndex));
	std::cout << "Another random note: " << picker.note(noteIndex) << '\n';
	player.play();

	std::cout << "C Major!" << '\n';
	player.duration = 0.2;
	unsigned int scale[8] = {0, 2, 4, 5, 7, 9, 11, 12};
	for (int i = 0; i < 8; ++i) {
		reader.setStep(hertzFromNumber(scale[i]));
		player.play();
	}

	std::cout << "Whole tone scale!!" << '\n';
	player.duration = 0.13;
	unsigned int scale2[21] = {2, 4, 6, 8, 10, 12, 14, 12, 10, 8, 12, 10,
		8, 10, 8, 6, 4, 8, 6 ,4, 2};
	for (int i = 0; i < 21; ++i) {
		reader.setStep(hertzFromNumber(scale2[i]));
		player.play();
	}
	reader.setStep(hertzFromNumber(4));
	player.duration = 1;
	player.play();


	return 0;
}
