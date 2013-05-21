@echo off

rem ###############################################################################
rem #                                                                             #
rem # VitoshaTrade is Distributed Artificial Neural Network trained by            #
rem # Differential Evolution for prediction of Forex. Project development is in   #
rem # Sofia, Bulgaria. Vitosha is a mountain massif, on the outskirts of Sofia,   #
rem # the capital of Bulgaria.                                                    #
rem #                                                                             #
rem # Copyright (C) 2008-2009 by Todor Balabanov  ( tdb@tbsoft.eu )               #
rem #                            Iliyan Zankinski ( iliyan_mf@abv.bg )            #
rem #                            Galq Cirkalova   ( galq_cirkalova@abv.bg )       #
rem #                            Ivan Grozev      ( ivan.iliev.grozev@gmail.com ) #
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
rem # Java style source code format.                                           #
rem ############################################################################
astyle *.cpp *.h *.php *.mq4 *.mqh *.js *.java --indent=force-tab --style=java / -A2 --recursive 

@echo on
