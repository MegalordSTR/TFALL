////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_WINDOW_HPP
#define SFML_WINDOW_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Export.hpp>
#include <SFML/Window/GlResource.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowHandle.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>


namespace sf
{
namespace priv
{
    class GlContext;
    class WindowImpl;
}

class Event;

////////////////////////////////////////////////////////////
/// \brief Window that serves as a target for OpenGL rendering
///
////////////////////////////////////////////////////////////
class SFML_WINDOW_API Window : GlResource, NonCopyable
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// This constructor doesn't actually create the m_window,
    /// use the other constructors or call create() to do so.
    ///
    ////////////////////////////////////////////////////////////
    Window();

    ////////////////////////////////////////////////////////////
    /// \brief Construct a new m_window
    ///
    /// This constructor creates the m_window with the size and pixel
    /// depth defined in \a mode. An optional style can be passed to
    /// customize the look and behavior of the m_window (borders,
    /// title bar, resizable, closable, ...). If \a style contains
    /// Style::Fullscreen, then \a mode must be a valid video mode.
    ///
    /// The fourth parameter is an optional structure specifying
    /// advanced OpenGL context settings such as antialiasing,
    /// depth-buffer bits, etc.
    ///
    /// \param mode     Video mode to use (defines the width, height and depth of the rendering area of the m_window)
    /// \param title    Title of the m_window
    /// \param style    %Window style, a bitwise OR combination of sf::Style enumerators
    /// \param settings Additional settings for the underlying OpenGL context
    ///
    ////////////////////////////////////////////////////////////
    Window(VideoMode mode, const String& title, Uint32 style = Style::Default, const ContextSettings& settings = ContextSettings());

    ////////////////////////////////////////////////////////////
    /// \brief Construct the m_window from an existing control
    ///
    /// Use this constructor if you want to create an OpenGL
    /// rendering area into an already existing control.
    ///
    /// The second parameter is an optional structure specifying
    /// advanced OpenGL context settings such as antialiasing,
    /// depth-buffer bits, etc.
    ///
    /// \param handle   Platform-specific handle of the control
    /// \param settings Additional settings for the underlying OpenGL context
    ///
    ////////////////////////////////////////////////////////////
    explicit Window(WindowHandle handle, const ContextSettings& settings = ContextSettings());

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    /// Closes the m_window and frees all the resources attached to it.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~Window();

    ////////////////////////////////////////////////////////////
    /// \brief Create (or recreate) the m_window
    ///
    /// If the m_window was already created, it closes it first.
    /// If \a style contains Style::Fullscreen, then \a mode
    /// must be a valid video mode.
    ///
    /// The fourth parameter is an optional structure specifying
    /// advanced OpenGL context settings such as antialiasing,
    /// depth-buffer bits, etc.
    ///
    /// \param mode     Video mode to use (defines the width, height and depth of the rendering area of the m_window)
    /// \param title    Title of the m_window
    /// \param style    %Window style, a bitwise OR combination of sf::Style enumerators
    /// \param settings Additional settings for the underlying OpenGL context
    ///
    ////////////////////////////////////////////////////////////
    void create(VideoMode mode, const String& title, Uint32 style = Style::Default, const ContextSettings& settings = ContextSettings());

    ////////////////////////////////////////////////////////////
    /// \brief Create (or recreate) the m_window from an existing control
    ///
    /// Use this function if you want to create an OpenGL
    /// rendering area into an already existing control.
    /// If the m_window was already created, it closes it first.
    ///
    /// The second parameter is an optional structure specifying
    /// advanced OpenGL context settings such as antialiasing,
    /// depth-buffer bits, etc.
    ///
    /// \param handle   Platform-specific handle of the control
    /// \param settings Additional settings for the underlying OpenGL context
    ///
    ////////////////////////////////////////////////////////////
    void create(WindowHandle handle, const ContextSettings& settings = ContextSettings());

    ////////////////////////////////////////////////////////////
    /// \brief Close the m_window and destroy all the attached resources
    ///
    /// After calling this function, the sf::Window instance remains
    /// valid and you can call create() to recreate the m_window.
    /// All other functions such as pollEvent() or display() will
    /// still work (i.e. you don't have to test isOpen() every time),
    /// and will have no effect on closed windows.
    ///
    ////////////////////////////////////////////////////////////
    void close();

    ////////////////////////////////////////////////////////////
    /// \brief Tell whether or not the m_window is open
    ///
    /// This function returns whether or not the m_window exists.
    /// Note that a hidden m_window (setVisible(false)) is open
    /// (therefore this function would return true).
    ///
    /// \return True if the m_window is open, false if it has been closed
    ///
    ////////////////////////////////////////////////////////////
    bool isOpen() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the settings of the OpenGL context of the m_window
    ///
    /// Note that these settings may be different from what was
    /// passed to the constructor or the create() function,
    /// if one or more settings were not supported. In this case,
    /// SFML chose the closest match.
    ///
    /// \return Structure containing the OpenGL context settings
    ///
    ////////////////////////////////////////////////////////////
    const ContextSettings& getSettings() const;

