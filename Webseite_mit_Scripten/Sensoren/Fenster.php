<?php

$web = '../Webseite/fenster';

$app = '../App/fenster';

$temp = $_GET[t];

file_put_contents($web, $temp);

$temp = '{ "data": "' . $temp . '" }';

file_put_contents($app, $temp);


?>