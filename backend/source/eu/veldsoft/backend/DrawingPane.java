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
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.io.FileInputStream;
import java.util.Properties;
import java.util.Random;

import javax.swing.JPanel;

/**
 * Panel with ANN drawoing functionality.
 * 
 * @author Momchil Anachkov
 * 
 * @email mZer0000@gmail.com
 * 
 * @date 10 Jan 2011
 */
class DrawingPane extends JPanel {
	/**
	 * Default serial version UID.
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * Selection alpha value.
	 */
	private static int SELECTION_ALPHA = 127;

	/**
	 * Regular neuron color.
	 */
	private Color regularNeuronColor;

	/**
	 * Bias neuron color.
	 */
	private Color biasNeuronColor;

	/**
	 * Input neuron color.
	 */
	private Color inputNeuronColor;

	/**
	 * Output neuron color.
	 */
	private Color outputNeuronColor;

	/**
	 * Input-Output neuron color.
	 */
	private Color inputOutputNeuronColor;

	/**
	 * Input-Bias neuron color.
	 */
	private Color inputBiasNeuronColor;

	/**
	 * Output-Bias neuron color.
	 */
	private Color outputBiasNeuronColor;

	/**
	 * Input-Output-Bias neuron color.
	 */
	private Color inputOutputBiasNeuronColor;

	/**
	 * Connections color.
	 */
	private Color connectionColor = new Color(0, 0, 0);

	/**
	 * Helps making the connections colors, different colors depending on
	 * activities/weights/both.
	 */
	double connectionColorTemp = 0;

	/**
	 * No index selected constant.
	 */
	private static final int INDEX_NOT_SELECTED = -1;

	/**
	 * Neuron visual radius.
	 */
	private int neuronRadius = 0;

	/**
	 * Parent applet reference.
	 */
	private VitoshaTradeApplet parent = null;

	/**
	 * Keep selection of first neuron index during visualization.
	 */
	private int firstNeuronIndex = INDEX_NOT_SELECTED;

	/**
	 * Keep selection of second neuron index during visualization.
	 */
	private int secondNeuronIndex = INDEX_NOT_SELECTED;

