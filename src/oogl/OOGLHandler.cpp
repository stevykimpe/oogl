////////////////////////////////////////////////////////////////////////////////////////////////////
///! \file     OOGLHandler.cpp
///! \brief    This file contains the definition of the class oogl::OOGLHandler and its features.
///!           The class oogl::OOGLHandler is the class inherited by the other classes of the
///!           framework that are in charge of the graphic library initialization, the data storage
///!           and the process to properly free the memory space.
///! \author   Stevy Kimpe
///! \version  1.0.0
///! \see      oogl::OOGLHandler
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "OOGLHandler.hpp"    // Inclusion of the header file which declares the class and
                              // features which get defined here.



//==================================================================================================
// Primitive of the methods in charge of the library initialization.
// Just performs a test checking it is possible to initialize the library.
// Rest of the implementation must come in child classes.
//==================================================================================================
void oogl::OOGLHandler::init()
{
    if (m_isInitialized) { // The library has already been initialized
        throw oogl::OOGLException(oogl::ExceptionCode::LIB_ALREADY_INIT);
    }

    // No exception to throw here, initialize the library

    m_isInitialized = true;
}


//==================================================================================================
// Primitive of the methods in charge of the library exit.
// Just performs a test checking it is possible to exit the library.
// Rest of the implementation must come in child classes. 
//==================================================================================================
void oogl::OOGLHandler::exit()
{
    if (! m_isInitialized) { // The library is not yet initialized
        throw oogl::OOGLException(oogl::ExceptionCode::LIB_NOT_INIT);
    }

    // No exception to throw here

    // Destroy the tracked objects
    std::set<ITrackableObject*>::iterator objectIt;
    for (objectIt = m_tracker.begin(); objectIt != m_tracker.end(); objectIt++) {
        (*objectIt)->destroy();
    }

    m_tracker = std::set<ITrackableObject*>();  // Make the tracker set empty

    m_isInitialized = false;    // Library marked as unitialized


}


//==================================================================================================
// Method which activates the library subsystem.
//==================================================================================================
oogl::OOGLHandler & oogl::OOGLHandler::activateSystem(MediaSystem system) noexcept
{
    if (m_systems == oogl::MediaSystem::NONE) {          // no system to activate : return
        return *this;
    }

    if (system == oogl::MediaSystem::ALL) {              // activate all the system using one flag
        m_systems = oogl::MediaSystem::ALL;
    } else if (m_systems != oogl::MediaSystem::ALL) {    // there are systems left to activate
        m_systems = m_systems | system;
    }

    return *this;
}


//==================================================================================================
// Method which deactivates the library subsystem.
//==================================================================================================
oogl::OOGLHandler & oogl::OOGLHandler::deactivateSystem(MediaSystem system) noexcept
{
    if (m_systems == oogl::MediaSystem::NONE) {          // no system to deactivate : return
        return *this;
    }

    if (system == oogl::MediaSystem::ALL) {              // deactivate all the system using one flag
        m_systems = oogl::MediaSystem::NONE;
    } else if (m_systems != oogl::MediaSystem::ALL) {    // there are systems left to deactivate
        m_systems = m_systems & (!system);
    }

    return *this;
}


//==================================================================================================
// Method which registers a new trackable object.
//==================================================================================================
oogl::OOGLHandler & oogl::OOGLHandler::track(ITrackableObject * object) noexcept
{
    if (object == nullptr) {    // the pointer does not point to an actual object
        throw oogl::OOGLException(oogl::ExceptionCode::OOGLHANDLER_NULL_OBJ_TRACK);
    }

    m_tracker.insert(object);   // Add the object to the tracker set.

    return *this;
}


//==================================================================================================
// Method which unregisters a given trackable object.
//==================================================================================================
oogl::OOGLHandler & oogl::OOGLHandler::untrack(ITrackableObject * object) noexcept
{
    if (object == nullptr) {    // the pointer does not point to an actual object
        throw oogl::OOGLException(oogl::ExceptionCode::OOGLHANDLER_NULL_OBJ_TRACK);
    }

    m_tracker.erase(object);   // Add the object to the tracker set.

    return *this;
}


//==================================================================================================
// Protected class constructor.
//==================================================================================================
oogl::OOGLHandler::OOGLHandler() :
m_isInitialized(false),
m_systems(oogl::MediaSystem::NONE),
m_tracker(std::set<ITrackableObject*> ())
{}
