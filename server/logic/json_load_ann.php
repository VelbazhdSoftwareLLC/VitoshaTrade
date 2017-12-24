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

header("access-control-allow-origin: *");

/*
 * Response output variable.
 */
$response = '';

/*
 * Check input parameters.
 */
if ( !isset($_POST['annid']) ) {
	$annid = -1;
} else {
	$annid = intval($_POST['annid']);
}

/*
 * Open database.
 */
open_db();

/*
 * Prepare SQL query.
 */
$sql = 'select currency_pairs.symbol, time_periods.minutes, ann.fitness, ann_kind.number_of_neurons, ann_kind.flags, ann.weights, ann_kind.activities from ann, ann_kind, currency_pairs, time_periods where ann_kind.currency_pairs_id=currency_pairs.id and currency_pairs.period_id=time_periods.id and ann.id=' . $annid . ' and ann.ann_kind_id=ann_kind.id;';

/*
 * Run SQL query.
 */
$result = query_db( $sql );

/*
 * Check SQL query result.
 */
$response .= "{";
if ($result != false) {
	$response .= "\n";

	/*
	 * Response with artificial neural networks structure.
	 */
	$response .= '"size":"1",';
	$response .= "\n";

	/*
	 * MetaTrader 4 symbol.
	 */
	$response .= '"symbol":"' . trim($result[0][0],"\r\n") . '",';
	$response .= "\n";

	/*
	 * MetaTrader 4 period.
	 */
	$response .= '"period":"' . trim($result[0][1],"\r\n") . '",';
	$response .= "\n";

	/*
	 * Artificial neural network weights fitness.
	 */
	$response .= '"fitness":"' . trim($result[0][2],"\r\n") . '",';
	$response .= "\n";

	/*
	 * Artificial neural network number of neurons.
	 */
	$response .= '"numberOfNeurons":"' . trim($result[0][3],"\r\n") . '",';
	$response .= "\n";

	/*
	 * Artificial neural network neurons flags.
	 */
	$response .= '"flags": [';
	$values = explode(" ", trim($result[0][4],"\r\n"));
	foreach($values as $value) {
		$response .= '"'.$value.'",';
	}
	$response = trim($response,",");
	$response .=  '],';
	$response .= "\n";

	/*
	 * Artificial neural network weights.
	 */
	$response .= '"weights": [';
	$response .= "\n";
	$lines = explode("\r\n", trim($result[0][5],"\r\n"));
	foreach($lines as $line) {
		$response .= '[';
		$values = explode(" ", $line);
		foreach($values as $value) {
			$response .= '"'.$value.'",';
		}
		$response = trim($response,",");
		$response .=  '],';
		$response .= "\n";
	}
	$response = trim($response,"\n,");
	$response .= "\n";
	$response .=  '],';
	$response .= "\n";

	/*
	 * Artificial neural network weights activities.
	 */
	$response .= '"activities": [';
	$response .= "\n";
	$lines = explode("\r\n", trim($result[0][6],"\r\n"));
	foreach($lines as $line) {
		$response .= '[';
		$values = explode(" ", $line);
		foreach($values as $value) {
			$response .= '"'.$value.'",';
		}
		$response = trim($response,",");
		$response .=  '],';
		$response .= "\n";
	}
	$response = trim($response,"\n,");
	$response .= "\n";
	$response .=  ']';
	$response .= "\n";
} else {
	/*
	 * Response with -1 flag that artificial neural networks can not be loaded.
	 */
	$response .= '"size":"0"';
	$response .= "\n";
}
$response .= "}";

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