	/**
	 * Drawing pane constructor.
	 * 
	 * @param parent
	 *            The parent class.
	 * 
	 * @author Momchil Anachkov
	 * 
	 * @email mZer0000@gmail.com
	 * 
	 * @date 10 Jan 2011
	 */
	public DrawingPane(final VitoshaTradeApplet parent) {
		this.parent = parent;
		this.setPreferredSize(new Dimension(
				VitoshaTradeApplet.CENTRAL_PANE_WIDTH,
				VitoshaTradeApplet.CENTRAL_PANE_HEIGHT));

		// TODO Do it in size changed listener.
		neuronRadius = calculateNeuronRadius();

		/*
		 * Mouse listener for click events to select components (neurons or
		 * connections).
		 */
		this.addMouseListener(new MouseListener() {

			public void mouseClicked(MouseEvent event) {
			}

			public void mouseEntered(MouseEvent event) {
			}

			public void mouseExited(MouseEvent event) {
			}

			public void mousePressed(MouseEvent event) {
				/*
				 * Do nothing if there is no coordinates.
				 */
				if (parent.ann == null) {
					return;
				}

				int x = event.getX();
				int y = event.getY();
				boolean controlKeyDown = event.isControlDown();

				/*
				 * Find selected neuron index.
				 */
				int xi;
				int yi;
				int squareDistance;
				int coordinates[][] = parent.ann.coordinates;
				int selectedNeuronIndex = INDEX_NOT_SELECTED;
				for (int i = 0; i < coordinates.length; i++) {
					xi = coordinates[i][0];
					yi = coordinates[i][1];

					squareDistance = (x - xi) * (x - xi) + (y - yi) * (y - yi);

					if (neuronRadius * neuronRadius >= squareDistance) {
						selectedNeuronIndex = i;
						break;
					}
				}

				/*
				 * Display connection properties if connection is selected.
				 */
				if (selectedNeuronIndex != INDEX_NOT_SELECTED
						&& firstNeuronIndex != INDEX_NOT_SELECTED
						&& secondNeuronIndex == INDEX_NOT_SELECTED
						&& controlKeyDown == true) {
					secondNeuronIndex = selectedNeuronIndex;

					repaint();
					parent.showConnectionPane();
					parent.connectionPane
							.setValues(
									firstNeuronIndex,
									selectedNeuronIndex,
									parent.ann.activities[firstNeuronIndex][secondNeuronIndex],
									parent.ann.weights[firstNeuronIndex][secondNeuronIndex]);
					return;
				}

				/*
				 * Start selection of connection.
				 */
				if (selectedNeuronIndex != INDEX_NOT_SELECTED
						&& firstNeuronIndex == INDEX_NOT_SELECTED
						&& secondNeuronIndex == INDEX_NOT_SELECTED
						&& controlKeyDown == true) {
					firstNeuronIndex = selectedNeuronIndex;
					secondNeuronIndex = INDEX_NOT_SELECTED;

					return;
				}

				/*
				 * Select single neuron.
				 */
				if (selectedNeuronIndex != INDEX_NOT_SELECTED
						&& firstNeuronIndex == INDEX_NOT_SELECTED
						&& secondNeuronIndex == INDEX_NOT_SELECTED
						&& controlKeyDown == false) {
					firstNeuronIndex = selectedNeuronIndex;
					secondNeuronIndex = INDEX_NOT_SELECTED;

					parent.showNeuronPane();
					parent.neuronPane
							.setValues(
									firstNeuronIndex,
									parent.ann.flags[firstNeuronIndex],
									parent.ann.coordinates[firstNeuronIndex][0],
									parent.ann.coordinates[firstNeuronIndex][1],
									parent.ann.activities[firstNeuronIndex][firstNeuronIndex],
									parent.ann.weights[firstNeuronIndex][firstNeuronIndex]);

					return;
				}

				/*
				 * If nothing is selected show network pane.
				 */
				if (selectedNeuronIndex == INDEX_NOT_SELECTED) {
					firstNeuronIndex = INDEX_NOT_SELECTED;
					secondNeuronIndex = INDEX_NOT_SELECTED;
					parent.showNetworkPane();
					return;
				}
			}

			public void mouseReleased(MouseEvent event) {
				/*
				 * Selection of connections needs two mouse clicks.
				 */
				if (event.isControlDown() == true) {
					return;
				}

				/*
				 * After mouse button release it is better neuron not to be
				 * selected.
				 */
				firstNeuronIndex = INDEX_NOT_SELECTED;
				secondNeuronIndex = INDEX_NOT_SELECTED;
			}
		});

		/*
		 * Drag neuron source code (changing neuron position).
		 */
		addMouseMotionListener(new MouseMotionListener() {
			public void mouseDragged(MouseEvent event) {
				if (firstNeuronIndex != INDEX_NOT_SELECTED
						&& secondNeuronIndex == INDEX_NOT_SELECTED) {
					parent.ann.coordinates[firstNeuronIndex][0] = event.getX();
					parent.ann.coordinates[firstNeuronIndex][1] = event.getY();

					parent.neuronPane.axisX.setText(""
							+ parent.ann.coordinates[firstNeuronIndex][0]);
					parent.neuronPane.axisY.setText(""
							+ parent.ann.coordinates[firstNeuronIndex][1]);

					repaint();
				}
			}

			public void mouseMoved(MouseEvent event) {
			}
		});
	}

