#pragma once

/*
   Some classes do not permit copies to be made of an object. These
   classes contains a private copy constructor and assignment
   operator to disable copying (the compiler gives an error message).

   These macros are copied and pasted from qglobal.h
*/

#define DISABLE_COPY(Class) \
	Class(const Class &) = delete;\
	Class &operator=(const Class &) = delete;

#define DISABLE_MOVE(Class) \
	Class(Class &&) = delete; \
	Class &operator=(Class &&) = delete;

#define DISABLE_COPY_MOVE(Class) \
	DISABLE_COPY(Class) \
	DISABLE_MOVE(Class)