    ////////////////////////////////////////////////////////////
    /// \brief Pop the event on top of the event queue, if any, and return it
    ///
    /// This function is not blocking: if there's no pending event then
    /// it will return false and leave \a event unmodified.
    /// Note that more than one event may be present in the event queue,
    /// thus you should always call this function in a loop
    /// to make sure that you process every pending event.
    /// \code
    /// sf::Event event;
    /// while (m_window.pollEvent(event))
    /// {
    ///    // process event...
    /// }
    /// \endcode
    ///
    /// \param event Event to be returned
    ///
    /// \return True if an event was returned, or false if the event queue was empty
    ///
    /// \see waitEvent
    ///
    ////////////////////////////////////////////////////////////
    bool pollEvent(Event& event);

    ////////////////////////////////////////////////////////////
    /// \brief Wait for an event and return it
    ///
    /// This function is blocking: if there's no pending event then
    /// it will wait until an event is received.
    /// After this function returns (and no error occurred),
    /// the \a event object is always valid and filled properly.
    /// This function is typically used when you have a thread that
    /// is dedicated to events handling: you want to make this thread
    /// sleep as long as no new event is received.
    /// \code
    /// sf::Event event;
    /// if (m_window.waitEvent(event))
    /// {
    ///    // process event...
    /// }
    /// \endcode
    ///
    /// \param event Event to be returned
    ///
    /// \return False if any error occurred
    ///
    /// \see pollEvent
    ///
    ////////////////////////////////////////////////////////////
    bool waitEvent(Event& event);

    ////////////////////////////////////////////////////////////
    /// \brief Get the position of the m_window
    ///
    /// \return Position of the m_window, in pixels
    ///
    /// \see setPosition
    ///
    ////////////////////////////////////////////////////////////
    Vector2i getPosition() const;

    ////////////////////////////////////////////////////////////
    /// \brief Change the position of the m_window on screen
    ///
    /// This function only works for top-level windows
    /// (i.e. it will be ignored for windows created from
    /// the handle of a child m_window/control).
    ///
    /// \param position New position, in pixels
    ///
    /// \see getPosition
    ///
    ////////////////////////////////////////////////////////////
    void setPosition(const Vector2i& position);

    ////////////////////////////////////////////////////////////
    /// \brief Get the size of the rendering region of the m_window
    ///
    /// The size doesn't include the titlebar and borders
    /// of the m_window.
    ///
    /// \return Size in pixels
    ///
    /// \see setSize
    ///
    ////////////////////////////////////////////////////////////
    Vector2u getSize() const;

    ////////////////////////////////////////////////////////////
    /// \brief Change the size of the rendering region of the m_window
    ///
    /// \param size New size, in pixels
    ///
    /// \see getSize
    ///
    ////////////////////////////////////////////////////////////
    void setSize(const Vector2u& size);

    ////////////////////////////////////////////////////////////
    /// \brief Change the title of the m_window
    ///
    /// \param title New title
    ///
    /// \see setIcon
    ///
    ////////////////////////////////////////////////////////////
    void setTitle(const String& title);

    ////////////////////////////////////////////////////////////
    /// \brief Change the m_window's icon
    ///
    /// \a pixels must be an array of \a width x \a height pixels
    /// in 32-bits RGBA format.
    ///
    /// The OS default icon is used by default.
    ///
    /// \param width  Icon's width, in pixels
    /// \param height Icon's height, in pixels
    /// \param pixels Pointer to the array of pixels in memory. The
    ///               pixels are copied, so you need not keep the
    ///               source alive after calling this function.
    ///
    /// \see setTitle
    ///
    ////////////////////////////////////////////////////////////
    void setIcon(unsigned int width, unsigned int height, const Uint8* pixels);

    ////////////////////////////////////////////////////////////
    /// \brief Show or hide the m_window
    ///
    /// The m_window is shown by default.
    ///
    /// \param visible True to show the m_window, false to hide it
    ///
    ////////////////////////////////////////////////////////////
    void setVisible(bool visible);

    ////////////////////////////////////////////////////////////
    /// \brief Enable or disable vertical synchronization
    ///
    /// Activating vertical synchronization will limit the number
    /// of frames displayed to the refresh rate of the monitor.
    /// This can avoid some visual artifacts, and limit the framerate
    /// to a good value (but not constant across different computers).
    ///
    /// Vertical synchronization is disabled by default.
    ///
    /// \param enabled True to enable v-sync, false to deactivate it
    ///
    ////////////////////////////////////////////////////////////
    void setVerticalSyncEnabled(bool enabled);