	/**
	 * Panel paint.
	 * 
	 * @param g
	 *            Graphic context.
	 * 
	 * @author Momchil Anachkov
	 * 
	 * @email mZer0000@gmail.com
	 * 
	 * @date 10 Jan 2011
	 */
	public void paint(Graphics g) {
		ArtificialNeuralNetwork ann = parent.ann;

		if (ann == null) {
			return;
		}

		/*
		 * Calls a function to load the work area background color.
		 */
		selectBackgroundColor(g);

		/*
		 * Clear background.
		 */
		g.fillRect(0, 0, getWidth(), getHeight());

		/*
		 * Draw neurons connections between i and j neurons.
		 */
		g.setColor(connectionColor);
		for (int j = 0; j < ann.numberOfNeurons; j++) {
			for (int i = j + 1; i < ann.numberOfNeurons; i++) {

				/*
				 * Do not draw selected connection.
				 */
				if ((i == firstNeuronIndex && j == secondNeuronIndex)
						|| (j == firstNeuronIndex && i == secondNeuronIndex)) {
					continue;
				}

				/*
				 * Draw line between coordinates of two neurons.
				 */
				selectConnectionsColorByChosenMesh(i, j, g);
			}
		}

		/*
		 * Selected connection should be with different color.
		 */
		g.setColor(new Color(connectionColor.getRed(), connectionColor
				.getGreen(), connectionColor.getBlue(), SELECTION_ALPHA));
		for (int j = 0; j < ann.numberOfNeurons; j++) {
			for (int i = 0; i < ann.numberOfNeurons; i++) {
				if ((i == firstNeuronIndex && j == secondNeuronIndex)
						|| (j == firstNeuronIndex && i == secondNeuronIndex)) {
					/*
					 * Draw line between coordinates of two neurons of selected
					 * connection.
					 */
					g.drawLine(ann.coordinates[i][0], ann.coordinates[i][1],
							ann.coordinates[j][0], ann.coordinates[j][1]);
				}
			}
		}

		/*
		 * Set neuron types colors.
		 */
		regularNeuronColor = readNeuronColor(Util.REGULAR_NEURON_COLOR_PROPERTY_KEY);
		inputNeuronColor = readNeuronColor(Util.INPUT_NEURON_COLOR_PROPERTY_KEY);
		outputNeuronColor = readNeuronColor(Util.OUTPUT_NEURON_COLOR_PROPERTY_KEY);
		biasNeuronColor = readNeuronColor(Util.BIAS_NEURON_COLOR_PROPERTY_KEY);
		inputOutputNeuronColor = readNeuronColor(Util.INPUT_OUTPUT_NEURON_COLOR_PROPERTY_KEY);
		inputBiasNeuronColor = readNeuronColor(Util.INPUT_BIAS_NEURON_COLOR_PROPERTY_KEY);
		outputBiasNeuronColor = readNeuronColor(Util.OUTPUT_BIAS_NEURON_COLOR_PROPERTY_KEY);
		inputOutputBiasNeuronColor = readNeuronColor(Util.INPUT_OUTPUT_BIAS_NEURON_COLOR_PROPERTY_KEY);

		/*
		 * Draw neurons.
		 */
		Color neuronColor = null;
		for (int i = 0; i < ann.numberOfNeurons; i++) {
			/*
			 * Change color for different neurons type. It is possible neuron to
			 * have more than one flag up (example neuron which is input and
			 * output).
			 */
			switch (ann.flags[i]) {
			case (ArtificialNeuralNetwork.REGULAR_NEURON):
				neuronColor = regularNeuronColor;
				break;
			case (ArtificialNeuralNetwork.BIAS_NEURON):
				neuronColor = biasNeuronColor;
				break;
			case (ArtificialNeuralNetwork.INPUT_NEURON):
				neuronColor = inputNeuronColor;
				break;
			case (ArtificialNeuralNetwork.BIAS_NEURON | ArtificialNeuralNetwork.INPUT_NEURON):
				neuronColor = inputBiasNeuronColor;
				break;
			case (ArtificialNeuralNetwork.OUTPUT_NEURON):
				neuronColor = outputNeuronColor;
				break;
			case (ArtificialNeuralNetwork.BIAS_NEURON | ArtificialNeuralNetwork.OUTPUT_NEURON):
				neuronColor = outputBiasNeuronColor;
				break;
			case (ArtificialNeuralNetwork.INPUT_NEURON | ArtificialNeuralNetwork.OUTPUT_NEURON):
				neuronColor = inputOutputNeuronColor;
				break;
			case (ArtificialNeuralNetwork.BIAS_NEURON
					| ArtificialNeuralNetwork.INPUT_NEURON | ArtificialNeuralNetwork.OUTPUT_NEURON):
				neuronColor = inputOutputBiasNeuronColor;
				break;
			}

			/*
			 * Selected neuron should be with different color.
			 */
			if (i == firstNeuronIndex
					&& secondNeuronIndex == INDEX_NOT_SELECTED) {
				g.setColor(new Color(neuronColor.getRed(), neuronColor
						.getGreen(), neuronColor.getBlue(), SELECTION_ALPHA));
			} else {
				g.setColor(neuronColor);
			}

			/*
			 * Gets the neuron radius size.
			 */
			neuronRadius = calculateNeuronRadius();

			/*
			 * Draw circle on coordinates of neurons.
			 */
			g.fillOval(ann.coordinates[i][0] - neuronRadius,
					ann.coordinates[i][1] - neuronRadius, neuronRadius * 2,
					neuronRadius * 2);

			/*
			 * Shows the ID of each neuron on the screen.
			 */
			showNeuronNumbers(g, i, neuronColor, ann.coordinates[i][0] - 3,
					ann.coordinates[i][1] + 3);
		}
	}

