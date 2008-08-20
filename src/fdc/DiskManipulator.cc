// $Id$

#include "DiskManipulator.hh"
#include "DiskContainer.hh"
#include "DiskChanger.hh"
#include "MSXtar.hh"
#include "DSKDiskImage.hh"
#include "CommandController.hh"
#include "CommandException.hh"
#include "MSXMotherBoard.hh"
#include "Reactor.hh"
#include "File.hh"
#include "Filename.hh"
#include "FileContext.hh"
#include "FileException.hh"
#include "FileOperations.hh"
#include "SectorBasedDisk.hh"
#include "StringOp.hh"
#include <cassert>
#include <ctype.h>

using std::set;
using std::string;
using std::vector;

namespace openmsx {

DiskManipulator::DiskManipulator(CommandController& commandController)
	: SimpleCommand(commandController, "diskmanipulator")
{
	virtualDrive.reset(new DiskChanger("virtual_drive", commandController,
	                                   *this, NULL));
}

DiskManipulator::~DiskManipulator()
{
	virtualDrive.reset();

	assert(diskImages.empty()); // all DiskContainers must be unregistered
}

string DiskManipulator::getMachinePrefix() const
{
	string id = getCommandController().getReactor().getMachineID();
	return id.empty() ? id : id + "::";
}

void DiskManipulator::registerDrive(DiskContainer& drive, MSXMotherBoard* board)
{
	assert(findDriveSettings(drive) == diskImages.end());
	DriveSettings driveSettings;
	driveSettings.drive = &drive;
	string prefix = board ? (board->getMachineID() + "::") : "";
	driveSettings.driveName = prefix + drive.getContainerName();
	driveSettings.partition = 0;
	for (int i = 0; i < 31; ++i) {
		driveSettings.workingDir[i] = "/";
	}
	diskImages.push_back(driveSettings);
}

void DiskManipulator::unregisterDrive(DiskContainer& drive)
{
	DiskImages::iterator it = findDriveSettings(drive);
	assert(it != diskImages.end());
	diskImages.erase(it);
}

DiskManipulator::DiskImages::iterator DiskManipulator::findDriveSettings(
	DiskContainer& drive)
{
	for (DiskImages::iterator it = diskImages.begin();
	     it != diskImages.end(); ++it) {
		if (it->drive == &drive) {
			return it;
		}
	}
	return diskImages.end();
}

DiskManipulator::DiskImages::iterator DiskManipulator::findDriveSettings(
	const string& name)
{
	for (DiskImages::iterator it = diskImages.begin();
	     it != diskImages.end(); ++it) {
		if (it->driveName == name) {
			return it;
		}
	}
	return diskImages.end();
}

DiskManipulator::DriveSettings& DiskManipulator::getDriveSettings(
	const string& diskname)
{
	// first split of the end numbers if present
	// these will be used as partition indication
	string::size_type pos = diskname.find("::");
	pos = diskname.find_first_of("0123456789", ((pos != string::npos) ? pos : 0));
	string tmp = diskname.substr(0, pos);

	DiskImages::iterator it = findDriveSettings(tmp);
	if (it == diskImages.end()) {
		it = findDriveSettings(getMachinePrefix() + tmp);
		if (it == diskImages.end()) {
			throw CommandException("Unknown drive: "  + tmp);
		}
	}

	it->partition = 0;
	if (pos != string::npos) {
		string num = diskname.substr(pos);
		int i = strtol(num.c_str(), NULL, 10);
		// check number in range
		if (i <= 0 || i > 31) {
			throw CommandException(
				"Invalid partition specified (must be 1-31).");
		}
		// check whether drive really have this partition
		bool hasPartition = false;
		try {
			SectorAccessibleDisk* sectorDisk =
				it->drive->getSectorAccessibleDisk();
			MSXtar workhorse(*sectorDisk);
			if (workhorse.hasPartition(i - 1)) {
				hasPartition = true;
			}
		} catch (MSXException& e) {
			// ignore
		}
		if (!hasPartition) {
			throw CommandException("Drive " + tmp +
			                       " does not have a partition " + num);
		}
		// ok
		it->partition = i - 1;
	}
	return *it;
}

SectorAccessibleDisk& DiskManipulator::getDisk(const DriveSettings& driveData)
{
	SectorAccessibleDisk* disk = driveData.drive->getSectorAccessibleDisk();
	if (!disk) {
		// not a SectorBasedDisk
		throw CommandException("Unsupported disk type.");
	}
	return *disk;
}


string DiskManipulator::execute(const vector<string>& tokens)
{
	string result;
	if (tokens.size() == 1) {
		throw CommandException("Missing argument");

	} else if ((tokens.size() != 4 && ( tokens[1] == "savedsk"
	                                || tokens[1] == "mkdir"))
	        || (tokens.size() != 3 && (tokens[1] == "dir"
	                                || tokens[1] == "format"))
	        || ((tokens.size() < 3 || tokens.size() > 4) &&
	                                  (tokens[1] == "chdir"))
	        || (tokens.size() < 4 && ( tokens[1] == "export"
					|| tokens[1] == "import"))
	        || (tokens.size() <= 3 && (tokens[1] == "create"))) {
		throw CommandException("Incorrect number of parameters");

	} else if ( tokens[1] == "export" ) {
		if (!FileOperations::isDirectory(tokens[3])) {
			throw CommandException(tokens[3] + " is not a directory");
		}
		DriveSettings& settings = getDriveSettings(tokens[2]);
		vector<string> lists(tokens.begin() + 4, tokens.end());
		exprt(settings, tokens[3], lists);

	} else if (tokens[1] == "import" ) {
		DriveSettings& settings = getDriveSettings(tokens[2]);
		vector<string> lists(tokens.begin() + 3, tokens.end());
		result = import(settings, lists);

	} else if (tokens[1] == "savedsk") {
		DriveSettings& settings = getDriveSettings(tokens[2]);
		savedsk(settings, tokens[3]);

	} else if (tokens[1] == "chdir") {
		DriveSettings& settings = getDriveSettings(tokens[2]);
		if (tokens.size() == 3) {
			result += "Current directory: " +
			          settings.workingDir[settings.partition];
		} else {
			chdir(settings, tokens[3], result);
		}

	} else if (tokens[1] == "mkdir") {
		DriveSettings& settings = getDriveSettings(tokens[2]);
		mkdir(settings, tokens[3]);

	} else if (tokens[1] == "create") {
		create(tokens);

	} else if (tokens[1] == "format") {
		DriveSettings& settings = getDriveSettings(tokens[2]);
		format(settings);

	} else if (tokens[1] == "dir") {
		DriveSettings& settings = getDriveSettings(tokens[2]);
		dir(settings, result);

	} else {
		throw CommandException("Unknown subcommand: " + tokens[1]);
	}
	return result;
}

string DiskManipulator::help(const vector<string>& tokens) const
{
	string helptext;
	if (tokens.size() >= 2) {
	  if (tokens[1] == "import" ) {
	  helptext=
	    "diskmanipulator import <disk name> <host directory|host file>\n"
	    "Import all files and subdirs from the host OS as specified into the\n"
	    "<disk name> in the current MSX subdirectory as was specified with the\n"
	    "last chdir command.\n";
	  } else if (tokens[1] == "export" ) {
	  helptext=
	    "diskmanipulator export <disk name> <host directory>\n"
	    "Extract all files and subdirs from the MSX subdirectory specified with\n"
	    "the chdir command from <disk name> to the host OS in <host directory>.\n";
	  } else if (tokens[1] == "savedsk") {
	  helptext=
	    "diskmanipulator savedsk <disk name> <dskfilename>\n"
	    "This saves the complete drive content to <dskfilename>, it is not possible to\n"
	    "save just one partition. The main purpose of this command is to make it\n"
	    "possible to save a 'ramdsk' into a file and to take 'live backups' of\n"
	    "dsk-files in use.\n";
	  } else if (tokens[1] == "chdir") {
	  helptext=
	    "diskmanipulator chdir <disk name> <MSX directory>\n"
	    "Change the working directory on <disk name>. This will be the\n"
	    "directory were the 'import', 'export' and 'dir' commands will\n"
	    "work on.\n"
	    "In case of a partitioned drive, each partition has its own\n"
	    "working directory.\n";
	  } else if (tokens[1] == "mkdir") {
	  helptext=
	    "diskmanipulator mkdir <disk name> <MSX directory>\n"
	    "This creates the directory on <disk name>. If needed, all missing\n"
	    "parent directories are created at the same time. Accepts both\n"
	    "absolute and relative pathnames.\n";
	  } else if (tokens[1] == "create") {
	  helptext=
	    "diskmanipulator create <dskfilename> <size/option> [<size/option>...]\n"
	    "Creates a formatted dsk file with the given size.\n"
	    "If multiple sizes are given, a partitioned disk image will\n"
	    "be created with each partition having the size as indicated. By\n"
	    "default the sizes are expressed in kilobyte, add the postfix M\n"
	    "for megabyte.\n";
	  } else if (tokens[1] == "format") {
	  helptext=
	    "diskmanipulator format <disk name>\n"
	    "formats the current (partition on) <disk name> with a regular\n"
	    "FAT12 MSX filesystem with an MSX-DOS2 boot sector.\n";
	  } else if (tokens[1] == "dir") {
	  helptext=
	    "diskmanipulator dir <disk name>\n"
	    "Shows the content of the current directory on <disk name>\n";
	  } else {
	  helptext = "Unknown diskmanipulator subcommand: " + tokens[1];
	  }
	} else {
	  helptext=
	    "diskmanipulator create <fn> <sz> [<sz> ...]  : create a formatted dsk file with name <fn>\n"
	    "                                               having the given (partition) size(s)\n"
	    "diskmanipulator savedsk <disk name> <fn>     : save <disk name> as dsk file named as <fn>\n"
	    "diskmanipulator format <disk name>           : format (a partition) on <disk name>\n"
	    "diskmanipulator chdir <disk name> <MSX dir>  : change directory on <disk name>\n"
	    "diskmanipulator mkdir <disk name> <MSX dir>  : create directory on <disk name>\n"
	    "diskmanipulator dir <disk name>              : long format file listing of current\n"
	    "                                               directory on <disk name>\n"
	    "diskmanipulator import <disk> <dir/file> ... : import files and subdirs from <dir/file>\n"
	    "diskmanipulator export <disk> <host dir>     : export all files on <disk> to <host dir>\n"
	    "For more info use 'help diskmanipulator <subcommand>'.\n";
	}
	return helptext;
}

void DiskManipulator::tabCompletion(vector<string>& tokens) const
{
	if (tokens.size() == 2) {
		set<string> cmds;
		cmds.insert("import");
		cmds.insert("export");
		cmds.insert("savedsk");
		cmds.insert("dir");
		cmds.insert("create");
		cmds.insert("format");
		cmds.insert("chdir");
		cmds.insert("mkdir");
		completeString(tokens, cmds);

	} else if ((tokens.size() == 3) && (tokens[1] == "create")) {
		UserFileContext context;
		completeFileName(getCommandController(), tokens, context);

	} else if (tokens.size() == 3) {
		set<string> names;
		for (DiskImages::const_iterator it = diskImages.begin();
		     it != diskImages.end(); ++it) {
			string name1 = it->driveName; // with prexix
			string name2 = it->drive->getContainerName(); // without prefix
			names.insert(name1);
			names.insert(name2);
			// if it has partitions then we also add the partition
			// numbers to the autocompletion
			SectorAccessibleDisk* sectorDisk =
				it->drive->getSectorAccessibleDisk();
			if (sectorDisk != NULL) {
				try {
					MSXtar workhorse(*sectorDisk);
					for (int i = 0; i < 31; ++i) {
						if (workhorse.hasPartition(i)) {
							names.insert(name1 + StringOp::toString(i + 1));
							names.insert(name2 + StringOp::toString(i + 1));
						}
					}
				} catch (MSXException& e) {
					// ignore
				}
			}
		}
		completeString(tokens, names);

	} else if (tokens.size() >= 4) {
		if ((tokens[1] == "savedsk") ||
		    (tokens[1] == "import")  ||
		    (tokens[1] == "export")) {
			UserFileContext context;
			completeFileName(getCommandController(), tokens, context);
		} else if (tokens[1] == "create") {
			set<string> cmds;
			cmds.insert("360");
			cmds.insert("720");
			cmds.insert("32M");
			completeString(tokens, cmds);
		}
	}
}

void DiskManipulator::savedsk(const DriveSettings& driveData,
                              const string& filename)
{
	SectorAccessibleDisk& disk = getDisk(driveData);
	unsigned nrsectors = disk.getNbSectors();
	byte buf[SectorBasedDisk::SECTOR_SIZE];
	File file(filename, File::CREATE);
	for (unsigned i = 0; i < nrsectors; ++i) {
		disk.readSector(i, buf);
		file.write(buf, SectorBasedDisk::SECTOR_SIZE);
	}
}

void DiskManipulator::create(const vector<string>& tokens)
{
	vector<unsigned> sizes;
	unsigned totalSectors = 0;
	for (unsigned i = 3; i < tokens.size(); ++i) {
		char* q;
		int sectors = strtol(tokens[i].c_str(), &q, 0);
		int scale = 1024; // default is kilobytes
		if (*q) {
			if ((q == tokens[i].c_str()) || *(q + 1)) {
				throw CommandException(
					"Invalid size: " + tokens[i]);
			}
			switch (tolower(*q)) {
				case 'b':
					scale = 1;
					break;
				case 'k':
					scale = 1024;
					break;
				case 'm':
					scale = 1024 * 1024;
					break;
				case 's':
					scale = SectorBasedDisk::SECTOR_SIZE;
					break;
				default:
					throw CommandException(
					    string("Invalid postfix: ") + q);
			}
		}
		sectors = (sectors * scale) / SectorBasedDisk::SECTOR_SIZE;
		// for a 32MB disk or greater the sectors would be >= 65536
		// since MSX use 16 bits for this, in case of sectors = 65536
		// the truncated word will be 0 -> formatted as 320 Kb disk!
		if (sectors > 65535) sectors = 65535; // this is the max size for fat12 :-)

		// TEMP FIX: the smallest bootsector we create in MSXtar is for
		// a normal single sided disk.
		// TODO: MSXtar must be altered and this temp fix must be set to
		// the real smallest dsk possible (= bootsecor + minimal fat +
		// minial dir + minimal data clusters)
		if (sectors < 720) sectors = 720;

		sizes.push_back(sectors);
		totalSectors += sectors;
	}
	if (sizes.size() > 1) {
		// extra sector for partition table
		++totalSectors;
	}

	// create file with correct size
	try {
		File file(tokens[2], File::CREATE);
		file.truncate(totalSectors * SectorBasedDisk::SECTOR_SIZE);
	} catch (FileException& e) {
		throw CommandException("Couldn't create image: " + e.getMessage());
	}

	// initialize (create partition tables and format partitions)
	Filename filename(tokens[2]);
	DSKDiskImage image(filename);
	MSXtar workhorse(image);
	workhorse.createDiskFile(sizes);
}

void DiskManipulator::format(DriveSettings& driveData)
{
	MSXtar workhorse(getDisk(driveData));
	try {
		if (workhorse.hasPartitionTable()) {
			assert(workhorse.hasPartition(driveData.partition));
			workhorse.usePartition(driveData.partition);
		}
	} catch (MSXException& e) {
		// ignore, because only the partition selection part is
		// interesting for the format command, so ignore other
		// errors (see MSXtar code)
	}
	workhorse.format();
	driveData.workingDir[driveData.partition] = "/";
}

void DiskManipulator::restoreCWD(MSXtar& workhorse, DriveSettings& driveData)
{
	if (!workhorse.hasPartitionTable()) {
		workhorse.usePartition(0); //read the bootsector
	} else {
		assert(workhorse.hasPartition(driveData.partition));
		workhorse.usePartition(driveData.partition);
	}
	try {
		workhorse.chdir(driveData.workingDir[driveData.partition]);
	} catch (MSXException& e) {
		driveData.workingDir[driveData.partition] = "/";
		throw CommandException(
		    "Directory " + driveData.workingDir[driveData.partition] +
		    " doesn't exist anymore. Went back to root "
		    "directory. Command aborted, please retry.");
	}
}

void DiskManipulator::dir(DriveSettings& driveData, string& result)
{
	MSXtar workhorse(getDisk(driveData));
	restoreCWD(workhorse, driveData);
	result += workhorse.dir();
}

void DiskManipulator::chdir(DriveSettings& driveData,
                            const string& filename, string& result)
{
	MSXtar workhorse(getDisk(driveData));
	restoreCWD(workhorse, driveData);
	try {
		workhorse.chdir(filename);
	} catch (MSXException& e) {
		throw CommandException("chdir failed: " + e.getMessage());
	}
	// TODO clean-up this temp hack, used to enable relative paths
	string& cwd = driveData.workingDir[driveData.partition];
	if (filename.find_first_of("/") == 0) {
		cwd = filename;
	} else {
		if (*cwd.rbegin() != '/') cwd += '/';
		cwd += filename;
	}
	result += "New working directory: " + cwd;
}

void DiskManipulator::mkdir(DriveSettings& driveData, const string& filename)
{
	MSXtar workhorse(getDisk(driveData));
	restoreCWD(workhorse, driveData);
	try {
		workhorse.mkdir(filename);
	} catch (MSXException& e) {
		throw CommandException(e.getMessage());
	}
}

string DiskManipulator::import(DriveSettings& driveData,
                             const vector<string>& lists)
{
	string messages;
	MSXtar workhorse(getDisk(driveData));
	restoreCWD(workhorse, driveData);

	for (vector<string>::const_iterator it = lists.begin();
	     it != lists.end(); ++it) {
		vector<string> list;
		getCommandController().splitList(*it, list);

		for (vector<string>::const_iterator it = list.begin();
		     it != list.end(); ++it) {
			try {
				if (FileOperations::isDirectory(*it)) {
					messages += workhorse.addDir(*it);
				} else if (FileOperations::isRegularFile(*it)) {
					messages += workhorse.addFile(*it);
				} else {
					// ignore other stuff (sockets, device nodes, ..)
					messages += "Ignoring " + *it + '\n';
				}
			} catch (MSXException& e) {
				throw CommandException(e.getMessage());
			}
		}
	}
	return messages;
}

void DiskManipulator::exprt(DriveSettings& driveData, const string& dirname,
                            const vector<string>& lists)
{
	try {
		MSXtar workhorse(getDisk(driveData));
		restoreCWD(workhorse, driveData);
		if (lists.empty()) {
			// export all
			workhorse.getDir(dirname);
		} else {
			for (vector<string>::const_iterator it = lists.begin();
			     it != lists.end(); ++it) {
				workhorse.getItemFromDir(dirname, *it);
			}
		}
	} catch (MSXException& e) {
		throw CommandException(e.getMessage());
	}
}

} // namespace openmsx
