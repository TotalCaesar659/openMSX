// $Id$

#ifndef __WAVAUDIOINPUT_HH__
#define __WAVAUDIOINPUT_HH__

#include <SDL/SDL.h>
#include "AudioInputDevice.hh"
#include "Settings.hh"
#include "EmuTime.hh"


namespace openmsx {

class WavAudioInput : public AudioInputDevice, private SettingListener
{
public:
	WavAudioInput();
	virtual ~WavAudioInput();

	// AudioInputDevice
	virtual const string &getName() const;
	virtual void plug(Connector *connector, const EmuTime &time)
		throw(PlugException);
	virtual void unplug(const EmuTime &time);
	virtual short readSample(const EmuTime &time);

private:
	void freeWave();
	void loadWave() throw(MSXException);
	void update(const SettingLeafNode *setting);

	int length;
	Uint8 *buffer;
	int freq;
	EmuTime reference;
	bool plugged;

	FilenameSetting audioInputFilenameSetting;
};

} // namespace openmsx

#endif
