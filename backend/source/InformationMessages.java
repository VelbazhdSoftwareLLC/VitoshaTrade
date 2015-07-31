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
import javax.swing.JOptionPane;

/**
 * Shows a pop-up message on the screen.
 *
 * @author Ralitza Koleva
 *
 * @email rallly@abv.bg
 *
 * @date 05 Dec 2011
 */
public class InformationMessages {

	/**
	 * Frame for the connection error message.
	 */
	protected static final Component frame = null;

	/**
	 * Message text.
	 */
	private String message;

	/**
	 * Message title.
	 */
	private String title;

	/**
	 * Message type.
	 */
	private int messageType;

	/**
	 * Constructing pop-up message.
	 *
	 * @param message
	 *            Message text.
	 *
	 * @param header
	 *            Message header.
	 *
	 * @param messageType
	 *            Message type (error/warning/information, etc.).
	 *
	 * @author Ralitza Koleva
	 *
	 * @email rallly@abv.bg
	 *
	 * @date 05 Dec 2011
	 */
	public InformationMessages(String message, String header, int messageType) {
		this.message = message;
		this.title = header;
		this.messageType = messageType;
	}

	/**
	 * Shows a pop-up message on the screen.
	 *
	 * @author Ralitza Koleva
	 *
	 * @email rallly@abv.bg
	 *
	 * @date 05 Dec 2011
	 */
	void showMessage() {
		JOptionPane.showMessageDialog(frame, message, title, messageType);
		return;
	}
}
