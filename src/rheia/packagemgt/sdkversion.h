#ifndef SDKVERSION_H
#define SDKVERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "20";
	static const char MONTH[] = "02";
	static const char YEAR[] = "2010";
	static const double UBUNTU_VERSION_STYLE = 10.02;
	
	//Software Status
	static const char STATUS[] = "Beta";
	static const char STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 15;
	static const long BUILD = 1131;
	static const long REVISION = 7092;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 1471;
	#define RC_FILEVERSION 1,15,1131,7092
	#define RC_FILEVERSION_STRING "1, 15, 1131, 7092\0"
	static const char FULLVERSION_STRING[] = "1.15.1131.7092";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 75;
	

}
#endif //SDKVERSION_H
