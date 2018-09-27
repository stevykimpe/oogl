////////////////////////////////////////////////////////////////////////////////////////////////////
///! \file     MessagedException.cpp
///! \brief    This file contains the definition of the class oogl::MessagedException and its
///!           features. The class oogl::MessagedException is a simple featured class whose only aim
///!           is to handle special C++ exception, registering a message. It is inherited by
///!           OOGLException which is widely used by the other classes of this graphic framework.
///! \author   Stevy Kimpe
///! \version  1.0
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "MessagedException.hpp"    // Inclusion of the header file which declares the class and
                                    // features which get defined here.



//==================================================================================================
// Class constructor implementation
//==================================================================================================
oogl::MessagedException::MessagedException(std::string const & message) noexcept :
m_message(std::string(message))
{}


//==================================================================================================
// Copy constructor implementation
//==================================================================================================
oogl::MessagedException::MessagedException(MessagedException const & exception) noexcept :
m_message(std::string(exception.m_message))
{}


//==================================================================================================
// Move constructor implementation
//==================================================================================================
oogl::MessagedException::MessagedException(MessagedException && exception) noexcept :
m_message(std::move(exception.m_message))
{}


//==================================================================================================
// Method that returns the exception message.
//==================================================================================================
const char * oogl::MessagedException::what() const throw()
{
    return m_message.c_str();
}
