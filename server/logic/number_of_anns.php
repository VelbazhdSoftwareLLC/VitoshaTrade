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
 * Prepare SQL query by ANN id.
 */
$sql = 'select id from ann where ann.ann_kind_id=(select ann_kind_id from ann where id=' . $annid . ') order by fitness asc;';

/*
 * Run SQL query.
 */
$result = query_db( $sql );

/*
 * Count number of artificial neural networks available.
 */
$count = 0;

/*
 * Check SQL query result.
 */
if ($result != false) {
	/*
	 * Response with all artificial neural networks identifyers available.
	 */
	for ($i=0; $i<count($result); $i++) {
		$response .= trim($result[$i][0],"\r\n");
		$response .= "\n";
		$count++;
	}
}

/*
 * Prepare SQL query by ANN symbol and period.
 */
$sql = 'select id, ann_kind_id from ann where ann.ann_kind_id=(select ann_kind_id from ann_kind, currency_pairs, time_periods where currency_pairs_id=currency_pairs.id and period_id=time_periods.id and symbol=' . $symbol . ' and period=' . $period . ') order by fitness asc;';

/*
 * Run SQL query.
 */
$result = query_db( $sql );

/*
 * Check SQL query result if there is no list by ANN id.
 */
if ($count==0 && $result!=false) {
	/*
	 * Artificial neural networks should be from the same kind.
	 */
	$ann_kind_id = $result[0][1];

	/*
	 * Response with all artificial neural networks identifyers available.
	 */
	for ($i=0; $i<count($result); $i++) {
		if ($result[$i][1] == $ann_kind_id) {
			$response .= trim($result[$i][0],"\r\n");
			$response .= "\n";
			$count++;
		}
	}
}

/*
 * Response with number of artificial neural networks available.
 */
$response = "\n" . $response;
$response = trim($count,"\r\n") . $response;

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
