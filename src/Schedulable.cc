// $Id$

#include "Schedulable.hh"
#include "Scheduler.hh"

namespace openmsx {

Schedulable::Schedulable(Scheduler& scheduler_)
	: scheduler(scheduler_)
{
}

Schedulable::~Schedulable()
{
}

void Schedulable::setSyncPoint(const EmuTime& timestamp, int userData) {
	scheduler.setSyncPoint(timestamp, *this, userData);
}

void Schedulable::removeSyncPoint(int userData) {
	scheduler.removeSyncPoint(*this, userData);
}

bool Schedulable::pendingSyncPoint(int userData) {
	return scheduler.pendingSyncPoint(*this, userData);
}

Scheduler& Schedulable::getScheduler() const
{
	return scheduler;
}

} // namespace openmsx
