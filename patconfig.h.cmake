
#ifndef __PATCONFIG_HPP__
#define __PATCONFIG_HPP__

#if (defined WIN32 || defined _WIN32 || defined WINCE) && defined PATAPI_EXPORTS
    #define PAT_EXPORTS __declspec(dllexport)
#else
    #define PAT_EXPORTS
#endif

/* Version number of package */
#define PAT_VERSION "${pat_version}"

#endif

