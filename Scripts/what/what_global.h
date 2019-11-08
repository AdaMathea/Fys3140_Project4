#ifndef WHAT_GLOBAL_H
#define WHAT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(WHAT_LIBRARY)
#  define WHAT_EXPORT Q_DECL_EXPORT
#else
#  define WHAT_EXPORT Q_DECL_IMPORT
#endif

#endif // WHAT_GLOBAL_H
