# #
# SCons build description for the sdl2_tests project ------------------------------------------
#
# Only tested on GNU/Linux with clang and gcc

import os
import sys
import shutil
import re
import commands
from glob import glob
import subprocess
from os import access, F_OK

EnsureSConsVersion(2, 3, 0)

# Warn user of current set of build options.
AddOption('--option-cache',
          dest='option_cache',
          nargs=1, type='string',
          action='store',
          metavar='FILE',
          help='file with cached construction variables',
          default='.scons-option-cache')

if os.path.exists(GetOption("option_cache")):
    optfile = file(GetOption("option_cache"))
    print("Saved options:", optfile.read().replace("\n", ", ")[:-2])
    optfile.close()

# Build-control options -----------------------------------------------------------------------

opts = Variables(GetOption("option_cache"))

def OptionalPath(key, val, env):
    if val:
        PathVariable.PathIsDir(key, val, env)

opts.AddVariables(
    # Basic Build Options ---------------------------------------------------------------------
    ListVariable('default_targets',
                 'Targets that will be built if no target is specified in command line.',
                 "libsilly,client,daemon",
                 Split("libsilly client daemon")),
    EnumVariable('build',
                 'Build variant: debug, release profile or base (no subdirectory)',
                 "debug",
                 ["release", "debug", ]),
    ('jobs',
                'Set the number of parallel compilations',
                1),
    BoolVariable('distcc',
                 'Use distcc',
                 False),
    BoolVariable('ccache',
                 "Use ccache",
                 False),

    # Advanced Build Options ------------------------------------------------------------------
    EnumVariable('cxxtool',
                 'Set c++ compiler.',
                 'clang++',
                 ['clang++', 'g++']),
    EnumVariable('cxxstd',
                 'The C++ standard to use. i.e. -std=c++11, etc.',
                 'c++11',
                 ['c++11', 'gnu++11', 'c++1y', 'gnu++1y']),
    EnumVariable('cstd',
                 'The C standard to use. i.e. -std=c11, etc.',
                 'c11',
                 ['c11', 'gnu11']),
    BoolVariable("lockfile",
                 "Use lockfile to prevent multiple instances of scons running at the same time.",
                 True),
    BoolVariable('strict',
                 'Compile with -Werror',
                 False),

    # Compiler/Linker Flags -------------------------------------------------------------------
    ('extra_flags_config',
     'Extra compiler and linker flags to use for configuration and all builds',
     "-march=core-avx-i -lprofiler -ltcmalloc"),
    ('extra_flags_release',
     'Extra compiler and linker flags to use for release builds',
     "-O4 -fslp-vectorize -fslp-vectorize-aggressive"),
    ('extra_flags_debug',
     'Extra compiler and linker flags to use for debug builds',
     "-O0 -g"),
    # Names -----------------------------------------------------------------------------------
    ('server_gid',
     'group id of the user who runs daemon',
     ""),
    ('server_uid',
     'user id of the user who runs daemon',
     ""),

    # Paths and Directory Locations -----------------------------------------------------------
    PathVariable('build_dir',
                 'Build all intermediate files(objects, test programs, etc) under this dir',
                 "build",
                 PathVariable.PathAccept),
)

# Setup ---------------------------------------------------------------------------------------
env = Environment(options=opts)

# Define build directory ----------------------------------------------------------------------
builds = {
    "debug"         : dict(CCFLAGS="$DEBUG_FLAGS"),
    "release"       : dict(CCFLAGS="$OPT_FLAGS"),
}
build = env["build"]
build_dir = os.path.join("$build_dir", build)
VariantDir("$build_dir", "src", duplicate=0)

if env["lockfile"]:
    print "Creating lockfile"
    lockfile = os.path.join(env['build_dir'], 'scons.lock')
    open(lockfile, "wx").write(str(os.getpid()))
    import atexit
    atexit.register(os.remove, lockfile)

opts.Save(GetOption("option_cache"), env)
env.SConsignFile("$build_dir/sconsign.dblite")

# Make sure the user's environment is always available
env['ENV']['PATH'] = os.environ["PATH"]
env['ENV']['TERM'] = os.environ["TERM"]

# @todo: Add support for icc, and anything else interesting
if env['cxxtool'] in ("clang++", "clang", "llvm"):
    env['CC'] = 'clang'
    env['CXX'] = "clang++"
    env.Append(LINKFLAGS="-Wl,-plugin,/usr/lib/LLVMgold.so")
