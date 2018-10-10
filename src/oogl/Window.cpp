////////////////////////////////////////////////////////////////////////////////////////////////////
///! \file     Window.cpp
///! \brief    This file contains the definition of the class oogl::Window features.
///!           The class oogl::Window is the abstract class defining the primitive features of any
///!           object, instanciated from a child class, that aims to implement a graphical window.
///! \author   Stevy Kimpe
///! \version  1.0.0
////////////////////////////////////////////////////////////////////////////////////////////////////


// Include list
#include "OOGLHandler.hpp"
#include "OOGLHandlerFactory.hpp"

#include "Window.hpp"    // Inclusion of the header file which declares the class and
                         // features which get defined here.



//==================================================================================================
// Default constructor.
//==================================================================================================
oogl::Window::Window() :
m_children(std::set<Window *>()), m_dimensions({0,0,0,0}), m_isInit(false),
m_option(oogl::WindowOption::NONE), m_parent(nullptr), m_title(std::string())
{}


//==================================================================================================
// Constructors to set the title and the position
//==================================================================================================
oogl::Window::Window(std::string tittle, oogl::Rectangle const & dimensions) :
m_children(std::set<Window *>()), m_dimensions(dimensions), m_isInit(false),
m_option(oogl::WindowOption::NONE), m_parent(nullptr), m_title(std::string(tittle))
{}


//==================================================================================================
// Copy constructor.
//==================================================================================================
oogl::Window::Window(oogl::Window const & instance) :
m_children(std::set<Window *>(instance.m_children)), m_dimensions(instance.m_dimensions),
m_isInit(instance.m_isInit), m_option(instance.m_option), m_parent(instance.m_parent),
m_title(std::string(instance.m_title))
{}


//==================================================================================================
// Move constructor.
//==================================================================================================
oogl::Window::Window(oogl::Window && instance) :
m_children(std::move(instance.m_children)), m_dimensions(std::move(instance.m_dimensions)),
m_isInit(instance.m_isInit), m_option(instance.m_option), m_parent(instance.m_parent),
m_title(std::move(instance.m_title))
{}


//==================================================================================================
// Class destructor.
//==================================================================================================
oogl::Window::~Window() noexcept
{}


//==================================================================================================
// Method to override in child classes. Primitive method.
//==================================================================================================
void oogl::Window::init()
{
    // Check the instance is not yet initialized
    if (m_isInit) {
        throw oogl::OOGLException(oogl::ExceptionCode::WIN_ALREADY_CREATED);
    }

    // Get the library handler instance : the next line either access a handler or throw an except.
    oogl::OOGLHandlerFactory()
        .getGraphicLibraryHandler()
        .track(this);                   // Track the new initialized window

    // Indicates the instance has been created
    m_isInit = true;
}


//==================================================================================================
// Method to override in child classes. Here check the liberation is relevant (window was created).
//==================================================================================================
void oogl::Window::free()
{
    // Check the instance is created
    if (!m_isInit) {
        throw oogl::OOGLException(oogl::ExceptionCode::WIN_NOT_CREATED);
    }

    // Get the library handler instance : the next line is not supposed to fail here.
    oogl::OOGLHandlerFactory()
        .getGraphicLibraryHandler()
        .untrack(this);                 // Untrack the window
    
    // Indicates the instance is not initialized anymore
    m_isInit = false;
}


//==================================================================================================
// Method which activate an option flag.
//==================================================================================================
oogl::Window & oogl::Window::activateOption(WindowOption option) noexcept
{
    if (m_option == oogl::WindowOption::NONE) {          // no option to activate : return
        return *this;
    }

    if (option == oogl::WindowOption::ALL) {             // activate all the options using one flag
        m_option = oogl::WindowOption::ALL;
    } else if (m_option != oogl::WindowOption::ALL) {    // there are systems left to activate
        m_option = m_option | option;
    }

    return *this;
}

//==================================================================================================
// Method which deactivate an option of the creation.
//==================================================================================================
oogl::Window & oogl::Window::deactivateOption(WindowOption option) noexcept
{
    if (m_option == oogl::WindowOption::NONE) {          // no option to deactivate : return
        return *this;
    }

    if (option == oogl::WindowOption::ALL) {             // deactivate every options using one flag
        m_option = oogl::WindowOption::NONE;
    } else if (m_option != oogl::WindowOption::NONE) {   // there are options left to deactivate
        m_option = m_option & (!option);
    }

    return *this;
}


//==================================================================================================
// The calling becomes a child of the given instance.
//==================================================================================================
oogl::Window & oogl::Window::linkToParent(oogl::Window & window) noexcept
{
    m_parent = &window;
    window.m_children.insert(this);
    return *this;
}


//==================================================================================================
// Unlink the parent-child windows involved in the method call.
//==================================================================================================
oogl::Window & oogl::Window::looseParent() noexcept
{
    m_parent->m_children.erase(this);
    m_parent = nullptr;
    return *this;
}


//==================================================================================================
// Returns a reference to the parent method.
//==================================================================================================
oogl::Window & oogl::Window::getParent() const noexcept
{
    return *m_parent;
}


//==================================================================================================
// Returns the set of the attached children windows.
//==================================================================================================
std::set<oogl::Window *> oogl::Window::getChildren() const noexcept
{
    return m_children;
}


//==================================================================================================
// Title getter.
//==================================================================================================
std::string oogl::Window::getTitle() const noexcept
{
    return std::string(m_title);
}


//==================================================================================================
// Title setter.
//==================================================================================================
void oogl::Window::setTitle(std::string const & title) noexcept
{
    m_title = std::string(title);
}


//==================================================================================================
// Dimensions getter.
//==================================================================================================
oogl::Rectangle oogl::Window::getDimensions() const noexcept
{
    return oogl::Rectangle(m_dimensions);
}


//==================================================================================================
// Dimensions setter.
//==================================================================================================
void oogl::Window::setDimensions(oogl::Rectangle const & dimensions) noexcept
{
    m_dimensions = oogl::Rectangle(dimensions);
}