    ////////////////////////////////////////////////////////////
    /// \brief Show or hide the mouse cursor
    ///
    /// The mouse cursor is visible by default.
    ///
    /// \param visible True to show the mouse cursor, false to hide it
    ///
    ////////////////////////////////////////////////////////////
    void setMouseCursorVisible(bool visible);

    ////////////////////////////////////////////////////////////
    /// \brief Grab or release the mouse cursor
    ///
    /// If set, grabs the mouse cursor inside this m_window's client
    /// area so it may no longer be moved outside its bounds.
    /// Note that grabbing is only active while the m_window has
    /// focus.
    ///
    /// \param grabbed True to enable, false to disable
    ///
    ////////////////////////////////////////////////////////////
    void setMouseCursorGrabbed(bool grabbed);

    ////////////////////////////////////////////////////////////
    /// \brief Set the displayed cursor to a native system cursor
    ///
    /// Upon m_window creation, the arrow cursor is used by default.
    ///
    /// \warning The cursor must not be destroyed while in use by
    ///          the m_window.
    ///
    /// \warning Features related to Cursor are not supported on
    ///          iOS and Android.
    ///
    /// \param cursor Native system cursor type to display
    ///
    /// \see sf::Cursor::loadFromSystem
    /// \see sf::Cursor::loadFromPixels
    ///
    ////////////////////////////////////////////////////////////
    void setMouseCursor(const Cursor& cursor);

    ////////////////////////////////////////////////////////////
    /// \brief Enable or disable automatic key-repeat
    ///
    /// If key repeat is enabled, you will receive repeated
    /// KeyPressed events while keeping a key pressed. If it is disabled,
    /// you will only get a single event when the key is pressed.
    ///
    /// Key repeat is enabled by default.
    ///
    /// \param enabled True to enable, false to disable
    ///
    ////////////////////////////////////////////////////////////
    void setKeyRepeatEnabled(bool enabled);

    ////////////////////////////////////////////////////////////
    /// \brief Limit the framerate to a maximum fixed frequency
    ///
    /// If a limit is set, the m_window will use a small delay after
    /// each call to display() to ensure that the current frame
    /// lasted long enough to match the framerate limit.
    /// SFML will try to match the given limit as much as it can,
    /// but since it internally uses sf::sleep, whose precision
    /// depends on the underlying OS, the results may be a little
    /// unprecise as well (for example, you can get 65 FPS when
    /// requesting 60).
    ///
    /// \param limit Framerate limit, in frames per seconds (use 0 to disable limit)
    ///
    ////////////////////////////////////////////////////////////
    void setFramerateLimit(unsigned int limit);

    ////////////////////////////////////////////////////////////
    /// \brief Change the joystick threshold
    ///
    /// The joystick threshold is the value below which
    /// no JoystickMoved event will be generated.
    ///
    /// The threshold value is 0.1 by default.
    ///
    /// \param threshold New threshold, in the range [0, 100]
    ///
    ////////////////////////////////////////////////////////////
    void setJoystickThreshold(float threshold);

    ////////////////////////////////////////////////////////////
    /// \brief Activate or deactivate the m_window as the current target
    ///        for OpenGL rendering
    ///
    /// A m_window is active only on the current thread, if you want to
    /// make it active on another thread you have to deactivate it
    /// on the previous thread first if it was active.
    /// Only one m_window can be active on a thread at a time, thus
    /// the m_window previously active (if any) automatically gets deactivated.
    /// This is not to be confused with requestFocus().
    ///
    /// \param active True to activate, false to deactivate
    ///
    /// \return True if operation was successful, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    bool setActive(bool active = true) const;

    ////////////////////////////////////////////////////////////
    /// \brief Request the current m_window to be made the active
    ///        foreground m_window
    ///
    /// At any given time, only one m_window may have the input focus
    /// to receive input events such as keystrokes or mouse events.
    /// If a m_window requests focus, it only hints to the operating
    /// system, that it would like to be focused. The operating system
    /// is free to deny the request.
    /// This is not to be confused with setActive().
    ///
    /// \see hasFocus
    ///
    ////////////////////////////////////////////////////////////
    void requestFocus();

    ////////////////////////////////////////////////////////////
    /// \brief Check whether the m_window has the input focus
    ///
    /// At any given time, only one m_window may have the input focus
    /// to receive input events such as keystrokes or most mouse
    /// events.
    ///
    /// \return True if m_window has focus, false otherwise
    /// \see requestFocus
    ///
    ////////////////////////////////////////////////////////////
    bool hasFocus() const;

