#include <array>
#include <random>


/**
 * Random note picker.
 *
 * Call pickIndex() to get a random note index.
 * Call note(unsigned int index) to retrieve the corresponding note name.
 */
class NotePicker {
	public:
		NotePicker();

		/*
		 * @return A random integer between 0 and 11.
		 */
		unsigned int pickIndex();

		/*
		 * Return the note name, given its index.
		 *
		 * Notes are ordered in such a way that
		 *  note(0) is "C"
		 *  note(1) is "C#"
		 *  note(2) is "D"
		 * and so on. The accidental is always sharp.
		 * @param index An integer between 0 and 11.
		 * @return The note name with sharp accidental, if present.
		 */
		char* note(unsigned int index);

	private:
		std::array<char[3], 12> notes;
		std::uniform_int_distribution<int> distribution;
		unsigned int seed;
};
