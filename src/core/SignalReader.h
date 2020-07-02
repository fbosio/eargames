#include <valarray>

#pragma once


/**
 * Read samples of a reference signal using the given step.
 */
class SignalReader {
	public:
		/**
		 * Create new reader.
		 *
		 * @param signal reference passed by a SignalGenerator
		 * @param step the reader will skip this number of samples to read the next one
		 */
		SignalReader(const std::valarray<float>& signal,
				float frequency, float samplingFrequency);

		/**
		 * Skip the number of samples given by the step in SignalReader(const std::valarray<float>& signal, int step).
		 *
		 * @return The value of the signal
		 */
		float nextSample();

		/**
		 * Change the number of samples that the reader will skip.
		 * @param frequency new signal fundamental frequency in Hz.
		 */
		void setStep(float frequency);

	private:
		const std::valarray<float>& signal;
		int step;
		float samplingFrequency;
		unsigned int n;
};
