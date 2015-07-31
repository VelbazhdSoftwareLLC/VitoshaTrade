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
import javax.swing.JTextField;

/**
 * Panel with GUI controls for Connection Management.
 *
 * @author Momchil Anachkov
 *
 * @email mZer0000@gmail.com
 *
 * @date 18 Nov 2010
 */
public class ConnectionPane extends JPanel {
	/**
	 * Default serial version UID.
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * Parent applet reference.
	 */
	private VitoshaTradeApplet parent = null;

	/**
	 * GUI control for obtaining the source neuron for a specific connection.
	 */
	private JTextField neuronSource = new JTextField();

	/**
	 * GUI control for obtaining the neuron-recipient for a specific connection.
	 */
	private JTextField neuronDestination = new JTextField();

	/**
	 * GUI control for obtaining and setting the activity for a specific
	 * connection.
	 */
	private JTextField activity = new JTextField();

	/**
	 * GUI control for obtaining the weight for a specific connection.
	 */
	private JTextField weight = new JTextField();

	/**
	 * Constructing connection pane.
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
	public ConnectionPane(final VitoshaTradeApplet parent) {
		this.parent = parent;
		this.setPreferredSize(new Dimension(VitoshaTradeApplet.EAST_PANE_WIDTH,
											VitoshaTradeApplet.EAST_PANE_HEIGHT));

		setLayout(new GridLayout(25, 1));

		add(new JLabel(Texts.LABEL_SOURCE));
		add(neuronSource);
		neuronSource.setEditable(false);

		add(new JLabel(Texts.LABEL_DESTINATION));
		add(neuronDestination);
		neuronDestination.setEditable(false);

		add(new JLabel(Texts.LABEL_WEIGHT));
		add(weight);

		add(new JLabel(Texts.LABEL_ACTIVITY));
		add(activity);

		weight.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent å) {
				parent.ann.weights[Integer.parseInt(neuronSource.getText())][Integer
						.parseInt(neuronDestination.getText())] = Double
								.parseDouble(weight.getText());
				parent.workArea.repaint();
			}
		});

		activity.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent å) {
				parent.ann.activities[Integer.parseInt(neuronSource.getText())][Integer
						.parseInt(neuronDestination.getText())] = Double
								.parseDouble(activity.getText());
				parent.workArea.repaint();
			}
		});
	}

	/**
	 * Loading connection properties.
	 *
	 * @param sourceIndex
	 *            Source neuron of selected connection.
	 *
	 * @param destinationIndex
	 *            Destination neuron of selected connection.
	 *
	 * @param connectionActivity
	 *            Activity of selected connection.
	 *
	 * @param connectionWeight
	 *            Weight of selected connection.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 01 Feb 2010
	 */
	void setValues(int sourceIndex, int destinationIndex,
				   double connectionActivity, double connectionWeight) {
		neuronSource.setText("" + sourceIndex);
		neuronDestination.setText("" + destinationIndex);
		activity.setText("" + connectionActivity);
		weight.setText("" + connectionWeight);
	}
}
