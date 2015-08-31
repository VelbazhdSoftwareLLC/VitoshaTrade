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
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JComboBox;

/**
 * Panel with GUI controls for Neural Network Management.
 * 
 * @author Momchil Anachkov
 * 
 * @email mZer0000@gmail.com
 * 
 * @date 18 Nov 2010
 */
class NetworkPane extends JPanel {

	/**
	 * Determines what filter should be applied when symbol and/or period are
	 * changed.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 30 Oct 2011
	 */
	private class SetFiltersBySimbolAndPeriod implements ItemListener {

		/**
		 * Calls functions to apply different filters depending on the chosen
		 * values in the drop down menus for currency pair and period.
		 * 
		 * @author Ralitza Koleva
		 * 
		 * @email rallly@abv.bg
		 * 
		 * @date 30 Oct 2011
		 */
		public void itemStateChanged(ItemEvent event) {

			/*
			 * If neither symbol, nor period is chosen, all ANN IDs are shown in
			 * the ANN ID JComboBox.
			 */
			if ((networkSymbol.getItemCount() == 0 || "---"
					.equals(networkSymbol.getSelectedItem()) == true)
					&& (networkPeriod.getItemCount() == 0 || "---"
							.equals(networkPeriod.getSelectedItem()) == true)) {

				/*
				 * Loads all ANN IDs.
				 */
				setAllAnnIds();
			}

			/*
			 * If both symbol and period are chosen, only corresponding ANN IDs
			 * are shown in the ANN ID JComboBox.
			 */
			else if ((networkSymbol.getItemCount() > 0 && "---"
					.equals(networkSymbol.getSelectedItem()) == false)
					&& (networkPeriod.getItemCount() > 0 && "---"
							.equals(networkPeriod.getSelectedItem()) == false)) {

				/*
				 * Loads ANN IDs depending on the chosen symbol and period.
				 */
				try {
					setFilteredAnnIdsBySymbolAndPeriod();
				} catch (Exception e) {
					// TODO: handle exception
				}

				/*
				 * If only symbol is chosen, only corresponding ANN IDs are
				 * shown in the ANN ID JComboBox.
				 */
			} else if ((networkSymbol.getItemCount() > 0 && "---"
					.equals(networkSymbol.getSelectedItem()) == false)
					&& (networkPeriod.getItemCount() > 0 && "---"
							.equals(networkPeriod.getSelectedItem()) == true)) {

				/*
				 * Loads ANN IDs depending on the chosen symbol.
				 */
				try {
					setFilteredAnnIdsBySymbol();
				} catch (Exception e) {
					// TODO: handle exception
				}

				/*
				 * If only period is chosen, only corresponding ANN IDs are
				 * shown in the ANN ID JComboBox.
				 */
			} else if ((networkSymbol.getItemCount() > 0 && "---"
					.equals(networkSymbol.getSelectedItem()) == true)
					&& (networkPeriod.getItemCount() > 0 && "---"
							.equals(networkPeriod.getSelectedItem()) == false)) {

				/*
				 * Load ANN IDs depending on the chosen period.
				 */
				try {
					setFilteredAnnIdsByPeriod();
				} catch (Exception e) {
					// TODO: handle exception
				}
			}
		}

		/**
		 * Shows all ANN IDs in the ANN ID JComboBox.
		 * 
		 * @author Ralitza Koleva
		 * 
		 * @email rallly@abv.bg
		 * 
		 * @date 29 Oct 2011
		 */
		public void setAllAnnIds() {
			String listIds[][] = parent.dbHelp.loadAnnList();
			networkId.removeAllItems();
			networkId.addItem("---");
			for (int i = 0; i < listIds.length; i++) {
				networkId.addItem(listIds[i][2]);
			}
		}

		/**
		 * Shows ANN IDs in the ANN ID JComboBox filtered by symbol and period.
		 * 
		 * @author Ralitza Koleva
		 * 
		 * @email rallly@abv.bg
		 * 
		 * @date 29 Oct 2011
		 */
		public void setFilteredAnnIdsBySymbolAndPeriod() {
			String selectedSymbol = networkSymbol.getSelectedItem().toString();
			int selectedPeriod = ((SymbolPeriodKeyValue) networkPeriod
					.getSelectedItem()).getKey();
			networkId.removeAllItems();
			networkId.addItem("---");
			String listFilteredId[][] = parent.dbHelp.loadAnnList(
					selectedSymbol, selectedPeriod);
			try {
				for (int i = 0; i < listFilteredId.length; i++) {
					networkId.addItem(listFilteredId[i][2]);
				}
			} catch (Exception e) {

			}
		}

		/**
		 * Shows ANN IDs in the ANN ID JComboBox filtered by period.
		 * 
		 * @author Ralitza Koleva
		 * 
		 * @email rallly@abv.bg
		 * 
		 * @date 29 Oct 2011
		 */
		public void setFilteredAnnIdsByPeriod() {
			int selectedPeriod = ((SymbolPeriodKeyValue) networkPeriod
					.getSelectedItem()).getKey();
			networkId.removeAllItems();
			networkId.addItem("---");
			String listFilteredId[][] = parent.dbHelp
					.loadAnnListByPeriod(selectedPeriod);
			try {
				for (int i = 0; i < listFilteredId.length; i++) {
					networkId.addItem(listFilteredId[i][2]);
				}
			} catch (Exception e) {

			}
		}

