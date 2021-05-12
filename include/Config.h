// the configured options and settings for Tutorial
#define Toolbox_VERSION_MAJOR 0
#define Toolbox_VERSION_MINOR 1

#if defined(_WIN32)
#  if defined(EXPORTING_MYMATH)
#    define DECLSPEC __declspec(dllexport)
#  else
#    define DECLSPEC __declspec(dllimport)
#  endif
#else // non windows
#  define DECLSPEC
#endif

#ifdef DISABLE_RELEASE_LOGS
	#ifndef NDEBUG
		#define DISABLE_LOGS	
	#endif
#endif
