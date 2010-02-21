/**
*   @file RheiaLoggersDoc.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 26-November-2009
*/

/**
*   @page rheia_loggers Rheia Loggers Documentation
*   @defgroup rheia_loggers Rheia Loggers
*
*   Rheia provides you with different and very usefull loggers. The different logging classes are :
*
*   <ul>
*       <li>
*           RheiaStdLogger : which allow you to log directly in one of the standard stream either
*               std::cout or std::cerr for example. This will depend on the Rheiaogging::RheiaLogLevel
*               you've choosen when you call it's RheiaLogger::Log method
*       </li>
*       <li>
*           RheiaFileLogger : which allow you to log in a file. The file has to be set by the user.
*       </li>
*       <li>
*           RheiaListLogger : which allow you to log in a wxListCtrl which commonly is very inetresting
*               for displaying properly the level and the message and the provenance.
*       </li>
*       <li>
*           RheiaTextLogger : which allow you to log in a wxTextCtrl which is the most simple you can
*               do for displaying log messages.
*       </li>
*       <li>
*           RheiaHtmlLogger : which allow you to log in a wxHTMLWindow and to display different kind of
*               information using some very simple HTML formating tags.
*       </li>
*       <li>
*           RheiaTimeStampableTextLogger : same as RheiaTextLogger but with date and time informations
*       </li>
*       <li>
*           RheiaTimeStampableFileLogger : Same as RheiaFileLogger but with the date and time information
*       </li>
*       <li>
*           RheiaTimeStampableListLogger : Same as RheiaListLogger but with the date and time information
*       </li>
*       <li>
*           RheiaTimeStampableHtmlLogger : Same as RheiaHtmlLogger but with the date and time information
*       </li>
*       <li>
*           RheiaTimeStampableStdLogger : Same as RheiaStdLogger but with the date and time information
*       </li>
*   </ul>
*
*   Rheia implements different basic kind of loggers in order to allow you to log without bothering about these
*   models. However, you can choose either to develop your own RheiaLogger by defining a new class Inherited from
*   the RheiaLogger abstract class,  or to register an existing logger in Rheia's RheiaLoggerManager in order
*   to log your specific information into it.
*/
