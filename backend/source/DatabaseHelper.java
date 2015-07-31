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

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

/**
 * Database helping class.
 *
 * @author Momchil Anachkov
 *
 * @email mZer0000@gmail.com
 *
 * @date 19 Dec 2010
 */
public class DatabaseHelper {

	/**
	 * SQL query for selecting all ANN ids, symbols and periods.
	 */
	private static final String SQL_QUERY_SYMBOL_PERIOD_ID = "SELECT currency_pairs.symbol, time_periods.period, ann.id FROM ann, ann_kind, time_periods, currency_pairs WHERE currency_pairs.id=ann_kind.currency_pairs_id AND time_periods.id=currency_pairs.period_id AND ann.ann_kind_id=ann_kind.id ORDER BY ann.id;";

	/**
	 * SQL query for selecting all ANN ids, symbols and periods by symbol.
	 */
	private static final String SQL_QUERY_SYMBOL_PERIOD_ID_BY_SYMBOL = "SELECT currency_pairs.symbol, time_periods.period, ann.id FROM ann, ann_kind, time_periods, currency_pairs WHERE ann.ann_kind_id=ann_kind.id AND ann_kind.currency_pairs_id=currency_pairs.id AND time_periods.id=currency_pairs.period_id AND currency_pairs.symbol='%s' ORDER BY ann.id;";

	/**
	 * SQL query for selecting all ANN ids, symbols and periods by period.
	 */
	private static final String SQL_QUERY_SYMBOL_PERIOD_ID_BY_PERIOD = "SELECT currency_pairs.symbol, time_periods.period, ann.id FROM ann, ann_kind, time_periods, currency_pairs WHERE ann_kind.currency_pairs_id=currency_pairs.id AND time_periods.id=currency_pairs.period_id AND time_periods.id=%d AND ann.ann_kind_id=ann_kind.id ORDER BY ann.id;";

	/**
	 * SQL query for selecting all ANN ids, symbols and periods by symbol and
	 * period.
	 */
	private static final String SQL_QUERY_SYMBOL_PERIOD_ID_BY_SYMBOL_AND_PERIOD = "SELECT currency_pairs.symbol, time_periods.period, ann.id FROM ann, ann_kind, time_periods, currency_pairs WHERE currency_pairs.symbol='%s' AND period_id=%d AND ann_kind.currency_pairs_id=currency_pairs.id AND time_periods.id=currency_pairs.period_id AND ann.ann_kind_id=ann_kind.id ORDER BY ann.id;";

	/**
	 * SQL query for selecting information about all ANN kinds ids symbol,
	 * period.
	 */
	private static final String SQL_QUERY_ANN_KINDS_ID = "SELECT ann_kind.id AS id, currency_pairs.symbol AS symbol, time_periods.id AS period FROM ann_kind, time_periods, currency_pairs WHERE ann_kind.currency_pairs_id=currency_pairs.id AND time_periods.id=currency_pairs.period_id ";

	/**
	 * SQL query for selecting ANN values by ANN id.
	 */
	private static final String SQL_QUERY_ANN_BY_ID = "SELECT ann.id AS id, currency_pairs.symbol AS symbol, time_periods.id AS period_id, ann_kind.number_of_neurons, ann_kind.flags, ann.fitness, ann.weights, ann_kind.activities, neurons_coordinates.coordinates FROM ann, ann_kind, neurons_coordinates, currency_pairs, time_periods WHERE ann.id=%d AND neurons_coordinates.ann_id=ann.id AND ann_kind.currency_pairs_id=currency_pairs.id AND currency_pairs.period_id=time_periods.id AND ann.ann_kind_id = ann_kind.id;";

	/**
	 * SQL query for selecting currency pairs ID by simbol and period.
	 */
	private static final String SQL_QUERY_CURRENCY_PAIR_BY_CURRENCY_PAIR_AND_PERIOD = "SELECT id FROM currency_pairs WHERE symbol='%s' AND period_id=%d";

