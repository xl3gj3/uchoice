<?php
  /**
   *
   */
  require "Database.class.inc";

  class organizing_data
  {
    public $data;
    private $db;

    private   $dic_sensor_name = array(
        "TEMP" => "temperature",
        "CO2"  => "co2"
      );
    function __construct($data)
    {
      $this->data = $data;
      $this->db = new Database();
      date_default_timezone_set("America/Vancouver");

    }
    // private function json_change_key($arr, $oldkey, $newkey) {
    //  $json = str_replace('"'.$oldkey.'":', '"'.$newkey.'":', json_encode($arr));
    //  return json_decode($json,true);
    // }
    public function oraganized_data(){
      $this->json_change_key();
      $this->obtain_ids();
      $this->round_number();

      $this->data["update_date"] = date("Y-m-d D G:i:s",time());
      return $this->data;
    }
    private function round_number(){
      foreach ($this->data as $key => $value) {
        echo "the key is $key".PHP_EOL;
        echo "the type of value is " . gettype($value).PHP_EOL;
        if (gettype($value) == "double") {
          $this->data[$key] = round($this->data[$key],2);
        }
      }
    }
    private function obtain_ids(){
      $this->db->query('SELECT customer_id from serial_number where serial_id = :serial_id')
               ->bind(':serial_id',hexdec($this->data["serial_id"]))
               ->execute();
      $result = $this->db->resultset();
      // echo dechex(2147483647);
      var_dump($result);
      // 2147483647
    }
    private function json_change_key() {
      $size = sizeof($this->data);
      $arr_key = array_keys($this->data);

      for ($i=0; $i < $size; $i++) {
        if (array_key_exists($arr_key[$i],$this->dic_sensor_name)) {
          $json = str_replace('"'.$arr_key[$i].'":', '"'.$this->dic_sensor_name[$arr_key[$i]].'":', json_encode($this->data));
        }
      }
      return json_decode($json,true);
    }




  }


?>
