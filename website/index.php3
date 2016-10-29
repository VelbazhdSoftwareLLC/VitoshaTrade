<?php
/*
 * Include database functions.
 */
include "./common/db.php";

/**
 * Order e-mail address constant.
 */
define("ORDER_EMAIL", "todor.balabanov@gmail.com");

/**
 * ANN list results per page.
 */
define("PAGES_BEFORE_AND_AFTER", 5);

/**
 * ANN list results per page.
 */
define("RESULTS_PER_PAGE", 5);

/*
 * Check input parameters.
 */
if ( !isset($_POST['first_name']) ) {
	$first_name = "";
} else {
	$first_name = trim($_POST['first_name']);
}

if ( !isset($_POST['last_name']) ) {
	$last_name = "";
} else {
	$last_name = trim($_POST['last_name']);
}

if ( !isset($_POST['country_code']) ) {
	$country_code = "";
} else {
	$country_code = trim($_POST['country_code']);
}

if ( !isset($_POST['area_code']) ) {
	$area_code = "";
} else {
	$area_code = trim($_POST['area_code']);
}

if ( !isset($_POST['phone_number']) ) {
	$phone_number = "";
} else {
	$phone_number = trim($_POST['phone_number']);
}

if ( !isset($_POST['email']) ) {
	$email = "";
} else {
	$email = trim($_POST['email']);
}

if ( !isset($_GET['offset']) ) {
	$offset = 0;
} else {
	$offset = intval($_GET['offset']);
}

/*
 * Assemble order message.
 */
$message = "";
$message .= $first_name;
$message .= "\n";
$message .= $last_name;
$message .= "\n";
$message .= "+" . $country_code . $area_code . $phone_number;
$message .= "\n";
$message .= $email;
$message .= "\n";
if ($email != '') {
	mail(ORDER_EMAIL, 'VitoshaTrade order!', $message, "From: " . $email . "\nReply-to: " . $email);
}

/*
 * Open database.
 */
open_db();

$number_of_pages = 0;

/*
 * Prepare SQL query.
 */
$sql = "select ann.id, currency_pairs.symbol, time_periods.minutes, ann.fitness from ann, ann_kind, currency_pairs, time_periods where ann.ann_kind_id=ann_kind.id and ann_kind.currency_pairs_id=currency_pairs.id and currency_pairs.period_id=time_periods.id order by ann.fitness asc;";

/*
 * Run SQL query.
 */
$result = query_db( $sql );

/*
 * Check SQL query result.
 */
if ($result != false) {
	$number_of_pages = (int)ceil((double)count($result)/(double)RESULTS_PER_PAGE);
}

/*
 * Close database.
 */
close_db();

