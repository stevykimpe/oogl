////////////////////////////////////////////////////////////////////////////////////////////////////
///! \file     OOGLHandler.hpp
///! \brief    This file contains the declaration of the class oogl::OOGLHandler and its features.
///!           The class oogl::OOGLHandler is the class inherited by the other classes of the
///!           framework that are in charge of the graphic library initialization, the data storage
///!           and the process to properly free the memory space.
///! \author   Stevy Kimpe
///! \version  1.0.0
////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma once                                // Non standard include guard

#ifndef OOGL_OOGLHANDLER_HPP_INLUDED        // Standard include guard
#define OOGL_OOGLHANDLER_HPP_INLUDED


// Standard include list
#include <set>

// Project include list
#include "ITrackableObject.hpp"
#include "OOGLException.hpp"



////////////////////////////////////////////////////////////////////////////////////////////////////
///! \namespace  oogl OOGLHandler.hpp
///! \brief      The namespace oogl contains the different features (classes, P.O.D. structures...)
///!             generalizing the current object oriented graphic framework. Most of the classes are
///!             inherited in other specific namespaces, where the methods implementation is adapted
///!             to the given embedded graphic library.
///! \version    1.0.0
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace oogl
{


    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///! \enum     MediaSystem OOGLHandler.hpp
    ///! \brief    Lists the different subsystems handled by this framework.
    ///!           Please, note the flags associated with this subsystem can be combined through the
    ///!           use of the | and & and ! operators that are overloadded.
    ///! \version  1.0.0
    ////////////////////////////////////////////////////////////////////////////////////////////////
    enum MediaSystem : uint32_t
    {
        ALL             = 1 << 0,    ///!< Flag to use to deal with all the subsystems.
        AUDIO           = 1 << 1,    ///!< Flag to use to deal with the audio subsystem.
        EVENTS          = 1 << 2,    ///!< Flag to use to deal with the events subsystem.
        GAME_CONTROLLER = 1 << 3,    ///!< Flag to use to deal with the game controller subsystem.
        HAPTIC          = 1 << 4,    ///!< Flag to use to deal with the haptic subsystem.
        JOYSTICK        = 1 << 5,    ///!< Flag to use to deal with the joystick subsystem.
        TIMER           = 1 << 6,    ///!< Flag to use to deal with the timer subsystem.
        VIDEO           = 1 << 7,    ///!< Flag to use to deal with the video subsystem.

        NONE            = 0          ///!< Flag to use to deal with non of those subsystems.
    };


    // Overload the OR '|' operator for the flags of the above enumeration.
    inline MediaSystem operator|(MediaSystem sys1, MediaSystem sys2)
    {
        return static_cast<MediaSystem>(
            static_cast<uint32_t>(sys1) | static_cast<uint32_t>(sys2)
        );
    }

    // Overload the AND '&' operator for the flags of the above enumeration.
    inline MediaSystem operator&(MediaSystem sys1, MediaSystem sys2)
    {
        return static_cast<MediaSystem>(
            static_cast<uint32_t>(sys1) & static_cast<uint32_t>(sys2)
        );
    }

    // Overload the NOT '!' operator for the flags of the above enumeration.
    inline MediaSystem operator!(MediaSystem sys)
    {
        return static_cast<MediaSystem>(! static_cast<uint32_t>(sys));
    }




    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///! \class    OOGLHandler OOGLHandler.hpp
    ///! \brief    Abstract class defining the main features of the graphic library handlers, that
    ///!           are objects in charge of the initialization of the given library, and a proper
    ///!           exit with memory space getting free.
    ///! \version  1.0.0
    ///! \see      oogl::OOGLHandlerFactory
    ////////////////////////////////////////////////////////////////////////////////////////////////
    class OOGLHandler
    {
        public:

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief                        Initialize the graphic library features.
        ///!                               Overriden method in child classes as the initialization
        ///!                               strongly depends on the library which is used.
        ///! \throw oogl::OOGLException    When the system is already initialized.
        ///! \version                      1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual void init();

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief                        Stop the graphic library features and free allocated
        ///!                               memory space. Overriden method in child classes as
        ///!                               freeing the used memory space strongly depends on the
        ///!                               library which is involved.
        ///! \throw oogl::OOGLException    When the system has not been initialized.
        ///! \version                      1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual void exit();

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief         Activate the given system or combination of systems.
        ///! \arg system    Flag associated with the system or combination of systems to activate.
        ///! \return        A reference to the calling instance.
        ///! \version       1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual OOGLHandler & activateSystem(MediaSystem system) noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief         Deactivate the given system or combination of systems.
        ///! \arg system    Flag associated with the system or combination of systems to deactivate.
        ///! \return        A reference to the calling instance.
        ///! \version       1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual OOGLHandler & deactivateSystem(MediaSystem system) noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief         Give a new trackable object to keep trace on to the GL handler.
        ///! \arg object    Object to get tracked by the graphic library handler.
        ///! \return        A reference to the calling instance.
        ///! \version       1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual OOGLHandler & track(ITrackableObject * object) noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief         Delete a trackable object from the track list of the GL handler.
        ///! \arg object    Object to get untracked by the graphic library handler.
        ///! \return        A reference to the calling instance.
        ///! \version       1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual OOGLHandler & untrack(ITrackableObject * object) noexcept;



        protected:

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief    Class constructor. Should never be called outside child classes or an
        ///!           OOGLHandlerFactory instance. This is why it is protected : it can thus be
        ///!           inherited in child classes. The child constructor will be called in the
        ///!           factory instance.
        ///! \version  1.0.0
        ///! \see      oogl::OOGLHandlerFactory
        ////////////////////////////////////////////////////////////////////////////////////////////
        OOGLHandler();

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief    Class destructor. For the same reason than for the constructor, it is
        ///!           declared protected.
        ///! \version  1.0.0
        ///! \see      oogl::OOGLHandlerFactory
        ////////////////////////////////////////////////////////////////////////////////////////////
        ~OOGLHandler() = default;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief    Get the combination of flags furnishing the activated systems.
        ///! \version  1.0.0
        ///! \see      oogl::OOGLHandler::m_systems
        ////////////////////////////////////////////////////////////////////////////////////////////
        inline MediaSystem getActivatedSystems() const    { return m_systems; }

        // For the same reasons, no copy constructor are wanted.
        OOGLHandler(OOGLHandler const &) = delete;

        // For the same reasons, no assignement operator are wanted.
        OOGLHandler & operator=(OOGLHandler const &) = delete;



        private:

        bool           m_isInitialized;    ///!< Indicates whether the library has been initilized.
        MediaSystem    m_systems;          ///!< Flag associated to the tracked systems.

        std::set<oogl::ITrackableObject *>    m_tracker;    /*!< Set in charge of the trackable
                                                             *   objects pointers storage.   */


    };

}



#endif    // OOGL_OOGLHANDLER_HPP_INLUDED