#include <valarray>
#include "SignalReader.h"


/**
 * Store samples of a generic signal.
 *
 * Call generate(float frequency, float amplitude) to get a particular signal.
 */
class SignalGenerator {
	public:
		/**
		 * Create a signal generator.
		 *
		 * Store a vector, which contains the signal.
		 * @param lowestFrequency lowest frequency of the signal in Hz
		 * @param samplingFrequency number of samples corresponding to one second
		 */
		SignalGenerator(float lowestFrequency, float samplingFrequency);

		/**
		 * Create a signal reader and give a reference of a new signal to it.
		 *
		 * The new signal equals the generic signal multiplied by the given amplitude.
		 * @param frequency fundamental frequency of the signal in Hz
		 * @param amplitude a float between 0 and 1
		 * @return The signal reader
		 */
		SignalReader generate(float frequency, float amplitude = 0.125f);

		SignalReader generate();

	private:
		float samplingFrequency;
		unsigned int samplesNumber;
		std::valarray<float> signal;
		std::valarray<float> amplifiedSignal;
};
