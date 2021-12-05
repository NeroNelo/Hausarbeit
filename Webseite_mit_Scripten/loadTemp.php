<?php
	$temperatur = file_get_contents('http://192.168.2.121/Projekt/Webseite/temperatur');
	echo $temperatur. ' °C'
?>