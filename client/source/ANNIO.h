/*******************************************************************************
 *                                                                             *
 * VitoshaTrade is Distributed Artificial Neural Network trained by            *
 * Differential Evolution for prediction of Forex. Project development is in   *
 * Sofia, Bulgaria. Vitosha is a mountain massif, on the outskirts of Sofia,   *
 * the capital of Bulgaria.                                                    *
 *                                                                             *
 * Copyright (C) 2008-2011 by Todor Balabanov  ( todor.balabanov@gmail.com )   *
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

#ifndef ANN_IO_H
#define ANN_IO_H

#include <vector>
#include <iostream>

/**
 * ANN input/ouput base class.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 11 Aug 2011
 */
class ANNIO {

private:

	/**
	 * Input/output values.
	 */
	std::vector<double> values;

public:

	/**
	 * Constructor without parameters.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 11 Aug 2011
	 */
	ANNIO();

	/**
	 * Class constructor. Memory allocation and internal variables initializaton.
	 *
	 * @param size Size of the input.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 11 Aug 2011
	 */
	ANNIO(int size);

	/**
	 * Copy constructor.
	 *
	 * @param io Instance to be copied.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 11 Aug 2011
	 */
	ANNIO(const ANNIO &io);


	/**
	 * Size of ANN input.
	 *
	 * @return Size of ANN input/ouput.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 11 Aug 2011
	 */
	int dimension() const;


	/**
	 * Class destructor. Memory release and variables deinitialization.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 11 Aug 2011
	 */
	virtual ~ANNIO();

	/**
	 * List elements access operator overloading.
	 *
	 * @param index Index of element.
	 *
	 * @return Constant element value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 11 Aug 2011
	 */
	double operator[](int index) const;

	/**
	 * List elements access operator overloading.
	 *
	 * @param index Index of element.
	 *
	 * @return Element reference value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 11 Aug 2011
	 */
	double& operator[](int index);

	/**
	 * Assignment operator overloading.
	 *
	 * @param io Right side operand.
	 *
	 * @return Neurons list instance reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 11 Aug 2011
	 */
	virtual ANNIO& operator=(const ANNIO &io);

	friend std::ostream& operator<<(std::ostream &out, ANNIO &io);
};

/**
 * Output operator redefinition.
 *
 * @param out Output stream.
 *
 * @param io ANN input/ouput instance.
 *
 * @return Output stream.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 11 Aug 2011
 */
std::ostream& operator<<(std::ostream &out, ANNIO &io);

#endif
