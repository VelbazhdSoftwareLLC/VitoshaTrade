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
 *                            Ralitza Koleva   ( rallly@abv.bg )	       *
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

/**
 * Gives a JComboBox two values - a visible value in the drop down menu and a
 * hidden one.
 * 
 * @author Ralitza Koleva
 * 
 * @email rallly@abv.bg
 * 
 * @date 29 Oct 2011
 */
public class SymbolPeriodKeyValue {

	/**
	 * Hidden value of the JComboBox item.
	 */
	private String key;

	/**
	 * Visible value of the JComboBox item.
	 */
	private String value;

	/**
	 * SymbolPeriodKeyValue constructor.
	 * 
	 * @param key
	 *            Hidden value of the JComboBox item.
	 * 
	 * @param value
	 *            Visible value of the JComboBox item.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 29 Oct 2011
	 */
	public SymbolPeriodKeyValue(String key, String value) {
		this.key = key;
		this.value = value;
	}

	/**
	 * Gets the visible value of the JComboBox item.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 29 Oct 2011
	 * 
	 * @return The visible value of the JComboBox item.
	 */
	public String getValue() {
		return (value);
	}

	/**
	 * Gets the hidden value of the JComboBox item.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 29 Oct 2011
	 * 
	 * @return The hidden value of the JComboBox item.
	 */
	public int getKey() {
		return (Integer.parseInt(key));
	}

	/**
	 * Converts the visible value of the JComboBox item to a string.
	 * 
	 * @author Ralitza Koleva
	 * 
	 * @email rallly@abv.bg
	 * 
	 * @date 29 Oct 2011
	 * 
	 * @return The visible value of the JComboBox item as a string.
	 */
	public String toString() {
		return (value);
	}
}
