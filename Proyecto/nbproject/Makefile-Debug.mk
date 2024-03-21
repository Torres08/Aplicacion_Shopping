#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/DateTime.o \
	${OBJECTDIR}/src/Event.o \
	${OBJECTDIR}/src/EventSet.o \
	${OBJECTDIR}/src/Index.o \
	${OBJECTDIR}/src/Matrix.o \
	${OBJECTDIR}/src/Pair.o \
	${OBJECTDIR}/src/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../DataTable/dist/Debug/GNU-Linux/libdatatable.a ../AnsiTerminal/dist/Debug/GNU-Linux/libansiterminal.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shopping3a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shopping3a: ../DataTable/dist/Debug/GNU-Linux/libdatatable.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shopping3a: ../AnsiTerminal/dist/Debug/GNU-Linux/libansiterminal.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shopping3a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shopping3a ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/DateTime.o: src/DateTime.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../MPTest/include -I../googletest-master/googletest/include -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/DateTime.o src/DateTime.cpp

${OBJECTDIR}/src/Event.o: src/Event.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../MPTest/include -I../googletest-master/googletest/include -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Event.o src/Event.cpp

${OBJECTDIR}/src/EventSet.o: src/EventSet.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../MPTest/include -I../googletest-master/googletest/include -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/EventSet.o src/EventSet.cpp

${OBJECTDIR}/src/Index.o: src/Index.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../MPTest/include -I../googletest-master/googletest/include -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Index.o src/Index.cpp

${OBJECTDIR}/src/Matrix.o: src/Matrix.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../MPTest/include -I../googletest-master/googletest/include -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Matrix.o src/Matrix.cpp

${OBJECTDIR}/src/Pair.o: src/Pair.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../MPTest/include -I../googletest-master/googletest/include -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Pair.o src/Pair.cpp

${OBJECTDIR}/src/main.o: src/main.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../MPTest/include -I../googletest-master/googletest/include -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:
	cd ../DataTable && ${MAKE}  -f Makefile CONF=Debug
	cd ../AnsiTerminal && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:
	cd ../DataTable && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../AnsiTerminal && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
