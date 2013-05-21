@echo off

rem ###############################################################################
rem #                                                                             #
rem # VitoshaTrade is Distributed Artificial Neural Network trained by            #
rem # Differential Evolution for prediction of Forex. Project development is in   #
rem # Sofia, Bulgaria. Vitosha is a mountain massif, on the outskirts of Sofia,   #
rem # the capital of Bulgaria.                                                    #
rem #                                                                             #
rem # Copyright (C) 2008-2011 by Todor Balabanov  ( tdb@tbsoft.eu )               #
rem #                            Iliyan Zankinski ( iliyan_mf@abv.bg )            #
rem #                            Galq Cirkalova   ( galq_cirkalova@abv.bg )       #
rem #                            Ivan Grozev      ( ivan.iliev.grozev@gmail.com ) #
rem #                            Ivan Grozev      ( ivan.iliev.grozev@gmail.com ) #
rem #                            Nikola Simeonov  ( n.simeonow@gmail.com )        #
rem #                                                                             #
rem # This program is free software: you can redistribute it and/or modify        #
rem # it under the terms of the GNU General Public License as published by        #
rem # the Free Software Foundation, either version 3 of the License, or           #
rem # (at your option) any later version.                                         #
rem #                                                                             #
rem # This program is distributed in the hope that it will be useful,             #
rem # but WITHOUT ANY WARRANTY; without even the implied warranty of              #
rem # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               #
rem # GNU General Public License for more details.                                #
rem #                                                                             #
rem # You should have received a copy of the GNU General Public License           #
rem # along with this program. If not, see <http://www.gnu.org/licenses/>.        #
rem #                                                                             #
rem ###############################################################################

rem ############################################################################
rem # Change working directory to binaries.                                    #
rem ############################################################################
cd binaries

rem ############################################################################
rem # Clean to binaries directory.                                             #
rem ############################################################################
del *.o
del VitoshaTrade.scr

rem ############################################################################
rem # Compiling.                                                               #
rem ############################################################################
g++ -c ../../../client/source/ann/*.cpp
g++ -c ../../../client/source/de/*.cpp
g++ -c ../../../client/source/trainer/*.cpp
g++ -c ../../../client/source/common/*.cpp
g++ -c ../../../client/source/net/*.cpp
g++ -c ../source/*.cpp

rem ############################################################################
rem # Linking.                                                                 #
rem ############################################################################
g++ *.o -o VitoshaTrade.scr ../../../mql4/libraries/libws2_32.a ../../../mql4/libraries/libpdh.a ../libraries/libscrnsave.a -lstdc++ -lglut32 -lglu32 -lopengl32 -lwinmm -lgdi32 -IScrnSave -IGdi32 -lwinmm -lgdi32

rem ############################################################################
rem # Stop screen.                                                             #
rem ############################################################################
pause

rem ############################################################################
rem # Clean to binaries directory.                                             #
rem ############################################################################
del *.o

@echo on