    ////////////////////////////////////////////////////////////
    /// \brief Display on screen what has been rendered to the m_window so far
    ///
    /// This function is typically called after all OpenGL rendering
    /// has been done for the current frame, in order to show
    /// it on screen.
    ///
    ////////////////////////////////////////////////////////////
    void display();

    ////////////////////////////////////////////////////////////
    /// \brief Get the OS-specific handle of the m_window
    ///
    /// The type of the returned handle is sf::WindowHandle,
    /// which is a typedef to the handle type defined by the OS.
    /// You shouldn't need to use this function, unless you have
    /// very specific stuff to implement that SFML doesn't support,
    /// or implement a temporary workaround until a bug is fixed.
    ///
    /// \return System handle of the m_window
    ///
    ////////////////////////////////////////////////////////////
    WindowHandle getSystemHandle() const;

protected:

    ////////////////////////////////////////////////////////////
    /// \brief Function called after the m_window has been created
    ///
    /// This function is called so that derived classes can
    /// perform their own specific initialization as soon as
    /// the m_window is created.
    ///
    ////////////////////////////////////////////////////////////
    virtual void onCreate();

    ////////////////////////////////////////////////////////////
    /// \brief Function called after the m_window has been resized
    ///
    /// This function is called so that derived classes can
    /// perform custom actions when the size of the m_window changes.
    ///
    ////////////////////////////////////////////////////////////
    virtual void onResize();

private:

    ////////////////////////////////////////////////////////////
    /// \brief Processes an event before it is sent to the user
    ///
    /// This function is called every time an event is received
    /// from the internal m_window (through pollEvent or waitEvent).
    /// It filters out unwanted events, and performs whatever internal
    /// stuff the m_window needs before the event is returned to the
    /// user.
    ///
    /// \param event Event to filter
    ///
    ////////////////////////////////////////////////////////////
    bool filterEvent(const Event& event);

    ////////////////////////////////////////////////////////////
    /// \brief Perform some common internal initializations
    ///
    ////////////////////////////////////////////////////////////
    void initialize();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    priv::WindowImpl* m_impl;           ///< Platform-specific implementation of the m_window
    priv::GlContext*  m_context;        ///< Platform-specific implementation of the OpenGL context
    Clock             m_clock;          ///< Clock for measuring the elapsed time between frames
    Time              m_frameTimeLimit; ///< Current framerate limit
    Vector2u          m_size;           ///< Current size of the m_window
};

} // namespace sf


#endif // SFML_WINDOW_HPP


////////////////////////////////////////////////////////////
/// \class sf::Window
/// \ingroup m_window
///
/// sf::Window is the main class of the Window module. It defines
/// an OS m_window that is able to receive an OpenGL rendering.
///
/// A sf::Window can create its own new m_window, or be embedded into
/// an already existing control using the create(handle) function.
/// This can be useful for embedding an OpenGL rendering area into
/// a view which is part of a bigger GUI with existing windows,
/// controls, etc. It can also serve as embedding an OpenGL rendering
/// area into a m_window created by another (probably richer) GUI library
/// like Qt or wxWidgets.
///
/// The sf::Window class provides a simple interface for manipulating
/// the m_window: move, resize, show/hide, control mouse cursor, etc.
/// It also provides event handling through its pollEvent() and waitEvent()
/// functions.
///
/// Note that OpenGL experts can pass their own parameters (antialiasing
/// level, bits for the depth and stencil buffers, etc.) to the
/// OpenGL context attached to the m_window, with the sf::ContextSettings
/// structure which is passed as an optional argument when creating the
/// m_window.
///
/// On dual-graphics systems consisting of a low-power integrated GPU
/// and a powerful discrete GPU, the driver picks which GPU will run an
/// SFML application. In order to inform the driver that an SFML application
/// can benefit from being run on the more powerful discrete GPU,
/// #SFML_DEFINE_DISCRETE_GPU_PREFERENCE can be placed in a source file
/// that is compiled and linked into the final application. The macro
/// should be placed outside of any scopes in the global namespace.
///
/// Usage example:
/// \code
/// // Declare and create a new m_window
/// sf::Window m_window(sf::VideoMode(800, 600), "SFML m_window");
///
/// // Limit the framerate to 60 frames per second (this step is optional)
/// m_window.setFramerateLimit(60);
///
/// // The main loop - ends as soon as the m_window is closed
/// while (m_window.isOpen())
/// {
///    // Event processing
///    sf::Event event;
///    while (m_window.pollEvent(event))
///    {
///        // Request for closing the m_window
///        if (event.type == sf::Event::Closed)
///            m_window.close();
///    }
///
///    // Activate the m_window for OpenGL rendering
///    m_window.setActive();
///
///    // OpenGL drawing commands go here...
///
///    // End the current frame and display its contents on screen
///    m_window.display();
/// }
/// \endcode
///
////////////////////////////////////////////////////////////
