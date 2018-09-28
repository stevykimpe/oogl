////////////////////////////////////////////////////////////////////////////////////////////////////
///! \file     OOGLHandlerFactory.cpp
///! \brief    This file contains the definition of the class oogl::OOGLHandlerFactory and its
///!           features. The class oogl::OOGLHandlerFactory stores the active graphic library
///!           handler, and makes it available to other classes. It is designed with respect to the
///!           singleton pattern, so that any other classes of the framework can easily access the
///!           one and unique instance of the class.
///! \author   Stevy Kimpe
///! \version  1.0
///! \see      oogl::OOGLHandler
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "OOGLHandlerFactory.hpp"    // Inclusion of the header file which declares the class and
                                     // features which get defined here.

// Other required includes
#include "OOGLException.hpp"



//==================================================================================================
// Set the static member with default value.
//==================================================================================================
oogl::OOGLHandler *  oogl::OOGLHandlerFactory::s_graphicLibraryHandler = nullptr;


//==================================================================================================
// Method creating a new graphic library handler.
//==================================================================================================
void oogl::OOGLHandlerFactory::createGraphicLibraryHandler(oogl::GraphicLibrary library)
{
    // Test a GL handler is not already instanciated
    if (s_graphicLibraryHandler != nullptr) {
        throw oogl::OOGLException(oogl::ExceptionCode::OOGL_HANDLER_ALREADY_CREATED);
    }

    // According to the specified library, the right constructor gets called.
    if (/* Library test */true) {           // TO DO!
        ;
    } else {
        ;
    }
}


//==================================================================================================
// Method destroying the instanciated graphic library handler.
//==================================================================================================
void oogl::OOGLHandlerFactory::destroyGraphicLibraryHandler()
{
    // Test the handler exist before returning it
    if (s_graphicLibraryHandler == nullptr) {
        throw oogl::OOGLException(oogl::ExceptionCode::OOGL_HANDLER_NOT_CREATED);
    }

    // Exit properly the library system
    s_graphicLibraryHandler->exit();

    // Delete the pointer to the instance
    s_graphicLibraryHandler = nullptr;
}


//==================================================================================================
// Method returning a reference to the instanciated graphic library handler.
//==================================================================================================
oogl::OOGLHandler & oogl::OOGLHandlerFactory::getGraphicLibraryHandler() const
{
    // Test the handler exist before returning it
    if (s_graphicLibraryHandler == nullptr) {
        throw oogl::OOGLException(oogl::ExceptionCode::OOGL_HANDLER_NOT_CREATED);
    }

    // Returns the reference
    return *s_graphicLibraryHandler;
}