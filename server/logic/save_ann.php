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

if ( !isset($_POST['fitness']) ) {
	$fitness = PHP_INT_MAX;
} else {
	$fitness = floatval($_POST['fitness']);
}

if ( !isset($_POST['number_of_neurons']) ) {
	$number_of_neurons = 0;
} else {
	$number_of_neurons = intval($_POST['number_of_neurons']);
}

if ( !isset($_POST['flags']) ) {
	$flags = "";
} else {
	$flags = trim($_POST['flags'],"\r\n");
}

if ( !isset($_POST['weights']) ) {
	$weights = "";
} else {
	$weights = trim($_POST['weights'],"\r\n");
}

if ( !isset($_POST['activities']) ) {
	$activities = "";
} else {
	$activities = trim($_POST['activities'],"\r\n");
}

/*
 * Validate flags array.
 */
$tok = strtok($flags, " \r\n");
$buffer = "";
for ($i=0; $i<$number_of_neurons; $i++) {
	if ($tok != false) {
		$buffer .= (intval($tok) . " ");
	} else {
		$buffer .= "0" . " ";
	}
	$tok = strtok(" \r\n");
}
$buffer = trim($buffer, " \r\n");
$flags = $buffer;

/*
 * Validate weights matrix.
 */
//TODO Be very careful with matrix transpose (C++ vs PHP).
$tok = strtok($weights, " \r\n");
$buffer = "";
for ($j=0; $j<$number_of_neurons; $j++) {
	for ($i=0; $i<$number_of_neurons; $i++) {
		if ($tok != false) {
			$buffer .= (floatval($tok) . " ");
		} else {
			$buffer .= "0" . " ";
		}

		$tok = strtok(" \r\n");
	}

	$buffer = trim($buffer, " \r\n");
	$buffer .= "\r\n";
}
$buffer = trim($buffer, " \r\n");
$weights = $buffer;

/*
 * Validate activities matrix.
 */
$tok = strtok($activities, " \r\n");
$buffer = "";
//TODO Be very careful with matrix transpose (C++ vs PHP).
for ($j=0; $j<$number_of_neurons; $j++) {
	for ($i=0; $i<$number_of_neurons; $i++) {
		if ($tok != false) {
			$buffer .= (floatval($tok) . " ");
		} else {
			$buffer .= "0" . " ";
		}

		$tok = strtok(" \r\n");
	}

	$buffer = trim($buffer, " \r\n");
	$buffer .= "\r\n";
}
$buffer = trim($buffer, " \r\n");
$activities = $buffer;

/*
 * Open database.
 */
open_db();

/*
 * SQL query for ANN save.
 */
$sql = "call saveAnn('" . $symbol . "', " . $period . ", " . $number_of_neurons . ", '" . $flags . "', '" . $activities . "', " . $fitness . ", '" . $weights . "')";

$result = query_db( $sql );

/*
 * Close database.
 */
close_db();
?>
