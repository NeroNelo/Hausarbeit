<?php

$file = '../Webseite/klingel';

$app = '../App/klingel';

$temp = $_GET[t];

file_put_contents($file, $temp);

$temp = '{ "data": "' . $temp . '" }';

file_put_contents($app, $temp);

?>