	/**
	 * SQL query for checking if selected ANN has neuron coordinates.
	 */
	private static final String SQL_QUERY_HAS_COORDINATES = "SELECT * FROM neurons_coordinates WHERE neurons_coordinates.ann_id=%d;";

	/**
	 * SQL query for obtaining number of neurons.
	 */
	private static final String SQL_QUERY_NUMBER_OF_NEURONS = "SELECT ann_kind.number_of_neurons FROM ann, ann_kind WHERE ann.ann_kind_id = ann_kind.id AND ann.id = %d;";

	/**
	 * SQL query for insertion of default initial coordinates.
	 */
	private static final String SQL_QUERY_INSERT_DEFAULT_COORDINATES = "INSERT INTO neurons_coordinates (ann_id, coordinates) VALUES (%d, '%s');";

	/**
	 * SQL query updating neurons flags and weights activities.
	 */
	private static final String SQL_QUERY_UPDATE_FLAGS_AND_ACTIVITIES = "UPDATE ann_kind SET flags = '%s', activities = '%s' WHERE ann_kind.id = (SELECT ann_kind_id FROM ann WHERE ann.id = %d);";

	/**
	 * SQL query updating weights.
	 */
	private static final String SQL_QUERY_UPDATE_WEIGHTS = "UPDATE ann SET weights = '%s' WHERE ann.id = %d;";

	/**
	 * SQL query for updating neurons coordinates.
	 */
	private static final String SQL_QUERY_UPDATE_COORDINATES = "UPDATE neurons_coordinates SET coordinates = '%s' WHERE neurons_coordinates.ann_id = '%d';";

	/**
	 * SQL query for inserting information about a new ANN kind.
	 */
	private static final String SQL_QUERY_INSERT_ANN_KIND = "INSERT INTO ann_kind(currency_pairs_id, number_of_neurons, flags, activities) VALUES ('%s', '%d', '%s', '%s')";

	/**
	 * SQL query for inserting information about a new ANN.
	 */
	private static final String SQL_QUERY_INSERT_ANN = "INSERT INTO ann(ann_kind_id, fitness, weights) VALUES('%d', '%d', '%s')";

	/**
	 * SQL query for deleting information about an ANN kind.
	 */
	private static final String SQL_QUERY_DELETE_ANN_KIND = "DELETE FROM ann_kind WHERE id IN (SELECT ann_kind_id FROM ann WHERE id='%d')";

	/**
	 * SQL query for deleting information about an ANN.
	 */
	private static final String SQL_QUERY_DELETE_ANN = "DELETE FROM ann WHERE id='%d'";

	/**
	 * SQL query for inserting information about a new ANN.
	 */
	private static final String SQL_QUERY_INSERT_ANN_COORDINATES = "INSERT INTO neurons_coordinates(ann_id, coordinates) VALUES('%d', '%s')";

	/**
	 * SQL query for selecting currency pairs.
	 */
	private static final String SQL_QUERY_SYMBOL = "SELECT DISTINCT symbol FROM currency_pairs";

	/**
	 * SQL query for selecting periods.
	 */
	private static final String SQL_QUERY_PERIOD = "SELECT id, period FROM time_periods";

	/**
	 * Containing the MYSQL driver for the connection.
	 */
	private static final String MYSQL_DRIVER = "com.mysql.jdbc.Driver";

	/**
	 * Default minimum x coordinate to be written into database.
	 */
	private static final int DEFAULT_MIN_X_COORDINATE = 100;

	/**
	 * Default minimum y coordinate to be written into database.
	 */
	private static final int DEFAULT_MIN_Y_COORDINATE = 100;

	/**
	 * Default maximum x coordinate to be written into database.
	 */
	private static final int DEFAULT_MAX_X_COORDINATE = 500;

	/**
	 * Default maximum y coordinate to be written into database.
	 */
	private static final int DEFAULT_MAX_Y_COORDINATE = 500;

	/**
	 * Default database name.
	 */
	private static final String DEFAULT_DATABASE_NAME = "todorb_vitoshatrade";

	/**
	 * Containing the address where the database is hosted.
	 */
	private String host;

	/**
	 * Representing the port number for the host.
	 */
	private int port;

