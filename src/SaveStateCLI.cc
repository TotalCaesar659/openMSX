#include "SaveStateCLI.hh"
#include "CommandLineParser.hh"
#include "TclObject.hh"

using std::string;

namespace openmsx {

SaveStateCLI::SaveStateCLI(CommandLineParser& parser_)
	: parser(parser_)
{
	parser.registerOption("-savestate", *this);
	parser.registerFileType("oms", *this);
}

void SaveStateCLI::parseOption(const string& option, span<string>& cmdLine)
{
	parseFileType(getArgument(option, cmdLine), cmdLine);
}

std::string_view SaveStateCLI::optionHelp() const
{
	return "Load savestate and start emulation from there";
}

void SaveStateCLI::parseFileType(const string& filename,
                                 span<string>& /*cmdLine*/)
{
	// TODO: this is basically a C++ version of a part of savestate.tcl.
	// Can that be improved?
	auto& interp = parser.getInterpreter();

	TclObject command1 = makeTclList("restore_machine", filename);
	auto newId = command1.executeCommand(interp);

	TclObject command2 = makeTclList("machine");
	auto currentId = command2.executeCommand(interp);

	if (!currentId.empty()) {
		TclObject command3 = makeTclList("delete_machine", currentId);
		command3.executeCommand(interp);
	}

	TclObject command4 = makeTclList("activate_machine", newId);
	command4.executeCommand(interp);
}

std::string_view SaveStateCLI::fileTypeHelp() const
{
	return "openMSX savestate";
}

} // namespace openmsx
