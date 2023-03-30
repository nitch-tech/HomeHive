# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/HomeHive

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/HomeHive

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components
.PHONY : list_install_components/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /root/HomeHive/CMakeFiles /root/HomeHive//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /root/HomeHive/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named HomeHiveRequests

# Build rule for target.
HomeHiveRequests: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 HomeHiveRequests
.PHONY : HomeHiveRequests

# fast build rule for target.
HomeHiveRequests/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveRequests.dir/build.make CMakeFiles/HomeHiveRequests.dir/build
.PHONY : HomeHiveRequests/fast

#=============================================================================
# Target rules for targets named HomeHiveEvent

# Build rule for target.
HomeHiveEvent: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 HomeHiveEvent
.PHONY : HomeHiveEvent

# fast build rule for target.
HomeHiveEvent/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveEvent.dir/build.make CMakeFiles/HomeHiveEvent.dir/build
.PHONY : HomeHiveEvent/fast

#=============================================================================
# Target rules for targets named HomeHiveGUI

# Build rule for target.
HomeHiveGUI: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 HomeHiveGUI
.PHONY : HomeHiveGUI

# fast build rule for target.
HomeHiveGUI/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveGUI.dir/build.make CMakeFiles/HomeHiveGUI.dir/build
.PHONY : HomeHiveGUI/fast

#=============================================================================
# Target rules for targets named HomeHive

# Build rule for target.
HomeHive: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 HomeHive
.PHONY : HomeHive

# fast build rule for target.
HomeHive/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHive.dir/build.make CMakeFiles/HomeHive.dir/build
.PHONY : HomeHive/fast

#=============================================================================
# Target rules for targets named test

# Build rule for target.
test: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test
.PHONY : test

# fast build rule for target.
test/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/build
.PHONY : test/fast

#=============================================================================
# Target rules for targets named resources

# Build rule for target.
resources: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 resources
.PHONY : resources

# fast build rule for target.
resources/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resources.dir/build.make CMakeFiles/resources.dir/build
.PHONY : resources/fast

event/SettingsEvent.o: event/SettingsEvent.cpp.o
.PHONY : event/SettingsEvent.o

# target to build an object file
event/SettingsEvent.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveEvent.dir/build.make CMakeFiles/HomeHiveEvent.dir/event/SettingsEvent.cpp.o
.PHONY : event/SettingsEvent.cpp.o

event/SettingsEvent.i: event/SettingsEvent.cpp.i
.PHONY : event/SettingsEvent.i

# target to preprocess a source file
event/SettingsEvent.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveEvent.dir/build.make CMakeFiles/HomeHiveEvent.dir/event/SettingsEvent.cpp.i
.PHONY : event/SettingsEvent.cpp.i

event/SettingsEvent.s: event/SettingsEvent.cpp.s
.PHONY : event/SettingsEvent.s

# target to generate assembly for a file
event/SettingsEvent.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveEvent.dir/build.make CMakeFiles/HomeHiveEvent.dir/event/SettingsEvent.cpp.s
.PHONY : event/SettingsEvent.cpp.s

event/Timer.o: event/Timer.cpp.o
.PHONY : event/Timer.o

# target to build an object file
event/Timer.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveEvent.dir/build.make CMakeFiles/HomeHiveEvent.dir/event/Timer.cpp.o
.PHONY : event/Timer.cpp.o

event/Timer.i: event/Timer.cpp.i
.PHONY : event/Timer.i

# target to preprocess a source file
event/Timer.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveEvent.dir/build.make CMakeFiles/HomeHiveEvent.dir/event/Timer.cpp.i
.PHONY : event/Timer.cpp.i

event/Timer.s: event/Timer.cpp.s
.PHONY : event/Timer.s

# target to generate assembly for a file
event/Timer.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveEvent.dir/build.make CMakeFiles/HomeHiveEvent.dir/event/Timer.cpp.s
.PHONY : event/Timer.cpp.s

gui/App.o: gui/App.cpp.o
.PHONY : gui/App.o

# target to build an object file
gui/App.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveGUI.dir/build.make CMakeFiles/HomeHiveGUI.dir/gui/App.cpp.o
.PHONY : gui/App.cpp.o

gui/App.i: gui/App.cpp.i
.PHONY : gui/App.i

# target to preprocess a source file
gui/App.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveGUI.dir/build.make CMakeFiles/HomeHiveGUI.dir/gui/App.cpp.i
.PHONY : gui/App.cpp.i

