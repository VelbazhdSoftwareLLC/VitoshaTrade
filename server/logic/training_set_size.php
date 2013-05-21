<?php
/*******************************************************************************
 *                                                                             *
 * VitoshaTrade is Distributed Artificial Neural Network trained by            *
 * Differential Evolution for prediction of Forex. Project development is in   *
 * Sofia, Bulgaria. Vitosha is a mountain massif, on the outskirts of Sofia,   *
 * the capital of Bulgaria.                                                    *
 *                                                                             *
 * Copyright (C) 2008-2009 by Todor Balabanov  ( tdb@tbsoft-bg.com )           *
 *                            Iliyan Zankinski ( iliyan_mf@abv.bg )            *
 *                            Galq Cirkalova   ( galq_cirkalova@abv.bg )       *
 *                            Ivan Grozev      ( ivan.iliev.grozev@gmail.com ) *
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
?>

<?php
/*
 * Include database functions.
 */
include "../common/db.php";

/*
 * Response output variable.
 */
$response = '';

/*
 * Check input parameters.
 */
if ( !isset($_POST['symbol']) ) {
	$symbol = "";
} else {
	$symbol = trim($_POST['symbol'],"\r\n");
}

if ( !isset($_POST['period']) ) {
	$period = 0;
} else {
	$period = intval($_POST['period']);
}

/*
 * Open database.
 */
open_db();

/*
 * Prepare SQL query.
 */
$sql = "select number_of_examples from training_set, currency_pairs, time_periods where training_set.currency_pairs_id=currency_pairs.id and currency_pairs.period_id=time_periods.id and currency_pairs.symbol='" . $symbol . "' and time_periods.minutes=" . $period . ";";

/*
 * Run SQL query.
 */
$result = query_db( $sql );

/*
 * Check SQL query result.
 */
if ($result != false) {
	/*
	 * Response with number of training examples.
	 */
	$response .= trim($result[0][0],"\r\n");
	$response .= "\n";
} else {
	/*
	 * Response with zeor available training examples.
	 */
	$response .= 0;
	$response .= "\n";
}

/*
 * Close database.
 */
close_db();

/*
 * Output response.
 */
echo( $response );
flush();
?>