	/**
	 * Containing the name of the database.
	 */
	private String databaseName;

	/**
	 * Containing the username for logging in.
	 */
	private String username;

	/**
	 * Containing the password for logging in.
	 */
	private String password;

	/**
	 * Link to the database server.
	 */
	private Connection connection;

	/**
	 * Constructing the database helping class with passed parameters.
	 *
	 * @param host
	 *            The address where the database is hosted.
	 *
	 * @param port
	 *            The port number for the host.
	 *
	 * @param databaseName
	 *            The name of the database.
	 *
	 * @param username
	 *            The username for logging into the server.
	 *
	 * @param password
	 *            The password for logging into the server.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	public DatabaseHelper(String host, int port, String databaseName,
						  String username, String password) {
		super();

		this.host = host;
		this.port = port;
		this.databaseName = databaseName;
		this.username = username;
		this.password = password;
	}

	/**
	 * Constructing the database helping class without passed parameters.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	public DatabaseHelper() {
		this("", 0, DEFAULT_DATABASE_NAME, "", "");
	}

	/**
	 * Database host URL getter.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	public String getHost() {
		return host;
	}

	/**
	 * Database host URL setter.
	 *
	 * @param host
	 *            The host to be set.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	public void setHost(String host) {
		this.host = host;
	}

	/**
	 * Databes server port getter.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	public int getPort() {
		return port;
	}

	/**
	 * Databes server port setter.
	 *
	 * @param port
	 *            The port to be set.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	public void setPort(int port) {
		this.port = port;
	}

	/**
	 * Database name getter.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	public String getDatabaseName() {
		return databaseName;
	}

	/**
	 * Database name setter.
	 *
	 * @param databaseName
	 *            The database name to be set.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	public void setDatabaseName(String databaseName) {
		this.databaseName = databaseName;
	}

	/**
	 * Database username getter.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	public String getUsername() {
		return username;
	}

	/**
	 * Database username setter.
	 *
	 * @param username
	 *            The username to be set.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	public void setUsername(String username) {
		this.username = username;
	}

	/**
	 * Database password getter.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	public String getPassword() {
		return password;
	}

	/**
	 * Database password setter.
	 *
	 * @param password
	 *            The password to be set.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	public void setPassword(String password) {
		this.password = password;
	}

	/**
	 * Connecting to database.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	public void connect() throws Exception {
		Class.forName(MYSQL_DRIVER).newInstance();
		connection = DriverManager.getConnection("jdbc:mysql://" + host + ":"
					 + port + "/" + databaseName, username, password);
	}

	/**
	 * Disconnecting from database.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	public void disconnect() throws Exception {
		connection.close();
	}

	/**
	 * Provide list with available networks.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 *
	 * @return 2D array of strings with ANN information (id, symbol, period).
	 */
	public String[][] loadAnnList() {
		String[][] result = null;
		try {
			Statement select = connection.createStatement();
			ResultSet resultSet = select
								  .executeQuery(SQL_QUERY_SYMBOL_PERIOD_ID);

			resultSet.last();
			int size = resultSet.getRow();
			resultSet.beforeFirst();
			if (size > 0) {
				result = new String[size][3];
				int i = 0;
				while (resultSet.next() == true) {
					result[i][0] = resultSet.getString("symbol");
					result[i][1] = resultSet.getString("period");
					result[i][2] = Integer.toString(resultSet.getInt("id"));
					i++;
				}
			}
		} catch (Exception ex) {
			result = null;
			System.err.println(Texts.ERROR_LOAD_ANN_LIST);
			ex.printStackTrace();
			// TODO Inform user that there is no valid ANN list.
		}

		return (result);
	}