gui/App.s: gui/App.cpp.s
.PHONY : gui/App.s

# target to generate assembly for a file
gui/App.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveGUI.dir/build.make CMakeFiles/HomeHiveGUI.dir/gui/App.cpp.s
.PHONY : gui/App.cpp.s

gui/BaseView.o: gui/BaseView.cpp.o
.PHONY : gui/BaseView.o

# target to build an object file
gui/BaseView.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveGUI.dir/build.make CMakeFiles/HomeHiveGUI.dir/gui/BaseView.cpp.o
.PHONY : gui/BaseView.cpp.o

gui/BaseView.i: gui/BaseView.cpp.i
.PHONY : gui/BaseView.i

# target to preprocess a source file
gui/BaseView.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveGUI.dir/build.make CMakeFiles/HomeHiveGUI.dir/gui/BaseView.cpp.i
.PHONY : gui/BaseView.cpp.i

gui/BaseView.s: gui/BaseView.cpp.s
.PHONY : gui/BaseView.s

# target to generate assembly for a file
gui/BaseView.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveGUI.dir/build.make CMakeFiles/HomeHiveGUI.dir/gui/BaseView.cpp.s
.PHONY : gui/BaseView.cpp.s

gui/HomeView.o: gui/HomeView.cpp.o
.PHONY : gui/HomeView.o

# target to build an object file
gui/HomeView.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveGUI.dir/build.make CMakeFiles/HomeHiveGUI.dir/gui/HomeView.cpp.o
.PHONY : gui/HomeView.cpp.o

gui/HomeView.i: gui/HomeView.cpp.i
.PHONY : gui/HomeView.i

# target to preprocess a source file
gui/HomeView.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveGUI.dir/build.make CMakeFiles/HomeHiveGUI.dir/gui/HomeView.cpp.i
.PHONY : gui/HomeView.cpp.i

gui/HomeView.s: gui/HomeView.cpp.s
.PHONY : gui/HomeView.s

# target to generate assembly for a file
gui/HomeView.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveGUI.dir/build.make CMakeFiles/HomeHiveGUI.dir/gui/HomeView.cpp.s
.PHONY : gui/HomeView.cpp.s

gui/settings.o: gui/settings.cpp.o
.PHONY : gui/settings.o

# target to build an object file
gui/settings.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveGUI.dir/build.make CMakeFiles/HomeHiveGUI.dir/gui/settings.cpp.o
.PHONY : gui/settings.cpp.o

gui/settings.i: gui/settings.cpp.i
.PHONY : gui/settings.i

# target to preprocess a source file
gui/settings.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveGUI.dir/build.make CMakeFiles/HomeHiveGUI.dir/gui/settings.cpp.i
.PHONY : gui/settings.cpp.i

gui/settings.s: gui/settings.cpp.s
.PHONY : gui/settings.s

# target to generate assembly for a file
gui/settings.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveGUI.dir/build.make CMakeFiles/HomeHiveGUI.dir/gui/settings.cpp.s
.PHONY : gui/settings.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHive.dir/build.make CMakeFiles/HomeHive.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHive.dir/build.make CMakeFiles/HomeHive.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHive.dir/build.make CMakeFiles/HomeHive.dir/main.cpp.s
.PHONY : main.cpp.s

request/Unsplash.o: request/Unsplash.cpp.o
.PHONY : request/Unsplash.o

# target to build an object file
request/Unsplash.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveRequests.dir/build.make CMakeFiles/HomeHiveRequests.dir/request/Unsplash.cpp.o
.PHONY : request/Unsplash.cpp.o

request/Unsplash.i: request/Unsplash.cpp.i
.PHONY : request/Unsplash.i

# target to preprocess a source file
request/Unsplash.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveRequests.dir/build.make CMakeFiles/HomeHiveRequests.dir/request/Unsplash.cpp.i
.PHONY : request/Unsplash.cpp.i

request/Unsplash.s: request/Unsplash.cpp.s
.PHONY : request/Unsplash.s

# target to generate assembly for a file
request/Unsplash.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveRequests.dir/build.make CMakeFiles/HomeHiveRequests.dir/request/Unsplash.cpp.s
.PHONY : request/Unsplash.cpp.s

request/UnsplashBackground.o: request/UnsplashBackground.cpp.o
.PHONY : request/UnsplashBackground.o

