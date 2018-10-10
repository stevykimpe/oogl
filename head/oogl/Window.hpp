////////////////////////////////////////////////////////////////////////////////////////////////////
///! \file     Window.hpp
///! \brief    This file contains the declaration of the class oogl::Window and its features.
///!           The class oogl::Window is the abstract class defining the primitive features of any
///!           object, instanciated from a child class, that aims to implement a graphical window.
///! \author   Stevy Kimpe
///! \version  1.0.0
////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma once                            // Non standard include guard

#ifndef OOGL_WINDOW_HPP_INCLUDED        // Standard include guard
#define OOGL_WINDOW_HPP_INCLUDED


// Standard include list
#include <set>
#include <string>

// Project include list
#include "ITrackableObject.hpp"
#include "OOGLException.hpp"



////////////////////////////////////////////////////////////////////////////////////////////////////
///! \namespace  oogl Window.hpp
///! \brief      The namespace oogl contains the different features (classes, P.O.D. structures...)
///!             generalizing the current object oriented graphic framework. Most of the classes are
///!             inherited in other specific namespaces, where the methods implementation is adapted
///!             to the given embedded graphic library.
///! \version    1.0.0
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace oogl
{


    #ifndef OOGL_RECTANGLE_STRUCT_DEFINED        // Guarantee the structure is only defined once
    #define OOGL_RECTANGLE_STRUCT_DEFINED

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///! \struct   Rectangle Window.hpp
    ///! \brief    Describe a rectangle shape through the position of its top left corner, its
    ///!           width and its height.
    ///! \version  1.0.0
    ////////////////////////////////////////////////////////////////////////////////////////////////
    struct Rectangle
    {
        unsigned int xPosition;
        unsigned int yPosition;
        unsigned int width;
        unsigned int height;
    };

    // Typedef to remove the struct keyword from the type
    typedef struct Rectangle Rectangle;

    #endif    // OOGL_RECTANGLE_STRUCT_DEFINED




    #ifndef OOGL_WINDOWOPTION_ENUM_DEFINED        // Guarantee the enumeration is only defined once
    #define OOGL_WINDOWOPTION_ENUM_DEFINED

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///! \enum     WindowOption Window.hpp
    ///! \brief    Lists the different options supported by a Window instance for its creation, i.e.
    ///!           its call for <code>Window::create();</code>.
    ///!           Please, note the flags associated with this options can be combined through the
    ///!           use of the | and & and ! operators that are overloadded.
    ///! \version  1.0.0
    ////////////////////////////////////////////////////////////////////////////////////////////////
    enum WindowOption : uint32_t
    {
        ALL                = 1 << 0,   ///!< Flag used to (de)activate all the options.
        FULLSCREEN         = 1 << 1,   ///!< Flag used to (de)activate the full screen mode.
        FULLSCREEN_DESKTOP = 1 << 2,   ///!< Flag used to (de)activate the full screen desktop mode.
        RESIZABLE          = 1 << 3,   ///!< Flag used to (de)activate the resizability option.
        SHOWN              = 1 << 4,   ///!< Flag used to (un)make the window visible.
        HIDDEN             = 1 << 5,   ///!< Flag used to (un)make the window hidden.
        MINIMIZED          = 1 << 6,   ///!< Flag used to (un)make the window minimized.
        MAXIMIZED          = 1 << 7,   ///!< Flag used to (un)make the window maximized.
        GRABBED            = 1 << 8,   ///!< Flag used to give/take the grab to the window.
        INPUT_FOCUS        = 1 << 9,   ///!< Flag used to give/take input focus to the window.
        MOUSE_FOCUS        = 1 << 10,  ///!< Flag used to give/take mouse focus to the window.

        NONE               = 0         ///!< Flag to use to deal with non of those subsystems.
    };


    // Overload the OR '|' operator for the flags of the above enumeration.
    inline WindowOption operator|(WindowOption opt1, WindowOption opt2)
    {
        return static_cast<WindowOption>(
            static_cast<uint32_t>(opt1) | static_cast<uint32_t>(opt2)
        );
    }

    // Overload the AND '&' operator for the flags of the above enumeration.
    inline WindowOption operator&(WindowOption opt1, WindowOption opt2)
    {
        return static_cast<WindowOption>(
            static_cast<uint32_t>(opt1) & static_cast<uint32_t>(opt2)
        );
    }

    // Overload the NOT '!' operator for the flags of the above enumeration.
    inline WindowOption operator!(WindowOption opt)
    {
        return static_cast<WindowOption>(! static_cast<uint32_t>(opt));
    }


    #endif    // OOGL_WINDOWOPTION_ENUM_DEFINED




    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///! \class    Window Window.hpp
    ///! \brief    Primitive class defining the main features of the graphic library handlers, that
    ///!           are objects in charge of the initialization of the given library, and a proper
    ///!           exit with memory space getting free.
    ///! \version  1.0.0
    ///! \see      oogl::OOGLHandlerFactory
    ///! \see      oogl::ITrackableObject
    ////////////////////////////////////////////////////////////////////////////////////////////////
    class Window : public ITrackableObject
    {
        public:

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief    Class constructor.
        ///! \version  1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        Window();

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief               Class constructor which sets the title and the dimensions of the
        ///!                      window to design.
        ///! \param tittle        Title of the Window, to give to the Operating System.
        ///! \param dimensions    Window's dimensions registered in a Rectangle instance.
        ///! \version             1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        Window(std::string tittle, oogl::Rectangle const & dimensions);

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief               Copy constructor.
        ///! \param window        Instance to copy.
        ///! \version             1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        Window(Window const & instance);

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief               Move constructor.
        ///! \param window        Instance to move into the new one.
        ///! \version             1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        Window(Window && instance);

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief               Class destructor.
        ///! \version             1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~Window() noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief                        Method, to be fully implemented in child classes, for a
        ///!                               window to get properly initialized.
        ///! \throw oogl::OOGLException    When there is a failure in the initialization process.
        ///! \version                      1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual void init();

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief                        Method, to be fully implemented in child classes, for a
        ///!                               window to get properly free.
        ///! \throw oogl::OOGLException    When there is a failure during the liberation process.
        ///! \version                      1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual void free();

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief           Activate the given option or combination of options.
        ///! \param option    Flag associated with the option or combination of options to activate.
        ///! \return          A reference to the calling instance.
        ///! \version         1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual Window & activateOption(WindowOption option) noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief           Deactivate the given option or combination of options.
        ///! \param option    Flag associated with the option or combination of options to
        ///!                  deactivate.
        ///! \return          A reference to the calling instance.
        ///! \version         1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual Window & deactivateOption(WindowOption option) noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief           Link the calling instance to another instance of the class. The
        ///!                  calling instance will become the child of the other one, and will
        ///!                  consequently be slaved to it.
        ///! \param window    Instance that becomes the master of the calling one.
        ///! \return          A reference to the calling instance.
        ///! \version         1.0.0
        ///!
        ///! <p>Link the calling instance to another instance of the class. The calling instance
        ///! will become the child of the other one, and will consequently be slaved to it.</p>
        ///! <p>A parent instance slaves the child one as the destruction of the parent instance
        ///! causes the destruction of the child one. Note destruction does not mean the destructor
        ///! gets called, but the method <code>Window::destroy()</code> that makes an instance being
        ///! unable to get used, but free all dynamically allocated memory.
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual Window & linkToParent(Window & window) noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief    Loose the link between the calling instance and its parent.
        ///! \return   A reference to the calling instance.
        ///! \version  1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual Window & looseParent() noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief                        Get the parent Window instance.
        ///! \return                       A reference to the parent instance.
        ///! \throw oogl::OOGLException    When no instances have been linked to the calling one as
        ///!                               a parent.
        ///! \version                      1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual Window & getParent() const noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief    Get the list of children Window instances.
        ///! \return   The set of pointers of the children instances.
        ///! \version  1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::set<Window *> getChildren() const noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief    Get the title attached to the Window instance.
        ///! \return   A string containing the title.
        ///! \version  1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::string getTitle() const noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief          Set the title attached to the Window instance.
        ///! \param title    A string containing the title to be attached to the Window instance.
        ///! \version        1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTitle(std::string const & title) noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief    Get the dimensions of the Window instance.
        ///! \return   A structure containing the dimensions.
        ///! \version  1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual oogl::Rectangle getDimensions() const noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief          Set the dimensions of the Window instance.
        ///! \param title    A structure containing the dimensions to get set to this instance.
        ///! \version        1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setDimensions(oogl::Rectangle const & dimensions) noexcept;



        private:

        std::string           m_title;         ///<! Title attached to the window.
        oogl::Rectangle       m_dimensions;    ///!< Contains the position and size of the window.
        Window *              m_parent;        ///!< Points to the parent window.
        std::set<Window *>    m_children;      ///!< Contains the child/slaved windows.
        WindowOption          m_option;        ///!< Options used for the creation of the window.
        bool                  m_isInit;        ///!< Indicates whether the window is initialized.

    };

}



#endif    // OOGL_WINDOW_HPP_INCLUDED
