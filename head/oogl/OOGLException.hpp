////////////////////////////////////////////////////////////////////////////////////////////////////
///! \file     OOGLException.hpp
///! \brief    This file contains the declaration of the class oogl::OOGLException and its features.
///!           The class oogl::OOGLException is the class used by the framework to send exceptions
///!           regarding the other classes of this graphic framework.
///! \author   Stevy Kimpe
///! \version  1.0.0
////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma once                                   // Non standard include guard

#ifndef OOGL_OOGLEXCEPTION_HPP_INCLUDED        // Standard include guard
#define OOGL_OOGLEXCEPTION_HPP_INCLUDED


// Standard include list
#include <functional>
#include <map>

// Project include list
#include "MessagedException.hpp"



////////////////////////////////////////////////////////////////////////////////////////////////////
///! \namespace  oogl OOGLException.hpp
///! \brief      The namespace oogl contains the different features (classes, P.O.D. structures...)
///!             generalizing the current object oriented graphic framework. Most of the classes are
///!             inherited in other specific namespaces, where the methods implementation is adapted
///!             to the given embedded graphic library.
///! \version    1.0.0
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace oogl
{
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///! \enum     ExceptionCode OOGLException.hpp
    ///! \brief    Enumerate the different exception code of the framework.
    ///! \version  1.0.0
    ///! \see      oogl::OOGLException
    ////////////////////////////////////////////////////////////////////////////////////////////////
    enum ExceptionCode
    {
        NO_EXCEPTION                       ///!< No exception.
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///! \class    OOGLException OOGLException.hpp
    ///! \brief    Simple exception class that stores exception code and message. This class gets
    ///!           set up by the OOGLHandler that is instanciated : it allows to set the private
    ///!           static attributes calling the function that gets the error encountered by the
    ///!           graphic library.
    ///! \version  1.0.0
    ///! \see      oogl::MessagedException
    ///! \see      oogl::ExceptionCode
    ////////////////////////////////////////////////////////////////////////////////////////////////
    class OOGLException : public oogl::MessagedException
    {
        public:

        // No default constructor
        OOGLException() noexcept = delete;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief         Class constructor ; requires an exception code.
        ///! \param code    Exception code which references the exception to throw.
        ///! \version       1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        OOGLException(oogl::ExceptionCode exceptionCode) noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief              Copy constructor.
        ///! \param exception    Another instance of OOGLException, whose value is copied.
        ///! \version            1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        OOGLException(OOGLException const & exception) noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief              Move constructor.
        ///! \param exception    Another instance of OOGLException, whose value is moved. The
        ///!                     initial object is left in a valid but unspecified state.
        ///! \version            1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        OOGLException(OOGLException && exception) noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief    Class destructor.
        ///! \version  1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~OOGLException() noexcept = default;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief     Get the exception message.
        ///! \return    The exception message as a C-like string.
        ///! \version   1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual const char * what() const throw();

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief             Set the external method that is called to get a more detailed error
        ///!                    message.
        ///! \param getError    Function of the external graphic library that makes it possible to
        ///!                    get a precise description of the error encountered by the graphic
        ///!                    library.
        ///! \version           1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        static void setExternalErrorFunction(std::function<std::string(void)> getError);

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief             Set the external method that is called to get a more detailed error
        ///!                    message.
        ///! \param getError    Function of the external graphic library that makes it possible to
        ///!                    get a precise description of the error encountered by the graphic
        ///!                    library.
        ///! \version           1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        static std::string getMessageFromCode(oogl::ExceptionCode code) noexcept;



        private:

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief  External function making it possible to get a more detailed exception message
        ///!         using the functions of the used external graphic library.
        ////////////////////////////////////////////////////////////////////////////////////////////
        static std::function<std::string(void)>   getExternalExceptionMessage;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief  Map associating the exception codes to the exception messages.
        ////////////////////////////////////////////////////////////////////////////////////////////
        static std::map<ExceptionCode, std::string>    mapExceptionCodeMessage;


        ExceptionCode   m_code;    ///!< Code related to the exception
        

    };

}



#endif    // OOGL_OOGLEXCEPTION_HPP_INCLUDED
