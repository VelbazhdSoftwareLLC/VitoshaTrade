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

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.ButtonGroup;
import javax.swing.JCheckBoxMenuItem;
import javax.swing.JMenu;
import javax.swing.JApplet;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JRadioButtonMenuItem;

/**
 * VitoshaTrade backend applet class.
 *
 * @author Momchil Anachkov, Ralitza Koleva
 *
 * @email mZer0000@gmail.com
 *
 * @date 11 Nov 2010
 */
public class VitoshaTradeApplet extends JApplet {
	/**
	 * Constant integer referring to applet width.
	 */
	// TODO Get parameters from HTML file.
	public static int WIDTH = 800;

	/**
	 * Constant integer referring to applet height.
	 */
	// TODO Get parameters from HTML file.
	public static int HEIGHT = 600;

	/**
	 * Constant integer referring to central pane height.
	 */
	public static int CENTRAL_PANE_HEIGHT = 600;

	/**
	 * Constant integer referring to central pane width.
	 */
	public static int CENTRAL_PANE_WIDTH = 670;

	/**
	 * Constant integer referring to east pane height.
	 */
	public static int EAST_PANE_WIDTH = 130;

	/**
	 * Constant integer referring to east pane width.
	 */
	public static int EAST_PANE_HEIGHT = 600;

	/**
	 * Default serial version UID.
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * Database helping class.
	 */
	DatabaseHelper dbHelp = new DatabaseHelper();

	/**
	 * Applet menu bar.
	 */
	private JMenuBar menuBar = new JMenuBar();

	/**
	 * Applet menu bar item.
	 */
	private JMenu commandsMenu = new JMenu(Texts.MENU_COMMANDS);

	/**
	 * Applet menu bar item.
	 */
	private JMenuItem loginItem = new JMenuItem(Texts.MENU_ITEM_LOGIN);

	/**
	 * Applet menu bar item.
	 */
	private JMenuItem logoutItem = new JMenuItem(Texts.MENU_ITEM_LOGOUT);

	/**
	 * Applet menu bar item.
	 */
	private JMenu networkMenu = new JMenu(Texts.MENU_NETWORK);

	/**
	 * Applet menu bar item.
	 */
	private JMenuItem newNetworkItem = new JMenuItem(Texts.MENU_ITEM_NEW);

	/**
	 * Applet menu bar item.
	 */
	private JMenuItem loadNetworkItem = new JMenuItem(Texts.MENU_ITEM_LOAD);

	/**
	 * Applet menu bar item.
	 */
	private JMenuItem deleteNetworkItem = new JMenuItem(Texts.MENU_ITEM_DELETE);

	/**
	 * Applet menu bar item.
	 */
	private JMenu toolsMenu = new JMenu(Texts.MENU_TOOLS);

	/**
	 * Applet menu bar item.
	 */
	private JMenuItem settingsItem = new JMenuItem(Texts.MENU_ITEM_SETTINGS);

	/**
	 * Applet menu item.
	 */
	private JMenu meshMenu = new JMenu(Texts.MENU_MESH);

	/**
	 * Applet menu bar item.
	 */
	public JRadioButtonMenuItem meshActivitiesItem = new JRadioButtonMenuItem(
		Texts.MENU_ITEM_ACTIVITIES);

	/**
	 * Applet menu bar item.
	 */
	public JRadioButtonMenuItem meshWeightsItem = new JRadioButtonMenuItem(
		Texts.MENU_ITEM_WEIGHTS);

	/**
	 * Applet menu bar item.
	 */
	public JRadioButtonMenuItem meshBothItem = new JRadioButtonMenuItem(
		Texts.MENU_ITEM_BOTH);

	/**
	 * Applet menu bar item.
	 */
	public JRadioButtonMenuItem meshSolidItem = new JRadioButtonMenuItem(
		Texts.MENU_ITEM_SOLID);

	/**
	 * Applet menu bar item.
	 */
	private ButtonGroup meshItemsGroup = new ButtonGroup();

	/**
	 * Applet menu bar item.
	 */
	public JCheckBoxMenuItem numberingItem = new JCheckBoxMenuItem(
		Texts.MENU_ITEM_NUMBERING);

	/**
	 * Working area controls. It is default access to able to repaint from other
	 * classes.
	 */
	DrawingPane workArea = new DrawingPane(this);

	/**
	 * Login pane controls.
	 */
	private LoginPane loginPane = new LoginPane(this);

	/**
	 * Neuron pane controls.
	 */
	public NeuronPane neuronPane = new NeuronPane(this);

	/**
	 * New ANN pane controls.
	 */
	public NewAnnPane newAnnPane = new NewAnnPane(this);

	/**
	 * Delete ANN pane controls.
	 */
	public DeleteAnnPane deleteAnnPane = new DeleteAnnPane(this);

	/**
	 * Settings pane controls.
	 */
	public SettingsPane settingsPane = new SettingsPane(this);

	/**
	 * Connection pane controls. Default access is used for GUI controls
	 * modification from other classes.
	 */
	ConnectionPane connectionPane = new ConnectionPane(this);

	/**
	 * Network pane controls.
	 */
	private NetworkPane networkPane = new NetworkPane(this);

