////////////////////////////////////////////////////////////////////////////////////////////////////
///! \file     ITrackableObject.hpp
///! \brief    This file contains the declaration of the class oogl::ITrackableObject and its
///!           features. The class oogl::ITrackableObject is an interface describing objects that
///!           get tracked by the graphic library handler so as to be able to free the memory space
///!           at the end of the program.
///! \author   Stevy Kimpe
///! \version  1.0.0
////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma once                                      // Non standard include guard

#ifndef OOGL_ITRACKABLEOBJECT_HPP_INCLUDED        // Standard include guard
#define OOGL_ITRACKABLEOBJECT_HPP_INCLUDED


// No required includes



////////////////////////////////////////////////////////////////////////////////////////////////////
///! \namespace  oogl ITrackableObject.hpp
///! \brief      The namespace oogl contains the different features (classes, P.O.D. structures...)
///!             generalizing the current object oriented graphic framework. Most of the classes are
///!             inherited in other specific namespaces, where the methods implementation is adapted
///!             to the given embedded graphic library.
///! \version    1.0.0
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace oogl
{

    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///! \class    ITrackableObject ITrackableObject.hpp
    ///! \brief    The interface class ITrackableObject describes any objects getting tracked by a
    ///!           graphic library handler.
    ///! \version  1.0.0
    ///! \see      oogl::OOGLHandler
    ////////////////////////////////////////////////////////////////////////////////////////////////
    class ITrackableObject
    {
        public:

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief    Virtual class desctructor.
        ///! \version  1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~ITrackableObject() noexcept = default;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief                        Method, to be implemented in child classes, for an object
        ///!                               to get properly created.
        ///! \throw oogl::OOGLException    When there is a failure during the creation process.
        ///! \version                      1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual void create() = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief                        Method, to be implemented in child classes, for an object
        ///!                               to get properly destroyed without memory leak.
        ///! \throw oogl::OOGLException    When there is a failure during the destruction process.
        ///! \version                      1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual void destroy() = 0;

    };

}



#endif    // OOGL_ITRACKABLEOBJECT_HPP_INCLUDED
