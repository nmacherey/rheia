/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
 * @file RheiaComponentCleaner.h
 * @brief Abstract class for cleaning a Rheia Component Library
 * @author Nicolas Macherey (nm@graymat.fr)
 * @version 10.6.1
 */
#ifndef RHEIACOMPONENT_CLEANER_H
#define RHEIACOMPONENT_CLEANER_H

#include <vector>

/** previous define */
class RheiaComponentCleaner;

/** define a map of components cleaner */ 
typedef std::vector< RheiaComponentCleaner* > RheiaComponentCleanerArray;

/** @class RheiaComponentCleaner
 * @brief Abtract class for cleaning a library component
 * 
 * You shall overload this class in order to clean your library components 
 * when the application will close. This is very important as it will be 
 * registered in the RheiaManager.
 * @author Nicolas Macherey (nm@graymat.fr)
 * @version 10.6.1
 */
class RheiaComponentCleaner {
	
public :
	
	/** Virtual method that you shall overload in order to clean your components 
	 * when the application stops
	 */
	virtual void DoCleanUp() = 0;
};

#endif

 