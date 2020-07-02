#include "portaudiocpp/PortAudioCpp.hxx"
#include "SignalReader.h"


/*
 * The audio player gets a SignalReader and some data to setup portaudio.
 * Use play() to play the signal stored in the reader.
 */
class AudioPlayer {
	public:
		/**
		 * Create a player and initialize portaudio.
		 * @param reader reference to the reader that is reading the signal
		 * @param duration amount of playing time in seconds
		 * @param samplingFrequency number of samples in one second
		 * @param bufferSize number of samples handled by the buffer
		 */
		AudioPlayer(SignalReader& reader, float duration, float samplingFrequency, unsigned int bufferSize);

		/*
		 * Play the signal of the reader.
		 */
		void play();

		/** Amount of playing time in seconds. */
		float duration;
	private:
		SignalReader& reader;
		portaudio::AutoSystem autoSys;
		portaudio::System& sys;
		portaudio::DirectionSpecificStreamParameters outParams;
		portaudio::MemFunCallbackStream<AudioPlayer> stream;
		int memFun(const void *inputBuffer, void *outputBuffer,
	       	unsigned long framesPerBuffer,
	       	const PaStreamCallbackTimeInfo *timeInfo,
	       	PaStreamCallbackFlags statusFlags);
};
