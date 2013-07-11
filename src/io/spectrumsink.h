#ifndef SPECTRUMSINK_H_
#define SPECTRUMSINK_H_

#include <vector>
#include <string>
#include <fftw3.h>
#include <pthread.h>

#include "samplesink.h"

#define DEFAULT_FFT_SIZE		512

using namespace std;

/* NOTE: Using single-precision version of FFTW since e.g. the Pi doesn't
 * have a double-precision FPU.  The incoming interleaved I/Q samples are
 * copied directly to the FFTW buffer, so if using double-precision is
 * desired then the entire app needs to be updated to pass around doubles
 * instead of floats! */

class SpectrumSink : public SampleSink
{
public:
	SpectrumSink(const string &name = "<undefined>");
	virtual ~SpectrumSink();

	unsigned int fftSize() const { return _fftSize; }
	void setFftSize(unsigned int size);

	void getSpectrum(float *magnitudes); // FIXME: Better for clients to register for a callback?
private:
	bool init();
	void deinit();
	bool process(const vector<sample_t> &inBuffer, vector<sample_t> &outBuffer);

	fftwf_complex *inbuf;
	fftwf_complex *outbuf;
	fftwf_plan p;
	unsigned int inoffset;
	
	pthread_mutex_t mutex;
	
	unsigned int _fftSize;
	vector<float> window;
};

#endif /* SPECTRUMSINK_H_ */