	/**
	 * Provide list with available networks.
	 *
	 * @param symbol
	 *            Currency pair symbol.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 *
	 * @return 2D array of strings with ANN information (id, symbol, period).
	 */
	public String[][] loadAnnListBySymbol(String symbol) {
		String[][] result = null;

		try {
			String sql = String.format(SQL_QUERY_SYMBOL_PERIOD_ID_BY_SYMBOL,
									   symbol);
			Statement select = connection.createStatement();
			ResultSet resultSet = select.executeQuery(sql);

			resultSet.last();
			int size = resultSet.getRow();
			resultSet.beforeFirst();
			if (size > 0) {
				result = new String[size][3];
				int i = 0;
				while (resultSet.next() == true) {
					result[i][0] = resultSet.getString("symbol");
					result[i][1] = resultSet.getString("period");
					result[i][2] = Integer.toString(resultSet.getInt("id"));
					i++;
				}
			}
		} catch (Exception e) {
			System.err.println(Texts.ERROR_LOAD_ANN_LIST);
			result = null;
			// TODO Inform user that there is no valid ANN list.
		}

		return (result);
	}

	/**
	 * Provide list with available networks.
	 *
	 * @param period
	 *            Currency pair period.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 *
	 * @return 2D array of strings with ANN information (id, symbol, period).
	 */
	public String[][] loadAnnListByPeriod(int period) {
		String[][] result = null;

		try {
			String sql = String.format(SQL_QUERY_SYMBOL_PERIOD_ID_BY_PERIOD,
									   period);
			Statement select = connection.createStatement();
			ResultSet resultSet = select.executeQuery(sql);

			resultSet.last();
			int size = resultSet.getRow();
			resultSet.beforeFirst();
			if (size > 0) {
				result = new String[size][3];
				int i = 0;
				while (resultSet.next() == true) {
					result[i][0] = resultSet.getString("symbol");
					result[i][1] = resultSet.getString("period");
					result[i][2] = Integer.toString(resultSet.getInt("id"));
					i++;
				}
			}
		} catch (Exception ex) {
			System.err.println(Texts.ERROR_LOAD_ANN_LIST);
			result = null;
			// TODO Inform user that there is no valid ANN list.
		}

		return (result);
	}

	/**
	 * Provide list with available networks.
	 *
	 * @param symbol
	 *            Currency pair symbol.
	 *
	 * @param period
	 *            Currency pair period.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 *
	 * @return 2D array of strings with ANN information (id, symbol, period).
	 */
	public String[][] loadAnnList(String symbol, int period) {
		String[][] result = null;

		try {
			String sql = String.format(
							 SQL_QUERY_SYMBOL_PERIOD_ID_BY_SYMBOL_AND_PERIOD, symbol,
							 period);
			Statement select = connection.createStatement();
			ResultSet resultSet = select.executeQuery(sql);

			resultSet.last();
			int size = resultSet.getRow();
			resultSet.beforeFirst();
			if (size > 0) {
				result = new String[size][3];
				int i = 0;
				while (resultSet.next() == true) {
					result[i][0] = resultSet.getString("symbol");
					result[i][1] = resultSet.getString("period");
					result[i][2] = Integer.toString(resultSet.getInt("id"));
					i++;
				}
			}
		} catch (Exception e) {
			System.err.println(Texts.ERROR_LOAD_ANN_LIST);
			e.printStackTrace();
			result = null;
			// TODO Inform user that there is no valid ANN list.
		}

		return (result);
	}

	/**
	 * Provides a list with available currency pairs.
	 *
	 * @author Ralitza Koleva
	 *
	 * @email rallly@abv.bg
	 *
	 * @date 17 Oct 2011
	 *
	 * @return Array of strings with currency pairs.
	 */
	public String[][] loadCurrencyPairs() {
		String[][] result = null;
		try {
			Statement select = connection.createStatement();
			ResultSet resultSet = select.executeQuery(SQL_QUERY_SYMBOL);

			resultSet.last();
			int size = resultSet.getRow();
			resultSet.beforeFirst();
			if (size > 0) {
				result = new String[size][2];
				int i = 0;
				while (resultSet.next() == true) {
					result[i][0] = resultSet.getString("symbol");
					i++;
				}
			}
		} catch (Exception ex) {
			result = null;
			System.err.println(Texts.ERROR_LOAD_CURRENCY_PAIRS_LIST);
			ex.printStackTrace();
			// TODO Inform user that there is no valid currency pairs list.
		}
		return (result);
	}

