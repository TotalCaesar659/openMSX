#include "SDLVideoSystem.hh"
#include "SDLVisibleSurface.hh"
#include "SDLRasterizer.hh"
#include "V9990SDLRasterizer.hh"
#include "FBPostProcessor.hh"
#include "Reactor.hh"
#include "Display.hh"
#include "RenderSettings.hh"
#include "IntegerSetting.hh"
#include "EventDistributor.hh"
#include "VDP.hh"
#include "V9990.hh"
#include "build-info.hh"
#include "unreachable.hh"
#include <memory>

#include "components.hh"
#if COMPONENT_GL
#include "SDLGLVisibleSurface.hh"
#include "GLPostProcessor.hh"
#endif
#if COMPONENT_LASERDISC
#include "LaserdiscPlayer.hh"
#include "LDSDLRasterizer.hh"
#endif

namespace openmsx {

SDLVideoSystem::SDLVideoSystem(Reactor& reactor_, CommandConsole& console)
	: reactor(reactor_)
	, display(reactor.getDisplay())
	, renderSettings(reactor.getDisplay().getRenderSettings())
{
	resize();

	consoleLayer = screen->createConsoleLayer(reactor, console);
	snowLayer = screen->createSnowLayer();
	osdGuiLayer = screen->createOSDGUILayer(display.getOSDGUI());
	display.addLayer(*consoleLayer);
	display.addLayer(*snowLayer);
	display.addLayer(*osdGuiLayer);

	renderSettings.getScaleFactorSetting().attach(*this);

	reactor.getEventDistributor().registerEventListener(
		OPENMSX_RESIZE_EVENT, *this);
}

SDLVideoSystem::~SDLVideoSystem()
{
	reactor.getEventDistributor().unregisterEventListener(
		OPENMSX_RESIZE_EVENT, *this);

	renderSettings.getScaleFactorSetting().detach(*this);

	display.removeLayer(*osdGuiLayer);
	display.removeLayer(*snowLayer);
	display.removeLayer(*consoleLayer);
}

std::unique_ptr<Rasterizer> SDLVideoSystem::createRasterizer(VDP& vdp)
{
	std::string videoSource = (vdp.getName() == "VDP")
	                        ? "MSX" // for backwards compatibility
	                        : vdp.getName();
	auto& motherBoard = vdp.getMotherBoard();
	switch (renderSettings.getRenderer()) {
	case RenderSettings::SDL:
	case RenderSettings::SDLGL_FB16:
	case RenderSettings::SDLGL_FB32:
		switch (screen->getSDLFormat().BytesPerPixel) {
#if HAVE_16BPP
		case 2:
			return std::make_unique<SDLRasterizer<uint16_t>>(
				vdp, display, *screen,
				std::make_unique<FBPostProcessor<uint16_t>>(
					motherBoard, display, *screen,
					videoSource, 640, 240, true));
#endif
#if HAVE_32BPP
		case 4:
			return std::make_unique<SDLRasterizer<uint32_t>>(
				vdp, display, *screen,
				std::make_unique<FBPostProcessor<uint32_t>>(
					motherBoard, display, *screen,
					videoSource, 640, 240, true));
#endif
		default:
			UNREACHABLE; return nullptr;
		}
#if COMPONENT_GL
	case RenderSettings::SDLGL_PP:
		return std::make_unique<SDLRasterizer<uint32_t>>(
			vdp, display, *screen,
			std::make_unique<GLPostProcessor>(
				motherBoard, display, *screen,
				videoSource, 640, 240, true));
#endif
	default:
		UNREACHABLE; return nullptr;
	}
}

std::unique_ptr<V9990Rasterizer> SDLVideoSystem::createV9990Rasterizer(
	V9990& vdp)
{
	std::string videoSource = (vdp.getName() == "Sunrise GFX9000")
	                        ? "GFX9000" // for backwards compatibility
	                        : vdp.getName();
	MSXMotherBoard& motherBoard = vdp.getMotherBoard();
	switch (renderSettings.getRenderer()) {
	case RenderSettings::SDL:
	case RenderSettings::SDLGL_FB16:
	case RenderSettings::SDLGL_FB32:
		switch (screen->getSDLFormat().BytesPerPixel) {
#if HAVE_16BPP
		case 2:
			return std::make_unique<V9990SDLRasterizer<uint16_t>>(
				vdp, display, *screen,
				std::make_unique<FBPostProcessor<uint16_t>>(
					motherBoard, display, *screen,
					videoSource, 1280, 240, true));
#endif
#if HAVE_32BPP
		case 4:
			return std::make_unique<V9990SDLRasterizer<uint32_t>>(
				vdp, display, *screen,
				std::make_unique<FBPostProcessor<uint32_t>>(
					motherBoard, display, *screen,
					videoSource, 1280, 240, true));
#endif
		default:
			UNREACHABLE; return nullptr;
		}
#if COMPONENT_GL
	case RenderSettings::SDLGL_PP:
		return std::make_unique<V9990SDLRasterizer<uint32_t>>(
			vdp, display, *screen,
			std::make_unique<GLPostProcessor>(
				motherBoard, display, *screen,
				videoSource, 1280, 240, true));
#endif
	default:
		UNREACHABLE; return nullptr;
	}
}

#if COMPONENT_LASERDISC
std::unique_ptr<LDRasterizer> SDLVideoSystem::createLDRasterizer(
	LaserdiscPlayer& ld)
{
	std::string videoSource = "Laserdisc"; // TODO handle multiple???
	MSXMotherBoard& motherBoard = ld.getMotherBoard();
	switch (renderSettings.getRenderer()) {
	case RenderSettings::SDL:
	case RenderSettings::SDLGL_FB16:
	case RenderSettings::SDLGL_FB32:
		switch (screen->getSDLFormat().BytesPerPixel) {
#if HAVE_16BPP
		case 2:
			return std::make_unique<LDSDLRasterizer<uint16_t>>(
				*screen,
				std::make_unique<FBPostProcessor<uint16_t>>(
					motherBoard, display, *screen,
					videoSource, 640, 480, false));
#endif
#if HAVE_32BPP
		case 4:
			return std::make_unique<LDSDLRasterizer<uint32_t>>(
				*screen,
				std::make_unique<FBPostProcessor<uint32_t>>(
					motherBoard, display, *screen,
					videoSource, 640, 480, false));
#endif
		default:
			UNREACHABLE; return nullptr;
		}
#if COMPONENT_GL
	case RenderSettings::SDLGL_PP:
		return std::make_unique<LDSDLRasterizer<uint32_t>>(
			*screen,
			std::make_unique<GLPostProcessor>(
				motherBoard, display, *screen,
				videoSource, 640, 480, false));
#endif
	default:
		UNREACHABLE; return nullptr;
	}
}
#endif

gl::ivec2 SDLVideoSystem::getWindowSize()
{
	int factor = renderSettings.getScaleFactor();
	switch (renderSettings.getRenderer()) {
	case RenderSettings::SDL:
	case RenderSettings::SDLGL_FB16:
	case RenderSettings::SDLGL_FB32:
		// We don't have 4x software scalers yet.
		if (factor > 3) factor = 3;
		break;
	case RenderSettings::SDLGL_PP:
		// All scale factors are supported.
		break;
	default:
		UNREACHABLE;
	}
	return {320 * factor, 240 * factor};
}

// TODO: If we can switch video system at any time (not just frame end),
//       is this polling approach necessary at all?
bool SDLVideoSystem::checkSettings()
{
	// Check resolution.
	if (getWindowSize() != screen->getLogicalSize()) {
		return false;
	}

	// Check fullscreen.
	return screen->setFullScreen(renderSettings.getFullScreen());
}

void SDLVideoSystem::flush()
{
	screen->finish();
}

void SDLVideoSystem::takeScreenShot(const std::string& filename, bool withOsd)
{
	if (withOsd) {
		// we can directly save current content as screenshot
		screen->saveScreenshot(filename);
	} else {
		// we first need to re-render to an off-screen surface
		// with OSD layers disabled
		ScopedLayerHider hideConsole(*consoleLayer);
		ScopedLayerHider hideOsd(*osdGuiLayer);
		std::unique_ptr<OutputSurface> surf = screen->createOffScreenSurface();
		display.repaint(*surf);
		surf->saveScreenshot(filename);
	}
}

void SDLVideoSystem::updateWindowTitle()
{
	screen->updateWindowTitle();
}

OutputSurface* SDLVideoSystem::getOutputSurface()
{
	return screen.get();
}

void SDLVideoSystem::resize()
{
	auto& rtScheduler         = reactor.getRTScheduler();
	auto& eventDistributor    = reactor.getEventDistributor();
	auto& inputEventGenerator = reactor.getInputEventGenerator();

	auto windowSize = getWindowSize();
	unsigned width  = windowSize[0];
	unsigned height = windowSize[1];
	// Destruct existing output surface before creating a new one.
	screen.reset();

	switch (renderSettings.getRenderer()) {
	case RenderSettings::SDL:
		screen = std::make_unique<SDLVisibleSurface>(
			width, height, display, rtScheduler,
			eventDistributor, inputEventGenerator,
			reactor.getCliComm());
		break;
#if COMPONENT_GL
	case RenderSettings::SDLGL_PP:
		screen = std::make_unique<SDLGLVisibleSurface>(
			width, height, display, rtScheduler,
			eventDistributor, inputEventGenerator,
			reactor.getCliComm());
		break;
	case RenderSettings::SDLGL_FB16:
		screen = std::make_unique<SDLGLVisibleSurface>(
			width, height, display, rtScheduler,
			eventDistributor, inputEventGenerator,
			reactor.getCliComm(),
			SDLGLVisibleSurface::FB_16BPP);
		break;
	case RenderSettings::SDLGL_FB32:
		screen = std::make_unique<SDLGLVisibleSurface>(
			width, height, display, rtScheduler,
			eventDistributor, inputEventGenerator,
			reactor.getCliComm(),
			SDLGLVisibleSurface::FB_32BPP);
		break;
#endif
	default:
		UNREACHABLE;
	}
}

void SDLVideoSystem::update(const Setting& subject)
{
	if (&subject == &renderSettings.getScaleFactorSetting()) {
		// TODO: This is done via checkSettings instead,
		//       but is that still needed?
		//resize();
	} else {
		UNREACHABLE;
	}
}

int SDLVideoSystem::signalEvent(const std::shared_ptr<const Event>& /*event*/)
{
	// TODO: Currently window size depends only on scale factor.
	//       Maybe in the future it will be handled differently.
	//auto& resizeEvent = checked_cast<const ResizeEvent&>(event);
	//resize(resizeEvent.getX(), resizeEvent.getY());
	//resize();
	return 0;
}

} // namespace openmsx
