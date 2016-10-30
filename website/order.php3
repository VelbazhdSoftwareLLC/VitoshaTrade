<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>.:: Vitosha Trade ::.</title>
<link href="styles.css" rel="stylesheet" type="text/css" />
</head>

<body>
	<div id="wrapper">
		<?php include 'menu.php';?>

		<?php include 'header.php';?>

		<div class="innerContainerTop"></div>

		<div class="innerContainer">
			<h1 style="margin-top:-10px;">Order Vitosha Trade</h1>
			<form action="#" class="orderform" method="post">
            	<fieldset id="general_details">
                	<ul>
                    	<li>
                            <label for="title">Title </label> 
                            <select id="title" class="shortInput" title="Title" name="title">
                                <option value="Mr" selected="selected">Mr.</option>
                                <option value="Ms">Ms.</option>
                                <option value="Mrs">Mrs</option>
                                <option value="Miss">Miss</option>
                                <option value="Dr">Dr.</option>
                            </select>
                        </li>            
                        <li><label for="first_name">First Name </label><input id="first_name" type="text" title="First Name" name="first_name"/></li>
                        <li><label for="last_name">Last Name </label><input id="last_name" type="text" title="Last Name" name="last_name"/></li>
                        <li>
                        	<label for="country_code" >Phone Number </label><input id="country_code" type="text" class="shortInput" value="Country" onfocus="this.value='';" title="Country Code" name="country_code"/> 
                            <input id="area_code" type="text" class="shortInput" value="Area" onfocus="this.value='';" title="Area Code" name="area_code"/>
                            <input id="phone_number" type="text" value="Phone Number" class="phoneField" onfocus="this.value='';" title="Phone Number" name="phone_number"/>
                        </li>
                        <li><label for="email" >Email Address </label><input id="email" type="text" title="Email Address" name="email"/></li>
						<li><label class="labelLong">All information is required because all orders will be confirmed by phone call, billing details and the software itself will be sent by email.</label></li>
                    </ul> 
                </fieldset>
				<div class="submit">
					<input type="button" value="Send Order" title="Send Order" class="btn" onmouseover="this.className='btn btnHov'" onmouseout="this.className='btn'"/> 
				</div>               
            </form>
		</div>

		<div class="innerContainerBottom"></div>

		<div class="clearer"></div>
		
		<?php include 'footer.php';?>
	</div>
</body>
</html>
