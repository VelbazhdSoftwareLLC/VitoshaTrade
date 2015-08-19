package eu.veldsoft.backend;

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
 *                            Momchil Anachkov ( mZer0000@gmail.com )          *
 *                            Ralitza Koleva   ( rallly@abv.bg )               *
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

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Properties;
import java.util.Random;

/**
 * Utility class.
 * 
 * @author Todor Balabanov
 * 
 * @email todor.balabanov@gmail.com
 * 
 * @date 19 Aug 2015
 */
class Util {

	/**
	 * Pseudo-random number generator.
	 */
	static final Random PRNG;

	/**
	 * Visual preferences.
	 * 
	 * @author Todor Balabanov
	 * 
	 * @email todor.balabanov@gmail.com
	 * 
	 * @date 19 Aug 2015
	 */
	static class Preferences {
		static String neuronSize;
		static int neuronRadius;
		static int backgroundColor;
		static int neuronIdFontSize;
		static String dbHost;
		static String dbPort;
		static String dbName;
		static int chooseNeuronsNumbersSize;
		static int regularNeuronColor;
		static int inputNeuronColor;
		static int outputNeuronColor;
		static int biasNeuronColor;
		static int inputOutputNeuronColor;
		static int inputBiasNeuronColor;
		static int outputBiasNeuronColor;
		static int inputOutputBiasNeuronColor;
	}

