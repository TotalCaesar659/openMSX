#include "HotKey.hh"
#include "InputEventFactory.hh"
#include "GlobalCommandController.hh"
#include "CommandException.hh"
#include "EventDistributor.hh"
#include "CliComm.hh"
#include "InputEvents.hh"
#include "XMLElement.hh"
#include "TclArgParser.hh"
#include "TclObject.hh"
#include "SettingsConfig.hh"
#include "outer.hh"
#include "ranges.hh"
#include "view.hh"
#include "build-info.hh"
#include <cassert>
#include <memory>

using std::string;
using std::vector;
using std::make_shared;

// This file implements all Tcl key bindings. These are the 'classical' hotkeys
// (e.g. F11 to (un)mute sound) and the more recent input layers. The idea
// behind an input layer is something like an OSD widget that (temporarily)
// takes semi-exclusive access to the input. So while the widget is active
// keyboard (and joystick) input is no longer passed to the emulated MSX.
// However the classical hotkeys or the openMSX console still receive input.

namespace openmsx {

const bool META_HOT_KEYS =
#ifdef __APPLE__
	true;
#else
	false;
#endif

HotKey::HotKey(RTScheduler& rtScheduler,
               GlobalCommandController& commandController_,
               EventDistributor& eventDistributor_)
	: RTSchedulable(rtScheduler)
	, bindCmd         (commandController_, *this, false)
	, bindDefaultCmd  (commandController_, *this, true)
	, unbindCmd       (commandController_, *this, false)
	, unbindDefaultCmd(commandController_, *this, true)
	, activateCmd     (commandController_)
	, deactivateCmd   (commandController_)
	, commandController(commandController_)
	, eventDistributor(eventDistributor_)
{
	initDefaultBindings();

	eventDistributor.registerEventListener(
		OPENMSX_KEY_DOWN_EVENT, *this, EventDistributor::HOTKEY);
	eventDistributor.registerEventListener(
		OPENMSX_KEY_UP_EVENT, *this, EventDistributor::HOTKEY);
	eventDistributor.registerEventListener(
		OPENMSX_MOUSE_MOTION_EVENT, *this, EventDistributor::HOTKEY);
	eventDistributor.registerEventListener(
		OPENMSX_MOUSE_BUTTON_DOWN_EVENT, *this, EventDistributor::HOTKEY);
	eventDistributor.registerEventListener(
		OPENMSX_MOUSE_BUTTON_UP_EVENT, *this, EventDistributor::HOTKEY);
	eventDistributor.registerEventListener(
		OPENMSX_MOUSE_WHEEL_EVENT, *this, EventDistributor::HOTKEY);
	eventDistributor.registerEventListener(
		OPENMSX_JOY_BUTTON_DOWN_EVENT, *this, EventDistributor::HOTKEY);
	eventDistributor.registerEventListener(
		OPENMSX_JOY_BUTTON_UP_EVENT, *this, EventDistributor::HOTKEY);
	eventDistributor.registerEventListener(
		OPENMSX_JOY_AXIS_MOTION_EVENT, *this, EventDistributor::HOTKEY);
	eventDistributor.registerEventListener(
		OPENMSX_JOY_HAT_EVENT, *this, EventDistributor::HOTKEY);
	eventDistributor.registerEventListener(
		OPENMSX_FOCUS_EVENT, *this, EventDistributor::HOTKEY);
	eventDistributor.registerEventListener(
		OPENMSX_OSD_CONTROL_RELEASE_EVENT, *this, EventDistributor::HOTKEY);
	eventDistributor.registerEventListener(
		OPENMSX_OSD_CONTROL_PRESS_EVENT, *this, EventDistributor::HOTKEY);
}

HotKey::~HotKey()
{
	eventDistributor.unregisterEventListener(OPENMSX_OSD_CONTROL_PRESS_EVENT, *this);
	eventDistributor.unregisterEventListener(OPENMSX_OSD_CONTROL_RELEASE_EVENT, *this);
	eventDistributor.unregisterEventListener(OPENMSX_FOCUS_EVENT, *this);
	eventDistributor.unregisterEventListener(OPENMSX_JOY_BUTTON_UP_EVENT, *this);
	eventDistributor.unregisterEventListener(OPENMSX_JOY_BUTTON_DOWN_EVENT, *this);
	eventDistributor.unregisterEventListener(OPENMSX_JOY_AXIS_MOTION_EVENT, *this);
	eventDistributor.unregisterEventListener(OPENMSX_JOY_HAT_EVENT, *this);
	eventDistributor.unregisterEventListener(OPENMSX_MOUSE_WHEEL_EVENT, *this);
	eventDistributor.unregisterEventListener(OPENMSX_MOUSE_BUTTON_UP_EVENT, *this);
	eventDistributor.unregisterEventListener(OPENMSX_MOUSE_BUTTON_DOWN_EVENT, *this);
	eventDistributor.unregisterEventListener(OPENMSX_MOUSE_MOTION_EVENT, *this);
	eventDistributor.unregisterEventListener(OPENMSX_KEY_UP_EVENT, *this);
	eventDistributor.unregisterEventListener(OPENMSX_KEY_DOWN_EVENT, *this);
}

void HotKey::initDefaultBindings()
{
	// TODO move to Tcl script?

	if (META_HOT_KEYS) {
		// Hot key combos using Mac's Command key.
		bindDefault(HotKeyInfo(make_shared<KeyDownEvent>(
		                            Keys::combine(Keys::K_D, Keys::KM_META)),
		                       "screenshot -guess-name"));
		bindDefault(HotKeyInfo(make_shared<KeyDownEvent>(
		                            Keys::combine(Keys::K_P, Keys::KM_META)),
		                       "toggle pause"));
		bindDefault(HotKeyInfo(make_shared<KeyDownEvent>(
		                            Keys::combine(Keys::K_T, Keys::KM_META)),
		                       "toggle throttle"));
		bindDefault(HotKeyInfo(make_shared<KeyDownEvent>(
		                            Keys::combine(Keys::K_L, Keys::KM_META)),
		                       "toggle console"));
		bindDefault(HotKeyInfo(make_shared<KeyDownEvent>(
		                            Keys::combine(Keys::K_U, Keys::KM_META)),
		                       "toggle mute"));
		bindDefault(HotKeyInfo(make_shared<KeyDownEvent>(
		                            Keys::combine(Keys::K_F, Keys::KM_META)),
		                       "toggle fullscreen"));
		bindDefault(HotKeyInfo(make_shared<KeyDownEvent>(
		                            Keys::combine(Keys::K_Q, Keys::KM_META)),
		                       "exit"));
	} else {
		// Hot key combos for typical PC keyboards.
		bindDefault(HotKeyInfo(make_shared<KeyDownEvent>(Keys::K_PRINT),
		                       "screenshot -guess-name"));
		bindDefault(HotKeyInfo(make_shared<KeyDownEvent>(Keys::K_PAUSE),
		                       "toggle pause"));
		bindDefault(HotKeyInfo(make_shared<KeyDownEvent>(Keys::K_F9),
		                       "toggle throttle"));
		bindDefault(HotKeyInfo(make_shared<KeyDownEvent>(Keys::K_F10),
		                       "toggle console"));
		bindDefault(HotKeyInfo(make_shared<KeyDownEvent>(Keys::K_F11),
		                       "toggle mute"));
		bindDefault(HotKeyInfo(make_shared<KeyDownEvent>(Keys::K_F12),
		                       "toggle fullscreen"));
		bindDefault(HotKeyInfo(make_shared<KeyDownEvent>(
		                            Keys::combine(Keys::K_F4, Keys::KM_ALT)),
		                       "exit"));
		bindDefault(HotKeyInfo(make_shared<KeyDownEvent>(
		                            Keys::combine(Keys::K_PAUSE, Keys::KM_CTRL)),
		                       "exit"));
		bindDefault(HotKeyInfo(make_shared<KeyDownEvent>(
		                            Keys::combine(Keys::K_RETURN, Keys::KM_ALT)),
		                       "toggle fullscreen"));
		// and for Android
		bindDefault(HotKeyInfo(make_shared<KeyDownEvent>(Keys::K_BACK),
		                       "quitmenu::quit_menu"));
	}
}

static HotKey::EventPtr createEvent(const TclObject& obj, Interpreter& interp)
{
	auto event = InputEventFactory::createInputEvent(obj, interp);
	if (!dynamic_cast<const KeyEvent*>             (event.get()) &&
	    !dynamic_cast<const MouseButtonEvent*>     (event.get()) &&
	    !dynamic_cast<const GroupEvent*>           (event.get()) &&
	    !dynamic_cast<const JoystickEvent*>        (event.get()) &&
	    !dynamic_cast<const OsdControlEvent*>      (event.get()) &&
	    !dynamic_cast<const FocusEvent*>           (event.get())) {
		throw CommandException("Unsupported event type");
	}
	return event;
}
static HotKey::EventPtr createEvent(const string& str, Interpreter& interp)
{
	return createEvent(TclObject(str), interp);
}

void HotKey::loadBindings(const XMLElement& config)
{
	// restore default bindings
	unboundKeys.clear();
	boundKeys.clear();
	cmdMap = defaultMap;

	// load bindings
	auto* bindingsElement = config.findChild("bindings");
	if (!bindingsElement) return;
	auto copy = *bindingsElement; // dont iterate over changing container
	for (auto& elem : copy.getChildren()) {
		try {
			auto& interp = commandController.getInterpreter();
			if (elem.getName() == "bind") {
				bind(HotKeyInfo(createEvent(elem.getAttribute("key"), interp),
				                elem.getData(),
				                elem.getAttributeAsBool("repeat", false),
				                elem.getAttributeAsBool("event", false)));
			} else if (elem.getName() == "unbind") {
				unbind(createEvent(elem.getAttribute("key"), interp));
			}
		} catch (MSXException& e) {
			commandController.getCliComm().printWarning(
				"Error while loading key bindings: ", e.getMessage());
		}
	}
}

struct EqualEvent {
	EqualEvent(const Event& event_) : event(event_) {}
	bool operator()(const HotKey::EventPtr& e) const {
		return event == *e;
	}
	bool operator()(const HotKey::HotKeyInfo& info) const {
		return event == *info.event;
	}
	const Event& event;
};

void HotKey::saveBindings(XMLElement& config) const
{
	auto& bindingsElement = config.getCreateChild("bindings");
	bindingsElement.removeAllChildren();

	// add explicit bind's
	for (auto& k : boundKeys) {
		auto& info = *find_if_unguarded(cmdMap, EqualEvent(*k));
		auto& elem = bindingsElement.addChild("bind", info.command);
		elem.addAttribute("key", k->toString());
		if (info.repeat) {
			elem.addAttribute("repeat", "true");
		}
		if (info.passEvent) {
			elem.addAttribute("event", "true");
		}
	}
	// add explicit unbind's
	for (auto& k : unboundKeys) {
		auto& elem = bindingsElement.addChild("unbind");
		elem.addAttribute("key", k->toString());
	}
}

template<typename T>
static bool contains(const vector<T>& v, const Event& event)
{
	return ranges::any_of(v, EqualEvent(event));
}

template<typename T>
static void erase(vector<T>& v, const Event& event)
{
	auto it = ranges::find_if(v, EqualEvent(event));
	if (it != end(v)) move_pop_back(v, it);
}

static void insert(HotKey::KeySet& set, HotKey::EventPtr event)
{
	auto it = ranges::find_if(set, EqualEvent(*event));
	if (it == end(set)) {
		set.push_back(event);
	} else {
		*it = event;
	}
}

template<typename HotKeyInfo>
static void insert(HotKey::BindMap& map, HotKeyInfo&& info)
{
	auto it = ranges::find_if(map, EqualEvent(*info.event));
	if (it == end(map)) {
		map.push_back(std::forward<HotKeyInfo>(info));
	} else {
		*it = std::forward<HotKeyInfo>(info);
	}
}

void HotKey::bind(HotKeyInfo&& info)
{
	erase(unboundKeys, *info.event);
	erase(defaultMap, *info.event);
	insert(boundKeys, info.event);
	insert(cmdMap, std::move(info));

	saveBindings(commandController.getSettingsConfig().getXMLElement());
}

void HotKey::unbind(const EventPtr& event)
{
	auto it1 = ranges::find_if(boundKeys, EqualEvent(*event));
	if (it1 == end(boundKeys)) {
		// only when not a regular bound event
		insert(unboundKeys, event);
	} else {
		//erase(boundKeys, *event);
		move_pop_back(boundKeys, it1);
	}

	erase(defaultMap, *event);
	erase(cmdMap, *event);

	saveBindings(commandController.getSettingsConfig().getXMLElement());
}

void HotKey::bindDefault(HotKeyInfo&& info)
{
	if (!contains(  boundKeys, *info.event) &&
	    !contains(unboundKeys, *info.event)) {
		// not explicity bound or unbound
		insert(cmdMap, info);
	}
	insert(defaultMap, std::move(info));
}

void HotKey::unbindDefault(const EventPtr& event)
{
	if (!contains(  boundKeys, *event) &&
	    !contains(unboundKeys, *event)) {
		// not explicity bound or unbound
		erase(cmdMap, *event);
	}
	erase(defaultMap, *event);
}

void HotKey::bindLayer(HotKeyInfo&& info, const string& layer)
{
	insert(layerMap[layer], std::move(info));
}

void HotKey::unbindLayer(const EventPtr& event, const string& layer)
{
	erase(layerMap[layer], *event);
}

void HotKey::unbindFullLayer(const string& layer)
{
	layerMap.erase(layer);
}

void HotKey::activateLayer(std::string layer, bool blocking)
{
	// Insert new activattion record at the end of the list.
	// (it's not an error if the same layer was already active, in such
	// as case it will now appear twice in the list of active layer,
	// and it must also be deactivated twice).
	activeLayers.push_back({std::move(layer), blocking});
}

void HotKey::deactivateLayer(std::string_view layer)
{
	// remove the first matching activation record from the end
	// (it's not an error if there is no match at all)
	auto it = ranges::find_if(view::reverse(activeLayers),
	                          [&](auto& info) { return info.layer == layer; });
	if (it != activeLayers.rend()) {
		// 'reverse_iterator' -> 'iterator' conversion is a bit tricky
		activeLayers.erase((it + 1).base());
	}
}

static HotKey::BindMap::const_iterator findMatch(
	const HotKey::BindMap& map, const Event& event)
{
	return ranges::find_if(map, [&](auto& p) {
		return p.event->matches(event);
	});
}

void HotKey::executeRT()
{
	if (lastEvent) executeEvent(lastEvent);
}

int HotKey::signalEvent(const EventPtr& event)
{
	if (lastEvent != event) {
		// If the newly received event is different from the repeating
		// event, we stop the repeat process.
		// Except when we're repeating a OsdControlEvent and the
		// received event was actually the 'generating' event for the
		// Osd event. E.g. a cursor-keyboard-down event will generate
		// a corresponding osd event (the osd event is send before the
		// original event). Without this hack, key-repeat will not work
		// for osd key bindings.
		if (lastEvent && lastEvent->isRepeatStopper(*event)) {
			stopRepeat();
		}
	}
	return executeEvent(event);
}

int HotKey::executeEvent(const EventPtr& event)
{
	// First search in active layers (from back to front)
	bool blocking = false;
	for (auto& info : view::reverse(activeLayers)) {
		auto& cmap = layerMap[info.layer]; // ok, if this entry doesn't exist yet
		auto it = findMatch(cmap, *event);
		if (it != end(cmap)) {
			executeBinding(event, *it);
			// Deny event to MSX listeners, also don't pass event
			// to other layers (including the default layer).
			return EventDistributor::MSX;
		}
		blocking = info.blocking;
		if (blocking) break; // don't try lower layers
	}

	// If the event was not yet handled, try the default layer.
	auto it = findMatch(cmdMap, *event);
	if (it != end(cmdMap)) {
		executeBinding(event, *it);
		return EventDistributor::MSX; // deny event to MSX listeners
	}

	// Event is not handled, only let it pass to the MSX if there was no
	// blocking layer active.
	return blocking ? EventDistributor::MSX : 0;
}

void HotKey::executeBinding(const EventPtr& event, const HotKeyInfo& info)
{
	if (info.repeat) {
		startRepeat(event);
	}
	try {
		// Make a copy of the command string because executing the
		// command could potentially execute (un)bind commands so
		// that the original string becomes invalid.
		// Valgrind complained about this in the following scenario:
		//  - open the OSD menu
		//  - activate the 'Exit openMSX' item
		// The latter is triggered from e.g. a 'OSDControl A PRESS'
		// event. The Tcl script bound to that event closes the main
		// menu and reopens a new quit_menu. This will re-bind the
		// action for the 'OSDControl A PRESS' event.
		TclObject command(info.command);
		if (info.passEvent) {
			// Add event as the last argument to the command.
			// (If needed) the current command string is first
			// converted to a list (thus split in a command name
			// and arguments).
			command.addListElement(event->toTclList());
		}

		// ignore return value
		command.executeCommand(commandController.getInterpreter());
	} catch (CommandException& e) {
		commandController.getCliComm().printWarning(
			"Error executing hot key command: ", e.getMessage());
	}
}

void HotKey::startRepeat(const EventPtr& event)
{
	// I initially thought about using the builtin SDL key-repeat feature,
	// but that won't work for example on joystick buttons. So we have to
	// code it ourselves.

	// On android, because of the sensitivity of the touch screen it's
	// very hard to have touches of short durations. So half a second is
	// too short for the key-repeat-delay. A full second should be fine.
	static const unsigned DELAY = PLATFORM_ANDROID ? 1000 : 500;
	// Repeat period.
	static const unsigned PERIOD = 30;

	unsigned delay = (lastEvent ? PERIOD : DELAY) * 1000;
	lastEvent = event;
	scheduleRT(delay);
}

void HotKey::stopRepeat()
{
	lastEvent.reset();
	cancelRT();
}


// class BindCmd

static std::string_view getBindCmdName(bool defaultCmd)
{
	return defaultCmd ? "bind_default" : "bind";
}

HotKey::BindCmd::BindCmd(CommandController& commandController_, HotKey& hotKey_,
                         bool defaultCmd_)
	: Command(commandController_, getBindCmdName(defaultCmd_))
	, hotKey(hotKey_)
	, defaultCmd(defaultCmd_)
{
}

string HotKey::BindCmd::formatBinding(const HotKey::HotKeyInfo& info)
{
	return strCat(info.event->toString(), (info.repeat ? " [repeat]" : ""),
	              (info.passEvent ? " [event]" : ""), ":  ", info.command, '\n');
}

void HotKey::BindCmd::execute(span<const TclObject> tokens, TclObject& result)
{
	string layer;
	bool layers = false;
	bool repeat = false;
	bool passEvent = false;
	ArgsInfo parserInfo[] = {
		valueArg("-layer", layer),
		flagArg("-layers", layers),
		flagArg("-repeat", repeat),
		flagArg("-event", passEvent),
	};
	auto arguments = parseTclArgs(getInterpreter(), tokens.subspan<1>(), parserInfo);
	if (defaultCmd && !layer.empty()) {
		throw CommandException("Layers are not supported for default bindings");
	}

	auto& cMap = defaultCmd
		? hotKey.defaultMap
		: layer.empty() ? hotKey.cmdMap
		                : hotKey.layerMap[layer];

	if (layers) {
		for (const auto& [layerName, bindings] : hotKey.layerMap) {
			// An alternative for this test is to always properly
			// prune layerMap. ATM this approach seems simpler.
			if (!bindings.empty()) {
				result.addListElement(layerName);
			}
		}
		return;
	}

	switch (arguments.size()) {
	case 0: {
		// show all bounded keys (for this layer)
		string r;
		for (auto& p : cMap) {
			r += formatBinding(p);
		}
		result = r;
		break;
	}
	case 1: {
		// show bindings for this key (in this layer)
		auto it = ranges::find_if(cMap,
		                          EqualEvent(*createEvent(arguments[0], getInterpreter())));
		if (it == end(cMap)) {
			throw CommandException("Key not bound");
		}
		result = formatBinding(*it);
		break;
	}
	default: {
		// make a new binding
		string command(arguments[1].getString());
		for (const auto& arg : view::drop(arguments, 2)) {
			strAppend(command, ' ', arg.getString());
		}
		HotKey::HotKeyInfo info(
			createEvent(arguments[0], getInterpreter()),
			command, repeat, passEvent);
		if (defaultCmd) {
			hotKey.bindDefault(std::move(info));
		} else if (layer.empty()) {
			hotKey.bind(std::move(info));
		} else {
			hotKey.bindLayer(std::move(info), layer);
		}
		break;
	}
	}
}
string HotKey::BindCmd::help(const vector<string>& /*tokens*/) const
{
	auto cmd = getBindCmdName(defaultCmd);
	return strCat(
		cmd, "                       : show all bounded keys\n",
		cmd, " <key>                 : show binding for this key\n",
		cmd, " <key> [-repeat] [-event] <cmd> : bind key to command, optionally "
		"repeat command while key remains pressed and also optionally "
		"give back the event as argument (a list) to <cmd>\n"
		"These 3 take an optional '-layer <layername>' option, "
		"see activate_input_layer.\n",
		cmd, " -layers               : show a list of layers with bound keys\n");
}


// class UnbindCmd

static string getUnbindCmdName(bool defaultCmd)
{
	return defaultCmd ? "unbind_default" : "unbind";
}

HotKey::UnbindCmd::UnbindCmd(CommandController& commandController_,
                             HotKey& hotKey_, bool defaultCmd_)
	: Command(commandController_, getUnbindCmdName(defaultCmd_))
	, hotKey(hotKey_)
	, defaultCmd(defaultCmd_)
{
}

void HotKey::UnbindCmd::execute(span<const TclObject> tokens, TclObject& /*result*/)
{
	string layer;
	ArgsInfo info[] = { valueArg("-layer", layer) };
	auto arguments = parseTclArgs(getInterpreter(), tokens.subspan<1>(), info);
	if (defaultCmd && !layer.empty()) {
		throw CommandException("Layers are not supported for default bindings");
	}

	if ((arguments.size() > 1) || (layer.empty() && (arguments.size() != 1))) {
		throw SyntaxError();
	}

	HotKey::EventPtr event;
	if (arguments.size() == 1) {
		event = createEvent(arguments[0], getInterpreter());
	}

	if (defaultCmd) {
		assert(event);
		hotKey.unbindDefault(event);
	} else if (layer.empty()) {
		assert(event);
		hotKey.unbind(event);
	} else {
		if (event) {
			hotKey.unbindLayer(event, layer);
		} else {
			hotKey.unbindFullLayer(layer);
		}
	}
}
string HotKey::UnbindCmd::help(const vector<string>& /*tokens*/) const
{
	auto cmd = getUnbindCmdName(defaultCmd);
	return strCat(
		cmd, " <key>                    : unbind this key\n",
		cmd, " -layer <layername> <key> : unbind key in a specific layer\n",
		cmd, " -layer <layername>       : unbind all keys in this layer\n");
}


// class ActivateCmd

HotKey::ActivateCmd::ActivateCmd(CommandController& commandController_)
	: Command(commandController_, "activate_input_layer")
{
}

void HotKey::ActivateCmd::execute(span<const TclObject> tokens, TclObject& result)
{
	bool blocking = false;
	ArgsInfo info[] = { flagArg("-blocking", blocking) };
	auto args = parseTclArgs(getInterpreter(), tokens.subspan(1), info);

	auto& hotKey = OUTER(HotKey, activateCmd);
	switch (args.size()) {
	case 0: {
		string r;
		for (auto& layerInfo : view::reverse(hotKey.activeLayers)) {
			r += layerInfo.layer;
			if (layerInfo.blocking) {
				r += " -blocking";
			}
			r += '\n';
		}
		result = r;
		break;
	}
	case 1: {
		std::string_view layer = args[0].getString();
		hotKey.activateLayer(string(layer), blocking);
		break;
	}
	default:
		throw SyntaxError();
	}
}

string HotKey::ActivateCmd::help(const vector<string>& /*tokens*/) const
{
	return "activate_input_layer                         "
	       ": show list of active layers (most recent on top)\n"
	       "activate_input_layer [-blocking] <layername> "
	       ": activate new layer, optionally in blocking mode\n";
}


// class DeactivateCmd

HotKey::DeactivateCmd::DeactivateCmd(CommandController& commandController_)
	: Command(commandController_, "deactivate_input_layer")
{
}

void HotKey::DeactivateCmd::execute(span<const TclObject> tokens, TclObject& /*result*/)
{
	checkNumArgs(tokens, 2, "layer");
	auto& hotKey = OUTER(HotKey, deactivateCmd);
	hotKey.deactivateLayer(tokens[1].getString());
}

string HotKey::DeactivateCmd::help(const vector<string>& /*tokens*/) const
{
	return "deactivate_input_layer <layername> : deactive the given input layer";
}


} // namespace openmsx
