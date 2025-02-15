#include "YM2413.hh"
#include "YM2413Okazaki.hh"
#include "YM2413Burczynski.hh"
#include "DeviceConfig.hh"
#include "serialize.hh"
#include "cstd.hh"
#include "outer.hh"
#include <cmath>
#include <memory>

namespace openmsx {

// Debuggable

YM2413::Debuggable::Debuggable(
		MSXMotherBoard& motherBoard_, const std::string& name_)
	: SimpleDebuggable(motherBoard_, name_ + " regs", "MSX-MUSIC", 0x40)
{
}

byte YM2413::Debuggable::read(unsigned address)
{
	auto& ym2413 = OUTER(YM2413, debuggable);
	return ym2413.core->peekReg(address);
}

void YM2413::Debuggable::write(unsigned address, byte value, EmuTime::param time)
{
	auto& ym2413 = OUTER(YM2413, debuggable);
	ym2413.writeReg(address, value, time);
}


// YM2413

static std::unique_ptr<YM2413Core> createCore(const DeviceConfig& config)
{
	if (config.getChildDataAsBool("alternative", false)) {
		return std::make_unique<YM2413Burczynski::YM2413>();
	} else {
		return std::make_unique<YM2413Okazaki::YM2413>();
	}
}

static constexpr auto INPUT_RATE = unsigned(cstd::round(YM2413Core::CLOCK_FREQ / 72.0));

YM2413::YM2413(const std::string& name_, const DeviceConfig& config)
	: ResampledSoundDevice(config.getMotherBoard(), name_, "MSX-MUSIC", 9 + 5, INPUT_RATE, false)
	, core(createCore(config))
	, debuggable(config.getMotherBoard(), getName())
{
	registerSound(config);
}

YM2413::~YM2413()
{
	unregisterSound();
}

void YM2413::reset(EmuTime::param time)
{
	updateStream(time);
	core->reset();
}

void YM2413::writeReg(byte reg, byte value, EmuTime::param time)
{
	updateStream(time);
	core->writeReg(reg, value);
}

void YM2413::generateChannels(float** bufs, unsigned num)
{
	core->generateChannels(bufs, num);
}

float YM2413::getAmplificationFactorImpl() const
{
	return core->getAmplificationFactor();
}


template<typename Archive>
void YM2413::serialize(Archive& ar, unsigned /*version*/)
{
	ar.serializePolymorphic("ym2413", *core);
}
INSTANTIATE_SERIALIZE_METHODS(YM2413);

} // namespace openmsx
