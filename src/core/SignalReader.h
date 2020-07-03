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
		 * @param frequency is the note fundamental frequency in Hz
		 * @param samplingFrequency how much samples are in one second
		 */
		SignalReader(const std::valarray<float>& signal,
				float frequency, float samplingFrequency);

		/**
		 * Create new reader.
		 *
		 * The step (i.e. the number of samples the reader skips) is set to 1.
		 * Hence, the note frequency is set to the lowest possible.
		 * Use setStep(float frequency) to change it.
		 * @param signal reference passed by a SignalGenerator
		 * @param samplingFrequency how much samples are in one second
		 */
		SignalReader(const std::valarray<float>& signal,
				float samplingFrequency); 
		/**
		 * Skip the number of samples given by the step.
		 *
		 * The step may be indirectly set by some frequency in the constructor SignalReader() or by means of the setStep() method.
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