	/**
	 * Provides a list with available periods.
	 *
	 * @author Ralitza Koleva
	 *
	 * @email rallly@abv.bg
	 *
	 * @date 17 Oct 2011
	 *
	 * @return 2D array of strings with periods.
	 */
	public String[][] loadPeriods() {
		String[][] result = null;
		try {
			Statement select = connection.createStatement();
			ResultSet resultSet = select.executeQuery(SQL_QUERY_PERIOD);

			resultSet.last();
			int size = resultSet.getRow();
			resultSet.beforeFirst();
			if (size > 0) {
				result = new String[size][2];
				int i = 0;
				while (resultSet.next() == true) {
					result[i][0] = resultSet.getString("id");
					result[i][1] = resultSet.getString("period");
					i++;
				}
			}
		} catch (Exception ex) {
			result = null;
			System.err.println(Texts.ERROR_LOAD_PERIODS_LIST);
			ex.printStackTrace();
			// TODO Inform user that there is no valid periods list.
		}
		return (result);
	}

	/**
	 * Checking if selected ANN has neuron coordinates.
	 *
	 * @param id
	 *            Unique identifier for the ANN.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 03 Jan 2010
	 */
	void initIfNeeded(int id) {
		String sql = "";
		Statement statement = null;
		ResultSet resultSet = null;

		try {
			statement = connection.createStatement();

			sql = String.format(SQL_QUERY_HAS_COORDINATES, id);
			resultSet = statement.executeQuery(sql);

			resultSet.last();
			if (resultSet.getRow() == 1) {
				return;
			}
			sql = String.format(SQL_QUERY_NUMBER_OF_NEURONS, id);
			resultSet = statement.executeQuery(sql);
			resultSet.first();
			int numberOfNeurons = resultSet.getInt("number_of_neurons");
			String values = "";
			for (int i = 0; i < numberOfNeurons; i++) {
				values += DEFAULT_MIN_X_COORDINATE
						  + (int) (Math.random() * (DEFAULT_MAX_X_COORDINATE
													- DEFAULT_MIN_X_COORDINATE + 1));
				values += " ";
				values += DEFAULT_MIN_Y_COORDINATE
						  + (int) (Math.random() * (DEFAULT_MAX_Y_COORDINATE
													- DEFAULT_MIN_Y_COORDINATE + 1));
				values += " ";
			}
			values = values.trim();

			sql = String.format(SQL_QUERY_INSERT_DEFAULT_COORDINATES, id,
								values);

			statement.executeUpdate(sql);
		} catch (Exception ex) {
			// TODO Inform user that there is database problem.
		}
	}

	/**
	 * Provide selected ANN.
	 *
	 * @param id
	 *            Unique identifier for the ANN.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	public ArtificialNeuralNetwork loadAnn(int id) {
		String line = "";
		String values[] = null;
		ArtificialNeuralNetwork result = null;

		initIfNeeded(id);

		try {
			Statement select = connection.createStatement();
			String sql = String.format(SQL_QUERY_ANN_BY_ID, id);
			ResultSet resultSet = select.executeQuery(sql);

			resultSet.last();
			if (resultSet.getRow() != 1) {
				throw (new Exception(Texts.ERROR_NUMBER_DATABASE_RESULTS));
			}

			result = new ArtificialNeuralNetwork();
			result.id = resultSet.getInt("id");
			result.symbol = resultSet.getString("symbol");
			result.period = resultSet.getInt("period_id");
			result.numberOfNeurons = resultSet.getInt("number_of_neurons");
			result.fitness = resultSet.getDouble("fitness");

			/*
			 * Passing values from database to array of flags.
			 */
			line = resultSet.getString("flags");
			values = line.split("\\s+");
			result.flags = new int[result.numberOfNeurons];
			if (values.length != result.numberOfNeurons) {
				throw (new Exception("Wrong number of neuron flags."));
			}
			for (int i = 0; i < result.flags.length; i++) {
				result.flags[i] = Integer.parseInt(values[i]);
			}

