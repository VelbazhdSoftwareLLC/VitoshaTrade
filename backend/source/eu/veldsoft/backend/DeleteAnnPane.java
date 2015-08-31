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

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JComboBox;

/**
 * Panel with GUI controls for Neural Network Management.
 * 
 * @author Ralitza Koleva
 * 
 * @email rallly@abv.bg
 * 
 * @date 27 Nov 2010
 */
class DeleteAnnPane extends JPanel {

	/**
	 * Default serial version UID.
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * Parent applet reference.
	 */
	private VitoshaTradeApplet parent = null;

	/**
	 * GUI control for obtaining and selecting network ID.
	 */
	private JComboBox networkId = new JComboBox();

	/**
	 * GUI control for deleting a selected network.
	 */
	private JButton delete = new JButton();

	/**
	 * GUI control for updating ANN server information.
	 */
	private JButton refresh = new JButton();

	/**
	 * Constructing delete ANN pane.
	 * 
	 * @param parent
	 *            The parent class.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 27 Nov 2011
	 */
	public DeleteAnnPane(final VitoshaTradeApplet parent) {
		this.parent = parent;
		this.setPreferredSize(new Dimension(VitoshaTradeApplet.EAST_PANE_WIDTH,
				VitoshaTradeApplet.EAST_PANE_HEIGHT));

		setLayout(new GridLayout(25, 1));

		add(new JLabel(Texts.LABEL_ANN_ID));
		add(networkId);
		networkId.setEditable(false);

		/*
		 * Acts as separator.
		 */
		add(new JLabel());

		add(delete);
		delete.setText(Texts.LABEL_BUTTON_DELETE);
		delete.addActionListener(new ActionListener() {

			/**
			 * Deletes all ANN information.
			 * 
			 * @author Ralitza Koleva
			 * 
			 * @email rallly@abv.bg
			 * 
			 * @date 27 Nov 2011
			 */
			public void actionPerformed(ActionEvent event) {
				try {
					int ann_id = Integer.parseInt((String) networkId
							.getSelectedItem());
					parent.dbHelp.deleteAnn(ann_id);
					loadAllAnnIds();
					parent.workArea.repaint();
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
			 * Refreshes ANN IDs in the ANN ID JComboBox.
			 * 
			 * @author Ralitza Koleva
			 * 
			 * @email rallly@abv.bg
			 * 
			 * @date 27 Nov 2011
			 */
			public void actionPerformed(ActionEvent event) {
				loadAllAnnIds();
			}
		});
	}

	/**
	 * Loads all ANN IDs in the ANN ID JComboBox.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 29 Oct 2011
	 */
	public void loadAllAnnIds() {
		String listIds[][] = parent.dbHelp.loadAnnList();
		networkId.removeAllItems();
		networkId.addItem("---");
		for (int i = 0; i < listIds.length; i++) {
			networkId.addItem(listIds[i][2]);
		}
	}

	/**
	 * Shows a message if no ANN ID is selected to delete.
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
