#!python
import os, subprocess

# Local dependency paths, adapt them to your setup
godot_headers_path = ARGUMENTS.get("headers", "godot_headers/")

# default to release build, add target=debug to build debug build
target = ARGUMENTS.get("target", "release")

# platform= makes it in line with Godots scons file
platform = ARGUMENTS.get("platform", "windows")

# start building our destination path
godot_build_path = 'demo/addons/arvrsimple/bin/'

# This makes sure to keep the session environment variables on windows, 
# that way you can run scons in a vs 2017 prompt and it will find all the required tools
env = Environment()
if platform == "windows":
    env = Environment(ENV = os.environ)

bits = '64'
if 'bits' in env:
    bits = env['bits']

if ARGUMENTS.get("use_llvm", "no") == "yes":
    env["CXX"] = "clang++"

def add_sources(sources, directory):
    for file in os.listdir(directory):
        if file.endswith('.c'):
            sources.append(directory + '/' + file)

if platform == "osx":
    godot_build_path = godot_build_path + 'osx/'
    env.Append(CCFLAGS = ['-g','-O3', '-arch', 'x86_64'])
    env.Append(LINKFLAGS = ['-arch', 'x86_64'])
elif platform == "linux":
    godot_build_path = godot_build_path + 'x11/'
    env.Append(CCFLAGS = ['-fPIC', '-g','-O3', '-std=c++14'])
elif platform == "windows":
    godot_build_path = godot_build_path + 'win' + str(bits) + '/'
    if target == "debug":
        env.Append(CCFLAGS = ['-EHsc', '-D_DEBUG', '/MDd'])
    else:
        env.Append(CCFLAGS = ['-O2', '-EHsc', '-DNDEBUG', '/MD'])

# , 'include', 'include/core'
env.Append(CPPPATH=['.', godot_headers_path])

sources = []
add_sources(sources, "src")

library = env.SharedLibrary(target=godot_build_path + 'arvrsimple', source=sources)
Default(library)
