#ifndef CB_ITERATOR_STATIC_MULTI_H
#define CB_ITERATOR_STATIC_MULTI_H

#include <assert.h>
#include "CB_CriticalSection.h"

#ifdef _AFXEXT
#define CB_EXT_CLASS       AFX_CLASS_EXPORT
#else
#define CB_EXT_CLASS
#endif

#ifndef CB_PTR
#define CB_PTR(ClassName) ClassName*
#endif

#define ITERATOR_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    class CB_EXT_CLASS NameTo##Iterator\
    {\
    private:\
		static CriticalSection& CriticalSection##NameTo();\
		\
        ClassTo* _ref##NameTo;\
        ClassTo* _prev##NameTo;\
        ClassTo* _next##NameTo;\
        \
        NameTo##Iterator* _prev;\
        NameTo##Iterator* _next;\
        \
        int (ClassTo::*_method)() const;\
        \
        static NameTo##Iterator* _first;\
        static NameTo##Iterator* _last;\
        \
    public:\
        NameTo##Iterator(int (ClassTo::*method)() const = 0,\
                         ClassTo* ref##NameTo = (ClassTo*)0);\
        NameTo##Iterator(const NameTo##Iterator& iterator__,\
                         int (ClassTo::*method)() const = 0);\
        ~NameTo##Iterator();\
        \
        NameTo##Iterator& operator= (const NameTo##Iterator& iterator__)\
        {\
            _ref##NameTo = iterator__._ref##NameTo;\
            _prev##NameTo = iterator__._prev##NameTo;\
            _next##NameTo = iterator__._next##NameTo;\
            _method = iterator__._method;\
            return *this;\
        }\
        ClassTo* operator++ ()\
        {\
            _next##NameTo = GetNext##NameTo(_next##NameTo);\
            if (_method != 0)\
            {\
                while (_next##NameTo && !(_next##NameTo->*_method)())\
                    _next##NameTo = GetNext##NameTo(_next##NameTo);\
            }\
            _ref##NameTo = _prev##NameTo = _next##NameTo;\
            return _ref##NameTo;\
        }\
        ClassTo* operator-- ()\
        {\
            _prev##NameTo = GetPrev##NameTo(_prev##NameTo);\
            if (_method != 0)\
            {\
                while (_prev##NameTo && !(_prev##NameTo->*_method)())\
                    _prev##NameTo = GetPrev##NameTo(_prev##NameTo);\
            }\
            _ref##NameTo = _next##NameTo = _prev##NameTo;\
            return _ref##NameTo;\
        }\
        operator ClassTo*() { return _ref##NameTo; }\
        ClassTo* operator-> () { return _ref##NameTo; }\
        ClassTo* Get() { return _ref##NameTo; }\
        void Reset() { _ref##NameTo = _prev##NameTo = _next##NameTo = (ClassTo*)0; }\
        \
        int IsLast() { return (GetLast##NameTo() == _ref##NameTo); }\
        int IsFirst() { return (GetFirst##NameTo() == _ref##NameTo); }\
        \
        static void Check(ClassTo* item##NameTo);\
        static void Check(ClassTo* item##NameTo, ClassTo* newItem##NameTo);\
    }; 

#define METHODS_ITERATOR_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
ClassFrom::NameTo##Iterator* ClassFrom::NameTo##Iterator::_first = 0;\
ClassFrom::NameTo##Iterator* ClassFrom::NameTo##Iterator::_last = 0;\
\
CriticalSection& ClassFrom::NameTo##Iterator::CriticalSection##NameTo()\
{\
	static CriticalSection criticalSection##NameTo;\
	return criticalSection##NameTo;\
}\
\
ClassFrom::NameTo##Iterator::NameTo##Iterator(int (ClassTo::*method)() const, ClassTo* ref##NameTo)\
{\
    CriticalSectionLock lock(CriticalSection##NameTo());\
	\
    _ref##NameTo = _prev##NameTo = _next##NameTo = ref##NameTo;\
    _prev = (NameTo##Iterator*)0;\
    _next = (NameTo##Iterator*)0;\
    _method = method;\
    if (_last)\
    {\
        _last->_next = this;\
        _prev = _last;\
        _last = this;\
    }\
    else\
        _first = _last = this;\
}\
\
ClassFrom::NameTo##Iterator::NameTo##Iterator(const NameTo##Iterator& iterator__, int (ClassTo::*method)() const)\
{\
    CriticalSectionLock lock(CriticalSection##NameTo());\
	\
    _ref##NameTo = iterator__._ref##NameTo;\
    _prev##NameTo = iterator__._prev##NameTo;\
    _next##NameTo = iterator__._next##NameTo;\
    _prev = (NameTo##Iterator*)0;\
    _next = (NameTo##Iterator*)0;\
    _method = method;\
    if (_last)\
    {\
        _last->_next = this;\
        _prev = _last;\
        _last = this;\
    }\
    else\
        _first = _last = this;\
}\
\
ClassFrom::NameTo##Iterator::~NameTo##Iterator()\
{\
    CriticalSectionLock lock(CriticalSection##NameTo());\
	\
    if (_next)\
        _next->_prev = _prev;\
    else\
        _last = _prev;\
\
    if (_prev)\
        _prev->_next = _next;\
    else\
        _first = _next;\
}\
\
void ClassFrom::NameTo##Iterator::Check(ClassTo* item##NameTo)\
{\
    CriticalSectionLock lock(CriticalSection##NameTo());\
	\
    for (NameTo##Iterator* item = _first; item; item = item->_next)\
    {\
        if (item->_prev##NameTo == item##NameTo)\
        {\
            item->_prev##NameTo = GetNext##NameTo(item->_prev##NameTo);\
            item->_ref##NameTo = 0;\
        }\
        if (item->_next##NameTo == item##NameTo)\
        {\
            item->_next##NameTo = GetPrev##NameTo(item->_next##NameTo);\
            item->_ref##NameTo = 0;\
        }\
    }\
}\
\
void ClassFrom::NameTo##Iterator::Check(ClassTo* item##NameTo, ClassTo* newItem##NameTo)\
{\
    CriticalSectionLock lock(CriticalSection##NameTo());\
	\
    for (NameTo##Iterator* item = _first; item; item = item->_next)\
    {\
        if (item->_ref##NameTo == item##NameTo)\
        {\
            item->_ref##NameTo = item->_prev##NameTo = item->_next##NameTo = newItem##NameTo;\
        }\
        if (item->_prev##NameTo == item##NameTo)\
        {\
            item->_prev##NameTo = newItem##NameTo;\
            item->_ref##NameTo = 0;\
        }\
        if (item->_next##NameTo == item##NameTo)\
        {\
            item->_next##NameTo = newItem##NameTo;\
            item->_ref##NameTo = 0;\
        }\
    }\
}

#define ITERATOR_NOFILTER_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    class CB_EXT_CLASS NameTo##Iterator\
    {\
    private:\
		static CriticalSection& CriticalSection##NameTo();\
		\
        ClassTo* _ref##NameTo;\
        ClassTo* _prev##NameTo;\
        ClassTo* _next##NameTo;\
        \
        NameTo##Iterator* _prev;\
        NameTo##Iterator* _next;\
        \
        static NameTo##Iterator* _first;\
        static NameTo##Iterator* _last;\
        \
    public:\
        NameTo##Iterator(ClassTo* ref##NameTo = (ClassTo*)0);\
        NameTo##Iterator(const NameTo##Iterator& iterator__);\
        ~NameTo##Iterator();\
        \
        NameTo##Iterator& operator= (const NameTo##Iterator& iterator__)\
        {\
            _ref##NameTo = iterator__._ref##NameTo;\
            _prev##NameTo = iterator__._prev##NameTo;\
            _next##NameTo = iterator__._next##NameTo;\
            return *this;\
        }\
        ClassTo* operator++ ()\
        {\
            _next##NameTo = GetNext##NameTo(_next##NameTo);\
            _ref##NameTo = _prev##NameTo = _next##NameTo;\
            return _ref##NameTo;\
        }\
        ClassTo* operator-- ()\
        {\
            _prev##NameTo = GetPrev##NameTo(_prev##NameTo);\
            _ref##NameTo = _next##NameTo = _prev##NameTo;\
            return _ref##NameTo;\
        }\
        operator ClassTo*() { return _ref##NameTo; }\
        ClassTo* operator-> () { return _ref##NameTo; }\
        ClassTo* Get() { return _ref##NameTo; }\
        void Reset() { _ref##NameTo = _prev##NameTo = _next##NameTo = (ClassTo*)0; }\
        \
        int IsLast() { return (GetLast##NameTo() == _ref##NameTo); }\
        int IsFirst() { return (GetFirst##NameTo() == _ref##NameTo); }\
        \
        static void Check(ClassTo* item##NameTo);\
        static void Check(ClassTo* item##NameTo, ClassTo* newItem##NameTo);\
    }; 

#define METHODS_ITERATOR_NOFILTER_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
ClassFrom::NameTo##Iterator* ClassFrom::NameTo##Iterator::_first = 0;\
ClassFrom::NameTo##Iterator* ClassFrom::NameTo##Iterator::_last = 0;\
\
CriticalSection& ClassFrom::NameTo##Iterator::CriticalSection##NameTo()\
{\
	static CriticalSection criticalSection##NameTo;\
	return criticalSection##NameTo;\
}\
\
ClassFrom::NameTo##Iterator::NameTo##Iterator(ClassTo* ref##NameTo)\
{\
    CriticalSectionLock lock(CriticalSection##NameTo());\
	\
    _ref##NameTo = _prev##NameTo = _next##NameTo = ref##NameTo;\
    _prev = (NameTo##Iterator*)0;\
    _next = (NameTo##Iterator*)0;\
    if (_last)\
    {\
        _last->_next = this;\
        _prev = _last;\
        _last = this;\
    }\
    else\
        _first = _last = this;\
}\
\
ClassFrom::NameTo##Iterator::NameTo##Iterator(const NameTo##Iterator& iterator__)\
{\
    CriticalSectionLock lock(CriticalSection##NameTo());\
	\
    _ref##NameTo = iterator__._ref##NameTo;\
    _prev##NameTo = iterator__._prev##NameTo;\
    _next##NameTo = iterator__._next##NameTo;\
    _prev = (NameTo##Iterator*)0;\
    _next = (NameTo##Iterator*)0;\
    if (_last)\
    {\
        _last->_next = this;\
        _prev = _last;\
        _last = this;\
    }\
    else\
        _first = _last = this;\
}\
\
ClassFrom::NameTo##Iterator::~NameTo##Iterator()\
{\
    CriticalSectionLock lock(CriticalSection##NameTo());\
	\
    if (_next)\
        _next->_prev = _prev;\
    else\
        _last = _prev;\
    \
    if (_prev)\
        _prev->_next = _next;\
    else\
        _first = _next;\
}\
\
void ClassFrom::NameTo##Iterator::Check(ClassTo* item##NameTo)\
{\
    CriticalSectionLock lock(CriticalSection##NameTo());\
	\
    for (NameTo##Iterator* item = _first; item; item = item->_next)\
    {\
        if (item->_prev##NameTo == item##NameTo)\
        {\
            item->_prev##NameTo = GetNext##NameTo(item->_prev##NameTo);\
            item->_ref##NameTo = 0;\
        }\
        if (item->_next##NameTo == item##NameTo)\
        {\
            item->_next##NameTo = GetPrev##NameTo(item->_next##NameTo);\
            item->_ref##NameTo = 0;\
        }\
    }\
}\
\
void ClassFrom::NameTo##Iterator::Check(ClassTo* item##NameTo, ClassTo* newItem##NameTo)\
{\
    CriticalSectionLock lock(CriticalSection##NameTo());\
	\
    for (NameTo##Iterator* item = _first; item; item = item->_next)\
    {\
        if (item->_ref##NameTo == item##NameTo)\
        {\
            item->_ref##NameTo = item->_prev##NameTo = item->_next##NameTo = newItem##NameTo;\
        }\
        if (item->_prev##NameTo == item##NameTo)\
        {\
            item->_prev##NameTo = newItem##NameTo;\
            item->_ref##NameTo = 0;\
        }\
        if (item->_next##NameTo == item##NameTo)\
        {\
            item->_next##NameTo = newItem##NameTo;\
            item->_ref##NameTo = 0;\
        }\
    }\
}

#endif
