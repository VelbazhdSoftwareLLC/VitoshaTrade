@echo off

rem ###############################################################################
rem #                                                                             #
rem # VitoshaTrade is Distributed Artificial Neural Network trained by            #
rem # Differential Evolution for prediction of Forex. Project development is in   #
rem # Sofia, Bulgaria. Vitosha is a mountain massif, on the outskirts of Sofia,   #
rem # the capital of Bulgaria.                                                    #
rem #                                                                             #
rem # Copyright (C) 2008-2010 by Todor Balabanov  ( tdb@tbsoft.eu )               #
rem #                            Iliyan Zankinski ( iliyan_mf@abv.bg )            #
rem #                            Galq Cirkalova   ( galq_cirkalova@abv.bg )       #
rem #                            Ivan Grozev      ( ivan.iliev.grozev@gmail.com ) #
rem #                            Momchil Anachkov ( mZer0000@gmail.com )          #
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
rem # Check input parameters.                                                  #
rem ############################################################################
if "%~1"=="" goto end

rem ############################################################################
rem # Create web back-end directory.                                           #
rem ############################################################################
md "%~dp1backend\"

rem ############################################################################
rem # Compilation.                                                             #
rem ############################################################################
javac.exe -d ./binaries ./source/*.java -classpath ./binaries

rem ############################################################################
rem # Archiving.                                                               #
rem ############################################################################
cd binaries
jar.exe cf VitoshaTrade.jar *.class
cd ..

rem ############################################################################
rem # Deployment.                                                              #
rem ############################################################################
rem copy .\binaries\*.class "%~dp1backend\"
copy .\binaries\*.jar "%~dp1backend\"
copy .\source\*.html "%~dp1backend\"

rem ############################################################################
rem # End of the srcipt if there are no input parameters.                      #
rem ############################################################################
:end

rem ############################################################################
rem # Stop screen.                                                             #
rem ############################################################################
pause

@echo on