# target to build an object file
request/UnsplashBackground.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveRequests.dir/build.make CMakeFiles/HomeHiveRequests.dir/request/UnsplashBackground.cpp.o
.PHONY : request/UnsplashBackground.cpp.o

request/UnsplashBackground.i: request/UnsplashBackground.cpp.i
.PHONY : request/UnsplashBackground.i

# target to preprocess a source file
request/UnsplashBackground.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveRequests.dir/build.make CMakeFiles/HomeHiveRequests.dir/request/UnsplashBackground.cpp.i
.PHONY : request/UnsplashBackground.cpp.i

request/UnsplashBackground.s: request/UnsplashBackground.cpp.s
.PHONY : request/UnsplashBackground.s

# target to generate assembly for a file
request/UnsplashBackground.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveRequests.dir/build.make CMakeFiles/HomeHiveRequests.dir/request/UnsplashBackground.cpp.s
.PHONY : request/UnsplashBackground.cpp.s

request/request.o: request/request.cpp.o
.PHONY : request/request.o

# target to build an object file
request/request.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveRequests.dir/build.make CMakeFiles/HomeHiveRequests.dir/request/request.cpp.o
.PHONY : request/request.cpp.o

request/request.i: request/request.cpp.i
.PHONY : request/request.i

# target to preprocess a source file
request/request.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveRequests.dir/build.make CMakeFiles/HomeHiveRequests.dir/request/request.cpp.i
.PHONY : request/request.cpp.i

request/request.s: request/request.cpp.s
.PHONY : request/request.s

# target to generate assembly for a file
request/request.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveRequests.dir/build.make CMakeFiles/HomeHiveRequests.dir/request/request.cpp.s
.PHONY : request/request.cpp.s

request/weather.o: request/weather.cpp.o
.PHONY : request/weather.o

# target to build an object file
request/weather.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveRequests.dir/build.make CMakeFiles/HomeHiveRequests.dir/request/weather.cpp.o
.PHONY : request/weather.cpp.o

request/weather.i: request/weather.cpp.i
.PHONY : request/weather.i

# target to preprocess a source file
request/weather.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveRequests.dir/build.make CMakeFiles/HomeHiveRequests.dir/request/weather.cpp.i
.PHONY : request/weather.cpp.i

request/weather.s: request/weather.cpp.s
.PHONY : request/weather.s

# target to generate assembly for a file
request/weather.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/HomeHiveRequests.dir/build.make CMakeFiles/HomeHiveRequests.dir/request/weather.cpp.s
.PHONY : request/weather.cpp.s

test.o: test.cpp.o
.PHONY : test.o

# target to build an object file
test.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/test.cpp.o
.PHONY : test.cpp.o

test.i: test.cpp.i
.PHONY : test.i

# target to preprocess a source file
test.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/test.cpp.i
.PHONY : test.cpp.i

test.s: test.cpp.s
.PHONY : test.s

# target to generate assembly for a file
test.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/test.cpp.s
.PHONY : test.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... resources"
	@echo "... HomeHive"
	@echo "... HomeHiveEvent"
	@echo "... HomeHiveGUI"
	@echo "... HomeHiveRequests"
	@echo "... test"
	@echo "... event/SettingsEvent.o"
	@echo "... event/SettingsEvent.i"
	@echo "... event/SettingsEvent.s"
	@echo "... event/Timer.o"
	@echo "... event/Timer.i"
	@echo "... event/Timer.s"
	@echo "... gui/App.o"
	@echo "... gui/App.i"
	@echo "... gui/App.s"
	@echo "... gui/BaseView.o"
	@echo "... gui/BaseView.i"
	@echo "... gui/BaseView.s"
	@echo "... gui/HomeView.o"
	@echo "... gui/HomeView.i"
	@echo "... gui/HomeView.s"
	@echo "... gui/settings.o"
	@echo "... gui/settings.i"
	@echo "... gui/settings.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... request/Unsplash.o"
	@echo "... request/Unsplash.i"
	@echo "... request/Unsplash.s"
	@echo "... request/UnsplashBackground.o"
	@echo "... request/UnsplashBackground.i"
	@echo "... request/UnsplashBackground.s"
	@echo "... request/request.o"
	@echo "... request/request.i"
	@echo "... request/request.s"
	@echo "... request/weather.o"
	@echo "... request/weather.i"
	@echo "... request/weather.s"
	@echo "... test.o"
	@echo "... test.i"
	@echo "... test.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