	/**
	 * Calculates neurons radius.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 06 Dec 2011
	 */
	private int calculateNeuronRadius() {

		/**
		 * Default neuron radius.
		 */
		int neuronRadius = Math.min(VitoshaTradeApplet.CENTRAL_PANE_WIDTH,
				VitoshaTradeApplet.CENTRAL_PANE_HEIGHT) / 100;
		/**
		 * Default neuron radius size.
		 */
		String neuronRadiusSize = "Small";
		try {
			Properties p = new Properties();
			FileInputStream in = new FileInputStream(Util.PROPERTIES_FILE_NAME);
			p.load(in);
			neuronRadiusSize = p.getProperty("NeuronsSize");
			if (neuronRadiusSize.equals("Small")) {
				neuronRadius = Math.min(VitoshaTradeApplet.CENTRAL_PANE_WIDTH,
						VitoshaTradeApplet.CENTRAL_PANE_HEIGHT) / 100;
			} else if (neuronRadiusSize.equals("Medium")) {
				neuronRadius = Math.min(VitoshaTradeApplet.CENTRAL_PANE_WIDTH,
						VitoshaTradeApplet.CENTRAL_PANE_HEIGHT) / 80;
			} else if (neuronRadiusSize.equals("Large")) {
				neuronRadius = Math.min(VitoshaTradeApplet.CENTRAL_PANE_WIDTH,
						VitoshaTradeApplet.CENTRAL_PANE_HEIGHT) / 70;
			}

		} catch (Exception ex) {
			neuronRadius = Math.min(VitoshaTradeApplet.CENTRAL_PANE_WIDTH,
					VitoshaTradeApplet.CENTRAL_PANE_HEIGHT) / 100;
		}
		return (neuronRadius);
	}

	/**
	 * Reads the current color of the neuron from a file, depending on its type
	 * (flag).
	 * 
	 * @param colorProperty
	 *            The parameter name, containing the color.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 26 Oct 2011
	 * 
	 * @return The current color of the neuron.
	 */
	public Color readNeuronColor(String colorProperty) {
		Color neuronColor = new Color(0, 0, 0);
		try {
			Properties properties = new Properties();
			FileInputStream in = new FileInputStream(Util.PROPERTIES_FILE_NAME);
			properties.load(in);
			int color = Integer.parseInt(properties.getProperty(colorProperty));
			neuronColor = new Color(color);
		} catch (Exception ex) {
			neuronColor = new Color(Util.PRNG.nextInt(256),
					Util.PRNG.nextInt(256), Util.PRNG.nextInt(256));
		}
		return (neuronColor);
	}

