<?php
  if ($_GET) {
    echo "get request accepted".PHP_EOL;
    echo "content is ".PHP_EOL;
    var_dump($_GET["data"]);
    $json = $_GET["data"];

    echo $json;
    $parse_json = json_decode($json);
    var_dump($parse_json);
    // $array = ["data"=>['name'=>"jerry","email"=>"jerry@hotmail.com"]];
    // var_dump($array);
    // $json_array = json_encode($array);
    // echo $json_array;
    // $data = json_decode($json);
    // var_dump($data);
  }
  // var_dump($_REQUEST);

  if ($_POST) {
    echo "post request accepted".PHP_EOL;
    echo "content is ".PHP_EOL;


  }
?>
