<?php
require_once('errorlogger.inc');
class loginDB
{
private $logindb;

public function __construct()
{
    $this->logindb = new mysqli("192.168.1.120","frank","frank","login");
    if ($this->logindb->connect_errno != 0)
    {
        echo "Error connecting to database: ".$this->logindb->connect_error.PHP_EOL;
               $options = array();
               $options[0] = 'e';
               $options[1] = 'loginServer';
               $options[2] = 'Error connecting to database: '.$this->logindb->connect_error.PHP_EOL;
                sendLogs($options);
        exit(1);
    }
    echo "correctly connected to database".PHP_EOL;
}

public function validateLogin($username,$password)
{
    $un = $this->logindb->real_escape_string($username);
    $pw = $this->logindb->real_escape_string($password);
    $statement = "select * from users where screenname = '$un';";
    $response = $this->logindb->query($statement);

    while ($row = $response->fetch_assoc())
    {
            echo "checking password for $username".PHP_EOL;
        if ($row["password"] == $pw)
        {
                echo "passwords match for $username".PHP_EOL;
                $options = array();
                $options[0] = 'info';
                $options[1] = 'loginServer';
                $options[2] = $username.' has logged in.';
                sendLogs($options);
            return 1;// password match
        }
            echo "passwords did not match for $username".PHP_EOL;
       
    }
  
        echo "$username was not found in the database".PHP_EOL;
        $options = array();
        $options[0] = 'info';
        $options[1] = 'loginServer';
        $options[2] = $username.' was not found in the database.';
        sendLogs($options);
   	return 0;
   
   
    }   
}

?>