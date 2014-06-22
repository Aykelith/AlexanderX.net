<?php
function connectDatabase() 
{ 
	$host = 'host'; 
	$db = 'database'; 
	$user = 'user'; 
	$pwd = 'password';

	$connection =  new mysqli($host, $user, $pwd, $db) or die ('Cannot open database');
	return $connection; 
}
?>
