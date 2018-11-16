<?php
  // require "../global_config/development_data_process/test.inc";
  require "../../global_includes/development_data_process/config.inc";
  require "../../global_includes/development_data_process/Database.class.inc";
  require "../../global_includes/development_data_process/db_helper.inc";
  require "../../global_includes/development_data_process/parse_hex.inc";
  require "../../global_includes/development_data_process/organize_data.inc";



  $dic_lenght = array(
    "id_len" => 8,
    "nubmer_sensors_len" => 2,
    "name_len" => 10,
    "data_type_len" => 2
  );

  // var_dump($dic_lenght);


  if ($_GET) {
    $db = new db_helper();
    $tranform = new parse_hex($dic_lenght);
    $data = $_GET["data"];

    $output = $tranform->parse_data($data);
    // echo "get request accepted".PHP_EOL;
    // echo "content is ".PHP_EOL;
    echo "after parsing ".PHP_EOL;
    var_dump($output);

    $organization = new organizing_data($output);
    $output = $organization->oraganized_data();


    // $output = json_change_key($output, "TEMP", "temperature");
    echo "after chaning key name ".PHP_EOL;

    var_dump($output);
    // echo hexdec($output["serial_id"]).PHP_EOL;
    // echo "before settting time zone".date("Y-m-d D G:i:s",time()).PHP_EOL;
    // date_default_timezone_set("America/Vancouver");
    // echo "after settting time zone".date("Y-m-d D G:i:s",time()).PHP_EOL;

    // echo $data;
    // TEMP: comment the db process

    // $parse_json = json_decode($json,true);
    // var_dump($parse_json);
    // {{url}}/sensor_process.php?id=1&data=AF75DC34024f322020000341a0cccd54454d50000341b170a4
    // $table_name = "data_product_".$parse_json["product_id"];
    // unset($parse_json["product_id"]);
    // $parse_json["update_date"] = date("Y-m-d G:i:s",time());
    //
    // $id = $db->insert($parse_json,$table_name);
    //
    // echo "save successfully and the id is $id".PHP_EOL;
    // $array = ["data"=>['name'=>"jerry","email"=>"jerry@hotmail.com"]];
    // var_dump($array);
    // $json_array = json_encode($array);
    // echo $json_array;
    // $data = json_decode($json);
    // var_dump($data);
  }
    // var_dump($_REQUEST);

?>