	/**
	 * Initialize all static members.
	 */
	static {
		PRNG = new Random();

		FileInputStream in = null;
		Properties properties = new Properties();

		try {
			in = new FileInputStream(Util.PROPERTIES_FILE_NAME);
			properties.load(in);
		} catch (Exception ex) {
			Preferences.neuronSize = "Small";
			Preferences.neuronRadius = Math.min(
					VitoshaTradeApplet.CENTRAL_PANE_WIDTH,
					VitoshaTradeApplet.CENTRAL_PANE_HEIGHT) / 100;
			Preferences.backgroundColor = 0xFFFFFF;
			Preferences.neuronIdFontSize = 9;
			Preferences.dbHost = "localhost";
			Preferences.dbPort = "3306";
			Preferences.dbName = "veldsoft_vitoshatrade";
			Preferences.chooseNeuronsNumbersSize = 9;
			Preferences.regularNeuronColor = Util.PRNG.nextInt(0xFFFFFF + 1);
			Preferences.inputNeuronColor = Util.PRNG.nextInt(0xFFFFFF + 1);
			Preferences.outputNeuronColor = Util.PRNG.nextInt(0xFFFFFF + 1);
			Preferences.biasNeuronColor = Util.PRNG.nextInt(0xFFFFFF + 1);
			Preferences.inputOutputNeuronColor = Util.PRNG
					.nextInt(0xFFFFFF + 1);
			Preferences.inputBiasNeuronColor = Util.PRNG.nextInt(0xFFFFFF + 1);
			Preferences.outputBiasNeuronColor = Util.PRNG.nextInt(0xFFFFFF + 1);
			Preferences.inputOutputBiasNeuronColor = Util.PRNG
					.nextInt(0xFFFFFF + 1);
		}

		if (in != null) {
			Preferences.neuronSize = properties.getProperty("NeuronsSize");
			if (Preferences.neuronSize.equals("Small")) {
				Preferences.neuronRadius = Math.min(
						VitoshaTradeApplet.CENTRAL_PANE_WIDTH,
						VitoshaTradeApplet.CENTRAL_PANE_HEIGHT) / 100;
			} else if (Preferences.neuronSize.equals("Medium")) {
				Preferences.neuronRadius = Math.min(
						VitoshaTradeApplet.CENTRAL_PANE_WIDTH,
						VitoshaTradeApplet.CENTRAL_PANE_HEIGHT) / 80;
			} else if (Preferences.neuronSize.equals("Large")) {
				Preferences.neuronRadius = Math.min(
						VitoshaTradeApplet.CENTRAL_PANE_WIDTH,
						VitoshaTradeApplet.CENTRAL_PANE_HEIGHT) / 70;
			}

			Preferences.backgroundColor = Integer.parseInt(properties
					.getProperty(Util.WORK_AREA_BACKGROUND_COLOR_PROPERTY_KEY));

			Preferences.neuronIdFontSize = Integer.parseInt(properties
					.getProperty("NeuronsNumbersSize"));

			Preferences.dbHost = properties.getProperty("DatabaseHost");
			Preferences.dbPort = properties.getProperty("DatabasePort");
			Preferences.dbName = properties.getProperty("DatabaseName");

			Preferences.chooseNeuronsNumbersSize = Integer.parseInt(properties
					.getProperty("NeuronsNumbersSize"));

			Preferences.regularNeuronColor = Integer.parseInt(properties
					.getProperty(Util.REGULAR_NEURON_COLOR_PROPERTY_KEY));
			Preferences.inputNeuronColor = Integer.parseInt(properties
					.getProperty(Util.INPUT_NEURON_COLOR_PROPERTY_KEY));
			Preferences.outputNeuronColor = Integer.parseInt(properties
					.getProperty(Util.OUTPUT_NEURON_COLOR_PROPERTY_KEY));
			Preferences.biasNeuronColor = Integer.parseInt(properties
					.getProperty(Util.BIAS_NEURON_COLOR_PROPERTY_KEY));
			Preferences.inputOutputNeuronColor = Integer.parseInt(properties
					.getProperty(Util.INPUT_OUTPUT_NEURON_COLOR_PROPERTY_KEY));
			Preferences.inputBiasNeuronColor = Integer.parseInt(properties
					.getProperty(Util.INPUT_BIAS_NEURON_COLOR_PROPERTY_KEY));
			Preferences.outputBiasNeuronColor = Integer.parseInt(properties
					.getProperty(Util.OUTPUT_BIAS_NEURON_COLOR_PROPERTY_KEY));
			Preferences.inputOutputBiasNeuronColor = Integer
					.parseInt(properties
							.getProperty(Util.INPUT_OUTPUT_BIAS_NEURON_COLOR_PROPERTY_KEY));
		}

		try {
			if (in != null) {
				in.close();
			}
		} catch (Exception ex) {
		}

		properties.setProperty("NeuronsSize", Preferences.neuronSize);
		properties.setProperty(Util.WORK_AREA_BACKGROUND_COLOR_PROPERTY_KEY, ""
				+ Preferences.backgroundColor);
		properties.setProperty("NeuronsNumbersSize", ""
				+ Preferences.neuronIdFontSize);
		properties.setProperty("DatabaseHost", Preferences.dbHost);
		properties.setProperty("DatabasePort", Preferences.dbPort);
		properties.setProperty("DatabaseName", Preferences.dbName);
		properties.setProperty("NeuronsNumbersSize", ""
				+ Preferences.chooseNeuronsNumbersSize);
		properties.setProperty(Util.REGULAR_NEURON_COLOR_PROPERTY_KEY, ""
				+ Preferences.regularNeuronColor);
		properties.setProperty(Util.INPUT_NEURON_COLOR_PROPERTY_KEY, ""
				+ Preferences.inputNeuronColor);
		properties.setProperty(Util.OUTPUT_NEURON_COLOR_PROPERTY_KEY, ""
				+ Preferences.outputNeuronColor);
		properties.setProperty(Util.BIAS_NEURON_COLOR_PROPERTY_KEY, ""
				+ Preferences.biasNeuronColor);
		properties.setProperty(Util.INPUT_OUTPUT_NEURON_COLOR_PROPERTY_KEY, ""
				+ Preferences.inputOutputNeuronColor);
		properties.setProperty(Util.INPUT_BIAS_NEURON_COLOR_PROPERTY_KEY, ""
				+ Preferences.inputBiasNeuronColor);
		properties.setProperty(Util.OUTPUT_BIAS_NEURON_COLOR_PROPERTY_KEY, ""
				+ Preferences.outputBiasNeuronColor);
		properties.setProperty(
				Util.INPUT_OUTPUT_BIAS_NEURON_COLOR_PROPERTY_KEY, ""
						+ Preferences.inputOutputBiasNeuronColor);

		try {
			FileOutputStream out = new FileOutputStream(
					Util.PROPERTIES_FILE_NAME);
			properties.store(out, "");
			out.close();
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	/**
	 * Properties file name constant.
	 */
	static final String PROPERTIES_FILE_NAME = "setup.ini";

	/**
	 * Name of the property key which has as a value the color of regular
	 * neurons.
	 */
	static final String REGULAR_NEURON_COLOR_PROPERTY_KEY = "RegularNeuronColor";

	/**
	 * Name of the property key which has as a value the color of input neurons.
	 */
	static final String INPUT_NEURON_COLOR_PROPERTY_KEY = "InputNeuronColor";

	/**
	 * Name of the property key which has as a value the color of output
	 * neurons.
	 */
	static final String OUTPUT_NEURON_COLOR_PROPERTY_KEY = "OutputNeuronColor";

	/**
	 * Name of the property key which has as a value the color of output
	 * neurons.
	 */
	static final String BIAS_NEURON_COLOR_PROPERTY_KEY = "BiasNeuronColor";

	/**
	 * Name of the property key which has as a value the color of input-output
	 * neurons.
	 */
	static final String INPUT_OUTPUT_NEURON_COLOR_PROPERTY_KEY = "InputOutputNeuronColor";

	/**
	 * Name of the property key which has as a value the color of input-bias
	 * neurons.
	 */
	static final String INPUT_BIAS_NEURON_COLOR_PROPERTY_KEY = "InputBiasNeuronColor";

	/**
	 * Name of the property key which has as a value the color of output-bias
	 * neurons.
	 */
	static final String OUTPUT_BIAS_NEURON_COLOR_PROPERTY_KEY = "OutputBiasNeuronColor";

	/**
	 * Name of the property key which has as a value the color of
	 * input-output-bias neurons.
	 */
	static final String INPUT_OUTPUT_BIAS_NEURON_COLOR_PROPERTY_KEY = "InputOutputBiasNeuronColor";

	/**
	 * Name of the property key which has as a value the color of work area.
	 */
	static final String WORK_AREA_BACKGROUND_COLOR_PROPERTY_KEY = "WorkAreaBackgroundColor";

}
