#include "WavAudioInput.hh"
#include "CommandController.hh"
#include "PlugException.hh"
#include "CliComm.hh"
#include "serialize.hh"

using std::string;

namespace openmsx {

WavAudioInput::WavAudioInput(CommandController& commandController)
	: audioInputFilenameSetting(
		commandController, "audio-inputfilename",
		"filename of the file where the sampler reads data from",
		"audio-input.wav")
	, reference(EmuTime::zero)
{
	audioInputFilenameSetting.attach(*this);
}

WavAudioInput::~WavAudioInput()
{
	audioInputFilenameSetting.detach(*this);
}

void WavAudioInput::loadWave()
{
	wav = WavData(string(audioInputFilenameSetting.getString()));
}

const string& WavAudioInput::getName() const
{
	static const string name("wavinput");
	return name;
}

std::string_view WavAudioInput::getDescription() const
{
	return "Read .wav files. Can for example be used as input for "
		"samplers.";
}

void WavAudioInput::plugHelper(Connector& /*connector*/, EmuTime::param time)
{
	try {
		if (wav.getSize() == 0) {
			loadWave();
		}
	} catch (MSXException& e) {
		throw PlugException("Load of wave file failed: ", e.getMessage());
	}
	reference = time;
}

void WavAudioInput::unplugHelper(EmuTime::param /*time*/)
{
}

void WavAudioInput::update(const Setting& setting)
{
	(void)setting;
	assert(&setting == &audioInputFilenameSetting);
	try {
		if (isPluggedIn()) {
			loadWave();
		}
	} catch (MSXException& e) {
		// TODO proper error handling, message should go to console
		setting.getCommandController().getCliComm().printWarning(
			"Load of wave file failed: ", e.getMessage());
	}
}

int16_t WavAudioInput::readSample(EmuTime::param time)
{
	if (wav.getSize()) {
		unsigned pos = (time - reference).getTicksAt(wav.getFreq());
		return wav.getSample(pos);
	}
	return 0;
}

template<typename Archive>
void WavAudioInput::serialize(Archive& ar, unsigned /*version*/)
{
	ar.serialize("reference", reference);
	if (ar.isLoader()) {
		update(audioInputFilenameSetting);
	}
}
INSTANTIATE_SERIALIZE_METHODS(WavAudioInput);
REGISTER_POLYMORPHIC_INITIALIZER(Pluggable, WavAudioInput, "WavAudioInput");

} // namespace openmsx
