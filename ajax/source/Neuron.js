/*******************************************************************************
 *                                                                             *
 * VitoshaTrade is Distributed Artificial Neural Network trained by            *
 * Differential Evolution for prediction of Forex. Project development is in   *
 * Sofia, Bulgaria. Vitosha is a mountain massif, on the outskirts of Sofia,   *
 * the capital of Bulgaria.                                                    *
 *                                                                             *
 * Copyright (C) 2008-2011 by Todor Balabanov  ( tdb@tbsoft.eu )               *
 *                            Iliyan Zankinski ( iliyan_mf@abv.bg )            *
 *                            Galq Cirkalova   ( galq_cirkalova@abv.bg )       *
 *                            Ivan Grozev      ( ivan.iliev.grozev@gmail.com ) *
 *                            Daniel Chutrov   ( d.chutrov@gmail.com )         *
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
/*
 * Include files.
 */
document.write('<script type="text/javascript" src="' + 'NeuronType.js' + '"></script>');

/**
 * Bias neuron value.
 */
const BIAS_VALUE = 1.0;

/**
 * Neurons reset constant value.
 */
const RESET_VALUE = 0.5;

/**
 * Minimal error constant value.
 */
const MIN_ERROR = 0.0;

/**
 * Single neuron class.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 03 Aug 2011
 */
