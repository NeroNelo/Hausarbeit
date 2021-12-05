<?php
	$tuer = file_get_contents('http://192.168.2.121/Projekt/Webseite/tuer');
	if($tuer >10){ echo 'Offen';}else{echo 'Zu'; }
?>