// $Id$

#ifndef __MSXROM16KB_HH__
#define __MSXROM16KB_HH__

#include "MSXMemDevice.hh"
#include "MSXRom.hh"
#include "MSXDevice.hh"
#include "EmuTime.hh"
#include "msxconfig.hh"

class MSXRom16KB : public MSXMemDevice, public MSXRom
{
	public:
		/**
		 * Constructor
		 */
		MSXRom16KB(MSXConfig::Device *config);

		/**
		 * Destructor
		 */
		~MSXRom16KB();
		
		// don't forget you inherited from MSXDevice
		void init();
		
		byte readMem(word address, EmuTime &time);
};
#endif
