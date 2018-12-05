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
    "msgTypeLengh"=>2,
    "name_len" => 12,
    "data_type_len" => 2
  );
  $msgType = array(
    "D" => "data"
  );
  $data_structure = array(
    "serial_id" => "",
    "sensor_type" => "",
    "data" => 0,
    "update_date" =>"",
    "day" => ""
  );
  $table_name = "sensor_data";
  $number_of_sensor = 0;

  // var_dump($dic_lenght);


  if ($_GET) {
    $db = new db_helper();
    $tranform = new parse_hex($dic_lenght);
    $data = $_GET["data"];
    $output = $tranform->parse_data($data);
    // echo "after parse".PHP_EOL;
    var_dump($output);
    // echo "after return from organization".PHP_EOL;

    if ($msgType[$output["msgType"]]) {
      unset($output["msgType"]);
      $number_of_sensor = $tranform->get_number_sensors();

      $organization = new organizing_data($output);
      $output = $organization->oraganized_data();
      var_dump($output);

      $arr_key = array_keys($output);
      for ($i=0; $i < sizeof($arr_key); $i++) {
        if (array_key_exists($arr_key[$i],$data_structure)) {
          $data_structure[$arr_key[$i]] = $output[$arr_key[$i]];
          unset($output[$arr_key[$i]]);
        }
      }
      $sensor_name = array_keys($output);

      for ($i=0; $i < $number_of_sensor; $i++) {
        $data_structure["sensor_type"] = $sensor_name[$i];
        $data_structure["data"] = $output[$sensor_name[$i]];

        // $status = $this->db->insert($this->data_structure, $this->table_name);
        $status = $db->insert($data_structure, $table_name);

      }
      if ($status) {
        echo "Insert Done";
      }
    }
  }

?>
