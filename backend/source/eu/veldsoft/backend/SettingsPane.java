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

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Properties;

import javax.swing.JButton;
import javax.swing.JColorChooser;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;

/**
 * Panel with GUI controls for Neural Network Color Settings.
 * 
 * @author Ralitza Koleva
 * 
 * @email rallly@abv.bg
 * 
 * @date 21 Oct 2011
 */
class SettingsPane extends JPanel {

	/**
	 * Class ActionListener for buttons choosing a neuron type color.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 21 Oct 2011
	 */
	private class ChooseNeuronColorListener implements ActionListener {

		/**
		 * A field which shows the neuron type color.
		 */
		JTextField neuronTypeColorField;

		/**
		 * Constructor of the listener for choosing a neuron type color.
		 * 
		 * @param neuronTypeColorField
		 *            Shows the chosen neuron type color.
		 * 
		 * @author Ralitza Koleva
		 * 
		 * @email rallly@abv.bg
		 * 
		 * @date 21 Oct 2011
		 */
		public ChooseNeuronColorListener(JTextField neuronTypeColorField) {
			this.neuronTypeColorField = neuronTypeColorField;
		}

		/**
		 * Shows a color chooser to change a neuron type color and fills the
		 * relevant field in the chosen color.
		 * 
		 * @author Ralitza Koleva
		 * 
		 * @email rallly@abv.bg
		 * 
		 * @date 21 Oct 2011
		 */
		public void actionPerformed(ActionEvent event) {
			Color initialBackground = neuronTypeColorField.getBackground();
			Color background = JColorChooser.showDialog(null,
					Texts.LABEL_BUTTON_CHOOSE_COLOR, initialBackground);
			if (background != null) {
				neuronTypeColorField.setBackground(background);
			}
		}
	};

	/**
	 * Default serial version UID.
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * Parent applet reference.
	 */
	private VitoshaTradeApplet parent = null;

	/**
	 * Label for Regular Neuron.
	 */
	private JLabel labelColorRegular = new JLabel(
			Texts.LABEL_REGULAR_NEURON_COLOR, SwingConstants.RIGHT);

	/**
	 * Button to open a color picker for choosing color for Regular Neuron.
	 */
	private JButton chooseColorRegular = new JButton(
			Texts.LABEL_BUTTON_CHOOSE_COLOR);

	/**
	 * Field to show the chosen color for Regular Neuron.
	 */
	private JTextField showColorRegular = new JTextField(10);

	/**
	 * Label for Input Neuron.
	 */
	private JLabel labelColorInput = new JLabel(Texts.LABEL_INPUT_NEURON_COLOR,
			SwingConstants.RIGHT);

	/**
	 * Button to open a color picker for choosing color for Input Neuron.
	 */
	private JButton chooseColorInput = new JButton(
			Texts.LABEL_BUTTON_CHOOSE_COLOR);

	/**
	 * Field to show the chosen color for Input Neuron.
	 */
	private JTextField showColorInput = new JTextField(10);

	/**
	 * Label for Output Neuron.
	 */
	private JLabel labelColorOutput = new JLabel(
			Texts.LABEL_OUTPUT_NEURON_COLOR, SwingConstants.RIGHT);

	/**
	 * Button to open a color picker for choosing color for Output Neuron.
	 */
	private JButton chooseColorOutput = new JButton(
			Texts.LABEL_BUTTON_CHOOSE_COLOR);

	/**
	 * Field to show the chosen color for Output Neuron.
	 */
	private JTextField showColorOutput = new JTextField(10);

	/**
	 * Label for Bias Neuron.
	 */
	private JLabel labelColorBias = new JLabel(Texts.LABEL_BIAS_NEURON_COLOR,
			SwingConstants.RIGHT);

	/**
	 * Button to open a color picker for choosing color for Bias Neuron.
	 */
	private JButton chooseColorBias = new JButton(
			Texts.LABEL_BUTTON_CHOOSE_COLOR);