			/*
			 * Passing values from database to array of weights.
			 */
			line = resultSet.getString("weights");
			values = line.split("\\s+");
			result.weights = new double[result.numberOfNeurons][result.numberOfNeurons];
			if (values.length != result.numberOfNeurons
					* result.numberOfNeurons) {
				throw (new Exception("Wrong number of weights."));
			}
			for (int j = 0; j < result.numberOfNeurons; j++) {
				for (int i = 0; i < result.numberOfNeurons; i++) {
					result.weights[i][j] = Double.parseDouble(values[i + j
										   * result.numberOfNeurons]);
				}
			}

			/*
			 * Passing values from database to array of activities.
			 */
			line = resultSet.getString("activities");
			values = line.split("\\s+");
			result.activities = new double[result.numberOfNeurons][result.numberOfNeurons];
			if (values.length != result.numberOfNeurons
					* result.numberOfNeurons) {
				throw (new Exception("Wrong number of activities."));
			}
			for (int j = 0; j < result.numberOfNeurons; j++) {
				for (int i = 0; i < result.numberOfNeurons; i++) {
					result.activities[i][j] = Double.parseDouble(values[i + j
											  * result.numberOfNeurons]);
				}
			}

			/*
			 * Passing values from database to array of coordinates.
			 */
			line = resultSet.getString("coordinates");
			values = line.split("\\s+");
			result.coordinates = new int[result.numberOfNeurons][2];
			if (values.length != result.numberOfNeurons * 2) {
				throw (new Exception("Wrong number of coordinates."));
			}
			for (int i = 0; i < result.numberOfNeurons; i++) {
				for (int k = 0; k < 2; k++) {
					result.coordinates[i][k] = Integer.parseInt(values[i * 2
											   + k]);
				}
			}

		} catch (Exception ex) {
			result = null;
			System.err.println(Texts.ERROR_LOAD_ANN_PART_1 + id
							   + Texts.ERROR_LOAD_ANN_PART_2);
			ex.printStackTrace();
			// TODO Inform user that there is no valid ANN list.
		}

		return (result);
	}

	/**
	 * Save ANN to remote database server.
	 *
	 * @param ann
	 *            ANN container.
	 *
	 * @author Momchil Anachkov
	 *
	 * @email mZer0000@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	public void saveAnn(ArtificialNeuralNetwork ann) {
		String sql = "";

		String flags = "";
		for (int i = 0; i < ann.flags.length; i++) {
			flags = flags + Integer.toString(ann.flags[i]) + " ";
		}
		flags = flags.trim();

		String activities = "";
		for (int j = 0; j < ann.numberOfNeurons; j++) {
			for (int i = 0; i < ann.numberOfNeurons; i++) {
				activities = activities + Double.toString(ann.activities[i][j])
							 + " ";
			}
			activities = activities.trim();
			activities += "\n";
		}
		activities = activities.trim();

		String weights = "";
		for (int j = 0; j < ann.numberOfNeurons; j++) {
			for (int i = 0; i < ann.numberOfNeurons; i++) {
				weights = weights + Double.toString(ann.weights[i][j]) + " ";
			}
			weights = weights.trim();
			weights += "\n";
		}
		weights = weights.trim();

		String coordinates = "";
		for (int i = 0; i < ann.numberOfNeurons; i++) {
			for (int k = 0; k < 2; k++) {
				coordinates = coordinates
							  + Integer.toString(ann.coordinates[i][k]) + " ";
			}
		}
		coordinates = coordinates.trim();

		try {
			Statement update = connection.createStatement();
			sql = String.format(SQL_QUERY_UPDATE_FLAGS_AND_ACTIVITIES, flags,
								activities, ann.id);
			update.executeUpdate(sql);

			sql = String.format(SQL_QUERY_UPDATE_WEIGHTS, weights, ann.id);
			update.executeUpdate(sql);

			sql = String.format(SQL_QUERY_UPDATE_COORDINATES, coordinates,
								ann.id);
			update.executeUpdate(sql);
		} catch (Exception ex) {
			System.err.println(Texts.ERROR_UPDATE_ANN);
			// TODO Inform user that the update process failed.
		}
	}

	/**
	 * Saves a new ANN to the remote database server.
	 *
	 * @param annSymbol
	 *            A currency pair chosen for the new ANN.
	 *
	 * @param annPeriod
	 *            A time period chosen for the new ANN.
	 *
	 * @param annNumberNeurons
	 *            Number of neurons of the new ANN.
	 *
	 * @param annActivitiesWeights
	 *            Weights of the new ANN.
	 *
	 * @param annFitness
	 *            Fitness of the new ANN.
	 *
	 * @param annFlags
	 *            Flags (neuron types) of the new ANN's neurons.
	 *
	 * @author Ralitza Koleva
	 *
	 * @email rallly@abv.bg
	 *
	 * @date 20 Sep 2011
	 */
	public int saveNewAnn(String annSymbol, int annPeriod,
						  int annNumberNeurons, String annActivitiesWeights, int annFitness,
						  String annFlags) {
		String sql = "";

		/*
		 * The ID of the currency pair of the new inserted ANN.
		 */
		int currencyPairId = 0;

		/*
		 * The ID of the new inserted ANN kind.
		 */
		int annKindId = 0;

		/*
		 * The ID of the new inserted ANN.
		 */
		int annId = 0;

		try {

			/*
			 * Selects the currency pair ID by symbol and period.
			 */
			Statement insert = connection.createStatement();
			sql = String.format(
					  SQL_QUERY_CURRENCY_PAIR_BY_CURRENCY_PAIR_AND_PERIOD,
					  annSymbol, annPeriod);
			insert.execute(sql);
			ResultSet selectedCurrencyPairId = insert.getResultSet();
			if (selectedCurrencyPairId.next()) {

				/*
				 * Gets the automatically generated ID of the new ANN kind.
				 */
				currencyPairId = selectedCurrencyPairId.getInt(1);
			}

			/*
			 * Inserts information about the new ANN kind.
			 */
			sql = String.format(SQL_QUERY_INSERT_ANN_KIND, currencyPairId,
								annNumberNeurons, annFlags, annActivitiesWeights);
			insert.executeUpdate(sql, Statement.RETURN_GENERATED_KEYS);
			ResultSet generatedAnnKindId = insert.getGeneratedKeys();
			if (generatedAnnKindId.next()) {

				/*
				 * Gets the automatically generated ID of the new ANN kind.
				 */
				annKindId = generatedAnnKindId.getInt(1);
			}

			/*
			 * Inserts information about the new ANN.
			 */
			sql = String.format(SQL_QUERY_INSERT_ANN, annKindId, annFitness,
								annActivitiesWeights);
			insert.executeUpdate(sql, Statement.RETURN_GENERATED_KEYS);
			ResultSet generatedAnnId = insert.getGeneratedKeys();
			if (generatedAnnId.next()) {

				/*
				 * Gets the automatically generated ID of the new ANN.
				 */
				annId = generatedAnnId.getInt(1);
			}
		} catch (Exception ex) {
			System.err.println(Texts.ERROR_ADD_ANN);
			ex.printStackTrace();
		}
		return annId;
	}

	/**
	 * Deletes an ANN from the remote database server.
	 *
	 * @param id
	 *            Unique identifier of the ANN.
	 *
	 * @author Ralitza Koleva
	 *
	 * @email rallly@abv.bg
	 *
	 * @date 27 Nov 2011
	 */
	public void deleteAnn(int id) {

		/*
		 * SQL string.
		 */
		String sql = "";

		try {

			/*
			 * Deletes information about the ANN kind.
			 */
			Statement delete = connection.createStatement();
			sql = String.format(SQL_QUERY_DELETE_ANN_KIND, id);
			delete.executeUpdate(sql);

			/*
			 * Deletes information about the ANN.
			 */
			sql = String.format(SQL_QUERY_DELETE_ANN, id);
			delete.executeUpdate(sql);
		} catch (Exception ex) {
			System.err.println(Texts.ERROR_DELETE_ANN);
			ex.printStackTrace();
		}
	}
}