elif env['cxxtool'] in (None, "", "g++"):
    env['CC'] = "gcc"
    env['CXX'] = "g++"

if 'HOME' in os.environ:
    env['ENV']['HOME'] = os.environ['HOME']

if env['jobs'] > 1:
    SetOption("num_jobs", env['jobs'])

if env['distcc'] and env['ccache']:
    env['CC'] = 'ccache ' + env['CC']
    env['CXX'] = 'ccache ' + env['CXX']
    env['CCACHE_PREFIX'] = 'distcc'
elif env['distcc']:
    env['CC'] = 'distcc ' + env['CC']
    env['CXX'] = 'distcc ' + env['CXX']
elif env['ccache']:
    env['CC'] = 'ccache ' + env['CC']
    env['CXX'] = 'ccache ' + env['CXX']


Help("""Arguments may be a mixture of switches and targets in any order.
Switches apply to the entire build regardless of where they are in the order.
Important switches include:

    prefix=/usr     probably what you want for installation
    build=release   optimized build
    build=debug     debugging build

With no arguments, the recipe builds client and daemon. Available
build targets include:

    client
    daemon
    all
    install
    uninstall
    docs = generate automated documentation

Options are cached in a file named .scons-option-cache and persist to later
invocations.  The file is editable.  Delete it to start fresh. You can also 
use a different file by specifying --option-cache=FILE command line argument. 
Current option values can be listed with 'scons -h'.

If you set CXXFLAGS and/or LDFLAGS in the environment, the values will
be appended to the appropriate variables within scons.
""" + opts.GenerateHelpText(env, sort=cmp))

if GetOption("help"):
    Return()

env.MergeFlags(env["extra_flags_config"])

env['CPPPATH'] = ['./src/', '/usr/include/SDL2', '/usr/include', ]
env['LIBPATH'] = ['/usr/lib', '/usr/lib64', '/usr/local/lib', ]
env.ParseConfig('pkg-config --cflags --libs sdl2')
env.ParseConfig('pkg-config --cflags --libs SDL2_image')
env.AppendUnique(LIBS="pthread")
env.AppendUnique(LIBS="SDL2")
env.AppendUnique(LIBS="SDL2_image")
env.AppendUnique(LIBS="zmq")
env.AppendUnique(LIBS="msgpack")

# Implement configuration switches

# env.Prepend(CPPPATH=["#/", "#/src"])
env.AppendUnique(CCFLAGS=Split("-W -Wall"))
env.AppendUnique(CFLAGS='-std=' + env["cstd"])
env.AppendUnique(CXXFLAGS='-std=' + env['cxxstd'])
if env['strict']:
    env.AppendUnique(CCFLAGS=Split("-Werror $(-Wno-unused-local-typedefs$)"))

# Export(["env", ])

libsilly_sources = ['src/libsilly/defs.cpp', ]
libsilly = env.Library("libsilly", libsilly_sources)

client_sources = ['src/client/client.cpp',
                  'src/client/blitmgr.cpp']
client = env.Program("client", [client_sources, libsilly])

daemon_sources = ['src/daemon/daemon.cpp',
                  'src/daemon/winmgr.cpp']
daemon = env.Program("daemon", [daemon_sources, libsilly])

binaries = [libsilly, client, daemon]
env.AppendUnique(**builds[build])
env.MergeFlags(env["extra_flags_" + build])

# Define object file names --------------------------------------------------------------------
if build == "release" :
    build_suffix = ""
else                  :
    build_suffix = "-" + build

env.Append(CPPDEFINES="$EXTRA_DEFINE")

print("--------------------------------------------------------------------------------------")
print("Current FLAGS")
print("--------------------------------------------------------------------------------------")
print("\tCXXFLAGS   = %s" % env['CXXFLAGS'])
print("\tCPPPATH    = %s" % env['CPPPATH'])
print("\tLINKFLAGS  = %s" % env['LINKFLAGS'])
print("\tLIBS       = %s" % env['LIBS'])
print("--------------------------------------------------------------------------------------")


all = env.Alias("all", map(Alias, binaries))

env.Default(all)

##---------------------------------------------------------------------------------------------
# @brief Get the git sha revision hash.
def get_git_version():
    gpr = subprocess.Popen(['git', 'rev-parse', 'HEAD'], stdout=subprocess.PIPE)
    gpr.wait()
    ver = gpr.stdout.readlines()
    return ver[0].strip()
