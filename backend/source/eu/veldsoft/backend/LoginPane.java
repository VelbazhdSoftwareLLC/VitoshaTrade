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

import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Properties;

import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JTextField;
import javax.swing.JPasswordField;

/**
 * Panel with GUI controls for longin.
 * 
 * @author Momchil Anachkov
 * 
 * @email mZer0000@gmail.com
 * 
 * @date 16 Nov 2010
 */
class LoginPane extends JPanel {
	/**
	 * Default serial version UID.
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * Parent applet reference.
	 */
	private VitoshaTradeApplet parent = null;

	/**
	 * GUI control for obtaining username.
	 */
	private JTextField username = new JTextField();

	/**
	 * GUI control for obtaining password.
	 */
	private JPasswordField password = new JPasswordField();

	/**
	 * GUI control for obtaining password.
	 */
	private JButton login = new JButton(Texts.LABEL_BUTTON_LOGIN);

	/**
	 * GUI control for obtaining the database location.
	 */
	private JTextField dbHost = new JTextField();

	/**
	 * GUI control for obtaining the database port.
	 */
	private JTextField dbPort = new JTextField();

	/**
	 * GUI control for obtaining the database name.
	 */
	private JTextField dbName = new JTextField();

	/**
	 * Constructing login pane.
	 * 
	 * @param parent
	 *            The parent class.
	 * 
	 * @author Momchil Anachkov
	 * 
	 * @email mZer0000@gmail.com
	 * 
	 * @date 16 Nov 2010
	 */
	public LoginPane(final VitoshaTradeApplet parent) {
		this.parent = parent;
		this.setPreferredSize(new Dimension(VitoshaTradeApplet.EAST_PANE_WIDTH,
				VitoshaTradeApplet.EAST_PANE_HEIGHT));

		setLayout(new GridLayout(25, 1));

		add(new JLabel(Texts.LABEL_DATABASE_HOST));
		add(dbHost);

		add(new JLabel(Texts.LABEL_DATABASE_PORT));
		add(dbPort);

		add(new JLabel(Texts.LABEL_DATABASE_NAME));
		add(dbName);

		/*
		 * Load login properties.
		 */
		try {
			Properties p = new Properties();
			FileInputStream in = new FileInputStream(Util.PROPERTIES_FILE_NAME);
			p.load(in);
			in.close();
			dbHost.setText(p.getProperty("DatabaseHost"));
			dbPort.setText(p.getProperty("DatabasePort"));
			dbName.setText(p.getProperty("DatabaseName"));
		} catch (Exception ex) {
		}

		add(new JLabel(Texts.LABEL_USERNAME));
		add(username);
		add(new JLabel(Texts.LABEL_PASSWORD));
		add(password);
		add(login);

		/*
		 * Listener for the login button.
		 */
		login.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				parent.dbHelp.setDatabaseName(dbName.getText());
				parent.dbHelp.setHost(dbHost.getText());
				try {
					parent.dbHelp.setPort((new Integer(dbPort.getText()))
							.intValue());
				} catch (Exception ex) {
					System.err.println(Texts.ERROR_DATABASE_PORT);
					// TODO Inform user that port should be number.
				}
				parent.dbHelp.setUsername(username.getText());
				parent.dbHelp.setPassword(password.getText());
				try {
					parent.dbHelp.connect();

					/*
					 * Show network pane.
					 */
					parent.showNetworkPane();
				} catch (Exception ex) {
					System.err.println(Texts.ERROR_DATABASE_CONNECT);
					System.err.println(ex);

					/*
					 * Shows connection error.
					 */
					showConnectionError();
				}

				/*
				 * Save login properties.
				 */
				try {
					Properties p = new Properties();
					FileInputStream allProperties = new FileInputStream(
							Util.PROPERTIES_FILE_NAME);
					p.load(allProperties);
					p.setProperty("DatabaseHost", dbHost.getText());
					p.setProperty("DatabasePort", dbPort.getText());
					p.setProperty("DatabaseName", dbName.getText());

					FileOutputStream out = new FileOutputStream(
							Util.PROPERTIES_FILE_NAME);
					p.store(out, "");
					allProperties.close();
					out.close();
				} catch (Exception ex) {
				}
			}
		});

		password.setEchoChar('*');
	}

	/**
	 * Shows error message when login fails.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 24 Nov 2011
	 */
	private void showConnectionError() {
		InformationMessages error = new InformationMessages(
				Texts.ERROR_DATABASE_CONNECT,
				Texts.ERROR_DATABASE_CONNECT_TITLE, JOptionPane.ERROR_MESSAGE);
		error.showMessage();
		parent.showLoginPane();
	}
}