	/**
	 * Field to show the chosen color for Bias Neuron.
	 */
	private JTextField showColorBias = new JTextField(10);

	/**
	 * Label for Input-Output Neuron.
	 */
	private JLabel labelColorInputOutput = new JLabel(
			Texts.LABEL_INPUT_OUTPUT_NEURON_COLOR, JLabel.RIGHT);

	/**
	 * Button to open a color picker for choosing color for Input-Output Neuron.
	 */
	private JButton chooseColorInputOutput = new JButton(
			Texts.LABEL_BUTTON_CHOOSE_COLOR);

	/**
	 * Field to show the chosen color for Input-Output Neuron.
	 */
	private JTextField showColorInputOutput = new JTextField(10);

	/**
	 * Label for Input-Bias Neuron.
	 */
	private JLabel labelColorInputBias = new JLabel(
			Texts.LABEL_INPUT_BIAS_NEURON_COLOR, JLabel.RIGHT);

	/**
	 * Button to open a color picker for choosing color for Input-Bias Neuron.
	 */
	private JButton chooseColorInputBias = new JButton(
			Texts.LABEL_BUTTON_CHOOSE_COLOR);

	/**
	 * Field to show the chosen color for Input-Bias Neuron.
	 */
	private JTextField showColorInputBias = new JTextField(10);

	/**
	 * Label for Output-Bias Neuron.
	 */
	private JLabel labelColorOutputBias = new JLabel(
			Texts.LABEL_OUTPUT_BIAS_NEURON_COLOR, JLabel.RIGHT);

	/**
	 * Button to open a color picker for choosing color for Output-Bias Neuron.
	 */
	private JButton chooseColorOutputBias = new JButton(
			Texts.LABEL_BUTTON_CHOOSE_COLOR);

	/**
	 * Field to show the chosen color for Output-Bias Neuron.
	 */
	private JTextField showColorOutputBias = new JTextField(10);

	/**
	 * Label for Input-Output-Bias Neuron.
	 */
	private JLabel labelColorInputOutputBias = new JLabel(
			Texts.LABEL_INPUT_OUTPUT_BIAS_NEURON_COLOR, JLabel.RIGHT);

	/**
	 * Button to open a color picker for choosing color for Input-Output-Bias
	 * Neuron.
	 */
	private JButton chooseColorInputOutputBias = new JButton(
			Texts.LABEL_BUTTON_CHOOSE_COLOR);

	/**
	 * Field to show the chosen color for Input-Output-Bias Neuron.
	 */
	private JTextField showColorInputOutputBias = new JTextField(10);

	/**
	 * Drop down menu for choosing the size of neurons.
	 */
	private JComboBox chooseNeuronsSize = new JComboBox();

	/**
	 * Label for size of neurons.
	 */
	private JLabel labelNeuronsSize = new JLabel(Texts.LABEL_NEURONS_SIZE,
			JLabel.RIGHT);

	/**
	 * Label for size of neurons' numbers.
	 */
	private JLabel labelNeuronsNumbersSize = new JLabel(
			Texts.LABEL_NEURONS_NUMBERS_SIZE, JLabel.RIGHT);

	/**
	 * Drop down menu for choosing the size of neurons' numbers.
	 */
	private JComboBox chooseNeuronsNumbersSize = new JComboBox();

	/**
	 * Label for work area background color.
	 */
	private JLabel labelWorkAreaBackgroundColor = new JLabel(
			Texts.LABEL_WORK_AREA_BACKGROUND_COLOR, JLabel.RIGHT);

	/**
	 * Button to open a color picker for choosing color for Input-Bias Neuron.
	 */
	private JButton chooseWorkAreaBackgroundColor = new JButton(
			Texts.LABEL_BUTTON_CHOOSE_COLOR);

	/**
	 * Field to show the chosen color for Input-Bias Neuron.
	 */
	private JTextField showWorkAreaBackgroundColor = new JTextField(10);

