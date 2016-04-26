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

if ( !isset($_POST['number_of_examples']) ) {
	$number_of_examples = 0;
} else {
	$number_of_examples = intval($_POST['number_of_examples']);
}

if ( !isset($_POST['time']) ) {
	$time = "";
} else {
	$time = trim($_POST['time'],"\r\n");
}

if ( !isset($_POST['open']) ) {
	$open = "";
} else {
	$open = trim($_POST['open'],"\r\n");
}

if ( !isset($_POST['low']) ) {
	$low = "";
} else {
	$low = trim($_POST['low'],"\r\n");
}

if ( !isset($_POST['high']) ) {
	$high = "";
} else {
	$high = trim($_POST['high'],"\r\n");
}

if ( !isset($_POST['close']) ) {
	$close = "";
} else {
	$close = trim($_POST['close'],"\r\n");
}

if ( !isset($_POST['volume']) ) {
	$volume = "";
} else {
	$volume = trim($_POST['volume'],"\r\n");
}

/*
 * Validate time array.
 */
$tok = strtok($time, " \r\n");
$buffer = "";
for ($i=0; $i<$number_of_examples; $i++) {
	if ($tok != false) {
		$buffer .= (intval($tok) . " ");
	} else {
		$buffer .= "0" . " ";
	}
	$tok = strtok(" \r\n");
}
$buffer = trim($buffer, " \r\n");
$time = $buffer;

/*
 * Validate open array.
 */
$tok = strtok($open, " \r\n");
$buffer = "";
for ($i=0; $i<$number_of_examples; $i++) {
	if ($tok != false) {
		$buffer .= (floatval($tok) . " ");
	} else {
		$buffer .= "0" . " ";
	}
	$tok = strtok(" \r\n");
}
$buffer = trim($buffer, " \r\n");
$open = $buffer;

/*
 * Validate low array.
 */
$tok = strtok($low, " \r\n");
$buffer = "";
for ($i=0; $i<$number_of_examples; $i++) {
	if ($tok != false) {
		$buffer .= (floatval($tok) . " ");
	} else {
		$buffer .= "0" . " ";
	}
	$tok = strtok(" \r\n");
}
$buffer = trim($buffer, " \r\n");
$low = $buffer;

/*
 * Validate high array.
 */
$tok = strtok($high, " \r\n");
$buffer = "";
for ($i=0; $i<$number_of_examples; $i++) {
	if ($tok != false) {
		$buffer .= (floatval($tok) . " ");
	} else {
		$buffer .= "0" . " ";
	}
	$tok = strtok(" \r\n");
}
$buffer = trim($buffer, " \r\n");
$high = $buffer;

/*
 * Validate close array.
 */
$tok = strtok($close, " \r\n");
$buffer = "";
for ($i=0; $i<$number_of_examples; $i++) {
	if ($tok != false) {
		$buffer .= (floatval($tok) . " ");
	} else {
		$buffer .= "0" . " ";
	}
	$tok = strtok(" \r\n");
}
$buffer = trim($buffer, " \r\n");
$close = $buffer;

/*
 * Validate volume array.
 */
$tok = strtok($volume, " \r\n");
$buffer = "";
for ($i=0; $i<$number_of_examples; $i++) {
	if ($tok != false) {
		$buffer .= (floatval($tok) . " ");
	} else {
		$buffer .= "0" . " ";
	}
	$tok = strtok(" \r\n");
}
$buffer = trim($buffer, " \r\n");
$volume = $buffer;

/*
 * Open database.
 */
open_db();

/*
 * Run SQL query to replace previous record or insert new one.
 */
$sql = "call saveTrainingSet('" . $symbol . "', $period, $number_of_examples, '" . $time . "', '" . $open . "', '" . $low . "', '" . $high . "', '" . $close . "', '" . $volume . "');";
query_db( $sql );

/*
 * Close database.
 */
close_db();
?>
