<?php
// require "../global_config/development_data_process/test.inc";
require "../global_config/development_data_process/config.inc";
require "../global_config/development_data_process/Database.class.inc";
require "../global_config/development_data_process/db_helper.inc";

  if ($_GET) {
    $db = new db_helper();
    // echo "get request accepted".PHP_EOL;
    // echo "content is ".PHP_EOL;
    // var_dump($_GET["data"]);
    $json = $_GET["data"];

    // echo $json;
    $parse_json = json_decode($json,true);
    var_dump($parse_json);
    $table_name = "data_product_".$parse_json["product_id"];
    unset($parse_json["product_id"]);
    $parse_json["update_date"] = date("Y-m-d G:i:s",time());

    $id = $db->insert($parse_json,$table_name);

    echo "save successfully and the id is $id".PHP_EOL;
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
