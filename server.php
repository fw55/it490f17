#!/usr/bin/php
<?php
require_once('path.inc');
require_once('get_host_info.inc');
require_once('lib.inc');
require_once('login.php.inc');
function doLogin($username,$password)
{
    $login = new logindb();
    $output = $login->validateLogin($username,$password);
	if($output)
		{
			echo "success";
		}
	return $output;
	
}
function doErrorLog($level,$loc,$msg) {
  
  file_put_contents('/home/dean/git/rabbitmq/errorlog'.date("j.n.Y").'.txt', $msg, FILE_APPEND);
 
  
}
function requestProcessor($request)
{
  echo "received request".PHP_EOL;
  var_dump($request);
  if(!isset($request['type']))
  {
    return "ERROR: unsupported message type";
  }
  switch ($request['type'])
  {
    case "errorLog":
      return doErrorLog($request['level'],$request['loc'],$request['message']);
    case "login":
      return doLogin($request['username'],$request['password']);
    case "validate_session":
      return doValidate($request['sessionId']);
  }
  return array("returnCode" => '0', 'message'=>"Server received request and processed");
}

$server = new rabbitMQServer("server.ini","testServer");

$server->process_requests('requestProcessor');
exit();
?>