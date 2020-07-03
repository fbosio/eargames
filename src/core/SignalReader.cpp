#include "SignalReader.h"

#include <iostream>


SignalReader::SignalReader(const std::valarray<float>& signal,
		float samplingFrequency) : signal(signal), step(1),
       	samplingFrequency(samplingFrequency), n(0)
{
}

SignalReader::SignalReader(const std::valarray<float>& signal, float frequency,
	       	float samplingFrequency) : signal(signal),
       	step((frequency/samplingFrequency)*signal.size()),
       	samplingFrequency(samplingFrequency), n(0)
{
}

float SignalReader::nextSample()
{
	n += step;
	if (n >= signal.size())
		n -= signal.size();


	return signal[n];
}

void SignalReader::setStep(float frequency)
{
	step = (frequency/samplingFrequency) * signal.size();
}
