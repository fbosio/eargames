#include "core/AudioPlayer.h"
#include "core/NotePicker.h"
#include "core/SignalGenerator.h"
#include <cmath>
#include <iostream>
#include <string>
#include <locale>


// Calculate frequency of a note in the central octave using the equal-tone
// temperament scale
float hertzFromNumber(int semitoneNumber)
{
	return 440 * pow(2, (semitoneNumber-9)/12.0);
}

// Trim spaces, keep 2 chars only and convert them to uppercase
void format(std::string& answer)
{
	const unsigned int answerLength = 2;
	char formatted[answerLength] = "";
	unsigned int charsFound = 0;
	for (unsigned int i = 0; i < answer.size(); ++i) {
		if (answer[i] != ' ') {
			formatted[charsFound] = std::toupper(answer[i]);
			++charsFound;
		}
		if (charsFound == answerLength)
			break;
	}
	answer = formatted;
}

int main(int, char* [])
{
	// Pick an int between 0 and 11 which is a note in the central octave.
	NotePicker picker;

	// Define discrete points of a sine wave and create a reader for them
	const auto samplingFrequency = 44100;
	const auto lowestFrequency = 16;
	SignalGenerator generator(samplingFrequency, lowestFrequency);
	auto reader = generator.generate();

	// Create a player that will use the sine wave of the reader
	const auto duration = 1.5;
	const auto bufferSize = 512;
	AudioPlayer player(reader, duration, samplingFrequency, bufferSize);


	// Start game
	std::cout << "\nGuess the note!\n";
	int noteIndex;
	std::string answer;
	std::string note;
	unsigned int correctAnswers = 0;
	unsigned int totalAnswers = 0;
	do {
		std::cout << "Listen\n";
		noteIndex = picker.pickIndex();
		reader.setStep(hertzFromNumber(noteIndex));
		player.play();
		std::cout << "\nWhich note is that?\n";
		std::cout << " C C# D D# E F F# G G# A A# B\n"
			<< "Answer (leave empty to quit): ";
		std::getline(std::cin, answer);
		format(answer);
		if (answer == "")
			break;
		note = picker.note(noteIndex);
		if (note == answer) {
			std::cout << "\nCorrect!\n";
			++correctAnswers;
		} else {
			std::cout << "\nIncorrect, that note is " << note
				<< '\n';
			player.play();
		}
		++totalAnswers;
	} while (true);

	std::cout << "Game over.\n Correct answers:\t" << correctAnswers
		<< "\n Total answers:\t" << totalAnswers << "\n Score:\t"
		<< 100.0f*correctAnswers/totalAnswers << "%\n";

	return 0;
}