	/**
	 * Button to save the new neuron colors.
	 */
	private JButton save = new JButton(Texts.LABEL_BUTTON_SAVE_CAPS);

	/**
	 * Button to close the setting pane and return to the network pane (load).
	 */
	private JButton close = new JButton(Texts.LABEL_BUTTON_CLOSE_CAPS);

	/**
	 * Labels width.
	 */
	private static final int LABELS_WIDTH = 200;

	/**
	 * Labels height.
	 */
	private static final int LABELS_HEIGHT = 20;

	/**
	 * Labels dimensions.
	 */
	private static final Dimension LABELS_DIMENTIONS = new Dimension(
			LABELS_WIDTH, LABELS_HEIGHT);

	/**
	 * Buttons width.
	 */
	private static final int BUTTONS_WIDTH = 120;

	/**
	 * Buttons height.
	 */
	private static final int BUTTONS_HEIGHT = 25;

	/**
	 * Minimum neurons' numbers size.
	 */
	private static final int MIN_NEURONS_NUMBERS_SIZE = 8;

	/**
	 * Maximum neurons' numbers size.
	 */
	private static final int MAX_NEURONS_NUMBERS_SIZE = 14;

	/**
	 * Name of the property key which has as a value the color of regular
	 * neurons.
	 */
	private static final String REGULAR_NEURON_COLOR_PROPERTY_KEY = "RegularNeuronColor";

	/**
	 * Name of the property key which has as a value the color of input neurons.
	 */
	private static final String INPUT_NEURON_COLOR_PROPERTY_KEY = "InputNeuronColor";

	/**
	 * Name of the property key which has as a value the color of output
	 * neurons.
	 */
	private static final String OUTPUT_NEURON_COLOR_PROPERTY_KEY = "OutputNeuronColor";

	/**
	 * Name of the property key which has as a value the color of output
	 * neurons.
	 */
	private static final String BIAS_NEURON_COLOR_PROPERTY_KEY = "BiasNeuronColor";

	/**
	 * Name of the property key which has as a value the color of input-output
	 * neurons.
	 */
	private static final String INPUT_OUTPUT_NEURON_COLOR_PROPERTY_KEY = "InputOutputNeuronColor";

	/**
	 * Name of the property key which has as a value the color of input-bias
	 * neurons.
	 */
	private static final String INPUT_BIAS_NEURON_COLOR_PROPERTY_KEY = "InputBiasNeuronColor";

	/**
	 * Name of the property key which has as a value the color of output-bias
	 * neurons.
	 */
	private static final String OUTPUT_BIAS_NEURON_COLOR_PROPERTY_KEY = "OutputBiasNeuronColor";

	/**
	 * Name of the property key which has as a value the color of
	 * input-output-bias neurons.
	 */
	private static final String INPUT_OUTPUT_BIAS_NEURON_COLOR_PROPERTY_KEY = "InputOutputBiasNeuronColor";

	/**
	 * Name of the property key which has as a value the color of work area.
	 */
	private static final String WORK_AREA_BACKGROUND_COLOR_PROPERTY_KEY = "WorkAreaBackgroundColor";

	/**
	 * Buttons dimensions.
	 */
	private static final Dimension BUTTONS_DIMENTIONS = new Dimension(
			BUTTONS_WIDTH, BUTTONS_HEIGHT);

	/**
	 * Constraints determining the elements' arrangement in the panel.
	 */
	private GridBagConstraints constraints = new GridBagConstraints();

	/**
	 * Panel to arrange all elements inside.
	 */
	private JPanel panel = new JPanel(new GridBagLayout());

