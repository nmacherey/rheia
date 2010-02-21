/**
*	@file RheiaEnvironmentPlugin.cpp
*
*   Revision : 20-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	15-Nov-2008
*	@version 0.0.1
*/
#include <RheiaEnvironmentPlugin.h>

#include <RheiaManager.h>

#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

/* Default constructor */
RheiaEnvironmentPlugin::RheiaEnvironmentPlugin()
{
    Type = ptEnvironment;
}
