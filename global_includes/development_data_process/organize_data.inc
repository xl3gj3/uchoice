<?php
  /**
   *
   */
  require "Database.class.inc";

  class organizing_data
  {
    public $data;
    private $db;

    private $dic_sensor_name = array(
        "TEMP" => "temperature",
        "CO2"  => "co2",
        "O2" => "o2",
        "HUMI" =>'humidity',
        "LIGH" => "light"
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
      var_dump($this->data);

      $this->determineSensorType();
      $this->json_change_key();
      $this->obtain_ids();
      $this->insert_date_time();
      // $this->round_number();

      // echo "before return out".PHP_EOL;
      return $this->data;
    }
    public function determineSensorType(){
      $temp_data = $this->data;
      unset($temp_data["serial_id"]);
      foreach ($temp_data as $sensorName => $sensorData) {
        $sensorNameArray = str_split($sensorName,1);
        var_dump($sensorNameArray[0]);
        // COMBAK: This is the place deal with the prefix , ie s,D,d;
        // the s is the sensor data, which just store into db
        // D and d is the digital input and output, this is realted to the front end display
        unset($sensorNameArray[0]);
        $newSensorName = implode("",$sensorNameArray);
        $this->data[$newSensorName] = $sensorData;
        unset($this->data[$sensorName]);
      }

    }
    public function insert_date_time(){
      $this->data["update_date"] = date("Y-m-d G:i:s",time());
      $this->data["day"] = date('D',time());
    }
    // private function round_number(){
    //   foreach ($this->data as $key => $value) {
    //     echo "the key is $key".PHP_EOL;
    //     echo "the type of value is " . gettype($value).PHP_EOL;
    //     if (gettype($value) == "double") {
    //       $this->data[$key] = round($this->data[$key],12);
    //     }
    //   }
    // }
    private function obtain_ids(){
      $this->db->query('SELECT customer_id from serial_number where serial_id = :serial_id')
               ->bind(':serial_id',$this->data["serial_id"])
               ->execute();
      $result = $this->db->single();
      // echo dechex(2147483647);
      // $this->data["customer_id"] = $result["customer_id"];
      // var_dump($result);
      // 2147483647
    }
    private function json_change_key() {
      $size = sizeof($this->data);
      $arr_key = array_keys($this->data);
      for ($i=0; $i < $size; $i++) {

        if (array_key_exists($arr_key[$i],$this->dic_sensor_name)) {
          // echo "the array key is " .$arr_key[$i].PHP_EOL;
          // echo "new key is ".$this->dic_sensor_name[$arr_key[$i]].PHP_EOL;
          $json = str_replace('"'.$arr_key[$i].'":', '"'.$this->dic_sensor_name[$arr_key[$i]].'":', json_encode($this->data));
          // echo "the json is ".PHP_EOL;
          // echo $json.PHP_EOL;
          $this->data = json_decode($json,true);
        }

      }
      // var_dump($json);
    }




  }


?>
