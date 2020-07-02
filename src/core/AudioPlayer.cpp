#include "AudioPlayer.h"
#include "portaudiocpp/PortAudioCpp.hxx"


AudioPlayer::AudioPlayer(SignalReader& reader, float duration,
	       	float samplingFrequency, unsigned int bufferSize)
	: reader(reader), duration(duration),
       	sys(portaudio::System::instance())
{
	outParams.setDevice(sys.defaultOutputDevice());
	outParams.setNumChannels(2);
	outParams.setSampleFormat(portaudio::FLOAT32, false);
	auto latency = sys.defaultOutputDevice().defaultLowOutputLatency();
	outParams.setSuggestedLatency(latency);
	outParams.setHostApiSpecificStreamInfo(nullptr);
	portaudio::StreamParameters params(
			portaudio::DirectionSpecificStreamParameters::null(),
			outParams, samplingFrequency, bufferSize, paClipOff);
	stream.open(params, *this, &AudioPlayer::memFun);
}

void AudioPlayer::play()
{
	stream.start();
	sys.sleep(duration*1000);
	stream.stop();
}

int AudioPlayer::memFun(const void *inputBuffer, void *outputBuffer,
	       	unsigned long framesPerBuffer,
	       	const PaStreamCallbackTimeInfo *timeInfo,
	       	PaStreamCallbackFlags statusFlags)
{
	if (outputBuffer != nullptr) {
		float** out = static_cast<float**>(outputBuffer);

		for (unsigned int i = 0; i < framesPerBuffer; ++i) {
			float sample = reader.nextSample();
			out[0][i] = sample;
			out[1][i] = sample;
		}
	}

	return paContinue;
}
