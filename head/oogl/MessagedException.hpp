////////////////////////////////////////////////////////////////////////////////////////////////////
///! \file     MessagedException.hpp
///! \brief    This file contains the declaration of the class oogl::MessagedException and its
///!           features. The class oogl::MessagedException is a simple featured class whose only aim
///!           is to handle special C++ exception, registering a message. It is inherited by
///!           OOGLException which is widely used by the other classes of this graphic framework.
///! \author   Stevy Kimpe
///! \version  1.0.0
////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma once                                       // Non standard include guard

#ifndef OOGL_MESSAGEDEXCEPTION_HPP_INCLUDED        // Standard include guard
#define OOGL_MESSAGEDEXCEPTION_HPP_INCLUDED


// Include list
#include <exception>
#include <string>



////////////////////////////////////////////////////////////////////////////////////////////////////
///! \namespace  oogl MessagedException.hpp
///! \brief      The namespace oogl contains the different features (classes, P.O.D. structures...)
///!             generalizing the current object oriented graphic framework. Most of the classes are
///!             inherited in other specific namespaces, where the methods implementation is adapted
///!             to the given embedded graphic library.
///! \version    1.0.0
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace oogl
{


    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///! \class    MessagedException MessagedException.hpp
    ///! \brief    The class MessagedException is a simple exception class that stores an error
    ///!           message given during exception creation, and returns it whenever required.
    ///! \version  1.0.0
    ///! \see      oogl::OOGLException
    ////////////////////////////////////////////////////////////////////////////////////////////////
    class MessagedException : public std::exception
    {
        public:

        // No default constructor : a message is required.
        MessagedException() noexcept = delete;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief            Class constructor ; requires an exception message.
        ///! \param message    Exception message that gets thrown with an instance of the class.
        ///! \version          1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        MessagedException(std::string const & message) noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief              Copy constructor.
        ///! \param exception    Another instance of MessagedException, whose value is copied.
        ///! \version            1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        MessagedException(MessagedException const & exception) noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief              Move constructor.
        ///! \param exception    Another instance of MessagedException, whose value is moved. The
        ///!                     initial object is left in a valid but unspecified state.
        ///! \version            1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        MessagedException(MessagedException && exception) noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief    Class destructor.
        ///! \version  1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~MessagedException() noexcept = default;

        ////////////////////////////////////////////////////////////////////////////////////////////
        ///! \brief     Get the exception message.
        ///! \return    The exception message as a C-like string.
        ///! \version   1.0.0
        ////////////////////////////////////////////////////////////////////////////////////////////
        virtual const char * what() const throw();


        private:

        std::string    m_message;    ///!< Exception message.

    };

}



#endif    // OOGL_MESSAGEDEXCEPTION_HPP_INCLUDED
