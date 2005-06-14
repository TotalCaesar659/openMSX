// $Id$

#ifndef DEBUGGER_HH
#define DEBUGGER_HH

#include <map>
#include <set>
#include <string>
#include "Command.hh"

namespace openmsx {

class Debuggable;
class CommandController;
class MSXCPU;

class Debugger
{
public:
	static Debugger& instance();

	void registerDebuggable  (const std::string& name, Debuggable& interface);
	void unregisterDebuggable(const std::string& name, Debuggable& interface);

	void setCPU(MSXCPU* cpu);

private:
	Debugger();
	~Debugger();

	Debuggable* getDebuggable(const std::string& name);
	void getDebuggables(std::set<std::string>& result) const;

	class DebugCmd : public Command {
	public:
		DebugCmd(Debugger& parent);
		virtual void execute(const std::vector<TclObject*>& tokens,
		                     TclObject& result);
		virtual std::string help(const std::vector<std::string>& tokens) const;
		virtual void tabCompletion(std::vector<std::string>& tokens) const;

	private:
		void list(TclObject& result);
		void desc(const std::vector<TclObject*>& tokens,
		          TclObject& result);
		void size(const std::vector<TclObject*>& tokens,
		          TclObject& result);
		void read(const std::vector<TclObject*>& tokens,
		          TclObject& result);
		void readBlock(const std::vector<TclObject*>& tokens,
		               TclObject& result);
		void write(const std::vector<TclObject*>& tokens,
		           TclObject& result);
		void writeBlock(const std::vector<TclObject*>& tokens,
		                TclObject& result);
		void setBreakPoint(const std::vector<TclObject*>& tokens,
		                   TclObject& result);
		void removeBreakPoint(const std::vector<TclObject*>& tokens,
		                      TclObject& result);
		void listBreakPoints(const std::vector<TclObject*>& tokens,
		                     TclObject& result);

		Debugger& parent;
	} debugCmd;

	std::map<std::string, Debuggable*> debuggables;
	CommandController& commandController;
	MSXCPU* cpu;
};

} // namespace openmsx

#endif
