#include "Completer.hh"
#include "Interpreter.hh"
#include "InterpreterOutput.hh"
#include "FileContext.hh"
#include "FileOperations.hh"
#include "ReadDir.hh"
#include "ranges.hh"
#include "stl.hh"
#include "strCat.hh"
#include "stringsp.hh"
#include "TclObject.hh"
#include "utf8_unchecked.hh"
#include "view.hh"

using std::vector;
using std::string;
using std::string_view;

namespace openmsx {

InterpreterOutput* Completer::output = nullptr;


Completer::Completer(string_view name_)
	: name(std::string(name_)) // TODO take std::string parameter instead and move()
{
}

static bool formatHelper(const vector<string_view>& input, size_t columnLimit,
                         vector<string>& result)
{
	size_t column = 0;
	auto it = begin(input);
	do {
		size_t maxcolumn = column;
		for (size_t i = 0; (i < result.size()) && (it != end(input));
		     ++i, ++it) {
			auto curSize = utf8::unchecked::size(result[i]);
			strAppend(result[i], spaces(column - curSize), *it);
			maxcolumn = std::max(maxcolumn,
			                     utf8::unchecked::size(result[i]));
			if (maxcolumn > columnLimit) return false;
		}
		column = maxcolumn + 2;
	} while (it != end(input));
	return true;
}

static vector<string> format(const vector<string_view>& input, size_t columnLimit)
{
	vector<string> result;
	for (size_t lines = 1; lines < input.size(); ++lines) {
		result.assign(lines, string());
		if (formatHelper(input, columnLimit, result)) {
			return result;
		}
	}
	append(result, input);
	return result;
}

vector<string> Completer::formatListInColumns(const vector<string_view>& input)
{
	return format(input, output->getOutputColumns() - 1);
}

bool Completer::equalHead(string_view s1, string_view s2, bool caseSensitive)
{
	if (s2.size() < s1.size()) return false;
	if (caseSensitive) {
		return memcmp(s1.data(), s2.data(), s1.size()) == 0;
	} else {
		return strncasecmp(s1.data(), s2.data(), s1.size()) == 0;
	}
}

bool Completer::completeImpl(string& str, vector<string_view> matches,
                             bool caseSensitive)
{
	assert(ranges::all_of(matches, [&](auto& m) {
		return equalHead(str, m, caseSensitive);
	}));

	if (matches.empty()) {
		// no matching values
		return false;
	}
	if (matches.size() == 1) {
		// only one match
		str = matches.front();
		return true;
	}

	// Sort and remove duplicates.
	//  For efficiency it's best if the list doesn't contain duplicates to
	//  start with. Though sometimes this is hard to avoid. E.g. when doing
	//  filename completion + some extra allowed strings and one of these
	//  extra strings is the same as one of the filenames.
	ranges::sort(matches);
	matches.erase(ranges::unique(matches), end(matches));

	bool expanded = false;
	while (true) {
		auto it = begin(matches);
		if (str.size() == it->size()) {
			// match is as long as first word
			goto out; // TODO rewrite this
		}
		// expand with one char and check all strings
		auto b = begin(*it);
		auto e = b + str.size();
		utf8::unchecked::next(e); // one more utf8 char
		string_view string2(&*b, e - b);
		for (/**/; it != end(matches); ++it) {
			if (!equalHead(string2, *it, caseSensitive)) {
				goto out; // TODO rewrite this
			}
		}
		// no conflict found
		str = string2;
		expanded = true;
	}
	out:
	if (!expanded && output) {
		// print all possibilities
		for (auto& line : formatListInColumns(matches)) {
			output->output(line);
		}
	}
	return false;
}

void Completer::completeFileName(vector<string>& tokens,
                                 const FileContext& context)
{
	completeFileNameImpl(tokens, context, vector<string_view>());
}

void Completer::completeFileNameImpl(vector<string>& tokens,
                                     const FileContext& context,
                                     vector<string_view> matches)
{
	string& filename = tokens.back();
	filename = FileOperations::expandTilde(filename);
	filename = FileOperations::expandCurrentDirFromDrive(filename);
	string_view dirname1 = FileOperations::getDirName(filename);

	vector<string> paths;
	if (FileOperations::isAbsolutePath(filename)) {
		paths.emplace_back();
	} else {
		paths = context.getPaths();
	}

	vector<string> filenames;
	for (auto& p : paths) {
		string dirname = FileOperations::join(p, dirname1);
		ReadDir dir(FileOperations::getNativePath(dirname));
		while (dirent* de = dir.getEntry()) {
			string name = FileOperations::join(dirname, de->d_name);
			if (FileOperations::exists(name)) {
				string nm = FileOperations::join(dirname1, de->d_name);
				if (FileOperations::isDirectory(name)) {
					nm += '/';
				}
				nm = FileOperations::getConventionalPath(nm);
				if (equalHead(filename, nm, true)) {
					filenames.push_back(nm);
				}
			}
		}
	}
	append(matches, filenames);
	bool t = completeImpl(filename, matches, true);
	if (t && !filename.empty() && (filename.back() != '/')) {
		// completed filename, start new token
		tokens.emplace_back();
	}
}

void Completer::checkNumArgs(span<const TclObject> tokens, unsigned exactly, const char* errMessage) const
{
	checkNumArgs(tokens, exactly, Prefix{exactly - 1}, errMessage);
}

void Completer::checkNumArgs(span<const TclObject> tokens, AtLeast atLeast, const char* errMessage) const
{
	checkNumArgs(tokens, atLeast, Prefix{atLeast.min - 1}, errMessage);
}

void Completer::checkNumArgs(span<const TclObject> tokens, Between between, const char* errMessage) const
{
	checkNumArgs(tokens, between, Prefix{between.min - 1}, errMessage);
}

void Completer::checkNumArgs(span<const TclObject> tokens, unsigned exactly, Prefix prefix, const char* errMessage) const
{
	if (tokens.size() == exactly) return;
	getInterpreter().wrongNumArgs(prefix.n, tokens, errMessage);
}

void Completer::checkNumArgs(span<const TclObject> tokens, AtLeast atLeast, Prefix prefix, const char* errMessage) const
{
	if (tokens.size() >= atLeast.min) return;
	getInterpreter().wrongNumArgs(prefix.n, tokens, errMessage);
}

void Completer::checkNumArgs(span<const TclObject> tokens, Between between, Prefix prefix, const char* errMessage) const
{
	if (tokens.size() >= between.min && tokens.size() <= between.max) return;
	getInterpreter().wrongNumArgs(prefix.n, tokens, errMessage);
}

} // namespace openmsx
