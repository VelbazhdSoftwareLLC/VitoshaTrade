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
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

/**
 * Panel with GUI controls for a new ANN management.
 * 
 * @author Ralitza Koleva
 * 
 * @email rallly@abv.bg
 * 
 * @date 18 Sep 2011
 */
public class NewAnnPane extends JPanel {

	/**
	 * Default serial version UID.
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * Parent applet reference.
	 */
	private VitoshaTradeApplet parent = null;

	/**
	 * GUI control for obtaining the ANN kind (shows symbols).
	 */
	private JComboBox networkSymbol = new JComboBox();

	/**
	 * GUI control for obtaining the ANN kind (shows period).
	 */
	private JComboBox networkPeriod = new JComboBox();

	/**
	 * GUI control for number of neurons.
	 */
	private JTextField networkNumberNeurons = new JTextField();

	/**
	 * GUI control for updating ANN server information.
	 */
	private JButton refresh = new JButton();

	/**
	 * GUI control for saving a new network.
	 */
	private JButton save = new JButton();

	/**
	 * Constructing new ANN pane.
	 * 
	 * @param parent
	 *            The parent class.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 18 Sep 2011
	 */
	public NewAnnPane(final VitoshaTradeApplet parent) {
		this.parent = parent;
		this.setPreferredSize(new Dimension(VitoshaTradeApplet.EAST_PANE_WIDTH,
				VitoshaTradeApplet.EAST_PANE_HEIGHT));

		setLayout(new GridLayout(25, 1));

		add(new JLabel(Texts.LABEL_SYMBOL));
		add(networkSymbol);
		networkSymbol.setEditable(false);

		add(new JLabel(Texts.LABEL_PERIOD));
		add(networkPeriod);
		networkPeriod.setEditable(false);

		add(new JLabel(Texts.LABEL_NUMBER_NEURONS));
		add(networkNumberNeurons);

		/*
		 * Deletes all tokens different from numbers. Only numbers are allowed
		 * in the field for inputting the number of neurons in the ANN.
		 */
		networkNumberNeurons.addKeyListener(new KeyAdapter() {
			/**
			 * Deletes all tokens different from numbers typed by the user.
			 * 
			 * @author Ralitza Koleva
			 * 
			 * @email rallly@abv.bg
			 * 
			 * @date 17 Oct 2011
			 */
			public void keyTyped(KeyEvent event) {
				char c = event.getKeyChar();
				if ((c < '0') || (c > '9') || (c == KeyEvent.VK_BACK_SPACE)
						|| (c == KeyEvent.VK_DELETE)) {
					getToolkit().beep();
					event.consume();
				}
			}
		});

		/*
		 * Acts as separator.
		 */
		add(new JLabel());

		add(save);
		save.setText(Texts.LABEL_BUTTON_SAVE);
		save.addActionListener(new ActionListener() {

			/**
			 * Prepares a new ANN for saving and calls a function to save it.
			 * 
			 * @author Ralitza Koleva
			 * 
			 * @email rallly@abv.bg
			 * 
			 * @date 18 Sep 2011
			 */
			public void actionPerformed(ActionEvent event) {
				try {
					/*
					 * Gets the selected currency pair (symbol) ID of the new
					 * ANN.
					 */
					String selectedSymbol = networkSymbol.getSelectedItem()
							.toString();

					/*
					 * Gets the selected period ID of the new ANN.
					 */
					int selectedPeriod = ((SymbolPeriodKeyValue) networkPeriod
							.getSelectedItem()).getKey();

					/*
					 * Gets the input number of neurons of the new ANN.
					 */
					String networkNumberNeuronsStr = networkNumberNeurons
							.getText();
					int networkNumberNeurons = Integer
							.parseInt(networkNumberNeuronsStr);

					/*
					 * Prepares the default weights, fitness and flags of the
					 * new ANN.
					 */
					String networkWeights = "";
					int networkFitness = 0;
					String networkFlags = "";
					for (int i = 0; i < networkNumberNeurons; i++) {
						networkFlags = networkFlags + "0" + " ";
						for (int j = 0; j < networkNumberNeurons; j++) {
							networkWeights = networkWeights + "1.0" + " ";
						}
					}

					/*
					 * Calls a function for saving the new ANN.
					 */
					int newAnn = parent.dbHelp.saveNewAnn(selectedSymbol,
							selectedPeriod, networkNumberNeurons,
							networkWeights, networkFitness, networkFlags);

					/*
					 * Loads the new ANN in the work area.
					 */
					parent.ann = parent.dbHelp.loadAnn(newAnn);
					parent.workArea.repaint();

					/*
					 * Shows the screen for loading an ANN.
					 */
					parent.showNetworkPane();
				} catch (Exception ex) {
					showInformationMessage();
				}
			}
		});

		/*
		 * Acts as separator.
		 */
		add(new JLabel());

		add(refresh);
		refresh.setText(Texts.LABEL_BUTTON_REFRESH);
		refresh.addActionListener(new ActionListener() {

			/**
			 * Updates ANN server information in the symbol and period
			 * JComboBoxes.
			 * 
			 * @author Ralitza Koleva
			 * 
			 * @email rallly@abv.bg
			 * 
			 * @date 18 Sep 2011
			 */
			public void actionPerformed(ActionEvent event) {
				String listCurrencyPairs[][] = parent.dbHelp
						.loadCurrencyPairs();
				if (listCurrencyPairs == null) {
					return;
				}

				/*
				 * Updates symbols JComboBox items.
				 */
				networkSymbol.removeAllItems();
				for (int i = 0; i < listCurrencyPairs.length; i++) {
					networkSymbol.addItem(listCurrencyPairs[i][0]);
				}

				String listPeriods[][] = parent.dbHelp.loadPeriods();
				if (listPeriods == null) {
					return;
				}

				/*
				 * Updates periods JComboBox items.
				 */
				networkPeriod.removeAllItems();
				for (int i = 0; i < listPeriods.length; i++) {
					networkPeriod.addItem(new SymbolPeriodKeyValue(
							listPeriods[i][0], listPeriods[i][1]));
				}
			}
		});
	}

	/**
	 * Shows a message if no symbol/period is selected to save the new ANN.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 05 Dec 2011
	 */
	private void showInformationMessage() {
		InformationMessages error = new InformationMessages(
				Texts.INFORMATION_SELECT_SYMBOL_AND_PERIOD,
				Texts.INFORMATION_SELECT_SYMBOL_AND_PERIOD_TITLE,
				JOptionPane.INFORMATION_MESSAGE);
		error.showMessage();
	}
}
