#include <exception>
#include <iostream>

#include "SDLW.hpp"

#include "Application.hpp"
#include "Renderer.hpp"
#include "Window.hpp"

namespace TappyPlane {

void run()
{
    const SDLW::Subsystem sdlwGuard{SDLW::Subsystem::Flags::Video};
    const SDLW::IMG::Subsystem imgGuard{SDLW::IMG::Subsystem::Flags::PNG};
    Window::instance();
    Renderer::instance();
    Application app;
}

} // namespace TappyPlane

int main(int argc, char* argv[])
{
    try {
        TappyPlane::run();
    } catch (const SDLW::Exception& e) {
        std::cerr << "Uncaught SDLW exception: " << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Uncaught exception: " << e.what() << '\n';
    } catch (...) {
        std::cerr << "Unknown uncaught exception\n";
    }
    return 0;
}