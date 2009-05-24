##############################
#  SConscript for OgreOpcode #
##############################
#SCons scripts maintained by:
#  Van Aarde "nanocell" Krynauw.

#TODO:
# - Add commandline options to specify include dirs, defines, compiler defs, libraries, etc.
# - Add Sconscripts for the samples.
# - Add a binary SConstruct file.

#####################
#     Options       #
#####################

OPT_INCLUDES =	'''#include
									 /usr/local/include/OGRE
								'''

OPT_FLAGS = ' '
OPT_LIBNAME = 'OgreOpcode'
OPT_SUBDIRS = 'src'
OPT_CC = 'g++'
OPT_FLAGS = '-Wall -ansi'
OPT_LIBTARGET = '#/libs'

####################

import sys, os

################################
#    Some helper functions     #
################################
def BuildSharedLib(environment, name, objs):
	output = env['LIBTARGET'] + '/' + name
	environment.SharedLibrary(output, objs)

def CreateAppFromObjs(objs):
	output = '#' + OPT_APPNAME
	environment.Program( output, objs, duplicate=0)
#################################

platform_build = 'build' + os.path.sep + sys.platform

#Set up a building environment

env = Environment()

env.BuildSharedLib = BuildSharedLib
env.CreateAppFromObjs = CreateAppFromObjs

#Check if OgreOpcode objects should be built as static or shared
env.BuildObject = env.SharedObject

#Check if OgreOpcode is being compiled on linux. If so,
#then define LINUX_FLOAT

if sys.platform == "linux2":
	OPT_FLAGS = OPT_FLAGS + ' -DLINUX_FLOAT'

env.Replace(CC = OPT_CC)
env.Replace(CXXFLAGS = Split(OPT_FLAGS))

#Current path. Used for relative hierarchical building
env['CURRENT_PATH'] = '#'

#The build directory for the current 
#platform. TODO: Add command line
#support for cross compiling.
env['PLATFORM_BUILD'] = platform_build
#Target directory where the libaries
#will be built.
env['LIBTARGET'] = OPT_LIBTARGET

env.Append(CPPPATH = Split(OPT_INCLUDES))

#env.Append(LIBPATH = Split(LIBSDIR))

Export('env')

print "Building to: " + env['PLATFORM_BUILD']

#TODO: Check for dependencies...?

objs = []

#Map the 'build' subdirectory to be compile from 'src'

#Run all the SConscripts in sub directories.
for subdir in Split(OPT_SUBDIRS):
	#Map a given subdirectory into the build directory...Let's see how this goes.
	env.BuildDir( env['PLATFORM_BUILD'] + "/" + subdir, subdir, duplicate=0)
	o = env.SConscript( env['PLATFORM_BUILD'] + "/" + subdir + '/SConscript')
	#o = senv.SConscript( senv['PLATFORM_BUILD'] + '/' + subdir + '/SConscript')
	objs.append(o)

#All the objects that were returned should be compiled 
#into the final OgreOpcode library
#o = env.SConscript( env['PLATFORM_BUILD'] + os.path.sep + 'SConscript')

env.SharedLibrary(OPT_LIBTARGET + "/" + OPT_LIBNAME, o);
