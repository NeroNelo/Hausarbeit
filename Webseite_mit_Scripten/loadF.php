<?php
	$fenster = file_get_contents('http://192.168.2.121/Projekt/Webseite/fenster');
	if($fenster >10){ echo 'Offen';}else{echo 'Zu';}
?>