	/**
	 * Draws the connection in a specific color depending on the chosen radio
	 * button in menu Tools->Mesh.
	 * 
	 * @param firstNeuronIndex
	 *            Index of the first neuron in the connection.
	 * 
	 * @param secondNeuronIndex
	 *            Index of the second neuron in the connection.
	 * 
	 * @param g
	 *            Graphic context.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 31 Oct 2011
	 */
	public void selectConnectionsColorByChosenMesh(int firstNeuronIndex,
			int secondNeuronIndex, Graphics g) {

		/*
		 * Takes minimum and maximum activity, weight and both activity and
		 * weight.
		 */
		double minActivity = parent.ann.activities[0][0];
		double maxActivity = parent.ann.activities[0][0];
		double minWeight = parent.ann.weights[0][0];
		double maxWeight = parent.ann.weights[0][0];
		double minActivityWeight = parent.ann.activities[0][0]
				* parent.ann.weights[0][0];
		double maxActivityWeight = parent.ann.activities[0][0]
				* parent.ann.weights[0][0];
		for (int j = 0; j < parent.ann.numberOfNeurons; j++) {
			for (int i = 0; i < parent.ann.numberOfNeurons; i++) {
				if (parent.ann.activities[i][j] < minActivity)
					minActivity = parent.ann.activities[i][j];
				if (parent.ann.activities[i][j] > maxActivity)
					maxActivity = parent.ann.activities[i][j];
				if (parent.ann.weights[i][j] < minWeight)
					minWeight = parent.ann.weights[i][j];
				if (parent.ann.weights[i][j] > maxWeight)
					maxWeight = parent.ann.weights[i][j];
				if (parent.ann.activities[i][j] * parent.ann.weights[i][j] < minActivityWeight)
					minActivityWeight = parent.ann.activities[i][j]
							* parent.ann.weights[i][j];
				if (parent.ann.activities[i][j] * parent.ann.weights[i][j] > maxActivityWeight)
					maxActivityWeight = parent.ann.activities[i][j]
							* parent.ann.weights[i][j];
			}
		}

		/*
		 * If option "Solid" is chosen in "Mesh" menu - all connections are in
		 * black color.
		 */
		if (parent.meshSolidItem.isSelected() == true) {
			g.drawLine(parent.ann.coordinates[firstNeuronIndex][0],
					parent.ann.coordinates[firstNeuronIndex][1],
					parent.ann.coordinates[secondNeuronIndex][0],
					parent.ann.coordinates[secondNeuronIndex][1]);

			/*
			 * If option "Activities" is chosen in "Mesh" menu - connections
			 * colors depend on their activities.
			 */
		} else if (parent.meshActivitiesItem.isSelected() == true) {
			connectionColorTemp = parent.ann.activities[firstNeuronIndex][secondNeuronIndex]
					- minActivity;
			connectionColorTemp = 255 - connectionColorTemp
					* (255 / (maxActivity - minActivity));
			int color = (int) Math.round(connectionColorTemp);
			g.setColor(new Color(color, color, color));

			if (parent.ann.activities[firstNeuronIndex][secondNeuronIndex] != 0.0) {
				g.drawLine(parent.ann.coordinates[firstNeuronIndex][0],
						parent.ann.coordinates[firstNeuronIndex][1],
						parent.ann.coordinates[secondNeuronIndex][0],
						parent.ann.coordinates[secondNeuronIndex][1]);
			}

			/*
			 * If option "Weights" is chosen in "Mesh" menu - connections colors
			 * depend on their weights.
			 */
		} else if (parent.meshWeightsItem.isSelected() == true) {
			connectionColorTemp = parent.ann.weights[firstNeuronIndex][secondNeuronIndex]
					- minWeight;
			connectionColorTemp = 255 - connectionColorTemp
					* (255 / (maxWeight - minWeight));
			int color = (int) Math.round(connectionColorTemp);
			g.setColor(new Color(color, color, color));
			g.drawLine(parent.ann.coordinates[firstNeuronIndex][0],
					parent.ann.coordinates[firstNeuronIndex][1],
					parent.ann.coordinates[secondNeuronIndex][0],
					parent.ann.coordinates[secondNeuronIndex][1]);

			/*
			 * If option "Both" is chosen in "Mesh" menu - connections colors
			 * depend on their activities and weights.
			 */
		} else if (parent.meshBothItem.isSelected() == true) {
			connectionColorTemp = parent.ann.activities[firstNeuronIndex][secondNeuronIndex]
					* parent.ann.weights[firstNeuronIndex][secondNeuronIndex]
					- minActivityWeight;
			connectionColorTemp = 255 - connectionColorTemp
					* (255 / (maxActivityWeight - minActivityWeight));
			int color = (int) Math.round(connectionColorTemp);
			g.setColor(new Color(color, color, color));
			g.drawLine(parent.ann.coordinates[firstNeuronIndex][0],
					parent.ann.coordinates[firstNeuronIndex][1],
					parent.ann.coordinates[secondNeuronIndex][0],
					parent.ann.coordinates[secondNeuronIndex][1]);
		}
	}

