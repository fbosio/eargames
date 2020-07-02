#include "SignalGenerator.h"
#include <cmath>
#include <iostream>


SignalGenerator::SignalGenerator(float samplingFrequency, float lowestFrequency)
	: samplingFrequency(samplingFrequency),
	  samplesNumber(samplingFrequency/lowestFrequency),
	  signal(samplesNumber),
	  amplifiedSignal(samplesNumber)
{
	signal.resize(samplesNumber);
	const double tau = 6.28318530717958;  // 2 * pi
	for (unsigned int n = 0; n < samplesNumber; ++n) {
		signal[n] = sin(tau*n/samplesNumber);
	}
}

SignalReader SignalGenerator::generate(float frequency, float amplitude)
{
	amplifiedSignal = amplitude*signal;
	SignalReader reader(amplifiedSignal, frequency, samplingFrequency);

	return reader;
}
