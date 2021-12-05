<?php

$file = '../Webseite/tuer';

$app = '../App/tuer';

$temp = $_GET[t];

file_put_contents($file, $temp);

$temp = '{ "data": "' . $temp . '" }';

file_put_contents($app, $temp);

?>