////////////////////////////////////////////////////////////////////////////////////////////////////
///! \file     OOGLHandlerFactory.hpp
///! \brief    This file contains the declaration of the class oogl::OOGLHandlerFactory and its
///!           features. The class oogl::OOGLHandlerFactory stores the active graphic library
///!           handler, and makes it available to other classes.
///! \author   Stevy Kimpe
///! \version  1.0.0
///! \see      oogl::OOGLHandler
///!
///! <p>To tell the truth, the only goal of this class is to avoid making the graphic library
///! handler, designed through the class oogl::OOGLHandler, follow the singleton pattern. Indeed,
///! this pattern ensures the unicity of the instance of the class, which is what is wanted for
///! the graphic library handler, but it also prevents a class from being able to be inherited by
///! others.</p>
///! <p>A class implementing a graphic library handler inherits from oogl::OOGLHandler, which make
///! it not possible to be implemented as a singleton. The class developped in this file creates
///! and stores a unique graphic library handler that then can be accessed.
////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma once                                        // Non standard include guard

#ifndef OOGL_OOGLHANDLERFACTORY_HPP_INCLUDED        // Standard include guard
#define OOGL_OOGLHANDLERFACTORY_HPP_INCLUDED


// No includes : simple forward class declaration



////////////////////////////////////////////////////////////////////////////////////////////////////
///! \namespace  oogl OOGLHandlerFactory.hpp
///! \brief      The namespace oogl contains the different features (classes, P.O.D. structures...)
///!             generalizing the current object oriented graphic framework. Most of the classes are
///!             inherited in other specific namespaces, where the methods implementation is adapted
///!             to the given embedded graphic library.
///! \version    1.0.0
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace oogl
{

    
    // Forward declaration
    class OOGLHandler;
    
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///! \enum     GraphicLibrary OOGLHandlerFactory.hpp
    ///! \brief    Enumerate the different accessible graphic library of the framework.
    ///! \version  1.0.0
    ////////////////////////////////////////////////////////////////////////////////////////////////
    enum GraphicLibrary                // TO DO !
    {
        UNDEFINED                      ///!< No library specified.
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///! \class    OOGLHandlerFactory OOGLHandlerFactory.hpp
    ///! \brief    Special factory class designed to create and store a unique graphic library
    ///!           handler, that can then be accessed by other classes through OOGLHandlerFactory.
    ///! \version  1.0.0
    ////////////////////////////////////////////////////////////////////////////////////////////////
    class OOGLHandlerFactory
    {
        public:

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief    Class constructor.
        ///! \version  1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        OOGLHandlerFactory() noexcept = default;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief    Class destructor.
        ///! \version  1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        ~OOGLHandlerFactory() = default;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief                        Create if possible a new graphic library handler that is
        ///!                               specified through the input label.
        ///! \param library                Label associated to the library to use, the library
        ///!                               handler will get created according to the chosen library.
        ///! \throw oogl::OOGLException    When the factory is asked to create a new graphic
        ///!                               library handler instance while there already is one.
        ///! \version                      1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        void createGraphicLibraryHandler(oogl::GraphicLibrary library);

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief                        Destroy the instanciated graphic library handler.
        ///! \throw oogl::OOGLException    When the factory is asked to destroy a graphic library
        ///!                               handler instance while none were created.
        ///! \version                      1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        void destroyGraphicLibraryHandler();

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief                        Get a reference to the unique graphic library handler.
        ///! \return                       A reference to the instanciated graphic library handler.
        ///! \throw oogl::OOGLException    When no graphic library handlers have been created.
        ///! \version                      1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        oogl::OOGLHandler & getGraphicLibraryHandler() const;



        private:

        static oogl::OOGLHandler *   s_graphicLibraryHandler;  ///!< Instance of the unique handler


    };
}



#endif
