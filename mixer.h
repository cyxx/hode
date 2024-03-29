
#ifndef MIXER_H__
#define MIXER_H__

#include "intern.h"

struct MixerChannel {
	const int16_t *ptr;
	const int16_t *end;
	int panL;
	int panR;
	uint8_t panType;
	bool stereo;
};

struct Mixer {

	static const int kMixingQueueSize = 32;

	void (*_lock)(int);

	MixerChannel _mixingQueue[kMixingQueueSize];
	int _mixingQueueSize;

	Mixer();
	~Mixer();

	void queue(const int16_t *ptr, const int16_t *end, int panType, int panL, int panR, bool stereo);

	void mix(int16_t *buf, int len);
};

struct MixerLock {
	Mixer *_mix;
	MixerLock(Mixer *mix)
		: _mix(mix) {
		_mix->_lock(1);
	}
	~MixerLock() {
		_mix->_lock(0);
	}
};

#endif
