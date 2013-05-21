/*******************************************************************************
 *                                                                             *
 * VitoshaTrade is Distributed Artificial Neural Network trained by            *
 * Differential Evolution for prediction of Forex. Project development is in   *
 * Sofia, Bulgaria. Vitosha is a mountain massif, on the outskirts of Sofia,   *
 * the capital of Bulgaria.                                                    *
 *                                                                             *
 * Copyright (C) 2008-2011 by Todor Balabanov  ( tdb@tbsoft.eu )               *
 *                       Iliyan Zankinski   ( iliyan_mf@abv.bg )               *
 *                       Momchil Anachkov   ( mZer0000@gmail.com )             *
 *                       Daniel Chutrov     ( d.chutrov@gmail.com )            *
 *                       Nikola Simeonov    ( n.simeonow@gmail.com )           *
 *                       Galq Cirkalova     ( galq_cirkalova@abv.bg )          *
 *                       Ivan Grozev        ( ivan.iliev.grozev@gmail.com )    *
 *                       Elisaveta Hristova ( elisaveta.s.hristova@gmail.com ) *
 *                                                                             *
 * This program is free software: you can redistribute it and/or modify        *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.        *
 *                                                                             *
 ******************************************************************************/

#ifndef VITOSHA_TRADE_H
#define VITOSHA_TRADE_H

#include "../../client/source/RateInfo.h"

/**
 * DLL functions prototype style.
 */
#define MT4_EXPFUNC /*extern "C"*/ __declspec(dllexport)

/**
 * Show about message dialog.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 07 Apr 2009
 */
MT4_EXPFUNC void __stdcall about();

/**
 * Start predictor instance and calculation loop of it.
 *
 * @param dbId Database identifier of specific record.
 *
 * @param symbol Forex symbol for trading.
 *
 * @param period Chart period value.
 *
 * @param neuronsAmount Neurons amout to be used if predictor will not be loaded from database.
 *
 * @param populationSize Population size to be used if predictor will not be loaded from database.
 *
 * @param bars Prediction bars interval.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 07 Apr 2009
 */
MT4_EXPFUNC void __stdcall startPredictor(const int dbId, const char *symbol, const int period, const int neuronsAmount, const int populationSize, const int bars);

/**
 * Stop predictor and its loop.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 07 Apr 2009
 */
MT4_EXPFUNC void __stdcall stopPredictor();

/**
 * Load chart historical data.
 *
 * @param rates Chart time series.
 *
 * @param size Size of the time series.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 11 Aug 2009
 */
MT4_EXPFUNC void __stdcall loadChartData(const RateInfo *rates, int size);

/**
 * Load historical data into predictig module.
 *
 * @return Prediction price value.
 *
 * @author Iliyan Zankinski
 *
 * @email iliyan_mf@abv.bg
 *
 * @date 26 Jul 2009
 */
MT4_EXPFUNC double __stdcall prediction();

#endif