	/**
	 * Constructing settings pane.
	 * 
	 * @param parent
	 *            The parent class.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 21 Oct 2011
	 */
	public SettingsPane(final VitoshaTradeApplet parent) {
		this.parent = parent;

		add(panel);
		this.setPreferredSize(new Dimension(VitoshaTradeApplet.WIDTH,
				VitoshaTradeApplet.HEIGHT));

		/*
		 * Inserts available neurons sizes.
		 */
		chooseNeuronsSize.addItem(Texts.LABEL_NEURONS_SIZE_SMALL);
		chooseNeuronsSize.addItem(Texts.LABEL_NEURONS_SIZE_MEDIUM);
		chooseNeuronsSize.addItem(Texts.LABEL_NEURONS_SIZE_LARGE);

		/*
		 * Inserts available neurons' numbers sizes.
		 */
		for (int i = MIN_NEURONS_NUMBERS_SIZE; i <= MAX_NEURONS_NUMBERS_SIZE; i++) {
			chooseNeuronsNumbersSize.addItem(i);
		}

		/*
		 * Sets the size of the buttons.
		 */
		chooseColorRegular.setPreferredSize(BUTTONS_DIMENTIONS);
		chooseColorInput.setPreferredSize(BUTTONS_DIMENTIONS);
		chooseColorOutput.setPreferredSize(BUTTONS_DIMENTIONS);
		chooseColorBias.setPreferredSize(BUTTONS_DIMENTIONS);
		chooseColorInputOutput.setPreferredSize(BUTTONS_DIMENTIONS);
		chooseColorInputBias.setPreferredSize(BUTTONS_DIMENTIONS);
		chooseColorOutputBias.setPreferredSize(BUTTONS_DIMENTIONS);
		chooseColorInputOutputBias.setPreferredSize(BUTTONS_DIMENTIONS);
		chooseWorkAreaBackgroundColor.setPreferredSize(BUTTONS_DIMENTIONS);
		save.setPreferredSize(BUTTONS_DIMENTIONS);
		close.setPreferredSize(BUTTONS_DIMENTIONS);

		/*
		 * Sets the size of the combobox of neurons sizes and neurons' numbers
		 * sizes.
		 */
		chooseNeuronsNumbersSize.setPreferredSize(BUTTONS_DIMENTIONS);
		chooseNeuronsSize.setPreferredSize(BUTTONS_DIMENTIONS);

		/*
		 * Sets the size of the labels.
		 */
		labelColorRegular.setPreferredSize(LABELS_DIMENTIONS);
		labelColorInput.setPreferredSize(LABELS_DIMENTIONS);
		labelColorOutput.setPreferredSize(LABELS_DIMENTIONS);
		labelColorBias.setPreferredSize(LABELS_DIMENTIONS);
		labelColorInputOutput.setPreferredSize(LABELS_DIMENTIONS);
		labelColorInputBias.setPreferredSize(LABELS_DIMENTIONS);
		labelColorOutputBias.setPreferredSize(LABELS_DIMENTIONS);
		labelColorInputOutputBias.setPreferredSize(LABELS_DIMENTIONS);
		labelNeuronsSize.setPreferredSize(LABELS_DIMENTIONS);
		labelNeuronsNumbersSize.setPreferredSize(LABELS_DIMENTIONS);
		labelWorkAreaBackgroundColor.setPreferredSize(LABELS_DIMENTIONS);

		/*
		 * Places the elements on the screen, make them editable or not.
		 */
		arrangeElements(labelColorRegular, 0, 10, true);
		arrangeElements(showColorRegular, 10, 10, false);
		arrangeElements(chooseColorRegular, 20, 10, true);
		arrangeElements(labelColorInput, 0, 20, true);
		arrangeElements(showColorInput, 10, 20, false);
		arrangeElements(chooseColorInput, 20, 20, true);
		arrangeElements(labelColorOutput, 0, 30, true);
		arrangeElements(showColorOutput, 10, 30, false);
		arrangeElements(chooseColorOutput, 20, 30, true);
		arrangeElements(labelColorBias, 0, 40, true);
		arrangeElements(showColorBias, 10, 40, false);
		arrangeElements(chooseColorBias, 20, 40, true);
		arrangeElements(labelColorInputOutput, 0, 50, true);
		arrangeElements(showColorInputOutput, 10, 50, false);
		arrangeElements(chooseColorInputOutput, 20, 50, true);
		arrangeElements(labelColorInputBias, 0, 60, true);
		arrangeElements(showColorInputBias, 10, 60, false);
		arrangeElements(chooseColorInputBias, 20, 60, true);
		arrangeElements(labelColorOutputBias, 0, 70, true);
		arrangeElements(showColorOutputBias, 10, 70, false);
		arrangeElements(chooseColorOutputBias, 20, 70, true);
		arrangeElements(labelColorInputOutputBias, 0, 80, true);
		arrangeElements(showColorInputOutputBias, 10, 80, false);
		arrangeElements(chooseColorInputOutputBias, 20, 80, true);
		arrangeElements(labelNeuronsSize, 0, 90, true);
		arrangeElements(chooseNeuronsSize, 20, 90, true);
		arrangeElements(labelNeuronsNumbersSize, 0, 100, true);
		arrangeElements(chooseNeuronsNumbersSize, 20, 100, true);
		arrangeElements(labelWorkAreaBackgroundColor, 0, 110, true);
		arrangeElements(showWorkAreaBackgroundColor, 10, 110, false);
		arrangeElements(chooseWorkAreaBackgroundColor, 20, 110, true);
		arrangeElements(save, 20, 120, true);
		arrangeElements(close, 20, 130, true);

		/*
		 * Gets the color for each type of neuron.
		 */
		readNeuronsTypesAndWorkAreaBackgroundColor(showColorRegular,
				REGULAR_NEURON_COLOR_PROPERTY_KEY);
		readNeuronsTypesAndWorkAreaBackgroundColor(showColorInput,
				INPUT_NEURON_COLOR_PROPERTY_KEY);
		readNeuronsTypesAndWorkAreaBackgroundColor(showColorOutput,
				OUTPUT_NEURON_COLOR_PROPERTY_KEY);
		readNeuronsTypesAndWorkAreaBackgroundColor(showColorBias,
				BIAS_NEURON_COLOR_PROPERTY_KEY);
		readNeuronsTypesAndWorkAreaBackgroundColor(showColorInputOutput,
				INPUT_OUTPUT_NEURON_COLOR_PROPERTY_KEY);
		readNeuronsTypesAndWorkAreaBackgroundColor(showColorInputBias,
				INPUT_BIAS_NEURON_COLOR_PROPERTY_KEY);
		readNeuronsTypesAndWorkAreaBackgroundColor(showColorOutputBias,
				OUTPUT_BIAS_NEURON_COLOR_PROPERTY_KEY);
		readNeuronsTypesAndWorkAreaBackgroundColor(showColorInputOutputBias,
				INPUT_OUTPUT_BIAS_NEURON_COLOR_PROPERTY_KEY);

		/*
		 * Gets the work area background color.
		 */
		readNeuronsTypesAndWorkAreaBackgroundColor(showWorkAreaBackgroundColor,
				WORK_AREA_BACKGROUND_COLOR_PROPERTY_KEY);

		/*
		 * Gets the current size of neurons and selects it in the available
		 * sizes combobox.
		 */
		readNeuronsSize();

		/*
		 * Gets the current size of neuron's numbers and selects it in the
		 * available sizes combobox.
		 */
		readNeuronsNumbersSize();

		/*
		 * Adds Action Listener to each button.
		 */
		chooseColorRegular.addActionListener(new ChooseNeuronColorListener(
				showColorRegular));
		chooseColorInput.addActionListener(new ChooseNeuronColorListener(
				showColorInput));
		chooseColorOutput.addActionListener(new ChooseNeuronColorListener(
				showColorOutput));
		chooseColorBias.addActionListener(new ChooseNeuronColorListener(
				showColorBias));
		chooseColorInputOutput.addActionListener(new ChooseNeuronColorListener(
				showColorInputOutput));
		chooseColorInputBias.addActionListener(new ChooseNeuronColorListener(
				showColorInputBias));
		chooseColorOutputBias.addActionListener(new ChooseNeuronColorListener(
				showColorOutputBias));
		chooseColorInputOutputBias
				.addActionListener(new ChooseNeuronColorListener(
						showColorInputOutputBias));
		chooseWorkAreaBackgroundColor
				.addActionListener(new ChooseNeuronColorListener(
						showWorkAreaBackgroundColor));

		save.addActionListener(new ActionListener() {

			/**
			 * Saves the newly chosen colors to a file.
			 * 
			 * @author Ralitza Koleva
			 * 
			 * @email rallly@abv.bg
			 * 
			 * @date 21 Oct 2011
			 */
			public void actionPerformed(ActionEvent event) {
				try {
					Properties properties = new Properties();

					/*
					 * Loads all properties from the property file.
					 */
					FileInputStream allProperties = new FileInputStream(
							Util.PROPERTIES_FILE_NAME);
					properties.load(allProperties);

					/*
					 * Calls a function to write the newly chosen colors to a
					 * file.
					 */
					writeNeuronsTypesAndWorkAreaBackgroundColor(
							showColorRegular,
							REGULAR_NEURON_COLOR_PROPERTY_KEY, properties);
					writeNeuronsTypesAndWorkAreaBackgroundColor(showColorInput,
							INPUT_NEURON_COLOR_PROPERTY_KEY, properties);
					writeNeuronsTypesAndWorkAreaBackgroundColor(
							showColorOutput, OUTPUT_NEURON_COLOR_PROPERTY_KEY,
							properties);
					writeNeuronsTypesAndWorkAreaBackgroundColor(showColorBias,
							BIAS_NEURON_COLOR_PROPERTY_KEY, properties);
					writeNeuronsTypesAndWorkAreaBackgroundColor(
							showColorInputOutput,
							INPUT_OUTPUT_NEURON_COLOR_PROPERTY_KEY, properties);
					writeNeuronsTypesAndWorkAreaBackgroundColor(
							showColorInputBias,
							INPUT_BIAS_NEURON_COLOR_PROPERTY_KEY, properties);
					writeNeuronsTypesAndWorkAreaBackgroundColor(
							showColorOutputBias,
							OUTPUT_BIAS_NEURON_COLOR_PROPERTY_KEY, properties);
					writeNeuronsTypesAndWorkAreaBackgroundColor(
							showColorInputOutputBias,
							INPUT_OUTPUT_BIAS_NEURON_COLOR_PROPERTY_KEY,
							properties);
					writeNeuronsTypesAndWorkAreaBackgroundColor(
							showWorkAreaBackgroundColor,
							WORK_AREA_BACKGROUND_COLOR_PROPERTY_KEY, properties);

					/*
					 * Calls a function to save the newly chosen neurons size to
					 * a file.
					 */
					writeNeuronsSize(properties);

					/*
					 * Calls a function to save the newly chosen neurons'
					 * numbers size to a file.
					 */
					writeNeuronsNumbersSize(properties);

					FileOutputStream out = new FileOutputStream(
							Util.PROPERTIES_FILE_NAME);
					properties.store(out, "");
					allProperties.close();
					out.close();
				} catch (Exception ex) {
					ex.printStackTrace();
				} finally {
					parent.showNetworkPane();
				}
			}
		});

		close.addActionListener(new ActionListener() {

			/**
			 * Closes the settings pane and goes to the screen for loading ANN.
			 * 
			 * @author Ralitza Koleva
			 * 
			 * @email rallly@abv.bg
			 * 
			 * @date 10 Nov 2011
			 */
			public void actionPerformed(ActionEvent event) {
				parent.showNetworkPane();
			}
		});
	}