	/**
	 * ANN container.
	 */
	ArtificialNeuralNetwork ann = null;

	/**
	 * Applet initialization.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 16 Nov 2010
	 */
	public void init() {
		setSize(WIDTH, HEIGHT);

		setLayout(new BorderLayout());

		setJMenuBar(menuBar);
		menuBar.add(commandsMenu);
		commandsMenu.add(loginItem);
		commandsMenu.add(logoutItem);

		add(workArea, BorderLayout.WEST);

		setJMenuBar(menuBar);
		menuBar.add(commandsMenu);
		commandsMenu.add(loginItem);
		loginItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				showLoginPane();
				loginItem.setEnabled(false);
				logoutItem.setEnabled(true);
			}
		});
		logoutItem.setEnabled(false);
		commandsMenu.add(logoutItem);
		logoutItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					dbHelp.disconnect();
				} catch (Exception ex) {
				}
				showLoginPane();
				loginItem.setEnabled(true);
				logoutItem.setEnabled(false);
				hideMenuBarAfterLogout();
			}
		});

		newNetworkItem.addActionListener(new ActionListener() {

			/**
			 * Shows a pane for creating a new ANN.
			 *
			 * @author Ralitza Koleva
			 *
			 * @email rallly@abv.bg
			 *
			 * @date 18 Sep 2011
			 */
			public void actionPerformed(ActionEvent event) {
				showNewAnnPane();
			}
		});

		loadNetworkItem.addActionListener(new ActionListener() {

			/**
			 * Shows a pane for loading an existing ANN.
			 *
			 * @author Ralitza Koleva
			 *
			 * @email rallly@abv.bg
			 *
			 * @date 18 Sep 2011
			 */
			public void actionPerformed(ActionEvent event) {
				showNetworkPane();

			}
		});

		deleteNetworkItem.addActionListener(new ActionListener() {

			/**
			 * Shows a pane for deleting an existing ANN.
			 *
			 * @author Ralitza Koleva
			 *
			 * @email rallly@abv.bg
			 *
			 * @date 27 Nov 2011
			 */
			public void actionPerformed(ActionEvent event) {
				showDeleteAnnPane();

			}
		});

		settingsItem.addActionListener(new ActionListener() {

			/**
			 * Shows a settings pane for changing ANN kinds colors.
			 *
			 * @author Ralitza Koleva
			 *
			 * @email rallly@abv.bg
			 *
			 * @date 21 Oct 2011
			 */
			public void actionPerformed(ActionEvent event) {
				showSettingsPane();

			}
		});

		/*
		 * When selected, this radio button menu item determines that ANN
		 * connections should be colored depending on ANN activities.
		 */
		meshActivitiesItem.addActionListener(new ActionListener() {

			/**
			 * Repaints work area.
			 *
			 * @author Ralitza Koleva
			 *
			 * @email rallly@abv.bg
			 *
			 * @date 31 Oct 2011
			 */
			public void actionPerformed(ActionEvent event) {
				workArea.repaint();
			}
		});

		/*
		 * When selected, this radio button menu item determines that ANN
		 * connections should be colored depending on ANN weights.
		 */
		meshWeightsItem.addActionListener(new ActionListener() {

			/**
			 * Repaints work area.
			 *
			 * @author Ralitza Koleva
			 *
			 * @email rallly@abv.bg
			 *
			 * @date 31 Oct 2011
			 */
			public void actionPerformed(ActionEvent event) {
				workArea.repaint();
			}
		});

		/*
		 * When selected, this radio button menu item determines that ANN
		 * connections should be colored depending on both ANN activities and
		 * weights.
		 */
		meshBothItem.addActionListener(new ActionListener() {

			/**
			 * Repaints work area.
			 *
			 * @author Ralitza Koleva
			 *
			 * @email rallly@abv.bg
			 *
			 * @date 31 Oct 2011
			 */
			public void actionPerformed(ActionEvent event) {
				workArea.repaint();
			}
		});

		/*
		 * When selected, this radio button menu item determines that ANN
		 * connections should be colored in a solid color, regardless of ANN
		 * activities and weights.
		 */
		meshSolidItem.addActionListener(new ActionListener() {

			/**
			 * Repaints work area.
			 *
			 * @author Ralitza Koleva
			 *
			 * @email rallly@abv.bg
			 *
			 * @date 31 Oct 2011
			 */
			public void actionPerformed(ActionEvent event) {
				workArea.repaint();
			}
		});

		/*
		 * When selected, this checkbox menu item determines that ANN neurons
		 * should be numbered.
		 */
		numberingItem.addActionListener(new ActionListener() {

			/**
			 * Repaints work area.
			 *
			 * @author Ralitza Koleva
			 *
			 * @email rallly@abv.bg
			 *
			 * @date 31 Oct 2011
			 */
			public void actionPerformed(ActionEvent event) {
				workArea.repaint();
			}
		});
	}

	/**
	 * Visualizing network pane.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 27 Dec 2010
	 */
	public void showNetworkPane() {
		remove(loginPane);
		remove(neuronPane);
		remove(connectionPane);
		remove(newAnnPane);
		remove(deleteAnnPane);
		remove(settingsPane);
		add(networkPane, BorderLayout.EAST);
		networkPane.revalidate();
		workArea.setVisible(true);
		repaint();
		showMenuBarAfterLogin();
	}

	/**
	 * Visualizing login pane.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 27 Dec 2010
	 */
	public void showLoginPane() {
		remove(networkPane);
		remove(neuronPane);
		remove(connectionPane);
		remove(newAnnPane);
		remove(deleteAnnPane);
		remove(settingsPane);
		add(loginPane, BorderLayout.EAST);
		loginPane.revalidate();
		workArea.setVisible(true);
		repaint();
	}

	/**
	 * Visualizing neuron pane.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 27 Dec 2010
	 */
	public void showNeuronPane() {
		remove(networkPane);
		remove(loginPane);
		remove(connectionPane);
		remove(newAnnPane);
		remove(deleteAnnPane);
		remove(settingsPane);
		add(neuronPane, BorderLayout.EAST);
		neuronPane.revalidate();
		workArea.setVisible(true);
		repaint();
	}

	/**
	 * Visualizing connection pane.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 27 Dec 2010
	 */
	public void showConnectionPane() {
		remove(networkPane);
		remove(loginPane);
		remove(neuronPane);
		remove(newAnnPane);
		remove(deleteAnnPane);
		remove(settingsPane);
		add(connectionPane, BorderLayout.EAST);
		connectionPane.revalidate();
		workArea.setVisible(true);
		repaint();
	}

	/**
	 * Visualizing new ANN pane.
	 *
	 * @author Ralitza Koleva
	 *
	 * @email rallly@abv.bg
	 *
	 * @date 18 Sep 2011
	 */
	public void showNewAnnPane() {
		remove(networkPane);
		remove(loginPane);
		remove(neuronPane);
		remove(connectionPane);
		remove(deleteAnnPane);
		remove(settingsPane);
		add(newAnnPane, BorderLayout.EAST);
		newAnnPane.revalidate();
		workArea.setVisible(false);
		repaint();
	}

	/**
	 * Visualizing delete ANN pane.
	 *
	 * @author Ralitza Koleva
	 *
	 * @email rallly@abv.bg
	 *
	 * @date 27 Nov 2011
	 */
	public void showDeleteAnnPane() {
		remove(networkPane);
		remove(loginPane);
		remove(neuronPane);
		remove(connectionPane);
		remove(newAnnPane);
		remove(settingsPane);
		add(deleteAnnPane, BorderLayout.EAST);
		deleteAnnPane.revalidate();
		workArea.setVisible(false);
		repaint();
	}

	/**
	 * Visualizing settings pane.
	 *
	 * @author Ralitza Koleva
	 *
	 * @email rallly@abv.bg
	 *
	 * @date 21 Oct 2011
	 */
	public void showSettingsPane() {
		remove(networkPane);
		remove(loginPane);
		remove(neuronPane);
		remove(connectionPane);
		remove(newAnnPane);
		remove(deleteAnnPane);
		add(settingsPane, BorderLayout.EAST);
		settingsPane.revalidate();
		repaint();
	}

	/**
	 * Shows the menu bar when a user logs in.
	 *
	 * @author Ralitza Koleva
	 *
	 * @email rallly@abv.bg
	 *
	 * @date 03 Sep 2011
	 */
	public void showMenuBarAfterLogin() {
		menuBar.add(networkMenu);
		networkMenu.add(newNetworkItem);
		networkMenu.add(loadNetworkItem);
		networkMenu.add(deleteNetworkItem);
		menuBar.add(toolsMenu);
		toolsMenu.add(settingsItem);
		toolsMenu.add(meshMenu);
		toolsMenu.add(numberingItem);
		meshItemsGroup.add(meshActivitiesItem);
		meshItemsGroup.add(meshWeightsItem);
		meshItemsGroup.add(meshBothItem);
		meshItemsGroup.add(meshSolidItem);
		meshMenu.add(meshActivitiesItem);
		meshMenu.add(meshWeightsItem);
		meshMenu.add(meshBothItem);
		meshMenu.add(meshSolidItem);

		/*
		 * At the beginning in menu "Tools->Mesh" the option "Solid" is
		 * selected.
		 */
		if (meshActivitiesItem.isSelected() == false
				&& meshWeightsItem.isSelected() == false
				&& meshBothItem.isSelected() == false
				&& meshSolidItem.isSelected() == false) {
			meshSolidItem.setSelected(true);
		}
		add(workArea);
	}

	/**
	 * Removes the menu bar when a user logs out.
	 *
	 * @author Ralitza Koleva
	 *
	 * @email rallly@abv.bg
	 *
	 * @date 03 Sep 2011
	 */
	public void hideMenuBarAfterLogout() {
		menuBar.remove(networkMenu);
		menuBar.remove(toolsMenu);
		remove(workArea);
		remove(loginPane);
		remove(networkPane);
		remove(neuronPane);
		remove(connectionPane);
		remove(newAnnPane);
		remove(deleteAnnPane);
		remove(settingsPane);
	}
}
