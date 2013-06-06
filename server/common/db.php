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
/**
 * Host name.
 */
define("HOSTNAME", "localhost");

/**
 * Database username.
 */
define("USERNAME", "root");

/**
 * Database user password.
 */
define("PASSWORD", "");

/**
 * Database name.
 */
define("DBNAME", "veldsoft_vitoshatrade");

/**
 * Database link global variable.
 */
$GLOBALS[ 'link' ] = null;

/**
 * Open global database link.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft-bg.com
 *
 * @date 27 Apr 2009
 */
function open_db() {
	$GLOBALS[ 'link' ] = mysql_connect(HOSTNAME, USERNAME, PASSWORD);
	mysql_select_db( DBNAME );
}

/**
 * Database query.
 *
 * @param $qrystr SQL query string.
 *
 * @return Array with SQL query result.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft-bg.com
 *
 * @date 27 Apr 2009
 */
function query_db( $qrystr ) {
	$resstrs = false;

	if($qrystr[strlen($qrystr)-1] == ',') {
		$qrystr[strlen($qrystr)-1] = " ";
	}

	if ( !$GLOBALS['link'] ) {
		$resstrs = false;
	} else {
		$result = mysql_query($qrystr, $GLOBALS['link']);

		$j = 0;
		if ($result!=1 && $result!=false) {
			while ($row = mysql_fetch_row($result)) {
				for ($i=0; $i<mysql_num_fields($result); $i++) {
					$resstrs[ $j ][ $i ] = $row[ $i ];
				}

				$j++;
			}
		} else {
			$resstrs = false;
		}
	}

	return( $resstrs );
}

/**
 * Close global database link.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft-bg.com
 *
 * @date 27 Apr 2009
 */
function close_db() {
	if ( $GLOBALS['link'] ) {
		mysql_close( $GLOBALS['link'] );
	}
}
?>
