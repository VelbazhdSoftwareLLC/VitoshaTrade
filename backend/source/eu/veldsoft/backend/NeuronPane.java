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

import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JCheckBox;
import javax.swing.JTextField;

/**
 * Panel with GUI controls for Neuron Management.
 *
 * @author Momchil Anachkov
 *
 * @email mZer0000@gmail.com
 *
 * @date 18 Nov 2010
 */
class NeuronPane extends JPanel {

	/**
	 * Default serial version UID.
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * Parent applet reference.
	 */
	private VitoshaTradeApplet parent = null;

	/**
	 * GUI control for obtaining the ID of a specific neuron.
	 */
	private JTextField neuronNumber = new JTextField();

	/**
	 * GUI control for obtaining and setting the input flag for a specific
	 * neuron.
	 */
	private JCheckBox inputCheckbox;

	/**
	 * GUI control for obtaining and setting the output flag for a specific
	 * neuron.
	 */
	private JCheckBox outputCheckbox;

	/**
	 * GUI control for obtaining and setting the regular flag for a specific
	 * neuron.
	 */
	private JCheckBox regularCheckbox;

	/**
	 * GUI control for obtaining and setting the BIAS flag for a specific
	 * neuron.
	 */
	private JCheckBox biasCheckbox;

	/**
	 * GUI control for obtaining and setting X location of a specific neuron.
	 */
	JTextField axisX = new JTextField();

	/**
	 * GUI control for obtaining and setting the Y location of a specific
	 * neuron.
	 */
	JTextField axisY = new JTextField();

	/**
	 * GUI control for obtaining neuron connection weight.
	 */
	private JTextField weight = new JTextField();

	/**
	 * GUI control for obtaining and setting neuron connection activity.
	 */
	private JTextField activity = new JTextField();

