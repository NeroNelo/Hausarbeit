<?php

$file = '../Webseite/temperatur';

$app = '../App/temperatur';

$temp = $_GET[t];

file_put_contents($file, $temp);

$temp = '{ "data": "' . $temp . '" }';

file_put_contents($app, $temp);

?>