if ($offset < 0) {
	$offset = 0;
}
if ($offset >= $number_of_pages) {
	$offset = $number_of_pages-1;
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>.:: Vitosha Trade ::.</title>
<link href="styles.css" rel="stylesheet" type="text/css" />
</head>

﻿<body>
	<div id="wrapper">
		<div id="logo">
			<ul id="menu">
				<li><a class="current" href="index.php" title="Home Page">Home Page</a></li>
				<li class="spacer">&nbsp;</li>
				<li><a href="products.php" title="Products Information">Products Information</a></li>
				<li class="spacer">&nbsp;</li>
				<li><a href="contactus.php" title="Contact Us">Contact Us</a></li>
			</ul>
		</div>
		<div id="header">
			<div id="slogan">The Ultimate<br />&nbsp; &nbsp; &nbsp; Forex Prediction<br />&nbsp; &nbsp; &nbsp; 
			&nbsp; &nbsp; &nbsp; Indicator...</div>
		</div>
		<div id="home_about_bevel">
			<h1>About Vitosha Trade</h1>
			<div class="home_bevel_txt">
				VitoshaTrade &reg; is <a href="http://en.wikipedia.org/wiki/Foreign_exchange_market">Forex</a> prediction indicator that can be used only with <a href="http://www.metatrader4.com/">MetaTrader 4</a> trading  platform. 
				The indicator is based on Artificial Neural Networks trained by Differential Evolution algorithm in 
				distributed environment.
			</div>
		</div>
		<div id="home_purchase_bevel">
			<h1>Purchase Information</h1>
			<div class="home_bevel_txt">
				VitoshaTrade &reg; comes on the price of &euro;9999 (1/100 company shares included in the price). To make your order we would like to ask you fill 
				out the <a href="order.php" title="Order Vitosha Trade">order form</a>
			</div>
		</div>
		<div id="home_contact_bevel">
			<h1>Contact Us</h1>
			<div class="home_bevel_txt">
				Velbazhd Software - Bulgarian Software Company
				<br /><br />
				Todor Balabanov, CEO<br />
				Email: <a href="mailto:todor.balabanov@gmail.com" title="VitoshaTrade Email Request">todor.balabanov gmail com</a><br />
				Phone: +359 89 8237103
			</div>
		</div>
		<div class="clearer"></div>
		<div id="grid_home">
			<!-- <h1><center>Artificial Neural Networks List</center></h1> -->

			<table class="tableBorder" style="width:100%;padding:1;border-spcacing:1;border-collapse:separate;">
				<tr class="tableHeading">
					<th>ID</th>
					<th>Symbol</th>
					<th>Period</th>
					<th>Fitness</th>
				</tr>

<!-- Dynamic table content.  -->
<?php
if ($result != false) {
	for ($i=$offset*RESULTS_PER_PAGE,$c=0; $i<(($offset+1)*RESULTS_PER_PAGE)&&$i<count($result); $i++,$c++) {
		switch( $result[$i][2] ){
		case 1: $result[$i][2] = "M1";
			break;
		case 5: $result[$i][2] = "M5";
			break;
		case 15: $result[$i][2] = "M15";
			break;
		case 30: $result[$i][2] = "M30";
			break;
		case 60: $result[$i][2] = "H1";
			break;
		case 240: $result[$i][2] = "H4";
			break;
		case 1440: $result[$i][2] = "D1";
			break;
		case 10080: $result[$i][2] = "W1";
			break;
		case 43200: $result[$i][2] = "MN1";
			break;
		default: $result[$i][2] = "N/A";
		}
?>

<tr class="<?php echo( (($c%2)==0?'tableRow':'tableRowAlternative') );?>">
<td><?php echo($result[$i][0]);?></td>
<td><?php echo($result[$i][1]);?></td>
<td><?php echo($result[$i][2]);?></td>
<td><?php echo($result[$i][3]);?></td>
</tr>

<?php
	}
}
?>
<!-- Dynamic table content.  -->

			</table>
			<br />
			<div class="paging">

<a href="?offset=0" title="First Page"><img src="images/paging_first.jpg" style="border:0;" alt="First Page" /></a>  &nbsp;
<a href="?offset=<?php echo($offset-1);?>" title="Previous"><img src="images/left_arrow.jpg" style="border:0;" alt="Previous" /></a>  &nbsp; 

<?php
if ($result != false) {
	for ($i=$offset-PAGES_BEFORE_AND_AFTER; $i<=$offset+PAGES_BEFORE_AND_AFTER; $i++) {
		if ($i<0 || $i>=$number_of_pages) {
			continue;
		}
?>

<a href="?offset=<?php echo($i);?>"><?php echo($i+1);?></a>&nbsp;

<?php
	}
}
?>

<a href="?offset=<?php echo($offset+1);?>" title="Next"><img src="images/right_arrow.jpg" style="border:0;" alt="Next" /></a>  &nbsp;
<a href="?offset=<?php echo($number_of_pages-1);?>" title="Last Page"><img src="images/paging_last.jpg" style="border:0;" alt="Last Page" /></a>  &nbsp; 

			</div>
		</div>
		<div class="clearer"></div>
		<div id="footer">
			<div class="footerLeft">
			 	Design by <a href="http://www.mxworkz.com/" target="_blank" title="MXWorkz Creative">MXWorkz</a>
			</div>
			<div class="copy">This website and its content is intellectual pfoperty of <strong>Velbazhd Software &copy;</strong>. </div>
			<div class="footerRight">
				 <a href="index.php" title="Home">Home</a> &nbsp; &nbsp; 
				 <a href="products.php" title="Products Information">Products Information</a> &nbsp; &nbsp; 
				 <a href="contactus.php" title="Contact Us">Contact Us</a>
			</div>
		</div>
	</div>
</body>
</html>