		/**
		 * Shows ANN IDs in the ANN ID JComboBox filtered by symbol.
		 * 
		 * @author Ralitza Koleva
		 * 
		 * @email rallly@abv.bg
		 * 
		 * @date 29 Oct 2011
		 */
		public void setFilteredAnnIdsBySymbol() {
			String selectedSymbol = networkSymbol.getSelectedItem().toString();
			networkId.removeAllItems();
			networkId.addItem("---");
			String listFilteredId[][] = parent.dbHelp
					.loadAnnListBySymbol(selectedSymbol);
			try {
				for (int i = 0; i < listFilteredId.length; i++) {
					networkId.addItem(listFilteredId[i][2]);
				}
			} catch (Exception e) {

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
	 * GUI control for obtaining and selecting network symbol.
	 */
	private JComboBox networkSymbol = new JComboBox();

	/**
	 * GUI control for obtaining and selecting network period.
	 */
	private JComboBox networkPeriod = new JComboBox();

	/**
	 * GUI control for obtaining and selecting network ID.
	 */
	private JComboBox networkId = new JComboBox();

	/**
	 * GUI control for loading a selected network.
	 */
	private JButton load = new JButton();

	/**
	 * GUI control for saving a selected network.
	 */
	private JButton save = new JButton();

	/**
	 * GUI control for rearrange neurons.
	 */
	private JButton rearrange = new JButton();

	/**
	 * GUI control for updating ANN server information.
	 */
	private JButton refresh = new JButton();

	/**
	 * Constructing network pane.
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
	public NetworkPane(final VitoshaTradeApplet parent) {
		this.parent = parent;
		this.setPreferredSize(new Dimension(VitoshaTradeApplet.EAST_PANE_WIDTH,
				VitoshaTradeApplet.EAST_PANE_HEIGHT));

		setLayout(new GridLayout(25, 1));

		add(new JLabel(Texts.LABEL_SYMBOL));
		add(networkSymbol);
		networkSymbol.setEditable(false);
		networkSymbol.addItemListener(new SetFiltersBySimbolAndPeriod());

		add(new JLabel(Texts.LABEL_PERIOD));
		add(networkPeriod);
		networkPeriod.setEditable(false);
		networkPeriod.addItemListener(new SetFiltersBySimbolAndPeriod());

		add(new JLabel(Texts.LABEL_ANN_ID));
		add(networkId);
		networkId.setEditable(false);

		/*
		 * Acts as separator.
		 */
		add(new JLabel());

		add(load);
		load.setText(Texts.LABEL_BUTTON_LOAD);
		load.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					int ann_id = Integer.parseInt((String) networkId
							.getSelectedItem());
					parent.ann = parent.dbHelp.loadAnn(ann_id);
					parent.workArea.repaint();
				} catch (Exception ex) {
					showInformationMessage();
				}
			}
		});

		add(save);
		save.setText(Texts.LABEL_BUTTON_SAVE);
		save.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					parent.dbHelp.saveAnn(parent.ann);
				} catch (Exception ex) {
					showInformationMessage();
				}
			}
		});

		/*
		 * Acts as separator.
		 */
		add(new JLabel());

		add(rearrange);
		rearrange.setText(Texts.LABEL_BUTTON_REARRANGE);
		rearrange.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				if (parent == null) {
					return;
				}
				if (parent.ann == null) {
					return;
				}
				if (parent.ann.flags == null) {
					return;
				}

				int width = parent.workArea.getWidth();
				int height = parent.workArea.getHeight();

				int idy = height / (parent.ann.numberOfInputNeurons() + 2);
				int hdy = height / (parent.ann.numberOfHiddenNeurons() + 2);
				int ody = height / (parent.ann.numberOfOutputNeurons() + 2);

				for (int k = 0, i = idy, h = hdy, o = ody; k < parent.ann.flags.length; k++) {
					if (parent.ann.flags[k] == ArtificialNeuralNetwork.INPUT_NEURON) {
						parent.ann.coordinates[k][0] = 20;
						parent.ann.coordinates[k][1] = i;
						i += idy;
					}
					if (parent.ann.flags[k] == ArtificialNeuralNetwork.REGULAR_NEURON) {
						parent.ann.coordinates[k][0] = width / 2;
						parent.ann.coordinates[k][1] = h;
						h += hdy;
					}
					if (parent.ann.flags[k] == ArtificialNeuralNetwork.OUTPUT_NEURON) {
						parent.ann.coordinates[k][0] = width - 20;
						parent.ann.coordinates[k][1] = o;
						o += ody;
					}
				}
			}
		});

		/*
		 * Acts as separator.
		 */
		add(new JLabel());

		add(refresh);
		refresh.setText(Texts.LABEL_BUTTON_REFRESH);
		refresh.doClick(10000);
		refresh.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String listSymbol[][] = parent.dbHelp.loadCurrencyPairs();
				String listPeriod[][] = parent.dbHelp.loadPeriods();
				String listIds[][] = parent.dbHelp.loadAnnList();
				if (listSymbol == null || listPeriod == null || listIds == null) {
					return;
				}

				networkSymbol.removeAllItems();
				networkPeriod.removeAllItems();
				networkSymbol.addItem("---");
				networkPeriod.addItem("---");

				/*
				 * Loads a drop down menu with symbols.
				 */
				for (int i = 0; i < listSymbol.length; i++) {
					networkSymbol.addItem(listSymbol[i][0]);
				}

				/*
				 * Loads a drop down menu with periods.
				 */
				for (int i = 0; i < listPeriod.length; i++) {
					networkPeriod.addItem(new SymbolPeriodKeyValue(
							listPeriod[i][0], listPeriod[i][1]));
				}
			}
		});
	}

	/**
	 * Shows a message if no ANN ID is selected to load/save.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 05 Dec 2011
	 */
	private void showInformationMessage() {
		InformationMessages error = new InformationMessages(
				Texts.INFORMATION_SELECT_ANN_ID,
				Texts.INFORMATION_SELECT_ANN_ID_TITLE,
				JOptionPane.INFORMATION_MESSAGE);
		error.showMessage();
	}
}