	/**
	 * Shows the IDs of the neurons on the screen.
	 * 
	 * @param g
	 *            Graphic context.
	 * 
	 * @param neuronId
	 *            Neuron ID shown on the screen.
	 * 
	 * @param neuronColor
	 *            The color of the neuron.
	 * 
	 * @param neuronIdXCoordinate
	 *            X-coordinate of the neuron ID.
	 * 
	 * @param neuronIdYCoordinate
	 *            Y-coordinate of the neuron ID.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 13 Nov 2011
	 */
	private void showNeuronNumbers(Graphics g, int neuronId, Color neuronColor,
			int neuronIdXCoordinate, int neuronIdYCoordinate) {
		if (parent.numberingItem.isSelected()) {

			/*
			 * Converts the neuron color to its opposite, so that the neuron ID
			 * stays visible inside the neuron.
			 */
			int convertedNeuronRedPrimaryColor = (neuronColor.getRed() ^ 0x80) & 0xff;
			int convertedNeuronGreenPrimaryColor = (neuronColor.getGreen() ^ 0x80) & 0xff;
			int convertedNeuronBluePrimaryColor = (neuronColor.getBlue() ^ 0x80) & 0xff;

			/*
			 * Reads the numbers size from a file. If the process fails, a
			 * default size is taken.
			 */
			int neuronIdFontSize = 9;
			try {
				Properties properties = new Properties();
				FileInputStream in = new FileInputStream(
						Util.PROPERTIES_FILE_NAME);
				properties.load(in);
				int currentNeuronsNumberSize = Integer.parseInt(properties
						.getProperty("NeuronsNumbersSize"));
				neuronIdFontSize = currentNeuronsNumberSize;
			} catch (Exception ex) {
			}

			/*
			 * Creates a new font for the neuron IDs.
			 */
			String neuronIdFontFamily = "Verdana";
			Font neuronIdFont = new Font(neuronIdFontFamily, Font.BOLD,
					neuronIdFontSize);
			Color neuronIdColor = new Color(convertedNeuronRedPrimaryColor,
					convertedNeuronGreenPrimaryColor,
					convertedNeuronBluePrimaryColor);

			/*
			 * Sets font and color of the neuron ID and draws it inside the
			 * neuron oval.
			 */
			g.setColor(neuronIdColor);
			g.setFont(neuronIdFont);
			g.drawString(Integer.toString(neuronId), neuronIdXCoordinate,
					neuronIdYCoordinate);
		}
	}

	/**
	 * Reads the work area background color.
	 * 
	 * @param g
	 *            Graphic context.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 23 Nov 2011
	 */
	private void selectBackgroundColor(Graphics g) {
		try {
			Properties properties = new Properties();
			FileInputStream in = new FileInputStream(Util.PROPERTIES_FILE_NAME);
			properties.load(in);
			int color = Integer.parseInt(properties
					.getProperty(Util.WORK_AREA_BACKGROUND_COLOR_PROPERTY_KEY));
			g.setColor(new Color(color));
		} catch (Exception ex) {
			g.setColor(new Color(255, 255, 255));
		}
	}
}
