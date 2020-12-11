/*
 * AudioDriver.cc
 *
 *  Created on: 3 ����. 2020 �.
 *      Author: prepod
 */

#include "AudioDriver.h"
#include <iostream>

static void audio_callback(void * userdata, Uint8 * stream, int len)
{
//	std::cout << len << std::endl;
	short * buffer = reinterpret_cast<short*>(stream);
	int samples = len / sizeof(short);
	AudioDriver * ad = reinterpret_cast<AudioDriver *>(userdata);

	ad->callback(buffer, samples);

}

AudioDriver::AudioDriver()
{
	_spec.channels = 1;
	_spec.format = AUDIO_S16;
	_spec.freq = AUDIO_SAMPLING_FREQUENCY;
	_spec.callback = audio_callback;
	_spec.userdata = this;

	_id = SDL_OpenAudioDevice(nullptr, 0, &_spec, &_obtained_spec, 0);
}

AudioDriver::~AudioDriver()
{
	pause();
	SDL_CloseAudioDevice(_id);
}

void AudioDriver::callback(short * buffer, int samples)
{
	for (int i = 0; i < samples; i++)
	{
		std::cout << samples << std::endl;
		buffer[i] = short(_source ->next_sample() * _master_volume);
	}
}
