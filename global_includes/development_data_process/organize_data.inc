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
    }
    // private function json_change_key($arr, $oldkey, $newkey) {
    //  $json = str_replace('"'.$oldkey.'":', '"'.$newkey.'":', json_encode($arr));
    //  return json_decode($json,true);
    // }
    public function oraganized_data(){
      $this->json_change_key();

      return $this->data;
    }
    private function obtain_ids(){
      
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