	/**
	 * Constructing neuron pane.
	 *
	 * @param parent
	 *            The parent class.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Nov 2010
	 */
	public NeuronPane(final VitoshaTradeApplet parent) {
		this.parent = parent;
		this.setPreferredSize(new Dimension(VitoshaTradeApplet.EAST_PANE_WIDTH,
											VitoshaTradeApplet.EAST_PANE_HEIGHT));

		setLayout(new GridLayout(25, 1));

		add(new JLabel(Texts.LABEL_NUMBER));
		add(neuronNumber);
		neuronNumber.setEditable(false);

		/*
		 * GUI control for obtaining and setting the flags of a specific neuron.
		 */
		biasCheckbox = new JCheckBox(Texts.LABEL_BIAS_NEURON);
		inputCheckbox = new JCheckBox(Texts.LABEL_INPUT_NEURON);
		outputCheckbox = new JCheckBox(Texts.LABEL_OUTPUT_NEURON);
		regularCheckbox = new JCheckBox(Texts.LABEL_REGULAR_NEURON);
		add(inputCheckbox);
		add(outputCheckbox);
		add(regularCheckbox);
		add(biasCheckbox);

		add(new JLabel(Texts.LABEL_WEIGHT));
		add(weight);

		add(new JLabel(Texts.LABEL_ACTIVITY));
		add(activity);

		add(new JLabel(Texts.LABEL_X_COORDINATE));
		add(axisX);

		add(new JLabel(Texts.LABEL_Y_COORDINATE));
		add(axisY);

		inputCheckbox.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				if (inputCheckbox.isSelected() == true) {
					parent.ann.flags[Integer.parseInt(neuronNumber.getText())] |= ArtificialNeuralNetwork.INPUT_NEURON;
				} else {
					parent.ann.flags[Integer.parseInt(neuronNumber.getText())] &= (~ArtificialNeuralNetwork.INPUT_NEURON);
				}
				parent.workArea.repaint();
			}
		});

		outputCheckbox.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				if (outputCheckbox.isSelected() == true) {
					parent.ann.flags[Integer.parseInt(neuronNumber.getText())] |= ArtificialNeuralNetwork.OUTPUT_NEURON;
				} else {
					parent.ann.flags[Integer.parseInt(neuronNumber.getText())] &= (~ArtificialNeuralNetwork.OUTPUT_NEURON);
				}
				parent.workArea.repaint();
			}
		});

		regularCheckbox.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				if (regularCheckbox.isSelected() == true) {
					parent.ann.flags[Integer.parseInt(neuronNumber.getText())] |= ArtificialNeuralNetwork.REGULAR_NEURON;
				} else {
					parent.ann.flags[Integer.parseInt(neuronNumber.getText())] &= (~ArtificialNeuralNetwork.REGULAR_NEURON);
				}
				parent.workArea.repaint();
			}
		});

		biasCheckbox.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				if (biasCheckbox.isSelected() == true) {
					parent.ann.flags[Integer.parseInt(neuronNumber.getText())] |= ArtificialNeuralNetwork.BIAS_NEURON;
				} else {
					parent.ann.flags[Integer.parseInt(neuronNumber.getText())] &= (~ArtificialNeuralNetwork.BIAS_NEURON);
				}
				parent.workArea.repaint();
			}
		});

		weight.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent å) {
				parent.ann.weights[Integer.parseInt(neuronNumber.getText())][Integer
						.parseInt(neuronNumber.getText())] = Double
								.parseDouble(weight.getText());
				parent.workArea.repaint();
			}
		});

		activity.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent å) {
				parent.ann.activities[Integer.parseInt(neuronNumber.getText())][Integer
						.parseInt(neuronNumber.getText())] = Double
								.parseDouble(activity.getText());
				parent.workArea.repaint();
			}
		});

		axisX.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent å) {
				parent.ann.coordinates[Integer.parseInt(neuronNumber.getText())][0] = Integer
						.parseInt(axisX.getText());
				parent.workArea.repaint();
			}
		});

		axisY.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent å) {
				parent.ann.coordinates[Integer.parseInt(neuronNumber.getText())][1] = Integer
						.parseInt(axisY.getText());
				parent.workArea.repaint();
			}
		});
	}

	/**
	 * Loading neuron properties.
	 *
	 * @param neuronIndex
	 *            Number of selected neuron.
	 *
	 * @param flags
	 *            Flags of selected neuron.
	 *
	 * @param coordinateX
	 *            X coordinate of selected neuron.
	 *
	 * @param coordinateY
	 *            Y coordinate of selected neuron.
	 *
	 * @param neuronConnectionActivity
	 *            Activity of neuron connection with itself.
	 *
	 * @param neuronConnectionWeight
	 *            Weight of neuron connection with itself.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 01 Feb 2010
	 */
	void setValues(int neuronIndex, int flags, int coordinateX,
				   int coordinateY, double neuronConnectionActivity,
				   double neuronConnectionWeight) {
		neuronNumber.setText(Integer.toString(neuronIndex));

		switch (flags) {
		case (ArtificialNeuralNetwork.REGULAR_NEURON):
			inputCheckbox.setSelected(false);
			outputCheckbox.setSelected(false);
			regularCheckbox.setSelected(true);
			biasCheckbox.setSelected(false);
			break;
		case (ArtificialNeuralNetwork.BIAS_NEURON):
			inputCheckbox.setSelected(false);
			outputCheckbox.setSelected(false);
			regularCheckbox.setSelected(false);
			biasCheckbox.setSelected(true);
			break;
		case (ArtificialNeuralNetwork.INPUT_NEURON):
			inputCheckbox.setSelected(true);
			outputCheckbox.setSelected(false);
			regularCheckbox.setSelected(false);
			biasCheckbox.setSelected(false);
			break;
		case (ArtificialNeuralNetwork.BIAS_NEURON | ArtificialNeuralNetwork.INPUT_NEURON):
			inputCheckbox.setSelected(true);
			outputCheckbox.setSelected(false);
			regularCheckbox.setSelected(false);
			biasCheckbox.setSelected(true);
			break;
		case (ArtificialNeuralNetwork.OUTPUT_NEURON):
			inputCheckbox.setSelected(false);
			outputCheckbox.setSelected(true);
			regularCheckbox.setSelected(false);
			biasCheckbox.setSelected(false);
			break;
		case (ArtificialNeuralNetwork.BIAS_NEURON | ArtificialNeuralNetwork.OUTPUT_NEURON):
			inputCheckbox.setSelected(false);
			outputCheckbox.setSelected(true);
			regularCheckbox.setSelected(false);
			biasCheckbox.setSelected(true);
			break;
		case (ArtificialNeuralNetwork.INPUT_NEURON | ArtificialNeuralNetwork.OUTPUT_NEURON):
			inputCheckbox.setSelected(true);
			outputCheckbox.setSelected(true);
			regularCheckbox.setSelected(false);
			biasCheckbox.setSelected(false);
			break;
		case (ArtificialNeuralNetwork.BIAS_NEURON
						| ArtificialNeuralNetwork.INPUT_NEURON | ArtificialNeuralNetwork.OUTPUT_NEURON):
			inputCheckbox.setSelected(true);
			outputCheckbox.setSelected(true);
			regularCheckbox.setSelected(false);
			biasCheckbox.setSelected(true);
			break;
		}

		axisX.setText(Integer.toString(coordinateX));
		axisY.setText(Integer.toString(coordinateY));
		activity.setText(Double.toString(neuronConnectionActivity));
		weight.setText(Double.toString(neuronConnectionWeight));
	}
}
