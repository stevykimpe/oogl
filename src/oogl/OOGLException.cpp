////////////////////////////////////////////////////////////////////////////////////////////////////
///! \file     OOGLException.hpp
///! \brief    This file contains the definition of the class oogl::OOGLException and its features.
///!           The class oogl::OOGLException is the class used by the framework to send exceptions
///!           regarding the other classes of this graphic framework.
///! \author   Stevy Kimpe
///! \version  1.0.0
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "OOGLException.hpp"    // Inclusion of the header file which declares the class and
                                // features which get defined here.



//==================================================================================================
// Set the static member with default value.
//==================================================================================================
std::function<std::string(void)> oogl::OOGLException::s_getExternalExceptionMessage
    = [] (void) { return std::string(""); };    // Default : no additional message to return

// The map associating exception codes to exception
// messages is defined at the end of the file.


//==================================================================================================
// Class constructor implementation
//==================================================================================================
oogl::OOGLException::OOGLException(oogl::ExceptionCode exceptionCode) noexcept :
m_code(exceptionCode), MessagedException(oogl::OOGLException::getMessageFromCode(exceptionCode))
{}


//==================================================================================================
// Copy constructor implementation
//==================================================================================================
oogl::OOGLException::OOGLException(OOGLException const & exception) noexcept :
m_code(exception.m_code), MessagedException(exception)
{}


//==================================================================================================
// Move constructor implementation
//==================================================================================================
oogl::OOGLException::OOGLException(OOGLException && exception) noexcept :
m_code(exception.m_code), MessagedException(std::move(exception))
{}


//==================================================================================================
// Method that returns the exception message
//==================================================================================================
const char * oogl::OOGLException::what() const throw()
{
    return (
        std::string(oogl::MessagedException::what()) + "\n"
        + oogl::OOGLException::s_getExternalExceptionMessage()
    ).c_str();
}


//==================================================================================================
// Set the external function that details graphic library error message
//==================================================================================================
void oogl::OOGLException::setExternalErrorFunction(std::function<std::string(void)> getError)
{
    s_getExternalExceptionMessage = getError;
}


//==================================================================================================
// Return the message associated in the map
//==================================================================================================
std::string oogl::OOGLException::getMessageFromCode(oogl::ExceptionCode code) noexcept
{
    return oogl::OOGLException::s_mapExceptionCodeMessage.at(code);
}


//==================================================================================================
// Build the map associating the exception codes to exception messages
//==================================================================================================
std::map<oogl::ExceptionCode, std::string> oogl::OOGLException::s_mapExceptionCodeMessage =
{
    {
        oogl::ExceptionCode::NO_EXCEPTION,
        "No detailed exception message."
    }, {
        oogl::ExceptionCode::OOGL_HANDLER_ALREADY_CREATED,
        "A graphic library handler already exist ; you cannot create another one."
    }, {
        oogl::ExceptionCode::OOGL_HANDLER_NOT_CREATED,
        "A graphic library handler must have been created before being either accessed or deleted."
    }, {
        oogl::ExceptionCode::LIB_ALREADY_INIT,
        "A graphic library has already been initialized ; it cannot be initialized twice."
    }, {
        oogl::ExceptionCode::LIB_NOT_INIT,
        "Trying to exit an unitialized library."
    }, {
        oogl::ExceptionCode::OOGLHANDLER_NULL_OBJ_TRACK,
        std::string("A trackable object, i.e. an object the graphic library handler will track")
        + std::string("to be able to free all memory space, should not be given through the null")
        + std::string("pointer.")
    }, {
        oogl::ExceptionCode::WIN_ALREADY_CREATED,
        std::string("The call of the method \\create\\ is make several times for a unique window.")
        + std::string(" A Window instance can only call this method once without calling")
        + std::string(" \\destroy\\.")
    }, {
        oogl::ExceptionCode::WIN_NOT_CREATED,
        "The Window instance which calls \\destroy\\ has not called \\create\\ before."
    }
};
