<?php
/**
 *
 */
 require "Database.class.inc";
 require "db_helper.inc";
class data_get
{
  private $db_helper;
  private $db;
  private $general_table_name = "data_product_";
  private $drop_col_name= ["data_id","serial_id","customer_id","version","sensors_number","generation",
                            "sensor_type","update_date","data"];
  private $unit = array(
    "o2" => "%",
    "co2" => "%",
    "temperature" => "C",
    "humidity" => "%"
  );
  private $static_key = ["customize_name","name"];

  // unset($preset_data_structure["version"]);
  // unset($preset_data_structure["sensors_number"]);
  // unset($preset_data_structure["sensor_type"]);
  // unset($preset_data_structure["update_date"]);
  // unset($preset_data_structure["data"]);
  private $product_info_key = ["customize_name","name","product_id"];

  public function get_customer_order_data($customer_info){
    // var_dump($customer_info);
    $this->db->query('select serial_number.product_id,serial_number.serial_id,serial_number.customize_name,product_list.*,customer_info.customer_id
                      from serial_number
                      inner join product_list on product_list.product_id = serial_number.product_id
                      inner join customer_info on serial_number.customer_id = customer_info.customer_id
                      where customer_info.customer_id = :customer_id;')
             ->bind(":customer_id",$customer_info["customer_id"])
             ->execute();
    $result = $this->db->resultset();
    // echo "<pre>";
    // var_dump($result);
    // echo "</pre>";
    return $result;

  }
  public function customize_product_name($data){
    $oldkey = "name";
    $newkey = "customize_name";
    $json = str_replace('"'.$oldkey.'":', '"'.$newkey.'":', json_encode($data));

    $data = json_decode($json,true);
    // var_dump($data);
    $this->db->query('UPDATE serial_number SET customize_name = :customize_name where serial_id = :serial_id')
             ->bind(':customize_name',$data[$newkey])
             ->bind(':serial_id',$data["serial_id"])
             ->execute();
    return $data;
  }
  public function get_sensor_data ($data){
    // var_dump($data);
    // $table = $this->general_table_name.$data["product_id"];
    $default_decimal = 3;
    $sensors_number = 0;
    $count = 0;
    $preset_data_structure = [];
    $final_result = [];
    $name = [];
    $output = [];
    $this->db->query('select sensor_data.*,serial_number.customize_name,product_list.name,product_list.generation,product_list.version,product_list.sensors_number
                      from sensor_data
                      inner join serial_number on serial_number.serial_id = sensor_data.serial_id
                      inner join product_list on product_list.product_id = serial_number.product_id
                      where serial_number.serial_id = :serial_id order by update_date desc;')
             ->bind(":serial_id",$data["serial_id"])
             ->execute();
    $result = $this->db->resultset();
    // use sensors number to know how many rows is a set of data
    $sensors_number = $result[0]["sensors_number"];
    for ($i=0; $i < sizeof($result) ; $i++) {
      if ($count == 0) {
        $preset_data_structure = $result[$i];
      }
      // add the o2, temp, etc... into the $preset_data_structure's key values
      $preset_data_structure[$result[$i]["sensor_type"]] = $result[$i]["data"];
      // assign the data for that key name;
      $preset_data_structure[$result[$i]["sensor_type"]] = round($preset_data_structure[$result[$i]["sensor_type"]],$default_decimal);
      // add the unit for the sensor type;
      $preset_data_structure[$result[$i]["sensor_type"]] = $preset_data_structure[$result[$i]["sensor_type"]].$this->unit[$result[$i]["sensor_type"]];
      $count = $count + 1;
      // when $count = sensors number,this mean we have completed the reading of 1 set of date
      // it is ready to go into the final_result array
      if ($count == $sensors_number) {
        $date_time = explode(" ",$preset_data_structure["update_date"]);
        // saperate date and time
        $preset_data_structure["update date"] = $date_time[0];
        $preset_data_structure["update time"] = $date_time[1];
        $preset_data_structure["ver"] = $preset_data_structure["generation"].".".$preset_data_structure["version"];
        for ($j=0; $j < sizeof($this->drop_col_name); $j++) {
          unset($preset_data_structure[$this->drop_col_name[$j]]);
        }
        // sort the result before going into the final result set
        // ksort($preset_data_structure);
        for ($k=0; $k < sizeof($this->static_key); $k++) {
          $name[$this->static_key[$k]] = $preset_data_structure[$this->static_key[$k]];
          unset($preset_data_structure[$this->static_key[$k]]);
        }
        $final_result[] = $preset_data_structure;
        // reset the count for new set of data
        $count = 0;
      }
      // echo "the count is $count".PHP_EOL;;


      // ksort($result[$i]);

    }
    $output["sensor_data"] = $final_result;
    $output["static_data"] = $name;
    return $output;
  }
  function __construct()
  {
    // $this->db_helper = new db_helper();
    $this->db = new Database();
  }
}

 ?>
