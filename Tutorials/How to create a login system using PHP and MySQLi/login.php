<?php
define("TIMEOUT_MINUTES", 1);

$error = "";

function loginForm($error = "")
{
	?> 
	<!DOCTYPE html>
	<html>
	<head>
		<title>Login</title>
	</head>
	<body>
		<?php if ($error != "") echo '<font color="red">'.$error.'</font>'; ?>
		<form name="login" method="post">
			<label for="username">Username:</label>
			<input type="text" name="username" />
			<label for="password">Password:</label>
			<input type="password" name="password" />
			<input type="submit" name="submit" value="Login" />
		</form>
	</body>

	<?php
	die();
}

if (isset($_POST["submit"]))
{
	if (isset($_POST["username"]) && isset($_POST["password"]))
	{
		include("database.php");

		// Connecting to the database
		$connection = connectDatabase();

		// Getting the Password field where Username field is equal to the entered username
		$statement = $connection->query("SELECT Password FROM Users WHERE Username='{$_POST['username']}'") or die($connection->error.' '.__LINE__.' '.__FILE__);

		// Checking if exists the username in the table by checking the rows returned by the query 
		if ($statement->num_rows > 0)
		{
			// Getting the password field by fetching the data and getting the Password field
			$password = $statement->fetch_assoc()["Password"];

			if ($password == md5($_POST["password"]))
			{
				setcookie("login", $_POST["username"], time() + (TIMEOUT_MINUTES*60), '/');
				echo '<meta http-equiv="refresh" content="0">';
			}
			else
			{
				loginForm("Password incorrect!");
			}
		}
		else
		{
			loginForm("Username does not exist!");
		}
	}
	else
	{
		loginForm("Insert the password or the username!");
	}
}
else if (!isset($_COOKIE["login"]))
{
	loginForm();
}
else
{
	setcookie("login", $_COOKIE["login"], time() + (TIMEOUT_MINUTES*60), '/');
}

?>