	/**
	 * Reads the current neuron types colors and work area background color from
	 * a file and shows the colors in their corresponding fields.
	 * 
	 * @param showNeuronColorField
	 *            The text field to be colored in the current color.
	 * 
	 * @param colorProperty
	 *            The parameter name, containing the color.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 21 Oct 2011
	 */
	public void readNeuronsTypesAndWorkAreaBackgroundColor(
			JTextField showNeuronColorField, String colorProperty) {
		try {
			Properties properties = new Properties();
			FileInputStream in = new FileInputStream(Util.PROPERTIES_FILE_NAME);
			properties.load(in);
			int color = Integer.parseInt(properties.getProperty(colorProperty));
			Color neuronColor = new Color(color);
			showNeuronColorField.setBackground(neuronColor);
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	/**
	 * Writes the new neuron types colors and the new work area background color
	 * to a file.
	 * 
	 * 
	 * @param showNeuronColorField
	 *            The text field to be colored in the current color.
	 * 
	 * @param colorProperty
	 *            The parameter name, containing the color.
	 * 
	 * @param properties
	 *            Properties to store the neuron types colors.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 21 Oct 2011
	 */
	public void writeNeuronsTypesAndWorkAreaBackgroundColor(
			JTextField showNeuronColorField, String colorProperty,
			Properties properties) {

		String color = Integer.toString(showNeuronColorField.getBackground()
				.getRGB());
		properties.setProperty(colorProperty, color);
	}

	/**
	 * Reads the current neurons size from a file and selects it in the
	 * available sizes combobox.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 06 Dec 2011
	 */
	public void readNeuronsSize() {
		try {
			Properties properties = new Properties();
			FileInputStream in = new FileInputStream(Util.PROPERTIES_FILE_NAME);
			properties.load(in);
			String currentNeuronsSize = properties.getProperty("NeuronsSize");
			chooseNeuronsSize.setSelectedItem(currentNeuronsSize);
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	/**
	 * Reads the current neurons' numbers size from a file and selects it in the
	 * available sizes combobox.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 23 Nov 2011
	 */
	public void readNeuronsNumbersSize() {
		try {
			Properties properties = new Properties();
			FileInputStream in = new FileInputStream(Util.PROPERTIES_FILE_NAME);
			properties.load(in);
			int currentNeuronsNumberSize = Integer.parseInt(properties
					.getProperty("NeuronsNumbersSize"));
			chooseNeuronsNumbersSize.setSelectedItem(currentNeuronsNumberSize);
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	/**
	 * Writes the new size of neurons to a file.
	 * 
	 * @param properties
	 *            Properties to store the size of neurons.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 06 Dec 2011
	 */
	public void writeNeuronsSize(Properties properties) {
		String neuronsSelectedSize = chooseNeuronsSize.getSelectedItem()
				.toString();
		properties.setProperty("NeuronsSize", neuronsSelectedSize);
	}

	/**
	 * Writes the new size of neurons' numbers to a file.
	 * 
	 * @param properties
	 *            Properties to store the size of neurons' numbers.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 23 Nov 2011
	 */
	public void writeNeuronsNumbersSize(Properties properties) {
		String neuronsNumbersSelectedSize = chooseNeuronsNumbersSize
				.getSelectedItem().toString();
		properties
				.setProperty("NeuronsNumbersSize", neuronsNumbersSelectedSize);
	}

	/**
	 * Helps arranging the elements on the screen.
	 * 
	 * @param component
	 *            The component to be placed inside the panel.
	 * 
	 * @param gridX
	 *            X-coordinate of the component.
	 * 
	 * @param gridY
	 *            Y-coordinate of the component.
	 * 
	 * @param editable
	 *            Determines whether the component is enabled.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 25 Oct 2011
	 */
	public void arrangeElements(JComponent component, int gridX, int gridY,
			boolean enabled) {
		constraints.gridx = gridX;
		constraints.gridy = gridY;
		constraints.insets = new Insets(10, 10, 8, 10);
		panel.add(component, constraints);
		component.setEnabled(enabled);
	}
}