function Neuron() {
	/**
	 * Neuron type. More than one neuron can be bias, input and output in multi
	 * layer networks. Also each neuron can be in more than single type.
	 */
	this.type = REGULAR;

	/**
	 * Neuron value.
	 */
	this.value = 0.0;

	/**
	 * Neuron error in back-propagation training.
	 */
	this.error = 0.0;

	/**
	 * Is regular neuron getter.
	 *
	 * @return True if neuron is regular, false otherwise.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	this.isRegular = function() {
		if (type == REGULAR) {
			return (true );
		} else {
			return (false );
		}
	};

	/**
	 * Regular neuron setter.
	 *
	 * @param value True if neuron will be regular, false otherwise.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	this.setRegular = function(value) {
		if (value == true) {
			type = REGULAR;
		}
	};

	/**
	 * Is bias neuron getter.
	 *
	 * @return True if neuron is bias, false otherwise.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 21 Aug 2009
	 */
	this.isBias = function() {
		if ((type & BIAS) == BIAS) {
			return (true );
		} else {
			return (false );
		}
	};

	/**
	 * Input neurons setter.
	 *
	 * @param value True if neuron will be input, false otherwise.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 29 Apr 2009
	 */
	this.setBias = function(value) {
		if (value == true) {
			switch (type) {
			case REGULAR:
				type = BIAS;
				break;
			case BIAS:
				break;
			case INPUT:
				type = INPUT_BIAS;
				break;
			case INPUT_BIAS:
				break;
			case OUTPUT:
				type = OUTPUT_BIAS;
				break;
			case OUTPUT_BIAS:
				break;
			case OUTPUT_INPUT:
				type = OUTPUT_INPUT_BIAS;
				break;
			case OUTPUT_INPUT_BIAS:
				break;
			}

			this.value = BIAS_VALUE;
		} else if (value == false) {
			switch (type) {
			case REGULAR:
				break;
			case BIAS:
				type = REGULAR;
				break;
			case INPUT:
				break;
			case INPUT_BIAS:
				type = INPUT;
				break;
			case OUTPUT:
				break;
			case OUTPUT_BIAS:
				type = OUTPUT;
				break;
			case OUTPUT_INPUT:
				break;
			case OUTPUT_INPUT_BIAS:
				type = OUTPUT_INPUT;
				break;
			}
		}
	};

	/**
	 * Is input neuron getter.
	 *
	 * @return True if neuron is input, false otherwise.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 30 Apr 2009
	 */
	this.isInput = function() {
		if ((type & INPUT) == INPUT) {
			return (true );
		} else {
			return (false );
		}
	};

	/**
	 * Input neurons setter.
	 *
	 * @param value True if neuron will be input, false otherwise.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 29 Apr 2009
	 */
	this.setInput = function(value) {
		if (value == true) {
			switch (type) {
			case REGULAR:
				type = INPUT;
				break;
			case BIAS:
				type = INPUT_BIAS;
				break;
			case INPUT:
				break;
			case INPUT_BIAS:
				break;
			case OUTPUT:
				type = OUTPUT_INPUT;
				break;
			case OUTPUT_BIAS:
				type = OUTPUT_INPUT_BIAS;
				break;
			case OUTPUT_INPUT:
				break;
			case OUTPUT_INPUT_BIAS:
				break;
			}
		} else if (value == false) {
			switch (type) {
			case REGULAR:
				break;
			case BIAS:
				break;
			case INPUT:
				break;
			case INPUT_BIAS:
				type = BIAS;
				break;
			case OUTPUT:
				break;
			case OUTPUT_BIAS:
				break;
			case OUTPUT_INPUT:
				type = OUTPUT;
				break;
			case OUTPUT_INPUT_BIAS:
				type = OUTPUT_BIAS;
				break;
			}
		}
	};

	/**
	 * Is output neuron getter.
	 *
	 * @return True if neuron is output, false otherwise.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 30 Apr 2009
	 */
	this.isOutput = function() {
		if ((type & OUTPUT) == OUTPUT) {
			return (true );
		} else {
			return (false );
		}
	};

	/**
	 * Output neurons setter.
	 *
	 * @param value True if neuron will be output, false otherwise.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 29 Apr 2009
	 */
	this.setOutput = function(value) {
		if (value == true) {
			switch (type) {
			case REGULAR:
				type = OUTPUT;
				break;
			case BIAS:
				type = OUTPUT_BIAS;
				break;
			case INPUT:
				type = OUTPUT_INPUT;
				break;
			case INPUT_BIAS:
				type = OUTPUT_INPUT_BIAS;
				break;
			case OUTPUT:
				break;
			case OUTPUT_BIAS:
				break;
			case OUTPUT_INPUT:
				break;
			case OUTPUT_INPUT_BIAS:
				break;
			}
		} else if (value == false) {
			switch (type) {
			case REGULAR:
				type = OUTPUT;
				break;
			case BIAS:
				type = OUTPUT_BIAS;
				break;
			case INPUT:
				type = OUTPUT_INPUT;
				break;
			case INPUT_BIAS:
				type = OUTPUT_INPUT_BIAS;
				break;
			case OUTPUT:
				break;
			case OUTPUT_BIAS:
				break;
			case OUTPUT_INPUT:
				break;
			case OUTPUT_INPUT_BIAS:
				break;
			}
		}
	};

	/**
	 * Neuron type getter.
	 *
	 * @return Neuron type.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 04 Aug 2011
	 */
	this.getType = function() {
		return (type );
	};

	/**
	 * Neuron type setter.
	 *
	 * @param type Neuron type.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 04 Aug 2011
	 */
	this.setType = function(type) {
		this.type = type;
	};

	/**
	 * Neuron value getter.
	 *
	 * @return Neuron value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	this.getValue = function() {
		return (value );
	};

	/**
	 * Neuron value setter.
	 *
	 * @param value Neuron value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	this.setValue = function(value) {
		this.value = value;
	};

	/**
	 * Neuron error getter.
	 *
	 * @return Neuron value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	this.getError = function() {
		return (error );
	};

	/**
	 * Neuron error setter.
	 *
	 * @param value Neuron value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	this.setError = function(error) {
		this.error = error;
	};

	/**
	 * Reset neuron to constant value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 19 Aug 2009
	 */
	this.reset = function() {
		if (isBias() == true) {
			value = BIAS_VALUE;
		} else {
			value = RESET_VALUE;
		}

		error = MIN_ERROR;
	};
}
